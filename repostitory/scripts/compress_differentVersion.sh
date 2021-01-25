rm ../repostitory/CR_version_ZFP.txt
rm ../repostitory/CR_version_SZ.txt
declare -i n=-1
declare -i ncol=1024
ratio=0.001
# Index of output file
declare -i j

List="Level_box_zordering_0.dat Level_box_zordering_levelreordering_0.dat Level_box_hilbert_0.dat Level_box_hilbert_levelreordering_0.dat"


cd ../PineIslandGlacier/
maxV=`python ../repostitory/findmax.py Level_box_zordering_0.dat`
#echo $maxV

maxV=$( echo $maxV | awk '{printf("%.15f\n", $1)}')
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
nrow=$(( $size/$ncol ))
	/home/luo/Tao/LossyCompressStudy/zfp/examples/zfp -a $err -s -d -1 $size -i $i -z $i.zfp
	echo $(stat -c%s $i)/$(stat -c%s $i.zfp) |bc -l>>../repostitory/CR_version_ZFP.txt 
	/home/luo/Tao/LossyCompressStudy/zfp/examples/zfp -a $err -s -d -2 $ncol $nrow -i $i -z $i.zfp
	echo $(stat -c%s $i)/$(stat -c%s $i.zfp) |bc -l>>../repostitory/CR_version_ZFP.txt 
	/home/luo/ZFP/zfp/bin/zfp -a $err -s -d -1 $size -i $i -z $i.zfp
	echo $(stat -c%s $i)/$(stat -c%s $i.zfp) |bc -l>>../repostitory/CR_version_ZFP.txt 
	/home/luo/ZFP/zfp/bin/zfp -a $err -s -d -2 $ncol $nrow -i $i -z $i.zfp
	echo $(stat -c%s $i)/$(stat -c%s $i.zfp) |bc -l>>../repostitory/CR_version_ZFP.txt 
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
nrow=$(( $size/$ncol ))
	echo $size 
	/home/luo/Tao/LossyCompressStudy/SZ/example/testdouble_compress /home/luo/ZFP/SZ/sz.config  $i $size
	echo $(stat -c%s $i)/$(stat -c%s $i.sz) |bc -l>>../repostitory/CR_version_SZ.txt
	/home/luo/Tao/LossyCompressStudy/SZ/example/testdouble_compress /home/luo/ZFP/SZ/sz.config  $i  $nrow $ncol
	echo $(stat -c%s $i)/$(stat -c%s $i.sz) |bc -l>>../repostitory/CR_version_SZ.txt
	/home/luo/SZ/SZ/example/testdouble_compress /home/luo/ZFP/SZ/sz.config  $i $size
	echo $(stat -c%s $i)/$(stat -c%s $i.sz) |bc -l>>../repostitory/CR_version_SZ.txt
	/home/luo/SZ/SZ/example/testdouble_compress /home/luo/ZFP/SZ/sz.config  $i $nrow $ncol
	echo $(stat -c%s $i)/$(stat -c%s $i.sz) |bc -l>>../repostitory/CR_version_SZ.txt

	done




	cd  ../MISMIP3D/

	maxV=`python ../repostitory/findmax.py Level_box_zordering_0.dat`
