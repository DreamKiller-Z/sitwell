import math
import pandas as pd
import numpy as np
from sklearn.decomposition import PCA
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
# import seaborn as sns
import os, glob
# import matplotlib for plotting
# import matplotlib.pyplot as plt
import numpy as np
from sklearn.decomposition import PCA
import pickle

# %matplotlib inline

tf.enable_eager_execution()

df = pd.DataFrame()
columns = [str(i) for i in range(256)]
columns.append("target")
filelist = []   

for filename in glob.glob('data/*.csv'):    # list all csv 
    filename = filename[5:]
    print(filename)
    filelist.append(filename)
print("whose data you want to train on? input someone's name")
username = input()

# for filename in glob.glob('data/*.csv'):
#     if (filename[5:] == username + '.csv'):
#         df_temp = pd.read_csv(filename, names=columns)
#         df =df.append(df_temp)

if username == "all":
    for filename in glob.glob('data/*.csv'):    # gather data
        df_temp = pd.read_csv(filename, names=columns)
        df =df.append(df_temp)
# elif ('data/' + username+'*.csv') not in glob.glob('data/*.csv'):    #Error if no person's data
#     # print(username)
#     print("No this person's data")
else:
    for filename in glob.glob('data/static*.csv'):    # gather data
        df_temp = pd.read_csv(filename, names=columns)
        df =df.append(df_temp)
    for filename in glob.glob('data/' + username + '*.csv'):    # gather data
        # if username in filename:
        df_temp = pd.read_csv(filename, names=columns)
        df =df.append(df_temp)

static = np.asarray(df, dtype=np.float32)
static = static[static[:,-1]==0]

static = np.average(static, axis = 0)
static = static[:-1]
print(static.shape)
df_none0 = static -df.iloc[:,:-1] 

np_none0 = np.asarray(df_none0, dtype= np.float32)
# np_none0 = np_none0.reshape(np_none0.shape[0], 8,8)
label = df.target

label = np.asarray(label, dtype=np.int64)

np_none0 = np_none0.reshape(np_none0.shape[0],16,16,1)

train_data, test_data, train_label, test_label = train_test_split(np_none0, label, test_size = 0.2, random_state = 101)

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Flatten, Conv1D, Conv2D, Activation, MaxPooling1D,MaxPooling2D, Dropout

num_classes = 6
epochs = 50
kernel_size = 2 #kernel_size of 1 worked surprisingly well
pool_size = 2
dropout_rate = 0.15

model = Sequential()
model.add(Conv2D(32, (3,3), padding = 'same', input_shape= [16,16,1]))
model.add(BatchNormalization()) 
model.add(Activation('relu'))

model.add(Conv2D(32, (3,3)))
model.add(BatchNormalization()) 
model.add(Activation('relu'))

model.add(MaxPooling2D((2, 2), strides=(2, 2)))
model.add(Dropout(0.2))

model.add(Conv2D(64, (3,3),padding='same'))
model.add(BatchNormalization()) 
model.add(Activation('relu'))

model.add(Conv2D(64, (3,3)))
model.add(BatchNormalization()) 
model.add(Activation('relu'))

model.add(MaxPooling2D((2, 2), strides=(2, 2)))
model.add(Dropout(0.3))

model.summary()


model.add(Flatten())
model.add(Dense(64, activation = 'relu'))
model.add(Dense(32, activation = 'relu'))
model.add(Dense(16, activation= 'relu'))
model.add(Dense(num_classes, activation ='softmax'))

model.compile(loss = 'sparse_categorical_crossentropy',
             optimizer = 'adam',
             metrics = ['accuracy'])

history = model.fit(train_data, train_label,
                   batch_size = 64,
                   epochs = 20,
                   validation_data = (test_data, test_label),
                   shuffle = True)

model.save("model.h5")

# print(history)
# pickle.dump(model, open("cnn.pickle.dat", "wb"))
