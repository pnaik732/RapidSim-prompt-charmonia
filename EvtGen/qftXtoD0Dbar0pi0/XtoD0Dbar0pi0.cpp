// XtoD0D0bar0pi0.cpp
// Paras Naik with assistance from Jeremy Dalseno

#include <iostream>
#include <fstream>

#include "TCanvas.h"
#include "TFile.h"
#include "TGenPhaseSpace.h"
#include "TH1.h"
#include "TH2.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#include "TRandom.h"
#include "TStyle.h"
#include "TTree.h"
#include "TPaveStats.h"

#include "include/qft++.h"

double gen_amp2( const double& X_mass,
		 const double& Dst0_mass, const double& Dst0_width );

void generate_flat_event( TGenPhaseSpace& generator );

int main()
{
  const double X_mass = 3.87169;
  const double Dst0_mass = 2.00685;
  //const double Dst0_width  = 0.000043; // realistic physical width
                                       // from Voloshin 2013 paper
  const double Dst0_width  = 0.0021;   // current upper limit
                                       // for testing only! (e.g. Comparison with EvtGen)

  double int_pdf = gen_amp2( X_mass, Dst0_mass, Dst0_width );

  std::cout << "int_pdf: " << int_pdf << std::endl;

  return 0;
}

Vector4<double> ROOTtoqft( const TLorentzVector& pROOT )
{
  const Vector4<double> pqft( pROOT.E(), pROOT.Px(), pROOT.Py(), pROOT.Pz() );

  return pqft;
}

double get_q( const double& mab, const double& ma, const double& mb )
{
  const double mab2 = mab*mab;
  const double ma_p_mb2 = (ma + mb)*(ma + mb);
  const double ma_m_mb2 = (ma - mb)*(ma - mb);

  const double q = sqrt((mab2-ma_p_mb2)*(mab2-ma_m_mb2))/(2.0*mab);

  return q;
}

double bwbf( const double& q, const double& d, const unsigned int& L )
{
  //Particle "radius" in (GeV/c)^-1
  //const double d = 1.0;
  const double z = q*q*d*d;

  double B;
  if( L == 0 )
    B = 1.0;
  else if( L == 1 )
    B = sqrt((2.0*z)/(1.0+z));
  else if( L == 2 )
    B = sqrt((13.0*z*z)/(((z-3.0)*(z-3.0))+(9.0*z)));
  else{
    std::cout << "ERROR: L>2" << std::endl;
    exit(1);
  }

  return B;
}

double bwbf( const double& q, const double& q0, const double& d, const unsigned int& L )
{
  //Particle "radius" in (GeV/c)^-1
  //const double d = 1.0;
  const double z = q*q*d*d;
  const double z0 = q0*q0*d*d;

  double Bp;
  if( L == 0 )
    Bp = 1.0;
  else if( L == 1 )
    Bp = sqrt((1.0+z0)/(1.0+z));
  else if( L == 2 )
    Bp = sqrt((((z0-3.0)*(z0-3.0))+(9.0*z0))/(((z-3.0)*(z-3.0))+(9.0*z)));
  else{
    std::cout << "ERROR: L>2" << std::endl;
    exit(1);
  }

  return Bp;
}

double bwbfHQ( const double& q, const double& d, const unsigned int& L )
{
  //Particle "radius" in (GeV/c)^-1
  //const double d = 1.0;
  const double z = q*q*d*d;

  double B;
  if( L == 0 )
    B = 1.0;
  else if( L == 1 )
    B = sqrt( 1.0 / (1.0 + z) );
  else if( L == 2 )
    B = sqrt( 1.0 / (9.0 + 3.0*z + z*z) );
  else{
    std::cout << "ERROR: L>2" << std::endl;
    exit(1);
  }

  return B;
}

