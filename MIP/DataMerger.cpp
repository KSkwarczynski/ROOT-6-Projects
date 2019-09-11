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
    
    const int NumberOfFiles=4;
    char filename[NumberOfFiles][200];
    sprintf(filename[0],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/MIP/Data/30August_14_MCR0_hadrons_1pt0Gev_0pt2T_4trigg___MuonCrosstalk.root");
    sprintf(filename[1],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/MIP/Data/30August_15_MCR0_hadrons_1pt0Gev_0pt2T_4trigg___MuonCrosstalk.root"); 
    sprintf(filename[2],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/MIP/Data/30August_17_MCR0_hadrons_1pt0Gev_0pt2T_4trigg___MuonCrosstalk.root");
    sprintf(filename[3],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/MIP/Data/30August_18_MCR0_hadrons_1pt0Gev_0pt2T_4trigg___MuonCrosstalk.root");
    
    TH2F *NewEventsMap_XY = new TH2F("NewEventsMap_XY","All_events_map_XY",  24,0,24, 8,0,8);
    TH2F *NewEventsMap_YZ = new TH2F("NewEventsMap_XY","All_events_map_YZ",  48,0,48, 8,0,8);
    TH2F *NewEventsMap_XZ = new TH2F("NewEventsMap_XY","All_events_map_XZ",  24,0,24, 48,0,48);
    
    TH1F *NewTrackDepositX = new TH1F("NewTrackDepositX", "Energy deposit by track X axis",500,0,500);
    TH1F *NewTrackDepositY = new TH1F("NewTrackDepositY", "Energy deposit by track Y axis",500,0,500);
        
    TH1F *NewCrosstalkEnergyDepositLeftX = new TH1F("NewCrosstalkEnergyDepositLeftX", "Crosstalk energy left from track deposit, in X plain",200,0,50);
    TH1F *NewCrosstalkEnergyDepositRightX = new TH1F("NewCrosstalkEnergyDepositRightX", "Crosstalk energy right from track deposit in X plain",200,0,50);
    
    TH1F *NewCrosstalkEnergyDepositLeftY = new TH1F("NewCrosstalkEnergyDepositLeftY", "Crosstalk energy left from track deposit, in Y plain",200,0,50);
    TH1F *NewCrosstalkEnergyDepositRightY = new TH1F("NewCrosstalkEnergyDepositRightY", "Crosstalk energy right from track deposit in Y plain",200,0,50);
    
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
        
        TH1F* TrackDepositXClone = (TH1F*) file->Get("TrackDepositX");
        NewTrackDepositX->Add(TrackDepositXClone);
        TH1F* TrackDepositYClone = (TH1F*) file->Get("TrackDepositY");
        NewTrackDepositY->Add(TrackDepositYClone);
        
        TH1F* CrosstalkEnergyDepositLeftXClone = (TH1F*) file->Get("CrosstalkEnergyDepositLeftX");
        NewCrosstalkEnergyDepositLeftX->Add(CrosstalkEnergyDepositLeftXClone);
        TH1F* CrosstalkEnergyDepositRightXClone = (TH1F*) file->Get("CrosstalkEnergyDepositRightX");
        NewCrosstalkEnergyDepositRightX->Add(CrosstalkEnergyDepositRightXClone);
        
        TH1F* CrosstalkEnergyDepositLeftYClone = (TH1F*) file->Get("CrosstalkEnergyDepositLeftY");
        NewCrosstalkEnergyDepositLeftY->Add(CrosstalkEnergyDepositLeftYClone);
        TH1F* CrosstalkEnergyDepositRightYClone = (TH1F*) file->Get("CrosstalkEnergyDepositRightY");
        NewCrosstalkEnergyDepositRightY->Add(CrosstalkEnergyDepositRightYClone);
        
        delete EventsMap_XYClone;
        delete EventsMap_YZClone;
        delete EventsMap_XZClone;
        delete TrackDepositXClone;
        delete TrackDepositYClone;
        delete CrosstalkEnergyDepositLeftXClone;
        delete CrosstalkEnergyDepositRightXClone;
        delete CrosstalkEnergyDepositLeftYClone;
        delete CrosstalkEnergyDepositRightYClone;
        
        file->Close();
        delete file;
    }
    TH2F *EventsMap_XY = (TH2F*)(NewEventsMap_XY->Clone("EventsMap_XY"));
    TH2F *EventsMap_YZ = (TH2F*)(NewEventsMap_YZ->Clone("EventsMap_YZ"));
    TH2F *EventsMap_XZ = (TH2F*)(NewEventsMap_XZ->Clone("EventsMap_XZ"));

    TH1F *TrackDepositX = (TH1F*)(NewTrackDepositX->Clone("TrackDepositX"));
    TrackDepositX->GetYaxis()->SetTitle("Number of events");
    TrackDepositX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *TrackDepositY = (TH1F*)(NewTrackDepositY->Clone("TrackDepositY"));
    TrackDepositY->GetYaxis()->SetTitle("Number of events");
    TrackDepositY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositLeftX = (TH1F*)(NewCrosstalkEnergyDepositLeftX->Clone("CrosstalkEnergyDepositLeftX"));
    TrackDepositY->GetYaxis()->SetTitle("Number of events");
    TrackDepositY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositRightX = (TH1F*)(NewCrosstalkEnergyDepositRightX->Clone("CrosstalkEnergyDepositRightX"));
    TrackDepositY->GetYaxis()->SetTitle("Number of events");
    TrackDepositY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositLeftY = (TH1F*)(NewCrosstalkEnergyDepositLeftY->Clone("CrosstalkEnergyDepositLeftY"));
    TrackDepositY->GetYaxis()->SetTitle("Number of events");
    TrackDepositY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *NewCrosstalkEnergyDepositRightY = (TH1F*)(NewCrosstalkEnergyDepositRightY->Clone("CrosstalkEnergyDepositRightY"));
    TrackDepositY->GetYaxis()->SetTitle("Number of events");
    TrackDepositY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TFile *fileout = new TFile("/Users/kolos/Desktop/Studia/CIS/Crosstalk/MIP/Data/MergedCrosstalk.root","RECREATE");
    if ( fileout->IsOpen() )
    {
        printf("File opened successfully\n");
    }  
        
    fileout->cd();
    
    EventsMap_XY->Write();
    EventsMap_YZ->Write();
    EventsMap_XZ->Write();
    
    TrackDepositX->Write();
    TrackDepositY->Write();
    
    CrosstalkEnergyDepositLeftX->Write();
    CrosstalkEnergyDepositRightX->Write();
    
    CrosstalkEnergyDepositLeftY->Write();
    NewCrosstalkEnergyDepositRightY->Write();
    
    cout<<"udalo sie"<<endl;
    
    fileout->Close();
    delete fileout;
        
}
