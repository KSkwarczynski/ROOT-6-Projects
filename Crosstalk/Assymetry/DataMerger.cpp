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
    
    const int NumberOfFiles=8;
    char filename[NumberOfFiles][200];
    sprintf(filename[0],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/StoppingProton/Assymetry/Data/27August_1_MCR0_hadrons_0pt8Gev_0pt0T_Beam___CrosstalkAsymmetry.root");
    sprintf(filename[1],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/StoppingProton/Assymetry/Data/27August_2_MCR0_hadrons_0pt8Gev_0pt0T_Beam___CrosstalkAsymmetry.root"); 
    sprintf(filename[2],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/StoppingProton/Assymetry/Data/26August_26_MCR0_hadrons_0pt8Gev_0pt0T_Beam___CrosstalkAsymmetry.root"); 
    sprintf(filename[3],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/StoppingProton/Assymetry/Data/26August_14_MCR0_hadrons_0pt8Gev_0pt0T_Beam___CrosstalkAsymmetry.root"); 
    sprintf(filename[4],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/StoppingProton/Assymetry/Data/26August_13_MCR0_hadrons_0pt8Gev_0pt0T_Beam___CrosstalkAsymmetry.root");
    sprintf(filename[5],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/StoppingProton/Assymetry/Data/26August_12_MCR0_hadrons_0pt8Gev_0pt0T_Beam___CrosstalkAsymmetry.root");
    sprintf(filename[6],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/StoppingProton/Assymetry/Data/26August_11_MCR0_hadrons_0pt8Gev_0pt0T_Beam___CrosstalkAsymmetry.root");
    sprintf(filename[7],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/StoppingProton/Assymetry/Data/26August_9_MCR0_hadrons_0pt8Gev_0pt0T_Beam___CrosstalkAsymmetry.root");
    
    TH2F *NewEventsMap_XY = new TH2F("NewEventsMap_XY","NewEventsMap_XY",  24,0,24, 8,0,8);
    TH2F *NewEventsMap_YZ = new TH2F("NewEventsMap_YZ","NewEventsMap_YZ",  48,0,48, 8,0,8);
    TH2F *NewEventsMap_XZ = new TH2F("NewEventsMap_XZ","NewEventsMap_XZ",  24,0,24, 48,0,48);
    
    TH2F *NewEnergyTrigTimeAll = new TH2F("NewEnergyTrigTimeAll","Energy and Time of Trigger whole run", 100,-100,100,500,0,1500);
    
    TH2F *NewEnergyTrigTimeX = new TH2F("NewEnergyTrigTimeX","Energy and Time of Trigger X axis stopping point + Crosstalk", 100,-100,100,500,0,1500);
    TH2F *NewEnergyTrigTimeY = new TH2F("NewEnergyTrigTimeY","Energy and Time of Trigger Y axis stopping point + Crosstalk", 100,-100,100,500,0,1500);
    
    TH1F *NewHistogramHighestEnergyDeposit = new TH1F("NewHistogramHighestEnergyDeposit", "Histogram of highest value deposit",100,0,2500);
    TH1F *NewHistogramRealPeakEnergyDeposit = new TH1F("NewHistogramRealPeakEnergyDeposit", "Histogram of found stopping proton deposit",100,0,2500);
    TH1F *NewStoppingPointLocation = new TH1F("NewStoppingPointLocation", "Location of stopping point",48,0,48);

    TH1F *NewCrosstalkEnergyDepositX = new TH1F("NewCrosstalkEnergyDepositX", "Crosstalk energy in X plain",500,0,500);
    TH1F *NewCrosstalkEnergyDepositY = new TH1F("NewCrosstalkEnergyDepositY", "Crosstalk energy in Y plain",500,0,500);
    
    TH1F *NewCrosstalkHistogramDifferenceX = new TH1F("NewCrosstalkHistogramDifferenceX", "Crosstalk right subtracted by crosstalk on the left in X plain",100.0,-50.0,50.0);
    TH1F *NewCrosstalkHistogramDifferenceY = new TH1F("NewCrosstalkHistogramDifferenceY", "Crosstalk right subtracted by crosstalk on the left in Y plain",100.0,-50.0,50.0);

    for(int i=0; i<NumberOfFiles; i++)
    {
        TFile *file = new TFile(filename[i],"READ");
        if ( file->IsOpen() )
        {
            printf("File opened successfully\n");
        }   
        //file->cd();
        
        TH2F* EventsMap_XYClone = (TH2F*) file->Get("EventsMap_XY");
        NewEventsMap_XY->Add(EventsMap_XYClone);
        TH2F* EventsMap_YZClone = (TH2F*) file->Get("EventsMap_YZ");
        NewEventsMap_YZ->Add(EventsMap_YZClone);
        TH2F* EventsMap_XZClone = (TH2F*) file->Get("EventsMap_XZ");
        NewEventsMap_XZ->Add(EventsMap_XZClone);
        
        TH2F* EnergyTrigTimeAllClone = (TH2F*) file->Get("EnergyTrigTimeAll");
        NewEnergyTrigTimeAll->Add(EnergyTrigTimeAllClone);

        TH2F* EnergyTrigTimeXClone = (TH2F*) file->Get("EnergyTrigTimeX");
        NewEnergyTrigTimeX->Add(EnergyTrigTimeXClone);
        TH2F* EnergyTrigTimeYClone = (TH2F*) file->Get("EnergyTrigTimeY");
        NewEnergyTrigTimeY->Add(EnergyTrigTimeYClone);
        
        TH1F* HistogramHighestEnergyDepositClone = (TH1F*) file->Get("HistogramHighestEnergyDeposit");
        NewHistogramHighestEnergyDeposit->Add(HistogramHighestEnergyDepositClone);
        
        TH1F* HistogramRealPeakEnergyDepositClone = (TH1F*) file->Get("HistogramRealPeakEnergyDeposit");
        NewHistogramRealPeakEnergyDeposit->Add(HistogramRealPeakEnergyDepositClone);
        
        TH1F* StoppingPointLocationClone = (TH1F*) file->Get("StoppingPointLocation");
        NewStoppingPointLocation->Add(StoppingPointLocationClone);
        
        TH1F* CrosstalkEnergyDepositXClone = (TH1F*) file->Get("CrosstalkEnergyDepositX");
        NewCrosstalkEnergyDepositX->Add(CrosstalkEnergyDepositXClone);
        TH1F* CrosstalkEnergyDepositYClone = (TH1F*) file->Get("CrosstalkEnergyDepositY");
        NewCrosstalkEnergyDepositY->Add(CrosstalkEnergyDepositYClone);
        
        TH1F* CrosstalkHistogramDifferenceXClone = (TH1F*) file->Get("CrosstalkHistogramDifferenceX");
        NewCrosstalkHistogramDifferenceX->Add(CrosstalkHistogramDifferenceXClone);
        TH1F* CrosstalkHistogramDifferenceYClone = (TH1F*) file->Get("CrosstalkHistogramDifferenceY");
        NewCrosstalkHistogramDifferenceY->Add(CrosstalkHistogramDifferenceYClone);
        
        
        delete EventsMap_XYClone;
        delete EventsMap_YZClone;
        delete EventsMap_XZClone;
        delete EnergyTrigTimeAllClone;
        delete EnergyTrigTimeXClone;
        delete EnergyTrigTimeYClone;
        delete HistogramHighestEnergyDepositClone;
        delete HistogramRealPeakEnergyDepositClone;
        delete StoppingPointLocationClone;
        delete CrosstalkEnergyDepositXClone;
        delete CrosstalkEnergyDepositYClone;
        delete CrosstalkHistogramDifferenceXClone;
        delete CrosstalkHistogramDifferenceYClone;
        
        file->Close();
        delete file;
    }
    
    TH2F *EventsMap_XY = (TH2F*)(NewEventsMap_XY->Clone("EventsMap_XY"));
    TH2F *EventsMap_YZ = (TH2F*)(NewEventsMap_YZ->Clone("EventsMap_YZ"));
    TH2F *EventsMap_XZ = (TH2F*)(NewEventsMap_XZ->Clone("EventsMap_XZ"));

    TH2F *EnergyTrigTimeAll = (TH2F*)(NewEnergyTrigTimeAll->Clone("EnergyTrigTimeAll"));
    EnergyTrigTimeAll->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeAll->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");

    TH2F *EnergyTrigTimeX = (TH2F*)(NewEnergyTrigTimeX->Clone("EnergyTrigTimeX"));
    EnergyTrigTimeX->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeX->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    TH2F *EnergyTrigTimeY = (TH2F*)(NewEnergyTrigTimeY->Clone("EnergyTrigTimeY"));
    EnergyTrigTimeY->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeY->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH1F *HistogramHighestEnergyDeposit = (TH1F*)(NewHistogramHighestEnergyDeposit->Clone("HistogramHighestEnergyDeposit"));
    HistogramHighestEnergyDeposit->GetYaxis()->SetTitle("Number of events");
    HistogramHighestEnergyDeposit->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *HistogramRealPeakEnergyDeposit = (TH1F*)(NewHistogramRealPeakEnergyDeposit->Clone("HistogramRealPeakEnergyDeposit"));
    HistogramRealPeakEnergyDeposit->GetYaxis()->SetTitle("Number of events");
    HistogramRealPeakEnergyDeposit->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *StoppingPointLocation = (TH1F*)(NewStoppingPointLocation->Clone("StoppingPointLocation"));
    StoppingPointLocation->GetYaxis()->SetTitle("Number of events");
    StoppingPointLocation->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositX = (TH1F*)(NewCrosstalkEnergyDepositX->Clone("CrosstalkEnergyDepositX"));
    CrosstalkEnergyDepositX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositY = (TH1F*)(NewCrosstalkEnergyDepositY->Clone("CrosstalkEnergyDepositY"));
    CrosstalkEnergyDepositY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkHistogramDifferenceX = (TH1F*)(NewCrosstalkHistogramDifferenceX->Clone("CrosstalkHistogramDifferenceX"));
    CrosstalkHistogramDifferenceX->GetYaxis()->SetTitle("Number of events");
    CrosstalkHistogramDifferenceX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkHistogramDifferenceY = (TH1F*)(NewCrosstalkHistogramDifferenceY->Clone("CrosstalkHistogramDifferenceY"));
    CrosstalkHistogramDifferenceY->GetYaxis()->SetTitle("Number of events");
    CrosstalkHistogramDifferenceY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    
    TFile *fileout = new TFile("/Users/kolos/Desktop/Studia/CIS/Crosstalk/StoppingProton/Assymetry/Data/MergedCrosstalk.root","RECREATE");
    if ( fileout->IsOpen() )
    {
        printf("File opened successfully\n");
    }  
        
    fileout->cd();
    
    EventsMap_XY->Write();
    EventsMap_YZ->Write();
    EventsMap_XZ->Write();
    
    EnergyTrigTimeAll->Write();
    
    EnergyTrigTimeX->Write();
    EnergyTrigTimeY->Write();
    
    HistogramHighestEnergyDeposit->Write();
    HistogramRealPeakEnergyDeposit->Write();
    
    StoppingPointLocation->Write();
    
    CrosstalkEnergyDepositX->Write();
    CrosstalkEnergyDepositY->Write();
    
    CrosstalkHistogramDifferenceX->Write();
    CrosstalkHistogramDifferenceY->Write();
    
    cout<<"udalo sie"<<endl;
    
    fileout->Close();
    delete fileout;
        
}
