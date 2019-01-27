#include <stdio.h>
#include <string.h>
#include <exception>
#include <fstream>
#include <vector>
#include "TFile.h"
#include "TDirectory.h"
#include "TH1D.h"
#include "TSystem.h"
#include "TMacro.h"
#include <TTree.h>
#include <iostream>
#include <sstream>
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TCanvas.h"
#include <iterator>
#include <algorithm>
#include "TImage.h"
#include "TStyle.h"

using namespace std;

string GetLocation(string str)
{
    int i = str.rfind("_Slot_");
    string way = str.substr(0,i);
    return way;
}

struct vectorsTree
{
  vector<double> *FEBSN;
  vector<double> *SpillTag;
  vector<double> *GTrigTag;
  vector<double> *GTrigTime;
  vector<double> *hitsChannel;
  vector<double> *hitAmpl;
  vector<double> *hitAmplRec;
  vector<double> *hitLGAmpl;
  vector<double> *hitLGAmplRec;
  vector<double> *hitHG_pe;
  vector<double> *hitLG_pe;
  vector<double> *hitToT_pe;
  vector<double> *hitCharge_pe;
  vector<double> *hitLeadTime;
  vector<double> *hitTrailTime;
  vector<double> *hitTimeDif;
  vector<double> *hitTimefromSpill;

};


int main ()
{

    int NumberOfEB = 30;
    int FEBs[19] = {0,1,2,3,4,8,9,10,11,12,16,17,18,19,20,24,25,26,27};

    vector<string> vFileNames;
    string sFileName;
    ifstream fList("febs_files_list.list");
    while (!fList.eof())
    {
        fList >> sFileName;
        vFileNames.push_back(sFileName);
    }
    fList.close();

    string rootFileInput=GetLocation(vFileNames[0].c_str());
    string rootFileOutput=GetLocation (vFileNames[0].c_str());
    rootFileInput+="_all_reconstructed.root";
    //rootFileInput+="_all.root";
    rootFileOutput+="_Crosstalk.root";
    cout << rootFileInput<<endl;

    TFile *FileInput = new TFile(rootFileInput.c_str());

    vectorsTree FEB[NumberOfEB];

    for (Int_t i=0;i<NumberOfEB;i++)
    {
        FEB[i].FEBSN=0;
        FEB[i].SpillTag=0;
        FEB[i].hitsChannel=0;
        FEB[i].hitAmpl=0;
        FEB[i].hitAmplRec=0;
        FEB[i].hitLeadTime=0;
        FEB[i].GTrigTag=0;
        FEB[i].GTrigTime=0;
        FEB[i].hitLGAmpl=0;
        FEB[i].hitLGAmplRec=0;
        FEB[i].hitTrailTime=0;
        FEB[i].hitTimeDif=0;
        FEB[i].hitTimefromSpill=0;

        FEB[i].hitHG_pe=0;
        FEB[i].hitLG_pe=0;
        FEB[i].hitToT_pe=0;
        FEB[i].hitCharge_pe=0;

    }

    TTree *FEBtree[NumberOfEB];
    Long64_t nentries[NumberOfEB];
    std::fill(nentries, nentries + NumberOfEB, 0);

    ostringstream sFEBnum;
    string sFEB;

    vector<int> FEBnumbers;
    FEBnumbers.clear();

    for (Int_t ih=0; ih<NumberOfEB; ih++)
    {
        sFEBnum.str("");
        sFEBnum << ih;
        sFEB = "FEB_"+sFEBnum.str();
        FEBtree[ih] = (TTree*)FileInput->Get(sFEB.c_str());
        if ((TTree*)FileInput->Get(sFEB.c_str()))
        {
            FEBtree[ih]->SetBranchAddress((sFEB+"_SN").c_str(),&FEB[ih].FEBSN);
            FEBtree[ih]->SetBranchAddress((sFEB+"_SpillTag").c_str(),&FEB[ih].SpillTag);
            FEBtree[ih]->SetBranchAddress((sFEB+"_GTrigTag").c_str(),&FEB[ih].GTrigTag);
            FEBtree[ih]->SetBranchAddress((sFEB+"_GTrigTime").c_str(),&FEB[ih].GTrigTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitsChannel").c_str(),&FEB[ih].hitsChannel);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitAmpl").c_str(),&FEB[ih].hitAmpl);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLGAmpl").c_str(),&FEB[ih].hitLGAmpl);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLeadTime").c_str(),&FEB[ih].hitLeadTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTrailTime").c_str(),&FEB[ih].hitTrailTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTimeDif").c_str(),&FEB[ih].hitTimeDif);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTimefromSpill").c_str(),&FEB[ih].hitTimefromSpill);

            FEBtree[ih]->SetBranchAddress((sFEB+"_hitAmplRecon").c_str(), &FEB[ih].hitAmplRec);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLGAmplRecon").c_str(), &FEB[ih].hitLGAmplRec);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitHG_pe").c_str(), &FEB[ih].hitHG_pe);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLG_pe").c_str(), &FEB[ih].hitLG_pe);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitToT_pe").c_str(), &FEB[ih].hitToT_pe);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitCharge_pe").c_str(), &FEB[ih].hitCharge_pe);

            nentries[ih] = FEBtree[ih]->GetEntries();
            FEBtree[ih]->GetEntry(0);
        }
    }

    double minEn = nentries[0];
    for(int i = 0; i < NumberOfEB; i++)
    {
        if(nentries[i] < minEn && nentries[i]>0)
        {
            minEn = nentries[i];
        }
    }
    cout << "Number of spills " << minEn << endl;

    TFile wfile(rootFileOutput.c_str(), "recreate");
    cout<<rootFileOutput<<endl;

    int MapCon[28][2][96];
    for (int iFEB = 0; iFEB<19; iFEB++)
    {
        if (FEBs[iFEB] != 12)
        {
            sFEBnum.str("");
            sFEBnum << FEBs[iFEB];
            sFEB = "../mapping/" + sFEBnum.str() + ".txt";
            ifstream fmap(sFEB.c_str());
            int temp=0;
            while (!fmap.eof())
            {
                fmap >> temp >> MapCon[FEBs[iFEB]][0][temp] >>MapCon[FEBs[iFEB]][1][temp];
                //cout<<temp<<" "<<MapCon[FEBs[iFEB]][0][temp]<<" "<<MapCon[FEBs[iFEB]][1][temp]<<endl;
                //temp++;
            }
            fmap.close();
       }
    }

    TH2F *EventsMap_XY = new TH2F("All_events_map_XY","All_events_map_XY",  24,0,24, 8,0,8);
    TH2F *EventsMap_YZ = new TH2F("All_events_map_YZ","All_events_map_YZ",  48,0,48, 8,0,8);
    TH2F *EventsMap_XZ = new TH2F("All_events_map_XZ","All_events_map_XZ",  24,0,24, 48,0,48);
    
    TH2F *EnergyTrigTimeAll = new TH2F("EnergyTrigTimeAll","Energy and Time of Trigger whole run", 100,-100,100,500,0,1500);
    EnergyTrigTimeAll->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeAll->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH1F *CrosstalkEnergyDepositX = new TH1F("CrosstalkEnergyDepositX", "Crosstalk energy in X plain",500,0,500);
    CrosstalkEnergyDepositX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositY = new TH1F("CrosstalkEnergyDepositY", "Crosstalk energy in Y plain",500,0,500);
    CrosstalkEnergyDepositY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositY->GetXaxis()->SetTitle("Energy [p.e.]");
       
    TH1F *StoppingPointLocation = new TH1F("StoppingPointLocation", "Location of stopping point",48,0,48);
    StoppingPointLocation->GetYaxis()->SetTitle("Number of events");
    StoppingPointLocation->GetXaxis()->SetTitle("Z detector axis [cm]");
    
    TH1F *HistogramHighestEnergyDeposit = new TH1F("HighestEnergyDepositHistogram", "Histogram of highest value deposit",500,0,2500);
    HistogramHighestEnergyDeposit->GetYaxis()->SetTitle("Number of events");
    HistogramHighestEnergyDeposit->GetXaxis()->SetTitle("Energy [p.e.]");
   
    TH1F *HistogramRealPeakEnergyDeposit = new TH1F("RealPeakEnergyDepositHistogram", "Histogram of found stopping proton deposit",500,0,2500);
    HistogramRealPeakEnergyDeposit->GetYaxis()->SetTitle("Number of events");
    HistogramRealPeakEnergyDeposit->GetXaxis()->SetTitle("Energy [p.e.]");

    TH1F *HistogramCrosstalkDistanceX= new TH1F("HistogramCrosstalkDistanceX", "Cube distance of energy deposit from peak X axis",48,-24,24);
    HistogramCrosstalkDistanceX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceX->GetXaxis()->SetTitle("X detector axis [cm]");
    
    TH1F *HistogramCrosstalkDistanceY = new TH1F("HistogramCrosstalkDistanceY", "Cube distance of energy deposit from peak Y axis",16,-8,8);
    HistogramCrosstalkDistanceY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceY->GetXaxis()->SetTitle("Y detector axis [cm]");

    TH1F *CrosstalkEnergyDepositRestrictedX= new TH1F("CrosstalkEnergyDepositRestrictedX", "Crosstalk energy in X plain maximaly 2 cubes from deposit",500,0,500);
    CrosstalkEnergyDepositRestrictedX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositRestrictedX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositRestrictedY= new TH1F("CrosstalkEnergyDepositRestrictedY", "Crosstalk energy in Y plain maximaly 2 cubes from deposit",500,0,500);
    CrosstalkEnergyDepositRestrictedY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositRestrictedY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *HistogramCrosstalkDistanceEnergyHigherThanY= new TH1F("HistogramCrosstalkDistanceEnergyHigherThanY", "Cube distance of energy deposit from peak Y axis if energy higher than 50",16,-8,8);
    HistogramCrosstalkDistanceEnergyHigherThanY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceEnergyHigherThanY->GetXaxis()->SetTitle("Y detector axis [cm]");
    
    TH1F *HistogramCrosstalkDistanceEnergyHigherThanX= new TH1F("HistogramCrosstalkDistanceEnergyHigherThanX", "Cube distance of energy deposit from peak X axis if energy higher than 50",48,-24,24);
    HistogramCrosstalkDistanceEnergyHigherThanX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceEnergyHigherThanX->GetXaxis()->SetTitle("X detector axis [cm]");
    
    TH1F *HistogramCrosstalkDistanceCutY= new TH1F("HistogramCrosstalkDistanceCutY", "Cube distance of energy deposit from peak Y axis if energy higher than 1",16,-8,8);
    HistogramCrosstalkDistanceCutY->GetYaxis()->SetTitle("Y detector axis [cm]");
    HistogramCrosstalkDistanceCutY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *HistogramCrosstalkDistanceCutX= new TH1F("HistogramCrosstalkDistanceCutX", "Cube distance of energy deposit from peak X axis if energy higher than 1",48,-24,24);
    HistogramCrosstalkDistanceCutX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceCutX->GetXaxis()->SetTitle("X detector axis [cm]");   
    
    TH1F *HistogramCrosstalkDistanceTypeX= new TH1F("HistogramCrosstalkDistanceTypeX", "Number of cubes that recieved signal X axis",48,0,48);
    HistogramCrosstalkDistanceTypeX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceTypeX->GetXaxis()->SetTitle("X detector axis [cm]");   
    
    TH1F *HistogramCrosstalkDistanceTypeY= new TH1F("HistogramCrosstalkDistanceTypeY", "Number of cubes that recieved signal Y axis",16,0,16);
    HistogramCrosstalkDistanceTypeY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceTypeY->GetXaxis()->SetTitle("Y detector axis [cm]"); 
