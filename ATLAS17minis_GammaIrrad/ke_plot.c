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
void ke_plot(){
  rootlogonATLAS();
  
  Scale("RSRun25Oct18ATLAS17GammaPreAnneal10Mrad_1/CCE_output_PF.txt",{-23.9,-24.2,-24.5,-24.8,-25.1,-25.5,-25.7,-25.9,-26.1,-26.3,-26.3},"10Mrad_PreAnneal");
  Scale("RSRun29Oct18ATLAS17GammaPreAnneal17p5Mrad_1/CCE_output_PF.txt",{-22.6,-23.4,-24.0,-24.4,-24.6,-24.8,-25.0,-25.1,-25.3,-25.7,-25.7},"17p5Mrad_PreAnneal");
  Scale("RSRun30Oct18ATLAS17PreAnneal35Mrad_1/CCE_output_PF.txt",{-23.0,-23.3,-24.1,-24.5,-24.8,-25.0,-25.2,-25.3,-25.4,-25.4,-25.4},"35Mrad_PreAnneal");
  Scale("RSRun01Nov18ATLAS17PreAnneal70Mrad_1/CCE_output_PF.txt",{-21.7,-21.9,-22.1,-22.5,-22.7,-22.9,-23.1,-23.2,-23.4,-23.6,-23.6},"70Mrad_PreAnneal");

  Scale("RSRun31Oct18ATLAS17PostAnneal35Mrad_2/CCE_output_PF.txt",{-21.4,-22.5,-23.2,-23.5,-23.5,-23.7,-23.6,-23.5,-23.8,-24.2,-24.2},"35Mrad_PostAnneal");
  Scale("RSRun05Nov18ATLAS17PostAnneal70Mrad_2/CCE_output_PF.txt",{-26.2,-26.3,-26.4,-26.6,-26.8,-27.0,-27.1,-27.2,-27.3,-27.4,-27.4},"70Mrad_PostAnneal");
  Scale("RSRun16Nov18ATLAS17PostAnneal10Mrad_2/CCE_output_PF.txt",{-27.0,-27.0,-27.0,-26.9,-26.9,-26.8,-26.8,-26.8,-26.5,-26.7,-26.7},"10Mrad_PostAnneal");
 
  TGraphErrors *PreMrad10 = new TGraphErrors("10Mrad_PreAnneal.txt");
  PreMrad10->SetMarkerColor(kBlack);
  PreMrad10->SetLineColor(kBlack);
  PreMrad10->SetMarkerStyle(20);
  TGraphErrors *PreMrad17p5 = new TGraphErrors("17p5Mrad_PreAnneal.txt");
  PreMrad17p5->SetMarkerColor(kBlue);
  PreMrad17p5->SetLineColor(kBlue);
  PreMrad17p5->SetMarkerStyle(20);
  TGraphErrors *PreMrad35 = new TGraphErrors("35Mrad_PreAnneal.txt");
  PreMrad35->SetMarkerColor(kRed);
  PreMrad35->SetLineColor(kRed);
  PreMrad35->SetMarkerStyle(20);
  TGraphErrors *PreMrad70 = new TGraphErrors("70Mrad_PreAnneal.txt");
  PreMrad70->SetMarkerColor(8);
  PreMrad70->SetLineColor(8);
  PreMrad70->SetMarkerStyle(20);  
  TGraphErrors *PreMrad52p5 = new TGraphErrors("RSRun07Nov18ATLAS17GammaPreAnneal52p5Mrad_1/CCE_output_PF_ke.txt");
  PreMrad52p5->SetMarkerColor(28);
  PreMrad52p5->SetLineColor(28);
  PreMrad52p5->SetMarkerStyle(20);
  
  TGraphErrors *PostMrad35 = new TGraphErrors("35Mrad_PostAnneal.txt");
  PostMrad35->SetMarkerColor(kRed);
  PostMrad35->SetLineColor(kRed);
  PostMrad35->SetMarkerStyle(25);
  TGraphErrors *PostMrad70 = new TGraphErrors("70Mrad_PostAnneal.txt");
  PostMrad70->SetMarkerColor(8);
  PostMrad70->SetLineColor(8);
  PostMrad70->SetMarkerStyle(21);
  TGraphErrors *PostMrad52p5 = new TGraphErrors("RSRun08Nov18ATLAS17GammaPostAnneal52p5Mrad_2/CCE_output_PF_ke.txt");
  PostMrad52p5->SetMarkerColor(28);
  PostMrad52p5->SetLineColor(28);
  PostMrad52p5->SetMarkerStyle(21);
  TGraphErrors *PostMrad10 = new TGraphErrors("10Mrad_PostAnneal.txt");
  PostMrad10->SetMarkerColor(kBlack);
  PostMrad10->SetLineColor(kBlack);
  PostMrad10->SetMarkerStyle(21);
  TGraphErrors *PostMrad17p5 = new TGraphErrors("RSRun20Nov18ATLAS17PostAnneal17p5Mrad_2/CCE_output_PF_ke.txt");
  PostMrad17p5->SetMarkerColor(kBlue);
  PostMrad17p5->SetLineColor(kBlue);
  PostMrad17p5->SetMarkerStyle(21);
  TGraphErrors *PostMrad35Run2 = new TGraphErrors("RSRun11Dec18ATLAS17PostAnneal35Mrad_2/CCE_output_PF_ke.txt");
  PostMrad35Run2->SetMarkerColor(kRed);
  PostMrad35Run2->SetLineColor(kRed);
  PostMrad35Run2->SetMarkerStyle(21);
   
  TMultiGraph *Combined_CCE = new TMultiGraph();
  Combined_CCE->GetXaxis()->SetTitle("Bias Voltage [-kV]");
  Combined_CCE->GetYaxis()->SetTitle("Collected Charge [ke]");
  Combined_CCE->GetYaxis()->SetTitleOffset(1.35);
  Combined_CCE->Add(PreMrad10,"p");
  Combined_CCE->Add(PreMrad17p5,"p");
  Combined_CCE->Add(PreMrad35,"p");
  Combined_CCE->Add(PreMrad70,"p");
  Combined_CCE->Add(PreMrad52p5,"p");
  //Combined_CCE->Add(PostMrad35,"p");
  Combined_CCE->Add(PostMrad70,"p");
  Combined_CCE->Add(PostMrad52p5,"p");
  Combined_CCE->Add(PostMrad10,"p");
  Combined_CCE->Add(PostMrad17p5,"p");
  Combined_CCE->Add(PostMrad35Run2,"p");
    
  TLegend *leg;
  leg = new TLegend(0.3,0.15,0.5,0.5);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(1000);
  leg->SetTextFont(42);
  leg->SetNColumns(1);
  leg->AddEntry(PreMrad10,"Pre-Annealing 10Mrad","lp");
  leg->AddEntry(PreMrad17p5,"Pre-Annealing 17.5Mrad","lp");
  leg->AddEntry(PreMrad35,"Pre-Annealing 35Mrad","lp");
  leg->AddEntry(PreMrad52p5,"Pre-Annealing 52.5Mrad","lp");
  leg->AddEntry(PreMrad70,"Pre-Annealing 70Mrad","lp");
  leg->AddEntry(PostMrad10,"Post-Annealing 10Mrad","lp");
  leg->AddEntry(PostMrad17p5,"Post-Annealing 17.5Mrad","lp");
  //leg->AddEntry(PostMrad35,"Post-Annealing 35Mrad","lp");
  leg->AddEntry(PostMrad35Run2,"Post-Annealing 35Mrad","lp");
  leg->AddEntry(PostMrad52p5,"Post-Annealing 52.5Mrad","lp");
  leg->AddEntry(PostMrad70,"Post-Annealing 70Mrad","lp");
    
  TGaxis::SetMaxDigits(2);
  
  TCanvas *CCE = new TCanvas("CCE","CCE",600,600);
  Combined_CCE->Draw("AP");
  leg->Draw("same");
  
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.03);
  //latex.DrawLatex(0.72,0.2,"(Sensor no longer");
  //latex.DrawLatex(0.72,0.17,"holds voltage)");
  gPad->RedrawAxis();
  
  //CCE->SaveAs("Combined_CCE_Plot_ke.pdf");
 
}

//Principle is to convert ADC counts at temperature T to ADC counts at -25C for an unirradiated sensor (at plateu), which is what Patrick's equation (correction double) does. And then use the fact that at -25C unirradiated, 1 ADC = ~202 electrons.
