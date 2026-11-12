# RapidSim-prompt-charmonia

Code used to generate D0 anti-D0 decays coming from prompt psi(3770) and chi_c1(3872) states in RapidSim (LHCb pseudo-detector simulation), from 14 TeV pp collisions.

The code was used in the paper: <br>
"Novel correlated D0 anti-D0 systems for c/b physics and tests of T/CPT" <br>
JHEP 03 (2023) 038 <br>
https://doi.org/10.1007/JHEP03%282023%29038 <br>
arXiv:2102.07729 [hep-ph] <br>
https://doi.org/10.48550/arXiv.2102.07729 

I used RapidSim to generate these decays (unfortunately it is hard to tell exactly which version, as the CMakeLists.txt file continues to say 1.4.0 even though the version numbers have since advanced). However I changed src/RapidParticleData.cc and src/RapidParticleData.h to allow for a Uniform (UNI) D0 anti-D0 distribution to be produced, and I changed config/particles.dat to setup the X(3872) and psi(3770) and UNI particle parameters. I also added a ROOT file with a new pT and pseudorapidity histogram for prompt charmonia. For near-threshold charmonia the decay dictates, that in the measurement frame, the particles in the D0 anti-D0 system will move approximately colinearly; thus the new ROOT file was generated using doubler.C which took the included FONLL charmed meson transverse momentum and pseudorapidity distributions, and simply extended them to represent low-mass charmonium by simply doubling the transverse momenta generated, while maintaining the pseudorapidity (LHCbx14.root). These changed and new files have been uploaded to this git repository (in the RapidSim directory), and are needed to generate RapidSim MC using the decay and config files provided in the psi*, X*, and DDbBackground directories.

The X(3872) to D0 anti-D0 pi0 decay model used in the paper, and files used to test the model, can be found in the EvtGen directory of the repository. I used EvtGen R01-07-00.

All output .root and .pdf files after running RapidSim and/or EvtGen have been removed to limit the size of this git repository. However log files still remain.

RapidSim page: https://github.com/lhcb/RapidSim <br>
EvtGen page (if needed, now "included" with RapidSim): https://evtgen.hepforge.org/
