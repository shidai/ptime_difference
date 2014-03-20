#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "ptime_difference.h"

int main (int argc, char *argv[])
{
	//int h,i,j,k;

	//////////////////////////////////////////////////////
	char fname[128];   // name of data file
	char tname[128];   // name of template
	//char oname[128];   // name of output .tim
	int mode = 0; // Default: without templates; to distinguish different type of templates
	double frac_on;

	int nchn_start, nchn_end;

	int i;
	int index, n;
	for (i = 1; i < argc; i++)
    {
		if (strcmp(argv[i],"-f") == 0)
		{
            index = i + 1;
			n = 0;
			while ( (index + n) < argc && strcmp(argv[index+n],"-std") != 0 && strcmp(argv[index+n],"-pt") != 0 && strcmp(argv[index+n],"-frac_on") != 0 && strcmp(argv[index+n],"-nchn_start") != 0 && strcmp(argv[index+n],"-nchn_end") != 0)
			//while ( (index + n) < argc && strcmp(argv[index+n],"-std") != 0 && strcmp(argv[index+n],"-pt") != 0 && strcmp(argv[index+n],"-o") != 0 && strcmp(argv[index+n],"-sim") != 0 && strcmp(argv[index+n],"-frac_on") != 0 && strcmp(argv[index+n],"-frac_off") != 0)
			{
				n++;
		    }
			i = index+n-1;
			//strcpy(fname,argv[++i]);
		}
		else if (strcmp(argv[i],"-std") == 0)
		{
			strcpy(tname,argv[++i]);
			mode = 1; // standard template format
			printf ("standard template format\n");
			//sscanf(argv[++i],"%d",&nbin);
		}
		else if (strcmp(argv[i],"-pt") == 0)
		{
			strcpy(tname,argv[++i]);
			mode = 2; // ptime template
			printf ("ptime template format\n");
		}
		else if (strcmp(argv[i],"-frac_on") == 0)
		{
			frac_on = atof(argv[++i]);
		}
		else if (strcmp(argv[i],"-nchn_start") == 0)
		{
			nchn_start = atof(argv[++i]);
		}
		else if (strcmp(argv[i],"-nchn_end") == 0)
		{
			nchn_end = atof(argv[++i]);
			//printf ("%lf\n", frac_off);
		}
		else 
		{
			printf ("Wrong options!!!\n");
			printf ("Usage: ptime_difference.out -f fname (-std tname; -pt tname) -nchn_start num1 -nchn_end num2\n"
					"       Calculate the differences between profiles.\n"
					"       -f fname: data file;\n" 
					"       tname: templates;\n" 
					"       -std: standard template format;\n" 
					"       -pt: ptime template;\n"
					"       -nchn_start: the first channel used;\n"
					"       -nchn_end: the last channel used;\n"); 
			exit (0);
		}
    }
	//printf ("%d\n", smode);

	// start to deal with different data file
	//
	// open file to write toa 
	//FILE *fp;
	//if ((fp = fopen(oname, "w+")) == NULL)
	//{
    //	fprintf (stdout, "Can't open file\n");
	//	exit(1);
	//}
    //fprintf (fp, "S0    S    err\n");
	/////////////////////////////////////////////////////////
	
	if (mode == 0)
	{
		int k;
		for (k = index; k < index + n; k++)
		{
			// get the data file name
			strcpy(fname,argv[k]);
			basic(fname, nchn_start, nchn_end, frac_on);
		}
	}
	else if (mode == 1 || mode == 2)
	{
		int k;
		for (k = index; k < index + n; k++)
		{
			// get the data file name
			strcpy(fname,argv[k]);
			advanced(fname, tname, mode, nchn_start, nchn_end, frac_on);
		}
	}

    //if (fclose (fp) != 0)
	//	fprintf (stderr, "Error closing\n");

	return 0;
}
