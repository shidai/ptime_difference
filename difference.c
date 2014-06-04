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
		a = temp[i];
		b = temp[i+1];
		//a = fabs(temp[i]);
		//b = fabs(temp[i+1]);
		c = (a >= b ? a : b);

		temp[i+1] = c;
	}
	peak = temp[n-1];

	for (i = 0; i < n; i++)
	{
		if (fabs(peak-s[i]) < 1.0e-3)
		//if (fabs(peak-fabs(s[i])) < 1.0e-3)
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
		a = temp[i];
		b = temp[i+1];
		//a = fabs(temp[i]);
		//b = fabs(temp[i+1]);
		c = (a >= b ? a : b);
		//c = (fabs(a) >= fabs(b) ? a : b);

		temp[i+1] = c;
	}

	return temp[n-1];
}

int corr (double *s, double *p, int nphase)
{
	/*
	FILE *fp1, *fp2;

	if ((fp1 = fopen(argv[1], "r")) == NULL)
	{
		fprintf (stdout, "Can't open file\n");
		exit(1);
	}

	if ((fp2 = fopen(argv[2], "r")) == NULL)
	{
		fprintf (stdout, "Can't open file\n");
		exit(1);
	}

	float x1[1024], x2[1024];
	int i = 0;
	while (fscanf (fp1, "%f", &x1[i]) == 1)
	{
		i++;
	}

	i = 0;
	while (fscanf (fp2, "%f", &x2[i]) == 1)
	{
		i++;
	}
	*/

	double r[nphase];
	int i, j;
	for (j = 0; j < nphase; j++)
	{
		r[j] = 0.0;
		for (i = 0; i < nphase; i++)
		{
			if ((i+j) > (nphase-1))
			{
				r[j] += p[i]*s[i+j-(nphase-1)];
			}
			else
			{
				r[j] += p[i]*s[i+j];
			}
			//printf ("%f %f\n", x1[i], x2[i]);
		}
	}

	int shift;
	find_peak (nphase, r,  &shift);
	/*
	for (j = 0; j < 1024; j++)
	{
		printf ("%f\n", r[j]);
	}
	*/

	return -shift;
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

int def_off_pulse (int nphase, double *in, double frac_off)
// define the off pulse region based on I, return the starting index of off pulse region
// using frac_off to calculate the off pulse region
{
	int n = nphase;
	int num_off = (int)(n*frac_off);
	int i,j;
	double small;
	double temp;
	int index = 0;

	for (i = 0; i < n; i++)
	{
		if (i == 0)
		{
			small = 0.0;
			for(j = 0; j < num_off; j++)
			{
				small += (in[j]+30000)*(in[j]+30000);
			}
			small = sqrt(small/num_off);
		}
			
		temp = 0.0;
		for(j = 0; j < num_off; j++)
		{
			if ((i+j) > n-1)
			{
				temp += (in[(i+j)-(n-1)]+30000)*(in[(i+j)-(n-1)]+30000);
			}
			else 
			{
				temp += (in[i+j]+30000)*(in[i+j]+30000);
			}
		}
		temp = sqrt(temp/num_off);

		small = (temp <= small ? temp : small);
		index = (temp <= small ? i : index);
		//printf ("%d %lf %lf\n", index, small, ave);
	}

	return index;
}

int off_pulse (int nphase, int index, double *in, double *out, double frac_off)
// get the off_pulse region
{
	int n = nphase;
	int num_off = (int)(n*frac_off);
	int i;

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

int remove_baseline (double *in, int index, double frac_off, int n, double *out)
{
	// define the off_pulse range, frac_off is the fraction of the phase
	// index is the starting point of the off_pulse range
	int num_off = (int)(n*frac_off);
	double off_0[num_off];

	off_pulse (n, index, in, off_0, frac_off);

	int i;
	double baseline = 0.0;
    for (i = 0; i < num_off; i++)
    {
        baseline += off_0[i];
        //average_s += s_off[i];
    }
	baseline = baseline/num_off;

    //printf ("the baseline of std is: %lf \n", baseline);
    //printf ("average is: %lf %lf\n", average, average_s);

	for (i = 0; i < n; i++)
	{
		out[i] = (in[i]-baseline);
		//s_norm[i] = (s[i]-baseline)/(s_peak-baseline);
	}
	
	return 0;
}

int pre_diff (double *s, int nphase, double frac_off, double *s_out)
{
	int n = nphase;
	
	int index;
	index = def_off_pulse (n, s, frac_off);
	// remove the baseline
	remove_baseline (s, index, frac_off, n, s_out);

    return 0;
}

int simple (char *fname, int nchn_start, int nchn_end, double frac_off)
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

				double ref_new[nphase];
				pre_diff (ref, nphase, frac_off, ref_new);

				for (p = nchn_start-1; p < nchn_end; p++)
				//for (p = 0; p < npol; p++)
				{
					for (j = 0; j < nphase; j++)
					{
						p_temp[j] = p_multi[i*nchn*nphase + p*nphase + j];
					}

					double p_new[nphase];
					pre_diff (p_temp, nphase, frac_off, p_new);

					diff_prof_simple (ref_new, p_new, nphase, p, i, h, fname);
				}
			}
		}
	}

	return 0;
}

int basic (char *fname, int nchn_start, int nchn_end, double frac_off)
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

				double ref_new[nphase];
				pre_diff (ref, nphase, frac_off, ref_new);

				for (p = nchn_start-1; p < nchn_end; p++)
				//for (p = 0; p < npol; p++)
				{
					for (j = 0; j < nphase; j++)
					{
						p_temp[j] = p_multi[i*nchn*nphase + p*nphase + j];
					}

					double p_new[nphase];
					pre_diff (p_temp, nphase, frac_off, p_new);

					diff_prof_std (ref_new, p_new, psrfreq, nphase, p, i, h, fname);
				}
			}
		}
	}

	return 0;
}


int advanced (char *fname, char *tname, int mode, int nchn_start, int nchn_end, double frac_off)
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

					double s_new[nphase];
					double p_new[nphase];
					pre_diff (s_temp, nphase, frac_off, s_new);
					pre_diff (p_temp, nphase, frac_off, p_new);

					diff_prof_std (s_new, p_new, psrfreq, nphase, p, i, h, fname);
				}
			}
		}
	}

	return 0;
}

