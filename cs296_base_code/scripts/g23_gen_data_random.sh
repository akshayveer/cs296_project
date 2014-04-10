#!/bin/bash
cd ../data
rm -f g23_projectdata_random.csv
touch g23_projectdata_random.csv
i=0
iters=100
steps=30
range=15
while [ $i -ne $iters ]
do
	j=0
	while [ $j -ne $steps ]
	do
		rand=$RANDOM
		let "rand %= $range"
		let "rand += 1"
		let "rand += $(($i*$range))"
		sed -n "$rand"p g23_projectdata.csv >> g23_projectdata_random.csv
		j=$(($j+1))
	done
	i=$(($i+1))
done