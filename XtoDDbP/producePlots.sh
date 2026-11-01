root -b -l -q 'makePlots.C("XtoDDbP_tree.root","RapidSim_XtoDDbP_PHSP_plots.pdf")' > output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbP-model-S_tree.root","RapidSim_XtoDDbP_Model_S_plots.pdf")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbP-model-D_tree.root","RapidSim_XtoDDbP_Model_D_plots.pdf")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbP-VVS-S-Dst0_tree.root","RapidSim_XtoDDbP-VVS-S-Dst0_plots.pdf")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbP-VVS-S-Dst0b_tree.root","RapidSim_XtoDDbP-VVS-S-Dst0b_plots.pdf")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbP-VVS-D-Dst0_tree.root","RapidSim_XtoDDbP-VVS-D-Dst0_plots.pdf")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbP-VVS-D-Dst0b_tree.root","RapidSim_XtoDDbP-VVS-D-Dst0b_plots.pdf")' >> output_makePlots.txt
# combined samples
root -b -l -q 'makePlots.C("XtoDDbP-model-S_tree.root","RapidSim_XtoDDbP_Model_plots.pdf","XtoDDbP-model-D_tree.root")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbP-VVS-S-Dst0_tree.root","RapidSim_XtoDDbP-VVS-S_plots.pdf","XtoDDbP-VVS-S-Dst0b_tree.root")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbP-VVS-D-Dst0_tree.root","RapidSim_XtoDDbP-VVS-D_plots.pdf","XtoDDbP-VVS-D-Dst0b_tree.root")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbP-VVS-S-Dst0_tree.root","RapidSim_XtoDDbP-VVS_plots.pdf","XtoDDbP-VVS-S-Dst0b_tree.root","XtoDDbP-VVS-D-Dst0_tree.root","XtoDDbP-VVS-D-Dst0b_tree.root")' >> output_makePlots.txt