/////  
    TH2F *EnergyTrigTimeX = new TH2F("EnergyTrigTimeX","Energy and Time of Trigger X axis stopping proton+Crosstalk", 100,-100,100,500,0,1500);
    EnergyTrigTimeX->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeX->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH2F *EnergyTrigTimeY = new TH2F("EnergyTrigTimeY","Energy and Time of Trigger Y axis stopping proton+Crosstalk", 100,-100,100,500,0,1500);
    EnergyTrigTimeY->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeY->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH2F *EnergyTrigTimeCrosstalkX = new TH2F("EnergyTrigTimeCrosstalkX","Energy and Time of Trigger X axis only Crosstalk", 100,-100,100,500,0,1500);
    EnergyTrigTimeCrosstalkX->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeCrosstalkX->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH2F *EnergyTrigTimeCrosstalkY = new TH2F("EnergyTrigTimeCrosstalkY","Energy and Time of Trigger Y axis only Crosstalk", 100,-100,100,500,0,1500);
    EnergyTrigTimeCrosstalkY->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeCrosstalkY->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH2F *EnergyTrigTimeSignalX = new TH2F("EnergyTrigTimeSignalX","Energy and Time of Trigger X axis only Signal", 100,-100,100,500,0,1500);
    EnergyTrigTimeSignalX->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeSignalX->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH2F *EnergyTrigTimeSignalY = new TH2F("EnergyTrigTimeSignalY","Energy and Time of Trigger Y axis only Signal", 100,-100,100,500,0,1500);
    EnergyTrigTimeSignalY->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeSignalY->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
/////
    TH1F *CrosstalkEnergyDepositMinus1X = new TH1F("CrosstalkEnergyDepositMinus1X", "Crosstalk energy in X plain, one cube backward.",500,0,500);
    CrosstalkEnergyDepositMinus1X->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1X->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMinus1Y = new TH1F("CrosstalkEnergyDepositMinus1Y", "Crosstalk energy in Y plain, one cube backward.",500,0,500);
    CrosstalkEnergyDepositMinus1Y->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1Y->GetXaxis()->SetTitle("Energy [p.e.]"); 
    
    TH1F *HistogramCrosstalkDistanceMinus1X= new TH1F("HistogramCrosstalkDistanceMinus1X", "Cube distance of energy deposit from peak X axis, one cube backward",48,-24,24);
    HistogramCrosstalkDistanceMinus1X->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMinus1X->GetXaxis()->SetTitle("X detector axis [cm]");
    
    TH1F *HistogramCrosstalkDistanceMinus1Y = new TH1F("HistogramCrosstalkDistanceMinus1Y", "Cube distance of energy deposit from peak Y axis, one cube backward",16,-8,8);
    HistogramCrosstalkDistanceMinus1Y->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMinus1Y->GetXaxis()->SetTitle("Y detector axis [cm]");
