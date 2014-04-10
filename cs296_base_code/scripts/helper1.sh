#!/bin/bash
cd ../data
rm -f g2help.txt
awk 'BEGIN {FS = "," } {s=$4+$5+$6; print $1","s} END {}' g23_projectdata.csv >> g2help.txt