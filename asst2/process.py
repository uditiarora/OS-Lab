class process:
	def __init__(self,pid,priority,at,times):
		self.pid = pid
		self.priority = priority
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