/////
    TH1F *CrosstalkEnergyDepositMiddleX = new TH1F("CrosstalkEnergyDepositMiddleX", "Crosstalk energy in X plain, 15 cubes away from stopping poin.",500,0,500);
    CrosstalkEnergyDepositMiddleX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMiddleY = new TH1F("CrosstalkEnergyDepositMiddleY", "Crosstalk energy in Y plain, 15 cubes away from stopping poin..",500,0,500);
    CrosstalkEnergyDepositMiddleY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleY->GetXaxis()->SetTitle("Energy [p.e.]"); 
    
    TH1F *HistogramCrosstalkDistanceMiddleX= new TH1F("HistogramCrosstalkDistanceMiddleX", "Cube distance of energy deposit from peak X axis, 15 cubes away from stopping poin.",48,-24,24);
    HistogramCrosstalkDistanceMiddleX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMiddleX->GetXaxis()->SetTitle("X detector axis [cm]");
    
    TH1F *HistogramCrosstalkDistanceMiddleY = new TH1F("HistogramCrosstalkDistanceMiddleY", "Cube distance of energy deposit from peak Y axis, 15 cubes away from stopping poin.",16,-8,8);
    HistogramCrosstalkDistanceMiddleY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMiddleY->GetXaxis()->SetTitle("Y detector axis [cm]");
    
    TH1F *HistogramRealPeakEnergyDepositMiddle = new TH1F("HistogramRealPeakEnergyDepositMiddle", "Histogram of highest value deposit, 15 cubes away from stopping poin.",500,0,2500);
    HistogramRealPeakEnergyDepositMiddle->GetYaxis()->SetTitle("Number of events");
    HistogramRealPeakEnergyDepositMiddle->GetXaxis()->SetTitle("Energy [p.e.]");
/////
    TH2F *EnergyTrigTimeTestX = new TH2F("EnergyTrigTimeTestX","X", 100,-100,100,500,0,1500);
    TH2F *EnergyTrigTimeTestY = new TH2F("EnergyTrigTimeTestY","Y", 100,-100,100,500,0,1500);
    
    TH2F *EnergyTrigTimeTestUpgradeX = new TH2F("EnergyTrigTimeTestUpgradeX","Upgrade X", 100,-100,100,500,0,1500);
    TH2F *EnergyTrigTimeTestUpgradeY = new TH2F("EnergyTrigTimeTestUpgradeY","Upgrade Y", 100,-100,100,500,0,1500);
    
    TH2F *EnergyTrigTimeTestLowX = new TH2F("EnergyTrigTimeTestLowX","X low", 100,-100,100,500,0,1500);
    TH2F *EnergyTrigTimeTestLowY = new TH2F("EnergyTrigTimeTestLowY","Y low", 100,-100,100,500,0,1500);
    
    TDirectory *events2D = wfile.mkdir("events2D");
    TDirectory *CrossEnergy = wfile.mkdir("CrossEnergy");
    //TDirectory *CrossStep = wfile.mkdir("CrossStep");
    TDirectory *CrossEnergyPlain = wfile.mkdir("CrossEnergyPlain");
    int NumberEvDis = 10000; // zmiana 10000

    ostringstream sEventnum;
    string sEvent;
//////////////////Histogram Declaration///////////////////////////////////
    TH2F *event_XY[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "event_XY_"+sEventnum.str();
        event_XY[ih] = new TH2F(sEvent.c_str(),sEvent.c_str(), 24,0,24, 8,0,8);
        event_XY[ih]->GetYaxis()->SetTitle("Y axis [cm]");
        event_XY[ih]->GetXaxis()->SetTitle("X axis [cm]");
    }

    TH2F *event_YZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "event_YZ_"+sEventnum.str();
        event_YZ[ih] = new TH2F(sEvent.c_str(),sEvent.c_str(), 48,0,48, 8,0,8);
        event_YZ[ih]->GetYaxis()->SetTitle("Y axis [cm]");
        event_YZ[ih]->GetXaxis()->SetTitle("Z axis [cm]");
    }

    TH2F *event_XZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++){
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "event_XZ_"+sEventnum.str();
        event_XZ[ih] = new TH2F(sEvent.c_str(),sEvent.c_str(), 24,0,24, 48,0,48);
        event_XZ[ih]->GetYaxis()->SetTitle("Z axis [cm]");
        event_XZ[ih]->GetXaxis()->SetTitle("X axis [cm]");
    }

    TH1F *energy_Z[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "energy_Z_"+sEventnum.str();
        energy_Z[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(),48,0,48);
        energy_Z[ih]->GetYaxis()->SetTitle("Energy deposit [p.e.]");
        energy_Z[ih]->GetXaxis()->SetTitle("Z axis [cm]");
    }
//////////Energy
    TH1F *energyZ_XZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "energyZ_XZ_"+sEventnum.str();
        energyZ_XZ[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(),48,0,48);
        energyZ_XZ[ih]->GetYaxis()->SetTitle("Energy deposit [p.e.]");
        energyZ_XZ[ih]->GetXaxis()->SetTitle("Z axis [cm]");
    }

    TH1F *energyZ_YZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "energyZ_YZ_"+sEventnum.str();
        energyZ_YZ[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(),48,0,48);
        energyZ_YZ[ih]->GetYaxis()->SetTitle("Energy deposit [p.e.]");
        energyZ_YZ[ih]->GetXaxis()->SetTitle("Z axis [cm]");
    }

    TH1F *energyX_XZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "energyX_XZ_"+sEventnum.str();
        energyX_XZ[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(),24,0,24);
        energyX_XZ[ih]->GetYaxis()->SetTitle("Energy deposit [p.e.]");
        energyX_XZ[ih]->GetXaxis()->SetTitle("X axis [cm]");
    }

    TH1F *energyY_YZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "energyY_YZ"+sEventnum.str();
        energyY_YZ[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(),8,0,8);
        energyY_YZ[ih]->GetYaxis()->SetTitle("Energy deposit [p.e.]");
        energyY_YZ[ih]->GetXaxis()->SetTitle("Y axis [cm]");
    }
////////////Step
    /*
    TH1F *StepCounterX_XZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "StepCounterX_XZ_"+sEventnum.str();
        StepCounterX_XZ[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(),24,0,24);
    }

    TH1F *StepCounterY_YZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "StepCounterY_YZ_"+sEventnum.str();
        StepCounterY_YZ[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(),8,0,8);
    }

    TH1F *StepCounterZ_XZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "StepCounterZ_XZ_"+sEventnum.str();
        StepCounterZ_XZ[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(),48,0,48);
    }

    TH1F *StepCounterZ_YZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "StepCounterZ_YZ_"+sEventnum.str();
        StepCounterZ_YZ[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(),48,0,48);
    }

    TH1F *StepCounterZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "StepCounterZ"+sEventnum.str();
        StepCounterZ[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(),48,0,48);
    }
    */
