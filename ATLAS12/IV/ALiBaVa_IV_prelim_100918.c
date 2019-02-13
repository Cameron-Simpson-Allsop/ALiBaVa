#include "TGraph.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"
#include "iostream"

void rootlogonATLAS(double ytoff = 1.0, bool atlasmarker =true, double left_margin=0.14) 
{

TStyle* atlasStyle= new TStyle("ATLAS","Atlas style");

// use plain black on white colors
Int_t icol=0;
atlasStyle->SetFrameBorderMode(icol);
atlasStyle->SetCanvasBorderMode(icol);
atlasStyle->SetPadBorderMode(icol);
atlasStyle->SetPadColor(icol);
atlasStyle->SetCanvasColor(icol);
atlasStyle->SetStatColor(icol);
//atlasStyle->SetFillColor(icol);

// set the paper & margin sizes
atlasStyle->SetPaperSize(20,26);
atlasStyle->SetPadTopMargin(0.05);
atlasStyle->SetPadRightMargin(0.05);
atlasStyle->SetPadBottomMargin(0.16);
atlasStyle->SetPadLeftMargin(0.12);

// use large fonts
//Int_t font=72;
Int_t font=42;
Double_t tsize=0.05;
atlasStyle->SetTextFont(font);


atlasStyle->SetTextSize(tsize);
atlasStyle->SetLabelFont(font,"x");
atlasStyle->SetTitleFont(font,"x");
atlasStyle->SetLabelFont(font,"y");
atlasStyle->SetTitleFont(font,"y");
atlasStyle->SetLabelFont(font,"z");
atlasStyle->SetTitleFont(font,"z");

atlasStyle->SetLabelSize(tsize,"x");
atlasStyle->SetTitleSize(tsize,"x");
atlasStyle->SetLabelSize(tsize,"y");
atlasStyle->SetTitleSize(tsize,"y");
atlasStyle->SetLabelSize(tsize,"z");
atlasStyle->SetTitleSize(tsize,"z");


//use bold lines and markers
if ( atlasmarker ) {
  atlasStyle->SetMarkerStyle(20);
  atlasStyle->SetMarkerSize(1.2);
}
atlasStyle->SetHistLineWidth(2.);
atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

//get rid of X error bars and y error bar caps
//atlasStyle->SetErrorX(0.001);

//do not display any of the standard histogram decorations
atlasStyle->SetOptTitle(0);
//atlasStyle->SetOptStat(1111);
atlasStyle->SetOptStat(0);
//atlasStyle->SetOptFit(1111);
atlasStyle->SetOptFit(0);

// put tick marks on top and RHS of plots
atlasStyle->SetPadTickX(1);
atlasStyle->SetPadTickY(1);

//gStyle->SetPadTickX(1);
//gStyle->SetPadTickY(1);

// DLA overrides
atlasStyle->SetPadLeftMargin(left_margin);
atlasStyle->SetPadBottomMargin(0.13);
atlasStyle->SetTitleYOffset(ytoff);
atlasStyle->SetTitleXOffset(1.0);

 const Int_t NRGBs = 5;
 const Int_t NCont = 255;
 
 Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
 Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
 Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
 Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
 TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
 atlasStyle->SetNumberContours(NCont);

// Enforce the style.
gROOT->SetStyle("ATLAS");
gROOT->ForceStyle();
}

void ALiBaVa_IV_prelim_100918()
{
rootlogonATLAS();

TMultiGraph *mg1 = new TMultiGraph();
TMultiGraph *mg2 = new TMultiGraph();
TGraph *plot1 = new TGraph("Prelim_ATLAS12_nonirrad_warm_IV.txt");
TGraph *plot2 = new TGraph("Prelim_ATLAS12_nonirrad_cold_IV.txt");
TGraph *plot3 = new TGraph("Prelim_ATLAS12_preannealirrad_cold_IV_microamp.txt");
TGraph *plot4 = new TGraph("Prelim_ATLAS12_postannealirrad_cold_IV_microamp.txt");

plot1->SetLineColor(kBlue);
plot1->SetMarkerColor(kBlue);
plot2->SetLineColor(kRed);
plot2->SetMarkerColor(kRed);
plot3->SetLineColor(kBlue);
plot3->SetMarkerColor(kBlue);
plot4->SetLineColor(kRed);
plot4->SetMarkerColor(kRed);

mg1->Add(plot1,"cp");
mg1->Add(plot2,"cp");
mg2->Add(plot3,"cp");
mg2->Add(plot4,"cp");

mg1->GetXaxis()->SetTitle("Bias Voltage (V)");
mg1->GetYaxis()->SetTitle("Current (-nA)");
mg2->GetXaxis()->SetTitle("Bias Voltage (V)");
mg2->GetYaxis()->SetTitle("Current (-#muA)");

mg1->GetXaxis()->SetMaxDigits(1);
mg2->GetXaxis()->SetMaxDigits(1);

TLegend *legend1 = new TLegend(0.2,0.8,0.6,0.9);
legend1->AddEntry(plot1,"Non-Irradiated Warm","l");
legend1->AddEntry(plot2,"Non-Irradiated Cold","l");

TLegend *legend2 = new TLegend(0.2,0.8,0.5,0.9);
legend2->AddEntry(plot3,"Pre-Annealing","l");
legend2->AddEntry(plot4,"Post-Annealing","l");


TCanvas *canvas1 = new TCanvas("canvas1","ATLAS12 Non-Irradiated I-V Characteristics",600,700);
canvas1->SetRightMargin(1);
mg1->Draw("ACP");
legend1->Draw();

TCanvas *canvas2 = new TCanvas("canvas2","ATLAS12 Irradiated I-V Characteristics",600,700);
canvas2->SetRightMargin(1);
mg2->Draw("ACP");
legend2->Draw();


}
