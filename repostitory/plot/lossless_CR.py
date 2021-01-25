import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re

name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/"
data = np.loadtxt("lossless_result.txt")
data=data.reshape(-1,8)
x=range(0,18)
namelist=["P1","P2","P3","P4","P5","P6","M1","M2","M3","M4","M5","M6","G1","G2","G3","G4","G5","G6"]
y1 =data[:,0]
y2 = data[:,1]
y3= data[:,2]
y4= data[:,3]
y5 =data[:,4]
y6 = data[:,5]
y7= data[:,6]
y8= data[:,7]

V=np.zeros((6,6),dtype=float)
V[0][0]=sum(y1[0:6])/6
V[0][1]=sum(y2[0:6])/6
V[0][3]=sum(y3[0:6])/6
V[0][4]=sum(y4[0:6])/6
V[1][0]=sum(y5[0:6])/6
V[1][1]=sum(y6[0:6])/6
V[1][3]=sum(y7[0:6])/6
V[1][4]=sum(y8[0:6])/6



V[2][0]=sum(y1[6:12])/6
V[2][1]=sum(y2[6:12])/6
V[2][3]=sum(y3[6:12])/6
V[2][4]=sum(y4[6:12])/6
V[3][0]=sum(y5[6:12])/6
V[3][1]=sum(y6[6:12])/6
V[3][3]=sum(y7[6:12])/6
V[3][4]=sum(y8[6:12])/6

V[4][0]=sum(y1[12:18])/6
V[4][1]=sum(y2[12:18])/6
V[4][3]=sum(y3[12:18])/6
V[4][4]=sum(y4[12:18])/6
V[5][0]=sum(y5[12:18])/6
V[5][1]=sum(y6[12:18])/6
V[5][3]=sum(y7[12:18])/6
V[5][4]=sum(y8[12:18])/6

for i in range(0,6):
    V[i][2]=(V[i][1]-V[i][0])/V[i][0]*100
    V[i][5]=(V[i][4]-V[i][3])/V[i][3]*100

print V
