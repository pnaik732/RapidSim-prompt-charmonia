#include "TCanvas.h"
#include "TROOT.h"
#include "TH1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"

void doubler(){
   TFile f("LHCc14.root");
   TH1D *pT_ = (TH1D*)f.Get("pT");
   TH1D *eta_ = (TH1D*)f.Get("eta");
   TFile g("LHCx14.root","RECREATE");
   int bins = pT_->GetNbinsX();
   TH1D pT("pT", "", bins, pT_->GetXaxis()->GetXmin(), pT_->GetXaxis()->GetXmax());
   int fetchbins = (int) bins / 2; 
   for (int i = fetchbins; i>0; i--)
   {
     double get = pT_->GetBinContent(i);
     pT.SetBinContent(i*2,get);
     pT.SetBinContent(i*2-1,get);
   }
   TH1D eta = (*eta_);
   gDirectory->ls();
   g.Write();
}
