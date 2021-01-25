
ratio=0.001
#ratio=0.0001
#List="Level_box_zordering_0.dat Level_box_zordering_levelreordering_0.dat"
List="Level_box_hilbert_0.dat Level_box_hilbert_levelreordering_0.dat"
cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier
echo PineIslandGlacier

maxV=`python ../repostitory/findmax.py Level_box_hilbert_0.dat`
#maxV=`python ../repostitory/findmax.py Level_box_zordering_0.dat`
#echo $maxV
err=$( echo "$ratio*$maxV " |bc )
toobig=$(echo "$err > 10000"|bc )
#echo "$err > 10000"|bc
if [ $toobig -gt 0 ];
then
err=100
fi
echo $err

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
	/home/luo/ZFP/SZ/example/testdouble_compress /home/luo/ZFP/SZ/sz.config  $i $size
	echo $(stat -c%s $i)/$(stat -c%s $i.sz) |bc -l 
	rm  ZFPresult.txt
	rm ZFP_zero.txt
	/home/luo/ZFP/zfp_revised/bin/zfp -a $err -s -d -1 $size -i $i -z $i.zfp
	cat ZFP_zero.txt |wc -l
	python ../repostitory/averageZFP.py ZFPresult.txt
	done



	cd ../MISMIP3D/ 
	echo MISMIP3D


	maxV=`python ../repostitory/findmax.py Level_box_zordering_0.dat`
#echo $maxV
	err=$( echo "$ratio*$maxV " |bc )
	toobig=$(echo "$err > 10000"|bc )
#echo "$err > 10000"|bc
	if [ $toobig -gt 0 ];
	then
	err=100
	fi
	echo $err

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
	/home/luo/ZFP/SZ/example/testdouble_compress /home/luo/ZFP/SZ/sz.config  $i $size
	echo $(stat -c%s $i)/$(stat -c%s $i.sz) |bc -l 
	rm  ZFPresult.txt
	rm ZFP_zero.txt
	/home/luo/ZFP/zfp_revised/bin/zfp -a $err -s -d -1 $size -i $i -z $i.zfp
	cat ZFP_zero.txt |wc -l
	python ../repostitory/averageZFP.py ZFPresult.txt
	done





	cd ../Greenland
	echo Greenland
	maxV=`python ../repostitory/findmax.py Level_box_zordering_0.dat`
#echo $maxV
	err=$( echo "$ratio*$maxV " |bc )
	toobig=$(echo "$err > 10000"|bc )
#echo "$err > 10000"|bc
	if [ $toobig -gt 0 ];
	then
	err=100
	fi
	echo $err

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
	/home/luo/ZFP/SZ/example/testdouble_compress /home/luo/ZFP/SZ/sz.config  $i $size
	echo $(stat -c%s $i)/$(stat -c%s $i.sz) |bc -l 
	rm  ZFPresult.txt
	rm ZFP_zero.txt
	/home/luo/ZFP/zfp_revised/bin/zfp -a $err -s -d -1 $size -i $i -z $i.zfp
	cat ZFP_zero.txt |wc -l
	python ../repostitory/averageZFP.py ZFPresult.txt
	done

