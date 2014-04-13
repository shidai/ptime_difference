NAME: ptime_difference, to calculate the differences between profiles and investigate the profile evolution
AUTHOR: SHI DAI
VERSION: 1.0 24-FEB-2014
		 
INPUT: fname, (tname,) nchn_start, nchn_end, frac_off, (align)
	   fname: the name of data file, PSRFITS format
	   (tname: the template, in PSRFITS format (-std) or ptime format (-pt); the profiles in fname will be aligned with respect to the template 
		       and then calculate the difference)
	   nchn_start: the first channel used
	   nchn_end: the last channel used; these channels will be substracted from the central channel
	   frac_off: off pulse fraction; 
       align: align the profile or not

OUTPUT: 


To compile: sh run.sh (fftw3 and cfitsio needed)

Usage: ./ptime_difference.out -f fname (-std tname; -pt tname) -nchn_start 1 -nchn_end 16 -frac_off 0.1 (-align)
		-fname: data file, using "...*..." to analyze multiple files; 
		(-tname: templates; -std: standard template format; -pt: ptime template;)
	    -nchn_start: the first channel used;
	    -nchn_end: the last channel used; 
		-frac_off: off pulse fraction; 
		(-align): add -align, the profiles will be aligned with respect to the reference first

