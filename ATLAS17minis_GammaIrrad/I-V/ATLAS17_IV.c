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
      
      outfile << voltage << "\t" << -scaled_current << "\t" << evoltage << "\t" << escaled_current << std::endl;

      std::cout << voltage << "\t" << current << "\t" << evoltage << "\t" << ecurrent <<  "\t\t\t" << voltage << "\t" << -scaled_current << "\t" << evoltage << "\t" << escaled_current  << std::endl;

    }
  
  infile.close();
  outfile.close();
  
}

void ATLAS17_IV(){
  rootlogonATLAS();

  TString Pre_10Mrad = "Pre_Anneal/ATLAS17_10Mrad_PreAnneal_IV_25-10-2018_Processed.txt";
  TString Pre_17p5Mrad = "Pre_Anneal/ATLAS17_17p5Mrad_PreAnneal_IV_30-10-18_Processed.txt";
  TString Pre_35Mrad = "Pre_Anneal/ATLAS17_35Mrad_PreAnneal_IV_31-10-2018_Processed.txt";
  TString Pre_70Mrad = "Pre_Anneal/ATLAS17_70Mrad_PreAnneal_IV_01-11-2018_Processed.txt";
  TString Pre_52p5Mrad = "Pre_Anneal/ATLAS17_52p5Mrad_PreAnneal_IV_07-11-2018_Processed.txt";

  TString Post_10Mrad = "Post_Anneal/ATLAS17_10Mrad_PostAnneal_IV_16-11-2018_Processed.txt";
  TString Post_17p5Mrad = "Post_Anneal/ATLAS17_17p5Mrad_PostAnneal_IV_20-11-2018_Processed.txt";
  TString Post_35Mrad = "Post_Anneal/ATLAS17_35Mrad_PostAnneal_IV_31-10-18_Processed.txt";
  TString Post_35MradRun2 = "Post_Anneal/ATLAS17_35Mrad_PostAnnealRun2_IV_11-12-2018_Processed.txt";
  TString Post_52p5Mrad = "Post_Anneal/ATLAS17_52p5Mrad_PostAnneal_IV_08-11-2018_Processed.txt";
  TString Post_70MradShort = "Post_Anneal/ATLAS17_70Mrad_PostAnneal_IV_06-11-18_Short_Processed.txt";
     
    std::cout <<"\n10Mrad_PreAnneal (Unscaled vs Scaled)\n\n"; TempScale(Pre_10Mrad,-26.7,"10Mrad_PreAnneal");
    std::cout <<"\n17.5Mrad_PreAnneal (Unscaled vs Scaled)\n\n"; TempScale(Pre_17p5Mrad,-26.4,"17p5Mrad_PreAnneal");
    std::cout <<"\n35Mrad_PreAnneal (Unscaled vs Scaled)\n\n"; TempScale(Pre_35Mrad,-26.3,"35Mrad_PreAnneal");
    std::cout <<"\n70Mrad_PreAnneal (Unscaled vs Scaled)\n\n"; TempScale(Pre_70Mrad,-23.7,"70Mrad_PreAnneal");
    std::cout <<"\n52.5Mrad_PreAnneal (Unscaled vs Scaled)\n\n"; TempScale(Pre_52p5Mrad,-24.4,"52p5Mrad_PreAnneal");

    std::cout <<"\n10Mrad_PostAnneal (Unscaled vs Scaled)\n\n"; TempScale(Post_10Mrad,-27.0,"10Mrad_PostAnneal");
    std::cout <<"\n17.5Mrad_PostAnneal_Short (Unscaled vs Scaled)\n\n"; TempScale(Post_17p5Mrad,-21.2,"17p5Mrad_PostAnneal"); 
    std::cout <<"\n35Mrad_PostAnneal (Unscaled vs Scaled)\n\n"; TempScale(Post_35Mrad,-24.1,"35Mrad_PostAnneal");
    std::cout <<"\n35Mrad_PostAnneal_Run2 (Unscaled vs Scaled)\n\n"; TempScale(Post_35MradRun2,-24.0,"35Mrad_PostAnneal_Run2");
    std::cout <<"\n52.5Mrad_PostAnneal (Unscaled vs Scaled)\n\n"; TempScale(Post_52p5Mrad,-25.8,"52p5Mrad_PostAnneal");
    std::cout <<"\n70Mrad_PostAnneal_Short (Unscaled vs Scaled)\n\n"; TempScale(Post_70MradShort,-29.3,"70Mrad_PostAnneal_Short");    
    
    Pre_10Mrad = "ATLAS17_10Mrad_PreAnneal_IV_scaled.txt";
    Pre_17p5Mrad = "ATLAS17_17p5Mrad_PreAnneal_IV_scaled.txt";
    Pre_35Mrad = "ATLAS17_35Mrad_PreAnneal_IV_scaled.txt";
    Pre_70Mrad = "ATLAS17_70Mrad_PreAnneal_IV_scaled.txt";
    Pre_52p5Mrad = "ATLAS17_52p5Mrad_PreAnneal_IV_scaled.txt";

    Post_10Mrad = "ATLAS17_10Mrad_PostAnneal_IV_scaled.txt";
    Post_17p5Mrad = "ATLAS17_17p5Mrad_PostAnneal_IV_scaled.txt";
    Post_35Mrad = "ATLAS17_35Mrad_PostAnneal_IV_scaled.txt";
    Post_35MradRun2 = "ATLAS17_35Mrad_PostAnneal_Run2_IV_scaled.txt";
    Post_52p5Mrad = "ATLAS17_52p5Mrad_PostAnneal_IV_scaled.txt";
    Post_70MradShort = "ATLAS17_70Mrad_PostAnneal_Short_IV_scaled.txt";
    
    TGraphErrors *Pre10Mrad = new TGraphErrors(Pre_10Mrad);
    Pre10Mrad->SetMarkerColor(kBlack);
    Pre10Mrad->SetLineColor(kBlack);
    Pre10Mrad->SetMarkerStyle(20);
    TGraphErrors *Pre17p5Mrad = new TGraphErrors(Pre_17p5Mrad);
    Pre17p5Mrad->SetMarkerColor(kBlue);
    Pre17p5Mrad->SetLineColor(kBlue);
    Pre17p5Mrad->SetMarkerStyle(20);
    TGraphErrors *Pre35Mrad = new TGraphErrors(Pre_35Mrad);  
    Pre35Mrad->SetMarkerColor(kRed);
    Pre35Mrad->SetLineColor(kRed);
    Pre35Mrad->SetMarkerStyle(20);
    TGraphErrors *Pre70Mrad = new TGraphErrors(Pre_70Mrad);
    Pre70Mrad->SetMarkerColor(8);
    Pre70Mrad->SetLineColor(8);
    Pre70Mrad->SetMarkerStyle(20);
    TGraphErrors *Pre52p5Mrad = new TGraphErrors(Pre_52p5Mrad);
    Pre52p5Mrad->SetMarkerColor(28);
    Pre52p5Mrad->SetLineColor(28);
    Pre52p5Mrad->SetMarkerStyle(20);

    TGraphErrors *Post10Mrad = new TGraphErrors(Post_10Mrad);  
    Post10Mrad->SetMarkerColor(kBlack);
    Post10Mrad->SetLineColor(kBlack);
    Post10Mrad->SetMarkerStyle(21);
    TGraphErrors *Post17p5Mrad = new TGraphErrors(Post_17p5Mrad);  
    Post17p5Mrad->SetMarkerColor(kBlue);
    Post17p5Mrad->SetLineColor(kBlue);
    Post17p5Mrad->SetMarkerStyle(21);
    TGraphErrors *Post35Mrad = new TGraphErrors(Post_35Mrad);  
    Post35Mrad->SetMarkerColor(kRed);
    Post35Mrad->SetLineColor(kRed);
    Post35Mrad->SetMarkerStyle(25);
    TGraphErrors *Post35MradRun2 = new TGraphErrors(Post_35MradRun2);  
    Post35MradRun2->SetMarkerColor(kRed);
    Post35MradRun2->SetLineColor(kRed);
    Post35MradRun2->SetMarkerStyle(21);
    TGraphErrors *Post52p5Mrad = new TGraphErrors(Post_52p5Mrad);  
    Post52p5Mrad->SetMarkerColor(28);
    Post52p5Mrad->SetLineColor(28);
    Post52p5Mrad->SetMarkerStyle(21);
    TGraphErrors *Post70MradShort = new TGraphErrors(Post_70MradShort);  
    Post70MradShort->SetMarkerColor(kBlack);
    Post70MradShort->SetLineColor(kBlack);
    Post70MradShort->SetMarkerStyle(20);
    
    TMultiGraph *mg = new TMultiGraph();
    mg->GetXaxis()->SetTitle("Bias Voltage (-V)");
    mg->GetYaxis()->SetTitle("Leakage Current (-nA)");
    mg->Add(Pre10Mrad,"p`");
    mg->Add(Pre17p5Mrad,"p");
    mg->Add(Pre35Mrad,"p");
    mg->Add(Pre70Mrad,"p");
    //mg->Add(Post35Mrad,"p");
    mg->Add(Pre52p5Mrad,"p");
    mg->Add(Post52p5Mrad,"p");
    mg->Add(Post10Mrad,"p");
    mg->Add(Post17p5Mrad,"p");
    mg->Add(Post35MradRun2,"p");
    //mg->Add(Post70MradShort,"p");

    TGaxis::SetMaxDigits(3);
    
    TLegend *leg;
    leg = new TLegend(0.2,0.5,0.4,0.8);
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->SetTextSize(0.035);
    leg->SetFillStyle(1000);
    leg->SetTextFont(42);
    leg->SetNColumns(1);
    leg->AddEntry(Pre10Mrad,"10Mrad Pre-Annealing","lp");
    leg->AddEntry(Pre17p5Mrad,"17.5Mrad Pre-Annealing","lp");
    leg->AddEntry(Pre35Mrad,"35Mrad Pre-Annealing","lp");
    leg->AddEntry(Pre52p5Mrad,"52.5Mrad Pre-Annealing","lp");
    leg->AddEntry(Pre70Mrad,"70Mrad Pre-Annealing","lp");
    leg->AddEntry(Post10Mrad,"10Mrad Post-Annealing","lp");
    leg->AddEntry(Post17p5Mrad,"17.5Mrad Post-Annealing","lp");
    //leg->AddEntry(Post35Mrad,"35Mrad Post-Annealing","lp");
    leg->AddEntry(Post35MradRun2,"35Mrad Post-Annealing","lp");
    leg->AddEntry(Post52p5Mrad,"52.5Mrad Post-Annealing","lp");
    //leg->AddEntry(Post70MradShort,"70Mrad Post-Annealing","lp");
    TCanvas *IV = new TCanvas("IV_scaled","IV_scaled",600,600);
    mg->Draw("AP");
    leg->Draw("same");
      
  
}
