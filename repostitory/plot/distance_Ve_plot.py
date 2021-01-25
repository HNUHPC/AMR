import numpy as np
import matplotlib.pyplot as plt
name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/"

fig = plt.figure(num=None,figsize=(10,5))
axis_font = {'size':'22'}
plt.rc('xtick', labelsize=22)          # fontsize of the tick labels
plt.rc('ytick', labelsize=22)
font = {'size':'22'}
r = 1
N = 15

# Calculate $p_k$

P = np.zeros(N,dtype=float)
P[0]=1/2
P[1]=3/8
for i in range(2,N):
    P[i]=P[i-1]/4

# For given N (the max value of k in a grid)
def comparison(N, r, D=1):
    P = np.zeros(N,dtype=float)
    P[0]=1/2
    if N>0:
        P[1]=3/8
    for i in range(2,N):
        P[i]=P[i-1]/4
    P[-1] *= 4/3    # (Longest)
    
    S2 = np.sqrt(2)/2*(1-2**(-r))

    T2 = np.array(list(map(lambda x:2**(-r)*np.sqrt(2**(2*x)-2**(x+1)+2), range(r,N+r))))
    # print(T2)
    T3 = np.array(list(map(lambda x:np.sqrt(2**(2*x)-2**(x+1)+2), range(N))))

    S3 = np.array(list(map(lambda x:np.sqrt(2**(2*x)-2**(x+1)+2)/2, range(1,N+1))))
    S3[0]=np.sqrt((1+2**(-2*r))/2)
    return np.sum(S2*P),np.sum(T2*P), np.sum(S3*P), np.sum(T3*P)
#     return (np.sum(S3*P-T3*P)),(np.sum(S2*P-T2*P))

length_S = np.zeros(10,dtype=float)
length_T = np.zeros(10,dtype=float)

for r in range(1,11):
    s2,t2,s3,t3 = comparison(20,r)
    length_T[r-1] = t2+t3
    length_S[r-1] = s2+s3
    #print s2 
    


# %matplotlib qt

#ax = fig.subplots()
ax=fig.add_subplot(111)
#print length_S
X = np.zeros(10,dtype=float)
for i in range(1,11):
    X[i-1]=pow(2,i)
ax.plot(X, length_S/2, label="$V_f$")
ax.plot(X, length_T/2, label="$V_e$")
ax.legend(fontsize=22)
ax.set_xscale('log',basex=2)
plt.xlabel("Refinement ratio", axis_font)
plt.ylabel("Expected Length, $i=0$", axis_font)

    
#fig.savefig("distance.pdf")
plt.savefig(name_hat+'fig_expected_lengths.pdf', format='pdf',bbox_inches="tight")
plt.show()    
