//--------------------------------------------------------------------------
//
// Environment:
//  This software is part of the EvtGen package. If you use all or part
//  of it, please give an appropriate acknowledgment.
//
// Copyright Information: See EvtGen/COPYRIGHT
//
// Module: EvtXtoD0D0Bpi0.cc
//
// Description: Routine to implement X(3872) -> D0 pi0 anti-D0
//               with C = +1 correlated D*0 anti-D0 and D0 anti-D*0 components
//               AND
//               accounts for the C = +1 D0 anti-D0 and anti-D0 D0 correlation
//               (Though the latter has no effect on the Dalitz plot, as expected)
//              Subsequent D0 and antiD0 decays are oblivious to the quantum correlations
//               (also as expected, since EvtGen does not know Kspi0 is CP- and KK is CP+)
//
//              X(3872) is also known as chi_{c1}(3872) in the PDG 2018
//
//              X(3872) -> (D0 pi0)_D*0 anti-D0     
//              X(3872) -> D0 (pi0 anti-D0)_anti-D*0 
//
//              We currently ignore non-resonant D0 pi0 anti-D0
//              It's fraction is limited to ~25% by the PDG
//              We'd have to figure out what to contract with the "eps"
//
//              Testing performed with these parameters in evt.pdl
//              You may wish to modernize these parameters
//              *X(3872) width from PDG 2018 upper limit
//              add  p Particle  X_1(3872)                    9920443  3.8716900e+00  1.2000000e-03  0.0000000e+00     0     2  0.0000000e+00    9920443
//              *D*0 width estimate from Voloshin 2003 paper
//              add  p Particle  anti-D*0                        -423  2.0068500e+00  4.3000000e-05  0.0000000e+00     0     2  0.0000000e+00       -423
//              add  p Particle  D*0                              423  2.0068500e+00  4.3000000e-05  0.0000000e+00     0     2  0.0000000e+00        423
//              * PDG 2018 (but lifetimes / widths unchanged from EvtGen)
//              add  p Particle  anti-D0                         -421  1.8648300e+00  0.0000000e+00  0.0000000e+00     0     0  1.2294489e-01       -421
//              add  p Particle  D0                               421  1.8648300e+00  0.0000000e+00  0.0000000e+00     0     0  1.2294489e-01        421
//              add  p Particle  pi0                              111  1.3497700e-01  7.7300000e-09  0.0000000e+00     0     0  0.0000000e+00        111
//
//              Routine could be modified to study
//               other 1+ -> 0- 0- 0- decays (e.g. a1+ -> K+ K- pi+)
//
// Modification history:
//
// Paras Naik    2 August 2018
//  Module created with assistance from Jeremy Dalseno
//
//------------------------------------------------------------------------

#include <math.h>

#include "EvtGenBase/EvtGenKine.hh"
#include "EvtGenBase/EvtParticle.hh"
#include "EvtGenBase/EvtPatches.hh"
#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenBase/EvtReport.hh"
#include "EvtGenBase/EvtConst.hh"
#include "EvtGenBase/EvtVector3R.hh"
#include "EvtGenBase/EvtVector4R.hh"
#include "EvtGenBase/EvtVector4C.hh"
#include "EvtGenBase/EvtTensor4C.hh"
#include "EvtGenBase/EvtDecayAmp.hh"

#include "EvtGenModels/EvtXtoD0D0Bpi0.hh"

void EvtXtoD0D0Bpi0::init()
{
  // Count events generated; we will only print full details for
  // the first nPrintEvt events.
  nEvt = 0;
  std::cout << "   \n   *** Printing full Details for first "<< nPrintEvt <<" events" << std::endl;

  // EvtXtoD0D0Bpi0 takes 6+3 = 9 arguments.
  // The 6 are the real and complex coefficients of the S, P, and D wave.
  // Note for this decay the P wave must be 0
  // due to parity conservation in strong decay.
  // This is checked later.
  // The 3 are the fractions which are polarized along eps(0), eps(1), and eps(2)
  // The sum of these fractions needs to add up to 3. (Unpolarized = 1, 1, 1)
  // checkNArg(6);
  checkNArg(9);

  // The X will have 3 daughters in the order D0, pi0, anti-D0
  checkNDaug(3); 

  // Establish X parent, and check.
  const EvtId X = getParentId();

  if (X != EvtPDL::getId("X_1(3872)"))
  {
    EvtGenReport(EVTGEN_ERROR,"EvtGen") << "EvtXtoD0D0Bpi0: There is an issue, the parent must be X_1(3872)" << std::endl;
    assert(0);
  }
  else
  {
    checkSpinParent(EvtSpinType::VECTOR);  // Spin-1 pseudovector parent
  }

  // Daughter types and ordering check
  // We expect three Spin-0 pseudoscalar daughters

  checkSpinDaughter(0,EvtSpinType::SCALAR);   
  checkSpinDaughter(1,EvtSpinType::SCALAR);
  checkSpinDaughter(2,EvtSpinType::SCALAR);

  const EvtId d1 = getDaug(0);
  const EvtId d2 = getDaug(1);
  const EvtId d3 = getDaug(2);
  
  if( !(d1 == EvtPDL::getId("D0") &&
        d2 == EvtPDL::getId("pi0") &&
        d3 == EvtPDL::getId("anti-D0")) )
  {
    EvtGenReport(EVTGEN_ERROR,"EvtGen") 
	<< "EvtXtoD0D0Bpi0: Daughter sequence should be D0, pi0, anti-D0" << std::endl;
    assert(0);
  }

}