//////Plain
    TH1F *energyY_YZ_Plain[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "energyY_YZ_Plain_"+sEventnum.str();
        energyY_YZ_Plain[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(),8,0,8);
        energyY_YZ_Plain[ih]->GetYaxis()->SetTitle("Energy deposit [p.e.]");
        energyY_YZ_Plain[ih]->GetXaxis()->SetTitle("Y axis [cm]");
    }
    TH1F *energyX_XZ_Plain[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "energyX_XZ_Plain_"+sEventnum.str();
        energyX_XZ_Plain[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(),24,0,24);
        energyX_XZ_Plain[ih]->GetYaxis()->SetTitle("Energy deposit [p.e.]");
        energyX_XZ_Plain[ih]->GetXaxis()->SetTitle("X axis [cm]");
    }

    double energyDepZ[48];
    double energyDepZ_XZ[48];
    double energyDepZ_YZ[48];
    double energyDepX_XZ[24];
    double energyDepY_YZ[8];
/*
    double StepX_XZ[24];
    double StepY_YZ[8];
    double StepZ_XZ[48];
    double StepZ_YZ[48];
    double StepZ[48];
*/
    double energyDepX_XZ_Plain[3][24];
    double energyDepY_YZ_Plain[3][8];

    int eventNum=0;

    int licznik=1;

    bool LargehitTimeDif = 0;
    
    double TriggerTime=0;
    
    TCanvas *DisplayCanvas = new TCanvas("DisplayCanvas","DisplayCanvas", 1400, 1000);
    TCanvas *CrossEnergyCanvas = new TCanvas("CrossEnergyCanvas","CrossEnergyCanvas", 1400, 1000);
    //TCanvas *CrossHitCanvas = new TCanvas("CrossHitCanvas","CrossHitCanvas", 1400, 1000);
    TCanvas *CrossEnergyPlainCanvas = new TCanvas("CrossEnergyPlainCanvas","CrossEnergyPlainCanvas", 1400, 1000);
    bool SpillMised = false;
    for (Int_t subSpill = 0; subSpill<minEn; subSpill++)
    {
        Int_t SpillNumber = subSpill;

        cout << "Getting Spill Number " << SpillNumber + 1 << endl;
        for (int ik = 0; ik < 19; ik++)
        {
            FEBtree[FEBs[ik]]->GetEntry(SpillNumber);
            if (FEB[FEBs[ik]].SpillTag->back() != SpillNumber + 1)
            {
                cout << "wtf" <<endl;
            }
            if (FEB[FEBs[ik]].SpillTag->size() < 2 )
            {
                cout << "NULL"<<endl;
                SpillMised = true;
                break;
            }
            else
            {
                SpillMised = false;
            }
        }
        if (!SpillMised)
        {

        for ( int TOFtrigger = 0; TOFtrigger < FEB[12].FEBSN->size(); TOFtrigger++)
            {
            if (FEB[12].hitTimeDif->at(TOFtrigger) > 0 && NumberEvDis > eventNum)
            {
                for (int ik = 0; ik < 48; ik++ ) //zerowanie tablic przechowujace dane, Z
                {
                    energyDepZ[ik] = 0;
                    energyDepZ_XZ[ik] = 0;
                    energyDepZ_YZ[ik] = 0;

                    //StepZ_XZ[ik] = 0;
                    //StepZ_YZ[ik] = 0;
                    //StepZ[ik] = 0;
                }
                for (int ik = 0; ik < 24; ik++ ) //zerowanie tablic przechowujace dane, X
                {
                    energyDepX_XZ[ik] = 0;
                    energyDepX_XZ_Plain[0][ik] = 0;
                    energyDepX_XZ_Plain[1][ik] = 0;
                    energyDepX_XZ_Plain[2][ik] = 0;
                    //StepX_XZ[ik] = 0;
                }
                for (int ik = 0; ik < 8; ik++ ) //zerowanie tablic przechowujace dane, X
                {
                    energyDepY_YZ[ik] = 0;
                    energyDepY_YZ_Plain[0][ik] = 0;
                    energyDepY_YZ_Plain[1][ik] = 0;
                    energyDepY_YZ_Plain[2][ik] = 0;
                    //StepY_YZ[ik] = 0;
                }
                LargehitTimeDif = 0;
                Int_t GTindex[2] = {0,0};
                for (int i = 0; i < 19; i++) //loop over FEB
                {
                    if (FEBs[i]!=12)
                    {
                    auto bounds=std::equal_range (FEB[FEBs[i]].GTrigTag->begin(), FEB[FEBs[i]].GTrigTag->end(), FEB[12].GTrigTag->at(TOFtrigger));
                    GTindex[0] = bounds.first - FEB[FEBs[i]].GTrigTag->begin();
                    GTindex[1] = bounds.second - FEB[FEBs[i]].GTrigTag->begin();

                    for (int check = GTindex[0]; check <  GTindex[1]; check++)
                    {
                        if (abs(FEB[12].hitTimefromSpill->at(TOFtrigger) - FEB[FEBs[i]].hitTimefromSpill->at(check)) < 100)
                        {
                            if (FEB[FEBs[i]].hitTimeDif->at(check) > 60)
                            {
                                LargehitTimeDif = 1;
                            }
                            TriggerTime = FEB[12].hitLeadTime->at(TOFtrigger);
                            
                            if ( FEBs[i] == 0 || FEBs[i] == 16) //Plaszczyzna XY
                            {
                                event_XY[eventNum]-> Fill( MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],FEB[FEBs[i]].hitCharge_pe->at(check) );
                                EventsMap_XY->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],1);
                                EnergyTrigTimeAll->Fill(FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime, FEB[FEBs[i]].hitCharge_pe->at(check));
                            }
                            else if ( FEBs[i] == 1 || FEBs[i] == 2 || FEBs[i] == 17 || FEBs[i] ==  24) //Plaszczyzna YZ
                            {
                                event_YZ[eventNum]->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)], MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],FEB[FEBs[i]].hitCharge_pe->at(check));
                                EventsMap_YZ->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],1);
                                EnergyTrigTimeAll->Fill( FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime, FEB[FEBs[i]].hitCharge_pe->at(check) );
                                if (FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000)// zmiana 0 and 10000
                                {
                                    energyDepZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                    energyDepZ_YZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                    energyDepY_YZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);

                                    //StepZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += 1;
                                    //StepZ_YZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += 1;
                                    //StepY_YZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += 1;
                                }
                            }
                            else //Plaszczyzna XZ
                            {
                                event_XZ[eventNum]->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],FEB[FEBs[i]].hitCharge_pe->at(check)); /////////////////////////////
                                EventsMap_XZ->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],1);
                                EnergyTrigTimeAll->Fill(FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime, FEB[FEBs[i]].hitCharge_pe->at(check));
                                if (FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000) //zmiana 0 and 10000
                                {
                                    energyDepZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                    energyDepZ_XZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                    energyDepX_XZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);

                                    //StepZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += 1;
                                    //StepZ_XZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += 1;
                                    //StepX_XZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += 1;
                                }
                            }
                        }
                    }
                }
            }
