for i in {1..40}
do
  if [ $i -le 9 ]; then
    echo "Generating DDbBackground File 0$i"
    cp DDbBackground.config DDbBackground_0$i.config
    cp DDbBackground.decay DDbBackground_0$i.decay
    $RAPIDSIM_ROOT/build/src/RapidSim.exe DDbBackground_0$i 800000 1 > DDbBackground_0$i.out 
    rm DDbBackground_0$i.config
    rm DDbBackground_0$i.decay
  else
    echo "Generating DDbBackground File $i"
    cp DDbBackground.config DDbBackground_$i.config
    cp DDbBackground.decay DDbBackground_$i.decay
    $RAPIDSIM_ROOT/build/src/RapidSim.exe DDbBackground_$i 800000 1 > DDbBackground_$i.out 
    rm DDbBackground_$i.config
    rm DDbBackground_$i.decay
  fi
done
grep -l 'INFO in rapidSim : Selected' *.out
grep 'INFO in rapidSim : Selected' *.out
grep -l 'econds to generate' *.out
grep 'econds to generate' *.out