void EvtXtoD0D0Bpi0::decay( EvtParticle *X )
{
	  // Build < D0 pi0 anti-D0 | X > amplitude
	  // i.e. f_X(m_D0pi0^2, m_D0Bpi0^2)

	  // We also have to build the < anti-D0 pi0 D0 | X > amplitude
	  // i.e. f_X(m_D0Bpi0^2, m_D0pi0^2) )
	  // this is simply the *swap* p4_D0 <-> p4_D0B,
	  //  and then flip the sign of the momentum of all decay particles
	  // all _swap terms below are related to this amplitude

  // Input parameters
  EvtComplex as(getArg(0)*cos(getArg(1)),getArg(0)*sin(getArg(1))); // PN: SWAVE
  EvtComplex ap(getArg(2)*cos(getArg(3)),getArg(2)*sin(getArg(3))); // PN: PWAVE [must be zero]
  EvtComplex ad(getArg(4)*cos(getArg(5)),getArg(4)*sin(getArg(5))); // PN: DWAVE
  double pol0 = getArg(6);
  double pol1 = getArg(7);
  double pol2 = getArg(8);

  if (nEvt <= nPrintEvt) std::cout << "as: " << as << "  ap (must be zero): " << ap << "  ad: " << ad << std::endl;

  if (ap!=EvtComplex(0.0,0.0))
  {
	EvtGenReport(EVTGEN_ERROR,"EvtGen") << "In EvtXtoDDbPi0.cc" << std::endl;
	EvtGenReport(EVTGEN_ERROR,"EvtGen") << "Note, P wave not possible due to conservation of parity in strong decays!" << std::endl;
	::abort();
  }

  // Increment nEvt
  nEvt++;
  if (nEvt <= nPrintEvt) std::cout << "\n   ***Details for Event #" << nEvt << "\n" << std::endl;

  if (X->getId() != EvtPDL::getId("X_1(3872)"))
  {
    if (nEvt <= nPrintEvt) std::cout <<  "NOT X_1(3872)!" << std::endl ;
  }
  
  // Generate 4-vectors in phase space
  X->initializePhaseSpace( getNDaug(), getDaugs() );

  // Daughters
  const EvtParticle *D0     = X->getDaug(0);
  const EvtParticle *pi0    = X->getDaug(1);
  const EvtParticle *antiD0 = X->getDaug(2);

  // Daughter 4-momenta
  const EvtVector4R p4_D0     = D0->getP4(); // i.e. D0 P4 in X rest frame
  const EvtVector4R p4_pi0    = pi0->getP4(); // i.e. pi0 P4 in X rest frame
  const EvtVector4R p4_antiD0 = antiD0->getP4(); // i.e. antiD0 P4 in X rest frame

  // for mirror/swap amplitude
  const EvtVector4R p4_D0_swap(antiD0->getP4().get(0),-antiD0->getP4().get(1),-antiD0->getP4().get(2),-antiD0->getP4().get(3));
  const EvtVector4R p4_pi0_swap(pi0->getP4().get(0),-pi0->getP4().get(1),-pi0->getP4().get(2),-pi0->getP4().get(3));
  const EvtVector4R p4_antiD0_swap(D0->getP4().get(0),-D0->getP4().get(1),-D0->getP4().get(2),-D0->getP4().get(3));

  double M_X;
  M_X = EvtPDL::getMeanMass(X->getId());
  if (nEvt <= nPrintEvt) std::cout <<  "M_X "        << M_X ;

  const double M_D0     = EvtPDL::getMeanMass(EvtPDL::getId("D0"));
  const double M_pi0    = EvtPDL::getMeanMass(EvtPDL::getId("pi0"));
  const double M_antiD0 = EvtPDL::getMeanMass(EvtPDL::getId("anti-D0"));
  if (nEvt <= nPrintEvt) 
  {
    std::cout << " M_D0 "       << M_D0 ;
    std::cout << " M_pi0 "      << M_pi0 ;
    std::cout << " M_antiD0 "   << M_antiD0 ;
  }

  const double M_Dst0     = EvtPDL::getMeanMass(EvtPDL::getId("D*0"));
  const double M_antiDst0 = EvtPDL::getMeanMass(EvtPDL::getId("anti-D*0"));
  if (nEvt <= nPrintEvt) 
  {
    std::cout << " M_Dst0 "     << M_Dst0 ;
    std::cout << " M_antiDst0 " << M_antiDst0 << std::endl;
  }

  const double G_Dst0     = EvtPDL::getWidth(EvtPDL::getId("D*0"));
  const double G_antiDst0 = EvtPDL::getWidth(EvtPDL::getId("anti-D*0"));
  if (nEvt <= nPrintEvt) 
  {
    std::cout << " G_Dst0 "     << G_Dst0 ;
    std::cout << " G_antiDst0 " << G_antiDst0 << std::endl;
  }

  const EvtVector4R p4_D0pi0     = p4_D0  + p4_pi0;
  const EvtVector4R p4_pi0antiD0 = p4_pi0 + p4_antiD0;

  const EvtVector4R q4_D0pi0     = p4_D0  - p4_pi0;
  const EvtVector4R q4_pi0antiD0 = p4_pi0 - p4_antiD0;

  const EvtVector4R p4_D0pi0_swap     = p4_D0_swap  + p4_pi0_swap;
  const EvtVector4R p4_pi0antiD0_swap = p4_pi0_swap + p4_antiD0_swap;

  const EvtVector4R q4_D0pi0_swap     = p4_D0_swap  - p4_pi0_swap;
  const EvtVector4R q4_pi0antiD0_swap = p4_pi0_swap - p4_antiD0_swap;

  double m_D0pi0     = (p4_D0pi0).mass();
  double m_pi0antiD0 = (p4_pi0antiD0).mass();

  double s_D0pi0     = (p4_D0pi0).mass2();
  double s_pi0antiD0 = (p4_pi0antiD0).mass2();

  double m_D0pi0_swap     = (p4_D0pi0_swap).mass();
  double m_pi0antiD0_swap = (p4_pi0antiD0_swap).mass();

  double s_D0pi0_swap     = (p4_D0pi0_swap).mass2();
  double s_pi0antiD0_swap = (p4_pi0antiD0_swap).mass2();

  // Mother 4-momentum
  // const EvtVector4R p4_X = X->getP4();
  const EvtVector4R p4_X(X->mass(),0.0,0.0,0.0); // we want everything in the X rest frame
  if (nEvt <= nPrintEvt) std::cout  <<  "X->mass() "  << M_X << std::endl ;

  const EvtVector4R q4_X_Dst0antiD0 = p4_D0pi0     - p4_antiD0;
  const EvtVector4R q4_X_D0antiDst0 = p4_D0        - p4_pi0antiD0;

  const EvtVector4R q4_X_Dst0antiD0_swap = p4_D0pi0_swap     - p4_antiD0_swap;
  const EvtVector4R q4_X_D0antiDst0_swap = p4_D0_swap        - p4_pi0antiD0_swap;

  // Set radial parameters (CHECK is this OK for X?)
  double r_X   = 1.5; // [hbar c / Gev] (use same as J/psi in PhysRevD.95.072007)
  double r_Dst = 1.5; // [hbar c / Gev]

  // Calculate X barrier factor for S and D wave
  // [using different methods; only one will be selected, see below]

//  double Dst0antiD0_BarrierX_S_BLN = Barrier(0,r_X,Breakup(p4_X.mass(),m_D0pi0,M_antiD0),Breakup(M_X,m_D0pi0,M_antiD0));
//  double D0antiDst0_BarrierX_S_BLN = Barrier(0,r_X,Breakup(p4_X.mass(),M_D0,m_pi0antiD0),Breakup(M_X,M_D0,m_pi0antiD0));

//  double Dst0antiD0_BarrierX_S_BL = Barrier(0,r_X,Breakup(p4_X.mass(),m_D0pi0,M_antiD0));
//  double D0antiDst0_BarrierX_S_BL = Barrier(0,r_X,Breakup(p4_X.mass(),M_D0,m_pi0antiD0));

  double Dst0antiD0_BarrierX_S_BLHQ = BarrierHQ(0,r_X,Breakup(p4_X.mass(),m_D0pi0,M_antiD0));
  double D0antiDst0_BarrierX_S_BLHQ = BarrierHQ(0,r_X,Breakup(p4_X.mass(),M_D0,m_pi0antiD0));

  double Dst0antiD0_BarrierX_S_BLHQN = BarrierHQ(0,r_X,Breakup(p4_X.mass(),m_D0pi0,M_antiD0),Breakup(M_X,m_D0pi0,M_antiD0));
  double D0antiDst0_BarrierX_S_BLHQN = BarrierHQ(0,r_X,Breakup(p4_X.mass(),M_D0,m_pi0antiD0),Breakup(M_X,M_D0,m_pi0antiD0));

  double Dst0antiD0_BarrierX_S_BLHQ_swap = BarrierHQ(0,r_X,Breakup(p4_X.mass(),m_D0pi0_swap,M_antiD0));
  double D0antiDst0_BarrierX_S_BLHQ_swap = BarrierHQ(0,r_X,Breakup(p4_X.mass(),M_D0,m_pi0antiD0_swap));

  double Dst0antiD0_BarrierX_S_BLHQN_swap = BarrierHQ(0,r_X,Breakup(p4_X.mass(),m_D0pi0_swap,M_antiD0),Breakup(M_X,m_D0pi0_swap,M_antiD0));
  double D0antiDst0_BarrierX_S_BLHQN_swap = BarrierHQ(0,r_X,Breakup(p4_X.mass(),M_D0,m_pi0antiD0_swap),Breakup(M_X,M_D0,m_pi0antiD0_swap));


//  double Dst0antiD0_BarrierX_D_BLN = Barrier(2,r_X,Breakup(p4_X.mass(),m_D0pi0,M_antiD0),Breakup(M_X,m_D0pi0,M_antiD0));
//  double D0antiDst0_BarrierX_D_BLN = Barrier(2,r_X,Breakup(p4_X.mass(),M_D0,m_pi0antiD0),Breakup(M_X,M_D0,m_pi0antiD0));

//  double Dst0antiD0_BarrierX_D_BL = Barrier(2,r_X,Breakup(p4_X.mass(),m_D0pi0,M_antiD0));
//  double D0antiDst0_BarrierX_D_BL = Barrier(2,r_X,Breakup(p4_X.mass(),M_D0,m_pi0antiD0));

  double Dst0antiD0_BarrierX_D_BLHQ = BarrierHQ(2,r_X,Breakup(p4_X.mass(),m_D0pi0,M_antiD0));
  double D0antiDst0_BarrierX_D_BLHQ = BarrierHQ(2,r_X,Breakup(p4_X.mass(),M_D0,m_pi0antiD0));

  double Dst0antiD0_BarrierX_D_BLHQN = BarrierHQ(2,r_X,Breakup(p4_X.mass(),m_D0pi0,M_antiD0),Breakup(M_X,m_D0pi0,M_antiD0));
  double D0antiDst0_BarrierX_D_BLHQN = BarrierHQ(2,r_X,Breakup(p4_X.mass(),M_D0,m_pi0antiD0),Breakup(M_X,M_D0,m_pi0antiD0));

  double Dst0antiD0_BarrierX_D_BLHQ_swap = BarrierHQ(2,r_X,Breakup(p4_X.mass(),m_D0pi0_swap,M_antiD0));
  double D0antiDst0_BarrierX_D_BLHQ_swap = BarrierHQ(2,r_X,Breakup(p4_X.mass(),M_D0,m_pi0antiD0_swap));

  double Dst0antiD0_BarrierX_D_BLHQN_swap = BarrierHQ(2,r_X,Breakup(p4_X.mass(),m_D0pi0_swap,M_antiD0),Breakup(M_X,m_D0pi0_swap,M_antiD0));
  double D0antiDst0_BarrierX_D_BLHQN_swap = BarrierHQ(2,r_X,Breakup(p4_X.mass(),M_D0,m_pi0antiD0_swap),Breakup(M_X,M_D0,m_pi0antiD0_swap));

  // Calculate resonance R barrier factor

//  double Dst0antiD0_BarrierR_BLN = Barrier(1,r_Dst,Breakup(m_D0pi0,M_D0,M_pi0)        ,Breakup(M_Dst0,M_D0,M_pi0)        );
//  double D0antiDst0_BarrierR_BLN = Barrier(1,r_Dst,Breakup(m_pi0antiD0,M_pi0,M_antiD0),Breakup(M_antiDst0,M_pi0,M_antiD0));

//  double Dst0antiD0_BarrierR_BL = Barrier(1,r_Dst,Breakup(m_D0pi0,M_D0,M_pi0)        );
//  double D0antiDst0_BarrierR_BL = Barrier(1,r_Dst,Breakup(m_pi0antiD0,M_pi0,M_antiD0));

  double Dst0antiD0_BarrierR_BLHQ = BarrierHQ(1,r_Dst,Breakup(m_D0pi0,M_D0,M_pi0)        );
  double D0antiDst0_BarrierR_BLHQ = BarrierHQ(1,r_Dst,Breakup(m_pi0antiD0,M_pi0,M_antiD0));

  double Dst0antiD0_BarrierR_BLHQN = BarrierHQ(1,r_Dst,Breakup(m_D0pi0,M_D0,M_pi0)        ,Breakup(M_Dst0,M_D0,M_pi0)        );
  double D0antiDst0_BarrierR_BLHQN = BarrierHQ(1,r_Dst,Breakup(m_pi0antiD0,M_pi0,M_antiD0),Breakup(M_antiDst0,M_pi0,M_antiD0));

  double Dst0antiD0_BarrierR_BLHQ_swap = BarrierHQ(1,r_Dst,Breakup(m_D0pi0_swap,M_D0,M_pi0)        );
  double D0antiDst0_BarrierR_BLHQ_swap = BarrierHQ(1,r_Dst,Breakup(m_pi0antiD0_swap,M_pi0,M_antiD0));

  double Dst0antiD0_BarrierR_BLHQN_swap = BarrierHQ(1,r_Dst,Breakup(m_D0pi0_swap,M_D0,M_pi0)        ,Breakup(M_Dst0,M_D0,M_pi0)        );
  double D0antiDst0_BarrierR_BLHQN_swap = BarrierHQ(1,r_Dst,Breakup(m_pi0antiD0_swap,M_pi0,M_antiD0),Breakup(M_antiDst0,M_pi0,M_antiD0));

  // Calculate mass dependent width (including selecting a barrier factor! We choose HQN)
  double Gamma_Dst0antiD0 = Gamma(G_Dst0    ,m_D0pi0    ,M_Dst0    ,Breakup(m_D0pi0,M_D0,M_pi0)        ,Breakup(M_Dst0,M_D0,M_pi0),        Dst0antiD0_BarrierR_BLHQN,1);
  double Gamma_D0antiDst0 = Gamma(G_antiDst0,m_pi0antiD0,M_antiDst0,Breakup(m_pi0antiD0,M_pi0,M_antiD0),Breakup(M_antiDst0,M_pi0,M_antiD0),D0antiDst0_BarrierR_BLHQN,1);

  double Gamma_Dst0antiD0_swap = Gamma(G_Dst0    ,m_D0pi0_swap    ,M_Dst0    ,Breakup(m_D0pi0_swap,M_D0,M_pi0)        ,Breakup(M_Dst0,M_D0,M_pi0),        Dst0antiD0_BarrierR_BLHQN_swap,1);
  double Gamma_D0antiDst0_swap = Gamma(G_antiDst0,m_pi0antiD0_swap,M_antiDst0,Breakup(m_pi0antiD0_swap,M_pi0,M_antiD0),Breakup(M_antiDst0,M_pi0,M_antiD0),D0antiDst0_BarrierR_BLHQN_swap,1);

  if (nEvt <= nPrintEvt) 
  {
	    std::cout << "Gamma_Dst0antiD0: " << Gamma_Dst0antiD0 << std::endl;
	    std::cout << "Gamma_D0antiDst0: " << Gamma_D0antiDst0 << std::endl;

	    std::cout << "Gamma_Dst0antiD0_swap: " << Gamma_Dst0antiD0_swap << std::endl;
	    std::cout << "Gamma_D0antiDst0_swap: " << Gamma_D0antiDst0_swap << std::endl;
  }

  // Define i_ = i
  const EvtComplex i_(0,1);

  // Calculate line shape
  const EvtComplex BW_Dst0antiD0_lineshape = 1 / (M_Dst0    *M_Dst0     - s_D0pi0     - i_*M_Dst0    *Gamma_Dst0antiD0);
  const EvtComplex BW_D0antiDst0_lineshape = 1 / (M_antiDst0*M_antiDst0 - s_pi0antiD0 - i_*M_antiDst0*Gamma_D0antiDst0);

  const EvtComplex BW_Dst0antiD0_lineshape_swap = 1 / (M_Dst0    *M_Dst0     - s_D0pi0_swap     - i_*M_Dst0    *Gamma_Dst0antiD0_swap);
  const EvtComplex BW_D0antiDst0_lineshape_swap = 1 / (M_antiDst0*M_antiDst0 - s_pi0antiD0_swap - i_*M_antiDst0*Gamma_D0antiDst0_swap);

  if (nEvt <= nPrintEvt) 
  {
	    std::cout << "BW_Dst0antiD0_lineshape AMP at pole:"<< 1 / ( - i_ * M_Dst0    * Gamma_Dst0antiD0 ) << std::endl;
	    std::cout << "BW_D0antiDst0_lineshape AMP at pole:"<< 1 / ( - i_ * M_antiDst0* Gamma_D0antiDst0 ) << std::endl;

	    std::cout << "BW_Dst0antiD0_lineshape_swap AMP at pole:"<< 1 / ( - i_ * M_Dst0    * Gamma_Dst0antiD0_swap ) << std::endl;
	    std::cout << "BW_D0antiDst0_lineshape_swap AMP at pole:"<< 1 / ( - i_ * M_antiDst0* Gamma_D0antiDst0_swap ) << std::endl;
  }

  // Calculate spin factors

  // \sum_{{s_z}_{\X}~{s_z}_{\Dstz}}\bra{(\Dz\pi^0)_{L = 1}}\mathcal{M}_{\Dstz}\ket{\Dstz}\bra{(\Dstz\Dzb)_{L = 0}}\mathcal{M}_{\X}\ket{\X} 

  const EvtVector4C L1_D0pi0     = L1(p4_D0pi0,    q4_D0pi0);
  const EvtVector4C L1_pi0antiD0 = L1(p4_pi0antiD0,q4_pi0antiD0);

  const EvtVector4C L1_D0pi0_swap     = L1(p4_D0pi0_swap,    q4_D0pi0_swap);
  const EvtVector4C L1_pi0antiD0_swap = L1(p4_pi0antiD0_swap,q4_pi0antiD0_swap);

  EvtComplex Spin_Xeps0_D0pi0_S,     Spin_Xeps1_D0pi0_S,     Spin_Xeps2_D0pi0_S;
  EvtComplex Spin_Xeps0_pi0antiD0_S, Spin_Xeps1_pi0antiD0_S, Spin_Xeps2_pi0antiD0_S;

  EvtComplex Spin_Xeps0_D0pi0_S_swap,     Spin_Xeps1_D0pi0_S_swap,     Spin_Xeps2_D0pi0_S_swap;
  EvtComplex Spin_Xeps0_pi0antiD0_S_swap, Spin_Xeps1_pi0antiD0_S_swap, Spin_Xeps2_pi0antiD0_S_swap;

  // eps(i) are the 3 different spin projections of the spin 1 X
  if (X->getId() == EvtPDL::getId("X_1(3872)"))
  {
	// note that S = X.cont(L) means S = X_ν L^ν
	    Spin_Xeps0_D0pi0_S     = (X->eps(0)).cont(L1_D0pi0);
	    Spin_Xeps1_D0pi0_S     = (X->eps(1)).cont(L1_D0pi0);
	    Spin_Xeps2_D0pi0_S     = (X->eps(2)).cont(L1_D0pi0);

	    Spin_Xeps0_pi0antiD0_S = (X->eps(0)).cont(L1_pi0antiD0);
	    Spin_Xeps1_pi0antiD0_S = (X->eps(1)).cont(L1_pi0antiD0);
	    Spin_Xeps2_pi0antiD0_S = (X->eps(2)).cont(L1_pi0antiD0);

	    Spin_Xeps0_D0pi0_S_swap     = (X->eps(0)).cont(L1_D0pi0_swap);
	    Spin_Xeps1_D0pi0_S_swap     = (X->eps(1)).cont(L1_D0pi0_swap);
	    Spin_Xeps2_D0pi0_S_swap     = (X->eps(2)).cont(L1_D0pi0_swap);

	    Spin_Xeps0_pi0antiD0_S_swap = (X->eps(0)).cont(L1_pi0antiD0_swap);
	    Spin_Xeps1_pi0antiD0_S_swap = (X->eps(1)).cont(L1_pi0antiD0_swap);
	    Spin_Xeps2_pi0antiD0_S_swap = (X->eps(2)).cont(L1_pi0antiD0_swap);
  }
  else
  {
    if (nEvt <= nPrintEvt) std::cout <<  "NOT X_1(3872)!" << std::endl ;

    Spin_Xeps0_D0pi0_S = 0;
    Spin_Xeps1_D0pi0_S = 0;
    Spin_Xeps2_D0pi0_S = 0;

    Spin_Xeps0_pi0antiD0_S = 0;
    Spin_Xeps1_pi0antiD0_S = 0;
    Spin_Xeps2_pi0antiD0_S = 0;

    Spin_Xeps0_D0pi0_S_swap = 0;
    Spin_Xeps1_D0pi0_S_swap = 0;
    Spin_Xeps2_D0pi0_S_swap = 0;

    Spin_Xeps0_pi0antiD0_S_swap = 0;
    Spin_Xeps1_pi0antiD0_S_swap = 0;
    Spin_Xeps2_pi0antiD0_S_swap = 0;
  }

  // \sum_{{s_z}_{\X}~{s_z}_{\Dstz}}\bra{(\Dz\pi^0)_{L = 1}}\mathcal{M}_{\Dstz}\ket{\Dstz}\bra{(\Dstz\Dzb)_{L = 2}}\mathcal{M}_{\X}\ket{\X}

  // already have the L1, from above

  const EvtTensor4C L2_Dst0antiD0 = L2(p4_X,q4_X_Dst0antiD0);
  const EvtTensor4C L2_D0antiDst0 = L2(p4_X,q4_X_D0antiDst0);

  const EvtTensor4C L2_Dst0antiD0_swap = L2(p4_X,q4_X_Dst0antiD0_swap);
  const EvtTensor4C L2_D0antiDst0_swap = L2(p4_X,q4_X_D0antiDst0_swap);

  EvtComplex Spin_Xeps0_D0pi0_D, Spin_Xeps1_D0pi0_D, Spin_Xeps2_D0pi0_D;
  EvtComplex Spin_Xeps0_pi0antiD0_D, Spin_Xeps1_pi0antiD0_D, Spin_Xeps2_pi0antiD0_D;

  EvtComplex Spin_Xeps0_D0pi0_D_swap, Spin_Xeps1_D0pi0_D_swap, Spin_Xeps2_D0pi0_D_swap;
  EvtComplex Spin_Xeps0_pi0antiD0_D_swap, Spin_Xeps1_pi0antiD0_D_swap, Spin_Xeps2_pi0antiD0_D_swap;

  // eps(i) are the 3 different spin projections of the spin 1 X

  // note that L = P.cont2(q) means L^μ = P^μν q_ν
  // presume (check) that L = P.cont2(q) also means L_μ = P_μν q^ν

  Spin_Xeps0_D0pi0_D = (X->eps(0)).cont(L2_Dst0antiD0.cont2(L1_D0pi0));
  Spin_Xeps1_D0pi0_D = (X->eps(1)).cont(L2_Dst0antiD0.cont2(L1_D0pi0));
  Spin_Xeps2_D0pi0_D = (X->eps(2)).cont(L2_Dst0antiD0.cont2(L1_D0pi0));

  Spin_Xeps0_pi0antiD0_D = (X->eps(0)).cont(L2_D0antiDst0.cont2(L1_pi0antiD0));
  Spin_Xeps1_pi0antiD0_D = (X->eps(1)).cont(L2_D0antiDst0.cont2(L1_pi0antiD0));
  Spin_Xeps2_pi0antiD0_D = (X->eps(2)).cont(L2_D0antiDst0.cont2(L1_pi0antiD0));

  Spin_Xeps0_D0pi0_D_swap = (X->eps(0)).cont(L2_Dst0antiD0_swap.cont2(L1_D0pi0_swap));
  Spin_Xeps1_D0pi0_D_swap = (X->eps(1)).cont(L2_Dst0antiD0_swap.cont2(L1_D0pi0_swap));
  Spin_Xeps2_D0pi0_D_swap = (X->eps(2)).cont(L2_Dst0antiD0_swap.cont2(L1_D0pi0_swap));

  Spin_Xeps0_pi0antiD0_D_swap = (X->eps(0)).cont(L2_D0antiDst0_swap.cont2(L1_pi0antiD0_swap));
  Spin_Xeps1_pi0antiD0_D_swap = (X->eps(1)).cont(L2_D0antiDst0_swap.cont2(L1_pi0antiD0_swap));
  Spin_Xeps2_pi0antiD0_D_swap = (X->eps(2)).cont(L2_D0antiDst0_swap.cont2(L1_pi0antiD0_swap));

  // Construct total S-wave amplitudes for each basis vector
  // Use normalized barrier factors in a covariant tensor formalism (but they are all normalized...)
  // We choose HQ barrier factors
  EvtComplex total_BW_Dst0antiD0_0_S = Spin_Xeps0_D0pi0_S * Dst0antiD0_BarrierX_S_BLHQ * Dst0antiD0_BarrierR_BLHQ * BW_Dst0antiD0_lineshape;
  EvtComplex total_BW_Dst0antiD0_1_S = Spin_Xeps1_D0pi0_S * Dst0antiD0_BarrierX_S_BLHQ * Dst0antiD0_BarrierR_BLHQ * BW_Dst0antiD0_lineshape;
  EvtComplex total_BW_Dst0antiD0_2_S = Spin_Xeps2_D0pi0_S * Dst0antiD0_BarrierX_S_BLHQ * Dst0antiD0_BarrierR_BLHQ * BW_Dst0antiD0_lineshape;

  EvtComplex total_BW_D0antiDst0_0_S = Spin_Xeps0_pi0antiD0_S * D0antiDst0_BarrierX_S_BLHQ * D0antiDst0_BarrierR_BLHQ * BW_D0antiDst0_lineshape;
  EvtComplex total_BW_D0antiDst0_1_S = Spin_Xeps1_pi0antiD0_S * D0antiDst0_BarrierX_S_BLHQ * D0antiDst0_BarrierR_BLHQ * BW_D0antiDst0_lineshape;
  EvtComplex total_BW_D0antiDst0_2_S = Spin_Xeps2_pi0antiD0_S * D0antiDst0_BarrierX_S_BLHQ * D0antiDst0_BarrierR_BLHQ * BW_D0antiDst0_lineshape;

  EvtComplex total_BW_Dst0antiD0_0_S_swap = Spin_Xeps0_D0pi0_S_swap * Dst0antiD0_BarrierX_S_BLHQ_swap * Dst0antiD0_BarrierR_BLHQ_swap * BW_Dst0antiD0_lineshape_swap;
  EvtComplex total_BW_Dst0antiD0_1_S_swap = Spin_Xeps1_D0pi0_S_swap * Dst0antiD0_BarrierX_S_BLHQ_swap * Dst0antiD0_BarrierR_BLHQ_swap * BW_Dst0antiD0_lineshape_swap;
  EvtComplex total_BW_Dst0antiD0_2_S_swap = Spin_Xeps2_D0pi0_S_swap * Dst0antiD0_BarrierX_S_BLHQ_swap * Dst0antiD0_BarrierR_BLHQ_swap * BW_Dst0antiD0_lineshape_swap;

  EvtComplex total_BW_D0antiDst0_0_S_swap = Spin_Xeps0_pi0antiD0_S_swap * D0antiDst0_BarrierX_S_BLHQ_swap * D0antiDst0_BarrierR_BLHQ_swap * BW_D0antiDst0_lineshape_swap;
  EvtComplex total_BW_D0antiDst0_1_S_swap = Spin_Xeps1_pi0antiD0_S_swap * D0antiDst0_BarrierX_S_BLHQ_swap * D0antiDst0_BarrierR_BLHQ_swap * BW_D0antiDst0_lineshape_swap;
  EvtComplex total_BW_D0antiDst0_2_S_swap = Spin_Xeps2_pi0antiD0_S_swap * D0antiDst0_BarrierX_S_BLHQ_swap * D0antiDst0_BarrierR_BLHQ_swap * BW_D0antiDst0_lineshape_swap;

  // Construct total D-wave amplitudes for each basis vector
  // Use normalized barrier factors in a covariant tensor formalism
  EvtComplex total_BW_Dst0antiD0_0_D = Spin_Xeps0_D0pi0_D * Dst0antiD0_BarrierX_D_BLHQ * Dst0antiD0_BarrierR_BLHQ * BW_Dst0antiD0_lineshape;
  EvtComplex total_BW_Dst0antiD0_1_D = Spin_Xeps1_D0pi0_D * Dst0antiD0_BarrierX_D_BLHQ * Dst0antiD0_BarrierR_BLHQ * BW_Dst0antiD0_lineshape;
  EvtComplex total_BW_Dst0antiD0_2_D = Spin_Xeps2_D0pi0_D * Dst0antiD0_BarrierX_D_BLHQ * Dst0antiD0_BarrierR_BLHQ * BW_Dst0antiD0_lineshape;

  EvtComplex total_BW_D0antiDst0_0_D = Spin_Xeps0_pi0antiD0_D * D0antiDst0_BarrierX_D_BLHQ * D0antiDst0_BarrierR_BLHQ * BW_D0antiDst0_lineshape;
  EvtComplex total_BW_D0antiDst0_1_D = Spin_Xeps1_pi0antiD0_D * D0antiDst0_BarrierX_D_BLHQ * D0antiDst0_BarrierR_BLHQ * BW_D0antiDst0_lineshape;
  EvtComplex total_BW_D0antiDst0_2_D = Spin_Xeps2_pi0antiD0_D * D0antiDst0_BarrierX_D_BLHQ * D0antiDst0_BarrierR_BLHQ * BW_D0antiDst0_lineshape;

  EvtComplex total_BW_Dst0antiD0_0_D_swap = Spin_Xeps0_D0pi0_D_swap * Dst0antiD0_BarrierX_D_BLHQ_swap * Dst0antiD0_BarrierR_BLHQ_swap * BW_Dst0antiD0_lineshape_swap;
  EvtComplex total_BW_Dst0antiD0_1_D_swap = Spin_Xeps1_D0pi0_D_swap * Dst0antiD0_BarrierX_D_BLHQ_swap * Dst0antiD0_BarrierR_BLHQ_swap * BW_Dst0antiD0_lineshape_swap;
  EvtComplex total_BW_Dst0antiD0_2_D_swap = Spin_Xeps2_D0pi0_D_swap * Dst0antiD0_BarrierX_D_BLHQ_swap * Dst0antiD0_BarrierR_BLHQ_swap * BW_Dst0antiD0_lineshape_swap;

  EvtComplex total_BW_D0antiDst0_0_D_swap = Spin_Xeps0_pi0antiD0_D_swap * D0antiDst0_BarrierX_D_BLHQ_swap * D0antiDst0_BarrierR_BLHQ_swap * BW_D0antiDst0_lineshape_swap;
  EvtComplex total_BW_D0antiDst0_1_D_swap = Spin_Xeps1_pi0antiD0_D_swap * D0antiDst0_BarrierX_D_BLHQ_swap * D0antiDst0_BarrierR_BLHQ_swap * BW_D0antiDst0_lineshape_swap;
  EvtComplex total_BW_D0antiDst0_2_D_swap = Spin_Xeps2_pi0antiD0_D_swap * D0antiDst0_BarrierX_D_BLHQ_swap * D0antiDst0_BarrierR_BLHQ_swap * BW_D0antiDst0_lineshape_swap;

  // Sum S and D wave for each basis vector, in proportions provided by DECAY.DEC
  EvtComplex total_BW_Dst0antiD0_0 = as*total_BW_Dst0antiD0_0_S + ad*total_BW_Dst0antiD0_0_D;
  EvtComplex total_BW_Dst0antiD0_1 = as*total_BW_Dst0antiD0_1_S + ad*total_BW_Dst0antiD0_1_D;
  EvtComplex total_BW_Dst0antiD0_2 = as*total_BW_Dst0antiD0_2_S + ad*total_BW_Dst0antiD0_2_D;

  EvtComplex total_BW_D0antiDst0_0 = as*total_BW_D0antiDst0_0_S + ad*total_BW_D0antiDst0_0_D;
  EvtComplex total_BW_D0antiDst0_1 = as*total_BW_D0antiDst0_1_S + ad*total_BW_D0antiDst0_1_D;
  EvtComplex total_BW_D0antiDst0_2 = as*total_BW_D0antiDst0_2_S + ad*total_BW_D0antiDst0_2_D;

  EvtComplex total_BW_Dst0antiD0_0_swap = as*total_BW_Dst0antiD0_0_S_swap + ad*total_BW_Dst0antiD0_0_D_swap;
  EvtComplex total_BW_Dst0antiD0_1_swap = as*total_BW_Dst0antiD0_1_S_swap + ad*total_BW_Dst0antiD0_1_D_swap;
  EvtComplex total_BW_Dst0antiD0_2_swap = as*total_BW_Dst0antiD0_2_S_swap + ad*total_BW_Dst0antiD0_2_D_swap;

  EvtComplex total_BW_D0antiDst0_0_swap = as*total_BW_D0antiDst0_0_S_swap + ad*total_BW_D0antiDst0_0_D_swap;
  EvtComplex total_BW_D0antiDst0_1_swap = as*total_BW_D0antiDst0_1_S_swap + ad*total_BW_D0antiDst0_1_D_swap;
  EvtComplex total_BW_D0antiDst0_2_swap = as*total_BW_D0antiDst0_2_S_swap + ad*total_BW_D0antiDst0_2_D_swap;

  // Finalize

  if (X->getId() != EvtPDL::getId("X_1(3872)"))
  {
    if (nEvt <= nPrintEvt) std::cout <<  "NOT X_1(3872)!" << std::endl ;
  }
  else
  {
    double D0antiDst0_ON = 1; // turn D antiD* on
    //double D0antiDst0_ON = 0; // turn D antiD* off
    double swap_ON = 1; // turn swap on
    // D*D vs DD* relative phase is fixed to + by C conservation
    EvtComplex total_0 = total_BW_Dst0antiD0_0 + D0antiDst0_ON * total_BW_D0antiDst0_0;
    EvtComplex total_1 = total_BW_Dst0antiD0_1 + D0antiDst0_ON * total_BW_D0antiDst0_1;
    EvtComplex total_2 = total_BW_Dst0antiD0_2 + D0antiDst0_ON * total_BW_D0antiDst0_2;
    EvtComplex total_0_swap = total_BW_Dst0antiD0_0_swap + D0antiDst0_ON * total_BW_D0antiDst0_0_swap;
    EvtComplex total_1_swap = total_BW_Dst0antiD0_1_swap + D0antiDst0_ON * total_BW_D0antiDst0_1_swap;
    EvtComplex total_2_swap = total_BW_Dst0antiD0_2_swap + D0antiDst0_ON * total_BW_D0antiDst0_2_swap;
    if (nEvt <= nPrintEvt) std::cout <<  "total_0" << total_0 << std::endl ;
    if (nEvt <= nPrintEvt) std::cout <<  "total_0_swap" << swap_ON * total_0_swap << std::endl ;
    if (nEvt <= nPrintEvt) std::cout <<  "total_1" << total_1 << std::endl ;
    if (nEvt <= nPrintEvt) std::cout <<  "total_1_swap" << swap_ON * total_1_swap << std::endl ;
    if (nEvt <= nPrintEvt) std::cout <<  "total_2" << total_2 << std::endl ;
    if (nEvt <= nPrintEvt) std::cout <<  "total_2_swap" << swap_ON * total_2_swap << std::endl ;

    if (pol0 > 0.00000001) vertex(0, sqrt(pol0) * (total_0 + swap_ON * total_0_swap) / (sqrt(2)) );
    if (pol1 > 0.00000001) vertex(1, sqrt(pol1) * (total_1 + swap_ON * total_1_swap) / (sqrt(2)) );
    if (pol2 > 0.00000001) vertex(2, sqrt(pol2) * (total_2 + swap_ON * total_2_swap) / (sqrt(2)) );
    // so this is sort of wrong if swap is off by a factor of sqrt(2), just keep track of it if ever comparing samples by amplitude
  }

}

