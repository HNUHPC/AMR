
#rm result.txt
#declare -i n=18
# Index of output file
#declare -i j

Mainlist="0 1 2 4 11 12"
# Main loop for batch execution
#for ((j=0;j<$n;j=$j+1))
set -- $Mainlist
for j 

do

#List="Level_box_$j.dat  Level_box_levelreordering_$j.dat Level_box_zordering_$j.dat Level_box_zordering_levelreordering_$j.dat"
#List="Level_box_zordering_$j.dat Level_box_zordering_levelreordering_$j.dat"
List="Level_box_zordering_$j.dat Level_box_zordering_levelreordering_$j.dat Level_box_hilbert_$j.dat Level_box_hilbert_levelreordering_$j.dat"
maxV=`python ../repostitory/findmax.py Level_box_zordering_$j.dat`
#echo $maxV

maxV=$( echo $maxV | awk '{printf("%.15f\n", $1)}')
ratio=0.001
err=$( echo "$ratio*$maxV " |bc )
toobig=$(echo "$err >50"|bc )
#echo "$err > 10000"|bc
if [ $toobig -gt 0 ];
then
err=50
fi

echo $err
set -- $List
for i
do
#    echo $err

echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
echo $i
echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"


	size='0'
size=$(( $size+ $(stat -c%s $i)/8 ))
	echo $size 
	/home/luo/ZFP/zfp/bin/zfp -a $err -s -d -1 $size -i $i -z $i.zfp
	echo $(stat -c%s $i)/$(stat -c%s $i.zfp) |bc -l>>../repostitory/result_largerdataset.txt 
#python ../PineIslandGlacier/cdf.py $i $j
	done

	set -- $List
	sed -i "66s/.*/absErrBound =$err/" /home/luo/ZFP/SZ/sz.config
	for i
	do
#    echo $err

	echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
	echo $i
	echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"


	size='0'
size=$(( $size+ $(stat -c%s $i)/8 ))
	echo $size 
#/home/luo/ZFP/SZ/bin/testdouble_compress /home/luo/ZFP/SZ/sz.config  $i $size
	/home/luo/SZ/SZ/example/testdouble_compress /home/luo/ZFP/SZ/sz.config  $i $size
	echo $(stat -c%s $i)/$(stat -c%s $i.sz) |bc -l>>../repostitory/result_largerdataset.txt

	done


	done
