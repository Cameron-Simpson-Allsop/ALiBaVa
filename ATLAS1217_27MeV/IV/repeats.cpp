#include <iostream>
#include <fstream>
#include <vector>
#include "rootlogonATLAS.h"

struct Data
{
  std::vector<double> voltage;
  std::vector<double> current;
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

void repeats()
{
  rootlogonATLAS();
  std::vector<string> files{"ATLAS17_mini4_IV_PreAnneal_manual.txt","ATLAS17_mini4_IV_PreAnneal_run2_manual.txt"};
  TMultiGraph *mg = new TMultiGraph();
  for(int i{0}; i<files.size(); ++i)
    {
      Data data1 = ReadFile("Pre-Annealing/"+files[i]);
      TGraphErrors *g = new TGraphErrors(data1.voltage.size(),&(data1.voltage[0]),&(data1.current[0]),&(data1.evoltage[0]),&(data1.ecurrent[0]));
      g->SetMarkerColor(i+1);
      g->SetMarkerStyle(i+20);
      mg->Add(g,"p");
    }
  TCanvas *c = new TCanvas("c","",600,600);
  mg->GetYaxis()->SetTitle("Leakage Current [nA]");
  mg->GetXaxis()->SetTitle("Reverse Bias [V]");
  mg->Draw("AP");
  c->SaveAs("ATLAS17_mini4_IV_PreAnnealing_manual.pdf");

}
