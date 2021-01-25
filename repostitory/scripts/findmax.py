import numpy as np
import matplotlib.pyplot as plt
from matplotlib import mlab
import sys
import array
import os

filename=sys.argv[1]
statinfo=os.stat(filename)
fsize=statinfo.st_size
#print fsize/8
fin = open(filename, 'rb')
vals = array.array('d',(int(fsize/8))*[0])

fin.readinto(vals)
fin.close()
y1=min(vals)
y2=max(vals)

print y2;
