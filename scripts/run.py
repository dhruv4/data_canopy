
import os



def run_1(filename,outfile,numactl):
	os.system("rm "+outfile)
	for i in range(2,20):
		#size = pow(2,i)
		size=i
		print size
		f = os.system(numactl + " ../bin/"+filename+" "+str(size) +" 1000 "+" 100>>"+outfile+" 2>&1")

def run_cache(filename,outfile,numactl):
	os.system("rm "+outfile)
	for i in range(19,30):
		size = pow(2,i)
		print size / 1024
		times = 10000000
		f = os.system(numactl + " ../bin/"+filename+" "+str(size)+" "+str(times) +">>"+outfile+" 2>&1")

def run_cache_vary_times(filename,outfile,numactl):
	os.system("rm "+outfile)
	for i in range(6,10):
		size = 60000
		print size / 1024
		times = pow(10,i)
		f = os.system(numactl + " ../bin/"+filename+" "+str(size)+" "+str(times) +">>"+outfile+" 2>&1")


def run_n(filename,outfile,numactl):
	os.system("rm "+outfile)
	for i in range(24,34):
		size = pow(2,i)
		print size
		print numactl + " ../bin/"+filename+" "+str(size)+" 16 "+">>"+outfile+" 2>&1"
		f = os.system(numactl + " ../bin/"+filename+" "+str(size)+" 8 "+">>"+outfile+" 2>&1")



import csv


def parseFile(filename):
	os.system("rm " + filename+".csv")
	f = open(filename)
	b = open(filename +'.csv', 'w')
	a = csv.writer(b)
	i=0
	print filename+'.csv'
	result =[]
	caption = []
	cap=False

	for line in f:
		
		if line[0]=="*":
			i=0
			#continue
			if not cap:	
				a.writerow(caption)
				cap = True
			a.writerow(result)
			result=[]
			caption=[]
			continue
		data = line.split(",,")
		size = len(data)
		result.append(data[0].strip('\n'))
		caption.append(data[size-1].strip('\n'))
	b.close()






run_1("test","../results/raw/run_c_probe","numactl -N 1 -m 1")
#run_1("run_1","../results/raw/run_1_rand_remote","numactl -N 1 -m 2")

#parseFile("../results/raw/run_1_rand_local")
#parseFile("../results/raw/run_1_rand_remote")

#run_1("run_1","../results/raw/run_1_local","numactl -N 1 -m 1")
#run_1("run_1","../results/raw/run_1_remote","numactl -N 1 -m 2")

#parseFile("../results/raw/run_1_local")
#parseFile("../results/raw/run_1_remote")

#run_n("run_n","../results/raw/run_n_rand_local","numactl -N 3 -m 3")
#run_n("run_n","../results/raw/run_n_rand_remote","numactl -N 3 -m 2")

parseFile("../results/raw/run_c_probe")
#parseFile("../results/raw/run_n_rand_remote")


#run_cache_vary_times("run_cache","../results/raw/run_cache_local_l2","numactl -N 3 -m 3")
#run_cache_vary_times("run_cache","../results/raw/run_cache_remote_l3","numactl -N 3 -m 2")

#parseFile("../results/raw/run_cache_local")
#parseFile("../results/raw/run_cache_remote_l3")