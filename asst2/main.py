import fcfs
import srtf
import priority
import mlfq
import ticket
import rr


fo = open("input.txt",'r')
list1 = fo.readLines()

for i in range(len(list1)):
	temp = list1[i].split(' ')
	pid = int(temp[0])
	priority = int(temp[1])
	
