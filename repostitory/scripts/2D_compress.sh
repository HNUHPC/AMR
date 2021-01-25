
cd ../repostitory/
sed -i "7s/.*/#define Level 5/" ../repostitory/2Dcompression.c
make -f Makefile


echo PineIslandGlacier 
cd ../PineIslandGlacier
rm 2Dcompressor.txt
 ../repostitory/2Dcompression>>2Dcompressor.txt




cd ../repostitory/
sed -i "7s/.*/#define Level 9/" ../repostitory/2Dcompression.c
make -f Makefile


echo MISMIP3D
cd ../MISMIP3D
rm 2Dcompressor.txt
 ../repostitory/2Dcompression>>2Dcompressor.txt





cd ../repostitory/
sed -i "7s/.*/#define Level 6/" ../repostitory/2Dcompression.c
make -f Makefile

echo Greenland
cd ../Greenland

rm 2Dcompressor.txt
 ../repostitory/2Dcompression >>2Dcompressor.txt

