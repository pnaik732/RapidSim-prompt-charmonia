root -b -l -q 'makePlots.C("XtoDDbG_tree.root","RapidSim_XtoDDbG_PHSP_plots.pdf")' > output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbG-VVS-S-Dst0_tree.root","RapidSim_XtoDDbG-VVS-S-Dst0_plots.pdf")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbG-VVS-S-Dst0b_tree.root","RapidSim_XtoDDbG-VVS-S-Dst0b_plots.pdf")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbG-VVS-D-Dst0_tree.root","RapidSim_XtoDDbG-VVS-D-Dst0_plots.pdf")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbG-VVS-D-Dst0b_tree.root","RapidSim_XtoDDbG-VVS-D-Dst0b_plots.pdf")' >> output_makePlots.txt
# combined samples
root -b -l -q 'makePlots.C("XtoDDbG-VVS-S-Dst0_tree.root","RapidSim_XtoDDbG-VVS-S_plots.pdf","XtoDDbG-VVS-S-Dst0b_tree.root")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbG-VVS-D-Dst0_tree.root","RapidSim_XtoDDbG-VVS-D_plots.pdf","XtoDDbG-VVS-D-Dst0b_tree.root")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbG-VVS-S-Dst0_tree.root","RapidSim_XtoDDbG-VVS_plots.pdf","XtoDDbG-VVS-S-Dst0b_tree.root","XtoDDbG-VVS-D-Dst0_tree.root","XtoDDbG-VVS-D-Dst0b_tree.root")' >> output_makePlots.txt

