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
columns = [str(i) for i in range(64)]
columns.append("target")
for filename in glob.glob('data/*.csv'):
  df_temp = pd.read_csv(filename, names=columns)
  df =df.append(df_temp)

static = np.asarray(df, dtype=np.float32)
static = static[static[:,-1]==0]
# static_wlabel = static
print(static)

static = np.average(static, axis = 0)
static = static[:-1]

df_none0 =static - df.iloc[:,:-1]

np_none0 = np.asarray(df_none0, dtype= np.float32)
# np_none0 = np_none0.reshape(np_none0.shape[0], 8,8)
print(np_none0)
label = df.target
print(label)
print(np.unique(label))

label = np.asarray(label, dtype=np.int64)

train_data, test_data, train_label, test_label = train_test_split(np_none0, label, test_size = 0.2, random_state = 101)

clf = GradientBoostingClassifier(n_estimators=100, learning_rate=1,
     max_depth=4, random_state=0).fit(train_data, train_label)
score = clf.score(test_data, test_label) 
pickle.dump(clf, open("milestone2.pickle.dat", "wb"))
print(score)
