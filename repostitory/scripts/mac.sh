
cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier
echo PineIslandGlacier

rm  ../repostitory/MAC.txt 
Mainlist="0 1 2 4 11 12"
# Main loop for batch execution
#for ((j=0;j<$n;j=$j+1))
set -- $Mainlist
for j

do

#List="Level_box_$j.dat  Level_box_levelreordering_$j.dat Level_box_zordering_$j.dat Level_box_zordering_levelreordering_$j.dat"
List="Level_box_zordering_$j.dat Level_box_zordering_levelreordering_$j.dat Level_box_hilbert_$j.dat Level_box_hilbert_levelreordering_$j.dat"


set -- $List
for i
do
#    echo $err

echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
echo $i
echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"

python ../repostitory/value_mac.py $i>>../repostitory/MAC.txt


done


done
cd ../MISMIP3D/ 
echo MISMIP3D

set -- $Mainlist
for j
do


List="Level_box_zordering_$j.dat Level_box_zordering_levelreordering_$j.dat Level_box_hilbert_$j.dat Level_box_hilbert_levelreordering_$j.dat"

set -- $List
for i
do
#    echo $err

echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
echo $i
echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"

python ../repostitory/value_mac.py $i>>../repostitory/MAC.txt


done


done



cd ../Greenland
echo Greenland

set -- $Mainlist
for j
do


List="Level_box_zordering_$j.dat Level_box_zordering_levelreordering_$j.dat Level_box_hilbert_$j.dat Level_box_hilbert_levelreordering_$j.dat"

set -- $List
for i
do
#    echo $err

echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
echo $i
echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"

python ../repostitory/value_mac.py $i>>../repostitory/MAC.txt


done


done

cd ../repostitory 
python MAC_plot.py
