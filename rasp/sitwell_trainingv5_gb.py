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
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler

import pickle
# data processing

df = pd.DataFrame()
columns = [str(i) for i in range(320)]
columns.append("target")
for filename in glob.glob('data/*.csv'):
  df_temp = pd.read_csv(filename, names=columns)
  df =df.append(df_temp)
# print(df)
# static = np.asarray(df, dtype=np.float32)
# static = static[static[:,-1]==0]
# # static_wlabel = static
# static = static[:,:-1]
# # print(static.shape)

# static_mean = np.average(static, axis = 0)
  
# static_std = np.std(static, axis = 0)

# static_result = (static - static_mean)/static_std
# static_result = np.mean(static_result, axis = 0)
label = df.target
label = np.asarray(label, dtype=np.int64)

df0 = df.iloc[:, :-1]
np0 = np.array(df0, dtype = np.float32)



# np0 = np0[np0[:,-1] != 0]
# print(np0.shape)
# np0_mean = np.mean(np0, axis = 0)
# # print(np0_mean)
# np0_std = np.std(np0,axis = 0)
# # print(np0_std)
# np_result = (np0 - np0_mean)/np0_std
# print(np_result.shape)
train_data, test_data, train_label, test_label = train_test_split(np0, label, test_size = 0.2, random_state = 101)

sc = StandardScaler()  
sc.fit(train_data)
test_data = sc.transform(test_data)
train_data = sc.transform(train_data)
pickle.dump(sc, open("sc.pickle.dat", "wb"))

pca = PCA(n_components=5)
pca.fit(train_data) 
train_data = pca.transform(train_data)
test_data = pca.transform(test_data)
pickle.dump(pca, open("pca.pickle.dat", "wb"))


clf = GradientBoostingClassifier(n_estimators=100, learning_rate=1,
     max_depth=4, random_state=0).fit(train_data, train_label)
score = clf.score(test_data, test_label) 
pickle.dump(clf, open("milestone2.pickle.dat", "wb"))
print(score)
