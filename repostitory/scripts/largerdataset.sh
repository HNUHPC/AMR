rm result_largerdataset.txt

cd ../repostitory/
sed -i "7s/.*/#define Level 4/" ../repostitory/reordering.c
sed -i "7s/.*/#define Level 4/" ../repostitory/reordering_hilbert.c
make -f Makefile
cd ../Greenland
echo Greenland
../../code/filetools/stats_all182d.Linux.64.g++.gfortran.DEBUG.ex plot.GIS.5km.l1l2.3lev.000000.2d.hdf5 918 1028 9.81
../repostitory/reordering
../repostitory/reordering_hilbert

cd ../Greenland
echo Greenland
../repostitory/compress_largerdataset.sh

cd ../repostitory/
sed -i "7s/.*/#define Level 6/" ../repostitory/reordering.c
sed -i "7s/.*/#define Level 6/" ../repostitory/reordering_hilbert.c
make -f Makefile
cd ../Greenland
echo Greenland
../../code/filetools/stats_all182d.Linux.64.g++.gfortran.DEBUG.ex plot.GIS.5km.l1l2.5lev.000000.2d.hdf5 918 1028 9.81
../repostitory/reordering
../repostitory/reordering_hilbert

cd ../Greenland
echo Greenland
../repostitory/compress_largerdataset.sh

cd ../repostitory/
sed -i "7s/.*/#define Level 8/" ../repostitory/reordering.c
sed -i "7s/.*/#define Level 8/" ../repostitory/reordering_hilbert.c
make -f Makefile
cd ../Greenland
echo Greenland
#../../code/filetools/stats_all182d.Linux.64.g++.gfortran.DEBUG.ex plot.GIS.5km.l1l2.7lev.preSolve.000000.2d.hdf5 918 1028 9.81
#../repostitory/reordering
#../repostitory/reordering_hilbert

cd ../Greenland
echo Greenland
../repostitory/compress_largerdataset.sh
cd ../repostitory/
python CR_largerdataset_plot.py
