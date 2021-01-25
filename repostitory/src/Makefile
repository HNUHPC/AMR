GFORTRAN    = gfortran -Wall
CC          = gcc -O3 -g
#CC          = gcc -g
MPI_FORTRAN = mpif90 -Wall
MPI_CC      = mpicc 
LD = -lm

.SUFFIXES : .o .c

Target:=reordering access_queries  distance overhead_all overhead_zorder overhead_hilbert 2Dcompression interpolate 

all: $(Target)


$(Target): %:%.o
	$(CC) $(LD) $< -o $@  -L/home/luo/ZFP/zfp/lib/ -lzfp   -lSZ  -lzstd -lzlib  -L/home/luo/ZFP/fpzip/lib/ -lfpzip -lm 
%.o : %.c
	$(CC) -c $(*F).c -I/home/luo/ZFP/zfp/include/  -I/home/luo/ZFP/fpzip/include/

clean :
	/bin/rm -f *.o $(Target) 
