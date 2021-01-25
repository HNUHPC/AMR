import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re 

name_hat = ""

namelist=[ "4","8","16","32","64","128","256","512","1K","2K","4K","8K","32K","64K","128K","256K","512K","1M","2M","4M","8M","32M","64M","128M","256M","512M","1G","2G","4G","8G","32G","64G","128G","256G","512G"]
data = np.loadtxt("../PineIslandGlacier/2Dcompressor.txt")
data=data.reshape(-1,3)
N=len(data[:,0])/2
x =range(0,N)
ZFP=np.zeros((N,3),dtype=float)
for i in range(0,N):
    for j in range(0,3):
        ZFP[i][j]=data[i][j] 
print  ZFP 
SZ=np.zeros((N,3),dtype=float)
for i in range(0,N):
    for j in range(0,3):
        SZ[i][j]=data[N+i][j] 
print  SZ 

ind = np.arange(N)  # the x locations for the groups
width = 0.2       # the width of the bars

axis_font = {'size':'28'}
plt.rc('xtick', labelsize=28)          # fontsize of the tick labels
plt.rc('ytick', labelsize=28)
font = {'size':'28'}

fig = plt.figure(num=None,figsize=(20,4))
ax = fig.add_subplot(111)

rects1 = ax.bar(ind-width, ZFP[:,0], width, color='b',label="LevelbyLevel" )
rects2 = ax.bar(ind, ZFP[:,1], width, color='g',label="Z-order")
rects3 = ax.bar(ind+width, ZFP[:,2], width, color='r',label="Z-order" )

ax.set_ylabel('Compression ratio',axis_font)
#ax.set_yscale('log')
#y_major_locator=plt.MultipleLocator(200)
#ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
ax.set_ylim([0,12])
ax.set_xlim([-0.3,N-0.3])
#ax.legend(ncol=3, prop=font,bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0)
ax.legend(ncol=3, prop=font)
ax.set_title("P1 ZFP compression",axis_font)

ax.set_xlabel('Number of row',axis_font)
plt.savefig(name_hat+'2D_ZFP_P1.pdf', format='pdf',bbox_inches="tight")
#plt.show()


fig = plt.figure(num=None,figsize=(20,4))
ax = fig.add_subplot(111)

rects1 = ax.bar(ind-width, SZ[:,0], width, color='b',label="LevelbyLevel" )
rects2 = ax.bar(ind, SZ[:,1], width, color='g',label="Z-order")
rects3 = ax.bar(ind+width, SZ[:,2], width, color='r',label="Z-order" )

ax.set_ylabel('Compression ratio',axis_font)
#ax.set_yscale('log')
#y_major_locator=plt.MultipleLocator(200)
#ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,12])
ax.set_xlim([-0.3,N-0.3])
#ax.legend(ncol=3, prop=font,bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0)
#ax.legend(ncol=3, prop=font)
ax.set_title("P1 SZ compression",axis_font)

ax.set_xlabel('Number of row',axis_font)
plt.savefig(name_hat+'2D_SZ_P1.pdf', format='pdf',bbox_inches="tight")
#plt.show()


data = np.loadtxt("../MISMIP3D/2Dcompressor.txt")
data=data.reshape(-1,3)
N=len(data[:,0])/2
x =range(0,N)
ZFP=np.zeros((N,3),dtype=float)
for i in range(0,N):
    for j in range(0,3):
        ZFP[i][j]=data[i][j] 
print  ZFP 
SZ=np.zeros((N,3),dtype=float)
for i in range(0,N):
    for j in range(0,3):
        SZ[i][j]=data[N+i][j] 
print  SZ 

ind = np.arange(N)  # the x locations for the groups
width = 0.2       # the width of the bars

axis_font = {'size':'28'}
plt.rc('xtick', labelsize=28)          # fontsize of the tick labels
plt.rc('ytick', labelsize=28)
font = {'size':'28'}

fig = plt.figure(num=None,figsize=(20,4))
ax = fig.add_subplot(111)

rects1 = ax.bar(ind-width, ZFP[:,0], width, color='b',label="LevelbyLevel" )
rects2 = ax.bar(ind, ZFP[:,1], width, color='g',label="Z-order")
rects3 = ax.bar(ind+width, ZFP[:,2], width, color='r',label="Z-order" )

