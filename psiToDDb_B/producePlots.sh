# make all plots only if a parameter (any parameter) is passed
if [ -n "$1" ]
then
  root -b -l -q 'makePlots.C("psiToDDb_B_tree.root","RapidSim_psiToDDb_B_VSS_plots.pdf")' > output_makePlots.txt
fi

root -b -l -q 'makePlots_Friend.C("psiToDDb_B_tree_friend.root","RapidSim_psiToDDb_B_VSS_plots_Friend.pdf")' > output_makePlots_Friend.txt
