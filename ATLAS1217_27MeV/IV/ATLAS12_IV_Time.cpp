#include <iostream>
#include <fstream>
#include "rootlogonATLAS.h"

struct Data
{
  std::vector<double> time; // s
  std::vector<double> voltage; // V
  std::vector<double> current; // A
  std::vector<double> timebin;
  std::vector<double> voltagebin;
  std::vector<double> currentbin;
};

int ATLAS12_IV_Time()
{
  rootlogonATLAS();
  ifstream inFile;
  Data data;
  inFile.open("ATLAS12_p2_PostAnneal_IV_time.txt");
  if(!inFile.good())
    {
      std::cout<<"Error opening file..."<<std::endl;
      return 0;
    }
  std::string line{""};
  int linecount{0};
  double time{0.};
  double ndouble = 500.;
  int nint = 500;
  std::string timestamp;
  double voltage, current;
  while(!inFile.eof())
    {
      ++linecount;
      getline(inFile,line);
      if(linecount >= 19)
	{
	  stringstream ss(line);
	  ss >> timestamp >> voltage >> current;
	  data.voltage.push_back(voltage);
	  data.current.push_back(current);

	  if((linecount-19.)/ndouble == (linecount - 19)/nint && linecount != 19)
	    {
	      time += 0.4;
	    }
	  else if(linecount != 19)
	    {
	      time += 1.2;
	    }
	  data.time.push_back(time);

	  //std::cout << data.time[linecount-19] << "\t" << data.voltage[linecount-19] << "\t" << data.current[linecount-19] << std::endl;
	}
    }

  int n{1};
  int count = 5;
  double voltagesum = 0.;
  double currentsum = 0.;
  for(int i{0}; i<data.time.size(); ++i)
    {
      if(n != count){++n;}
      else if(n==count)
	{
	  n=1;
	  data.timebin.push_back(data.time[i]);
	  voltagesum = 0.;
	  currentsum = 0.;
	  for(int n1{0}; n1<count; ++n1)
	    {
	      voltagesum += data.voltage[i-n1];
	      currentsum += data.current[i-n1];
	    }
	  data.voltagebin.push_back(voltagesum/(count*1.));
	  data.currentbin.push_back(currentsum/(count*1.));
	}
    }
  for(int i{0}; i<data.timebin.size(); ++i)
    {
      std::cout<<data.timebin[i]<<"\t"<<data.voltagebin[i]<<"\t"<<data.currentbin[i]<<std::endl;
    }
  
 
  TGraph2D *g2D = new TGraph2D();
  g2D->SetTitle(";Time [s];Voltage [V]; Current [A]");
  Double_t x,y,z;
  for(int i{0}; i<data.timebin.size(); ++i)
    {
      x=data.timebin[i];
      y=data.voltagebin[i];
      z=data.currentbin[i];
      g2D->SetPoint(i,x,y,z);
    }
  TCanvas *g2Dcan = new TCanvas("g2Dcan","g2Dcan",600,600);
  g2D->Draw("surf1");

  TGraph *g1D = new TGraph(data.time.size(),&(data.time[0]),&(data.current[0]));
  g1D->GetXaxis()->SetTitle("Time [s]");
  g1D->GetYaxis()->SetTitle("Current [A]");
  g1D->SetTitle("");
  g1D->SetLineColor(kRed);
  g1D->SetMarkerSize(1);
  TCanvas *g1Dcan = new TCanvas("g1Dcan","g1Dcan",600,600);
  g1D->Draw("ALP");

  TGraph *g1Dbin = new TGraph(data.timebin.size(),&(data.timebin[0]),&(data.currentbin[0]));
  g1Dbin->GetXaxis()->SetTitle("Time [s]");
  g1Dbin->GetYaxis()->SetTitle("Current [A]");
  g1Dbin->SetTitle("");
  g1Dbin->SetLineColor(kRed);
  g1Dbin->SetMarkerSize(1);
  TCanvas *g1Dbincan = new TCanvas("g1Dbincan","g1Dbincan",600,600);
  g1Dbin->Draw("ALP");
  
  return 0;
}
