import serial
from datetime import datetime
import os.path
import math
import pandas as pd
import numpy as np
import pickle
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_absolute_error 
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Activation, Flatten,BatchNormalization
from tensorflow.keras.callbacks import ModelCheckpoint
from scipy import stats
import tensorflow as tf
from sklearn.preprocessing import LabelBinarizer
from tensorflow.keras.utils import to_categorical
import warnings # current version of seaborn generates a bunch of warnings that we'll ignore
warnings.filterwarnings("ignore")
warnings.filterwarnings('ignore', category=DeprecationWarning)
import os, glob
from sklearn.ensemble import GradientBoostingClassifier
from sklearn import metrics
from sklearn.decomposition import PCA

ser = serial.Serial('/dev/ttyACM0',1000000)
data = []
try:
	loaded_model = pickle.load(open("milestone2.pickle.dat", "rb"))
	sc = pickle.load(open("sc.pickle.dat", "rb"))
	pca = pickle.load(open("pca.pickle.dat", "rb"))
except pickle.UnpicklingError:
	pass

# df = pd.DataFrame()
# columns = [str(i) for i in range(320)]
# columns.append("target")
# for filename in glob.glob('data/*.csv'):
# 		df_temp = pd.read_csv(filename, names=columns)
# 		df =df.append(df_temp)
# static = np.asarray(df, dtype=np.float32)
# static = static[static[:,-1]==0]

# static = np.average(static, axis = 0)
# static = static[:-1]

buff = []
def gb_predict(test_data):
	prediction =int(loaded_model.predict(test_data))
	buff.append(prediction)
	if len(buff) > 10:
		buff.pop(0)
		result = most_frequent(buff)
		print(result)
	# return result

def most_frequent(List): 
    return max(set(List), key = List.count) 

def dataprocess(data):
	# pca = PCA(n_components=5)
	sc_result = sc.transform(data.reshape(1,-1))
	pca_result = pca.transform(sc_result)  
	# result = static - data
	return pca_result

def collecting():
	while (True):
		try:
			read_serial = ser.readline().decode('utf-8').strip(',\r\n')
		except UnicodeDecodeError:
			continue
		# data = np.array(read_serial, dtype = np.float32)/600
		count = len(read_serial.split(","))
		if count != 320:
			continue
		else:
			data = read_serial.split(',')
			# print(data)
			data = np.asarray(data, dtype= np.float32)
			# print(data)
			processed = dataprocess(data)
			# if np.average(processed)/np.average(static) > 0.1:
				# pressure = True
			# processed = processed.reshape(1,-1)
			gb_predict(processed)
			# else:
				# pressure = False
				# print("No Pressure")
			# print(processed)
			# data = np.asarray(data, dtype = np.float32)
			
			# dataFile.write(read_serial)
			# print(read_serial)
while(True):
	collecting()
	