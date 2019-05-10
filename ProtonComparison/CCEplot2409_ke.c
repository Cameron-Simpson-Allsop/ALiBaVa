#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"
#include "iostream"
#include "fstream"

void Scale(TString filePath, std::vector<double> Temperature, TString rad){
  ifstream inFile;
  ofstream outFile;
  inFile.open(filePath);
  outFile.open(rad+".txt");

  int i{0};
  while(!inFile.eof())//Reads in file row by row, and adds variables to vectors on each loop
    {
      double Voltage, ADC_Counts, eVoltage, eADC_Counts;
      inFile >> Voltage >> ADC_Counts >> eVoltage >> eADC_Counts; //sets each column in row to defined variable
      double correction = 110.4/((-0.383*(Temperature[i]))+101); //check this
      double ADC_Ke = 0.202; //Estimate of 1 ADC count in Ke (22.5ke/ADC plateau at -25C of an unirradiated sensor))
      double ecorrection = abs((110.4*0.05)/(-0.383*pow(-0.383*(Temperature[i])+101,2))); 

      //std::cout << Voltage << " " << ADC_Counts << " " << eVoltage << " " << eADC_Counts << std::endl;
      //std::cout << Voltage << " " << ADC_Counts*correction*ADC_Ke << " " << eVoltage << " " << pow(pow(ADC_Counts*ADC_Ke*ecorrection,2)+pow(correction*ADC_Ke*eADC_Counts,2),0.5) << std::endl;
   
      outFile << Voltage/1000. << "\t" << ADC_Counts*correction*ADC_Ke << "\t" << eVoltage/1000. << "\t" << pow(pow(ADC_Counts*ADC_Ke*ecorrection,2)+pow(correction*ADC_Ke*eADC_Counts,2),0.5) << std::endl;

      i++;
    }

  inFile.close();
  outFile.close(); 
 
}


void CCEplot2409_ke(){

  Scale("RSRun11Sep18ATLAS12Unirrad_0.txt",{-20.9,-19.5,-20.9,-21.7,-21.5,-22.2,-22.6,-24.2,-24.0,-24.0,-25.2,-25.2,-25.2},"ATLAS12_Unirrad");
  Scale("RSRun12Sep18ATLAS12Irrad6e14PreAnneal_1_edit2.txt",{-24.6,-25.1,-25.5,-25.7,-26.0,-26.1,-26.3,-26.5,-26.6,-26.7,-26.7},"ATLAS12_6e14_PreAnneal");
  Scale("RSRun13Sep18ATLAS12Irrad6e14PostAnneal_2_edit.txt",{-25.6,-26.0,-26.2,-26.5,-26.7,-26.9,-27.0,-27.2,-27.5,-27.5},"ATLAS12_6e14_PostAnneal");
  Scale("RSRun24Aug18ATLAS12Irrad1e15PreAnnealed_1.txt",{-27.8,-24.7,-26.5,-28.4,-27.8,-27.6,-24.0,-24.7,-24.7},"ATLAS12_1e15_PreAnneal");
  Scale("RSRun19Jul18ATLAS17Irrad5e14Annealed_2.txt",{-24.9,-26.5,-26.7,-26.2,-25.2,-24.0,-24.5,-26.2,-25.2,-25.2},"ATLAS17_5e14_PostAnneal");
  
  TGraphErrors *g1 = new TGraphErrors("ATLAS12_Unirrad.txt");
  TGraphErrors *g2 = new TGraphErrors("ATLAS12_6e14_PreAnneal.txt");
  TGraphErrors *g3 = new TGraphErrors("ATLAS12_6e14_PostAnneal.txt");
  TGraphErrors *g4 = new TGraphErrors("ATLAS12_1e15_PreAnneal.txt"); 
  TGraphErrors *g5 = new TGraphErrors("ATLAS17_5e14_PostAnneal.txt");

  g1->SetLineColor(kBlack); 
  g1->SetMarkerColor(kBlack);
		
  g2->SetLineColor(kBlue); 
  g2->SetMarkerColor(kBlue);
		
  g3->SetLineColor(kRed); 
  g3->SetMarkerColor(kRed);

  g4->SetLineColor(kGreen); 
  g4->SetMarkerColor(kGreen);

  g5->SetLineColor(kMagenta); 
  g5->SetMarkerColor(kMagenta);

  g1->SetMarkerStyle(20);
  g2->SetMarkerStyle(20);
  g3->SetMarkerStyle(20);
  g4->SetMarkerStyle(20);
  g5->SetMarkerStyle(20);

  TMultiGraph *mg = new TMultiGraph();
  mg->Add(g1,"p");
  mg->Add(g2,"p");
  mg->Add(g3,"p");
  mg->Add(g4,"p");
  mg->Add(g5,"p");
  mg->GetXaxis()->SetTitle("Bias Voltage (-V)");
  mg->GetYaxis()->SetTitle("Collected Charge (ke)");

  TLegend *legend = new TLegend(0.35,0.15,0.85,0.4); //Defines Legend
  legend->AddEntry(g1,"ATLAS12 Unirradiated","p");
  legend->AddEntry(g2,"ATLAS12 6#times10^{14} n_{eq} /cm^{2} Pre-Annealing","p");
  legend->AddEntry(g3,"ATLAS12 6#times10^{14} n_{eq} /cm^{2} Post-Annealing","p");
  legend->AddEntry(g4,"ATLAS12 2.5#times10^{14} n_{eq} /cm^{2} Pre-Annealing ","p");
  legend->AddEntry(g5,"ATLAS17 5#times10^{14} n_{eq} /cm^{2} Post-Annealing","p");
  legend->SetLineColor(kWhite);		

  TCanvas* canvas = new TCanvas("CCE","CCE",600,600);
  mg->GetYaxis()->SetRangeUser(-6,25);
  mg->Draw("ALP");
  legend->Draw();
  canvas->SaveAs("Combined_CCE_protons_ke.pdf");

}
