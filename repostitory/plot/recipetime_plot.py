import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re 

name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/"

data = np.loadtxt("componentTime.txt")
#data=data.reshape(-1,5)
#data_H=data_H.reshape(-1,5)
x =range(0,3)
namelist=[ "P1","M1","G1"]
CPN=np.zeros((24,3),dtype=float)
for i in range(0,24):
    for j in range(0,3):
        CPN[i][j]=data[i//2][i%2+2*j] 
print CPN

N = len(x)
ind = np.arange(N)  # the x locations for the groups
width = 0.2       # the width of the bars

fig = plt.figure(num=None,figsize=(16,3.5))
axis_font = {'size':'28'}
plt.rc('xtick', labelsize=28)          # fontsize of the tick labels
plt.rc('ytick', labelsize=28)
font = {'size':'28'}



ax = fig.add_subplot(121)

rects1 = ax.bar(ind-width, CPN[0,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, CPN[1,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, CPN[10,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width, CPN[11,:], width, color='y',hatch='/',label="Hilbert+zMesh")

ax.set_ylabel('Time (s)',axis_font)
y_major_locator=plt.MultipleLocator(100)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,400])
ax.set_xlim([-0.3,2.7])
#ax.legend(loc=2,ncol=1, prop=font)
plt.legend( (rects1[0], rects2[0],rects3[0],rects4[0]), ('Z-order', 'Z-order+zMesh',"Hilbert","Hilbert+zMesh") ,ncol=2, bbox_to_anchor=(1.8, 1.7),prop=font)

#ax.set_title("ZFP compression",axis_font)
ax.set_xlabel("(a) Data reorder",{'family' : 'Times New Roman', 'size'   : 34})
#plt.savefig(name_hat+'ThrouputZFPCM.pdf', format='pdf',bbox_inches="tight")


#fig = plt.figure(num=None,figsize=(8,4))



ax = fig.add_subplot(122)

rects1 = ax.bar(ind-width, CPN[2,:], width, color='g',hatch='.',label="Z" )
rects2 = ax.bar(ind, CPN[3,:], width, color='r',hatch='+',label="Z+LevelRe")
rects3 = ax.bar(ind+width, CPN[12,:], width, color='blue',hatch='x',label="H" )
rects4 = ax.bar(ind+2*width, CPN[13,:], width, color='y',hatch='/',label="H+LevelRe")

#ax.set_ylabel('Throughput (MB/s)',axis_font)
y_major_locator=plt.MultipleLocator(100)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,400])
ax.set_xlim([-0.3,2.7])
#ax.legend(loc=2,ncol=2, prop=font)
#ax.set_title("ZFP decomepression",axis_font)

ax.set_xlabel("(b) Data Restoration ",{'family' : 'Times New Roman', 'size'   : 36})
#plt.savefig(name_hat+'ThrouputZFPDECM.pdf', format='pdf',bbox_inches="tight")



#fig = plt.figure(num=None,figsize=(8,4))



plt.tight_layout()

plt.savefig(name_hat+'Reordertime.pdf', format='pdf',bbox_inches="tight")
#plt.show()


data = np.loadtxt("componentTimeRelative.txt")
#data=data.reshape(-1,5)
#data_H=data_H.reshape(-1,5)
x =range(0,3)
namelist=[ "P1","M1","G1"]
CPN1=np.zeros((24,3),dtype=float)
CPN=np.zeros((24,3),dtype=float)
for i in range(0,24):
    for j in range(0,3):
        CPN[i][j]=data[i//2][i%2+2*j] 
print CPN

for i in range(0,3):
    CPN1[0][i]=CPN[0][i]/CPN[0][i]
    CPN1[1][i]=CPN[1][i]/CPN[0][i]
    CPN1[10][i]=CPN[10][i]/CPN[10][i]
    CPN1[11][i]=CPN[11][i]/CPN[10][i]

    CPN1[2][i]=CPN[2][i]/CPN[2][i]
    CPN1[3][i]=CPN[3][i]/CPN[2][i]
    CPN1[12][i]=CPN[12][i]/CPN[12][i]
    CPN1[13][i]=CPN[13][i]/CPN[12][i]

    CPN1[4][i]=CPN[4][i]/CPN[4][i]
    CPN1[5][i]=CPN[5][i]/CPN[4][i]
    CPN1[14][i]=CPN[14][i]/CPN[14][i]
    CPN1[15][i]=CPN[15][i]/CPN[14][i]

    CPN1[6][i]=CPN[6][i]/CPN[6][i]
    CPN1[7][i]=CPN[7][i]/CPN[6][i]
    CPN1[16][i]=CPN[16][i]/CPN[16][i]
    CPN1[17][i]=CPN[17][i]/CPN[16][i]


    CPN1[8][i]=CPN[8][i]/CPN[8][i]
    CPN1[9][i]=CPN[9][i]/CPN[8][i]
    CPN1[18][i]=CPN[18][i]/CPN[18][i]
    CPN1[19][i]=CPN[19][i]/CPN[18][i]

    CPN1[20][i]=CPN[20][i]/CPN[20][i]
    CPN1[21][i]=CPN[21][i]/CPN[20][i]
    CPN1[22][i]=CPN[22][i]/CPN[22][i]
    CPN1[23][i]=CPN[23][i]/CPN[22][i]
N = len(x)
ind = np.arange(N)  # the x locations for the groups
width = 0.2       # the width of the bars

fig=plt.figure(figsize=(16,3.5))
ax = fig.add_subplot(121)

rects1 = ax.bar(ind-width, CPN1[0,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, CPN1[1,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, CPN1[10,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width,CPN1[11,:], width, color='y',hatch='/',label="Hilbert+zMesh")

ax.set_ylabel('Overhead',axis_font)
#ax.set_yscale('log')
y_major_locator=plt.MultipleLocator(3)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,900])
ax.set_xlim([-0.3,2.7])
#ax.legend(ncol=1, prop=font,bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0)
#ax.set_title("Reorder recipe",axis_font)
ax.set_xlabel("(a) Data reorder",{'family' : 'Times New Roman', 'size'   : 34})

ax = fig.add_subplot(122)
rects1 = ax.bar(ind-width, CPN1[2,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, CPN1[3,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, CPN1[12,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width,CPN1[13,:], width, color='y',hatch='/',label="Hilbert+zMesh")

#ax.set_ylabel('Time (s)',axis_font)
y_major_locator=plt.MultipleLocator(3)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,900])
ax.set_xlim([-0.3,2.7])
#ax.legend(loc=2,ncol=2, prop=font)
#ax.set_title("Restore recipe",axis_font)

ax.set_xlabel("(b) Data restoration",{'family' : 'Times New Roman', 'size'   : 32})

plt.legend( (rects1[0], rects2[0],rects3[0],rects4[0]), ('Z-order', 'Z-order+zMesh',"Hilbert","Hilbert+zMesh") ,ncol=2, bbox_to_anchor=(0.7, 1.75),prop=font)
plt.tight_layout()

plt.savefig(name_hat+'Reordertime_relative.pdf', format='pdf',bbox_inches="tight")
#plt.show()
