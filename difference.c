// calculate the differences between profiles
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include <gsl/gsl_rng.h>
//#include <gsl/gsl_randist.h>
#include "ptime_difference.h"

int find_peak (int n, double *s, int *position)
{
	int i;
	double temp[n];
	double peak;

	for (i = 0; i < n; i++)
	{
		temp[i] = s[i];
	}

	double a, b, c;
	for (i = 0; i < n-1; i++)
	{
		a = fabs(temp[i]);
		b = fabs(temp[i+1]);
		c = (a >= b ? a : b);

		temp[i+1] = c;
	}
	peak = temp[n-1];

	for (i = 0; i < n; i++)
	{
		if (fabs(peak-fabs(s[i])) < 1.0e-3)
		{
			(*position) = i;
		}
	}

	return 0;
}

double find_peak_value (int n, double *s)
{
	int i;
	double temp[n];

	for (i = 0; i < n; i++)
	{
		temp[i] = s[i];
	}

	double a, b, c;
	for (i = 0; i < n-1; i++)
	{
		//a = temp[i];
		//b = temp[i+1];
		a = fabs(temp[i]);
		b = fabs(temp[i+1]);
		c = (fabs(a) >= fabs(b) ? a : b);

		temp[i+1] = c;
	}

	return temp[n-1];
}

int on_pulse (int nphase, int peak_position, double *in, double *out, double frac)
// define the on_pulse range, frac_on of the phase
{
	int n = nphase;
	int num = (int)(n*frac);
	int i;
	for (i = 0; i < num; i++)
	{
		if ((peak_position-(int)(num/2)+i) < 0)
		{
			out[i] = in[(n-1)+(peak_position-(int)(num/2)+i)];
		}
		else if ((peak_position-(int)(num/2)+i) > n-1)
		{
			out[i] = in[(peak_position-(int)(num/2)+i)-(n-1)];
		}
		else
		{
			out[i] = in[peak_position-(int)(num/2)+i];
		}
	}

	return 0;
}

int off_pulse (int nphase, int peak_position, double *in, double *out, double frac_off, double frac_on)
// define the on_pulse range, 10% of the phase
{
	int n = nphase;
	int num_off = (int)(n*frac_off);
	int num_on = (int)(n*frac_on);
	int i,j;
	double small;
	double temp;
	int index = 0;

	double ave;
	ave = 0.0;
	for (i = 0; i < num_off; i++)
	{
		if ((peak_position+(int)(num_on/2)+i) > n-1)
		{
			ave += in[(peak_position+(int)(num_on/2)+i)-(n-1)];
		}
		else
		{
			ave += in[peak_position+(int)(num_on/2)+i];
		}
	}
	ave = ave/num_off;

	for (i = 0; i < n; i++)
	{
		if (i == 0)
		{
			small = 0.0;
			for(j = 0; j < num_off; j++)
			{
				small += (in[j]-ave)*(in[j]-ave);
			}
			small = sqrt(small/num_off);
		}
			
		temp = 0.0;
		for(j = 0; j < num_off; j++)
		{
			if ((i+j) > n-1)
			{
				temp += (in[(i+j)-(n-1)]-ave)*(in[(i+j)-(n-1)]-ave);
			}
			else 
			{
				temp += (in[i+j]-ave)*(in[i+j]-ave);
			}
		}
		temp = sqrt(temp/num_off);

		small = (temp <= small ? temp : small);
		index = (temp <= small ? i : index);
		//printf ("%d %lf %lf\n", index, small, ave);
	}

	for (i = 0; i < num_off; i++)
	{
		if ((index+i) > n-1)
		{
			out[i] = in[(index+i)-(n-1)];
		}
		else 
		{
			out[i] = in[index+i];
		}
	}

	return 0;
}

