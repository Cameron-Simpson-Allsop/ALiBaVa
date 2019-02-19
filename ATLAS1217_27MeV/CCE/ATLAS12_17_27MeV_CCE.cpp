#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "rootlogonATLAS.h"

void ATLAS12_17_27MeV_CCE()
{
  rootlogonATLAS();
  std::vector<string> DirNames{"Pre-Annealing/ATLAS12_p1_PreAnnealing/","Post-Annealing/ATLAS12_p1_PostAnnealing/","Pre-Annealing/ATLAS12_p2_PreAnnealing/","Post-Annealing/ATLAS12_p2_PostAnnealing/","Pre-Annealing/ATLAS17_mini3_PreAnnealing/","Post-Annealing/ATLAS17_mini3_PostAnnealing/"};
  std::vector<string> fluences{"4.25e14","4.25e14","7.18e14","7.18e14","3.54e14","3.54e14"};
  TMultiGraph *mg = new TMultiGraph();
  TLegend *IVleg = new TLegend(0.45,0.17,0.75,0.32);
  int pre_i{1};
  int post_i{1};

  for(int i{0}; i<DirNames.size(); ++i)
    {
      TString filePath = DirNames[i] + "CCE_output_PF_ke.txt";
      TString Directory = DirNames[i];
      TString fluence = fluences[i];
      std::string sfilePath = DirNames[i] + "CCE_output_PF_ke.txt";
      std::size_t preanneal = sfilePath.find("Pre-Annealing");
      std::size_t postanneal = sfilePath.find("Post-Annealing");
      std::size_t ATLAS12 = sfilePath.find("ATLAS12");
      std::size_t ATLAS17 = sfilePath.find("ATLAS17");
      TGraphErrors *g = new TGraphErrors(filePath);
      g->SetMarkerSize(1.5);
      if(preanneal != std::string::npos && postanneal == std::string::npos)
	{
	  g->SetMarkerStyle(20);
	  if(pre_i!=4)	    
	    {
	      g->SetMarkerColor(pre_i);
	      g->SetLineColor(pre_i);
	      ++pre_i;
	    }
	  else if(pre_i==4)
	    {
	      ++pre_i;
	      g->SetMarkerColor(pre_i);
	      g->SetLineColor(pre_i);
	    }
	  if(ATLAS12 != std::string::npos)
	    {
	      TString tmp = "Pre-Annealing ATLAS12 " + fluence + " n_{eq}/cm^{2}";
	      IVleg->AddEntry(g,tmp,"lp");
	    }
	  else if(ATLAS17 != std::string::npos)
	    {
	      TString tmp = "Pre-Annealing ATLAS17 " + fluence + " n_{eq}/cm^{2}";
	      IVleg->AddEntry(g,tmp,"lp");
	    }
	}
      if(postanneal != std::string::npos && preanneal == std::string::npos)
	{
	  g->SetMarkerStyle(21);
	  if(post_i!=4)	    
	    {
	      g->SetMarkerColor(post_i);
	      g->SetLineColor(post_i);
	      ++post_i;
	    }
	  else if(post_i==4)
	    {
	      ++post_i;
	      g->SetMarkerColor(post_i);
	      g->SetLineColor(post_i);
	    }
	  if(ATLAS12 != std::string::npos)
	    {
	      TString tmp = "Post-Annealing ATLAS12 " + fluence + " n_{eq}/cm^{2}";
	      IVleg->AddEntry(g,tmp,"lp");
	    }
	  else if(ATLAS17 != std::string::npos)
	    {
	      TString tmp = "Post-Annealing ATLAS17 " + fluence + " n_{eq}/cm^{2}";
	      IVleg->AddEntry(g,tmp,"lp");
	    }
	}
      mg->Add(g,"p");
    }

  TCanvas *can = new TCanvas("ATLAS_27MeV_CCE","ATLAS_27MeV_CCE",600,600);  
  mg->GetYaxis()->SetTitle("CCE [ke]");
  mg->GetXaxis()->SetTitle("Bias [-kV]");
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetXaxis()->SetRangeUser(0,1);
  can->SetTopMargin(0.08);
  can->SetRightMargin(0.1);
  can->SetLeftMargin(0.15);
  TGaxis::SetMaxDigits(3);
  mg->Draw("AP");
  IVleg->SetBorderSize(0);
  IVleg->SetFillColor(0);
  IVleg->SetTextSize(0.02);
  IVleg->SetFillStyle(1000);
  IVleg->SetTextFont(42);
  IVleg->SetNColumns(1);
  IVleg->Draw("same");
  can->SaveAs("ATLAS12_17_CCE_27MeV.pdf");
  
}
