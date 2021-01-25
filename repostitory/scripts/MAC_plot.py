import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re 

name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/"
data = np.loadtxt("MAC.txt")
data=data.reshape(-1,4)
x=range(0,18)
namelist=["P1","P2","P3","P4","P5","P6","M1","M2","M3","M4","M5","M6","G1","G2","G3","G4","G5","G6"]
y1 =data[:,0]
y2 = data[:,1]
y3 =data[:,2]
y4 = data[:,3]
fig = plt.figure(num=None,figsize=(20,4))
#fig = plt.figure()
print np.shape(x)
axis_font = {'size':'32'}
plt.rc('xtick', labelsize=32)          # fontsize of the tick labels
plt.rc('ytick', labelsize=32)
font = {'size':'32'}

N = len(x)
print N
ind = np.arange(N)  # the x locations for the groups
width = 0.2       # the width of the bars

ax = fig.add_subplot(111)



rects1 = ax.bar(ind-width, y1, width, color='g',hatch='.',label="Z-order")
rects2 = ax.bar(ind, y2, width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, y3, width, color='b',hatch='x',label="Hilbert")
rects4 = ax.bar(ind+2*width, y4, width, color='y',hatch='/',label="Hilbert+zMesh")
ax.set_ylabel('MAC',font)
ax.set_ylim([0,150])
y_major_locator=plt.MultipleLocator(30)
ax.yaxis.set_major_locator(y_major_locator)

#ax.set_title("ZFP",axis_font)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
ax.set_xlim([-0.3,17.8])
ax.legend(loc="upper right",ncol=2, prop=font)
#plt.tight_layout()

plt.savefig(name_hat+'MAC_Zordering.pdf', format='pdf',bbox_inches="tight",pad_inches=0)
plt.show()





