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
      double ADC_Ke = 22.5/110.; //crude estimate of 1 ADC count in Ke (22.5ke/ADC plateau at -25C of an unirradiated sensor))
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
  
  Scale("11Sept2018_ATLAS12_Unirradiated_Cold/RSRun11Sep18ATLAS12Unirrad_0/CCE_output_PF.txt",{-20.9,-19.5,-20.9,-21.7,-21.5,-22.2,-22.6,-24.2,-24.0,-24.0,-25.2,-25.2,-25.2},"Unirrad");
  Scale("12Sept2018_ATLAS12_Irradiated_Cold/RSRun12Sep18ATLAS12Irrad6e14PreAnneal_1/CCE_output_PF.txt",{-24.6,-25.1,-25.5,-25.7,-26.0,-26.1,-26.3,-26.5,-26.6,-26.7,-26.7},"PreAnneal");
  Scale("13Sept2018_ATLAS12_PostAnneal_Irradiated_Cold/RSRun13Sep18ATLAS12Irrad6e14PostAnneal_2/CCE_output_PF.txt",{-25.6,-26.0,-26.2,-26.5,-26.7,-26.9,-27.0,-27.2,-27.5,-27.5},"PostAnneal");

  TGraphErrors *Unirrad = new TGraphErrors("Unirrad.txt");
  Unirrad->SetMarkerColor(kBlack);
  Unirrad->SetLineColor(kBlack);
  TGraphErrors *PreAnneal = new TGraphErrors("PreAnneal.txt");
  PreAnneal->SetMarkerColor(kBlue);
  PreAnneal->SetLineColor(kBlue);  
  TGraphErrors *PostAnneal = new TGraphErrors("PostAnneal.txt");
  PostAnneal->SetMarkerColor(kRed);
  PostAnneal->SetLineColor(kRed);
  TMultiGraph *Combined_CCE = new TMultiGraph();
  Combined_CCE->GetXaxis()->SetTitle("Bias Voltage [kV]");
  Combined_CCE->GetYaxis()->SetTitle("Collected Charge [ke]");
  Combined_CCE->GetYaxis()->SetTitleOffset(1.35);
  Combined_CCE->Add(Unirrad,"p");
  Combined_CCE->Add(PreAnneal,"p");
  Combined_CCE->Add(PostAnneal,"p");

  TGraphErrors *UnirradADC = new TGraphErrors("11Sept2018_ATLAS12_Unirradiated_Cold/RSRun11Sep18ATLAS12Unirrad_0/CCE_output_PF.txt");
  UnirradADC->SetMarkerColor(kBlack);
  UnirradADC->SetLineColor(kBlack);
  TGraphErrors *PreAnnealADC = new TGraphErrors("12Sept2018_ATLAS12_Irradiated_Cold/RSRun12Sep18ATLAS12Irrad6e14PreAnneal_1/CCE_output_PF.txt");
  PreAnnealADC->SetMarkerColor(kBlue);
  PreAnnealADC->SetLineColor(kBlue);  
  TGraphErrors *PostAnnealADC = new TGraphErrors("13Sept2018_ATLAS12_PostAnneal_Irradiated_Cold/RSRun13Sep18ATLAS12Irrad6e14PostAnneal_2/CCE_output_PF.txt");
  PostAnnealADC->SetMarkerColor(kRed);
  PostAnnealADC->SetLineColor(kRed);
  TMultiGraph *Combined_CCEADC = new TMultiGraph();
  Combined_CCEADC->GetXaxis()->SetTitle("Bias Voltage [V]");
  Combined_CCEADC->GetYaxis()->SetTitle("Collected Charge [ADC]");
  Combined_CCEADC->GetYaxis()->SetTitleOffset(1.35);
  Combined_CCEADC->Add(UnirradADC,"p");
  Combined_CCEADC->Add(PreAnnealADC,"p");
  Combined_CCEADC->Add(PostAnnealADC,"p");
  
  TLegend *leg;
  leg = new TLegend(0.4,0.2,0.6,0.3);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(1000);
  leg->SetTextFont(42);
  leg->SetNColumns(1);
  leg->AddEntry(Unirrad,"Unirradiated","lp");
  leg->AddEntry(PreAnneal,"Pre-Annealing 6x10^{14} n_{eq}/cm^{2}","lp");
  leg->AddEntry(PostAnneal,"Post-Annealing 6x10^{14} n_{eq}/cm^{2}","lp");

  TLegend *legADC;
  legADC = new TLegend(0.4,0.2,0.6,0.3);
  legADC->SetBorderSize(0);
  legADC->SetFillColor(0);
  legADC->SetTextSize(0.035);
  legADC->SetFillStyle(1000);
  legADC->SetTextFont(42);
  legADC->SetNColumns(1);
  legADC->AddEntry(UnirradADC,"Unirradiated","lp");
  legADC->AddEntry(PreAnnealADC,"Pre-Annealing 6x10^{14} n_{eq}/cm^{2}","lp");
  legADC->AddEntry(PostAnnealADC,"Post-Annealing 6x10^{14} n_{eq}/cm^{2}","lp");
  
  TGaxis::SetMaxDigits(2);
  
  TCanvas *CCE = new TCanvas("CCE","CCE",600,600);
  Combined_CCE->Draw("AP");
  leg->Draw("same");
  CCE->SaveAs("Combined_CCE_Plot_ke.pdf");

  TCanvas *CCEADC = new TCanvas("CCEADC","CCEADC",600,600);
  Combined_CCEADC->Draw("AP");
  legADC->Draw("same");
  //CCEADC->SaveAs("Combined_CCE_Plot_ADC.pdf");
  
}

//Principle is to convert ADC counts at temperature T to ADC counts at -25C for an unirradiated sensor (at plateu), which is what Patrick's equation (correction double) does. And then use the fact that at -25C unirradiated, ~110 ADC = ~22500 electrons.
