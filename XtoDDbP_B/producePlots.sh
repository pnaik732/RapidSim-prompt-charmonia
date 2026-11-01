root -b -l -q 'makePlots.C("XtoDDbP_B_tree.root","RapidSim_XtoDDbP_B_PHSP_plots.pdf")' > output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbP_B-model-S_tree.root","RapidSim_XtoDDbP_B_Model_S_plots.pdf")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbP_B-model-D_tree.root","RapidSim_XtoDDbP_B_Model_D_plots.pdf")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbP_B-VVS-S-Dst0_tree.root","RapidSim_XtoDDbP_B-VVS-S-Dst0_plots.pdf")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbP_B-VVS-S-Dst0b_tree.root","RapidSim_XtoDDbP_B-VVS-S-Dst0b_plots.pdf")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbP_B-VVS-D-Dst0_tree.root","RapidSim_XtoDDbP_B-VVS-D-Dst0_plots.pdf")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbP_B-VVS-D-Dst0b_tree.root","RapidSim_XtoDDbP_B-VVS-D-Dst0b_plots.pdf")' >> output_makePlots.txt
# combined samples
root -b -l -q 'makePlots.C("XtoDDbP_B-model-S_tree.root","RapidSim_XtoDDbP_B_Model_plots.pdf","XtoDDbP_B-model-D_tree.root")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbP_B-VVS-S-Dst0_tree.root","RapidSim_XtoDDbP_B-VVS-S_plots.pdf","XtoDDbP_B-VVS-S-Dst0b_tree.root")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbP_B-VVS-D-Dst0_tree.root","RapidSim_XtoDDbP_B-VVS-D_plots.pdf","XtoDDbP_B-VVS-D-Dst0b_tree.root")' >> output_makePlots.txt
root -b -l -q 'makePlots.C("XtoDDbP_B-VVS-S-Dst0_tree.root","RapidSim_XtoDDbP_B-VVS_plots.pdf","XtoDDbP_B-VVS-S-Dst0b_tree.root","XtoDDbP_B-VVS-D-Dst0_tree.root","XtoDDbP_B-VVS-D-Dst0b_tree.root")' >> output_makePlots.txt
