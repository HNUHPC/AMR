GFORTRAN    = gfortran -Wall
CC          = gcc -O3 -g -std=c99
#CC          = gcc -g
MPI_FORTRAN = mpif90 -Wall
MPI_CC      = mpicc 
LD = -lm

.SUFFIXES : .o .c

Target:=hilbert_parallel distance fetches_num 

all: $(Target)


$(Target): %:%.o
	$(CC) $(LD) $< -o $@  -L/home/luo/ZFP/zfp/lib/ -lzfp   -lSZ  -lzstd -lzlib  -L/home/luo/ZFP/fpzip/lib/ -lfpzip -lm 
%.o : %.c
	$(CC) -c $(*F).c -I/home/luo/ZFP/zfp/include/  -I/home/luo/ZFP/fpzip/include/

clean :
	/bin/rm -f *.o $(Target) 
