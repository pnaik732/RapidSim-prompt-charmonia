$RAPIDSIM_ROOT/build/src/RapidSim.exe psiToDDb_B 800000 1 > psiToDDb_B.out 
grep -l 'INFO in rapidSim : Selected' *.out
grep 'INFO in rapidSim : Selected' *.out
grep -l 'econds to generate' *.out 
grep 'econds to generate' *.out 
