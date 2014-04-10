#!/bin/bash
cd ../data
rm -f g5help*.txt
i=0
iters=100
steps=15
while [ $i -ne $iters ]
do
	start=$((($i*$steps)+1))
	end=$((($i+1)*$steps))
	echo -n $(($i+1)) "," >> g5help1.txt
	sed -n "$start,$end"p g23_projectdata.csv | awk -v t=$steps 'BEGIN {FS = ","} {s+=$3} END {print s/t}' >> g5help1.txt
	i=$(($i+1))
done

let "i = 0"
let "steps = 15"
while [ $i -ne $iters ]
do
	start=$((($i*$steps)+1))
	end=$((($i+1)*$steps))
	echo -n $(($i+1)) "," >> g5help2.txt
	sed -n "$start,$end"p g23_projectdata_random.csv | awk -v t=$steps 'BEGIN {FS = ","} {s+=$3} END {print s/t}' >> g5help2.txt
	i=$(($i+1))
done