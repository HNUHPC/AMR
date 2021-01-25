import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re 

name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/"
data = np.loadtxt("CR_EB_ZFP.txt")
data=data.reshape(-1,4)
x=range(0,12)
namelist=["E-5","E-4\n P1","E-3","E-2","E-5","E-4\n M1","E-3","E-2","E-5","E-4\n G1","E-3","E-2"]
xticks_minor = [-0.25, 3.7, 7.7, 11.7 ]

#namelist=["P1:E-5","P1:E-4","P1:E-3","P1:E-2","M1:E-5","M1:E-4","M1:E-3","M1:E-2","G1:E-5","G1:E-4","G1:E-3","G1E-2"]
y1 =data[:,0]
y2 = data[:,1]
y3= data[:,2]
y4= data[:,3]
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
ax.set_ylabel('Compression ratio',font)
#ax.set_title("ZFP",axis_font)
ax.set_ylim([0,20])
y_major_locator=plt.MultipleLocator(5)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
#ax.set_xticklabels( namelist,rotation=45 )
ax.set_xticklabels( namelist)
ax.set_xticks( xticks_minor, minor=True )
ax.tick_params( axis='x', which='minor', direction='out',  top='off',length=60 )

ax.set_xlim([-0.25,11.7])
#ax.set_xlabel('Dataset and relative error bound',font)
ax.set_xlabel("(a) ZFP",{'family' : 'Times New Roman', 'size'   : 36})
ax.legend(loc=2,ncol=2, prop=font)
#plt.text(0.45, -0.15, 'Unit y1', color='blue', transform=ax.transAxes)
#plt.text(0.45, -0.2, 'Unit y2', color='red', transform=ax.transAxes)


plt.savefig(name_hat+'CR_ZFP_EB.pdf', format='pdf',bbox_inches="tight",pad_inches=0)
plt.show()


data = np.loadtxt("CR_EB_SZ.txt")
data=data.reshape(-1,4)
y5 =data[:,0]
y6 = data[:,1]
y7= data[:,2]
y8= data[:,3]
fig = plt.figure(num=None,figsize=(20,4))
#fig = plt.figure()
print np.shape(x)
ax = fig.add_subplot(111)



rects1 = ax.bar(ind-width, y5, width, color='g',hatch='.',label="Z-order")
rects2 = ax.bar(ind, y6, width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, y7, width, color='b',hatch='x',label="Hilbert")
rects4 = ax.bar(ind+2*width, y8, width, color='y',hatch='/',label="Hilbert+zMesh")
ax.set_ylabel('Compression ratio',font)
ax.set_ylim([0,400])
y_major_locator=plt.MultipleLocator(100)
ax.yaxis.set_major_locator(y_major_locator)
#ax.set_title("SZ",axis_font)
ax.set_xticks(ind+width)
ax.set_xticks( xticks_minor, minor=True )
ax.tick_params( axis='x', which='minor', direction='out', top='off', length=60 )
ax.set_xticklabels( namelist )
ax.set_xlim([-0.25,11.7])
ax.set_xlabel("(b) SZ",{'family' : 'Times New Roman', 'size'   : 36})
#ax.set_xlabel('Dataset and relative error bound',font)
#ax.legend(loc=2,ncol=2, prop=font)


plt.savefig(name_hat+'CR_SZ_EB.pdf', format='pdf',bbox_inches="tight",pad_inches=0)
#plt.show()



