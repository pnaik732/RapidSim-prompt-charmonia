#root -b -l -q 'makeFriend.C("XtoDDbP_invisible_tree.root","XtoDDbP_invisible_tree_friend.root",200000)'
root -b -l -q 'makeFriend.C("XtoDDbP_invisible-VVS-S-Dst0_tree.root","XtoDDbP_invisible-VVS-S-Dst0_tree_friend.root",100000)'
root -b -l -q 'makeFriend.C("XtoDDbP_invisible-VVS-S-Dst0b_tree.root","XtoDDbP_invisible-VVS-S-Dst0b_tree_friend.root",100000)'
#root -b -l -q 'makeFriend.C("XtoDDbP_invisible-VVS-D-Dst0_tree.root","XtoDDbP_invisible-VVS-D-Dst0_tree_friend.root",100000)'
#root -b -l -q 'makeFriend.C("XtoDDbP_invisible-VVS-D-Dst0b_tree.root","XtoDDbP_invisible-VVS-D-Dst0b_tree_friend.root",100000)'
#root -b -l -q 'makeFriend.C("XtoDDbP_invisible-model-S_tree.root","XtoDDbP_invisible-model-S_tree_friend.root",200000)'
#root -b -l -q 'makeFriend.C("XtoDDbP_invisible-model-D_tree.root","XtoDDbP_invisible-model-D_tree_friend.root",200000)'
hadd -f hadd_XtoDDbP_invisible-VVS-S_tree_friend.root XtoDDbP_invisible-VVS-S-Dst0_tree_friend.root XtoDDbP_invisible-VVS-S-Dst0b_tree_friend.root
#hadd -f hadd_XtoDDbP_invisible-VVS-D_tree_friend.root XtoDDbP_invisible-VVS-D-Dst0_tree_friend.root XtoDDbP_invisible-VVS-D-Dst0b_tree_friend.root
#hadd -f hadd_XtoDDbP_invisible-VVS_tree_friend.root hadd_XtoDDbP_invisible-VVS-S_tree_friend.root hadd_XtoDDbP_invisible-VVS-D_tree_friend.root
#hadd -f hadd_XtoDDbP_invisible-model_tree_friend.root XtoDDbP_invisible-model-S_tree_friend.root XtoDDbP_invisible-model-D_tree_friend.root


