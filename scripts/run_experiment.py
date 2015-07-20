import experiment as exp
import plot as p

#####
# Configuration Parameters

vary_column_size = False
vary_chunk_size = False
vary_column_number = False
vary_thread_num = False

#vary_column_size = True
#vary_chunk_size = True
#vary_column_number = True
vary_thread_num = True

suffix=""

####
if vary_column_number:

	exp.run_vary_column_number("test","../results/raw/varyColumn.raw",2,20,10000000,10000)
	exp.parseFile("../results/raw/varyColumn.raw")
	p.Plot("../results/raw/varyColumn.raw.csv",'num_col',['level_one_time','level_two_time','rest_of_levels_time','total_time'],"../results/graphs/varyColumn",False)
#	p.Plot("../results/raw/varyColumn.raw.csv",'num_col',['cache-misses'],"../results/graphs/varyColumn_cacheMisses.pdf",False)

if vary_column_size:

	exp.run_vary_column_size("test","../results/raw/varyColumnSize.raw",5,9,15,1000)
	exp.parseFile("../results/raw/varyColumnSize.raw")
	p.Plot("../results/raw/varyColumnSize.raw.csv",'size_col',['level_one_time','level_two_time','rest_of_levels_time','total_time'],"../results/graphs/varyColumnSize",True)
#	p.Plot("../results/raw/varyColumnSize.raw.csv",'size_col',['cache-misses'],"../results/graphs/varyColumnSize_cacheMisses.pdf",True)

if vary_chunk_size:

	exp.run_vary_chunk_size("test","../results/raw/varyChunkSize.raw",2,8,15,10000000)
	exp.parseFile("../results/raw/varyChunkSize.raw")
	p.Plot("../results/raw/varyChunkSize.raw.csv",'size_chunk',['level_one_time','level_two_time','rest_of_levels_time','total_time'],"../results/graphs/varyChunkSize",True)
#	p.Plot("../results/raw/varyChunkSize.raw.csv",'size_chunk',['cache-misses'],"../results/graphs/varyChunkSize_cacheMisses.pdf",True)

if vary_thread_num:

	exp.run_vary_thread_number("test","../results/raw/varyThreadNum_noInsert.raw",0,4,15,1000000,1000)
	exp.parseFile("../results/raw/varyThreadNum_noInsert.raw")
	p.Plot("../results/raw/varyThreadNum_noInsert.raw.csv",'num_threads',['level_one_time','level_two_time','rest_of_levels_time','total_time'],"../results/graphs/varyThreadNum_noInsert",True)
#	p.Plot("../results/raw/varyChunkSize.raw.csv",'size_chunk',['cache-misses'],"../results/graphs/varyChunkSize_cacheMisses.pdf",True)

