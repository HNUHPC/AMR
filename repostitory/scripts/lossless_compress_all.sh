rm ../repostitory/lossless_result.txt
cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier
echo PineIslandGlacier
../repostitory/lossless_compress_index.sh
cd ../MISMIP3D/ 
echo MISMIP3D
../repostitory/lossless_compress_index.sh

cd ../Greenland
echo Greenland
../repostitory/lossless_compress_index.sh
