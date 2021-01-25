
cd ../repostitory/
sed -i "7s/.*/#define Level 5/" ../repostitory/access_number.c
make access_number

cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier
echo PineIslandGlacier

../repostitory/access_number 

cd ../repostitory/
sed -i "7s/.*/#define Level 9/" ../repostitory/access_number.c
make access_number

cd ../MISMIP3D/ 
echo MISMIP3D

../repostitory/access_number 



cd ../repostitory/
sed -i "7s/.*/#define Level 6/" ../repostitory/access_number.c
make access_number 
cd ../Greenland
echo Greenland

../repostitory/access_number 
