#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"
#include "iostream"
#include "rootlogonATLAS.h"

  
  void width_700V(){
    TGraph *cs = new TGraph("RSRun10Oct18ATLAS12UnirradChipGainCheckColdScaled_0/700V_width_output_PF.txt");
    TGraph *cu = new TGraph("RSRun10Oct18ATLAS12UnirradChipGainCheckColdUnscaled_0/700V_width_output_PF.txt");
    TGraph *is = new TGraph("RSRun10Oct18ATLAS12UnirradChipGainCheckIntermediateScaled_0/700V_width_output_PF.txt");
    TGraph *iu = new TGraph("RSRun10Oct18ATLAS12UnirradChipGainCheckIntermediateUnscaled_0/700V_width_output_PF.txt");
    TGraph *ws = new TGraph("RSRun10Oct18ATLAS12UnirradChipGainCheckWarmScaled_0/700V_width_output_PF.txt");
    TGraph *wu = new TGraph("RSRun10Oct18ATLAS12UnirradChipGainCheckWarmUnscaled_0/700V_width_output_PF.txt");

    cs->SetMarkerColor(kBlack);
    cu->SetMarkerColor(kBlack);
    ws->SetMarkerColor(kRed);
    wu->SetMarkerColor(kRed);
    is->SetMarkerColor(kBlue);
    iu->SetMarkerColor(kBlue);

    cs->SetMarkerSize(2);
    cu->SetMarkerSize(2);
    ws->SetMarkerSize(2);
    wu->SetMarkerSize(2);
    is->SetMarkerSize(2);
    iu->SetMarkerSize(2);
  
    cs->SetMarkerStyle(22);
    cu->SetMarkerStyle(23);
    ws->SetMarkerStyle(22);
    wu->SetMarkerStyle(23);
    is->SetMarkerStyle(22);
    iu->SetMarkerStyle(23);

    TMultiGraph *m = new TMultiGraph();
    m->Add(cs,"p");
    m->Add(cu,"p");
    m->Add(is,"p");
    m->Add(iu,"p");
    m->Add(ws,"p");
    m->Add(wu,"p");
    

    TLegend *leg = new TLegend(0.7,0.2,0.9,0.4);
    leg->AddEntry(cs,"cold scaled","p");
    leg->AddEntry(cu,"cold unscaled","p");
    leg->AddEntry(is,"intermediate scaled","p");
    leg->AddEntry(iu,"intermediate unscaled","p");
    leg->AddEntry(ws,"warm scaled","p");
    leg->AddEntry(wu,"warm unscaled","p");
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->SetTextSize(0.035);
    leg->SetFillStyle(1000);
    leg->SetTextFont(42);
    leg->SetNColumns(1);

    TCanvas *cluster = new TCanvas("cluster_700V","cluster_700V",600,600);
    m->Draw("ALP");
    leg->Draw("ALP");
    m->GetXaxis()->SetTitle("Relative Cluster Size");
    m->GetYaxis()->SetTitle("");
    m->SetTitle("");
    gPad->RedrawAxis();
  }

void ChipGainCheck(){

  rootlogonATLAS();
  TGaxis::SetMaxDigits(3);
  
  TGraphErrors *CCE_coldScaled = new TGraphErrors("RSRun10Oct18ATLAS12UnirradChipGainCheckColdScaled_0/CCE_output_PF.txt");
  TGraphErrors *CCE_intermediateScaled = new TGraphErrors("RSRun10Oct18ATLAS12UnirradChipGainCheckIntermediateScaled_0/CCE_output_PF.txt");
  TGraphErrors *CCE_warmScaled = new TGraphErrors("RSRun10Oct18ATLAS12UnirradChipGainCheckWarmScaled_0/CCE_output_PF.txt");
  
  TGraphErrors *CCE_coldUnscaled = new TGraphErrors("RSRun10Oct18ATLAS12UnirradChipGainCheckColdUnscaled_0/CCE_output_PF.txt");
  TGraphErrors *CCE_intermediateUnscaled = new TGraphErrors("RSRun10Oct18ATLAS12UnirradChipGainCheckIntermediateUnscaled_0/CCE_output_PF.txt");
  TGraphErrors *CCE_warmUnscaled = new TGraphErrors("RSRun10Oct18ATLAS12UnirradChipGainCheckWarmUnscaled_0/CCE_output_PF.txt");

  CCE_coldScaled->SetMarkerColor(kBlack);
  CCE_coldUnscaled->SetMarkerColor(kBlack);
  CCE_warmScaled->SetMarkerColor(kRed);
  CCE_warmUnscaled->SetMarkerColor(kRed);
  CCE_intermediateScaled->SetMarkerColor(kBlue);
  CCE_intermediateUnscaled->SetMarkerColor(kBlue);

  CCE_coldScaled->SetMarkerSize(2);
  CCE_coldUnscaled->SetMarkerSize(2);
  CCE_warmScaled->SetMarkerSize(2);
  CCE_warmUnscaled->SetMarkerSize(2);
  CCE_intermediateScaled->SetMarkerSize(2);
  CCE_intermediateUnscaled->SetMarkerSize(2);
  
  CCE_coldScaled->SetMarkerStyle(22);
  CCE_coldUnscaled->SetMarkerStyle(23);
  CCE_warmScaled->SetMarkerStyle(22);
  CCE_warmUnscaled->SetMarkerStyle(23);
  CCE_intermediateScaled->SetMarkerStyle(22);
  CCE_intermediateUnscaled->SetMarkerStyle(23);

  TMultiGraph *mg = new TMultiGraph();
  mg->GetXaxis()->SetTitle("Bias Voltage [V]");
  mg->GetYaxis()->SetTitle("Collected Charge [ADC]");
  mg->SetTitle("");
  mg->Add(CCE_coldScaled,"p");
  mg->Add(CCE_coldUnscaled,"p");
  mg->Add(CCE_intermediateScaled,"p");
  mg->Add(CCE_intermediateUnscaled,"p");
  mg->Add(CCE_warmScaled,"p");
  mg->Add(CCE_warmUnscaled,"p");

  TLegend *leg = new TLegend(0.7,0.2,0.9,0.4);
  leg->AddEntry(CCE_coldScaled,"cold scaled","p");
  leg->AddEntry(CCE_coldUnscaled,"cold unscaled","p");
  leg->AddEntry(CCE_intermediateScaled,"intermediate scaled","p");
  leg->AddEntry(CCE_intermediateUnscaled,"intermediate unscaled","p");
  leg->AddEntry(CCE_warmScaled,"warm scaled","p");
  leg->AddEntry(CCE_warmUnscaled,"warm unscaled","p");
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(1000);
  leg->SetTextFont(42);
  leg->SetNColumns(1);
  
  TCanvas *CCE = new TCanvas("CCE","CCE",600,600);
  mg->Draw("ALP");
  leg->Draw("ALP");

  width_700V();
  
}