//////////Zmienne pomocnicze
            double PeakEnergy=0;
            int PeakNumber=0;

            double RealPeakEnergy=0;
            int RealPeakNumber=0;

            double RealPeakEnergyX[3]={};
            int RealPeakNumberX[3]={};

            double RealPeakEnergyY[3]={};
            int RealPeakNumberY[3]={};

            double HighestEnergyY=0;
            int HighestEnergyNumberY=0;

            //double HighestEnergyX=0;
            //int HighestEnergyNumberX=0;

            int CrosstalkDistance=0;
            
            //double DepozytPomocniczy=0;
            
            int PomocniczyNumerKostki=0;
            
            int CrossEventTypeX[48]={};
            int CrossEventTypeY[16]={};
            
            int CrossEventTypeCounterX=0;
            int CrossEventTypeCounterY=0;
            
            double WierdTestX[2][2]={}; //[deposit][czas]
            double WierdTestY[2][2]={}; //[deposit][czas]
            
            int WierdLicznikX=0;
            int WierdLicznikY=0;

  ///////////Ciecia
            int StoppingParticle = 0; //ciecie usuwajace czastki które sie nie zatrzymaly
            if(energyDepZ[47]==0)
            {
                StoppingParticle=1;
            }
            for(int ik = 0; ik < 48; ik++ )
            {
                energy_Z[eventNum]->Fill(ik,energyDepZ[ik]);
                energyZ_XZ[eventNum]->Fill(ik,energyDepZ_XZ[ik]);
                energyZ_YZ[eventNum]->Fill(ik,energyDepZ_YZ[ik]);

                //StepCounterZ[eventNum]->Fill(ik,StepZ[ik]);
                //StepCounterZ_XZ[eventNum]->Fill(ik,StepZ_XZ[ik]);
                //StepCounterZ_YZ[eventNum]->Fill(ik,StepZ_YZ[ik]);
                if(energyDepZ[ik]>PeakEnergy)
                {
                    PeakEnergy=energyDepZ[ik];
                    PeakNumber=ik;
                }
            }
            RealPeakEnergy=PeakEnergy;
            RealPeakNumber=PeakNumber;
            if(PeakNumber+1!=48)
            {
                for(int ik = PeakNumber+1; ik < 48; ik++ )
                {
                    if(energyDepZ[ik]>RealPeakEnergy*0.75)
                    {
                        RealPeakEnergy=energyDepZ[ik];
                        RealPeakNumber=ik;
                    }
                }
            }

            for(int ik = 0; ik < 24; ik++ )
            {
                energyX_XZ[eventNum]->Fill(ik,energyDepX_XZ[ik]);
                //StepCounterX_XZ[eventNum]->Fill(ik,StepX_XZ[ik]);
                /*
                if(energyDepX_XZ[ik]>HighestEnergyX)
                {
                    HighestEnergyX=energyDepX_XZ[ik];
                    HighestEnergyNumberX=ik;
                }
                */
            }

            for(int ik = 0; ik < 8; ik++ )
            {
                energyY_YZ[eventNum]->Fill(ik,energyDepY_YZ[ik]);
                //StepCounterY_YZ[eventNum]->Fill(ik,StepY_YZ[ik]);
                if(energyDepY_YZ[ik]>HighestEnergyY)
                {
                    HighestEnergyY=energyDepY_YZ[ik];
                    HighestEnergyNumberY=ik;
                }
                
            }
           
           int DiscontinuityCut=0; // maximally two layers before peak can have 0 deposit
            if(RealPeakNumber>3)
            {
                if(energyDepZ[RealPeakNumber-1]!=0 || energyDepZ[RealPeakNumber-2]!=0 || energyDepZ[RealPeakNumber-3]!=0)
                {
                    DiscontinuityCut=1;
                }
            }
            int BorderCutY=0; // ciecie usuwajace eventy ktore sie slizgaja po krawedzi Y
            if(HighestEnergyNumberY!=0 && HighestEnergyNumberY!=7)
            {
                BorderCutY=1;
            }

            int TrackBeginningCut=0; //ciecie usuwajace czastki bez depozytu na poczatku detektora
            if(energyDepZ[0]>0 || energyDepZ[1]>0 || energyDepZ[2]>0)
            {
                TrackBeginningCut=1;
            }

            //Fitowanie potrzebne do ciecia usuwajacego nie gausowe smieci
            double sigma=0;
            if ( LargehitTimeDif == 0 && StoppingParticle==1 && PeakEnergy>250 && DiscontinuityCut==1 && TrackBeginningCut==1 && BorderCutY==1)
            {
                TF1 *EnergyFitX = new TF1("EnergyFitX", "gaus");
                energyX_XZ[eventNum]-> Fit(EnergyFitX,"q","",1 , 23);
                sigma = EnergyFitX->GetParameter(2); //wybieramy przypadki z sigma < 2 aby pozbyc sie smieci

                delete EnergyFitX;
            }
            if(LargehitTimeDif == 0 && StoppingParticle==1 && PeakEnergy>250 && DiscontinuityCut==1 && TrackBeginningCut==1 && BorderCutY==1 && sigma < 2)
            {
                Int_t GTindex[2] = {0,0};
                for (int i = 0; i < 19; i++) //loop over FEB
                {
                    if (FEBs[i]!=12)
                    {
                        auto bounds=std::equal_range (FEB[FEBs[i]].GTrigTag->begin(), FEB[FEBs[i]].GTrigTag->end(), FEB[12].GTrigTag->at(TOFtrigger));
                        GTindex[0] = bounds.first - FEB[FEBs[i]].GTrigTag->begin();
                        GTindex[1] = bounds.second - FEB[FEBs[i]].GTrigTag->begin();

                        for (int check = GTindex[0]; check <  GTindex[1]; check++)
                        {
                            if (abs(FEB[12].hitTimefromSpill->at(TOFtrigger) - FEB[FEBs[i]].hitTimefromSpill->at(check)) < 100)
                            {

                                if ( FEBs[i] == 0 || FEBs[i] == 16) //Plaszczyzna XY
                                {

                                }
                                else if( FEBs[i] == 1 || FEBs[i] == 2 || FEBs[i] == 17 || FEBs[i] ==  24) //Plaszczyzna YZ
                                {
                                    PomocniczyNumerKostki = MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)];
                                    if(PomocniczyNumerKostki == RealPeakNumber)
                                    {
                                        if (FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000)// zmiana 0 and 10000
                                        {
                                            energyDepY_YZ_Plain[0][MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                        }
                                    }
                                    if(PomocniczyNumerKostki == RealPeakNumber-1)
                                    {
                                        if (FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000)// zmiana 0 and 10000
                                        {
                                            energyDepY_YZ_Plain[1][MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                        }
                                    }
                                    if(PomocniczyNumerKostki == RealPeakNumber-15 && RealPeakNumber>15)
                                    {
                                        if (FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000)// zmiana 0 and 10000
                                        {
                                            energyDepY_YZ_Plain[2][MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                        }
                                    }
                                }
                                else //Plaszczyzna XZ
                                {
                                    PomocniczyNumerKostki = MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)];

                                    if(PomocniczyNumerKostki == RealPeakNumber)
                                    {
                                        if(FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000) //zmiana 0 and 10000
                                        {
                                            energyDepX_XZ_Plain[0][MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                        }
                                    }
                                    if(PomocniczyNumerKostki == RealPeakNumber-1)
                                    {
                                        if(FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000) //zmiana 0 and 10000
                                        {
                                            energyDepX_XZ_Plain[1][MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                        }
                                    }
                                    
                                    if(PomocniczyNumerKostki == RealPeakNumber-15 && RealPeakNumber>15)
                                    {
                                        if(FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000) //zmiana 0 and 10000
                                        {
                                            energyDepX_XZ_Plain[2][MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                int LoopLimit=3;
                if(RealPeakNumber<=15)
                {
                    LoopLimit=2;
                }
                for(int hk = 0; hk < LoopLimit; hk++ )
                {
                    for(int ik = 0; ik < 24; ik++ )
                    {
                        if(hk == 0)
                        {
                        energyX_XZ_Plain[eventNum] ->Fill(ik,energyDepX_XZ_Plain[hk][ik]);
                        }
                        if(energyDepX_XZ_Plain[hk][ik]>RealPeakEnergyX[hk])
                        {
                            RealPeakEnergyX[hk]=energyDepX_XZ_Plain[hk][ik];
                            RealPeakNumberX[hk]=ik;
                        }
                    }

                    for(int ik = 0; ik < 8; ik++ )
                    {
                        if(hk == 0)
                        {
                        energyY_YZ_Plain[eventNum] ->Fill(ik,energyDepY_YZ_Plain[hk][ik]);
                        }
                        if(energyDepY_YZ_Plain[hk][ik]>RealPeakEnergyY[hk])
                        {
                            RealPeakEnergyY[hk]=energyDepY_YZ_Plain[hk][ik];
                            RealPeakNumberY[hk]=ik;
                        }
                    }
                }
            }
            if(LargehitTimeDif == 0 && StoppingParticle==1 && PeakEnergy>250 && DiscontinuityCut==1 && TrackBeginningCut==1 && BorderCutY==1 && sigma < 2)
            {
                Int_t GTindex[2] = {0,0};
                for (int i = 0; i < 19; i++) //loop over FEB
                {
                    if (FEBs[i]!=12)
                    {
                        auto bounds=std::equal_range (FEB[FEBs[i]].GTrigTag->begin(), FEB[FEBs[i]].GTrigTag->end(), FEB[12].GTrigTag->at(TOFtrigger));
                        GTindex[0] = bounds.first - FEB[FEBs[i]].GTrigTag->begin();
                        GTindex[1] = bounds.second - FEB[FEBs[i]].GTrigTag->begin();

                        for (int check = GTindex[0]; check <  GTindex[1]; check++)
                        {
                            if (abs(FEB[12].hitTimefromSpill->at(TOFtrigger) - FEB[FEBs[i]].hitTimefromSpill->at(check)) < 100)
                            {
                                
                                if ( FEBs[i] == 0 || FEBs[i] == 16) //Plaszczyzna XY
                                {

                                }
                                else if( FEBs[i] == 1 || FEBs[i] == 2 || FEBs[i] == 17 || FEBs[i] ==  24) //Plaszczyzna YZ
                                {
                                    PomocniczyNumerKostki = MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)];
                                    if ( PomocniczyNumerKostki == RealPeakNumber && FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000)// zmiana 0 and 10000
                                    {
                                        CrosstalkDistance = RealPeakNumberY[0] - MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)];
                                        HistogramCrosstalkDistanceY->Fill(CrosstalkDistance);
                                        
                                        EnergyTrigTimeY->Fill(FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime, FEB[FEBs[i]].hitCharge_pe->at(check));
                                        
                                        if( abs(CrosstalkDistance)==2 || abs(CrosstalkDistance)==1)
                                        {
                                             CrosstalkEnergyDepositRestrictedY->Fill( FEB[FEBs[i]].hitCharge_pe->at(check) );
                                        }
                                        if(MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] == RealPeakNumberY[0])
                                        {
                                            //EnergyTrigTimeSignalY->Fill(FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime, FEB[FEBs[i]].hitCharge_pe->at(check));
//cout<<"Y licznik"<<licznik<<" Trigger "<< FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime<<" energia "<<FEB[FEBs[i]].hitCharge_pe->at(check)<<endl;
                                            WierdTestY[WierdLicznikY][0]=FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime;
                                            WierdTestY[WierdLicznikY][1]=FEB[FEBs[i]].hitCharge_pe->at(check);
                                            WierdLicznikY++;
                                        }
                                        if(MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] != RealPeakNumberY[0])
                                        {
                                         CrosstalkEnergyDepositY->Fill( FEB[FEBs[i]].hitCharge_pe->at(check) );
                                         EnergyTrigTimeCrosstalkY->Fill(FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime, FEB[FEBs[i]].hitCharge_pe->at(check));
                                            if(CrosstalkDistance>=0)
                                            {
                                                CrossEventTypeY[CrosstalkDistance+8]=1;
                                            }
                                            if(CrosstalkDistance<0)
                                            {
                                                CrossEventTypeY[CrosstalkDistance+8]=1;
                                            }
                                        }
                                        if(MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] != RealPeakNumberY[0] && FEB[FEBs[i]].hitCharge_pe->at(check)>50)
                                        {
                                         HistogramCrosstalkDistanceEnergyHigherThanY->Fill( CrosstalkDistance );
                                        }
                                        if(FEB[FEBs[i]].hitCharge_pe->at(check)>1)
                                        {
                                            HistogramCrosstalkDistanceCutY->Fill( CrosstalkDistance );
                                        }
                                    }
                                    if ( PomocniczyNumerKostki == RealPeakNumber-1 && FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000)// zmiana 0 and 10000, one cube backward
                                    {
                                        CrosstalkDistance = RealPeakNumberY[1] - MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)];
                                        HistogramCrosstalkDistanceMinus1Y->Fill(CrosstalkDistance);
                                        if(MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] != RealPeakNumberY[1])
                                        {
                                         CrosstalkEnergyDepositMinus1Y->Fill( FEB[FEBs[i]].hitCharge_pe->at(check) );
                                        }
                                    }
                                    if ( PomocniczyNumerKostki == RealPeakNumber-15 && FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000 && RealPeakNumber>15)// zmiana 0 and 10000, one cube backward
                                    {
                                        CrosstalkDistance = RealPeakNumberY[2] - MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)];
                                        HistogramCrosstalkDistanceMiddleY->Fill(CrosstalkDistance);
                                        if(MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] != RealPeakNumberY[2])
                                        {
                                            CrosstalkEnergyDepositMiddleY->Fill( FEB[FEBs[i]].hitCharge_pe->at(check) );
                                        }
                                    }
                                }
                                else //Plaszczyzna XZ
                                {
                                    PomocniczyNumerKostki = MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)];
                                    if( PomocniczyNumerKostki == RealPeakNumber && FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000) //zmiana 0 and 10000
                                    {
                                        CrosstalkDistance = RealPeakNumberX[0] - MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)];
                                        HistogramCrosstalkDistanceX->Fill(CrosstalkDistance);
                                        
                                        EnergyTrigTimeX->Fill(FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime, FEB[FEBs[i]].hitCharge_pe->at(check));
                                       
                                        if( abs(CrosstalkDistance)==2 || abs(CrosstalkDistance)==1)
                                        {
                                             CrosstalkEnergyDepositRestrictedX->Fill( FEB[FEBs[i]].hitCharge_pe->at(check) );
                                        }
                                        if(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] == RealPeakNumberX[0])
                                        {
                                            //EnergyTrigTimeSignalX->Fill(FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime, FEB[FEBs[i]].hitCharge_pe->at(check));
                                            
//cout<<"X licznik"<<licznik<<" Trigger "<< FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime<<" energia "<<FEB[FEBs[i]].hitCharge_pe->at(check)<<endl;
                                            WierdTestX[WierdLicznikX][0]=FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime;
                                            WierdTestX[WierdLicznikX][1]=FEB[FEBs[i]].hitCharge_pe->at(check);
                                            WierdLicznikX++;
                                        }
                                        if(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] != RealPeakNumberX[0])
                                        {
                                            CrosstalkEnergyDepositX->Fill( FEB[FEBs[i]].hitCharge_pe->at(check) );
                                            
                                            EnergyTrigTimeCrosstalkX->Fill(FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime, FEB[FEBs[i]].hitCharge_pe->at(check));
                                            
                                            if(CrosstalkDistance>=0)
                                            {
                                                CrossEventTypeX[CrosstalkDistance+24]=1;
                                            }
                                            if(CrosstalkDistance<0)
                                            {
                                                CrossEventTypeX[CrosstalkDistance+24]=1;
                                            }
                                        }
                                        if(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] != RealPeakNumberX[0] && FEB[FEBs[i]].hitCharge_pe->at(check)>50)
                                        {
                                            HistogramCrosstalkDistanceEnergyHigherThanX->Fill( CrosstalkDistance );
                                        }
                                        if(FEB[FEBs[i]].hitCharge_pe->at(check)>1)
                                        {
                                            HistogramCrosstalkDistanceCutX->Fill( CrosstalkDistance );
                                        }
                                    }
                                    if( PomocniczyNumerKostki == RealPeakNumber-1 && FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000) //zmiana 0 and 10000, one cube backward
                                    {
                                        CrosstalkDistance = RealPeakNumberX[1] - MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)];
                                        HistogramCrosstalkDistanceMinus1X->Fill(CrosstalkDistance);
                                        if(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] != RealPeakNumberX[1])
                                        {
                                            CrosstalkEnergyDepositMinus1X->Fill( FEB[FEBs[i]].hitCharge_pe->at(check) );
                                        } 
                                    }
                                    if( PomocniczyNumerKostki == RealPeakNumber-15 && FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000 && RealPeakNumber>15) //zmiana 0 and 10000, one cube backward
                                    {
                                        CrosstalkDistance = RealPeakNumberX[2] - MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)];
                                        HistogramCrosstalkDistanceMiddleX->Fill(CrosstalkDistance);
                                        if(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] != RealPeakNumberX[2])
                                        {
                                            CrosstalkEnergyDepositMiddleX->Fill( FEB[FEBs[i]].hitCharge_pe->at(check) );
                                        } 
                                    }
                                }
                            }
                        }
                    }
                } 
                for(int ik=0; ik<=48; ik++)
                {
                  CrossEventTypeCounterX+=CrossEventTypeX[ik];
                  CrossEventTypeX[ik]=0;
                }
                for(int ik=0; ik<=16; ik++)
                {
                  CrossEventTypeCounterY+=CrossEventTypeY[ik];
                  CrossEventTypeY[ik]=0;
                }
                HistogramCrosstalkDistanceTypeX->Fill(CrossEventTypeCounterX);
                HistogramCrosstalkDistanceTypeY->Fill(CrossEventTypeCounterY);
                
                cout <<"licznik "<<licznik<<" sigma " << sigma <<" RealPeakNumber "<<RealPeakNumber<<endl;
                cout <<"licznik "<<licznik<<" RealPeakEnergyX "<< RealPeakEnergyX[0]<<" RealPeakEnergyY "<<RealPeakEnergyY[0]<<endl;
                cout <<"licznik "<<licznik<<" RealPeakNumberX "<< RealPeakNumberX[0]<<" RealPeakNumberY "<<RealPeakNumberY[0]<<endl;
                if(energyDepZ[RealPeakNumber-15]>0 && RealPeakNumber>15)
                {
                    cout <<"licznik "<<licznik<<" RealPeakNumber-15: "<<RealPeakNumber-15<<" RealPeakEnergy-15: "<<energyDepZ[RealPeakNumber-15]<<endl;
                }
                licznik++;
                
                StoppingPointLocation->Fill(RealPeakNumber);
                HistogramHighestEnergyDeposit->Fill(PeakEnergy);
                HistogramRealPeakEnergyDeposit->Fill(RealPeakEnergy);
                if(energyDepZ[RealPeakNumber-15]>0 && RealPeakNumber>15)
                {
                    HistogramRealPeakEnergyDepositMiddle->Fill(energyDepZ[RealPeakNumber-15]);
                }
                double TemporaryTime=0;
                double TemporaryEnergy=0;
                if(WierdLicznikX==2)
                {
                    EnergyTrigTimeTestX->Fill(WierdTestX[0][0],WierdTestX[0][1]);
                    EnergyTrigTimeTestX->Fill(WierdTestX[1][0],WierdTestX[1][1]);
                    
                    TemporaryEnergy=WierdTestX[0][1];
                    if(WierdTestX[1][1]>TemporaryEnergy)
                    {
                        TemporaryEnergy=WierdTestX[1][1];
                    }
                    TemporaryTime=WierdTestX[0][0];
                    if(TemporaryTime>WierdTestX[1][0])
                    {
                       TemporaryTime=WierdTestX[1][0];
                    }
                    EnergyTrigTimeSignalX->Fill(TemporaryTime, TemporaryEnergy);
                    EnergyTrigTimeTestUpgradeX->Fill(TemporaryTime, TemporaryEnergy);
                    //cout<<"X Time "<<TemporaryTime<<" Energy "<<TemporaryEnergy<<" Time 1 "<<WierdTestX[0][0]<<" Time 2 "<<WierdTestX[1][0]<<endl;
                }
                if(WierdLicznikY==2)
                {
                    EnergyTrigTimeTestY->Fill(WierdTestY[0][0],WierdTestY[0][1]);
                    EnergyTrigTimeTestY->Fill(WierdTestY[1][0],WierdTestY[1][1]);
                    
                    TemporaryEnergy=WierdTestY[0][1];
                    if(WierdTestY[1][1]>TemporaryEnergy)
                    {
                        TemporaryEnergy=WierdTestY[1][1];
                    }
                    
                    TemporaryTime=WierdTestY[0][0];
                    if(TemporaryTime>WierdTestY[1][0])
                    {
                       TemporaryTime=WierdTestY[1][0];
                    }
                    EnergyTrigTimeSignalY->Fill(TemporaryTime, TemporaryEnergy);
                    EnergyTrigTimeTestUpgradeY->Fill(TemporaryTime, TemporaryEnergy);
                    //cout<<"Y Time "<<TemporaryTime<<" Energy "<<TemporaryEnergy<<" Time 1 "<<WierdTestY[0][0]<<" Time 2 "<<WierdTestY[1][0]<<endl;
                }
                if(WierdLicznikX==1)
                {
                    EnergyTrigTimeSignalX->Fill(WierdTestX[0][0], WierdTestX[0][1]);
                    if(WierdTestX[0][1]<40)
                    {
                        EnergyTrigTimeTestLowX->Fill(WierdTestX[0][0],WierdTestX[0][1]); 
                    }
                }
                if(WierdLicznikY==1)
                {
                    EnergyTrigTimeSignalY->Fill(WierdTestY[0][0], WierdTestY[0][1]);
                    if(WierdTestY[0][1]<40)
                    {
                        EnergyTrigTimeTestLowY->Fill(WierdTestY[0][0],WierdTestY[0][1]);
                    }
                }
                DisplayCanvas->Clear();
                CrossEnergyCanvas->Clear();
                //CrossHitCanvas->Clear();
                CrossEnergyPlainCanvas->Clear();

                    DisplayCanvas->Divide(2,2);


                    DisplayCanvas -> cd(1);
                    event_XZ[eventNum]-> Draw("colorz");

                    DisplayCanvas -> cd(2);
                    event_YZ[eventNum]-> Draw("colorz");

                    DisplayCanvas -> cd(3);
                    event_XY[eventNum]-> Draw("colorz");

                    DisplayCanvas -> cd(4);
                    energy_Z[eventNum]->Draw("HIST");

                    DisplayCanvas->Update();
                    events2D -> cd();

                    DisplayCanvas->Write();
                    //////////

                    CrossEnergyCanvas->Divide(2,2);

                    CrossEnergyCanvas -> cd(1);
                    energyX_XZ[eventNum]->Draw("HIST");

                    CrossEnergyCanvas -> cd(2);
                    energyY_YZ[eventNum]->Draw("HIST");

                    CrossEnergyCanvas -> cd(3);
                    energyZ_XZ[eventNum]->Draw("HIST");

                    CrossEnergyCanvas -> cd(4);
                    energyZ_YZ[eventNum]->Draw("HIST");

                    CrossEnergyCanvas->Update();
                    CrossEnergy-> cd();

                    CrossEnergyCanvas->Write();

                    /////////
                    /*
                    CrossHitCanvas->Divide(3,2);

                    CrossHitCanvas->cd(1);
                    StepCounterX_XZ[eventNum]->Draw("HIST");

                    CrossHitCanvas->cd(2);
                    StepCounterY_YZ[eventNum]->Draw("HIST");

                    CrossHitCanvas->cd(3);
                    StepCounterZ[eventNum]->Draw("HIST");

                    CrossHitCanvas->cd(4);
                    StepCounterZ_XZ[eventNum]->Draw("HIST");

                    CrossHitCanvas->cd(5);
                    StepCounterZ_YZ[eventNum]->Draw("HIST");

                    CrossHitCanvas->cd(6);
                    StepCounterZ[eventNum]->Draw("HIST");

                    CrossHitCanvas->Update();
                    CrossStep -> cd();

                    CrossHitCanvas->Write();
                    */
                    //////
                    CrossEnergyPlainCanvas->Divide(2,1);

                    CrossEnergyPlainCanvas->cd(1);
                    energyX_XZ_Plain[eventNum]->Draw("HIST");

                    CrossEnergyPlainCanvas->cd(2);
                    energyY_YZ_Plain[eventNum]->Draw("HIST");

                    CrossEnergyPlainCanvas->Update();
                    CrossEnergyPlain -> cd();

                    CrossEnergyPlainCanvas->Write();
                    //////
        }
        delete event_XY[eventNum];
        delete event_YZ[eventNum];
        delete event_XZ[eventNum];
        delete energy_Z[eventNum];

        delete energyX_XZ[eventNum];
        delete energyY_YZ[eventNum];
        delete energyZ_XZ [eventNum];
        delete energyZ_YZ[eventNum];
