
cd ../repostitory/
sed -i "7s/.*/#define Level 5/" ../repostitory/reordering.c
make -f Makefile

cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier
echo PineIslandGlacier
../../code/filetools/stats_all182d.Linux.64.g++.gfortran.DEBUG.ex plot.pigv5.1km.l1l2.4lev.005138.2d.hdf5 918 1028 9.81
../repostitory/reordering

