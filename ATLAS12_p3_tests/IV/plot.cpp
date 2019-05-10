#include "ReadFile.hpp"
#include <iostream>
#include <fstream>

void plot()
{
  Data data;
  data=ReadFile("IV_sweep.txt");
  ifstream IV;
  std::string line{""};
  int linecount{0};
  std::vector<double> voltage, current, evoltage, ecurrent;
  IV.open("IV.txt");
  while(!IV.eof())
    {
      ++linecount;
      getline(IV,line);
      if(linecount>2)
      {
	double v, c1, c2, c3, T;
	stringstream ss(line);
	ss >> v >> c1 >> c2 >> c3 >> T;
	voltage.push_back(v);
	evoltage.push_back(0.05);
	current.push_back((c1+c2+c3)*1.e-9/3.);
	ecurrent.push_back(pow(pow(c1-(c1+c2+c3)/3.,2)+pow(c2-(c1+c2+c3)/3.,2)+pow(c3-(c1+c2+c3)/3.,2)/2.,0.5)*1.e-9);
      }      
    }
  
  TGraphErrors *g_sweep = new TGraphErrors(data.voltage.size(),&(data.voltage[0]),&(data.current[0]),&(data.evoltage[0]),&(data.ecurrent[0]));
  TGraphErrors *g_manual = new TGraphErrors(voltage.size(),&(voltage[0]),&(current[0]),&(evoltage[0]),&(ecurrent[0]));
  g_sweep->SetMarkerStyle(20);
  g_manual->SetMarkerStyle(20);
  g_sweep->SetMarkerColor(kBlue);
  g_manual->SetMarkerColor(kRed);

  TMultiGraph *mg = new TMultiGraph();
  mg->Add(g_sweep,"p");
  mg->Add(g_manual,"p");

  TCanvas *c = new TCanvas("c","c",600,600);
  mg->GetXaxis()->SetTitle("Reverse Bias [V]");
  mg->GetYaxis()->SetTitle("Leakage Current [nA]");
  mg->Draw("AP");
  c->SaveAs("IV_overlay.root");
}
