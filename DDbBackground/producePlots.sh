# make all plots only if a parameter (any parameter) is passed
if [ -n "$1" ]
then
  #root -b -l -q 'makePlots.C("/Users/pnaik/cernbox/Xstuff/DDbBackground_tree.root","RapidSim_DDbBackground_plots.pdf")'
  root -b -l -q 'makePlots.C("DDbBackground_01_tree.root","RapidSim_DDbBackground_01_plots.pdf")' > output_makePlots.txt
fi

root -b -l -q 'makePlots_Friend.C("hadd_DDbBackground_tree_friend.root","RapidSim_DDbBackground_plots_Friend.pdf")' > output_makePlots_Friend.txt
root -b -l -q 'makePlots_Friend.C("hadd_DDbBackgroundMore_tree_friend.root","RapidSim_DDbBackgroundMore_plots_Friend.pdf")' >> output_makePlots_Friend.txt
#root -b -l -q 'makePlots_Friend.C("DDbBackground_01_tree_friend.root","RapidSim_DDbBackground_01_plots_Friend.pdf")'
