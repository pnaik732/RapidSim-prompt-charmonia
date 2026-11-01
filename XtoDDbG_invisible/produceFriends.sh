root -b -l -q 'makeFriend.C("XtoDDbG_invisible_tree.root","XtoDDbG_invisible_tree_friend.root",200000)'
root -b -l -q 'makeFriend.C("XtoDDbG_invisible-VVS-S-Dst0_tree.root","XtoDDbG_invisible-VVS-S-Dst0_tree_friend.root",100000)'
root -b -l -q 'makeFriend.C("XtoDDbG_invisible-VVS-S-Dst0b_tree.root","XtoDDbG_invisible-VVS-S-Dst0b_tree_friend.root",100000)'
root -b -l -q 'makeFriend.C("XtoDDbG_invisible-VVS-D-Dst0_tree.root","XtoDDbG_invisible-VVS-D-Dst0_tree_friend.root",100000)'
root -b -l -q 'makeFriend.C("XtoDDbG_invisible-VVS-D-Dst0b_tree.root","XtoDDbG_invisible-VVS-D-Dst0b_tree_friend.root",100000)'
hadd -f hadd_XtoDDbG_invisible-VVS-S_tree_friend.root XtoDDbG_invisible-VVS-S-Dst0_tree_friend.root XtoDDbG_invisible-VVS-S-Dst0b_tree_friend.root
hadd -f hadd_XtoDDbG_invisible-VVS-D_tree_friend.root XtoDDbG_invisible-VVS-D-Dst0_tree_friend.root XtoDDbG_invisible-VVS-D-Dst0b_tree_friend.root
hadd -f hadd_XtoDDbG_invisible-VVS_tree_friend.root hadd_XtoDDbG_invisible-VVS-S_tree_friend.root hadd_XtoDDbG_invisible-VVS-D_tree_friend.root


