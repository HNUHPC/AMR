cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier
echo PineIslandGlacier

python ../repostitory/value_plot.py Level_box_zordering_0.dat PineIslandGlacier_Z-ordering
python ../repostitory/value_plot.py Level_box_zordering_levelreordering_0.dat PineIslandGlacier_Z-ordering+level-reordering

cd ../MISMIP3D/ 
echo MISMIP3D
python ../repostitory/value_plot.py Level_box_zordering_0.dat MISMIP3D_Z-ordering
python ../repostitory/value_plot.py Level_box_zordering_levelreordering_0.dat MISMIP3D_Z-ordering+level-reordering

cd ../Greenland
echo Greenland
#../../code/filetools/stats2d.Linux.64.g++.gfortran.DEBUG.ex plot.GIS.5km.l1l2.5lev.000000.2d.hdf5 918 1028 9.81


#python ../PineIslandGlacier/value_plot.py Level_row.dat Greenland_Row-major
#python ../PineIslandGlacier/value_plot.py Level_row_levelreordering.dat Greenland_Row-major+Level-reordering
#python ../PineIslandGlacier/value_plot.py Level_box.dat Greenland_Row-major
#python ../PineIslandGlacier/value_plot.py Level_box_levelreordering.dat Greenland_Row-major+Box+Level-reordering
#python ../PineIslandGlacier/value_plot.py Level_row_zordering.dat Greenland_Z-ordering
#python ../PineIslandGlacier/value_plot.py Level_row_zordering_levelreordering.dat Greenland_Z-ordering+Level-reordering
python ../repostitory/value_plot.py Level_box_zordering_0.dat Greenland_Z-ordering
python ../repostitory/value_plot.py Level_box_zordering_levelreordering_0.dat Greenland_Z-ordering+level-reordering