/*
        delete StepCounterX_XZ[eventNum];
        delete StepCounterY_YZ[eventNum];
        delete StepCounterZ[eventNum];
        delete StepCounterZ_XZ[eventNum];
        delete StepCounterZ_YZ[eventNum];
*/
        delete energyX_XZ_Plain[eventNum];
        delete energyY_YZ_Plain[eventNum];

        eventNum++;
    }
  }
            for (Int_t i=0; i<NumberOfEB; i++)
            {
                FEB[i].FEBSN=0;
                FEB[i].SpillTag=0;
                FEB[i].hitsChannel=0;
                FEB[i].hitAmpl=0;
                FEB[i].hitAmplRec=0;
                FEB[i].hitLeadTime=0;
                FEB[i].GTrigTag=0;
                FEB[i].GTrigTime=0;
                FEB[i].hitLGAmpl=0;
                FEB[i].hitLGAmplRec=0;
                FEB[i].hitTrailTime=0;
                FEB[i].hitTimeDif=0;
                FEB[i].hitTimefromSpill=0;

                FEB[i].hitHG_pe=0;
                FEB[i].hitLG_pe=0;
                FEB[i].hitToT_pe=0;
                FEB[i].hitCharge_pe=0;
            }
        }
    }
    wfile.cd();
    EventsMap_XY->Write();
    EventsMap_YZ->Write();
    EventsMap_XZ->Write();
    EnergyTrigTimeAll->Write();
    
    HistogramHighestEnergyDeposit->Write();
    HistogramRealPeakEnergyDeposit->Write();
    
    StoppingPointLocation->Write();
    
    CrosstalkEnergyDepositX->Write();
    CrosstalkEnergyDepositY->Write();

    CrosstalkEnergyDepositRestrictedX->Write();
    CrosstalkEnergyDepositRestrictedY->Write();

    HistogramCrosstalkDistanceX->Write();
    HistogramCrosstalkDistanceY->Write();
    
    HistogramCrosstalkDistanceEnergyHigherThanX->Write();
    HistogramCrosstalkDistanceEnergyHigherThanY->Write();
    
    HistogramCrosstalkDistanceCutX->Write();
    HistogramCrosstalkDistanceCutY->Write();
    
    HistogramCrosstalkDistanceTypeX->Write();
    HistogramCrosstalkDistanceTypeY->Write();
    
    EnergyTrigTimeX->Write();
    EnergyTrigTimeY->Write();
    
    EnergyTrigTimeCrosstalkX->Write();
    EnergyTrigTimeCrosstalkY->Write();
    
    EnergyTrigTimeSignalX->Write();
    EnergyTrigTimeSignalY->Write();
    
    CrosstalkEnergyDepositMinus1X->Write();
    CrosstalkEnergyDepositMinus1Y->Write();
    
    HistogramCrosstalkDistanceMinus1X->Write();
    HistogramCrosstalkDistanceMinus1Y->Write();
    
    CrosstalkEnergyDepositMiddleX->Write();
    CrosstalkEnergyDepositMiddleY->Write();

    HistogramCrosstalkDistanceMiddleX->Write();
    HistogramCrosstalkDistanceMiddleY->Write();
    
    EnergyTrigTimeTestX->Write();
    EnergyTrigTimeTestY->Write();
    
    EnergyTrigTimeTestUpgradeX->Write();
    EnergyTrigTimeTestUpgradeY->Write();
    
    EnergyTrigTimeTestLowX->Write();
    EnergyTrigTimeTestLowY->Write();
    
    HistogramRealPeakEnergyDepositMiddle->Write();
    
    wfile.Close();
    FileInput->Close();
    return 0;
}
