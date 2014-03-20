#!/bin/bash

rm *_diff
rm Diff*

./ptime_difference.out -f 0613_20cm.pTf16 -nchn_start 1 -nchn_end 16 -frac_on 0.6 

touch 0613_20cm_diff

#for name in `ls Diff*20cm*`; do
for nchn in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15; do
	name=`ls Diff*20cm*_nchn_"$nchn"_*`
	paste -d ' ' 0613_20cm_diff $name > temp
	rm 0613_20cm_diff
	mv temp 0613_20cm_diff
done
