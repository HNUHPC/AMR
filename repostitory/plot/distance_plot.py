import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re 

name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/"

data = np.loadtxt("distance.txt")
data=data.reshape(-1,4)
x =[1,2,3,4,5,6,7,8,9,10,11,12]
#z1 = [5.230,5.837,9.358,7.098,5.925,5.331,5.277,5.974 ]
#z2 = [2.456,7.504,3.269,3.984,7.384,11.163,25.261,40.860]
#z3 = [103.526,76.541,63.936,52.817,49.631,47.876,46.092,46.122]
#z4 = [0.580,0.923,1.203,1.461,2.493,1.691,1.666,1.699]
#z5 = [1.621,1.740,1.973,2.273,2.446,2.485,2.460,2.596]
z1 = data[:,0] 
z2 = data[:,1] 
z3 = data[:,2] 
z4 = data[:,3] 

#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure(num=None,figsize=(10,5))
axis_font = {'size':'22'}
plt.rc('xtick', labelsize=22)          # fontsize of the tick labels
plt.rc('ytick', labelsize=22)
font = {'size':'22'}


N = len(x)
ind = np.arange(N)  # the x locations for the groups
width = 0.2       # the width of the bars

ax = fig.add_subplot(111)
ax.plot(x,z1,"g-o",linewidth=1,label="Z-order")
ax.plot(x,z2,"r-^",linewidth=1,label="Z-order+zMesh")
#ax.plot(x,z3,"b--",linewidth=1,label="H")
#ax.plot(x,z4,"y--",linewidth=1,label="H+LevelRe")
#rects1 = ax.bar(ind, z2, width, color='r',label="Z+LevelRe")
#rects3 = ax.bar(ind+width, z7, width, color='y',label="H+LevelRe")
#ax.set_yscale('log')
ax.set_ylabel('Total distance',axis_font)
#ax.set_ylim([0,2])
#ax.set_xticks(ind+width)
#ax.set_xticklabels( x )
#ax.set_xlim([-0.1,7.5])
ax.set_xlabel('Number of AMR levels',axis_font)
ax.legend(loc=2, prop=font)

plt.savefig(name_hat+'fig_distance.pdf', format='pdf',bbox_inches="tight")
plt.show()



fig = plt.figure(num=None,figsize=(10,5))
axis_font = {'size':'22'}
plt.rc('xtick', labelsize=22)          # fontsize of the tick labels
plt.rc('ytick', labelsize=22)
font = {'size':'22'}


N = len(x)
ind = np.arange(N)  # the x locations for the groups
width = 0.2       # the width of the bars

ax = fig.add_subplot(111)
#ax.plot(x,z1,"g-o",linewidth=1,label="Z")
#ax.plot(x,z2,"r-^",linewidth=1,label="Z+LevelRe")
ax.plot(x,z3,"b-o",linewidth=1,label="Hilbert")
ax.plot(x,z4,"y-^",linewidth=1,label="Hilbert+zMesh")
#ax.set_yscale('log')
ax.set_ylabel('Total distance',axis_font)
y_major_locator=plt.MultipleLocator(5000)
ax.yaxis.set_major_locator(y_major_locator)

#ax.set_ylim([0,2])
#ax.set_xticks(ind+width)
#ax.set_xticklabels( x )
#ax.set_xlim([-0.1,7.5])
ax.set_xlabel('Number of AMR levels',axis_font)
ax.legend(loc=2, prop=font)

plt.savefig(name_hat+'fig_distance_h.pdf', format='pdf',bbox_inches="tight")
plt.show()