double bwbfHQ( const double& q, const double& q0, const double& d, const unsigned int& L )
{
  //Particle "radius" in (GeV/c)^-1
  //const double d = 1.0;
  const double z = q*q*d*d;
  const double z0 = q0*q0*d*d;

  double Bp;
  if( L == 0 )
    Bp = 1.0;
  else if( L == 1 )
    Bp = sqrt( 1.0 / (1.0 + z) ) / sqrt( 1.0 / (1.0 + z0) );
  else if( L == 2 )
    Bp = sqrt( 1.0 / (9.0 + 3.0*z + z*z) ) / sqrt( 1.0 / (9.0 + 3.0*z0 + z0*z0) );
  else{
    std::cout << "ERROR: L>2" << std::endl;
    exit(1);
  }

  return Bp;
}

std::complex<double> bw( const double& m, const double& m0,
			 const double& Gamma0,
			 const double& q, const double& q0,
			 const unsigned int& L )
{
  const double s = m*m;
  const double s0 = m0*m0;
  const double d = 1.5;

  const double Gamma =
    Gamma0*m0/m*pow(q/q0,(2*L)+1)*
    bwbfHQ(q,q0,d,L)*bwbfHQ(q,q0,d,L); // using HQ barrier factors
                                       // as in JHEP 05 (2017) 143

  const std::complex<double> bw_pdf =
    1.0/(std::complex<double>(s0 - s,-m0*Gamma));

  return bw_pdf;
}

double s23_min( const double& s12, const double& M,
                const double& m1, const double& m2, const double& m3 )
{
  const double E2star = (s12 - (m1*m1) + (m2*m2))/2.0/sqrt(s12);
  const double E3star = (M*M - s12 - (m3*m3))/2.0/sqrt(s12);

  const double s23_min =
    ((E2star + E3star)*(E2star + E3star)) -
    ((sqrt((E2star*E2star) - (m2*m2)) + sqrt((E3star*E3star) - (m3*m3)))*
     (sqrt((E2star*E2star) - (m2*m2)) + sqrt((E3star*E3star) - (m3*m3))));

  return s23_min;
}

double s23_max( const double& s12, const double& M,
                const double& m1, const double& m2, const double& m3 )
{
  const double E2star = (s12 - (m1*m1) + (m2*m2))/2.0/sqrt(s12);
  const double E3star = (M*M - s12 - (m3*m3))/2.0/sqrt(s12);

  const double s23_max =
    ((E2star + E3star)*(E2star + E3star)) -
    ((sqrt((E2star*E2star) - (m2*m2)) - sqrt((E3star*E3star) - (m3*m3)))*
     (sqrt((E2star*E2star) - (m2*m2)) - sqrt((E3star*E3star) - (m3*m3))));

  return s23_max;
}

bool inside_phsp( const double& s12, const double& s23, const double& M,
		  const double& m1, const double& m2, const double& m3 )
{
  bool phsp_ok = false;

  const double s12min = (m1 + m2)*(m1 + m2);
  const double s12max = (M - m3)*(M - m3);

  if( s12 < s12min )
    return phsp_ok;
  if( s12max < s12 )
    return phsp_ok;

  const double s23min = s23_min(s12, M, m1, m2, m3);
  const double s23max = s23_max(s12, M, m1, m2, m3);

  if( s23 < s23min )
    return phsp_ok;
  if( s23max < s23 )
    return phsp_ok;

  phsp_ok = true;

  return phsp_ok;
}

