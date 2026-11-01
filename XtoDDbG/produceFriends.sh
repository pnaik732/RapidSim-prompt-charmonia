root -b -l -q 'makeFriend.C("XtoDDbG_tree.root","XtoDDbG_tree_friend.root",200000)'
root -b -l -q 'makeFriend.C("XtoDDbG-VVS-S-Dst0_tree.root","XtoDDbG-VVS-S-Dst0_tree_friend.root",100000)'
root -b -l -q 'makeFriend.C("XtoDDbG-VVS-S-Dst0b_tree.root","XtoDDbG-VVS-S-Dst0b_tree_friend.root",100000)'
root -b -l -q 'makeFriend.C("XtoDDbG-VVS-D-Dst0_tree.root","XtoDDbG-VVS-D-Dst0_tree_friend.root",100000)'
root -b -l -q 'makeFriend.C("XtoDDbG-VVS-D-Dst0b_tree.root","XtoDDbG-VVS-D-Dst0b_tree_friend.root",100000)'
hadd -f hadd_XtoDDbG-VVS-S_tree_friend.root XtoDDbG-VVS-S-Dst0_tree_friend.root XtoDDbG-VVS-S-Dst0b_tree_friend.root
hadd -f hadd_XtoDDbG-VVS-D_tree_friend.root XtoDDbG-VVS-D-Dst0_tree_friend.root XtoDDbG-VVS-D-Dst0b_tree_friend.root
hadd -f hadd_XtoDDbG-VVS_tree_friend.root hadd_XtoDDbG-VVS-S_tree_friend.root hadd_XtoDDbG-VVS-D_tree_friend.root


