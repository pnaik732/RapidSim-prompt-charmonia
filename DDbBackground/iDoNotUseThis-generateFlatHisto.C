#include "TCanvas.h"
#include "TROOT.h"
#include "TH1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"

void generateFlatHisto(){
   TFile g("FlatBackground.root","RECREATE");
   TH1D M_DD("M_DD", "", 20, 3.700, 3.900);
   int bins = M_DD.GetNbinsX();
   M_DD.SetBinContent(1,1.0);
   M_DD.SetBinContent(bins,1.0);
   for (int i = bins-1; i>1; i--)
   {
     M_DD.SetBinContent(i,1.0);
   }
   gDirectory->ls();
   g.Write();
}
