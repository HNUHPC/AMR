rm CR_RMSE_MaxE.txt
rm CR_RMSE_MaxE_H.txt
cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier

echo PineIslandGlacier
python ../repostitory/CR_RMSE.py
python ../repostitory/CR_RMSE_H.py
cd ../MISMIP3D/ 
echo MISMIP3D

python ../repostitory/CR_RMSE.py
python ../repostitory/CR_RMSE_H.py
cd ../Greenland
echo Greenland
python ../repostitory/CR_RMSE.py
python ../repostitory/CR_RMSE_H.py
