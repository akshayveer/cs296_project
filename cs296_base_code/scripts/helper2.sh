#!/bin/bash
cd ../data
rm -f g3help.txt
touch g3help.txt
i=0
iters=100
steps=15
while [ $i -ne $iters ]
do
	start=$((($i*$steps)+1))
	end=$((($i+1)*$steps))
	max=999
	min=0
	echo -n $(($i+1))"," >> g3help.txt
	sed -n "$start,$end"p g23_projectdata.csv | awk -v t=$steps 'BEGIN {FS = ",";a=0;b=999} {s+=$3;if($3>a)a=$3;if($3<b)b=$3} END {print s/t","a/2.0-b/2.0}' >> g3help.txt
	i=$(($i+1))
done