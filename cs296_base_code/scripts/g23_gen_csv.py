#!/usr/bin/env python3
from os import popen
from re import findall
from random import sample
iteration=100
re_runs=30
re_runs_to_select=15

first_csv=open("../data/g23_projectdata1.csv","w")
second_csv=open("../data/g23_projectdata2.csv","w")


def generate_first_csv():
	for a,b in [[x,y] for x in range(1,iteration+1) for y in range(1,re_runs+1)]:
		a=str(a)
		b=str(b)
		s=popen('echo '+a+'| ../mybins/cs296_23_exe').read()
		first_csv.write(",".join([a,b]+findall(r'\d*\.\d*',s))+'\n')
generate_first_csv()
first_csv.close()

def generate_second_csv():
	first_csv=open("../data/g23_projectdata1.csv","r")
	l=[(x-1)*re_runs+y for x in range(1,iteration+1) for y in sample(range(1,re_runs+1),re_runs_to_select)]
	for i,line in enumerate(first_csv):
		if i+1 in l:
			second_csv.write(line.strip()+'\n')
generate_second_csv()
second_csv.close()



