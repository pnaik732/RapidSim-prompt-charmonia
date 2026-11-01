# make all plots only if a parameter (any parameter) is passed
if [ -n "$1" ]
then
  root -b -l -q 'makePlots.C("XtoDDbP_invisible_tree.root","RapidSim_XtoDDbP_invisible_PHSP_plots.pdf")' > output_makePlots.txt
  root -b -l -q 'makePlots.C("XtoDDbP_invisible-model-S_tree.root","RapidSim_XtoDDbP_invisible_Model_S_plots.pdf")' >> output_makePlots.txt
  root -b -l -q 'makePlots.C("XtoDDbP_invisible-model-D_tree.root","RapidSim_XtoDDbP_invisible_Model_D_plots.pdf")' >> output_makePlots.txt
  root -b -l -q 'makePlots.C("XtoDDbP_invisible-VVS-S-Dst0_tree.root","RapidSim_XtoDDbP_invisible-VVS-S-Dst0_plots.pdf")' >> output_makePlots.txt
  root -b -l -q 'makePlots.C("XtoDDbP_invisible-VVS-S-Dst0b_tree.root","RapidSim_XtoDDbP_invisible-VVS-S-Dst0b_plots.pdf")' >> output_makePlots.txt
  root -b -l -q 'makePlots.C("XtoDDbP_invisible-VVS-D-Dst0_tree.root","RapidSim_XtoDDbP_invisible-VVS-D-Dst0_plots.pdf")' >> output_makePlots.txt
  root -b -l -q 'makePlots.C("XtoDDbP_invisible-VVS-D-Dst0b_tree.root","RapidSim_XtoDDbP_invisible-VVS-D-Dst0b_plots.pdf")' >> output_makePlots.txt
fi
# friend plots
root -b -l -q 'makePlots_Friend.C("XtoDDbP_invisible_tree_friend.root","RapidSim_XtoDDbP_invisible_PHSP_plots_Friend.pdf")' > output_makePlots_Friend.txt
root -b -l -q 'makePlots_Friend.C("XtoDDbP_invisible-model-S_tree_friend.root","RapidSim_XtoDDbP_invisible_Model_S_plots_Friend.pdf")' >> output_makePlots_Friend.txt
root -b -l -q 'makePlots_Friend.C("XtoDDbP_invisible-model-D_tree_friend.root","RapidSim_XtoDDbP_invisible_Model_D_plots_Friend.pdf")' >> output_makePlots_Friend.txt
root -b -l -q 'makePlots_Friend.C("XtoDDbP_invisible-VVS-S-Dst0_tree_friend.root","RapidSim_XtoDDbP_invisible-VVS-S-Dst0_plots_Friend.pdf")' >> output_makePlots_Friend.txt
root -b -l -q 'makePlots_Friend.C("XtoDDbP_invisible-VVS-D-Dst0_tree_friend.root","RapidSim_XtoDDbP_invisible-VVS-D-Dst0_plots_Friend.pdf")' >> output_makePlots_Friend.txt
root -b -l -q 'makePlots_Friend.C("XtoDDbP_invisible-VVS-S-Dst0b_tree_friend.root","RapidSim_XtoDDbP_invisible-VVS-S-Dst0b_plots_Friend.pdf")' >> output_makePlots_Friend.txt
root -b -l -q 'makePlots_Friend.C("XtoDDbP_invisible-VVS-D-Dst0b_tree_friend.root","RapidSim_XtoDDbP_invisible-VVS-D-Dst0b_plots_Friend.pdf")' >> output_makePlots_Friend.txt
# combined friend plots
root -b -l -q 'makePlots_Friend.C("hadd_XtoDDbP_invisible-VVS_tree_friend.root","RapidSim_XtoDDbP_invisible-VVS_plots_Friend.pdf")' >> output_makePlots_Friend.txt
root -b -l -q 'makePlots_Friend.C("hadd_XtoDDbP_invisible-model_tree_friend.root","RapidSim_XtoDDbP_invisible-Model_plots_Friend.pdf")' >> output_makePlots_Friend.txt
root -b -l -q 'makePlots_Friend.C("hadd_XtoDDbP_invisible-VVS-S_tree_friend.root","RapidSim_XtoDDbP_invisible-VVS-S_plots_Friend.pdf")' >> output_makePlots_Friend.txt
root -b -l -q 'makePlots_Friend.C("hadd_XtoDDbP_invisible-VVS-D_tree_friend.root","RapidSim_XtoDDbP_invisible-VVS-D_plots_Friend.pdf")' >> output_makePlots_Friend.txt

