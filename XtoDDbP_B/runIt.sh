$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_B 800000 1 > XtoDDbP_B.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_B-model-D 800000 1 > XtoDDbP_B-model-D.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_B-model-S 800000 1 > XtoDDbP_B-model-S.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_B-VVS-S-Dst0 400000 1 > XtoDDbP_B-VVS-S-Dst0.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_B-VVS-S-Dst0b 400000 1 > XtoDDbP_B-VVS-S-Dst0b.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_B-VVS-D-Dst0 400000 1 > XtoDDbP_B-VVS-D-Dst0.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_B-VVS-D-Dst0b 400000 1 > XtoDDbP_B-VVS-D-Dst0b.out 
grep -l 'INFO in rapidSim : Selected' *.out
grep 'INFO in rapidSim : Selected' *.out
grep -l 'econds to generate' *.out 
grep 'econds to generate' *.out 

