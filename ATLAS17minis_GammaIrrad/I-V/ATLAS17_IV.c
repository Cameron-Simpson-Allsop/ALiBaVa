#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"
#include "iostream"
#include "fstream"
#include "rootlogonATLAS.h"

void TempScale(TString file, double temp, TString rad){
  ifstream infile;
  ofstream outfile;
  infile.open(file);
  outfile.open("ATLAS17_"+rad+"_IV_scaled.txt");
  while(!infile.eof())
    {
      double reftemp = 248.; //-25C
      double Ea = 1.21; //eV
      double kb = 8.617e-5; //ev/K
      double voltage, current, evoltage, ecurrent, scaled_current, escaled_current;
      infile >> voltage >> current >> evoltage >> ecurrent; 
      scaled_current = current*pow(reftemp/(temp+273.),2)*exp((-Ea/(2*kb))*((1./reftemp)-(1./(temp+273.))));
      escaled_current = (scaled_current/current)*ecurrent;
      
      outfile << voltage << "\t" << scaled_current << "\t" << evoltage << "\t" << escaled_current << std::endl;

      std::cout << voltage << "\t" << current << "\t" << evoltage << "\t" << ecurrent <<  "\t\t\t" << voltage << "\t" << scaled_current << "\t" << evoltage << "\t" << escaled_current  << std::endl;

    }
  
  infile.close();
  outfile.close();
  
}