double calcXBasisAmp(const int eps, EvtParticle& X, EvtVector4R& p4_D0, EvtVector4R& p4_pi0, EvtVector4R& p4_antiD0)
{
	return 0.0;
}

double EvtXtoD0D0Bpi0::Breakup( const double& m12, const double& m1, const double& m2 )
{
    double p_p = sqrt( ( m12*m12 - (m1+m2)*(m1+m2) ) * ( m12*m12 - (m1-m2)*(m1-m2) ) / (4*m12*m12) );
	if ((m1 + m2) >= m12) {
		std::cout << "Breakup m1 + m2 >= m12. As failsafe, we set the breakup momentum to zero.\n" ;
		p_p = 0; // failsafe
	}
    if (nEvt <= nPrintEvt) std::cout << "EvtXtoD0D0Bpi0::Breakup called with result: M12 " << m12 << " M1 " << m1 << "  M2 " << m2 << "  Breakup " << p_p << std::endl;
    return p_p;
}

double EvtXtoD0D0Bpi0::Gamma(const double& GammaR, const double& mab , const double& mr, const double& p_mab, const double& p_mr, const double& BWbf, const double& J)
{
    double Gamma = GammaR * (mr / mab) * pow( (p_mab/p_mr), (2*J)+1 ) * pow(BWbf,2);
    if (nEvt <= nPrintEvt) std::cout << "EvtXtoD0D0Bpi0::Gamma called with result: " << Gamma << std::endl;
    return Gamma;
}

