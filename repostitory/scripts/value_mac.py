import numpy as np
import matplotlib.pyplot as plt
from matplotlib import mlab
import sys
import array
import os

if len(sys.argv) < 1 :
    print 'usage: python %s <file.dat' % sys.argv[0]
    sys.exit(0)

#print sys.argv[1]

statinfo=os.stat(sys.argv[1])
fsize=statinfo.st_size
#print fsize/8
fin = open(sys.argv[1], 'rb')
vals = array.array('d',(int(fsize/8))*[0])

fin.readinto(vals)
fin.close()


deltas = array.array('d',(int(fsize/8))*[0])
for i in range(1,len(vals)):
    deltas[i]=abs(vals[i]-vals[i-1])
    if deltas[i]> 10000:
       deltas[i]=10000


mad=sum(deltas)/len(deltas)
print mad
