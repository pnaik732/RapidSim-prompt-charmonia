$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP 800000 1 > XtoDDbP.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP-model-D 800000 1 > XtoDDbP-model-D.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP-model-S 800000 1 > XtoDDbP-model-S.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP-VVS-S-Dst0 400000 1 > XtoDDbP-VVS-S-Dst0.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP-VVS-S-Dst0b 400000 1 > XtoDDbP-VVS-S-Dst0b.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP-VVS-D-Dst0 400000 1 > XtoDDbP-VVS-D-Dst0.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP-VVS-D-Dst0b 400000 1 > XtoDDbP-VVS-D-Dst0b.out 
grep -l 'INFO in rapidSim : Selected' *.out
grep 'INFO in rapidSim : Selected' *.out
grep -l 'econds to generate' *.out 
grep 'econds to generate' *.out 

