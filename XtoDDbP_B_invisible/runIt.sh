$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_B_invisible 800000 1 > XtoDDbP_B_invisible.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_B_invisible-model-D 800000 1 > XtoDDbP_B_invisible-model-D.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_B_invisible-model-S 800000 1 > XtoDDbP_B_invisible-model-S.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_B_invisible-VVS-S-Dst0 400000 1 > XtoDDbP_B_invisible-VVS-S-Dst0.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_B_invisible-VVS-S-Dst0b 400000 1 > XtoDDbP_B_invisible-VVS-S-Dst0b.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_B_invisible-VVS-D-Dst0 400000 1 > XtoDDbP_B_invisible-VVS-D-Dst0.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_B_invisible-VVS-D-Dst0b 400000 1 > XtoDDbP_B_invisible-VVS-D-Dst0b.out 
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_B_invisible-VVS-S-Dst0-noFSR 400000 1 > XtoDDbP_B_invisible-VVS-S-Dst0-noFSR.out
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_B_invisible-VVS-S-Dst0b-noFSR 400000 1 > XtoDDbP_B_invisible-VVS-S-Dst0b-noFSR.out
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_B_invisible-VVS-S-Dst0-8TeV 400000 1 > XtoDDbP_B_invisible-VVS-S-Dst0-8TeV.out
$RAPIDSIM_ROOT/build/src/RapidSim.exe XtoDDbP_B_invisible-VVS-S-Dst0b-8TeV 400000 1 > XtoDDbP_B_invisible-VVS-S-Dst0b-8TeV.out
grep -l 'INFO in rapidSim : Selected' *.out
grep 'INFO in rapidSim : Selected' *.out
grep -l 'econds to generate' *.out 
grep 'econds to generate' *.out 

