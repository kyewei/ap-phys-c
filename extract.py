root = 'C:\\Users\\Kye\\Desktop\\'


time = []
data1 = []
data2 = []
data3 = []
dataList = time;

def nextList(currentList):
    if currentList is time:
        return data1
    elif currentList is data1:
        return data2
    elif currentList is data2:
        return data3
    elif currentList is data3:
        return None

dataCollect = False
with open(root+'blue','rU') as labPro:
    for line in labPro:
        if dataList != None:
            if "</ColumnCells>" in line:
                dataCollect = False
            if dataCollect:
                dataList.append (line.encode('utf-8'))
                #print(line)
            if "<ColumnCells>" in line:
                dataCollect = True
                dataList = nextList(dataList)


import csv
print(len(time))
with open(root+"output.csv", "w", newline='') as f:
    writer = csv.writer(f, delimiter=',')
    writer.writerow(time)
    #for x in range(0,len(time)-1):
    #    writer.writerow(time[x],data1[x], data2[x], data3[x])
