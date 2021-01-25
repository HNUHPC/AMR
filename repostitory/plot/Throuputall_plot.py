import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re 

name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/"

data = np.loadtxt("throuputall.txt")
x =range(0,6)
namelist=[ "1","2","3","4","5","6"]
#namelist=["P1","P2","P3","P4","P5","P6"]
Z=np.zeros((8,6),dtype=float)
for i in range(0,8):
    for j in range(0,6):
        Z[i][j]=data[i//2][i%2+2*j] 
print Z
H=np.zeros((8,6),dtype=float)
for i in range(0,8):
    for j in range(0,6):
        H[i][j]=data[4+i//2][i%2+2*j] 

print H

N = len(x)
ind = np.arange(N)  # the x locations for the groups
width = 0.2       # the width of the bars

fig = plt.figure(num=None,figsize=(16,7))
axis_font = {'size':'28'}
plt.rc('xtick', labelsize=28)          # fontsize of the tick labels
plt.rc('ytick', labelsize=28)
font = {'size':'28'}



ax = fig.add_subplot(221)

rects1 = ax.bar(ind-width, Z[0,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, Z[1,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, H[0,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width, H[1,:], width, color='y',hatch='/',label="Hilbert+zMesh")

ax.set_ylabel('Throughput\n (MB/s)',axis_font)
y_major_locator=plt.MultipleLocator(100)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
ax.set_ylim([0,300])
ax.set_xlim([-0.3,5.7])
#ax.legend(loc=2,ncol=1, prop=font)
plt.legend( (rects1[0], rects2[0],rects3[0],rects4[0]), ('Z-order', 'Z-order+zMesh',"Hilbert","Hilbert+zMesh") ,ncol=2, bbox_to_anchor=(1.8, 1.98),prop=font)
#ax.set_title("ZFP compression",axis_font)
#ax.set_xlabel("(a) ZFP compression",{'family' : 'Times New Roman', 'size'   : 36})
ax.set_xlabel("Number of quantities\n(a) ZFP compression",{ 'size'   : 28})
#ax.text(2,-1,"(a) ZFP compression",{'family' : 'Times New Roman', 'size'   : 36})

#plt.savefig(name_hat+'ThrouputZFPCM.pdf', format='pdf',bbox_inches="tight")
#plt.show()


#fig = plt.figure(num=None,figsize=(8,4))



ax = fig.add_subplot(222)

rects1 = ax.bar(ind-width, Z[2,:], width, color='g',hatch='.',label="Z" )
rects2 = ax.bar(ind, Z[3,:], width, color='r',hatch='+',label="Z+LevelRe")
rects3 = ax.bar(ind+width, H[2,:], width, color='blue',hatch='x',label="H" )
rects4 = ax.bar(ind+2*width, H[3,:], width, color='y',hatch='/',label="H+LevelRe")

#ax.set_ylabel('Throughput (MB/s)',axis_font)
y_major_locator=plt.MultipleLocator(100)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
ax.set_ylim([0,300])
ax.set_xlim([-0.3,5.7])
#ax.legend(loc=2,ncol=2, prop=font)
#ax.set_title("ZFP decomepression",axis_font)
ax.set_xlabel("Number of quantities\n(b) ZFP decompression",{ 'size'   : 28})

#ax.set_xlabel("(b) ZFP decompression",{'family' : 'Times New Roman', 'size'   : 36})
#plt.savefig(name_hat+'ThrouputZFPDECM.pdf', format='pdf',bbox_inches="tight")
#plt.show()



#fig = plt.figure(num=None,figsize=(8,4))



ax = fig.add_subplot(223)

rects1 = ax.bar(ind-width, Z[4,:], width, color='g',hatch='.',label="Z" )
rects2 = ax.bar(ind, Z[5,:], width, color='r',hatch='+',label="Z+LevelRe")
rects3 = ax.bar(ind+width, H[4,:], width, color='blue',hatch='x',label="H" )
rects4 = ax.bar(ind+2*width, H[5,:], width, color='y',hatch='/',label="H+LevelRe")

ax.set_ylabel('Throughput\n (MB/s)',axis_font)
y_major_locator=plt.MultipleLocator(100)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
ax.set_ylim([0,320])
ax.set_xlim([-0.3,5.7])
#ax.legend(loc=2,ncol=2, prop=font)
#ax.set_title("SZ compression",axis_font)
#ax.set_xlabel("(c) SZ compression",{'family' : 'Times New Roman', 'size'   : 36})
ax.set_xlabel("Number of quantities\n(c) SZ compression",{ 'size'   : 28})

#plt.savefig(name_hat+'ThrouputSZCM.pdf', format='pdf',bbox_inches="tight")
#plt.show()



#fig = plt.figure(num=None,figsize=(8,4))



ax = fig.add_subplot(224)

rects1 = ax.bar(ind-width, Z[6,:], width, color='g',hatch='.',label="Z" )
rects2 = ax.bar(ind, Z[7,:], width, color='r',hatch='+',label="Z+LevelRe")
rects3 = ax.bar(ind+width, H[6,:], width, color='blue',hatch='x',label="H" )
rects4 = ax.bar(ind+2*width, H[7,:], width, color='y',hatch='/',label="H+LevelRe")

#ax.set_ylabel('Throughput (MB/s)',axis_font)
y_major_locator=plt.MultipleLocator(100)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
ax.set_ylim([0,300])
ax.set_xlim([-0.3,5.7])
#ax.legend(loc=2,ncol=2, prop=font)
#ax.set_title("SZ decompression",axis_font)
#pax.set_xlabel("(d) SZ decompression",{'family' : 'Times New Roman', 'size'   : 36})
ax.set_xlabel("Number of quantities\n(d) SZ decompression",{ 'size'   : 28})
plt.tight_layout()

plt.savefig(name_hat+'Throuput1.pdf', format='pdf',bbox_inches="tight")
plt.show()

