#	Sanitize files to remove missing data
#	usage: python sanitize.py <filename.csv>
#	Input a CSV file with some fields are missing or non-numeric
#	output a csv file with non-numeric fields replaced with a 0
#	use this to sanitize data for the purpose of a data canopy

import pandas as pd
import sys


filename = sys.argv[1]

open_file = pd.read_csv(filename)

#print open_file

for column in open_file.columns:
	for i in range(0,len(open_file[column])-1):
		  
		if isinstance(open_file[column][i],str) and not open_file[column][i].isdigit() :
			#print open_file[column][i]
			open_file[column][i]=0

for column in open_file.columns:
	for item in open_file[column]:
		  print item

open_file.to_csv("san_"+filename)