ax.set_ylabel('Compression ratio',axis_font)
#ax.set_yscale('log')
#y_major_locator=plt.MultipleLocator(200)
#ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,12])
ax.set_xlim([-0.3,N-0.3])
#ax.legend(ncol=3, prop=font,bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0)
#ax.legend(ncol=3, prop=font)
ax.set_title("M1 ZFP compression",axis_font)

ax.set_xlabel('Number of row',axis_font)
plt.savefig(name_hat+'2D_ZFP_M1.pdf', format='pdf',bbox_inches="tight")
#plt.show()


fig = plt.figure(num=None,figsize=(20,4))
ax = fig.add_subplot(111)

rects1 = ax.bar(ind-width, SZ[:,0], width, color='b',label="LevelbyLevel" )
rects2 = ax.bar(ind, SZ[:,1], width, color='g',label="Z-order")
rects3 = ax.bar(ind+width, SZ[:,2], width, color='r',label="Z-order" )

ax.set_ylabel('Compression ratio',axis_font)
#ax.set_yscale('log')
#y_major_locator=plt.MultipleLocator(200)
#ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,12])
ax.set_xlim([-0.3,N-0.3])
#ax.legend(ncol=3, prop=font,bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0)
#ax.legend(ncol=3, prop=font)
ax.set_title("M1 SZ compression",axis_font)

ax.set_xlabel('Number of row',axis_font)
plt.savefig(name_hat+'2D_SZ_M1.pdf', format='pdf',bbox_inches="tight")
#plt.show()


data = np.loadtxt("../Greenland/2Dcompressor.txt")
data=data.reshape(-1,3)
N=len(data[:,0])/2
x =range(0,N)
ZFP=np.zeros((N,3),dtype=float)
for i in range(0,N):
    for j in range(0,3):
        ZFP[i][j]=data[i][j] 
print  ZFP 
SZ=np.zeros((N,3),dtype=float)
for i in range(0,N):
    for j in range(0,3):
        SZ[i][j]=data[N+i][j] 
print  SZ 

ind = np.arange(N)  # the x locations for the groups
width = 0.2       # the width of the bars

axis_font = {'size':'28'}
plt.rc('xtick', labelsize=28)          # fontsize of the tick labels
plt.rc('ytick', labelsize=28)
font = {'size':'28'}

fig = plt.figure(num=None,figsize=(20,4))
ax = fig.add_subplot(111)

rects1 = ax.bar(ind-width, ZFP[:,0], width, color='b',label="LevelbyLevel" )
rects2 = ax.bar(ind, ZFP[:,1], width, color='g',label="Z-order")
rects3 = ax.bar(ind+width, ZFP[:,2], width, color='r',label="Z-order" )

ax.set_ylabel('Compression ratio',axis_font)
#ax.set_yscale('log')
#y_major_locator=plt.MultipleLocator(200)
#ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,12])
ax.set_xlim([-0.3,N-0.3])
#ax.legend(ncol=3, prop=font,bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0)
#ax.legend(ncol=3, prop=font)
ax.set_title("G1 ZFP compression",axis_font)

ax.set_xlabel('Number of row',axis_font)
plt.savefig(name_hat+'2D_ZFP_G1.pdf', format='pdf',bbox_inches="tight")
#plt.show()


fig = plt.figure(num=None,figsize=(20,4))
ax = fig.add_subplot(111)

rects1 = ax.bar(ind-width, SZ[:,0], width, color='b',label="LevelbyLevel" )
rects2 = ax.bar(ind, SZ[:,1], width, color='g',label="Z-order")
rects3 = ax.bar(ind+width, SZ[:,2], width, color='r',label="Z-order" )

ax.set_ylabel('Compression ratio',axis_font)
#ax.set_yscale('log')
#y_major_locator=plt.MultipleLocator(200)
#ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,12])
ax.set_xlim([-0.3,N-0.3])
#ax.legend(ncol=3, prop=font,bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0)
#ax.legend(ncol=3, prop=font)
ax.set_title("G1 SZ compression",axis_font)

ax.set_xlabel('Number of row',axis_font)
plt.savefig(name_hat+'2D_SZ_G1.pdf', format='pdf',bbox_inches="tight")
#plt.show()
