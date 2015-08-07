import experiment as exp
import plot as p
import time
import os



#####
path_graphs="../results/graphs/"
path_raw="../results/raw/"
#####

folder_name = time.strftime("%j") + "-" + time.strftime("%x").replace('/','_')

if not os.path.exists(path_graphs+folder_name):
	os.system("mkdir "+ path_graphs+folder_name)

if not os.path.exists(path_raw+folder_name):
	os.system("mkdir "+ path_raw+folder_name)

print "***"
print "Running Experiments, results in: " + folder_name 
print "***"

####


# Configuration Parameters

vary_column_size = False
vary_chunk_size = False
vary_column_number = False
vary_thread_num = False

vary_column_size = True
#vary_chunk_size = True
vary_column_number = True
#vary_thread_num = True

num_threads=1

####
raw_ext=".raw"
csv_ext=".csv"
pdf_ext=".pdf"
####

if vary_column_number:

	file_name="varyColumnNumber"
	
	exp.run_vary_column_number("test",path_raw+folder_name+"/"+file_name+raw_ext,2,15,100000,10,num_threads)
	exp.parseFile(path_raw+folder_name+"/"+file_name+raw_ext)

	p.Plot(path_raw+folder_name+"/"+file_name+raw_ext+csv_ext,'num_col',['level_one_time','level_two_time','rest_of_levels_time','total_time'],path_graphs+folder_name+"/"+file_name,False,False)
	p.Plot(path_raw+folder_name+"/"+file_name+raw_ext+csv_ext,'num_col',['level_one_time','level_two_time','rest_of_levels_time','total_time'],path_graphs+folder_name+"/"+file_name,True,False)

if vary_column_size:

	file_name="varyColumnSize"
	
	exp.run_vary_column_size("test",path_raw+folder_name+"/"+file_name+raw_ext,4,9,10,10,num_threads)
	exp.parseFile(path_raw+folder_name+"/"+file_name+raw_ext)
	
	p.Plot(path_raw+folder_name+"/"+file_name+raw_ext+csv_ext,'size_col',['level_one_time','level_two_time','rest_of_levels_time','total_time'],path_graphs+folder_name+"/"+file_name,True,True)
	p.Plot(path_raw+folder_name+"/"+file_name+raw_ext+csv_ext,'size_col',['level_one_time','level_two_time','rest_of_levels_time','total_time'],path_graphs+folder_name+"/"+file_name,True,False)
	#p.Plot(path_raw+folder_name+"/"+file_name+raw_ext+csv_ext,'size_col',['cache-misses'],path_graphs+folder_name+"/"+file_name,True,False)

if vary_chunk_size:

	file_name="varyChunkSize"

	exp.run_vary_chunk_size("test",path_raw+folder_name+"/"+file_name+raw_ext,1,6,15,100000,num_threads)
	exp.parseFile(path_raw+folder_name+"/"+file_name+raw_ext)

	p.Plot(path_raw+folder_name+"/"+file_name+raw_ext+csv_ext,'size_chunk',['level_one_time','level_two_time','rest_of_levels_time','total_time'],path_graphs+folder_name+"/"+file_name,True,False)
	p.Plot(path_raw+folder_name+"/"+file_name+raw_ext+csv_ext,'size_chunk',['level_one_time','level_two_time','rest_of_levels_time','total_time'],path_graphs+folder_name+"/"+file_name,True,True)
	
if vary_thread_num:

	file_name="varyThreadNum"
	exp.run_vary_thread_number("test",path_raw+folder_name+"/"+file_name+raw_ext,0,8,15,1000000,1000)
	exp.parseFile(path_raw+folder_name+"/"+file_name+raw_ext)
	p.PlotSimple(path_raw+folder_name+"/"+file_name+raw_ext+csv_ext,'num_threads',['total_time'],path_raw+folder_name+"/"+file_name,True)
	p.Plot_scaling(path_raw+folder_name+"/"+file_name+raw_ext+csv_ext,'num_threads','total_time',path_raw+folder_name+"/"+file_name,True)
#	p.Plot("../results/raw/varyChunkSize.raw.csv",'size_chunk',['cache-misses'],"../results/graphs/varyChunkSize_cacheMisses.pdf",True)

