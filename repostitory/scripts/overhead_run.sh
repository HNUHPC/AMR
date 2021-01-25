
cd ../repostitory/
sed -i "7s/.*/#define Level 5/" ../repostitory/overhead_all.c
make -f Makefile


echo PineIslandGlacier 
 ../repostitory/overhead_all  ../PineIslandGlacier/datapoint_0




sed -i "7s/.*/#define Level 9/" ../repostitory/overhead_all.c
make -f Makefile


echo MISMIP3D
 ../repostitory/overhead_all ../MISMIP3D/datapoint_0




sed -i "7s/.*/#define Level 6/" ../repostitory/overhead_all.c
make -f Makefile

echo Greenland
 ../repostitory/overhead_all ../Greenland/datapoint_0
