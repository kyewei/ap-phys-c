#!/usr/bin/python 

file = open("/home/kye/Desktop/blue","r")
text = file.readlines()

datacolumns=0
for line in text:
	if "</ColumnCells>"in line:
		collect=False
		datacolumns+=1

data = [[] for i in range(datacolumns)]

datanumber=0
collect=False
for line in text:
	if "</ColumnCells>"in line:
		collect=False
		datanumber+=1
	if collect:
		data[datanumber].append(float(line))
	if "<ColumnCells>"in line:
		collect=True

file.close()

file = open("data2","w")
for j in range(0,len(data[0])):
	stringto=""
	for i in range(0,len(data)):
		stringto=stringto + str(data[i][j])
		if (i <len(data)-1):
			stringto=stringto + ","
	stringto=stringto+ "\n"
	file.write(stringto)

file.close()