void ATLAS17_IV(){
  rootlogonATLAS();

  TString Pre_10Mrad = "Pre_Anneal/ATLAS17_10Mrad_PreAnneal_IV_25-10-2018_Processed.txt";
  TString Pre_17p5Mrad = "Pre_Anneal/ATLAS17_17p5Mrad_PreAnneal_IV_30-10-18_Processed.txt";
  TString Pre_35Mrad = "Pre_Anneal/ATLAS17_35Mrad_PreAnneal_IV_31-10-2018_Processed.txt";
  TString Post_35Mrad = "Post_Anneal/ATLAS17_35Mrad_PostAnneal_IV_31-10-18_Processed.txt";
  
  TString input = "";
  std::cout << "Scale Temperature? (y/n)" << std::endl;
  while(input != "y" && input != "n")
    {
      std::cin >> input;
      if(input !="y" && input !="n")
	{
	  std::cout << "Invalid Input, please try again." << std::endl;
	}
    }
    
  if(input == "y"){
    std::cout <<"\n10Mrad_PreAnneal (Unscaled vs Scaled)\n\n"; TempScale(Pre_10Mrad,-26.7,"10Mrad_PreAnneal");
    std::cout <<"\n17.5Mrad_PreAnneal (Unscaled vs Scaled)\n\n"; TempScale(Pre_17p5Mrad,-26.4,"17p5Mrad_PreAnneal");
    std::cout <<"\n35Mrad_PreAnneal (Unscaled vs Scaled)\n\n"; TempScale(Pre_35Mrad,-26.3,"35Mrad_PreAnneal");
    std::cout <<"\n35Mrad_PostAnneal (Unscaled vs Scaled)\n\n"; TempScale(Post_35Mrad,-24.1,"35Mrad_PostAnneal"); 
    Pre_10Mrad = "ATLAS17_10Mrad_PreAnneal_IV_scaled.txt";
    Pre_17p5Mrad = "ATLAS17_17p5Mrad_PreAnneal_IV_scaled.txt";
    Pre_35Mrad = "ATLAS17_35Mrad_PreAnneal_IV_scaled.txt";
    Post_35Mrad = "ATLAS17_35Mrad_PostAnneal_IV_scaled.txt";
    
    TGraphErrors *Pre10Mrad = new TGraphErrors(Pre_10Mrad);
    Pre10Mrad->SetMarkerColor(kBlack);
    Pre10Mrad->SetLineColor(kBlack);
    Pre10Mrad->SetMarkerStyle(22);
    TGraphErrors *Pre17p5Mrad = new TGraphErrors(Pre_17p5Mrad);
    Pre17p5Mrad->SetMarkerColor(kBlue);
    Pre17p5Mrad->SetLineColor(kBlue);
    Pre17p5Mrad->SetMarkerStyle(22);
    TGraphErrors *Pre35Mrad = new TGraphErrors(Pre_35Mrad);  
    Pre35Mrad->SetMarkerColor(kRed);
    Pre35Mrad->SetLineColor(kRed);
    Pre35Mrad->SetMarkerStyle(22);
 
    TGraphErrors *Post35Mrad = new TGraphErrors(Post_35Mrad);  
    Post35Mrad->SetMarkerColor(kRed);
    Post35Mrad->SetLineColor(kRed);
    Post35Mrad->SetMarkerStyle(23);
    
    TMultiGraph *mg = new TMultiGraph();
    //mg->GetXaxis()->SetTitle("Bias Voltage (V)");
    mg->GetYaxis()->SetTitle("Leakage Current (nA)");
    mg->Add(Pre10Mrad,"p`");
    mg->Add(Pre17p5Mrad,"p");
    mg->Add(Pre35Mrad,"p");
    mg->Add(Post35Mrad,"p");
    
    TLegend *leg;
    leg = new TLegend(0.2,0.16,0.4,0.3);
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->SetTextSize(0.035);
    leg->SetFillStyle(1000);
    leg->SetTextFont(42);
    leg->SetNColumns(1);
    leg->AddEntry(Pre10Mrad,"10Mrad Pre-Annealing","lp");
    leg->AddEntry(Pre17p5Mrad,"17.5Mrad Pre-Annealing","lp");
    leg->AddEntry(Pre35Mrad,"35Mrad Pre-Annealing","lp");
    leg->AddEntry(Post35Mrad,"35Mrad Post-Annealing","lp");
    TCanvas *IV = new TCanvas("IV_scaled","IV_scaled",600,600);
    mg->Draw("AP");
    leg->Draw("same");
      
  }

  if(input == "n"){
    Pre_10Mrad = "Pre_Anneal/ATLAS17_10Mrad_PreAnneal_IV_25-10-2018_Processed.txt";
    Pre_17p5Mrad = "Pre_Anneal/ATLAS17_17p5Mrad_PreAnneal_IV_30-10-18_Processed.txt";
    Pre_35Mrad = "Pre_Anneal/ATLAS17_35Mrad_PreAnneal_IV_31-10-2018_Processed.txt";
    Post_35Mrad = "Post_Anneal/ATLAS17_35Mrad_PostAnneal_IV_31-10-18_Processed.txt";
    
    TGraphErrors *Pre10Mrad = new TGraphErrors(Pre_10Mrad);
    Pre10Mrad->SetMarkerColor(kBlack);
    Pre10Mrad->SetLineColor(kBlack);
    Pre10Mrad->SetMarkerStyle(22);
    TGraphErrors *Pre17p5Mrad = new TGraphErrors(Pre_17p5Mrad);
    Pre17p5Mrad->SetMarkerColor(kBlue);
    Pre17p5Mrad->SetLineColor(kBlue);
    Pre17p5Mrad->SetMarkerStyle(22);
    TGraphErrors *Pre35Mrad = new TGraphErrors(Pre_35Mrad);  
    Pre35Mrad->SetMarkerColor(kRed);
    Pre35Mrad->SetLineColor(kRed);
    Pre35Mrad->SetMarkerStyle(22);
 
    TGraphErrors *Post35Mrad = new TGraphErrors(Post_35Mrad);  
    Post35Mrad->SetMarkerColor(kRed);
    Post35Mrad->SetLineColor(kRed);
    Post35Mrad->SetMarkerStyle(23);
    
    TMultiGraph *mg = new TMultiGraph();
    //mg->GetXaxis()->SetTitle("Bias Voltage (V)");
    mg->GetYaxis()->SetTitle("Leakage Current (nA)");
    mg->Add(Pre10Mrad,"p`");
    mg->Add(Pre17p5Mrad,"p");
    mg->Add(Pre35Mrad,"p");
    mg->Add(Post35Mrad,"p");
    
    TLegend *leg;
    leg = new TLegend(0.2,0.16,0.4,0.3);
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->SetTextSize(0.035);
    leg->SetFillStyle(1000);
    leg->SetTextFont(42);
    leg->SetNColumns(1);
    leg->AddEntry(Pre10Mrad,"10Mrad Pre-Annealing -26.7C","lp");
    leg->AddEntry(Pre17p5Mrad,"17.5Mrad Pre-Annealing -26.4C","lp");
    leg->AddEntry(Pre35Mrad,"35Mrad Pre-Annealing -26.3C","lp");
    leg->AddEntry(Pre35Mrad,"35Mrad Post-Annealing -24.1C","lp");
    TCanvas *IV = new TCanvas("IV_unscaled","IV_unscaled",600,600);
    mg->Draw("AP");
    leg->Draw("same");
  }
  
}
