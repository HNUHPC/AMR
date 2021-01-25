import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re 

name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/"
data = np.loadtxt("level_overhead.txt")
x =[2,3,4,5,6,7,8,9]
#z1 = [5.230,5.837,9.358,7.098,5.925,5.331,5.277,5.974 ]
#z2 = [2.456,7.504,3.269,3.984,7.384,11.163,25.261,40.860]
#z3 = [103.526,76.541,63.936,52.817,49.631,47.876,46.092,46.122]
#z4 = [0.580,0.923,1.203,1.461,2.493,1.691,1.666,1.699]
#z5 = [1.621,1.740,1.973,2.273,2.446,2.485,2.460,2.596]

datasize=[39572.0,67736,128016,263044,543712,1094888,2227500,4574888]
for j in range(0,10):
    for i in range (0,8):
        data[i][j]=134217728/datasize[i]*data[i][j]
y1 = data[:,0]
y2 = data[:,1]
y3 =data[:,2]
y4 =data[:,3]
y5 =data[:,4]
y6 = data[:,5]
y7 = data[:,6]
y8 =data[:,7]
y9 =data[:,8]
y10 =data[:,9]
namelist=["2","3","4","5","6","7","8","9"]
fig = plt.figure(num=None,figsize=(20,5))
#fig = plt.figure()
print np.shape(x)
axis_font = {'size':'24'}
plt.rc('xtick', labelsize=24)          # fontsize of the tick labels
plt.rc('ytick', labelsize=24)

N = len(x)
print N
ind = np.arange(N)  # the x locations for the groups
width = 0.15       # the width of the bars

ax = fig.add_subplot(111)
font = {'size':'24'}



rects1 = ax.bar(ind-width, y1, width, color='g',label="B")
rects2 = ax.bar(ind, y2, width, color='r',label="L_Init")
rects3 = ax.bar(ind+width, y3, width, color='b',label="L_Z-ordering")
rects4 = ax.bar(ind+2*width, y4, width, color='y',label="L_Building")
rects5 = ax.bar(ind+3*width, y5, width, color='pink',label="L_Traversing")
ax.set_ylabel('Time for 1GB data (s)',font)
ax.set_ylim([0,4])
y_major_locator=plt.MultipleLocator(1)
ax.yaxis.set_major_locator(y_major_locator)

#ax.set_title("RMSE comparison",axis_font)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
ax.set_xlim([-0.3,7.8])
ax.set_xlabel('Number of AMR levels',font)
ax.legend(loc=0,ncol=5, prop=font)


plt.savefig(name_hat+'Time_level.pdf', format='pdf',bbox_inches="tight")
plt.show()