// Normalized to z = (r*q_0)^2 = 1, where q_0 = q(m_ab = m_r)
double EvtXtoD0D0Bpi0::Barrier( const int Spin, const double& d , const double& q_ab, const double& q_r)
{
	const double z = d*d*q_ab*q_ab;
	const double z0 = d*d*q_r*q_r;
	double F;
	if      (Spin == 2) F = sqrt((((z0-3.0)*(z0-3.0))+(9.0*z0))/(((z-3.0)*(z-3.0))+(9.0*z)));
	else if (Spin == 1) F = sqrt((1.0+z0)/(1.0+z));
	else if (Spin == 0) F = 1.0;
	else{
	    std::cout << "ERROR: Spin > 2" << std::endl;
	    exit(1);
	}
	if (nEvt <= nPrintEvt) std::cout << "EvtXtoD0D0Bpi0::Barrier (Normalized to z = (r*q_0)^2 = 1, where q_0 = q(m_ab = m_r)) called with result: " << F << std::endl;
    return F;
}

// Normalized to z = (r*q)^2 = 1
double EvtXtoD0D0Bpi0::Barrier( const int Spin, const double& d , const double& q_ab)
{
	const double z = d*d*q_ab*q_ab;
	double F;
	if      (Spin == 2) F = sqrt((13.0*z*z)/(((z-3.0)*(z-3.0))+(9.0*z)));
	else if (Spin == 1) F = sqrt((2.0*z)/(1.0+z));
	else if (Spin == 0) F = 1.0;
	else{
	    std::cout << "ERROR: Spin > 2" << std::endl;
	    exit(1);
	}
	if (nEvt <= nPrintEvt) std::cout << "EvtXtoD0D0Bpi0::Barrier (Normalized to z = (r*q)^2 = 1)) called with result: " << F << std::endl;
    return F;
}

