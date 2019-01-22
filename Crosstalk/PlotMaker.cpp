#include <TH2F.h>
#include <fstream>
#include <iostream>

void PlotMaker()
{
    char filename[200];
    sprintf(filename,"/Users/kolos/Desktop/Studia/CIS/Data/27August_1_MCR0_hadrons_0pt8Gev_0pt0T_Beam___Crosstalk.root");
    TFile *file = new TFile(filename,"READ");
    file->IsOpen();
    
    file->cd();
    
    TH2F* EnergyTrigTimeX = (TH2F*) file->Get("EnergyTrigTimeX");
    TH2F* EnergyTrigTimeY = (TH2F*) file->Get("EnergyTrigTimeY");
    TH2F* EnergyTrigTimeCrosstalkX = (TH2F*) file->Get("EnergyTrigTimeCrosstalkX");
    TH2F* EnergyTrigTimeCrosstalkY = (TH2F*) file->Get("EnergyTrigTimeCrosstalkY");
    TH2F* EnergyTrigTimeSignalX = (TH2F*) file->Get("EnergyTrigTimeSignalX");
    TH2F* EnergyTrigTimeSignalY = (TH2F*) file->Get("EnergyTrigTimeSignalY");


    TCanvas *Canvas = new TCanvas("Canvas","Canvas", 1400, 1000);
    Canvas->Divide(3,2);
    Canvas -> cd(1);
    EnergyTrigTimeX->Draw("COLZ");
    Canvas -> cd(2);
    EnergyTrigTimeCrosstalkX->Draw("COLZ");
    Canvas -> cd(3);
    EnergyTrigTimeSignalX->Draw("COLZ");
    Canvas -> cd(4);
    EnergyTrigTimeY->Draw("COLZ");
    Canvas -> cd(5);
    EnergyTrigTimeCrosstalkY->Draw("COLZ");
    Canvas -> cd(6);
    EnergyTrigTimeSignalX->Draw("COLZ");
}
