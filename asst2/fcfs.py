class process:
	def __init__(self,pid,priority,low,high,at,times):
		self.pid = pid
		self.priority = priority
		self.ticket_low = low
		self.ticket_high = high
		self.at = at
		self.times = times
		self.io = False
		self.io_end = 0
		self.cpu_end = 0
		self.rs = -1
		self.wt = 0
		self.tat = 0
		self.cpu_time = 0
		self.io_time = 0
		for i in range(0,len(times),2):
			self.cpu_time += times[i]
		for i in range(1,len(times),2):
			self.io_time += times[i]
		self.tot_time = self.cpu_time
		self.queue = 0
		self.queue_time = 0
		
def fcfs(p):
	p.sort(key = lambda x : x.at)
	n = len(p)
	count = 0
	cpu_end = 0
	io_end = 0
	proc = []
	while count!=n:
		i = 0
		while(i<len(p) and (p[i].at > cpu_end or p[i].io_end > cpu_end)):
			i += 1
		if(i<len(p)):
			if(p[i].rs==-1):
				p[i].rs = cpu_end - p[i].at
			cpu = p[i].times.pop(0)
			cpu_end +=  cpu
			p[i].cpu_end = cpu_end
			io_end = max(io_end,cpu_end)
			p[i].tot_time -= cpu

			if(len(p[i].times)>0):
				io = p[i].times.pop(0)
				io_end += io
				p[i].io_end = io_end
			print(p[i].pid,io_end,cpu_end)
			if(len(p[i].times)==0):
				p[i].tat = max(cpu_end,p[i].io_end) - p[i].at
				proc.append(p[i])
				p.pop(i)
				count += 1
			else:
				temp = p[i]
				p.pop(i)
				p.append(temp)
		else:
			cpu_end += 1
			#print("hi")
	print("PID  AT  RT  WT  TAT")
	for i in range(0,len(proc)):
		proc[i].wt = proc[i].tat - proc[i].rs - proc[i].cpu_time
		print(proc[i].pid," ",proc[i].at," ",proc[i].rs," ",proc[i].wt," ",proc[i].tat)


p1 = process(1,5,0,49,3,[4])
p2 = process(2,1,50,74,5,[3])
p3 = process(3,3,75,99,0,[2])
p4 = process(3,3,75,99,5,[1])
p5 = process(3,3,75,99,4,[3])
p = [p1,p2,p3,p4,p5]
fcfs(p)					

