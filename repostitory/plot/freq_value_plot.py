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
x1=0;
x2=int(fsize/8);
y1=min(vals)
y2=max(vals)
plt.figure(num=None,figsize=(3.5,3))
plt.rc('xtick', labelsize=14)          # fontsize of the tick labels
plt.rc('ytick', labelsize=14)
#plt.xlim(-60,60)   
plt.xlim(y1,y2)
#plt.xticks(np.arange(0,260000,50000))
#plt.xticks([y1,y2]);
print y2

axis_font = {'size':'14'}
axes = plt.gca()
#plt.xlabel('Data point ID', **axis_font)
plt.xlabel('Data value', **axis_font)

#plt.ylabel('Data value',**axis_font )
plt.ylabel('Data frequency',**axis_font )
title_name=sys.argv[2]
#plt.title(title_name, **axis_font)
n, bins, patches=plt.hist(vals,bins=100,normed=True,histtype='bar', label='pdf', color='black')
#n, bins, patches=plt.hist(vals,bins=1000,normed=True,histtype='step', cumulative=True, label='cdf',color='black')

#plt.plot(vals);

#plt.plot(vals,'b')


plt.tight_layout()
#plt.savefig('/home/luo/Dropbox/SC2019_Huizhang/AMR2019/figures/fig_frequency_zordering.pdf', format='pdf')
plt.savefig('/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/fig_'+sys.argv[2]+'.pdf', format='pdf',bbox_inches="tight")
#plt.show()
