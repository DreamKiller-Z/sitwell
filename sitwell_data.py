import serial
import pandas as pd
import numpy as np
from datetime import datetime
import os.path

ser = serial.Serial('/dev/ttyACM0',1000000)
data = []
dataFile = open("data/" + datetime.now().strftime("%m_%d_%Y_%H_%M_%S")+'.csv','w')

ser.readline()
while True:
	read_serial = ser.readline().decode('utf-8').strip(',\r\n')+'\n'

	# data[0] = str(int (ser.readline(),16))
	# data[0] = str(ser.readline())
	# data.append(int (ser.readline(),16))
	# print(s[0])
	dataFile.write(read_serial)
	print(read_serial)
	# print (data)

# def collectdata(target):
# 	while True:
# 		read_serial = ser.readline()
# 		# s[0] = str(ser.readline())
# 		data.append(read_serial)
# 		# print(s[0])
# 		print (read_serial)

# collectdata()

# try:
#     df_read=pd.read_csv("testdata.csv")
# except FileNotFoundError:
#     f = open("testdata.csv", "w")
# except pd.io.common.EmptyDataError:
#     pass   

# df_temp = pd.DataFrame(np.array(data))

# with open("testdata.csv", "a") as f:
#     df_temp.to_csv(f, index =False, header =False)


# choose = True
# while(choose):

#     print ("---------------------")
#     print("1. collect data \n2. save and end \n3. delete csv \n4. look at testdata.csv")
#     print ("---------------------")
#     answer = input()
#     print(answer)
#     if answer == '1':
#         print("target label? 0 for static")
#         choose_label = input()
#         # print("collecting data")
#         data = collecting(choose_label)
#         df_temp = pd.DataFrame(np.array(data), columns = ["g_x", "g_y", "g_z", "a_x", "a_y", "a_z","target"])
#         with open("testdata.csv", "a") as f:
#             df_temp.to_csv(f, index =False, header =False)
#         print(df_temp.tail(5))
#     elif answer == '2':
#         choose = False
#         print("end")
#         sendMessageTo("B8:27:EB:16:64:7A")
#     elif answer =='3':
#         os.remove("testdata.csv")
#         print("delete csv")
#         choose = False
#     elif answer =="4":
#         df_read = pd.read_csv("testdata.csv")
#         print(df_read.tail(10))
#         choose =False




