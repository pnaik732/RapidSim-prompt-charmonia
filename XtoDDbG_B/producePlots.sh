root -b -l -q 'makePlots.C("XtoDDbG_B_tree.root","RapidSim_XtoDDbG_B_PHSP_plots.pdf")' > output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbG_B-VVS-S-Dst0_tree.root","RapidSim_XtoDDbG_B-VVS-S-Dst0_plots.pdf")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbG_B-VVS-S-Dst0b_tree.root","RapidSim_XtoDDbG_B-VVS-S-Dst0b_plots.pdf")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbG_B-VVS-D-Dst0_tree.root","RapidSim_XtoDDbG_B-VVS-D-Dst0_plots.pdf")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbG_B-VVS-D-Dst0b_tree.root","RapidSim_XtoDDbG_B-VVS-D-Dst0b_plots.pdf")' >> output_makePlots.txt
# combined samples
root -b -l -q 'makePlots.C("XtoDDbG_B-VVS-S-Dst0_tree.root","RapidSim_XtoDDbG_B-VVS-S_plots.pdf","XtoDDbG_B-VVS-S-Dst0b_tree.root")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbG_B-VVS-D-Dst0_tree.root","RapidSim_XtoDDbG_B-VVS-D_plots.pdf","XtoDDbG_B-VVS-D-Dst0b_tree.root")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbG_B-VVS-S-Dst0_tree.root","RapidSim_XtoDDbG_B-VVS_plots.pdf","XtoDDbG_B-VVS-S-Dst0b_tree.root","XtoDDbG_B-VVS-D-Dst0_tree.root","XtoDDbG_B-VVS-D-Dst0b_tree.root")' >> output_makePlots.txt
