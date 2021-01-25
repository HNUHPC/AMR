import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re 

name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/"
data = np.loadtxt("box_pattern.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
print np.shape(x)
axis_font = {'size':'30'}
plt.rc('xtick', labelsize=28)          # fontsize of the tick labels
plt.rc('ytick', labelsize=28)

font = {'size':'28'}
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'g-',label="Z-order")
lns2=ax1.plot(x, y2,'r-',label="Z-order+zMesh")
ax1.set_ylabel('Fetching efficiency',font)
ax1.set_ylim([0.4,1.3])
y_major_locator=plt.MultipleLocator(0.2)
ax1.yaxis.set_major_locator(y_major_locator)
#ax1.set_title("Z-order: Pattern 1",axis_font)
ax1.set_xlim([0,len(data)]);
ax1.set_xlabel('Query ID\n(a) Z-order: Pattern 1',font)
ax1.legend(loc=0, prop=font)
#ax1.legend()


plt.savefig(name_hat+'fig_range_query.pdf', format='pdf',bbox_inches="tight")
#plt.show()

data = np.loadtxt("row_pattern.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'g-',label="Z")
lns2=ax1.plot(x, y2,'r-',label="Z+LevelRe")
ax1.set_ylabel('Fetching efficiency',font)
#ax1.set_title("Z-order: Pattern 2",axis_font)
ax1.set_xlim([0,len(data)]);
ax1.set_xlabel('Query ID\n(c) Z-order: Pattern 2',font)
#ax1.legend(loc="upper right", prop=font)
#ax1.legend()


plt.savefig(name_hat+'fig_row_query.pdf', format='pdf',bbox_inches="tight")
#plt.show()



data = np.loadtxt("box_pattern_h.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'b-',label="Hilbert")
lns2=ax1.plot(x, y2,'y-',label="Hilbert+zMesh")
ax1.set_ylabel('Fetching efficiency',font)
y_major_locator=plt.MultipleLocator(0.2)
ax1.yaxis.set_major_locator(y_major_locator)
#ax1.set_title("Hilbert: Pattern 1",axis_font)
ax1.set_xlim([0,len(data)]);
ax1.set_ylim([0.6,1.2]);
ax1.set_xlabel('Query ID\n(b) Hilbert: Pattern 1',font)
ax1.legend(loc=0, prop=font)
#ax1.legend()


plt.savefig(name_hat+'fig_range_query_h.pdf', format='pdf',bbox_inches="tight")
#plt.show()

data = np.loadtxt("row_pattern_h.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
print np.shape(x)
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'b-',label="H")
lns2=ax1.plot(x, y2,'y-',label="H+LevelRe")
ax1.set_ylabel('Fetching efficiency',font)
y_major_locator=plt.MultipleLocator(0.2)
ax1.yaxis.set_major_locator(y_major_locator)
#ax1.set_title("Hilbert: Pattern 2",axis_font)
ax1.set_xlim([0,len(data)]);
ax1.set_xlabel('Query ID\n(d) Hilbert: Pattern 2',font)
#ax1.legend(loc="upper right", prop=font)
#ax1.legend()


plt.savefig(name_hat+'fig_row_query_h.pdf', format='pdf',bbox_inches="tight")
#plt.show()

