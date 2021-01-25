import numpy as np
import matplotlib.pyplot as plt
from matplotlib import mlab
import sys
import array
import os

if len(sys.argv) < 1 :
    print 'usage: python %s <file.dat' % sys.argv[0]
    sys.exit(0)

print sys.argv[1]

statinfo=os.stat(sys.argv[1])
fsize=statinfo.st_size
print fsize/8
fin = open(sys.argv[1], 'rb')
vals = array.array('d',(int(fsize/8))*[0])

fin.readinto(vals)
fin.close()


deltas = array.array('d',(int(fsize/8))*[0])
deltas1 = array.array('d',(int(fsize/8))*[0])
for i in range(1,len(vals)):
    deltas[i]=vals[i]-vals[i-1]

for i in range(1,len(vals)):
    deltas1[i]=abs(vals[i]-vals[i-1])


std1=np.std(deltas)
mad=sum(deltas1)/len(deltas1)
x1=0;
x2=int(fsize/8);
y1=min(vals)
y2=max(vals)
plt.figure(num=None,figsize=(3.5,3))
plt.rc('xtick', labelsize=14)          # fontsize of the tick labels
plt.rc('ytick', labelsize=14)
#plt.ylim(y1,y2)   
#plt.xticks(np.arange(0,260000,50000))
plt.yticks(np.linspace(y1,2000,5));
#y_major_locator=plt.MultipleLocator(5000)
#plt.yaxis.set_major_locator(y_major_locator)
plt.xticks(np.linspace(x1,x2,4));
print y2

axis_font = {'size':'14'}
axes = plt.gca()
plt.xlabel('Data point ID', **axis_font)
#plt.xlabel('Data value', **axis_font)

plt.ylabel('Data value',**axis_font )
#plt.ylabel('Data frequency',**axis_font )
title_name="MAC="+str(mad).split('.')[0] + '.' + str(mad).split('.')[1][:2]
plt.title(title_name, fontsize=16)
#n, bins, patches=plt.hist(vals,bins=100,normed=True,histtype='bar', label='pdf', color='black')
#n, bins, patches=plt.hist(vals,bins=1000,normed=True,histtype='step', cumulative=True, label='cdf',color='black')

plt.plot(vals,'b-');

#plt.plot(vals,'b')


plt.tight_layout()
#plt.savefig('/home/luo/Dropbox/SC2019_Huizhang/AMR2019/figures/fig_frequency_zordering.pdf', format='pdf')
plt.savefig('/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/fig_'+sys.argv[2]+'.pdf', format='pdf',bbox_inches="tight",pad_inches=0)
#plt.savefig('/home/luo/Dropbox/SC2019_Huizhang/AMR2019/figures/fig_'+sys.argv[2]+'.pdf', format='pdf')
#plt.show()
