#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"
#include "iostream"
#include "fstream"
#include "rootlogonATLAS.h"

void Scale(TString filePath, std::vector<double> Temperature, TString rad){
  ifstream inFile;
  ofstream outFile;
  inFile.open(filePath);
  outFile.open(rad+".txt");

  int i = 0;
  while(!inFile.eof())//Reads in file row by row, and adds variables to vectors on each loop
    {
      double Voltage, ADC_Counts, eVoltage, eADC_Counts;
      inFile >> Voltage >> ADC_Counts >> eVoltage >> eADC_Counts; //sets each column in row to defined variable
      double correction = 110.4/((-0.383*(Temperature[i]))+101); //check this
      double ADC_Ke = 0.202; //Estimate of 1 ADC count in Ke (22.5ke/ADC plateau at -25C of an unirradiated sensor))
      double ecorrection = abs((110.4*0.05)/(-0.383*pow(-0.383*(Temperature[i])+101,2))); 

      //std::cout << Voltage << " " << ADC_Counts << " " << eVoltage << " " << eADC_Counts << std::endl;
      //std::cout << Voltage << " " << ADC_Counts*correction*ADC_Ke << " " << eVoltage << " " << pow(pow(ADC_Counts*ADC_Ke*ecorrection,2)+pow(correction*ADC_Ke*eADC_Counts,2),0.5) << std::endl;
      i = i+1;

      outFile << Voltage/1000. << "\t" << ADC_Counts*correction*ADC_Ke << "\t" << eVoltage << "\t" << pow(pow(ADC_Counts*ADC_Ke*ecorrection,2)+pow(correction*ADC_Ke*eADC_Counts,2),0.5) << std::endl;
      
    }

  inFile.close();
  outFile.close(); 
 
  }
void TemperatureCorrection(){
  rootlogonATLAS();
  
  Scale("25Oct2018_ATLAS17mini_GammaIrrad_10Mrad_PreAnneal_Cold/RSRun25Oct18ATLAS17GammaPreAnneal10Mrad_1/CCE_output_PF.txt",{-23.9,-24.2,-24.5,-24.8,-25.1,-25.5,-25.7,-25.9,-26.1,-26.3,-26.3},"10Mrad_PreAnneal");
  Scale("29Oct2018_ATLAS17mini_GammaIrrad_17p5Mrad_PreAnneal_Cold/RSRun29Oct18ATLAS17GammaPreAnneal17p5Mrad_1/CCE_output_PF.txt",{-22.6,-23.4,-24.0,-24.4,-24.6,-24.8,-25.0,-25.1,-25.3,-25.7,-25.7},"17p5Mrad_PreAnneal");
  Scale("30Oct2018_ATLAS17mini_GammaIrrad_35Mrad_PreAnneal_Cold/RSRun30Oct18ATLAS17PreAnneal35Mrad_1/CCE_output_PF.txt",{-23.0,-23.3,-24.1,-24.5,-24.8,-25.0,-25.2,-25.3,-25.4,-25.4,-25.4},"35Mrad_PreAnneal");


  TGraphErrors *PreMrad10 = new TGraphErrors("10Mrad_PreAnneal.txt");
  PreMrad10->SetMarkerColor(kBlack);
  PreMrad10->SetLineColor(kBlack);
  TGraphErrors *PreMrad17p5 = new TGraphErrors("17p5Mrad_PreAnneal.txt");
  PreMrad17p5->SetMarkerColor(kBlue);
  PreMrad17p5->SetLineColor(kBlue);
  TGraphErrors *PreMrad35 = new TGraphErrors("35Mrad_PreAnneal.txt");
  PreMrad35->SetMarkerColor(kRed);
  PreMrad35->SetLineColor(kRed);
  TMultiGraph *Combined_CCE = new TMultiGraph();
  Combined_CCE->GetXaxis()->SetTitle("Bias Voltage [kV]");
  Combined_CCE->GetYaxis()->SetTitle("Collected Charge [ke]");
  Combined_CCE->GetYaxis()->SetTitleOffset(1.35);
  Combined_CCE->Add(PreMrad10,"p");
  Combined_CCE->Add(PreMrad17p5,"p");
  Combined_CCE->Add(PreMrad35,"p");
  
  TLegend *leg;
  leg = new TLegend(0.5,0.2,0.7,0.3);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(1000);
  leg->SetTextFont(42);
  leg->SetNColumns(1);
  leg->AddEntry(PreMrad10,"Pre-Annealing 10Mrad","lp");
  leg->AddEntry(PreMrad17p5,"Pre-Annealing 17.5Mrad","lp");
  leg->AddEntry(PreMrad35,"Pre-Annealing 35Mrad","lp");
  
  TGaxis::SetMaxDigits(2);
  
  TCanvas *CCE = new TCanvas("CCE","CCE",600,600);
  Combined_CCE->Draw("AP");
  leg->Draw("same");
  CCE->SaveAs("Combined_CCE_Plot_ke.pdf");
 
}

//Principle is to convert ADC counts at temperature T to ADC counts at -25C for an unirradiated sensor (at plateu), which is what Patrick's equation (correction double) does. And then use the fact that at -25C unirradiated, 1 ADC = ~202 electrons.
