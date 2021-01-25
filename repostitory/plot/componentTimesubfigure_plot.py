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

axis_font = {'size':'32'}
plt.rc('xtick', labelsize=32)          # fontsize of the tick labels
plt.rc('ytick', labelsize=32)
font = {'size':'32'}
fig=plt.figure(figsize=(36,4))
ax = fig.add_subplot(161)

rects1 = ax.bar(ind-width, CPN[0,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, CPN[1,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, CPN[10,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width,CPN[11,:], width, color='y',hatch='/',label="Hilbert+zMesh")

ax.set_ylabel('Time (s)',axis_font)
#ax.set_yscale('log')
y_major_locator=plt.MultipleLocator(100)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,900])
ax.set_xlim([-0.3,2.7])
#ax.legend(ncol=1, prop=font,bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0)
#ax.set_title("Reorder recipe",axis_font)
ax.set_xlabel("(a) Data reorder",{'family' : 'Times New Roman', 'size'   : 36})

ax = fig.add_subplot(162)
rects1 = ax.bar(ind-width, CPN[2,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, CPN[3,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, CPN[12,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width,CPN[13,:], width, color='y',hatch='/',label="Hilbert+zMesh")

#ax.set_ylabel('Time (s)',axis_font)
y_major_locator=plt.MultipleLocator(100)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,900])
ax.set_xlim([-0.3,2.7])
#ax.legend(loc=2,ncol=2, prop=font)
#ax.set_title("Restore recipe",axis_font)

ax.set_xlabel("(b) Data restoration",{'family' : 'Times New Roman', 'size'   : 36})

ax = fig.add_subplot(163)

rects1 = ax.bar(ind-width, CPN[4,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, CPN[5,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, CPN[14,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width,CPN[15,:], width, color='y',hatch='/',label="Hilbert+zMesh")

#ax.set_ylabel('Time (s)',axis_font)
#ax.set_yscale('log')
y_major_locator=plt.MultipleLocator(50)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,900])
ax.set_xlim([-0.3,2.7])
#ax.legend(loc=2,ncol=2, prop=font)
#ax.set_title("ZFP compression",axis_font)

ax.set_xlabel("(c) ZFP compression",{'family' : 'Times New Roman', 'size'   : 36})

ax = fig.add_subplot(164)

rects1 = ax.bar(ind-width, CPN[6,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, CPN[7,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, CPN[16,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width,CPN[17,:], width, color='y',hatch='/',label="Hilbert+zMesh")

#ax.set_ylabel('Time (s)',axis_font)
#ax.set_yscale('log')
y_major_locator=plt.MultipleLocator(50)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,900])
ax.set_xlim([-0.3,2.7])
#ax.legend(loc=2,ncol=2, prop=font)
#ax.set_title("ZFP decompression",axis_font)

ax.set_xlabel("(d) ZFP decompression",{'family' : 'Times New Roman', 'size'   : 36})

ax = fig.add_subplot(165)

rects1 = ax.bar(ind-width, CPN[8,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, CPN[9,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, CPN[18,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width,CPN[19,:], width, color='y',hatch='/',label="Hilbert+zMesh")

#ax.set_ylabel('Time (s)',axis_font)
#ax.set_yscale('log')
y_major_locator=plt.MultipleLocator(50)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,900])
ax.set_xlim([-0.3,2.7])
#ax.legend(loc=2,ncol=2, prop=font)
#ax.set_title("SZ compression",axis_font)
ax.set_xlabel("(e) SZ compression",{'family' : 'Times New Roman', 'size'   : 36})

ax = fig.add_subplot(166)

rects1 = ax.bar(ind-width, CPN[20,:], width, color='g',hatch='.',label="Z-order" )
rects2 = ax.bar(ind, CPN[21,:], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, CPN[22,:], width, color='blue',hatch='x',label="Hilbert" )
rects4 = ax.bar(ind+2*width,CPN[23,:], width, color='y',hatch='/',label="Hilbert+zMesh")

#ax.set_ylabel('Time (s)',axis_font)
#ax.set_yscale('log')
y_major_locator=plt.MultipleLocator(50)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
#ax.set_ylim([0,900])
ax.set_xlim([-0.3,2.7])
#ax.legend(loc=2,ncol=2, prop=font)
#ax.set_title("SZ decompression",axis_font)
ax.set_xlabel("(f) SZ decompression",{'family' : 'Times New Roman', 'size'   : 36})

plt.legend( (rects1[0], rects2[0],rects3[0],rects4[0]), ('Z-order', 'Z-order+zMesh',"Hilbert","Hilbert+zMesh") ,ncol=4, bbox_to_anchor=(-1, 1.45),prop=font)
#plt.legend(bbox_to_anchor=(0, 1),(rects1[0],rects2[0],rects3[0],rects4[0]),("1", "2", "3","4"),ncol=4)
fig.tight_layout()
plt.savefig(name_hat+'CPN.pdf', format='pdf',bbox_inches="tight")
plt.show()