std::complex<double>
GetAmp_DstD( const TLorentzVector& p4D0,
	      const TLorentzVector& p4pi0, const TLorentzVector& p4D0B,
	      const double& X_mass, const double& Dst0_mass, const double& Dst0_width,
	      const Spin& mz )
{
  const double D0_mass = 1.86483; // PDG 2018
  const double pi0_mass = 0.1349770; // PDG 2018

  // Blatt-Weisskopf barrier factors
  const TLorentzVector p4D0pi0 = p4D0 + p4pi0;
  const TLorentzVector p43pi = p4D0pi0 + p4D0B;

  const double q_X = get_q(p43pi.M(), p4D0pi0.M(), p4D0B.M());
  const double q0_X = get_q(X_mass, Dst0_mass, D0_mass);
  const double q_Dst0 = get_q(p4D0pi0.M(), D0_mass, pi0_mass);
  const double q0_Dst0 = get_q(Dst0_mass, D0_mass, pi0_mass);

  // "Unnormalized" barrier factors
  // const double B_0 = bwbf(q_X, 1.5, 0)*bwbf(q_Dst0, 1.5, 1);
  // const double B_2 = bwbf(q_X, 1.5, 2)*bwbf(q_Dst0, 1.5, 1); // PN:  this looks like D-wave

  // pre-HQ
  // Use normalized barrier factors in a covariant tensor formalism
  // const double B_0 = bwbf(q_X, q0_X, 1.5, 0)*bwbf(q_Dst0, q0_Dst0, 1.5, 1);
  // const double B_2 = bwbf(q_X, q0_X, 1.5, 2)*bwbf(q_Dst0, q0_Dst0, 1.5, 1); // PN:  this looks like D-wave

  // We use standard HQ barrier factors (see JHEP 05 (2017) 143)
  const double B_0 = bwbfHQ(q_X, 1.5, 0)*bwbfHQ(q_Dst0, 1.5, 1);
  const double B_2 = bwbfHQ(q_X, 1.5, 2)*bwbfHQ(q_Dst0, 1.5, 1); // PN:  this looks like D-wave

  // Zemach tensor
  const Vector4<double> pqft4P0 = ROOTtoqft(p4D0);
  const Vector4<double> pqft4P1 = ROOTtoqft(p4pi0);
  const Vector4<double> pqft4P2 = ROOTtoqft(p4D0B);

  const Vector4<double> pqft4P0P1P2 = pqft4P0+pqft4P1+pqft4P2;
  const Vector4<double> pqft4P0P1 = pqft4P0+pqft4P1;

  const Spin S_1(1);
  PolVector eps_A(S_1); //Spin-1 [Axial = X]
  PolVector eps_V(S_1); //Spin-1 [normal = D*]
  eps_A.SetP4(pqft4P0P1P2, pqft4P0P1P2.M()); //Off-shell
  eps_V.SetP4(pqft4P0P1, pqft4P0P1.M()); //Off-shell

  OrbitalTensor L2_A(2);
  OrbitalTensor L1_V(1);

  L2_A.SetP4(pqft4P0P1, pqft4P2); // X -> D* D0B
  L1_V.SetP4(pqft4P0, pqft4P1); // D* -> D0 pi0

//  const Tensor< complex<double> > SF_DtoAP0_AtoVP1_VtoP2P3 = eps_A(mz)*(eps_V.Projector()*(pqft4P0-pqft4P1));//S-wave
//  const Tensor< complex<double> > SF_DtoAP0_AtoVP1_VtoP2P3 = eps_A(mz)*(pqft4P0P1-pqft4P2)*(pqft4P0P1P2*(eps_V.Projector()*(pqft4P0-pqft4P1)));//D-wave

  complex<double> as = std::complex<double>(1,0);
  complex<double> ad = std::complex<double>(0,0);

  const Tensor< complex<double> > SF_AtoVP1_VtoP2P3_0 =
	as * eps_A(mz) * L1_V ;
  const Tensor< complex<double> > SF_AtoVP1_VtoP2P3_2 =
	ad * eps_A(mz) * (L2_A | L1_V);

//  const double Z = SF_DtoAP0_AtoVP1_VtoP2P3().real();

  const complex<double> Z_0 = SF_AtoVP1_VtoP2P3_0();
  const complex<double> Z_2 = SF_AtoVP1_VtoP2P3_2();

  // Line shape
  const std::complex<double> T =
    bw( p4D0pi0.M(), Dst0_mass, Dst0_width, q_Dst0, q0_Dst0, 1);

  return B_0*Z_0*T + B_2*Z_2*T;
}

