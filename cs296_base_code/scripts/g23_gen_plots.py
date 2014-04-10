#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt

iteration=100
re_runs=30
re_runs_to_select=15
highest_roll_no=iteration

first_csv=open("../data/g23_projectdata1.csv","r")
second_csv=open("../data/g23_projectdata2.csv","r")

averaged_csv=open("../data/averaged.csv","w")

step_time_for_highest_no=[]
cumulative_step_time=[0]

def generate_averaged_data():
	no_of_lines_counted=0
	average_time=[0,0,0,0,0]    #step_time,collision_time,velocity_time,postion_time,loop_time,error
	for line in first_csv:
		no_of_lines_counted+=1
		l=line.split(',')
		if(no_of_lines_counted==1):
			max_value=float(l[2])
			min_value=float(l[2])
		max_value=max(max_value,float(l[2]))
		min_value=min(min_value,float(l[2]))
		average_time=[x+float(y) for x,y in zip(average_time,l[2:])]
		if(no_of_lines_counted==re_runs):
			average_time=[x/re_runs for x in average_time]+[(max_value-min_value)/2]
			averaged_csv.write(l[0]+','+','.join([str(x) for x in average_time])+ '\n')
			average_time=[0,0,0,0,0]
			no_of_lines_counted=0

random_step_time=[]

def generate_averaged_random_data():
	no_of_lines_counted=0
	average_time=0
	for line in second_csv:
		no_of_lines_counted+=1
		l=line.split(',')
		average_time+=float(l[2])
		if(no_of_lines_counted==re_runs_to_select):
			random_step_time.append(average_time/re_runs_to_select)
			average_time=0
			no_of_lines_counted=0

generate_averaged_data()
averaged_csv.close()
first_csv.close()
generate_averaged_random_data()

data=np.genfromtxt("../data/averaged.csv",delimiter=',',names=['iteration','step','collsion','velocity','postion','loop','error'])


#first plot
fig1=plt.figure(1) 
plt.bar(data['iteration'],data['step'],label="step time")
plt.plot(data['iteration'],data['loop'],label="loop time")
plt.title("Average Step Time  and loop time vs Iterations")
plt.xlabel("Number of Iterations")
plt.ylabel("Average Step Time , Loop Time  (ms)")
plt.legend(loc='upper center', shadow=True)
plt.savefig('../plots/1g23_plot01.png')


#second plot
plt.figure(2)
plt.plot(data['iteration'],data['step'],label="step")
plt.plot(data['iteration'],data['collsion'],label="collsion")
plt.plot(data['iteration'],data['velocity'],label="velocity")
plt.plot(data['iteration'],data['postion'],label="postion")
plt.plot(data['iteration'],data['collsion']+data['velocity']+data['postion'],label="averaged")
plt.title("All time constraints vs Iterations")
plt.xlabel("Iterations")
plt.ylabel("Averaged time for various parameters, and their sums (ms)")
plt.legend(loc='upper center', shadow=True)
plt.savefig('../plots/1g23_plot02.png')


#third plot
plt.figure(3)
plt.errorbar(data['iteration'], data['step'], yerr=data['error'],label="step time errorbar")
plt.legend(loc='upper center', shadow=True)
plt.title("Error in Reruns vs Iterations")
plt.xlabel("Iterations")
plt.ylabel("Error in Reruns (ms)")
plt.savefig('../plots/1g23_plot03.png')


#fourth plot
plt.figure(4)
m1,b1=np.polyfit(data['iteration'],data['step'],1)
m2,b2=np.polyfit(np.arange(1,iteration+1),random_step_time,1)
plt.plot(data['iteration'],data['step'],'ro',data['iteration'],m1*data['iteration']+b1,'r',label="step time")
plt.plot(np.arange(1,iteration+1),random_step_time,'bo',np.arange(1,1+iteration),m2*np.arange(1,1+iteration)+b2,'b',label="step time")
plt.title("Linear regression of step time and iteration from two csv files")
plt.legend(loc='upper center', shadow=True)
plt.xlabel("Iterations")
plt.ylabel("Average Step Time")
plt.savefig('../plots/1g23_plot04.png')
#plt.show()
