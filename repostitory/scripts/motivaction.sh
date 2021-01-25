
gcc interpolate.c -o interpolate
cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier
echo PineIslandGlacier
../repostitory/interpolate
python ../repostitory/value_plot1.py Level_0.dat P1_Level0
python ../repostitory/value_plot3.py Level_1.dat P1_Level1

python ../repostitory/value_plot2.py delta_0_1 P_Delta0_1


#python ../repostitory/freq_value_plot.py delta_0_1 P1_Delta0_1


cd ../MISMIP3D/ 
echo MISMIP3D

../repostitory/interpolate
python ../repostitory/value_plot1.py Level_0.dat M1_Level0
python ../repostitory/value_plot1.py Level_1.dat M1_Level1
#python ../repostitory/value_plot.py Level_2.dat M1_Level2
#python ../repostitory/value_plot.py Level_3.dat M1_Level3
#python ../repostitory/value_plot.py Level_4.dat M1_Level4

python ../repostitory/value_plot2.py delta_0_1 M_Delta0_1

#python ../repostitory/freq_value_plot.py delta_0_1 M1_Delta0_1
cd ../Greenland
echo Greenland

../repostitory/interpolate
python ../repostitory/value_plot1.py Level_0.dat G1_Level0
python ../repostitory/value_plot1.py Level_1.dat G1_Level1
#python ../repostitory/value_plot.py Level_2.dat G1_Level2
#python ../repostitory/value_plot.py Level_3.dat G1_Level3
#python ../repostitory/value_plot.py Level_4.dat G1_Level4

python ../repostitory/value_plot2.py delta_0_1 G_Delta0_1
#python ../repostitory/value_plot.py delta_1_2 g\)Greenland_Delta1_2
#python ../repostitory/value_plot.py delta_2_3 h\)Greenland_Delta2_3
#python ../repostitory/value_plot.py delta_3_4 i\)Greenland_Delta3_4

#python ../repostitory/freq_value_plot.py Level_0.dat a\)Greenland_Level0
#python ../repostitory/freq_value_plot.py Level_1.dat b\)Greenland_Level1
#python ../repostitory/freq_value_plot.py Level_2.dat c\)Greenland_Level2
#python ../repostitory/freq_value_plot.py Level_3.dat d\)Greenland_Level3
#python ../repostitory/freq_value_plot.py Level_4.dat e\)Greenland_Level4

#python ../repostitory/freq_value_plot.py delta_0_1 G1_Delta0_1
#python ../repostitory/freq_value_plot.py delta_1_2 G1_Delta1_2
#python ../repostitory/freq_value_plot.py delta_2_3 G1_Delta2_3
#python ../repostitory/freq_value_plot.py delta_3_4 G1_Delta3_4


#python ../repostitory/freq_value_plot.py delta_3_4 j\)Greenland_Delta3_4_dis