double gen_amp2( const double& X_mass,
		 const double& Dst0_mass, const double& Dst0_width )
{
  const unsigned int nevents = 320000;

  const unsigned int bins = 300;
  const double plot_ll = 3.995;
  const double plot_ul = 4.035;

  TH2D *hdp_plotAmp = new TH2D( Form("h_pdf%f",X_mass), "",
		    bins, plot_ll, plot_ul,
			bins, plot_ll, plot_ul ); // plot the PDF

  TH2D *hdp = new TH2D( Form("h_ev%f",X_mass), "",
		    bins, plot_ll, plot_ul,
			bins, plot_ll, plot_ul ); // generate points on the Dalitz plot

  const double D0_mass = 1.86483; // PDG 2018
  const double pi0_mass = 0.1349770; // PDG 2018

  TLorentzVector X(0.0, 0.0, 0.0, X_mass);
  const std::vector<double> masses = {D0_mass, pi0_mass, D0_mass};

  gRandom->SetSeed(0);
  TGenPhaseSpace event;
  TGenPhaseSpace generator;
  event.SetDecay(X, masses.size(), masses.data());
  generator.SetDecay(X, masses.size(), masses.data());

  const double amp2_max = 1.0;
  double int_phsp = 0.0;
  double pdf_max = 0.0;
  for( unsigned int i=0; i<nevents; i++){
	if (i%int(nevents/10) == 0) std::cout << i << " of " << nevents << " events generated" << std::endl;
    TLorentzVector p4D0, p4pi0, p4D0B;
    while(true){
      const double weight = event.Generate();
      const double height = gRandom->Uniform(amp2_max/weight);
      const double amp2 = 1.0;

      if( height < amp2 ){
	    p4D0 = *(event.GetDecay(0));
	    p4pi0  = *(event.GetDecay(1));
	    p4D0B = *(event.GetDecay(2));
	    break;
      }
      if( amp2 > amp2_max ){
	std::cout << "ERROR: PDF above determined maximum." << std::endl;
	std::cout << amp2 << " > " << amp2_max << std::endl;
	exit(1);
      }
    }

    const TLorentzVector p4D0pi0 = p4D0+p4pi0;
    const TLorentzVector p4D0Bpi0 = p4D0B+p4pi0;

    double pdf = 0.0;
    for( Spin mz = -1; mz <= +1; mz++ ){
      const std::complex<double> amp_DstD =
//    GetAmp_DstD( p4D0, p4pi0, p4D0B, X_mass, Dst0_mass, Dst0_width, mz ) +
//	  GetAmp_DstD( p4D0B, p4pi0, p4D0, X_mass, Dst0_mass, Dst0_width, mz );
	  GetAmp_DstD( p4D0, p4pi0, p4D0B, X_mass, Dst0_mass, Dst0_width, mz ) ; // only D*D

      //Intensity is the sum over spins of ***|amp|^2*** (see qft++ paper)
      pdf += std::norm(amp_DstD); // norm(amp_DstD) = |amp_DstD|^2
    }
    int_phsp += pdf;
    hdp_plotAmp->Fill(p4D0pi0.M2(), p4D0Bpi0.M2(), pdf);
    if (pdf > pdf_max) pdf_max = pdf;
  }
  std::cout << nevents << " events generated" << std::endl;

  std::cout << "pdf_max = " << pdf_max << std::endl;

  double wiggle = 1.1;

  for( unsigned int i=0; i<nevents; i++){
	if (i%int(nevents/10) == 0) std::cout << i << " of " << nevents << " events generated" << std::endl;
	TLorentzVector p4D0, p4pi0, p4D0B;
	TLorentzVector p4D0pi0, p4D0Bpi0;
    while(true){
      generate_flat_event(generator);
      const double height = gRandom->Uniform(wiggle*pdf_max);
	  p4D0 = *(generator.GetDecay(0));
	  p4pi0  = *(generator.GetDecay(1));
	  p4D0B = *(generator.GetDecay(2));
	  p4D0pi0 = p4D0+p4pi0;
	  p4D0Bpi0 = p4D0B+p4pi0;
      double pdf = 0.0;
      for( Spin mz = -1; mz <= +1; mz++ ){
        const std::complex<double> amp_DstD =
  	      GetAmp_DstD( p4D0, p4pi0, p4D0B, X_mass, Dst0_mass, Dst0_width, mz ) ; // only D*D
        //Intensity is the sum over spins of ***|amp|^2*** (see qft++ paper)
        pdf += std::norm(amp_DstD); // norm(amp_DstD) = |amp_DstD|^2
      }
      if (pdf > wiggle*pdf_max){
    	std::cout << "ERROR: PDF above 'wiggle' * the determined maximum. Consider increasing 'wiggle'." << std::endl;
    	std::cout << " wiggle: " << wiggle << std::endl;
    	std::cout << " pdf_max " << pdf_max << std::endl;
    	std::cout << " pdf " << pdf << std::endl;
    	std::cout << pdf << " > " << wiggle*pdf_max << std::endl;
    	exit(1);
      }
      if( height < pdf ){
        // accept
	    break;
      }
    }
    hdp->Fill(p4D0pi0.M2(), p4D0Bpi0.M2());
  }
  std::cout << nevents << " events generated" << std::endl;

  TCanvas* const canvas = new TCanvas("canvas", "", 600, 600);
  canvas->SetLeftMargin(0.15);
  canvas->SetBottomMargin(0.10);
  canvas->SetRightMargin(0.16);

  hdp_plotAmp->GetXaxis()->SetTitle("m^{2}_{D^{0}#pi^{0}}");
  hdp_plotAmp->GetYaxis()->SetTitle("m^{2}_{#bar{D^{0}}#pi^{0}}");
  hdp_plotAmp->Draw("COLZ");

  canvas->Update();

  TPaveStats *stat_canvas = (TPaveStats*)(hdp_plotAmp->FindObject("stats"));
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

  canvas->Print("qft_phsp_pdf.pdf");

  TCanvas* const canvas2 = new TCanvas("canvas2", "", 600, 600);
  canvas2->SetLeftMargin(0.15);
  canvas2->SetBottomMargin(0.10);
  canvas2->SetRightMargin(0.16);

  hdp->GetXaxis()->SetTitle("m^{2}(D^{*0}#pi^{0})");
  hdp->GetYaxis()->SetTitle("m^{2}(anti-D^{*0}#pi^{0})");
  hdp->Draw("COLZ");

  canvas2->Update();

  TPaveStats *stat_canvas2 = (TPaveStats*)(hdp->FindObject("stats"));
  if (stat_canvas2) {
      // std::cout << " OLD X1NDC: " << stat_canvas2->GetX1NDC() << " X2NDC: " << stat_canvas2->GetX2NDC() ;
      // std::cout << " Y1NDC: " << stat_canvas2->GetY1NDC() << " Y2NDC: " << stat_canvas2->GetY2NDC() << std::endl;
      stat_canvas2->SetX1NDC(0.20); stat_canvas2->SetX2NDC(0.30);
      stat_canvas2->SetY1NDC(0.75); stat_canvas2->SetY2NDC(0.85);
      // std::cout << " NEW X1NDC: " << stat_canvas2->GetX1NDC() << " X2NDC: " << stat_canvas2->GetX2NDC() ;
      // std::cout << " Y1NDC: " << stat_canvas2->GetY1NDC() << " Y2NDC: " << stat_canvas2->GetY2NDC() << std::endl;
      stat_canvas2->Draw();
  }
  else {
      std::cerr << "No stats box found!\n";
  }

  canvas2->Print("qft_phsp_ev.pdf");

  //exit(1); // Not sure why this is here

  return int_phsp;
}

void generate_flat_event( TGenPhaseSpace& generator )
{
  while(true){
    const double weight = generator.Generate();
    const double height = gRandom->Uniform(1.0/weight);
    if( height < 1.0 )
      break;
  }
}
