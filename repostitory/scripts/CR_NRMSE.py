from __future__ import division
import sys
import array
import scipy.stats as stats
import os


import numpy as np
import matplotlib.pyplot as plt

list1=["0.dat","1.dat","2.dat","4.dat","11.dat","12.dat"];
Ratio=0.001    
# Level_box_zordering_0.dat Level_box_zordering_levelreordering_0.dat 
fp=open("../repostitory/CR_RMSE_MaxE.txt","a")
for i in list1:
    print "*******************"
    print i 
    print "*******************"
    #PW_E=pow(10,(0-err)/4)*(v_max-v_min)
    #fp.write(str(err)+" ") 


    filename="Level_box_zordering_"+i;
    statinfo=os.stat(filename)
    fsize=statinfo.st_size/8
    print filename
    vals_baseline=np.fromfile(filename);
    Err=Ratio*max(vals_baseline)
    if Err>50:
        Err=50
    zfpcmpresscmd = '/home/luo/ZFP/zfp/bin/zfp -a '+str(Err)+' -s -d -1 '+str(fsize)+' -i '+filename+" -z "+filename+'.zfp'
    zfpdecmp = '/home/luo/ZFP/zfp/bin/zfp -a '+str(Err)+' -d -1 '+str(fsize)+ ' -z '+filename+ '.zfp -o '+ filename+ '.zfp.out'

    os.system(zfpcmpresscmd)
   # print zfpdecmp
    os.system(zfpdecmp)

    vals_baseline_0=np.fromfile(filename+".zfp.out");

    #NRMSE= np.sqrt(((vals_1 - vals) ** 2).mean())/(max(vals)-min(vals))
    NRMSE_baseline_zfp= np.sqrt(((vals_baseline_0 - vals_baseline) ** 2).mean())/(max(vals_baseline)-min(vals_baseline))

    Max_err_baseline_zfp=max(vals_baseline_0-vals_baseline)/Err
    print NRMSE_baseline_zfp, Max_err_baseline_zfp

    
    filename1="Level_box_zordering_levelreordering_"+i
    vals_levelRe=np.fromfile(filename1);

    zfpcmpresscmd = '/home/luo/ZFP/zfp/bin/zfp -a '+str(Err)+' -s -d -1 '+str(fsize)+' -i '+filename1+" -z "+filename1+'.zfp'
    zfpdecmp = '/home/luo/ZFP/zfp/bin/zfp -a '+str(Err)+' -d -1 '+str(fsize)+ ' -z '+filename1+ '.zfp -o '+ filename1+ '.zfp.out'

    os.system(zfpcmpresscmd)
   # print zfpdecmp
    os.system(zfpdecmp)

    vals_levelRe_0=np.fromfile(filename1+".zfp.out");

    #NRMSE= np.sqrt(((vals_1 - vals) ** 2).mean())/(max(vals)-min(vals))
    NRMSE_levelRe_zfp= np.sqrt(((vals_levelRe_0 - vals_levelRe) ** 2).mean())/(max(vals_baseline)-min(vals_baseline))
    Max_err_levelRe_zfp=max(vals_levelRe_0-vals_levelRe)/Err
    print NRMSE_levelRe_zfp


    sz1="sed -i \"66s/.*/absErrBound ="+str(Err)+"/\" /home/luo/ZFP/SZ/sz.config"
    os.system(sz1)
    szcmpresscmd = '/home/luo/ZFP/SZ/bin/testdouble_compress /home/luo/ZFP/SZ/sz.config '+ filename + " "+ str(fsize)

    szdecmp = '/home/luo/ZFP/SZ/bin/testdouble_decompress '+ filename+'.sz '+str(fsize)
    os.system(szcmpresscmd)
    os.system(szdecmp)

    statinfo=os.stat(filename+".sz")
    cmpr_fsize=statinfo.st_size/8

     
    vals_baseline_1=np.fromfile(filename+".sz.out");
    
    #NRMSE= np.sqrt(((vals_1 - vals) ** 2).mean())/(max(vals)-min(vals))
    NRMSE_baseline_sz= np.sqrt(((vals_baseline_1 - vals_baseline) ** 2).mean())/(max(vals_baseline)-min(vals_baseline))

    Max_err_baseline_sz=max(vals_baseline_1-vals_baseline)/Err
    print NRMSE_baseline_sz
    #fp.write(str(NRMSE)+" ")        
    


    szcmpresscmd = '/home/luo/ZFP/SZ/bin/testdouble_compress /home/luo/ZFP/SZ/sz.config '+ filename1 + " "+ str(fsize)

    szdecmp = '/home/luo/ZFP/SZ/bin/testdouble_decompress '+ filename1+'.sz '+str(fsize)
    os.system(szcmpresscmd)
    os.system(szdecmp)

    statinfo=os.stat(filename1+".sz")
    cmpr_fsize_levelRe=statinfo.st_size/8

     
    vals_levelRe_1=np.fromfile(filename1+".sz.out");
    
    #NRMSE= np.sqrt(((vals_1 - vals) ** 2).mean())/(max(vals)-min(vals))
    NRMSE_levelRe_sz= np.sqrt(((vals_levelRe_1 - vals_levelRe) ** 2).mean())/(max(vals_baseline)-min(vals_baseline))
    Max_err_levelRe_sz=max(vals_levelRe_1-vals_levelRe)/Err
    print NRMSE_levelRe_sz

    fp.write(str(NRMSE_baseline_zfp)+ " ")
    fp.write(str(NRMSE_levelRe_zfp)+" ")
    fp.write(str(NRMSE_baseline_sz)+ " ")
    fp.write(str(NRMSE_levelRe_sz)+" ")
    fp.write(str( Max_err_baseline_zfp)+ " ")
    fp.write(str( Max_err_levelRe_zfp)+" ")
    fp.write(str( Max_err_baseline_sz)+ " ")
    fp.write(str( Max_err_levelRe_sz)+"\n")
 
fp.close()