#echo $maxV

	maxV=$( echo $maxV | awk '{printf("%.15f\n", $1)}')
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
nrow=$(( $size/$ncol ))
	/home/luo/Tao/LossyCompressStudy/zfp/examples/zfp -a $err -s -d -1 $size -i $i -z $i.zfp
	echo $(stat -c%s $i)/$(stat -c%s $i.zfp) |bc -l>>../repostitory/CR_version_ZFP.txt 
	/home/luo/Tao/LossyCompressStudy/zfp/examples/zfp -a $err -s -d -2 $ncol $nrow -i $i -z $i.zfp
	echo $(stat -c%s $i)/$(stat -c%s $i.zfp) |bc -l>>../repostitory/CR_version_ZFP.txt 
	/home/luo/ZFP/zfp/bin/zfp -a $err -s -d -1 $size -i $i -z $i.zfp
	echo $(stat -c%s $i)/$(stat -c%s $i.zfp) |bc -l>>../repostitory/CR_version_ZFP.txt 
	/home/luo/ZFP/zfp/bin/zfp -a $err -s -d -2 $ncol $nrow -i $i -z $i.zfp
	echo $(stat -c%s $i)/$(stat -c%s $i.zfp) |bc -l>>../repostitory/CR_version_ZFP.txt 

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
nrow=$(( $size/$ncol ))
	echo $size 
	/home/luo/Tao/LossyCompressStudy/SZ/example/testdouble_compress /home/luo/ZFP/SZ/sz.config  $i $size
	echo $(stat -c%s $i)/$(stat -c%s $i.sz) |bc -l>>../repostitory/CR_version_SZ.txt
	/home/luo/Tao/LossyCompressStudy/SZ/example/testdouble_compress /home/luo/ZFP/SZ/sz.config  $i  $nrow $ncol
	echo $(stat -c%s $i)/$(stat -c%s $i.sz) |bc -l>>../repostitory/CR_version_SZ.txt
	/home/luo/SZ/SZ/example/testdouble_compress /home/luo/ZFP/SZ/sz.config  $i $size
	echo $(stat -c%s $i)/$(stat -c%s $i.sz) |bc -l>>../repostitory/CR_version_SZ.txt
	/home/luo/SZ/SZ/example/testdouble_compress /home/luo/ZFP/SZ/sz.config  $i $nrow $ncol
	echo $(stat -c%s $i)/$(stat -c%s $i.sz) |bc -l>>../repostitory/CR_version_SZ.txt


	done





	cd ../Greenland/
	maxV=`python ../repostitory/findmax.py Level_box_zordering_0.dat`
#echo $maxV

	maxV=$( echo $maxV | awk '{printf("%.15f\n", $1)}')
# Main loop for batch execution
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
nrow=$(( $size/$ncol ))
	/home/luo/Tao/LossyCompressStudy/zfp/examples/zfp -a $err -s -d -1 $size -i $i -z $i.zfp
	echo $(stat -c%s $i)/$(stat -c%s $i.zfp) |bc -l>>../repostitory/CR_version_ZFP.txt 
	/home/luo/Tao/LossyCompressStudy/zfp/examples/zfp -a $err -s -d -2 $ncol $nrow -i $i -z $i.zfp
	echo $(stat -c%s $i)/$(stat -c%s $i.zfp) |bc -l>>../repostitory/CR_version_ZFP.txt 
	/home/luo/ZFP/zfp/bin/zfp -a $err -s -d -1 $size -i $i -z $i.zfp
	echo $(stat -c%s $i)/$(stat -c%s $i.zfp) |bc -l>>../repostitory/CR_version_ZFP.txt 
	/home/luo/ZFP/zfp/bin/zfp -a $err -s -d -2 $ncol $nrow -i $i -z $i.zfp
	echo $(stat -c%s $i)/$(stat -c%s $i.zfp) |bc -l>>../repostitory/CR_version_ZFP.txt 

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
nrow=$(( $size/$ncol ))
	echo $size 
	/home/luo/Tao/LossyCompressStudy/SZ/example/testdouble_compress /home/luo/ZFP/SZ/sz.config  $i $size
	echo $(stat -c%s $i)/$(stat -c%s $i.sz) |bc -l>>../repostitory/CR_version_SZ.txt
	/home/luo/Tao/LossyCompressStudy/SZ/example/testdouble_compress /home/luo/ZFP/SZ/sz.config  $i  $nrow $ncol
	echo $(stat -c%s $i)/$(stat -c%s $i.sz) |bc -l>>../repostitory/CR_version_SZ.txt
	/home/luo/SZ/SZ/example/testdouble_compress /home/luo/ZFP/SZ/sz.config  $i $size
	echo $(stat -c%s $i)/$(stat -c%s $i.sz) |bc -l>>../repostitory/CR_version_SZ.txt
	/home/luo/SZ/SZ/example/testdouble_compress /home/luo/ZFP/SZ/sz.config  $i $nrow $ncol
	echo $(stat -c%s $i)/$(stat -c%s $i.sz) |bc -l>>../repostitory/CR_version_SZ.txt


	done


