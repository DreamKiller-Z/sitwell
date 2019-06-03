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
from sklearn.ensemble import GradientBoostingClassifier
from sklearn import metrics
import pickle
# data processing

df = pd.DataFrame()
columns = [str(i) for i in range(320)]
columns.append("target")
for filename in glob.glob('data/*.csv'):
  df_temp = pd.read_csv(filename, names=columns)
  df =df.append(df_temp)

df = pd.DataFrame(df)
# print(df)
label = df.target
# print(type(label))
label = np.asarray(label, dtype=np.int64)
df = df.iloc[:,:-1]
np_data = np.array(df, dtype = np.float32)
# print(np)
df_new = pd.DataFrame()
np_range = np.arange(64)
# np_final = np.array([]).reshape(,1)
np_newdata = np_data[:,np_range]
feature = np.mean(np_newdata, axis = 1).reshape(np_newdata.shape[0],1)

for i in range(4):
  np_range += 64
  np_newdata = np_data[:,np_range]
#   print(np)
  newfeature = np.mean(np_newdata, axis = 1).reshape(np_newdata.shape[0],1)
#   print(feature)
  feature = np.append(feature, newfeature, axis = 1)
  

train_data, test_data, train_label, test_label = train_test_split(feature, label, test_size = 0.2, random_state = 101)

clf = GradientBoostingClassifier(n_estimators=100, learning_rate=1,
     max_depth=4, random_state=0).fit(train_data, train_label)
score = clf.score(test_data, test_label) 
pickle.dump(clf, open("milestone2.pickle.dat", "wb"))
print(score)
