$RAPIDSIM_ROOT/build/src/RapidSim.exe psiToDDb 800000 1 > psiToDDb.out 
grep -l 'INFO in rapidSim : Selected' *.out
grep 'INFO in rapidSim : Selected' *.out
grep -l 'econds to generate' *.out 
grep 'econds to generate' *.out 
