import serial
# import pandas as pd
# import numpy as np
from datetime import datetime
import os.path
import os, glob

# import keyboard
ser = serial.Serial('/dev/ttyACM0',115200)
data = []
# dataFile = open("data/" + datetime.now().strftime("%m_%d_%Y_%H_%M_%S")+'.csv','w')
# dataFile = open("data/milestone2.csv",'w')

def collecting(target):
    while(True):
        print("get into while")
        for i in range(20):
            print("get into for")
        # while(True):
            try:
                read_serial = ser.readline().decode('utf-8').strip(',\r\n') + ',' + target+'\n'
            except UnicodeDecodeError:
                continue
            print("prepare to readline")
            # read_serial = ser.readline().strip(',\r\n') + ',' + target+'\n'
            count = len(read_serial.split(","))
            if count != 257:
                print(count)
                # print(read_serial)
                continue
            else:
                dataFile.write(read_serial)
                print(read_serial)
        print("Continue? y / n")
        if_continue = input()
        if if_continue == "n":
            break

choose = True
print("Whose data am I going to collect?")
username = input()
while(choose):
    print ("---------------------")
    print("1. collect data \n")
    print ("---------------------")
    answer = input()
    # print(answer)

    if answer == '1':
        
        
        file_count = 0
        filename = "data/"+username+str(file_count)+".csv"
        while(True):
            if filename in glob.glob("data/*.csv"):
                file_count += 1
                filename = "data/"+username+str(file_count)+".csv"
            else:
                break
        dataFile = open(filename, "w")
        print("target label? 0 for static")
        choose_label = input()
        # print("collecting data")
        collecting(choose_label)
        
        # df_temp = pd.DataFrame(np.array(data))
        # with open("testdata.csv", "a") as f:
        #     df_temp.to_csv(f, index =False, header =False)
        # print(df_temp.tail(5))
    # elif answer == '2':
    #     choose = False
    #     print("end")
    #     # sendMessageTo("B8:27:EB:16:64:7A")
    # elif answer =='3':
    #     os.remove("testdata.csv")
    #     print("delete csv")
    #     choose = False
    # elif answer =="4":
    #     df_read = pd.read_csv("testdata.csv")
    #     print(df_read.tail(10))
    #     choose =False

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