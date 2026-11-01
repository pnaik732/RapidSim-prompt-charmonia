root -b -l -q 'makeFriend.C("XtoDDbP_B_tree.root","XtoDDbP_B_tree_friend.root",200000)'
root -b -l -q 'makeFriend.C("XtoDDbP_B-VVS-S-Dst0_tree.root","XtoDDbP_B-VVS-S-Dst0_tree_friend.root",100000)'
root -b -l -q 'makeFriend.C("XtoDDbP_B-VVS-S-Dst0b_tree.root","XtoDDbP_B-VVS-S-Dst0b_tree_friend.root",100000)'
root -b -l -q 'makeFriend.C("XtoDDbP_B-VVS-D-Dst0_tree.root","XtoDDbP_B-VVS-D-Dst0_tree_friend.root",100000)'
root -b -l -q 'makeFriend.C("XtoDDbP_B-VVS-D-Dst0b_tree.root","XtoDDbP_B-VVS-D-Dst0b_tree_friend.root",100000)'
root -b -l -q 'makeFriend.C("XtoDDbP_B-model-S_tree.root","XtoDDbP_B-model-S_tree_friend.root",200000)'
root -b -l -q 'makeFriend.C("XtoDDbP_B-model-D_tree.root","XtoDDbP_B-model-D_tree_friend.root",200000)'
hadd -f hadd_XtoDDbP_B-VVS-S_tree_friend.root XtoDDbP_B-VVS-S-Dst0_tree_friend.root XtoDDbP_B-VVS-S-Dst0b_tree_friend.root
hadd -f hadd_XtoDDbP_B-VVS-D_tree_friend.root XtoDDbP_B-VVS-D-Dst0_tree_friend.root XtoDDbP_B-VVS-D-Dst0b_tree_friend.root
hadd -f hadd_XtoDDbP_B-VVS_tree_friend.root hadd_XtoDDbP_B-VVS-S_tree_friend.root hadd_XtoDDbP_B-VVS-D_tree_friend.root
hadd -f hadd_XtoDDbP_B-model_tree_friend.root XtoDDbP_B-model-S_tree_friend.root XtoDDbP_B-model-D_tree_friend.root


