// XtoD0D0bar0pi0.cpp
// Paras Naik with assistance from Jeremy Dalseno 

#include <iostream>

#include "TCanvas.h"
#include "TFile.h"
#include "TH2D.h"
#include "TTree.h"
#include "TPaveStats.h"
//#include "TVector3.h"

#include "EvtGen/EvtGen.hh"

#include "EvtGenBase/EvtMTRandomEngine.hh"
#include "EvtGenBase/EvtParticle.hh"
#include "EvtGenBase/EvtParticleFactory.hh"
#include "EvtGenBase/EvtRandom.hh"
#include "EvtGenBase/EvtRandomEngine.hh"
#include "EvtGenBase/EvtSimpleRandomEngine.hh"
#include "EvtGenBase/EvtVector4R.hh"
#include "EvtGenBase/EvtComplex.hh"

int main()
{
  // Define the random number generator
  EvtRandomEngine* myRandomEngine = 0;

#ifdef EVTGEN_CPP11
  // Use the Mersenne-Twister generator (C++11 only)
  myRandomEngine = new EvtMTRandomEngine();
  std::cout << "C++11 detected. Mersenne-Twister generator now activated. " << std::endl;
#else
  myRandomEngine = new EvtSimpleRandomEngine();
#endif

  EvtRandom::setRandomEngine(myRandomEngine);

  EvtGen myGenerator("XtoD0Dbar0pi0.dec", "/Users/pnaik/work/EvtGen/EvtGen/evtgen/evt.pdl",
		     myRandomEngine);

  // Relevant lines in my evt.pdl ... you may wish to change these parameters in your evt.pdl
  // width from PDG
  // add  p Particle  X_1(3872)                    9920443  3.8716900e+00  1.2000000e-03  0.0000000e+00     0     2  0.0000000e+00    9920443
  // width from Voloshin 2003 paper
  // add  p Particle  anti-D*0                        -423  2.0068500e+00  4.3000000e-05  0.0000000e+00     0     2  0.0000000e+00       -423
  // add  p Particle  D*0                              423  2.0068500e+00  4.3000000e-05  0.0000000e+00     0     2  0.0000000e+00        423

  // Set up the parent particle [decay via Model]
  const EvtId theId = EvtPDL::getId("B+");
//  const EvtId theId = EvtPDL::getId("X_1(3872)");
  const double mass = EvtPDL::getMeanMass(theId);
  //  const EvtVector4R pInit(EvtPDL::getMass(theId), 0.0, 0.0, 0.0); // Generates a mass according to a simple non-relativistic Breit-Wigner shape.
  const EvtVector4R pInit(mass, 0.0, 0.0, 0.0); // Returns the nominal mass.
  std::cout << "theID: " << theId << "   " << "mass: " << mass << std::endl;

  // Set up the parent particle [decay to PHSP only, for projections]
  const EvtId theId_PHSP = EvtPDL::getId("myX_1(3872)"); // Paras made this clone particle and put it into evt.pdl
  const double mass_PHSP = EvtPDL::getMeanMass(theId_PHSP);
  std::cout << "theID_PHSP: " << theId_PHSP << "   " << "mass_PHSP: " << mass_PHSP << std::endl;
  //  const EvtVector4R pInit(EvtPDL::getMass(theId), 0.0, 0.0, 0.0); // Generates a mass according to a simple non-relativistic Breit-Wigner shape.
  const EvtVector4R pInit_PHSP(mass_PHSP, 0.0, 0.0, 0.0); // Returns the nominal mass.

  TFile* const rootfile = new TFile("XtoD0Dbar0pi0.root", "RECREATE");
  TTree* const roottree = new TTree("XtoD0Dbar0pi0", "");
  TTree* const roottree2 = new TTree("X_PHSP", "");

  // angle between a and b in the X rest frame
  double CosTh_D0D0B_restX, CosTh_D0pi0_restX, CosTh_D0Bpi0_restX; 
  // DIFFERENT! angle between a and c in the ab rest frame (i.e. the helicity angle for ab resonance)
  double CosTh_D0D0Bres_helicity, CosTh_D0pi0res_helicity, CosTh_D0Bpi0res_helicity; 

  double pmag_D0, pmag_pi0, pmag_D0B; // B rest frame
  double pmag_D0_restX, pmag_pi0_restX, pmag_D0B_restX; // X rest frame
  double s_D0pi0, s_D0Bpi0, s_D0D0B; // invariant mass-squared
  int matchCode;
  double weight;

  double px_X, py_X, pz_X, E_X; // B rest frame
  double px_D0, py_D0, pz_D0, E_D0;
  double px_pi0, py_pi0, pz_pi0, E_pi0;
  double px_D0B, py_D0B, pz_D0B, E_D0B;
  double px_D0_restX, py_D0_restX, pz_D0_restX, E_D0_restX; // X rest frame
  double px_pi0_restX, py_pi0_restX, pz_pi0_restX, E_pi0_restX;
  double px_D0B_restX, py_D0B_restX, pz_D0B_restX, E_D0B_restX;
  double Delta_E; // = m_X - (E_D0 + E_D0B)  in the X rest frame
  double Delta_m; // = m_X - m_D0D0B  invariant

  double s_D0pi0_2, s_D0Bpi0_2, s_D0D0B_2; // for "PHSP" part

  roottree->Branch("px_X", &px_X);
  roottree->Branch("py_X", &py_X);
  roottree->Branch("pz_X", &pz_X);
  roottree->Branch("E_X",  &E_X);

  roottree->Branch("px_D0", &px_D0);
  roottree->Branch("py_D0", &py_D0);
  roottree->Branch("pz_D0", &pz_D0);
  roottree->Branch("E_D0",  &E_D0);

  roottree->Branch("px_pi0", &px_pi0);
  roottree->Branch("py_pi0", &py_pi0);
  roottree->Branch("pz_pi0", &pz_pi0);
  roottree->Branch("E_pi0",  &E_pi0);

  roottree->Branch("px_D0B", &px_D0B);
  roottree->Branch("py_D0B", &py_D0B);
  roottree->Branch("pz_D0B", &pz_D0B);
  roottree->Branch("E_D0B",  &E_D0B);

  roottree->Branch("px_D0_restX", &px_D0_restX);
  roottree->Branch("py_D0_restX", &py_D0_restX);
  roottree->Branch("pz_D0_restX", &pz_D0_restX);
  roottree->Branch("E_D0_restX",  &E_D0_restX);

  roottree->Branch("px_pi0_restX", &px_pi0_restX);
  roottree->Branch("py_pi0_restX", &py_pi0_restX);
  roottree->Branch("pz_pi0_restX", &pz_pi0_restX);
  roottree->Branch("E_pi0_restX",  &E_pi0_restX);

  roottree->Branch("px_D0B_restX", &px_D0B_restX);
  roottree->Branch("py_D0B_restX", &py_D0B_restX);
  roottree->Branch("pz_D0B_restX", &pz_D0B_restX);
  roottree->Branch("E_D0B_restX",  &E_D0B_restX);

  roottree->Branch("pmag_D0", &pmag_D0);
  roottree->Branch("pmag_pi0", &pmag_pi0);
  roottree->Branch("pmag_D0B", &pmag_D0B);

  roottree->Branch("pmag_D0_restX", &pmag_D0_restX);
  roottree->Branch("pmag_pi0_restX", &pmag_pi0_restX);
  roottree->Branch("pmag_D0B_restX", &pmag_D0B_restX);

  roottree->Branch("s_D0pi0", &s_D0pi0);
  roottree->Branch("s_D0Bpi0", &s_D0Bpi0);
  roottree->Branch("s_D0D0B", &s_D0D0B);

  roottree->Branch("CosTh_D0D0B_restX", &CosTh_D0D0B_restX);
  roottree->Branch("CosTh_D0pi0_restX", &CosTh_D0pi0_restX);
  roottree->Branch("CosTh_D0Bpi0_restX", &CosTh_D0Bpi0_restX);

  roottree->Branch("CosTh_D0D0Bres_helicity", &CosTh_D0D0Bres_helicity);
  roottree->Branch("CosTh_D0pi0res_helicity", &CosTh_D0pi0res_helicity);
  roottree->Branch("CosTh_D0Bpi0res_helicity", &CosTh_D0Bpi0res_helicity);

  roottree->Branch("Delta_E",&Delta_E);
  roottree->Branch("Delta_m",&Delta_m);

  roottree->Branch("matchCode", &matchCode);

  roottree2->Branch("s_D0pi0_PHSP", &s_D0pi0_2);
  roottree2->Branch("s_D0Bpi0_PHSP", &s_D0Bpi0_2);
  roottree2->Branch("s_D0D0B_PHSP", &s_D0D0B_2);

  roottree2->Branch("weight", &weight);

  int m=5;
  TH1** h_DalitzPlot = new TH1*[m];
  TH1** h_DalitzPlotE = new TH1*[m];
  TH1** h_DalitzPlot2 = new TH1*[m];
  TH1** h_cosangleD0D0B = new TH1*[m]; // X rest frame
  TH1** h_cosangleD0pi0 = new TH1*[m];
  TH1** h_cosangleD0Bpi0 = new TH1*[m];
  TH1** h_pmag_D0_restX = new TH1*[m];
  TH1** h_pmag_D0B_restX = new TH1*[m];
  TH1** h_pmag_pi0_restX = new TH1*[m];

  // Generate the events [PHSP]

  clock_t tStart_PHSP = clock();
  const unsigned int nevents_PHSP = 16000;
  for( unsigned int i=0; i<nevents_PHSP; ++i )
  {
	EvtParticle* const baseParticle_PHSP = EvtParticleFactory::particleFactory(theId_PHSP, pInit_PHSP);
	myGenerator.generateDecay(baseParticle_PHSP);
    EvtVector4R p_D0_PHSP;
    EvtVector4R p_pi0_PHSP;
    EvtVector4R p_D0B_PHSP;
    p_D0_PHSP  = baseParticle_PHSP->getDaug(0)->getP4Lab();
    p_pi0_PHSP = baseParticle_PHSP->getDaug(1)->getP4Lab();
    p_D0B_PHSP = baseParticle_PHSP->getDaug(2)->getP4Lab();
    double M_Dst0 = 2.00685;
    EvtComplex sqrt_of_minus_1(0,1);
    double Gamma_Dst0antiD0 = 0.0021;
    EvtComplex Amp = 1 / (M_Dst0*M_Dst0 - (p_pi0_PHSP+p_D0_PHSP).mass2() - sqrt_of_minus_1*M_Dst0*Gamma_Dst0antiD0);
    double Amp2 = abs2(Amp);
    s_D0pi0_2 = (p_pi0_PHSP+p_D0_PHSP).mass2();
    s_D0D0B_2 = (p_D0B_PHSP+p_D0_PHSP).mass2();
    s_D0Bpi0_2 = (p_pi0_PHSP+p_D0_PHSP).mass2();
    weight = Amp2;
    roottree2->Fill();
  }
  printf("Time taken to generate events: %.2fs\n", (double)(clock() - tStart_PHSP)/CLOCKS_PER_SEC);

  // Generate the events [Model]

  clock_t tStart = clock();

  const long unsigned int nevents = 320000;
  long unsigned int D0count = 0;
  long unsigned int Dst0count = 0;
  long unsigned int Dst0Bcount = 0;
  for( long unsigned int i=0; i<nevents; ++i )
  {
    if (i%(nevents/10) == 0) std::cout << i << " of " << nevents << " events generated" << std::endl;
    EvtParticle* const baseParticle = EvtParticleFactory::particleFactory(theId, pInit); // In this case, the B

    myGenerator.generateDecay(baseParticle);

    if (i%(nevents/10) == 0) std::cout << " event generated" << std::endl;

    bool matchD0 = (baseParticle->getDaug(0)->getDaug(0)->getName() == "D0");
    bool matchDst0 = (baseParticle->getDaug(0)->getDaug(0)->getName() == "D*0");
    bool matchDst0B = (baseParticle->getDaug(0)->getDaug(0)->getName() == "anti-D*0");

    bool matchGamma = ((baseParticle->getDaug(0)->getDaug(1)->getName() == "gamma") || (baseParticle->getDaug(0)->getDaug(0)->getDaug(1)->getName() == "gamma")  );

    EvtVector4R p_B;
    EvtVector4R p_X;
    EvtVector4R p_K;

    EvtVector4R p_D0; 
    EvtVector4R p_pi0;
    EvtVector4R p_D0B;

    EvtVector4R p_D0_restX;
    EvtVector4R p_pi0_restX;
    EvtVector4R p_D0B_restX;

    EvtVector4R p_Dst_restX;
    EvtVector4R p_D_restDst;
    EvtVector4R p_pi0_restDst;

    if (matchD0)
    {
      matchCode = 1;
      D0count++;
      p_B  = baseParticle->getP4Lab();
      p_K  = baseParticle->getDaug(1)->getP4Lab();
      p_X  = baseParticle->getDaug(0)->getP4Lab();
      p_D0  = baseParticle->getDaug(0)->getDaug(0)->getP4Lab();
      p_pi0 = baseParticle->getDaug(0)->getDaug(1)->getP4Lab();
      p_D0B = baseParticle->getDaug(0)->getDaug(2)->getP4Lab();

      p_D0_restX  = baseParticle->getDaug(0)->getDaug(0)->getP4();
      p_pi0_restX = baseParticle->getDaug(0)->getDaug(1)->getP4();
      p_D0B_restX = baseParticle->getDaug(0)->getDaug(2)->getP4();

      // Dummy
      p_Dst_restX   = baseParticle->getP4Lab();
      p_D_restDst   = baseParticle->getP4Lab();  
      p_pi0_restDst = baseParticle->getP4Lab();   
    }
    else if (matchDst0)
    {
      matchCode = 2;
      Dst0count++;
      p_B  = baseParticle->getP4Lab();
      p_K  = baseParticle->getDaug(1)->getP4Lab();
      p_X  = baseParticle->getDaug(0)->getP4Lab();
      p_D0  = baseParticle->getDaug(0)->getDaug(0)->getDaug(0)->getP4Lab();
      p_pi0 = baseParticle->getDaug(0)->getDaug(0)->getDaug(1)->getP4Lab();
      p_D0B = baseParticle->getDaug(0)->getDaug(1)->getP4Lab();

      p_Dst_restX = baseParticle->getDaug(0)->getDaug(0)->getP4();
      p_D0B_restX = baseParticle->getDaug(0)->getDaug(1)->getP4();

      p_D_restDst  = baseParticle->getDaug(0)->getDaug(0)->getDaug(0)->getP4();
      p_pi0_restDst = baseParticle->getDaug(0)->getDaug(0)->getDaug(1)->getP4();

      p_D0_restX = boostTo(p_D_restDst,p_Dst_restX);
      p_pi0_restX = boostTo(p_pi0_restDst,p_Dst_restX);
    }
    else if (matchDst0B)
    {
      matchCode = 3;
      Dst0Bcount++;
      p_B  = baseParticle->getP4Lab();
      p_K  = baseParticle->getDaug(1)->getP4Lab();
      p_X  = baseParticle->getDaug(0)->getP4Lab();
      p_D0  = baseParticle->getDaug(0)->getDaug(1)->getP4Lab();
      p_pi0 = baseParticle->getDaug(0)->getDaug(0)->getDaug(1)->getP4Lab();
      p_D0B = baseParticle->getDaug(0)->getDaug(0)->getDaug(0)->getP4Lab();

      p_D0_restX  = baseParticle->getDaug(0)->getDaug(1)->getP4();
      p_Dst_restX = baseParticle->getDaug(0)->getDaug(0)->getP4();

      p_pi0_restDst = baseParticle->getDaug(0)->getDaug(0)->getDaug(1)->getP4();
      p_D_restDst   = baseParticle->getDaug(0)->getDaug(0)->getDaug(0)->getP4();

      p_pi0_restX = boostTo(p_pi0_restDst,p_Dst_restX);
      p_D0B_restX = boostTo(p_D_restDst,p_Dst_restX);
    }
    else 
    {
      std::cerr << "Should not have ended up here." << std::endl;
    }

    if (i%(nevents/10) == 0) std::cout << " stage 2" << std::endl;

    px_D0  =  p_D0.get(1); // LAB
    py_D0  =  p_D0.get(2);
    pz_D0  =  p_D0.get(3);
    E_D0   =  p_D0.get(0);
    px_pi0 = p_pi0.get(1);
    py_pi0 = p_pi0.get(2);
    pz_pi0 = p_pi0.get(3);
    E_pi0  = p_pi0.get(0);
    px_D0B = p_D0B.get(1);
    py_D0B = p_D0B.get(2);
    pz_D0B = p_D0B.get(3);
    E_D0B  = p_D0B.get(0);
    px_X = p_X.get(1);
    py_X = p_X.get(2);
    pz_X = p_X.get(3);
    E_X  = p_X.get(0);
    px_D0_restX  =  p_D0_restX.get(1); // rest frame of the X
    py_D0_restX  =  p_D0_restX.get(2);
    pz_D0_restX  =  p_D0_restX.get(3);
    E_D0_restX   =  p_D0_restX.get(0);
    px_pi0_restX = p_pi0_restX.get(1);
    py_pi0_restX = p_pi0_restX.get(2);
    pz_pi0_restX = p_pi0_restX.get(3);
    E_pi0_restX  = p_pi0_restX.get(0);
    px_D0B_restX = p_D0B_restX.get(1);
    py_D0B_restX = p_D0B_restX.get(2);
    pz_D0B_restX = p_D0B_restX.get(3);
    E_D0B_restX  = p_D0B_restX.get(0);
    s_D0pi0  = (p_pi0+p_D0).mass2(); // invariant
    s_D0Bpi0 = (p_pi0+p_D0B).mass2();
    s_D0D0B  = (p_D0+p_D0B).mass2();
    pmag_D0  = p_D0.d3mag(); // LAB
    pmag_D0B = p_D0B.d3mag();
    pmag_pi0 = p_pi0.d3mag();
    pmag_D0_restX  = p_D0_restX.d3mag(); // rest frame of the X
    pmag_D0B_restX = p_D0B_restX.d3mag();
    pmag_pi0_restX = p_pi0_restX.d3mag();

    Delta_E = (p_X.mass() - (p_D0_restX.get(0) + p_D0B_restX.get(0))); // rest frame of the X
    Delta_m = (p_X.mass() - (p_D0 + p_D0B).mass()); // invariant

    CosTh_D0D0B_restX  = p_D0_restX.dot(p_D0B_restX)  / (pmag_D0_restX  * pmag_D0B_restX); // rest frame of the X
    CosTh_D0pi0_restX  = p_D0_restX.dot(p_pi0_restX)  / (pmag_D0_restX  * pmag_pi0_restX);
    CosTh_D0Bpi0_restX = p_D0B_restX.dot(p_pi0_restX) / (pmag_D0B_restX * pmag_pi0_restX);

    EvtVector4R boostD0D0B  = (p_D0_restX + p_D0B_restX);
    EvtVector4R p_D0_restD0D0B(p_D0_restX); 
    EvtVector4R p_D0B_restD0D0B(p_D0B_restX);
    EvtVector4R p_pi0_restD0D0B(p_pi0_restX);
    p_D0_restD0D0B.applyBoostTo(boostD0D0B,true);
    p_D0B_restD0D0B.applyBoostTo(boostD0D0B,true);    
    p_pi0_restD0D0B.applyBoostTo(boostD0D0B,true);   

    EvtVector4R boostD0pi0  = (p_D0_restX + p_pi0_restX);
    EvtVector4R p_D0_restD0pi0(p_D0_restX); 
    EvtVector4R p_D0B_restD0pi0(p_D0B_restX);
    EvtVector4R p_pi0_restD0pi0(p_pi0_restX);
    p_D0_restD0pi0.applyBoostTo(boostD0pi0,true);    
    p_D0B_restD0pi0.applyBoostTo(boostD0pi0,true);    
    p_pi0_restD0pi0.applyBoostTo(boostD0pi0,true);    

    EvtVector4R boostD0Bpi0 = (p_D0B_restX + p_pi0_restX);
    EvtVector4R p_D0_restD0Bpi0(p_D0_restX); 
    EvtVector4R p_D0B_restD0Bpi0(p_D0B_restX);
    EvtVector4R p_pi0_restD0Bpi0(p_pi0_restX);
    p_D0_restD0Bpi0.applyBoostTo(boostD0Bpi0,true);    
    p_D0B_restD0Bpi0.applyBoostTo(boostD0Bpi0,true);    
    p_pi0_restD0Bpi0.applyBoostTo(boostD0Bpi0,true);   

    CosTh_D0D0Bres_helicity  = p_D0_restD0D0B.dot(p_pi0_restD0D0B)   / (p_D0_restD0D0B.d3mag() * p_pi0_restD0D0B.d3mag() ); // helicity angles
    CosTh_D0pi0res_helicity  = p_pi0_restD0pi0.dot(p_D0B_restD0pi0)  / (p_pi0_restD0pi0.d3mag() * p_D0B_restD0pi0.d3mag());
    CosTh_D0Bpi0res_helicity = p_D0B_restD0Bpi0.dot(p_D0_restD0Bpi0) / (p_D0B_restD0Bpi0.d3mag() * p_D0_restD0Bpi0.d3mag());

    boostD0Bpi0.applyBoostTo(boostD0Bpi0,true);
    if (i%(nevents/10) == 0) std::cout << "This should be approx. the mass of the D*, and the zero momentum vector: " << boostD0Bpi0 << std::endl;

    if (i%(nevents/10) == 0) std::cout << " stage 3" << std::endl;

    if (nevents <= 50) // only make full printout for tiny samples
    {
      std::cout << "baseParticle->getDaug(0)->getDaug(0)->getName(): " << baseParticle->getDaug(0)->getDaug(0)->getName() ;
      std::cout << "  match D0: " << matchD0 ;
      std::cout << "  match D*0: " << matchDst0 ;
      std::cout << "  match anti-D*0: " << matchDst0B << std::endl;
      std::cout << "  cosangleD0D0B: " << CosTh_D0D0B_restX << std::endl;
    }

    if (D0count%100000 == 0 && D0count != 0) std::cout << "XtoD0Dbar0pi0.cpp: Events generated: " << D0count << std::endl;

    baseParticle->deleteTree();

    if (i%(nevents/10) == 0) std::cout << " stage 4" << std::endl;

    roottree->Fill();

    if (i%(nevents/10) == 0)  std::cout << "match" << matchGamma << std::endl;
    if (i%(nevents/10) == 0)  std::cout << "i" << i << std::endl;

    if (i == 0)
    {
		if (matchGamma)
		{
			  for (int ii=0; ii<m; ii++)
			  {
				h_DalitzPlot[ii] = new TH2D(TString::Format("h_DalitzPlot_%d", ii), "", 300, 3.435, 4.035, 300, 3.435, 4.035);
				h_DalitzPlotE[ii] = new TH2D(TString::Format("h_DalitzPlotE_%d", ii), "", 300, 3.932, 4.032, 300, 3.932, 4.032);
				h_DalitzPlot2[ii] = new TH2D(TString::Format("h_DalitzPlot2_%d", ii), "", 300, 3.435, 4.035, 280, 13.90, 15.00);
				h_cosangleD0D0B[ii] = new TH1D(TString::Format("h_cosangleD0D0B_%d", ii), "", 110, -1.1, 1.1);
				h_cosangleD0pi0[ii] = new TH1D(TString::Format("h_cosangleD0pi0_%d", ii), "", 110, -1.1, 1.1);
				h_cosangleD0Bpi0[ii] = new TH1D(TString::Format("h_cosangleD0Bpi0_%d", ii), "", 110, -1.1, 1.1);
				h_pmag_D0_restX[ii] = new TH1D(TString::Format("h_pmag_D0_restX_%d", ii), "", 130, 0, 0.130);
				h_pmag_D0B_restX[ii] = new TH1D(TString::Format("h_pmag_D0B_restX_%d", ii), "", 130, 0, 0.130);
				h_pmag_pi0_restX[ii] = new TH1D(TString::Format("h_pmag_pi0_restX_%d", ii), "", 150, 0, 0.060);
			  }
		}
		else
		{
			for (int ii=0; ii<m; ii++)
			{
				h_DalitzPlot[ii] = new TH2D(TString::Format("h_DalitzPlot_%d", ii), "", 300, 3.995, 4.035, 300, 3.995, 4.035);
				h_DalitzPlotE[ii] = new TH2D(TString::Format("h_DalitzPlotE_%d", ii), "", 300, 4.017, 4.032, 300, 4.017, 4.032);
				h_DalitzPlot2[ii] = new TH2D(TString::Format("h_DalitzPlot2_%d", ii), "", 300, 3.995, 4.035, 280, 13.90, 13.97);
				h_cosangleD0D0B[ii] = new TH1D(TString::Format("h_cosangleD0D0B_%d", ii), "", 110, -1.1, 1.1);
				h_cosangleD0pi0[ii] = new TH1D(TString::Format("h_cosangleD0pi0_%d", ii), "", 110, -1.1, 1.1);
				h_cosangleD0Bpi0[ii] = new TH1D(TString::Format("h_cosangleD0Bpi0_%d", ii), "", 110, -1.1, 1.1);
				h_pmag_D0_restX[ii] = new TH1D(TString::Format("h_pmag_D0_restX_%d", ii), "", 130, 0, 0.13);
				h_pmag_D0B_restX[ii] = new TH1D(TString::Format("h_pmag_D0B_restX_%d", ii), "", 130, 0, 0.13);
				h_pmag_pi0_restX[ii] = new TH1D(TString::Format("h_pmag_pi0_restX_%d", ii), "", 150, 0, 0.06);

			}
		}
    }
    h_DalitzPlot[0]->Fill(s_D0pi0, s_D0Bpi0);
    h_DalitzPlotE[0]->Fill(s_D0pi0, s_D0Bpi0);
    h_DalitzPlot2[0]->Fill(s_D0pi0, s_D0D0B);
    h_pmag_D0_restX[0]->Fill(pmag_D0_restX);
    h_pmag_D0B_restX[0]->Fill(pmag_D0B_restX);
    h_pmag_pi0_restX[0]->Fill(pmag_pi0_restX);
    h_cosangleD0D0B[0]->Fill(CosTh_D0D0B_restX);
    h_cosangleD0pi0[0]->Fill(CosTh_D0pi0_restX);
    h_cosangleD0Bpi0[0]->Fill(CosTh_D0Bpi0_restX);
    
    if (i%(nevents/10) == 0) std::cout << " stage 5" << std::endl;

    for (int ii=1; ii<m; ii++)
    {
      if (matchCode == ii)
      {
        h_DalitzPlot[ii]->Fill(s_D0pi0, s_D0Bpi0);
        h_DalitzPlotE[ii]->Fill(s_D0pi0, s_D0Bpi0);
        h_DalitzPlot2[ii]->Fill(s_D0pi0, s_D0D0B);
        h_pmag_D0_restX[ii]->Fill(pmag_D0_restX);
        h_pmag_D0B_restX[ii]->Fill(pmag_D0B_restX);
        h_pmag_pi0_restX[ii]->Fill(pmag_pi0_restX);
        h_cosangleD0D0B[ii]->Fill(CosTh_D0D0B_restX);
        h_cosangleD0pi0[ii]->Fill(CosTh_D0pi0_restX);
        h_cosangleD0Bpi0[ii]->Fill(CosTh_D0Bpi0_restX);
      }
      if (ii == (m-1) && (matchCode == 2 || matchCode == 3))
      {
        h_DalitzPlot[ii]->Fill(s_D0pi0, s_D0Bpi0);
        h_DalitzPlotE[ii]->Fill(s_D0pi0, s_D0Bpi0);
        h_DalitzPlot2[ii]->Fill(s_D0pi0, s_D0D0B);
        h_pmag_D0_restX[ii]->Fill(pmag_D0_restX);
        h_pmag_D0B_restX[ii]->Fill(pmag_D0B_restX);
        h_pmag_pi0_restX[ii]->Fill(pmag_pi0_restX);
        h_cosangleD0D0B[ii]->Fill(CosTh_D0D0B_restX);
        h_cosangleD0pi0[ii]->Fill(CosTh_D0pi0_restX);
        h_cosangleD0Bpi0[ii]->Fill(CosTh_D0Bpi0_restX);
      }
      if (i%(nevents/10) == 0) std::cout << " stage 5-b" << std::endl;
    }
    if (i%(nevents/10) == 0) std::cout << " stage 6" << std::endl;
  }
  delete myRandomEngine;


  std::cout << "X(3872)->D0D0Bpi0: " << D0count << "   X(3872)->Dst0D0B: " << Dst0count << "   X(3872)->Dst0BD0: " << Dst0Bcount << std::endl;
  printf("Time taken to generate events: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

  TCanvas* const canvas = new TCanvas("canvas", "", 600, 600);
  TCanvas* const canvasE = new TCanvas("canvasE", "", 600, 600);
  TCanvas* const canvas2 = new TCanvas("canvas2", "", 600, 600);
  TCanvas* const canvasAll = new TCanvas("canvasAll", "", 600, 600);

  for (int ii=0; ii<m; ii++)
  {
    canvas->cd();
    canvas->SetLeftMargin(0.15);
    canvas->SetBottomMargin(0.10);
    canvas->SetRightMargin(0.16);
    h_DalitzPlot[ii]->SetTitle("X(3872) #rightarrow D^{0} #bar{D^{0}} #pi^{0};m^{2}_{D^{0}#pi^{0}} (GeV^{2}/c^{4});m^{2}_{#bar{D^{0}}#pi^{0}} (GeV^{2}/c^{4})");
    h_DalitzPlot[ii]->Draw("COLZ");
    canvas->Update();
    TPaveStats *stat_canvas = (TPaveStats*)(h_DalitzPlot[ii]->FindObject("stats"));
    if (stat_canvas) {
      // std::cout << " OLD X1NDC: " << stat_canvas->GetX1NDC() << " X2NDC: " << stat_canvas->GetX2NDC() ;
      // std::cout << " Y1NDC: " << stat_canvas->GetY1NDC() << " Y2NDC: " << stat_canvas->GetY2NDC() << std::endl;
      stat_canvas->SetX1NDC(0.20); stat_canvas->SetX2NDC(0.30);
      stat_canvas->SetY1NDC(0.75); stat_canvas->SetY2NDC(0.85);
      // std::cout << " NEW X1NDC: " << stat_canvas->GetX1NDC() << " X2NDC: " << stat_canvas->GetX2NDC() ;
      // std::cout << " Y1NDC: " << stat_canvas->GetY1NDC() << " Y2NDC: " << stat_canvas->GetY2NDC() << std::endl;
      stat_canvas->Draw();
    } 
    else {
      std::cerr << "No stats box found!\n";
    }
    canvas->Print(TString::Format("XtoD0Dbar0pi0_%d.pdf(", ii));

    canvasE->cd();
    canvasE->SetLeftMargin(0.15);
    canvasE->SetBottomMargin(0.10);
    canvasE->SetRightMargin(0.16);
    h_DalitzPlotE[ii]->SetTitle("X(3872) #rightarrow D^{0} #bar{D^{0}} #pi^{0};m^{2}_{D^{0}#pi^{0}} (GeV^{2}/c^{4});m^{2}_{#bar{D^{0}}#pi^{0}} (GeV^{2}/c^{4})");
    h_DalitzPlotE[ii]->Draw("COLZ");
    canvasE->Update();
    TPaveStats *stat_canvasE = (TPaveStats*)(h_DalitzPlotE[ii]->FindObject("stats"));
    if (stat_canvasE) {
      // std::cout << " OLD X1NDC: " << stat_canvasE->GetX1NDC() << " X2NDC: " << stat_canvasE->GetX2NDC() ;
      // std::cout << " Y1NDC: " << stat_canvasE->GetY1NDC() << " Y2NDC: " << stat_canvasE->GetY2NDC() << std::endl;
      stat_canvasE->SetX1NDC(0.20); stat_canvasE->SetX2NDC(0.30);
      stat_canvasE->SetY1NDC(0.75); stat_canvasE->SetY2NDC(0.85);
      // std::cout << " NEW X1NDC: " << stat_canvasE->GetX1NDC() << " X2NDC: " << stat_canvasE->GetX2NDC() ;
      // std::cout << " Y1NDC: " << stat_canvasE->GetY1NDC() << " Y2NDC: " << stat_canvasE->GetY2NDC() << std::endl;
      stat_canvasE->Draw();
    } 
    else {
      std::cerr << "No stats box found!\n";
    }
    canvasE->Print(TString::Format("XtoD0Dbar0pi0_%d.pdf", ii));

    canvas2->cd();
    canvas2->SetLeftMargin(0.15);
    canvas2->SetBottomMargin(0.10);
    canvas2->SetRightMargin(0.16);
    h_DalitzPlot2[ii]->SetTitle("X(3872) #rightarrow D^{0} #bar{D^{0}} #pi^{0};m^{2}_{D^{0}#pi^{0}} (GeV^{2}/c^{4});m^{2}_{D^{0}#bar{D^{0}}} (GeV^{2}/c^{4})");
    h_DalitzPlot2[ii]->Draw("COLZ");
    canvas2->Update();
    TPaveStats *stat_canvas2 = (TPaveStats*)(h_DalitzPlot2[ii]->FindObject("stats"));
    if (stat_canvas2) {
      // std::cout << " OLD X1NDC: " << stat_canvas2->GetX1NDC() << " X2NDC: " << stat_canvas2->GetX2NDC() ;
      // std::cout << " Y1NDC: " << stat_canvas2->GetY1NDC() << " Y2NDC: " << stat_canvas2->GetY2NDC() << std::endl;
      stat_canvas2->SetX1NDC(0.70); stat_canvas2->SetX2NDC(0.80);
      stat_canvas2->SetY1NDC(0.75); stat_canvas2->SetY2NDC(0.85);
      // std::cout << " NEW X1NDC: " << stat_canvas2->GetX1NDC() << " X2NDC: " << stat_canvas2->GetX2NDC() ;
      // std::cout << " Y1NDC: " << stat_canvas2->GetY1NDC() << " Y2NDC: " << stat_canvas2->GetY2NDC() << std::endl;
      stat_canvas2->Draw();
    } 
    else {
      std::cerr << "No stats box found!\n";
    }
    canvas2->Print(TString::Format("XtoD0Dbar0pi0_%d.pdf", ii));

    canvasAll->cd();
    TObjArray *mycopy = (TObjArray*) roottree->GetListOfBranches()->Clone(); 
    mycopy->SetOwner(kFALSE); 
    mycopy->Sort();
    for(int j = 0; j < mycopy->GetEntries(); ++j) 
    {
      if (ii == m-1)
      {
        roottree->Draw(TString(mycopy->At(j)->GetName())+" >> h_"+TString(mycopy->At(j)->GetName()), "matchCode == 2 || matchCode == 3");
      }
      else if (ii == 0)
      {
        roottree->Draw(TString(mycopy->At(j)->GetName())+" >> h_"+TString(mycopy->At(j)->GetName()));
      }
      else
      {
        roottree->Draw(TString(mycopy->At(j)->GetName())+" >> h_"+TString(mycopy->At(j)->GetName()),TString::Format("matchCode == %d", ii));
      }
      canvasAll->Update();
      // canvasAll->ls();
      TH1 *hist_x;
      hist_x = (TH1*)canvasAll->GetPrimitive( ("h_"+TString(mycopy->At(j)->GetName())).Data() ) ;
      TPaveStats *stat_canvasAll = (TPaveStats*)(hist_x->FindObject("stats"));
      stat_canvasAll->SetX1NDC(0.85); stat_canvasAll->SetX2NDC(0.95);
      stat_canvasAll->SetY1NDC(0.85); stat_canvasAll->SetY2NDC(0.95);
      canvasAll->Print(TString::Format("XtoD0Dbar0pi0_%d.pdf", ii));
    }

    canvasAll->Print(TString::Format("XtoD0Dbar0pi0_%d.pdf]", ii));

  }

  rootfile->Write();
  rootfile->Close();

  return 0;
}