// Derived by Hippel and Quigg, Phys. Rev. D 5 (1972) 624.
// Used e.g. in JHEP 05 (2017) 143
double EvtXtoD0D0Bpi0::BarrierHQ( const int Spin, const double& d , const double& q_ab)
{
	const double z = d*d*q_ab*q_ab; // z = (r*|q|)^2
	double F;
	if      (Spin == 2) F = sqrt( 1.0 / (9.0 + 3.0*z + z*z) );
	else if (Spin == 1) F = sqrt( 1.0 / (1.0 + z) );
	else if (Spin == 0) F = 1.0;
	else{
	    std::cout << "ERROR: Spin > 2" << std::endl;
	    exit(1);
	}
	if (nEvt <= nPrintEvt) std::cout << "EvtXtoD0D0Bpi0::Barrier (Hipple and Quigg) called with result: " << F << std::endl;
    return F;
}

// Previous function, but now divided by the previous function evaluated at q_0
double EvtXtoD0D0Bpi0::BarrierHQ( const int Spin, const double& d , const double& q_ab, const double& q_r)
{
	const double z = d*d*q_ab*q_ab; // z = (r*|q|)^2
	const double z0 = d*d*q_r*q_r; // z0 = (r*|q0|)^2
	double F;
	if      (Spin == 2) F = sqrt( 1.0 / (9.0 + 3.0*z + z*z) ) / sqrt( 1.0 / (9.0 + 3.0*z0 + z0*z0) );
	else if (Spin == 1) F = sqrt( 1.0 / (1.0 + z) ) / sqrt( 1.0 / (1.0 + z0) ) ;
	else if (Spin == 0) F = 1.0;
	else{
	    std::cout << "ERROR: Spin > 2" << std::endl;
	    exit(1);
	}
	if (nEvt <= nPrintEvt) std::cout << "EvtXtoD0D0Bpi0::Barrier (Hipple and Quigg at q, divided by Hipple and Quigg at q_0) called with result: " << F << std::endl;
    return F;
}

