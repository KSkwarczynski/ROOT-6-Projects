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
    sprintf(filename[0],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/MIP/Data/1September_18_MCR0_hadrons_2Gev_0pt2T_4trigg_0deg___MuonCrosstalk.root");
    sprintf(filename[1],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/MIP/Data/1September_20_MCR0_muons_2Gev_0pt2T_4trigg_0deg___MuonCrosstalk.root"); 

    
    TH2F *NewEventsMap_XY = new TH2F("NewEventsMap_XY","NewEventsMap_XY",  24,0,24, 8,0,8);
    TH2F *NewEventsMap_YZ = new TH2F("NewEventsMap_YZ","NewEventsMap_YZ",  48,0,48, 8,0,8);
    TH2F *NewEventsMap_XZ = new TH2F("NewEventsMap_XZ","NewEventsMap_XZ",  24,0,24, 48,0,48);
    
    TH1F *TrackDepositX = new TH1F("TrackDepositX", "Energy deposit by track X axis",500,0,500);
    TH1F *TrackDepositY = new TH1F("TrackDepositY", "Energy deposit by track Y axis",500,0,500);
        
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
        
        delete EventsMap_XYClone;
        delete EventsMap_YZClone;
        delete EventsMap_XZClone;
        delete TrackDepositXClone;
        delete TrackDepositYClone;
        
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
    
    TFile *fileout = new TFile("/Users/kolos/Desktop/Studia/CIS/Data/MergedCrosstalk.root","RECREATE");
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
    
    cout<<"udalo sie"<<endl;
    
    fileout->Close();
    delete fileout;
        
}
