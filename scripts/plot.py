
import csv


def parseFile(filename):

	f = open(filename)
	b = open('test.csv', 'w')
	a = csv.writer(b)
	i=0

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
		data = line.split(",")
		size = len(data)
		result.append(data[0].strip('\n'))
		caption.append(data[size-1].strip('\n'))
	b.close()

parseFile('out')



