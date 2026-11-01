for i in {1..40}
do
  if [ $i -le 9 ]; then
    echo "Generating DDbBackground Friend File 0$i"
    root -b -l -q 'makeFriend.C("DDbBackground_0'${i}'_tree.root","DDbBackground_0'${i}'_tree_friend.root",1000000000,3.760)'
  else
    echo "Generating DDbBackground Friend File $i"
    root -b -l -q 'makeFriend.C("DDbBackground_'${i}'_tree.root","DDbBackground_'${i}'_tree_friend.root",1000000000,3.760)'
  fi
done
hadd -f hadd_DDbBackground_tree_friend.root DDbBackground_*_tree_friend.root
rm DDbBackground_*_tree_friend.root

for i in {1..40}
do
  if [ $i -le 9 ]; then
    echo "Generating DDbBackgroundMore Friend File 0$i"
    root -b -l -q 'makeFriend.C("DDbBackground_0'${i}'_tree.root","DDbBackgroundMore_0'${i}'_tree_friend.root",1000000000,3.825)'
  else
    echo "Generating DDbBackgroundMore Friend File $i"
    root -b -l -q 'makeFriend.C("DDbBackground_'${i}'_tree.root","DDbBackgroundMore_'${i}'_tree_friend.root",1000000000,3.825)'
  fi
done
hadd -f hadd_DDbBackgroundMore_tree_friend.root DDbBackgroundMore_*_tree_friend.root
rm DDbBackgroundMore_*_tree_friend.root
