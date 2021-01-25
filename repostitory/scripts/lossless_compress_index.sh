

Mainlist="0 1 2 4 11 12"
# Main loop for batch execution
#for ((j=0;j<$n;j=$j+1))
set -- $Mainlist
for j 

do

#List="Level_box_$j.dat  Level_box_levelreordering_$j.dat Level_box_zordering_$j.dat Level_box_zordering_levelreordering_$j.dat"
List="Level_box_zordering_$j.dat Level_box_zordering_levelreordering_$j.dat Level_box_hilbert_$j.dat Level_box_hilbert_levelreordering_$j.dat"
maxV=`python ../repostitory/findmax.py Level_box_zordering_$j.dat`
#echo $maxV

set -- $List
for i
do

echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
echo $i
echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"


	size='0'
size=$(( $size+ $(stat -c%s $i)/8 ))
	echo $size 
	/home/luo/ZFP/fpzip-1.3.0/bin/fpzip  -t double -1 $size -i $i -o $i.fpzip
	echo $(stat -c%s $i)/$(stat -c%s $i.fpzip) |bc -l>> ../repostitory/lossless_result.txt 

	done

	for i
	do
#    echo $err

	echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
	echo $i
	echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"


	size='0'
size=$(( $size+ $(stat -c%s $i)/8 ))
	echo $size 
/home/luo/ZFP/fpc/fpc 20 <$i  > $i.fpc
	echo $(stat -c%s $i)/$(stat -c%s $i.fpc) |bc -l>>../repostitory/lossless_result.txt
#/home/luo/ZFP/fpc/fpc  < base.fpc > base.fpc.out
	done


	done
