#!/bin/bash
cd ../data
rm -f g23_projectdata.csv
touch g23_projectdata.csv
i=0
iters=100
steps=15
while [ $i -ne $iters ]
do
	j=0
	while [ $j -ne $steps ]
	do
		echo -n $(($i+1))","$(($j+1))"," >> g23_projectdata.csv
		../mybins/cs296_23_exe <<< $(($i+1)) | egrep -o '[0-9]*\.[0-9]*' | tr '\n' ',' | sed s'/.$//' >> g23_projectdata.csv
		printf "\n" >> g23_projectdata.csv
		j=$(($j+1))
	done
	i=$(($i+1))
done