int remove_baseline (double *in, double frac_off, double frac_on, int n, double *out)
{
	// define the off_pulse range of std, frac_off is the fraction of the phase
	int num_off = (int)(n*frac_off);
	double off_0[num_off];

	int peak_position;
	find_peak (n, in, &peak_position);
	off_pulse(n, peak_position, in, off_0, frac_off, frac_on);

	// normalize std
	int i;
	double baseline = 0.0;
    for (i = 0; i < num_off; i++)
    {
        baseline += off_0[i];
        //average_s += s_off[i];
    }
	baseline = baseline/num_off;

    printf ("the baseline of std is: %lf \n", baseline);
    //printf ("average is: %lf %lf\n", average, average_s);

	for (i = 0; i < n; i++)
	{
		out[i] = (in[i]-baseline);
		//s_norm[i] = (s[i]-baseline)/(s_peak-baseline);
	}
	
	return 0;
}

int pre_diff (double *s, double *p, int nphase, double frac_on, double *s_out, double *p_out)
{
	double frac_off = 0.1;  // the off_pulse is fixed to 0.1, which is valid for most pulsars
	int n = nphase;
	
	// remove the baseline
	double s_nobase[n], p_nobase[n];
	remove_baseline (s, frac_off, frac_on, n, s_nobase);
	remove_baseline (p, frac_off, frac_on, n, p_nobase);

	// find the peak and peak position
	int s_peak_position, p_peak_position;
	double s_peak, p_peak;
	
	s_peak = find_peak_value (n, s_nobase);
	p_peak = find_peak_value (n, p_nobase);
	printf ("s_peak: %lf\n", s_peak);
	printf ("p_peak: %lf\n", p_peak);

	find_peak (n, s_nobase, &s_peak_position);
	find_peak (n, p_nobase, &p_peak_position);

	// define the on_pulse range, frac_on is the fraction of the phase

	on_pulse(n, s_peak_position, s_nobase, s_out, frac_on);
	on_pulse(n, p_peak_position, p_nobase, p_out, frac_on);

    return 0;
}

int basic (char *fname, int nchn_start, int nchn_end, double frac_on)
//int real_obs (char *fname, char *tname, char *oname, int mode, FILE *fp, double frac_on, double frac_off)
{
	//int mid = 1;
	int mid = (int)((nchn_end - nchn_start + 1)/2) + nchn_start - 1;
	printf ("central channel: %d\n", mid);
	
	// name of different extension of data files
	char name_data[50]; 
	char name_psrparam[50]; 

	char data[] = "[SUBINT]";
	char psrparam[] = "[PSRPARAM]";

	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	int h, i, j, p;
	{
		// name of different extension
		strcpy(name_data,fname);
		strcpy(name_psrparam,fname);

		strcat(name_data, data);
		strcat(name_psrparam, psrparam);

		////////////////////////////////////////////////////
		
		double psrfreq;
		psrfreq = read_psrfreq(name_psrparam);
		printf ("PSR frequency: %.15lf\n", psrfreq);

		////////////////////////////////////////////////////

		int nphase;
		int nchn;
		int nsub;
		int npol;
	
		nchn = get_nchan(name_data);	
		npol = get_npol(name_data);	
		nsub = get_subint(name_data);	
		nphase = get_nphase(name_data);	

		// new nphase for on pulse region
		int nphase_new = (int)(nphase*frac_on);

		//printf ("%d\n", nchn);
		////////////////////////////////////////////////

		//readfile(argv[1],&n,tt,s);
		//read_prof(std,1,s_multi,nphase);
	
		////////////////////////////////////////////////////////////////////////////////

		double p_multi[nchn*npol*nphase];
		double p_temp[nphase];

		// start to calculate shape paremeter for different subint
		for (h = 1; h <= nsub; h++)
		{
			// simulate data

			//SNR = 500.0 + 200.0*i;
			//simulate(n,SNR,s,p_temp);

			// read profiles from data file
			read_prof(name_data,h,p_multi,nphase,npol,nchn);
			//readfile(argv[2],&n,tt,p_multi);

			// start to calculate shape parameter for different channels
			for (i = 0; i < npol; i++)
			//for (i = 0; i < nchn; i++)
			{
				double ref[nphase];
				int jj;
				for (jj = 0; jj < nphase; jj++)
				{
					ref[jj] = p_multi[i*nchn*nphase + mid*nphase + jj];
				}

				for (p = nchn_start-1; p < nchn_end; p++)
				//for (p = 0; p < npol; p++)
				{
					for (j = 0; j < nphase; j++)
					{
						p_temp[j] = p_multi[i*nchn*nphase + p*nphase + j];
					}

					double ref_new[nphase_new];
					double p_new[nphase_new];
					pre_diff (ref, p_temp, nphase, frac_on, ref_new, p_new);

					diff_prof_std (ref_new, p_new, psrfreq, nphase_new, p, i, h, fname);
				}
			}
		}
	}

	return 0;
}


