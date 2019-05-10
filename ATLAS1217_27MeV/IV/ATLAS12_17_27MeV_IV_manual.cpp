#include <iostream>
#include <fstream>
#include <vector>
#include "rootlogonATLAS.h"

struct Data
{
  std::vector<double> voltage;
  std::vector<double> current;
  std::vector<double> currentdiff;
  std::vector<double> evoltage;
  std::vector<double> ecurrent;
};

double TempScale(double current, double T)
{
  double Ea = 1.21; //eV
  double kb = 8.6173e-5; //eVK^-1
  double Tr = 273-25; //K
  double exponent = -(Ea/(2*kb))*((1/Tr)-(1/(T+273)));
  return current;//*pow((Tr/T),2)*exp(exponent);
}

Data ReadFile(std::string filePath)
{
  Data data;
  ifstream inFile;
  inFile.open(filePath);
  int i=0;
  while(!inFile.eof())
    {
      double v, c1, c2, c3, cav, ecav, T;
      inFile >> v >> c1 >> c2 >> c3 >> T;
      //std::cout << v << "\t" << c1 << "\t" << c2 << "\t" << c3 << "\t" << T << std::endl;
      cav = ((c1+c2+c3)/3.)*pow(10,-9);
      ecav = pow((pow(c1*pow(10,-9)-cav,2)+pow(c2*pow(10,-9)-cav,2)+pow(c3*pow(10,-9)-cav,2)/2.),0.5);
      data.voltage.push_back(abs(v));
      data.evoltage.push_back(0.);
      data.current.push_back(TempScale(cav,T));
      data.ecurrent.push_back((TempScale(cav,T)/cav)*ecav);

      // std::cout<<data.voltage[i]<<"\t"<<data.current[i]<<std::endl;
      ++i;
    }  
  return data;
}

