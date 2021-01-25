rm ../repostitory/result.txt
cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier

echo PineIslandGlacier
../repostitory/compress_index.sh
cd ../MISMIP3D/ 
echo MISMIP3D
../repostitory/compress_index.sh

cd ../Greenland
echo Greenland
../repostitory/compress_index.sh

cd ../repostitory/
python CR_plot.py
