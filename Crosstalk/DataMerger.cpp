#include <TH2F.h>
#include <fstream>
#include <iostream>
#include "TStyle.h"
#include "TCutG.h"

void DataMerger()
{
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(111);
    gStyle->SetPalette(1,0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    
    const int NumberOfFiles=2;
    char filename[NumberOfFiles][200];
    sprintf(filename[0],"/Users/kolos/Desktop/Studia/CIS/Data/27August_1_MCR0_hadrons_0pt8Gev_0pt0T_Beam___Crosstalk.root");
    sprintf(filename[1],"/Users/kolos/Desktop/Studia/CIS/Data/26August_26_MCR0_hadrons_0pt8Gev_0pt0T_Beam___Crosstalk.root"); 
      
    TH1F *NewCrosstalkEnergyDepositX = new TH1F("NewCrosstalkEnergyDepositX", "Crosstalk energy in X plain",500,0,500);
    
    TH1F *NewCrosstalkEnergyDepositY = new TH1F("NewCrosstalkEnergyDepositY", "Crosstalk energy in Y plain",500,0,500);

    
    for(int i=0; i<NumberOfFiles; i++)
    {
        TFile *file = new TFile(filename[i],"READ");
        if ( file->IsOpen() )
        {
            printf("File opened successfully\n");
        }   
        
        //file->cd();
        TH1F* CrosstalkEnergyDepositXClone = (TH1F*) file->Get("CrosstalkEnergyDepositX");
        NewCrosstalkEnergyDepositX->Add(CrosstalkEnergyDepositXClone);
        TH1F* CrosstalkEnergyDepositYClone = (TH1F*) file->Get("CrosstalkEnergyDepositY");
        NewCrosstalkEnergyDepositY->Add(CrosstalkEnergyDepositYClone);
    
        delete CrosstalkEnergyDepositXClone;
        delete CrosstalkEnergyDepositYClone;
        
        
        file->Close();
        delete file;
    }
    
    TH1F *CrosstalkEnergyDepositX = (TH1F*)(NewCrosstalkEnergyDepositX->Clone("CrosstalkEnergyDepositX"));
    TH1F *CrosstalkEnergyDepositY = (TH1F*)(NewCrosstalkEnergyDepositY->Clone("CrosstalkEnergyDepositY"));
    
    TFile *fileout = new TFile("/Users/kolos/Desktop/Studia/CIS/Data/MergedCrosstalk.root","RECREATE");
    if ( fileout->IsOpen() )
    {
        printf("File opened successfully\n");
    }  
        
    fileout->cd();
    
    CrosstalkEnergyDepositX->Write();
    CrosstalkEnergyDepositY->Write();
        
    fileout->Close();
    delete fileout;
}