EvtTensor4C EvtXtoD0D0Bpi0::P1(const EvtVector4R& p4)
{
    EvtTensor4C g_uv,P1_uv;  // remember, the tensor g_μν = the tensor g^μν, and here P1_uv = P1^μν

    // The metric tensor g^μν
    g_uv.setdiag(1.0,-1.0,-1.0,-1.0); 

    EvtVector4R p_u = p4; // just so I can keep track, this is p^μ
    EvtVector4R p_v = p4; // just so I can keep track, this is p^ν
    double M2 = p4.mass2(); // this is M^2

    // note that T=directProd(k,p) has components T^μν = k^μ p^ν
    P1_uv =    (
                    EvtGenFunctions::directProd(p_u,p_v) * (1 / M2)
               +
                    ( -1 ) * g_uv
               );

    return P1_uv;
}


EvtVector4C EvtXtoD0D0Bpi0::L1(const EvtVector4R& p4, const EvtVector4R& q4)
{
    EvtTensor4C P1_uv; // P1_uv = P1^μν
    EvtVector4C L1_u; // L1_u = L1^μ

    // note that L = P.cont2(q) means L^μ = P^μν q_ν
    EvtVector4R q4_v = q4; // just so I can keep track
    P1_uv = P1(p4);
    L1_u  = (-1) * P1_uv.cont2(q4_v); 

    return L1_u;
}

EvtTensor4C EvtXtoD0D0Bpi0::L2(const EvtVector4R& p4, const EvtVector4R& q4)
{
    EvtTensor4C L2_ab;

    // Let's see if we can construct the L2(X) tensor
    EvtVector4C L1_a = L1(p4,q4); // just so I can keep track
    EvtVector4C L1_b = L1(p4,q4); // just so I can keep track
    EvtTensor4C P1_ab = P1(p4); // just so I can keep track 
    EvtTensor4C P1_uv = P1(p4); // just so I can keep track
    EvtVector4R q4_u = q4; // just so I can keep track
    EvtVector4R q4_v = q4; // just so I can keep track

    // note that T=directProd(k,p) has components T^μν = k^μ p^ν
    // presume (check) that T_μν = k_μ p_ν = T^μν = k^μ p^ν
    // note that L = P.cont2(q) means L^μ = P^μν q_ν
    // presume (check) that L = P.cont2(q) also means L_μ = P_μν q^ν
    L2_ab = EvtGenFunctions::directProd(L1_a,L1_b) - (1.0/3.0) * P1_ab * cont(P1_uv,EvtGenFunctions::directProd(q4_u,q4_v));

    return L2_ab;
}