void ATLAS12_17_27MeV_IV_manual()
{
  rootlogonATLAS();
  TMultiGraph *IVmg = new TMultiGraph();
  TLegend *IVleg = new TLegend(0.5,0.15,0.8,0.3);
  
  std::vector<string> filePath{"Pre-Annealing/ATLAS17_mini3_IV_PreAnneal_manual.txt","Post-Annealing/ATLAS17_mini3_IV_PostAnneal_manual.txt","Pre-Annealing/ATLAS12_p1_IV_PreAnneal_manual.txt","Post-Annealing/ATLAS12_p1_IV_PostAnneal_manual.txt","Pre-Annealing/ATLAS12_p2_IV_PreAnneal_manual.txt","Post-Annealing/ATLAS12_p2_IV_PostAnneal_manual.txt","Pre-Annealing/ATLAS17_mini4_IV_PreAnneal_run2_manual.txt"};
  std::vector<string> fluences{"3.54e14","3.54e14","4.25e14","4.25e14","7.18e14","7.18e14","8.58e14"};

  std::vector<string> filediff{"ATLAS17_mini3","ATLAS12_p1","ATLAS12_p2"};
  std::vector<string> fluencediff{"3.54e14","4.25e14","7.18e14"};
  std::vector<TString> Tfilediff{"ATLAS17_mini3","ATLAS12_p1","ATLAS12_p2"};
  std::vector<TString> Tfluencediff{"3.54e14","4.25e14","7.18e14"};

  TMultiGraph *diffmg = new TMultiGraph();
  TLegend *leg = new TLegend(0.55,0.8,0.85,0.9);
  diffmg->GetXaxis()->SetTitle("Bias [-V]");
  diffmg->GetYaxis()->SetTitle("Change in Current [A]");
  
  for(int i{0}; i<filediff.size(); ++i)
    {
      std::string prefilePath = "Pre-Annealing/"+filediff[i]+"_IV_PreAnneal_manual.txt";
      std::string postfilePath = "Post-Annealing/"+filediff[i]+"_IV_PostAnneal_manual.txt";
      std::vector<double> currentdiff;
      std::vector<double> ecurrentdiff;

      Data predata = ReadFile(prefilePath);
      Data postdata = ReadFile(postfilePath);
      for(int n{0}; n<predata.voltage.size(); ++n)
	{
	  currentdiff.push_back(postdata.current[n]-predata.current[n]);
	  ecurrentdiff.push_back(pow(pow(postdata.current[n]*predata.ecurrent[n],2) + pow(predata.current[n]*postdata.ecurrent[n],2),0.5));	  
	}
      TGraphErrors *g = new TGraphErrors(predata.voltage.size(),&(predata.voltage[0]),&(currentdiff[0]),&(predata.evoltage[0]),&(ecurrentdiff[0]));
      g->SetMarkerStyle(20);
      g->SetMarkerColor(i+1);
      g->SetLineColor(i+1);
      diffmg->Add(g,"p");
      
      TString legEntry = Tfilediff[i]+" "+Tfluencediff[i]+"n_{eq}/cm^{2}";
      leg->AddEntry(g,legEntry,"lp");      
    }

  // TCanvas *canvas = new TCanvas("pre-post difference", "pre-post difference",600,600);
  // canvas->SetTopMargin(0.06);
  // canvas->SetRightMargin(0.1);
  // TGaxis::SetMaxDigits(3);
  // leg->SetBorderSize(0);
  // leg->SetFillColor(0);
  // leg->SetTextSize(0.02);
  // leg->SetFillStyle(1000);
  // leg->SetTextFont(42);
  // leg->SetNColumns(1);
  // diffmg->Draw("AP");
  // leg->Draw();
  //canvas->SaveAs("Current_Change_Annealing_27MeV_manual.pdf");
  
  int pre_i{1};
  int post_i{1};
  for(int i{0}; i<filePath.size(); ++i)
    {
      TString fluence = fluences[i];
      std::size_t preanneal = filePath[i].find("PreAnneal");
      std::size_t postanneal = filePath[i].find("PostAnneal");
      std::size_t ATLAS12 = filePath[i].find("ATLAS12");
      std::size_t ATLAS17 = filePath[i].find("ATLAS17");
      Data data1 = ReadFile(filePath[i]);
      Data postdata;
      TGraphErrors *g = new TGraphErrors(data1.voltage.size(),&(data1.voltage[0]),&(data1.current[0]),&(data1.evoltage[0]),&(data1.ecurrent[0]));
      if(preanneal != std::string::npos)
	{
	  g->SetMarkerStyle(20);
	  if(pre_i!=5)	    
	    {
	      g->SetMarkerColor(pre_i);
	      g->SetLineColor(pre_i);
	      ++pre_i;
	    }
	  else if(pre_i==5)
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
      else if(postanneal != std::string::npos)
	{
	  g->SetMarkerStyle(21);
	  if(post_i!=5)	    
	    {
	      g->SetMarkerColor(post_i);
	      g->SetLineColor(post_i);
	      ++post_i;
	    }
	  else if(post_i==5)
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

      if(postanneal !=std::string::npos)
	{
	  IVmg->Add(g,"p");
	}
      if(preanneal !=std::string::npos)
	{
	  IVmg->Add(g,"p");
	}
    }
  
  TCanvas *can = new TCanvas("ATLAS_27MeV_IV","ATLAS_27MeV_IV",600,600);  
  IVmg->GetYaxis()->SetTitle("Current [-A]");
  IVmg->GetXaxis()->SetTitle("Bias [-V]");
  IVmg->GetYaxis()->SetTitleOffset(1.4);
  can->SetTopMargin(0.08);
  can->SetRightMargin(0.1);
  can->SetLeftMargin(0.15);
  TGaxis::SetMaxDigits(3);
  IVleg->SetBorderSize(0);
  IVleg->SetFillColor(0);
  IVleg->SetTextSize(0.0175);
  IVleg->SetFillStyle(1000);
  IVleg->SetTextFont(42);
  IVleg->SetNColumns(1);
  IVmg->Draw("AP");
  IVleg->Draw("same");
  can->SaveAs("ATLAS12_17_IV_27MeV_manual.pdf");
}
