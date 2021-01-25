import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re 

name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/"

data = np.loadtxt("metric_zfp.txt")
#data=data.reshape(-1,5)
data_H = np.loadtxt("metric_sz.txt")
#data_H=data_H.reshape(-1,5)
x =range(0,3)
namelist=[ "P1","M1","G1"]
ZFP=np.zeros((20,3),dtype=float)
for i in range(0,20):
    for j in range(0,3):
        ZFP[i][j]=data[i//2][i%2+2*j] 
print ZFP
SZ=np.zeros((20,3),dtype=float)
for i in range(0,20):
    for j in range(0,3):
        SZ[i][j]=data_H[i//2][i%2+2*j] 

print SZ 

N = len(x)
ind = np.arange(N)  # the x locations for the groups
width = 0.2       # the width of the bars

axis_font = {'size':'30'}
plt.rc('xtick', labelsize=30)          # fontsize of the tick labels
plt.rc('ytick', labelsize=30)
font = {'size':'30'}

fig = plt.figure(num=None,figsize=(30,4))
ax = fig.add_subplot(151)

rects1 = ax.bar(ind-width, ZFP[0,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, ZFP[1,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, ZFP[10,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width,ZFP[11,:], width, color='y',hatch='/',label="Hilbert+zMesh")

ax.set_ylabel('Average value',axis_font)
ax.set_yscale('log')
#y_major_locator=plt.MultipleLocator(200)
#ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,900])
ax.set_xlim([-0.3,2.7])
#ax.legend(ncol=1, prop=font,bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0)
#ax.set_title("ZeroCnt",axis_font)
ax.set_xlabel("(a) ZeroCnt",{'family' : 'Times New Roman', 'size'   : 36})


ax = fig.add_subplot(152)

rects1 = ax.bar(ind-width, ZFP[6,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, ZFP[7,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, ZFP[16,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width,ZFP[17,:], width, color='y',hatch='/',label="Hilbert+zMesh")

#ax.set_ylabel('Average value',axis_font)
#ax.set_yscale('log')
#y_major_locator=plt.MultipleLocator(200)
#ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,900])
ax.set_xlim([-0.3,2.7])
#ax.legend(loc=2,ncol=2, prop=font)
#ax.set_title("MaxExp",axis_font)

ax.set_xlabel("(b) MaxExp",{'family' : 'Times New Roman', 'size'   : 36})

ax = fig.add_subplot(153)

rects1 = ax.bar(ind-width, ZFP[4,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, ZFP[5,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, ZFP[14,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width,ZFP[15,:], width, color='y',hatch='/',label="Hilbert+zMesh")

#ax.set_ylabel('Average value',axis_font)
#ax.set_yscale('log')
y_major_locator=plt.MultipleLocator(3)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,900])
ax.set_xlim([-0.3,2.7])
#ax.legend(loc=2,ncol=2, prop=font)
#ax.set_title("MaxPrec",axis_font)
ax.set_xlabel("(c) MaxPrec",{'family' : 'Times New Roman', 'size'   : 36})


ax = fig.add_subplot(154)
rects1 = ax.bar(ind-width, ZFP[2,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, ZFP[3,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, ZFP[12,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width,ZFP[13,:], width, color='y',hatch='/',label="Hilbert+zMesh")

#ax.set_ylabel('Average value',axis_font)
y_major_locator=plt.MultipleLocator(10)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,900])
ax.set_xlim([-0.3,2.7])
#ax.legend(loc=2,ncol=2, prop=font)
#ax.set_title("BitsPerBitplane",axis_font)
ax.set_xlabel("(d) BitsBitplane",{'family' : 'Times New Roman', 'size'   : 36})

ax = fig.add_subplot(155)

rects1 = ax.bar(ind-width, ZFP[8,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, ZFP[9,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, ZFP[18,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width,ZFP[19,:], width, color='y',hatch='/',label="Hilbert+zMesh")

#ax.set_ylabel('Average value',axis_font)
#ax.set_yscale('log')
#y_major_locator=plt.MultipleLocator(200)
#ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,900])
ax.set_xlim([-0.3,2.7])
#ax.legend(loc=2,ncol=2, prop=font)
#ax.set_title("BlockSize",axis_font)
ax.set_xlabel("(e) BlockSize",{'family' : 'Times New Roman', 'size'   : 36})

plt.legend( (rects1[0], rects2[0],rects3[0],rects4[0]), ('Z-order', 'Z-order+zMesh',"Hilbert","Hilbert+zMesh") ,ncol=4, bbox_to_anchor=(-0.2, 1.5),prop=font)
#plt.legend(bbox_to_anchor=(0, 1),(rects1[0],rects2[0],rects3[0],rects4[0]),("1", "2", "3","4"),ncol=4)
fig.tight_layout()
plt.savefig(name_hat+'ZFP_metrics.pdf', format='pdf',bbox_inches="tight")
plt.show()



fig = plt.figure(num=None,figsize=(30,4))
ax = fig.add_subplot(151)

rects1 = ax.bar(ind-width, SZ[0,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, SZ[1,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, SZ[10,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width,SZ[11,:], width, color='y',hatch='/',label="Hilbert+zMesh")

ax.set_ylabel('Average value',axis_font)
#ax.set_yscale('log')
#y_major_locator=plt.MultipleLocator(200)
#ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,900])
ax.set_xlim([-0.3,2.7])
#ax.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0,ncol=1, prop=font)
#ax.set_title("HitRatio",axis_font)

ax.set_xlabel("(a) HitRatio",{'family' : 'Times New Roman', 'size'   : 36})

ax = fig.add_subplot(152)
rects1 = ax.bar(ind-width, SZ[2,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, SZ[3,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, SZ[12,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width,SZ[13,:], width, color='y',hatch='/',label="Hilbert+zMesh")

#ax.set_ylabel('Average value',axis_font)
y_major_locator=plt.MultipleLocator(20)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,900])
ax.set_xlim([-0.3,2.7])
#ax.legend(loc=2,ncol=2, prop=font)
#ax.set_title("QuantIntv",axis_font)

ax.set_xlabel("(b) QuantIntv",{'family' : 'Times New Roman', 'size'   : 36})

ax = fig.add_subplot(153)

rects1 = ax.bar(ind-width, SZ[4,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, SZ[5,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, SZ[14,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width,SZ[15,:], width, color='y',hatch='/',label="Hilbert+zMesh")

#ax.set_ylabel('Average value',axis_font)
#ax.set_yscale('log')
y_major_locator=plt.MultipleLocator(200)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,900])
ax.set_xlim([-0.3,2.7])
#ax.legend(loc=2,ncol=2, prop=font)
#ax.set_title("TreeSize",axis_font)

ax.set_xlabel("(c) TreeSize",{'family' : 'Times New Roman', 'size'   : 36})

ax = fig.add_subplot(154)

rects1 = ax.bar(ind-width, SZ[6,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, SZ[7,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, SZ[16,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width,SZ[17,:], width, color='y',hatch='/',label="Hilbert+zMesh")

#ax.set_ylabel('Average value',axis_font)
ax.set_yscale('log')
#y_major_locator=plt.MultipleLocator(200)
#ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,900])
ax.set_xlim([-0.3,2.7])
#ax.legend(loc=2,ncol=2, prop=font)
#ax.set_title("EncodeSize",axis_font)

ax.set_xlabel("(d) EncodeSize",{'family' : 'Times New Roman', 'size'   : 36})

ax = fig.add_subplot(155)

rects1 = ax.bar(ind-width, SZ[8,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, SZ[9,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, SZ[18,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width,SZ[19,:], width, color='y',hatch='/',label="Hilbert+zMesh")

#ax.set_ylabel('Average value',axis_font)
ax.set_yscale('log')
#y_major_locator=plt.MultipleLocator(200)
#ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,900])
ax.set_xlim([-0.3,2.7])
#ax.legend(loc=2,ncol=2, prop=font)
#ax.set_title("OutlierSize",axis_font)
ax.set_xlabel("(e) OutlierSize",{'family' : 'Times New Roman', 'size'   : 36})
plt.legend( (rects1[0], rects2[0],rects3[0],rects4[0]), ('Z-order', 'Z-order+zMesh',"Hilbert","Hilbert+zMesh") ,ncol=4, bbox_to_anchor=(-0.2, 1.51),prop=font)
#plt.legend(bbox_to_anchor=(0, 1),(rects1[0],rects2[0],rects3[0],rects4[0]),("1", "2", "3","4"),ncol=4)
fig.tight_layout()

plt.savefig(name_hat+'SZ_metrics.pdf', format='pdf',bbox_inches="tight")
#plt.show()
