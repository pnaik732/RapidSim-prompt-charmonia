# make all plots only if a parameter (any parameter) is passed
if [ -n "$1" ]
then
  root -b -l -q 'makePlots.C("XtoDDbG_B_invisible_tree.root","RapidSim_XtoDDbG_B_invisible_PHSP_plots.pdf")' > output_makePlots.txt
  root -b -l -q 'makePlots.C("XtoDDbG_B_invisible-VVS-S-Dst0_tree.root","RapidSim_XtoDDbG_B_invisible-VVS-S-Dst0_plots.pdf")' >> output_makePlots.txt
  root -b -l -q 'makePlots.C("XtoDDbG_B_invisible-VVS-S-Dst0b_tree.root","RapidSim_XtoDDbG_B_invisible-VVS-S-Dst0b_plots.pdf")' >> output_makePlots.txt
  root -b -l -q 'makePlots.C("XtoDDbG_B_invisible-VVS-D-Dst0_tree.root","RapidSim_XtoDDbG_B_invisible-VVS-D-Dst0_plots.pdf")' >> output_makePlots.txt
  root -b -l -q 'makePlots.C("XtoDDbG_B_invisible-VVS-D-Dst0b_tree.root","RapidSim_XtoDDbG_B_invisible-VVS-D-Dst0b_plots.pdf")' >> output_makePlots.txt
fi
# friend plots
root -b -l -q 'makePlots_Friend.C("XtoDDbG_B_invisible_tree_friend.root","RapidSim_XtoDDbG_B_invisible_PHSP_plots_Friend.pdf")' > output_makePlots_Friend.txt
root -b -l -q 'makePlots_Friend.C("XtoDDbG_B_invisible-VVS-S-Dst0_tree_friend.root","RapidSim_XtoDDbG_B_invisible-VVS-S-Dst0_plots_Friend.pdf")' >> output_makePlots_Friend.txt
root -b -l -q 'makePlots_Friend.C("XtoDDbG_B_invisible-VVS-D-Dst0_tree_friend.root","RapidSim_XtoDDbG_B_invisible-VVS-D-Dst0_plots_Friend.pdf")' >> output_makePlots_Friend.txt
root -b -l -q 'makePlots_Friend.C("XtoDDbG_B_invisible-VVS-S-Dst0b_tree_friend.root","RapidSim_XtoDDbG_B_invisible-VVS-S-Dst0b_plots_Friend.pdf")' >> output_makePlots_Friend.txt
root -b -l -q 'makePlots_Friend.C("XtoDDbG_B_invisible-VVS-D-Dst0b_tree_friend.root","RapidSim_XtoDDbG_B_invisible-VVS-D-Dst0b_plots_Friend.pdf")' >> output_makePlots_Friend.txt
# combined friend plots
root -b -l -q 'makePlots_Friend.C("hadd_XtoDDbG_B_invisible-VVS_tree_friend.root","RapidSim_XtoDDbG_B_invisible-VVS_plots_Friend.pdf")' >> output_makePlots_Friend.txt
root -b -l -q 'makePlots_Friend.C("hadd_XtoDDbG_B_invisible-VVS-S_tree_friend.root","RapidSim_XtoDDbG_B_invisible-VVS-S_plots_Friend.pdf")' >> output_makePlots_Friend.txt
root -b -l -q 'makePlots_Friend.C("hadd_XtoDDbG_B_invisible-VVS-D_tree_friend.root","RapidSim_XtoDDbG_B_invisible-VVS-D_plots_Friend.pdf")' >> output_makePlots_Friend.txt

