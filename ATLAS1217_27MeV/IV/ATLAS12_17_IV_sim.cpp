#include <iostream>
#include <vector>
#include "rootlogonATLAS.h"

struct Data
{
  std::vector<double> current_max;
  std::vector<double> phi_max;
  std::vector<double> current_min;
  std::vector<double> phi_min;
};

Data CurrentvFluence()
{
  Data data;
  double phi;
  double ephi;
  double current;
  double ecurrent;
  double a = 3.99e-17; //Acm^-1
  double ea = 0.03e-17; //Acm^-1
  double l = 0.8; //cm
  double w = 0.03; //cm
  int N=1000;
  
  for(int i{0}; i<N; ++i)
    {
      phi = i*1e12;
      ephi = phi*0.15;
      current = a*pow(l,2)*w*phi;
      ecurrent = pow(pow(pow(l,2)*w*phi*ea,2) + pow(a*pow(l,2)*w*ephi,2),2);

      data.current_max.push_back((current+ecurrent)*1e6);
      data.current_min.push_back((current-ecurrent)*1e6);
      data.phi_max.push_back(phi+ephi);
      data.phi_min.push_back(phi-ephi);
    }
  
  return data;
}

void GraphSettings(TGraph *g, TString xtitle, TString ytitle)
{
  g->SetTitle("");
  g->GetXaxis()->SetTitle(xtitle);
  g->GetXaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetTitle(ytitle);
  g->GetYaxis()->SetTitleOffset(1.2);
  g->SetMarkerStyle(20);
  g->SetMarkerSize(0.3);
}

void ATLAS12_17_IV_sim()
{
  rootlogonATLAS();
  Data data = CurrentvFluence();

  TCanvas *can = new TCanvas("IvPhi","IvPhi",600,600);
  TGaxis::SetMaxDigits(3);
  can->SetRightMargin(0.12);
  can->SetTopMargin(0.06);
  can->SetBottomMargin(0.15);
  
  TGraph *g_IvPhi_max = new TGraph(data.phi_max.size(), &(data.phi_max[0]), &(data.current_max[0]));
  GraphSettings(g_IvPhi_max,"#phi [n_{eq}/cm^{2}]","I [#muA]");
  TGraph *g_IvPhi_min = new TGraph(data.phi_min.size(), &(data.phi_min[0]), &(data.current_min[0]));
  GraphSettings(g_IvPhi_min,"#phi [n_{eq}/cm^{2}]","I [#muA]");
  TGraph *g_fill = new TGraph(2*data.phi_max.size());
  for(int i{0}; i<data.phi_max.size(); ++i)
    {
      g_fill->SetPoint(i,data.phi_max[i],data.current_max[i]);
      g_fill->SetPoint(i+data.phi_min.size(),data.phi_min[data.phi_min.size()-i-1],data.current_min[data.phi_min.size()-i-1]);
    }

  g_fill->SetFillStyle(3315);
  g_fill->SetFillColor(kRed);
  
  g_IvPhi_max->Draw("AL");
  g_IvPhi_min->Draw("same");
  g_fill->Draw("f");

  can->SaveAs("LeakageCurrent_vs_Fluence.pdf");
  can->Close();
}
