void marginReset(TCanvas *canvas, Double_t pLeft = 0.125, Double_t pRight = 0.075, Double_t pTop = 0.065, Double_t pBottom = 0.175)
{
  canvas->SetLeftMargin(pLeft);
  canvas->SetBottomMargin(pBottom);
  canvas->SetRightMargin(pRight);
  canvas->SetTopMargin(pTop);
}

void makePlots_style(Double_t pTSize = 0.055, Double_t pTSizeMultiplierX = 1.20, Double_t pOffsetX = 1.05, Double_t pTSizeMultiplierY = 1.20, Double_t pOffsetY = 0.90, Int_t pFont = 132, Double_t pWidth = 1.50, Double_t pLeft = 0.125, Double_t pRight = 0.075, Double_t pTop = 0.065, Double_t pBottom = 0.175)
{

  // define names for colours
  Int_t black  = 1;
  Int_t red    = 2;
  Int_t green  = 3;
  Int_t blue   = 4;
  Int_t yellow = 5; 
  Int_t magenta= 6;
  Int_t cyan   = 7;
  Int_t purple = 9;
  

// "Landscape histograms":
//
// The style here is designed for more or less square plots.
// For longer histograms, or canvas with many pads, adjustements are needed. 
// For instance, for a canvas with 1x5 histograms:
//  TCanvas* c1 = new TCanvas("c1", "L0 muons", 600, 800);
//  c1->Divide(1,5);
//  Adaptions like the following will be needed:
//  gStyle->SetTickLength(0.05,"x");
//  gStyle->SetTickLength(0.01,"y");
//  gStyle->SetLabelSize(0.15,"x");
//  gStyle->SetLabelSize(0.1,"y");
//  gStyle->SetStatW(0.15);
//  gStyle->SetStatH(0.5);
//
///////////////////////////////////////////////////////////////////

  // Use times new roman, precision 2
  //Int_t pFont        = 132;
  // Line thickness
  //Double_t pWidth    = 1.50;
  // Text size
  //Double_t pTSize    = 0.055;
  
  // use plain black on white colors
  //gROOT->SetStyle("Plain"); 
  //TStyle *pStyle= new TStyle("pStyle","plots style");
  
  //pStyle->SetErrorX(0); //  don't suppress the error bar along X

  /*
  gStyle->SetFillColor(1);
  gStyle->SetFillStyle(1001);   // solid
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetStatColor(0);
  gStyle->SetLegendBorderSize(0);
  */

  /*
  // If you want the usual gradient palette (blue -> red)
  gStyle->SetPalette(1);
  // If you want colors that correspond to gray scale in black and white:
  int colors[8] = {0,5,7,3,6,2,4,1};
  gStyle->SetPalette(8,colors);
  */

  // set the paper & margin sizes
  //gStyle->SetPaperSize(20,26);
  gStyle->SetPadTopMargin(pTop);
  gStyle->SetPadRightMargin(pRight); // increase for colz plots
  gStyle->SetPadBottomMargin(pBottom);
  gStyle->SetPadLeftMargin(pLeft);  

  // use large fonts
  gStyle->SetTextFont(pFont);
  gStyle->SetTextSize(pTSize);
  gStyle->SetLabelFont(pFont,"x");
  gStyle->SetLabelFont(pFont,"y");
  gStyle->SetLabelFont(pFont,"z");
  gStyle->SetLabelSize(pTSize,"x");
  gStyle->SetLabelSize(pTSize,"y");
  gStyle->SetLabelSize(pTSize,"z");
  gStyle->SetTitleFont(pFont);
  gStyle->SetTitleFont(pFont,"x");
  gStyle->SetTitleFont(pFont,"y");
  gStyle->SetTitleFont(pFont,"z");
  gStyle->SetTitleSize(pTSizeMultiplierX*pTSize,"x");
  gStyle->SetTitleSize(pTSizeMultiplierY*pTSize,"y");
  gStyle->SetTitleSize(1.2*pTSize,"z");

  // use medium bold lines and thick markers
  gStyle->SetLineWidth(pWidth);
  gStyle->SetFrameLineWidth(pWidth);
  gStyle->SetHistLineWidth(pWidth);
  gStyle->SetFuncWidth(pWidth);
  gStyle->SetGridWidth(pWidth);
  gStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(1.0);

  // label offsets
  gStyle->SetLabelOffset(0.005,"X"); // was .010
  gStyle->SetLabelOffset(0.005,"Y");

  // by default, do not display histogram decorations:
  //gStyle->SetOptStat(0);  
  //gStyle->SetOptStat("emr");  // show only nent -e , mean - m , rms -r
  // full opts at http://root.cern.ch/root/html/TStyle.html#TStyle:SetOptStat
  gStyle->SetStatFormat("6.3g"); // specified as c printf options
  gStyle->SetOptTitle(0);
  gStyle->SetOptFit(0);
  //gStyle->SetOptFit(1011); // order is probability, Chi2, errors, parameters
  //titles
  gStyle->SetTitleOffset(pOffsetX,"X"); 
  gStyle->SetTitleOffset(pOffsetY,"Y"); 
  gStyle->SetTitleOffset(1.2,"Z");
  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleFont(pFont,"title");
  gStyle->SetTitleX(0.0);
  gStyle->SetTitleY(1.0); 
  gStyle->SetTitleW(1.0);
  gStyle->SetTitleH(0.05);
  
  // look of the statistics box:
  gStyle->SetStatBorderSize(0);
  gStyle->SetStatFont(pFont);
  gStyle->SetStatFontSize(0.05);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.9);
  gStyle->SetStatW(0.25);
  gStyle->SetStatH(0.15);

  // put tick marks on top and RHS of plots
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  // histogram divisions: only 5 in x to avoid label overlaps
  gStyle->SetNdivisions(510,"x");
  gStyle->SetNdivisions(508,"y");
  
  //gROOT->SetStyle("pStyle");
  //gROOT->ForceStyle();
/*
  // add p label
  pName = new TPaveText(gStyle->GetPadLeftMargin() + 0.05,
                           0.87 - gStyle->GetPadTopMargin(),
                           gStyle->GetPadLeftMargin() + 0.20,
                           0.95 - gStyle->GetPadTopMargin(),
                           "BRNDC");
  pName->AddText("p");
  pName->SetFillColor(0);
  pName->SetTextAlign(12);
  pName->SetBorderSize(0);
*/
  TText *pLabel = new TText();
  pLabel->SetTextFont(pFont);
  pLabel->SetTextColor(1);
  pLabel->SetTextSize(pTSize);
  pLabel->SetTextAlign(12);

  TLatex *pLatex = new TLatex();
  pLatex->SetTextFont(pFont);
  pLatex->SetTextColor(1);
  pLatex->SetTextSize(pTSize);
  pLatex->SetTextAlign(12);

}