int advanced (char *fname, char *tname, int mode, int nchn_start, int nchn_end, double frac_on)
//int real_obs (char *fname, char *tname, char *oname, int mode, FILE *fp, double frac_on, double frac_off)
{
	// name of different extension of data files
	char name_data[50]; 
	char name_psrparam[50]; 

	char data[] = "[SUBINT]";
	char psrparam[] = "[PSRPARAM]";

	// read name of std
	char std[50];
	strcpy(std,tname);
	if ( mode == 1)
	{
		strcat(std, data);
	}

	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	int h, i, j, p;
	{
		// name of different extension
		strcpy(name_data,fname);
		strcpy(name_psrparam,fname);

		strcat(name_data, data);
		strcat(name_psrparam, psrparam);

		////////////////////////////////////////////////////
		
		double psrfreq;
		psrfreq = read_psrfreq(name_psrparam);
		printf ("PSR frequency: %.15lf\n", psrfreq);

		////////////////////////////////////////////////////

		int nphase;
		int nchn;
		int nsub;
		int npol;
	
		nchn = get_nchan(name_data);	
		npol = get_npol(name_data);	
		nsub = get_subint(name_data);	
		nphase = get_nphase(name_data);	

		// new nphase for on pulse region
		int nphase_new = (int)(nphase*frac_on);

		//printf ("%d\n", nchn);
		////////////////////////////////////////////////

		// read a std
		double s_multi[nphase*nchn*npol];
		double s_temp[nphase];

		//readfile(argv[1],&n,tt,s);
		//read_prof(std,1,s_multi,nphase);
	
		// check the channel and phase number of template
		check_std(std,1,mode,nchn,nphase,npol);

		read_std(std,1,s_multi,nphase,mode,nchn,npol);

		////////////////////////////////////////////////////////////////////////////////

		double p_multi[nchn*npol*nphase];
		double p_temp[nphase];

		// start to calculate shape paremeter for different subint
		for (h = 1; h <= nsub; h++)
		{
			// simulate data

			//SNR = 500.0 + 200.0*i;
			//simulate(n,SNR,s,p_temp);

			// read profiles from data file
			read_prof(name_data,h,p_multi,nphase,npol,nchn);
			//readfile(argv[2],&n,tt,p_multi);

			// start to calculate shape parameter for different channels
			for (i = 0; i < npol; i++)
			//for (i = 0; i < nchn; i++)
			{
				for (p = nchn_start-1; p < nchn_end; p++)
				//for (p = 0; p < npol; p++)
				{
					for (j = 0; j < nphase; j++)
					{
						p_temp[j] = p_multi[i*nchn*nphase + p*nphase + j];
						s_temp[j] = s_multi[i*nchn*nphase + p*nphase + j];
					}

					double s_new[nphase_new];
					double p_new[nphase_new];
					pre_diff (s_temp, p_temp, nphase, frac_on, s_new, p_new);

					diff_prof_std (s_new, p_new, psrfreq, nphase_new, p, i, h, fname);
				}
			}
		}
	}

	return 0;
}

