
import os
import plot as p

#num_col, size_col, size_chunk

def run_vary_column_size(filename,outfile,start,end,num_col,size_chunk):
	os.system("rm "+outfile)
	for i in range(start,end):
		size_col = pow(10,i)
		print " ../bin/"+ filename + " " + str(num_col) + " " + str(size_col) + " " +str(size_chunk)+ ">>" + outfile + " 2>&1"
		f = os.system(" ../bin/"+ filename + " " + str(num_col) + " " + str(size_col) + " " +str(size_chunk)+ ">>" + outfile + " 2>&1")



def run_vary_chunk_size(filename,outfile,start,end,num_col,size_col):
	os.system("rm "+outfile)
	for i in range(start,end):
		size_chunk = pow(10,i)
		print " ../bin/"+ filename + " " + str(num_col) + " " + str(size_col) + " " +str(size_chunk)+ ">>" + outfile + " 2>&1"
		f = os.system(" ../bin/"+ filename + " " + str(num_col) + " " + str(size_col) + " " +str(size_chunk)+ ">>" + outfile + " 2>&1")


def run_vary_column_number(filename,outfile,start,end,size_col,size_chunk):
	os.system("rm "+outfile)
	for i in range(start,end):
		num_col = i
		print " ../bin/"+ filename + " " + str(num_col) + " " + str(size_col) + " " +str(size_chunk)+ ">>" + outfile + " 2>&1"
		f = os.system(" ../bin/"+ filename + " " + str(num_col) + " " + str(size_col) + " " +str(size_chunk)+ ">>" + outfile + " 2>&1")




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




#run_vary_column_number("test","../results/raw/varyColumn.raw",2,20,10000000,10000)
#parseFile("../results/raw/varyColumn.raw")
p.Plot("../results/raw/varyColumn.raw.csv",'num_col',['level_one_time','level_two_time','rest_of_levels_time','total_time'],"../results/graphs/varyColumn",False)
#p.Plot("../results/raw/varyColumn.raw.csv",'num_col',['cache-misses'],"../results/graphs/varyColumn_cacheMisses.pdf",False)


#run_vary_column_size("test","../results/raw/varyColumnSize.raw",5,9,15,1000)
#parseFile("../results/raw/varyColumnSize.raw")
p.Plot("../results/raw/varyColumnSize.raw.csv",'size_col',['level_one_time','level_two_time','rest_of_levels_time','total_time'],"../results/graphs/varyColumnSize",True)
#p.Plot("../results/raw/varyColumnSize.raw.csv",'size_col',['cache-misses'],"../results/graphs/varyColumnSize_cacheMisses.pdf",True)

#run_vary_chunk_size("test","../results/raw/varyChunkSize.raw",2,8,15,10000000)
#parseFile("../results/raw/varyChunkSize.raw")
p.Plot("../results/raw/varyChunkSize.raw.csv",'size_chunk',['level_one_time','level_two_time','rest_of_levels_time','total_time'],"../results/graphs/varyChunkSize",True)
#p.Plot("../results/raw/varyChunkSize.raw.csv",'size_chunk',['cache-misses'],"../results/graphs/varyChunkSize_cacheMisses.pdf",True)

