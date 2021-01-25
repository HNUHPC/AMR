#cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier
echo PineIslandGlacier
rm level_overhead.txt
rm level_overhead_H.txt
i="2";
while [ $i -lt 6 ]
do
../../code/filetools/stats2d.Linux.64.g++.gfortran.DEBUG.ex ../PineIslandGlacier/plot.pigv5.1km.l1l2.$(( $i-1 ))lev.000000.2d.hdf5 918 1028 9.81
sed -i "7s/.*/#define Level $i/" overhead_level.c 
sed -i "7s/.*/#define Level $i/" overhead_level_H.c 
make -f Makefile
 ../repostitory/overhead_level ../repostitory/datapoint_level_overhead.info >>level_overhead.txt
 ../repostitory/overhead_level_H ../repostitory/datapoint_level_overhead.info >>level_overhead_H.txt
echo $i
i=$[$i+1]
done

i="6";
while [ $i -lt 10 ]
do
../../code/filetools/stats2d.Linux.64.g++.gfortran.DEBUG.ex ../PineIslandGlacier/error_plot.pigv5.1km.l1l2.$(( $i-1 ))lev.000000.2d.hdf5 918 1028 9.81
sed -i "7s/.*/#define Level $i/" overhead_level.c 
sed -i "7s/.*/#define Level $i/" overhead_level_H.c 
make -f Makefile
 ../repostitory/overhead_level ../repostitory/datapoint_level_overhead.info >>level_overhead.txt
 ../repostitory/overhead_level_H ../repostitory/datapoint_level_overhead.info >>level_overhead_H.txt
echo $i
i=$[$i+1]
done


