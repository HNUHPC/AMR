import matplotlib.pyplot as plt
import numpy as np
import sys
import array
import os
import re 
if len(sys.argv) < 2 :
    print 'usage: python %s <file.dat figure' % sys.argv[0]
    sys.exit(0)

print sys.argv[1]

filename=sys.argv[1]
data = np.loadtxt(filename)
data1=np.reshape(data,(-1,4));
print np.shape(data1)
lx1 =data1[:,0]
lx2 = data1[:,1]
lx3 = data1[:,2]
lx4= data1[:,3]
print sum(lx1)/len(lx1),sum(lx2)/len(lx1),sum(lx3)/len(lx1),sum(lx4)/len(lx1)
