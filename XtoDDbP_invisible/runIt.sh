$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_invisible 800000 1 > XtoDDbP_invisible.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_invisible-model-D 800000 1 > XtoDDbP_invisible-model-D.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_invisible-model-S 800000 1 > XtoDDbP_invisible-model-S.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_invisible-VVS-S-Dst0 400000 1 > XtoDDbP_invisible-VVS-S-Dst0.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_invisible-VVS-S-Dst0b 400000 1 > XtoDDbP_invisible-VVS-S-Dst0b.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_invisible-VVS-D-Dst0 400000 1 > XtoDDbP_invisible-VVS-D-Dst0.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_invisible-VVS-D-Dst0b 400000 1 > XtoDDbP_invisible-VVS-D-Dst0b.out 
grep -l 'INFO in rapidSim : Selected' *.out
grep 'INFO in rapidSim : Selected' *.out
grep -l 'econds to generate' *.out 
grep 'econds to generate' *.out 

