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
#include "TCutG.h"

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
            }
            fmap.close();
       }
    }
    TH2F *EventsMap_XY = new TH2F("EventsMap_XY","All_events_map_XY",  24,0,24, 8,0,8);
    TH2F *EventsMap_YZ = new TH2F("EventsMap_YZ","All_events_map_YZ",  48,0,48, 8,0,8);
    TH2F *EventsMap_XZ = new TH2F("EventsMap_XZ","All_events_map_XZ",  24,0,24, 48,0,48);
    
    TH2F *EnergyTrigTimeAll = new TH2F("EnergyTrigTimeAll","Energy and Time of Trigger whole run", 100,-100,100,500,0,1500);
    EnergyTrigTimeAll->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeAll->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH1F *HistogramHighestEnergyDeposit = new TH1F("HistogramHighestEnergyDeposit", "Histogram of highest value deposit",100,0,2500);
    HistogramHighestEnergyDeposit->GetYaxis()->SetTitle("Number of events");
    HistogramHighestEnergyDeposit->GetXaxis()->SetTitle("Energy [p.e.]");
   
    TH1F *HistogramRealPeakEnergyDeposit = new TH1F("HistogramRealPeakEnergyDeposit", "Histogram of found stopping proton deposit",100,0,2500);
    HistogramRealPeakEnergyDeposit->GetYaxis()->SetTitle("Number of events");
    HistogramRealPeakEnergyDeposit->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositX = new TH1F("CrosstalkEnergyDepositX", "Crosstalk energy in X plain",500,0,500);
    CrosstalkEnergyDepositX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositY = new TH1F("CrosstalkEnergyDepositY", "Crosstalk energy in Y plain",500,0,500);
    CrosstalkEnergyDepositY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositOneCubeX = new TH1F("CrosstalkEnergyDepositOneCubeX", "Crosstalk energy in X stopping point, one cube",50,0,100);
    CrosstalkEnergyDepositOneCubeX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositOneCubeX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositOneCubeY = new TH1F("CrosstalkEnergyDepositOneCubeY", "Crosstalk energy in Y stopping point, one cube",50,0,100);
    CrosstalkEnergyDepositOneCubeY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositOneCubeY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositTwoCubesX = new TH1F("CrosstalkEnergyDepositTwoCubesX", "Crosstalk energy in X stopping point, two cube",50,0,100);
    CrosstalkEnergyDepositTwoCubesX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositTwoCubesX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositTwoCubesY = new TH1F("CrosstalkEnergyDepositTwoCubesY", "Crosstalk energy in Y stopping point, two cube",50,0,100);
    CrosstalkEnergyDepositTwoCubesY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositTwoCubesY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositPercentageX = new TH1F("CrosstalkEnergyDepositPercentageX", "Crosstalk energy divided by main deposit in X plain",200,0,100);
    CrosstalkEnergyDepositPercentageX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositPercentageY = new TH1F("CrosstalkEnergyDepositPercentageY", "Crosstalk energy divided by main deposit in Y plain",200,0,100);
    CrosstalkEnergyDepositPercentageY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageY->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositPercentageOneCubeX = new TH1F("CrosstalkEnergyDepositPercentageOneCubeX", "Crosstalk energy divided by main deposit in X plain,  one cube",200,0,100);
    CrosstalkEnergyDepositPercentageOneCubeX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageOneCubeX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositPercentageOneCubeY = new TH1F("CrosstalkEnergyDepositPercentageOneCubeY", "Crosstalk energy divided by main deposit in Y plain,  one cube",200,0,100);
    CrosstalkEnergyDepositPercentageOneCubeY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageOneCubeY->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositPercentageTwoCubesX = new TH1F("CrosstalkEnergyDepositPercentageTwoCubesX", "Crosstalk energy divided by main deposit in X plain,  two cubes",100,0,100);
    CrosstalkEnergyDepositPercentageTwoCubesX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageTwoCubesX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositPercentageTwoCubesY = new TH1F("CrosstalkEnergyDepositPercentageTwoCubesY", "Crosstalk energy divided by main deposit in Y plain,  one cube",100,0,100);
    CrosstalkEnergyDepositPercentageTwoCubesY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageTwoCubesY->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositPercentageSecondCubeNewX = new TH1F("CrosstalkEnergyDepositPercentageSecondCubeNewX", "Crosstalk in second cube divided by crosstalk in first cube, in X plain, one cube backward",100,0,100);
    CrosstalkEnergyDepositPercentageSecondCubeNewX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageSecondCubeNewX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositCUTGX = new TH1F("CrosstalkEnergyDepositCUTGX", "Crosstalk energy in X plain after CUTG",200,0,200);
    CrosstalkEnergyDepositCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositCUTGX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositCUTGY = new TH1F("CrosstalkEnergyDepositCUTGY", "Crosstalk energy in Y plain",200,0,200);
    CrosstalkEnergyDepositCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositCUTGY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositOneCubeCUTGX = new TH1F("CrosstalkEnergyDepositOneCubeCUTGX", "Crosstalk energy in X plain after CUTG, only one cube away",50,0,100);
    CrosstalkEnergyDepositOneCubeCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositOneCubeCUTGX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositOneCubeCUTGY = new TH1F("CrosstalkEnergyDepositOneCubeCUTGY", "Crosstalk energy in Y plain after CUTG, only one cube away",50,0,100);
    CrosstalkEnergyDepositOneCubeCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositOneCubeCUTGY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositTwoCubesCUTGX = new TH1F("CrosstalkEnergyDepositTwoCubesCUTGX", "Crosstalk energy in X plain after CUTG only, two cubes away",50,0,100);
    CrosstalkEnergyDepositTwoCubesCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositTwoCubesCUTGX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositTwoCubesCUTGY = new TH1F("CrosstalkEnergyDepositTwoCubesCUTGY", "Crosstalk energy in Y plain after CUTG only, two cubes away",50,0,100);
    CrosstalkEnergyDepositTwoCubesCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositTwoCubesCUTGY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *StoppingPointLocation = new TH1F("StoppingPointLocation", "Location of stopping point",48,0,48);
    StoppingPointLocation->GetYaxis()->SetTitle("Number of events");
    StoppingPointLocation->GetXaxis()->SetTitle("Z detector axis [cm]");

    TH1F *HistogramCrosstalkDistanceX= new TH1F("HistogramCrosstalkDistanceX", "Cube distance of energy deposit from peak X axis",10,-5,5);
    HistogramCrosstalkDistanceX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceX->GetXaxis()->SetTitle("X detector axis [cm]");
    
    TH1F *HistogramCrosstalkDistanceY = new TH1F("HistogramCrosstalkDistanceY", "Cube distance of energy deposit from peak Y axis",10,-5,5);
    HistogramCrosstalkDistanceY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceY->GetXaxis()->SetTitle("Y detector axis [cm]");

    TH1F *HistogramCrosstalkDistanceCUTGX= new TH1F("HistogramCrosstalkDistanceCUTGX", "Cube distance in stopping point plain from peak X axis, after CUTG",10,-5,5);
    HistogramCrosstalkDistanceCUTGX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceCUTGX->GetXaxis()->SetTitle("X detector axis [cm]");
    
    TH1F *HistogramCrosstalkDistanceCUTGY = new TH1F("HistogramCrosstalkDistanceCUTGY", "Cube distance in stopping point plain from peak Y axis, after CUTG",10,-5,5);
    HistogramCrosstalkDistanceCUTGY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceCUTGY->GetXaxis()->SetTitle("Y detector axis [cm]");
    
    TH1F *CrosstalkEnergyDepositPercentageCUTGX = new TH1F("CrosstalkEnergyDepositPercentageCUTGX", "Crosstalk energy divided by main deposit in X plain, after CUTG.",200,0,100);
    CrosstalkEnergyDepositPercentageCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageCUTGX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositPercentageCUTGY = new TH1F("CrosstalkEnergyDepositPercentageCUTGY", "Crosstalk energy divided by main deposit in Y plain, after CUTG.",200,0,100);
    CrosstalkEnergyDepositPercentageCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageCUTGY->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositRestrictedX= new TH1F("CrosstalkEnergyDepositRestrictedX", "Crosstalk energy in X plain maximaly 2 cubes from deposit",500,0,500);
    CrosstalkEnergyDepositRestrictedX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositRestrictedX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositRestrictedY= new TH1F("CrosstalkEnergyDepositRestrictedY", "Crosstalk energy in Y plain maximaly 2 cubes from deposit",500,0,500);
    CrosstalkEnergyDepositRestrictedY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositRestrictedY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *HistogramCrosstalkDistanceEnergyHigherThanX= new TH1F("HistogramCrosstalkDistanceEnergyHigherThanX", "Cube distance of energy deposit from peak X axis if energy higher than 50",10,-5,5);
    HistogramCrosstalkDistanceEnergyHigherThanX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceEnergyHigherThanX->GetXaxis()->SetTitle("X detector axis [cm]");
    
    TH1F *HistogramCrosstalkDistanceEnergyHigherThanY= new TH1F("HistogramCrosstalkDistanceEnergyHigherThanY", "Cube distance of energy deposit from peak Y axis if energy higher than 50",10,-5,5);
    HistogramCrosstalkDistanceEnergyHigherThanY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceEnergyHigherThanY->GetXaxis()->SetTitle("Y detector axis [cm]");
    
    TH1F *HistogramCrosstalkDistanceCutX= new TH1F("HistogramCrosstalkDistanceCutX", "Cube distance of energy deposit from peak X axis if energy higher than 1",10,-5,5);
    HistogramCrosstalkDistanceCutX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceCutX->GetXaxis()->SetTitle("X detector axis [cm]");  
    
    TH1F *HistogramCrosstalkDistanceCutY= new TH1F("HistogramCrosstalkDistanceCutY", "Cube distance of energy deposit from peak Y axis if energy higher than 1",10,-5,5);
    HistogramCrosstalkDistanceCutY->GetYaxis()->SetTitle("Y detector axis [cm]");
    HistogramCrosstalkDistanceCutY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *HistogramCrosstalkDistanceTypeX= new TH1F("HistogramCrosstalkDistanceTypeX", "Number of cubes that recieved signal X axis, stopping point",48,0,48);
    HistogramCrosstalkDistanceTypeX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceTypeX->GetXaxis()->SetTitle("X detector axis [cm]");   
    
    TH1F *HistogramCrosstalkDistanceTypeY= new TH1F("HistogramCrosstalkDistanceTypeY", "Number of cubes that recieved signal Y axis, stopping point",16,0,16);
    HistogramCrosstalkDistanceTypeY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceTypeY->GetXaxis()->SetTitle("Y detector axis [cm]"); 
/////  
    TH2F *EnergyTrigTimeX = new TH2F("EnergyTrigTimeX","Energy and Time of Trigger X axis stopping point + Crosstalk", 100,-100,100,500,0,1500);
    EnergyTrigTimeX->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeX->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH2F *EnergyTrigTimeY = new TH2F("EnergyTrigTimeY","Energy and Time of Trigger Y axis stopping point + Crosstalk", 100,-100,100,500,0,1500);
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
    
    TH2F *EnergyTrigTimeCUTGX = new TH2F("EnergyTrigTimeCUTGX","Energy and Time of Trigger X axis after CUTG", 100,-100,100,500,0,1500);
    EnergyTrigTimeCUTGX->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeCUTGX->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH2F *EnergyTrigTimeCUTGY = new TH2F("EnergyTrigTimeCUTGY","Energy and Time of Trigger Y axis after CUTG", 100,-100,100,500,0,1500);
    EnergyTrigTimeCUTGY->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeCUTGY->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
/////
    TH1F *CrosstalkEnergyDepositMinus1X = new TH1F("CrosstalkEnergyDepositMinus1X", "Crosstalk energy in X plain, one cube backward.",500,0,500);
    CrosstalkEnergyDepositMinus1X->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1X->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMinus1Y = new TH1F("CrosstalkEnergyDepositMinus1Y", "Crosstalk energy in Y plain, one cube backward.",500,0,500);
    CrosstalkEnergyDepositMinus1Y->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1Y->GetXaxis()->SetTitle("Energy [p.e.]"); 
    
    TH1F *CrosstalkEnergyDepositMinus1OneCubeX = new TH1F("CrosstalkEnergyDepositMinus1OneCubeX", "Crosstalk energy in X plain, one cube backward, one cube away.",50,0,100);
    CrosstalkEnergyDepositMinus1OneCubeX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1OneCubeX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMinus1OneCubeY = new TH1F("CrosstalkEnergyDepositMinus1OneCubeY", "Crosstalk energy in Y plain, one cube backward, one cube away..",50,0,100);
    CrosstalkEnergyDepositMinus1OneCubeY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1OneCubeY->GetXaxis()->SetTitle("Energy [p.e.]"); 
    
    TH1F *CrosstalkEnergyDepositMinus1TwoCubesX = new TH1F("CrosstalkEnergyDepositMinus1TwoCubesX", "Crosstalk energy in X plain, one cube backward, two cubes away.",50,0,100);
    CrosstalkEnergyDepositMinus1TwoCubesX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1TwoCubesX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMinus1TwoCubesY = new TH1F("CrosstalkEnergyDepositMinus1TwoCubesY", "Crosstalk energy in Y plain, one cube backward, two cubes away..",50,0,100);
    CrosstalkEnergyDepositMinus1TwoCubesY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1TwoCubesY->GetXaxis()->SetTitle("Energy [p.e.]"); 
    
    TH1F *CrosstalkEnergyPercentageMinus1X = new TH1F("CrosstalkEnergyPercentageMinus1X", "Crosstalk divided by main deposit in X plain, one cube backward.",200,0,100);
    CrosstalkEnergyPercentageMinus1X->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMinus1X->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyPercentageMinus1Y = new TH1F("CrosstalkEnergyPercentageMinus1Y", "Crosstalk divided by main deposit in Y plain, one cube backward.",200,0,100);
    CrosstalkEnergyPercentageMinus1Y->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMinus1Y->GetXaxis()->SetTitle("Percentage %"); 
    
    TH1F *CrosstalkEnergyPercentageMinus1OneCubeX = new TH1F("CrosstalkEnergyPercentageMinus1OneCubeX", "Crosstalk divided by main deposit in X plain, one cube backward, one cube.",200,0,100);
    CrosstalkEnergyPercentageMinus1OneCubeX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMinus1OneCubeX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyPercentageMinus1OneCubeY = new TH1F("CrosstalkEnergyPercentageMinus1OneCubeY", "Crosstalk divided by main deposit in Y plain, one cube backward, one cube.",200,0,100);
    CrosstalkEnergyPercentageMinus1OneCubeY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMinus1OneCubeY->GetXaxis()->SetTitle("Percentage %"); 
    
    TH1F *CrosstalkEnergyPercentageMinus1TwoCubesX = new TH1F("CrosstalkEnergyPercentageMinus1TwoCubesX", "Crosstalk divided by main deposit in X plain, one cube backward, two cubes.",100,0,100);
    CrosstalkEnergyPercentageMinus1TwoCubesX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMinus1TwoCubesX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyPercentageMinus1TwoCubesY = new TH1F("CrosstalkEnergyPercentageMinus1TwoCubesY", "Crosstalk divided by main deposit in Y plain, one cube backward, two cubes.",100,0,100);
    CrosstalkEnergyPercentageMinus1TwoCubesY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMinus1TwoCubesY->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositPercentageMinus1SecondCubeNewX = new TH1F("CrosstalkEnergyDepositPercentageMinus1SecondCubeNewX", "Crosstalk in second cube divided by crosstalk in first cube, in X plain, one cube backward.",100,0,100);
    CrosstalkEnergyDepositPercentageMinus1SecondCubeNewX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageMinus1SecondCubeNewX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *HistogramCrosstalkDistanceMinus1X= new TH1F("HistogramCrosstalkDistanceMinus1X", "Cube distance of energy deposit from peak X axis, one cube backward",10,-5,5);
    HistogramCrosstalkDistanceMinus1X->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMinus1X->GetXaxis()->SetTitle("X detector axis [cm]");
    
    TH1F *HistogramCrosstalkDistanceMinus1Y = new TH1F("HistogramCrosstalkDistanceMinus1Y", "Cube distance of energy deposit from peak Y axis, one cube backward",10,-5,5);
    HistogramCrosstalkDistanceMinus1Y->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMinus1Y->GetXaxis()->SetTitle("Y detector axis [cm]");
    
    TH1F *CrosstalkEnergyDepositMinus1CUTGX = new TH1F("CrosstalkEnergyDepositMinus1CUTGX", "Crosstalk energy in X plain, one cube backward, after CUTG.",200,0,200);
    CrosstalkEnergyDepositMinus1CUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1CUTGX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMinus1CUTGY = new TH1F("CrosstalkEnergyDepositMinus1CUTGY", "Crosstalk energy in Y plain, one cube backward, after CUTG.",200,0,200);
    CrosstalkEnergyDepositMinus1CUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1CUTGY->GetXaxis()->SetTitle("Energy [p.e.]"); 
    
    TH1F *CrosstalkEnergyDepositMinus1OneCubeCUTGX = new TH1F("CrosstalkEnergyDepositMinus1OneCubeCUTGX", "Crosstalk energy in X plain, one cube backward, after CUTG only one cube away",50,0,100);
    CrosstalkEnergyDepositMinus1OneCubeCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1OneCubeCUTGX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMinus1OneCubeCUTGY = new TH1F("CrosstalkEnergyDepositMinus1OneCubeCUTGY", "Crosstalk energy in Y plain, one cube backward, after CUTG only, one cube away",50,0,100);
    CrosstalkEnergyDepositMinus1OneCubeCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1OneCubeCUTGY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMinus1TwoCubesCUTGX = new TH1F("CrosstalkEnergyDepositMinus1TwoCubesCUTGX", "Crosstalk energy in X plain, two cubes backward, after CUTG only one cube away",50,0,100);
    CrosstalkEnergyDepositMinus1TwoCubesCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1TwoCubesCUTGX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMinus1TwoCubesCUTGY = new TH1F("CrosstalkEnergyDepositMinus1TwoCubesCUTGY", "Crosstalk energy in Y plain, two cubes backward, after CUTG only, one cube away",50,0,100);
    CrosstalkEnergyDepositMinus1TwoCubesCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1TwoCubesCUTGY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyPercentageMinus1CUTGX = new TH1F("CrosstalkEnergyPercentageMinus1CUTGX", "Crosstalk divided by main deposit in X plain, one cube backward, after CUTG.",200,0,100);
    CrosstalkEnergyPercentageMinus1CUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMinus1CUTGX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyPercentageMinus1CUTGY = new TH1F("CrosstalkEnergyPercentageMinus1CUTGY", "Crosstalk divided by main deposit in Y plain, one cube backward, after CUTG.",200,0,100);
    CrosstalkEnergyPercentageMinus1CUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMinus1CUTGY->GetXaxis()->SetTitle("Percentage %"); 
    
    TH1F *HistogramCrosstalkDistanceMinus1CUTGX= new TH1F("HistogramCrosstalkDistanceMinus1CUTGX", "Cube distance of energy deposit from peak X axis, one cube backward, after CUTG",10,-5,5);
    HistogramCrosstalkDistanceMinus1CUTGX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMinus1CUTGX->GetXaxis()->SetTitle("X detector axis [cm]");
    
    TH1F *HistogramCrosstalkDistanceMinus1CUTGY = new TH1F("HistogramCrosstalkDistanceMinus1CUTGY", "Cube distance of energy deposit from peak Y axis, one cube backward after CUTG",10,-5,5);
    HistogramCrosstalkDistanceMinus1CUTGY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMinus1CUTGY->GetXaxis()->SetTitle("Y detector axis [cm]");
    
    TH1F *HistogramRealPeakEnergyDepositMinus1 = new TH1F("HistogramRealPeakEnergyDepositMinus1", "Histogram of highest value deposit, 1 cubes away from stopping poin.",100,0,2500);
    HistogramRealPeakEnergyDepositMinus1->GetYaxis()->SetTitle("Number of events");
    HistogramRealPeakEnergyDepositMinus1->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *HistogramCrosstalkDistanceTypeMinus1X= new TH1F("HistogramCrosstalkDistanceTypeMinus1X", "Number of cubes that recieved signal X axis, one cube backward",48,0,48);
    HistogramCrosstalkDistanceTypeMinus1X->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceTypeMinus1X->GetXaxis()->SetTitle("X detector axis [cm]");   
    
    TH1F *HistogramCrosstalkDistanceTypeMinus1Y= new TH1F("HistogramCrosstalkDistanceTypeMinus1Y", "Number of cubes that recieved signal Y axis, one cube backward",16,0,16);
    HistogramCrosstalkDistanceTypeMinus1Y->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceTypeMinus1Y->GetXaxis()->SetTitle("Y detector axis [cm]"); 
/////
    TH2F *EnergyTrigTimeMinus1X = new TH2F("EnergyTrigTimeMinus1X","Energy and Time of Trigger X axis, one cube backward", 100,-100,100,500,0,1500);
    EnergyTrigTimeMinus1X->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeMinus1X->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH2F *EnergyTrigTimeMinus1Y = new TH2F("EnergyTrigTimeMinus1Y","Energy and Time of Trigger Y axis, one cube backward", 100,-100,100,500,0,1500);
    EnergyTrigTimeMinus1Y->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeMinus1Y->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
///////////
    TH1F *CrosstalkEnergyDepositMiddleX = new TH1F("CrosstalkEnergyDepositMiddleX", "Crosstalk energy in X plain, 15 cubes away from stopping poin.",500,0,500);
    CrosstalkEnergyDepositMiddleX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMiddleY = new TH1F("CrosstalkEnergyDepositMiddleY", "Crosstalk energy in Y plain, 15 cubes away from stopping poin.",500,0,500);
    CrosstalkEnergyDepositMiddleY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleY->GetXaxis()->SetTitle("Energy [p.e.]"); 
    
    TH1F *CrosstalkEnergyDepositMiddleOneCubeX = new TH1F("CrosstalkEnergyDepositMiddleOneCubeX", "Crosstalk energy in X plain, 15 cubes away from stopping poin, one cube.",50,0,100);
    CrosstalkEnergyDepositMiddleOneCubeX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleOneCubeX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMiddleOneCubeY = new TH1F("CrosstalkEnergyDepositMiddleOneCubeY", "Crosstalk energy in Y plain, 15 cubes away from stopping poin, one cube.",50,0,100);
    CrosstalkEnergyDepositMiddleOneCubeY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleOneCubeY->GetXaxis()->SetTitle("Energy [p.e.]"); 
    
    TH1F *CrosstalkEnergyDepositMiddleTwoCubesX = new TH1F("CrosstalkEnergyDepositMiddleTwoCubesX", "Crosstalk energy in X plain, 15 cubes away from stopping poin, two cubes.",50,0,100);
    CrosstalkEnergyDepositMiddleTwoCubesX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleTwoCubesX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMiddleTwoCubesY = new TH1F("CrosstalkEnergyDepositMiddleTwoCubesY", "Crosstalk energy in Y plain, 15 cubes away from stopping poin, two cubes.",50,0,100);
    CrosstalkEnergyDepositMiddleTwoCubesY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleTwoCubesY->GetXaxis()->SetTitle("Energy [p.e.]"); 
    
    TH1F *CrosstalkEnergyPercentageMiddleX = new TH1F("CrosstalkEnergyPercentageMiddleX", "Crosstalk energy divided by main deposit in X plain, 15 cubes away from stopping poin.",200,0,100);
    CrosstalkEnergyPercentageMiddleX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMiddleX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyPercentageMiddleY = new TH1F("CrosstalkEnergyPercentageMiddleY", "Crosstalk energy divided by main deposit in Y plain, 15 cubes away from stopping poin..",200,0,100);
    CrosstalkEnergyPercentageMiddleY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMiddleY->GetXaxis()->SetTitle("Percentage %"); 
    
    TH1F *CrosstalkEnergyPercentageMiddleOneCubeX = new TH1F("CrosstalkEnergyPercentageMiddleOneCubeX", "Crosstalk energy divided by main deposit in X plain, 15 cubes away from stopping poin, one cube.",200,0,100);
    CrosstalkEnergyPercentageMiddleOneCubeX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMiddleOneCubeX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyPercentageMiddleOneCubeY = new TH1F("CrosstalkEnergyPercentageMiddleOneCubeY", "Crosstalk energy divided by main deposit in Y plain, 15 cubes away from stopping poin, one cube.",200,0,100);
    CrosstalkEnergyPercentageMiddleOneCubeY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMiddleOneCubeY->GetXaxis()->SetTitle("Percentage %"); 
    
    TH1F *CrosstalkEnergyPercentageMiddleTwoCubesX = new TH1F("CrosstalkEnergyPercentageMiddleTwoCubesX", "Crosstalk energy divided by main deposit in X plain, 15 cubes away from stopping poin, two cubes.",100,0,100);
    CrosstalkEnergyPercentageMiddleTwoCubesX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMiddleTwoCubesX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyPercentageMiddleTwoCubesY = new TH1F("CrosstalkEnergyPercentageMiddleTwoCubesY", "Crosstalk energy divided by main deposit in Y plain, 15 cubes away from stopping poin, two cubes.",100,0,100);
    CrosstalkEnergyPercentageMiddleTwoCubesY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMiddleTwoCubesY->GetXaxis()->SetTitle("Percentage %"); 
    
    TH1F *CrosstalkEnergyDepositPercentageMiddleSecondCubeNewX = new TH1F("CrosstalkEnergyDepositPercentageMiddleSecondCubeNewX", "Crosstalk in second cube divided by crosstalk in first cube, in X plain, 15 cubes backward.",100,0,100);
    CrosstalkEnergyDepositPercentageMiddleSecondCubeNewX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageMiddleSecondCubeNewX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *HistogramCrosstalkDistanceMiddleX= new TH1F("HistogramCrosstalkDistanceMiddleX", "Cube distance of energy deposit from peak X axis, 15 cubes away from stopping poin.",10,-5,5);
    HistogramCrosstalkDistanceMiddleX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMiddleX->GetXaxis()->SetTitle("X detector axis [cm]");
    
    TH1F *HistogramCrosstalkDistanceMiddleY = new TH1F("HistogramCrosstalkDistanceMiddleY", "Cube distance of energy deposit from peak Y axis, 15 cubes away from stopping poin.",10,-5,5);
    HistogramCrosstalkDistanceMiddleY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMiddleY->GetXaxis()->SetTitle("Y detector axis [cm]");
    
    TH1F *HistogramRealPeakEnergyDepositMiddle = new TH1F("HistogramRealPeakEnergyDepositMiddle", "Histogram of highest value deposit, 15 cubes away from stopping poin.",100,0,2500);
    HistogramRealPeakEnergyDepositMiddle->GetYaxis()->SetTitle("Number of events");
    HistogramRealPeakEnergyDepositMiddle->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *HistogramCrosstalkDistanceTypeMiddleX= new TH1F("HistogramCrosstalkDistanceTypeMiddleX", "Number of cubes that recieved signal X axis, middle of track",48,0,48);
    HistogramCrosstalkDistanceTypeMiddleX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceTypeMiddleX->GetXaxis()->SetTitle("X detector axis [cm]");   
    
    TH1F *HistogramCrosstalkDistanceTypeMiddleY= new TH1F("HistogramCrosstalkDistanceTypeMiddleY", "Number of cubes that recieved signal Y axis, middle of track",16,0,16);
    HistogramCrosstalkDistanceTypeMiddleY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceTypeMiddleY->GetXaxis()->SetTitle("Y detector axis [cm]"); 
    
    TH1F *CrosstalkEnergyDepositMiddleCUTGX = new TH1F("CrosstalkEnergyDepositMiddleCUTGX", "Crosstalk energy in X plain, 15 cubes away from stopping poin, after CUTG.",200,0,200);
    CrosstalkEnergyDepositMiddleCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleCUTGX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMiddleCUTGY = new TH1F("CrosstalkEnergyDepositMiddleCUTGY", "Crosstalk energy in Y plain, 15 cubes away from stopping point, after CUTG.",200,0,200);
    CrosstalkEnergyDepositMiddleCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleCUTGY->GetXaxis()->SetTitle("Energy [p.e.]"); 
    
    TH1F *CrosstalkEnergyDepositMiddleOneCubeCUTGX = new TH1F("CrosstalkEnergyDepositMiddleOneCubeCUTGX", "Crosstalk energy in X plain, 15 cube backward, after CUTG only one cube away",50,0,100);
    CrosstalkEnergyDepositMiddleOneCubeCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleOneCubeCUTGX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMiddleOneCubeCUTGY = new TH1F("CrosstalkEnergyDepositMiddleOneCubeCUTGY", "Crosstalk energy in Y plain, 15 cube backward, after CUTG only, one cube away",50,0,100);
    CrosstalkEnergyDepositMiddleOneCubeCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleOneCubeCUTGY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMiddleTwoCubesCUTGX = new TH1F("CrosstalkEnergyDepositMiddleTwoCubesCUTGX", "Crosstalk energy in X plain, 15 cube backward, after CUTG only two cubes away",50,0,100);
    CrosstalkEnergyDepositMiddleTwoCubesCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleTwoCubesCUTGX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMiddleTwoCubesCUTGY = new TH1F("CrosstalkEnergyDepositMiddleTwoCubesCUTGY", "Crosstalk energy in Y plain, 15 cube backward, after CUTG only, two cubes away",50,0,100);
    CrosstalkEnergyDepositMiddleTwoCubesCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleTwoCubesCUTGY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyPercentageMiddleCUTGX = new TH1F("CrosstalkEnergyPercentageMiddleCUTGX", "Crosstalk energy divided by main deposit in X plain, 15 cubes away from stopping point, after CUTG.",200,0,100);
    CrosstalkEnergyPercentageMiddleCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMiddleCUTGX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyPercentageMiddleCUTGY = new TH1F("CrosstalkEnergyPercentageMiddleCUTGY", "Crosstalk energy divided by main deposit in Y plain, 15 cubes away from stopping point, after CUTG.",200,0,100);
    CrosstalkEnergyPercentageMiddleCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMiddleCUTGY->GetXaxis()->SetTitle("Percentage %"); 
    
    TH1F *HistogramCrosstalkDistanceMiddleCUTGX= new TH1F("HistogramCrosstalkDistanceMiddleCUTGX", "Cube distance of energy deposit from peak X axis, 15 cubes away from stopping point, after CUTG.",10,-5,5);
    HistogramCrosstalkDistanceMiddleCUTGX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMiddleCUTGX->GetXaxis()->SetTitle("X detector axis [cm]");
    
    TH1F *HistogramCrosstalkDistanceMiddleCUTGY = new TH1F("HistogramCrosstalkDistanceMiddleCUTGY", "Cube distance of energy deposit from peak Y axis, 15 cubes away from stopping point, after CUTG.",10,-5,5);
    HistogramCrosstalkDistanceMiddleCUTGY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMiddleCUTGY->GetXaxis()->SetTitle("Y detector axis [cm]");
    /////
    TH2F *EnergyTrigTimeMiddleX = new TH2F("EnergyTrigTimeMiddleX","Energy and Time of Trigger X axis, 15 cubes away from stopping point", 100,-100,100,500,0,1500);
    EnergyTrigTimeMiddleX->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeMiddleX->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH2F *EnergyTrigTimeMiddleY = new TH2F("EnergyTrigTimeMiddleY","Energy and Time of Trigger Y axis, 15 cubes away from stopping point", 100,-100,100,500,0,1500);
    EnergyTrigTimeMiddleY->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeMiddleY->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
/////
    TH2F *EnergyTrigTimeTestX = new TH2F("EnergyTrigTimeTestX","X", 100,-100,100,500,0,1500);
    EnergyTrigTimeTestX->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeTestX->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    TH2F *EnergyTrigTimeTestY = new TH2F("EnergyTrigTimeTestY","Y", 100,-100,100,500,0,1500);
    EnergyTrigTimeTestY->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeTestY->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH2F *EnergyTrigTimeTestUpgradeX = new TH2F("EnergyTrigTimeTestUpgradeX","Upgrade X", 100,-100,100,500,0,1500);
    EnergyTrigTimeTestUpgradeX->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeTestUpgradeX->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    TH2F *EnergyTrigTimeTestUpgradeY = new TH2F("EnergyTrigTimeTestUpgradeY","Upgrade Y", 100,-100,100,500,0,1500);
    EnergyTrigTimeTestUpgradeY->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeTestUpgradeY->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH2F *EnergyTrigTimeTestLowX = new TH2F("EnergyTrigTimeTestLowX","X low", 100,-100,100,500,0,1500);
    EnergyTrigTimeTestLowX->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeTestLowX->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    TH2F *EnergyTrigTimeTestLowY = new TH2F("EnergyTrigTimeTestLowY","Y low", 100,-100,100,500,0,1500);
    EnergyTrigTimeTestLowY->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeTestLowY->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TDirectory *events2D = wfile.mkdir("events2D");
    TDirectory *CrossEnergy = wfile.mkdir("CrossEnergy");
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
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
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

    double energyDepX_XZ_Plain[3][24];
    double energyDepY_YZ_Plain[3][8];

    int eventNum=0;
    int licznik=1;
    bool LargehitTimeDif = 0;
    double TriggerTime=0;
    double DepozytPomocniczy=0;
    
    TCanvas *DisplayCanvas = new TCanvas("DisplayCanvas","DisplayCanvas", 1400, 1000);
    TCanvas *CrossEnergyCanvas = new TCanvas("CrossEnergyCanvas","CrossEnergyCanvas", 1400, 1000);
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
        for( int TOFtrigger = 0; TOFtrigger < FEB[12].FEBSN->size(); TOFtrigger++)
            {
            if (FEB[12].hitTimeDif->at(TOFtrigger) > 0 && NumberEvDis > eventNum)
            {
                for (int ik = 0; ik < 48; ik++ ) //zerowanie tablic przechowujace dane, Z
                {
                    energyDepZ[ik] = 0;
                    energyDepZ_XZ[ik] = 0;
                    energyDepZ_YZ[ik] = 0;
                }
                for (int ik = 0; ik < 24; ik++ ) //zerowanie tablic przechowujace dane, X
                {
                    energyDepX_XZ[ik] = 0;
                    energyDepX_XZ_Plain[0][ik] = 0;
                    energyDepX_XZ_Plain[1][ik] = 0;
                    energyDepX_XZ_Plain[2][ik] = 0;
                }
                for (int ik = 0; ik < 8; ik++ ) //zerowanie tablic przechowujace dane, X
                {
                    energyDepY_YZ[ik] = 0;
                    energyDepY_YZ_Plain[0][ik] = 0;
                    energyDepY_YZ_Plain[1][ik] = 0;
                    energyDepY_YZ_Plain[2][ik] = 0;
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
                                DepozytPomocniczy=FEB[FEBs[i]].hitCharge_pe->at(check);
                                event_XY[eventNum]-> Fill( MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)], DepozytPomocniczy);
                                EventsMap_XY->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],1);
                                EnergyTrigTimeAll->Fill(FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime, DepozytPomocniczy);
                            }
                            else if ( FEBs[i] == 1 || FEBs[i] == 2 || FEBs[i] == 17 || FEBs[i] ==  24) //Plaszczyzna YZ
                            {
                                DepozytPomocniczy=FEB[FEBs[i]].hitCharge_pe->at(check);
                                event_YZ[eventNum]->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)], MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],DepozytPomocniczy);
                                EventsMap_YZ->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],1);
                                EnergyTrigTimeAll->Fill( FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime, DepozytPomocniczy );
                                if (DepozytPomocniczy > 0 && DepozytPomocniczy < 10000)// zmiana 0 and 10000
                                {
                                    energyDepZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += DepozytPomocniczy;
                                    energyDepZ_YZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += DepozytPomocniczy;
                                    energyDepY_YZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += DepozytPomocniczy;
                                }
                            }
                            else //Plaszczyzna XZ
                            {
                                DepozytPomocniczy=FEB[FEBs[i]].hitCharge_pe->at(check);
                                event_XZ[eventNum]->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)], DepozytPomocniczy);
                                EventsMap_XZ->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],1);
                                EnergyTrigTimeAll->Fill(FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime, DepozytPomocniczy);
                                if (DepozytPomocniczy > 0 && DepozytPomocniczy < 10000) //zmiana 0 and 10000
                                {
                                    energyDepZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += DepozytPomocniczy;
                                    energyDepZ_XZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += DepozytPomocniczy;
                                    energyDepX_XZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += DepozytPomocniczy;
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

            double RealPeakEnergyX[3]={};   //0-StoppingPoint,1-OneCubeBackward,2-MiddleOfTrack
            int RealPeakNumberX[3]={};     //0-StoppingPoint,1-OneCubeBackward,2-MiddleOfTrack

            double RealPeakEnergyY[3]={}; //0-StoppingPoint,1-OneCubeBackward,2-MiddleOfTrack
            int RealPeakNumberY[3]={};   //0-StoppingPoint,1-OneCubeBackward,2-MiddleOfTrack
            
            double RealPeakEnergyResult[3]={};

            //double HighestEnergyY=0;
            //int HighestEnergyNumberY=0;

            int CrosstalkDistance=0;
            int PomocniczyNumerKostki=0;
            double PomicniczyTriggerTime=0;
            
            int CrossEventTypeX[3][48]={}; //Z,Z-1,Z-15||24+24
            int CrossEventTypeY[3][16]={}; //Z,Z-1,Z-15||8+8
            
            int CrossEventTypeCounterX[3]={}; //Z,Z-1,Z-15
            int CrossEventTypeCounterY[3]={}; //Z,Z-1,Z-15
            
            double WierdTestX[3][2][2]={}; //[Pozycje][deposit][czas]
            double WierdTestY[3][2][2]={}; //[Pozycje][deposit][czas]
            
            int WierdLicznikX[3]={};//[Pozycje]
            int WierdLicznikY[3]={};//[Pozycje]
            
            int EnergeticEventsX=0;
            int EnergeticEventsY=0;
            
            double CrosstalkFirstCubeValue[3][2]; //[Pozycje][0-lewo,1-prawo]
            
            double ProtonThreshold=-80; //Value to seperate protons from other hadrons (pions most likely)
            double TriggerTimeValue=0; 
            int TriggerTimerCounter=0;
            
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
                if(energyDepZ[ik]>PeakEnergy) //szukanie najwiekszego depozytu
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
                    if(energyDepZ[ik]>RealPeakEnergy*0.75) //szukanie stopping point
                    {
                        RealPeakEnergy=energyDepZ[ik];
                        RealPeakNumber=ik;
                    }
                }
            }
            for(int ik = 0; ik < 24; ik++ )
            {
                energyX_XZ[eventNum]->Fill(ik,energyDepX_XZ[ik]);
            }
            for(int ik = 0; ik < 8; ik++ )
            {
                energyY_YZ[eventNum]->Fill(ik,energyDepY_YZ[ik]);
                
                /*if(energyDepY_YZ[ik]>HighestEnergyY)
                {
                    HighestEnergyY=energyDepY_YZ[ik];
                    HighestEnergyNumberY=ik;
                }
                */
            }
           bool DiscontinuityCut=0; // maximally two layers before peak can have 0 deposit
            if(RealPeakNumber>3)
            {
                if(energyDepZ[RealPeakNumber-1]!=0 || energyDepZ[RealPeakNumber-2]!=0 || energyDepZ[RealPeakNumber-3]!=0)
                {
                    DiscontinuityCut=1;
                }
            }
            bool TrackBeginningCut=0; //ciecie usuwajace czastki bez depozytu na poczatku detektora
            if(energyDepZ[0]>0 || energyDepZ[1]>0 || energyDepZ[2]>0)
            {
                TrackBeginningCut=1;
            }
            //Fitowanie potrzebne do ciecia usuwajacego nie gausowe smieci
            double sigma=0;
            bool sigmaCut=0;
            if ( LargehitTimeDif == 0 && StoppingParticle==1 && PeakEnergy>250 && DiscontinuityCut==1 && TrackBeginningCut==1)
            {
                TF1 *EnergyFitX = new TF1("EnergyFitX", "gaus");
                energyX_XZ[eventNum]-> Fit(EnergyFitX,"q","",1 , 23);
                sigma = EnergyFitX->GetParameter(2); // We chosei sigma to get rid of garbage

                delete EnergyFitX;
                if(sigma < 1.4) ///setting value for sigma cut
                {
                    sigmaCut=1;
                }
            }
            ////////
            if(LargehitTimeDif == 0 && StoppingParticle==1 && PeakEnergy>250 && DiscontinuityCut==1 && TrackBeginningCut==1 && sigmaCut==1)
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
                                { //przypisanie depozytow w plaszczyznie znalezionego stopping point itd.
                                    PomocniczyNumerKostki = MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)];
                                    DepozytPomocniczy=FEB[FEBs[i]].hitCharge_pe->at(check);
                                    PomicniczyTriggerTime=FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime;
                                    if(PomocniczyNumerKostki == RealPeakNumber && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000)// zmiana 0 and 10000 
                                    {
                                        energyDepY_YZ_Plain[0][MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += DepozytPomocniczy;
                                        //TriggerTimeValue+=PomicniczyTriggerTime;
                                        //TriggerTimerCounter+=1;
                                    }
                                    if(PomocniczyNumerKostki == RealPeakNumber-1 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000)// zmiana 0 and 10000
                                    {
                                        energyDepY_YZ_Plain[1][MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += DepozytPomocniczy;
                                        //TriggerTimeValue+=PomicniczyTriggerTime;
                                       //TriggerTimerCounter+=1;
                                    }
                                    if(PomocniczyNumerKostki == RealPeakNumber-15 && RealPeakNumber>15 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000)// zmiana 0 and 10000
                                    {
                                        energyDepY_YZ_Plain[2][MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += DepozytPomocniczy;
                                        //TriggerTimeValue+=PomicniczyTriggerTime;
                                        //TriggerTimerCounter+=1;
                                    }
                                    TriggerTimeValue+=PomicniczyTriggerTime;
                                    TriggerTimerCounter+=1;
                                }
                                else //Plaszczyzna XZ
                                { //przypisanie depozytow w plaszczyznie znalezionego stopping point itd.
                                    PomocniczyNumerKostki = MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)];
                                    DepozytPomocniczy=FEB[FEBs[i]].hitCharge_pe->at(check);
                                    PomicniczyTriggerTime=FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime;
                                    if(PomocniczyNumerKostki == RealPeakNumber && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000) //zmiana 0 and 10000
                                    {
                                        energyDepX_XZ_Plain[0][MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += DepozytPomocniczy;
                                        //TriggerTimeValue+=PomicniczyTriggerTime;
                                        //TriggerTimerCounter+=1;
                                    }
                                    if(PomocniczyNumerKostki == RealPeakNumber-1 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000) //zmiana 0 and 10000
                                    {
                                        energyDepX_XZ_Plain[1][MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += DepozytPomocniczy;
                                        //TriggerTimeValue+=PomicniczyTriggerTime;
                                        //TriggerTimerCounter+=1;
                                    }
                                    if(PomocniczyNumerKostki == RealPeakNumber-15 && RealPeakNumber>15 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000) //zmiana 0 and 10000
                                    {
                                        energyDepX_XZ_Plain[2][MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += DepozytPomocniczy;
                                        //TriggerTimeValue+=PomicniczyTriggerTime;
                                        //TriggerTimerCounter+=1;
                                    }
                                    TriggerTimeValue+=PomicniczyTriggerTime;
                                    TriggerTimerCounter+=1;
                                }
                            }
                        }
                    }
                }
                int LoopLimit=3; //poniewaz patrzymy na 3 punkty
                if(RealPeakNumber<=15) //jesli mamy za krotki tor to nie chcemy wyjsc poza tablice
                {
                    LoopLimit=2;
                }
                for(int hk = 0; hk < LoopLimit; hk++ )
                {
                    for(int ik = 0; ik < 24; ik++ )
                    {
                        if(hk == 0)
                        {
                        energyX_XZ_Plain[eventNum]->Fill(ik,energyDepX_XZ_Plain[hk][ik]);
                        }
                        if(energyDepX_XZ_Plain[hk][ik]>RealPeakEnergyX[hk])
                        {
                            RealPeakEnergyX[hk]=energyDepX_XZ_Plain[hk][ik];
                            RealPeakNumberX[hk]=ik;
                        }
                        if(hk==0 && energyDepX_XZ_Plain[0][ik]>200)
                        {
                            EnergeticEventsX+=1;
                        }
                    }
                    for(int ik = 0; ik < 8; ik++ )
                    {
                        if(hk == 0)
                        {
                        energyY_YZ_Plain[eventNum]->Fill(ik,energyDepY_YZ_Plain[hk][ik]);
                        }
                        if(energyDepY_YZ_Plain[hk][ik]>RealPeakEnergyY[hk])
                        {
                            RealPeakEnergyY[hk]=energyDepY_YZ_Plain[hk][ik];
                            RealPeakNumberY[hk]=ik;
                        }
                        if(hk==0 && energyDepY_YZ_Plain[0][ik]>200)
                        {
                            EnergeticEventsY+=1;
                        }
                    }
                }
            }
            bool BorderCutY=0; // ciecie usuwajace eventy ktore sie slizgaja po krawedzi Y
            if(RealPeakNumberY[0]!=0 && RealPeakNumberY[0]!=7)
            {
                BorderCutY=1;
            }
            
            bool BorderCutX=0; // ciecie usuwajace eventy ktore sie slizgaja po krawedzi X
            if(RealPeakNumberX[0]!=0 && RealPeakNumberX[0]!=23)
            {
                BorderCutX=1;
            }
            bool ProtonFlag=0;
            if( (TriggerTimeValue/TriggerTimerCounter) > ProtonThreshold)
            {
                ProtonFlag=1;
            }
            
            if(LargehitTimeDif == 0 && StoppingParticle==1 && PeakEnergy>250 && DiscontinuityCut==1 && TrackBeginningCut==1 && BorderCutY==1 && BorderCutX && sigmaCut==1 && EnergeticEventsX==1 && EnergeticEventsY==1 && ProtonFlag==1)
            {   
//                 //Sprawdzenie wartosci stopujacego protonu potrzebna do wykresow procentowych 
                for(int ip=0; ip<3; ip++)
                {
                    RealPeakEnergyResult[ip]=(RealPeakEnergyX[ip]+RealPeakEnergyY[ip])/2;
                    if(0.2*RealPeakEnergyX[ip]>RealPeakEnergyY[ip])
                    {
                        RealPeakEnergyResult[ip]=RealPeakEnergyX[ip];
                    }
                    if(0.2*RealPeakEnergyY[ip]>RealPeakEnergyX[ip])
                    {
                        RealPeakEnergyResult[ip]=RealPeakEnergyY[ip];
                    }
                    
                    CrosstalkFirstCubeValue[ip][0]=energyDepX_XZ_Plain[ip][RealPeakNumberX[ip]-1];
                    CrosstalkFirstCubeValue[ip][1]=energyDepX_XZ_Plain[ip][RealPeakNumberX[ip]+1];
                }
                

                //Implenentation of CUTG neccesary to get rid of some nasty events|||| propably no longer neccesary
                TCutG *cutgTimeEnergy = new TCutG("cutgTimeEnergy",6);
                cutgTimeEnergy->SetFillColor(1);
                cutgTimeEnergy->SetPoint(0,-100,10);
                cutgTimeEnergy->SetPoint(1,-70,120);
                cutgTimeEnergy->SetPoint(2,200,120);
                cutgTimeEnergy->SetPoint(3,200,2000);
                cutgTimeEnergy->SetPoint(4,-100,2000);
                cutgTimeEnergy->SetPoint(5,-100,10);
                
                bool cutgCut;
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
                                    PomicniczyTriggerTime=FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime;
                                    DepozytPomocniczy=FEB[FEBs[i]].hitCharge_pe->at(check);
                                    if ( PomocniczyNumerKostki == RealPeakNumber && RealPeakEnergyY[0]>40 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000)// zmiana 0 and 10000
                                    {
                                        CrosstalkDistance = MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] - RealPeakNumberY[0];
                                        if( abs(CrosstalkDistance)==2 || abs(CrosstalkDistance)==1)
                                        {
                                             CrosstalkEnergyDepositRestrictedY->Fill( DepozytPomocniczy );
                                        }
                                        if(PomicniczyTriggerTime > -40 && DepozytPomocniczy > 200)
                                        {
//cout<<"Y Time "<<PomicniczyTriggerTime<<" Numer Z "<<RealPeakNumber<<" Numer X "<<MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]<<" Energia "<<DepozytPomocniczy<<endl;
                                        }
                                        if(MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] == RealPeakNumberY[0])
                                        {
                                            WierdTestY[0][WierdLicznikY[0]][0]=PomicniczyTriggerTime;
                                            WierdTestY[0][WierdLicznikY[0]][1]=DepozytPomocniczy;
                                            WierdLicznikY[0]++;
                                        }
                                        if(MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] != RealPeakNumberY[0])
                                        {
                                            CrosstalkEnergyDepositY->Fill( DepozytPomocniczy );
                                            HistogramCrosstalkDistanceY->Fill(CrosstalkDistance);
                                            if(RealPeakEnergyResult[0]>1)
                                            {
                                                CrosstalkEnergyDepositPercentageY->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[0] );
                                            }
                                         
                                            EnergyTrigTimeCrosstalkY->Fill(PomicniczyTriggerTime, DepozytPomocniczy);
                                            EnergyTrigTimeY->Fill(PomicniczyTriggerTime, DepozytPomocniczy);
                                            if(CrosstalkDistance==1 || CrosstalkDistance==-1)
                                            {
                                                CrosstalkEnergyDepositOneCubeY->Fill( DepozytPomocniczy );
                                                if(RealPeakEnergyResult[0]>1)
                                                {
                                                    CrosstalkEnergyDepositPercentageOneCubeY->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[0] );
                                                }
                                            }
                                            if(CrosstalkDistance==2 || CrosstalkDistance==-2)
                                            {
                                                CrosstalkEnergyDepositTwoCubesY->Fill( DepozytPomocniczy );
                                                CrosstalkEnergyDepositPercentageTwoCubesY->Fill( DepozytPomocniczy );
                                            }
                                            if(CrosstalkDistance>0)
                                            {
                                                CrossEventTypeY[0][CrosstalkDistance+8]=1;
                                            }
                                            if(CrosstalkDistance<0)
                                            {
                                                CrossEventTypeY[0][CrosstalkDistance+8]=1;
                                            }
                                            cutgCut=cutgTimeEnergy->IsInside(PomicniczyTriggerTime, DepozytPomocniczy);
                                            if(cutgCut==0)
                                            {
                                                EnergyTrigTimeCUTGY->Fill(PomicniczyTriggerTime, DepozytPomocniczy );
                                                CrosstalkEnergyDepositCUTGY->Fill( DepozytPomocniczy );
                                                HistogramCrosstalkDistanceCUTGY->Fill( CrosstalkDistance );
                                                if(RealPeakEnergyResult[0]>1)
                                                {
                                                    CrosstalkEnergyDepositPercentageCUTGY->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[0] );
                                                }
                                                if(CrosstalkDistance==1 || CrosstalkDistance==-1)
                                                {
                                                    CrosstalkEnergyDepositOneCubeCUTGY->Fill(DepozytPomocniczy);
                                                }
                                                if(CrosstalkDistance==2 || CrosstalkDistance==-2)
                                                {
                                                    CrosstalkEnergyDepositTwoCubesCUTGY->Fill(DepozytPomocniczy);
                                                }
                                                
                                            }
                                        }
                                        if(MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] != RealPeakNumberY[0] && DepozytPomocniczy > 50)
                                        {
                                         HistogramCrosstalkDistanceEnergyHigherThanY->Fill( CrosstalkDistance );
                                        }
                                        if(DepozytPomocniczy > 1)
                                        {
                                            HistogramCrosstalkDistanceCutY->Fill( CrosstalkDistance );
                                        }
                                    }
                                    if ( PomocniczyNumerKostki == RealPeakNumber-1 && RealPeakEnergyY[1]>40 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000)// zmiana 0 and 10000, one cube backward
                                    {
                                        CrosstalkDistance = MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] - RealPeakNumberY[1];
                                        if(MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] != RealPeakNumberY[1])
                                        {
                                            CrosstalkEnergyDepositMinus1Y->Fill( DepozytPomocniczy );
                                            HistogramCrosstalkDistanceMinus1Y->Fill(CrosstalkDistance);
                                            EnergyTrigTimeMinus1Y->Fill(PomicniczyTriggerTime, DepozytPomocniczy);
                                            if(CrosstalkDistance==1 || CrosstalkDistance==-1)
                                            {
                                                CrosstalkEnergyDepositMinus1OneCubeY->Fill( DepozytPomocniczy );
                                                if(RealPeakEnergyResult[1]>1)
                                                {
                                                    CrosstalkEnergyPercentageMinus1OneCubeY->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[1] );
                                                }
                                            }
                                            if(CrosstalkDistance==2 || CrosstalkDistance==-2)
                                            {
                                                CrosstalkEnergyDepositMinus1TwoCubesY->Fill( DepozytPomocniczy );
                                                if(RealPeakEnergyResult[1]>1)
                                                {
                                                    CrosstalkEnergyPercentageMinus1TwoCubesY->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[1] );
                                                }
                                            }
                                            if(RealPeakEnergyResult[1]>1)
                                            {
                                                CrosstalkEnergyPercentageMinus1Y->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[1] );
                                            }
                                            if(CrosstalkDistance>0)
                                            {
                                                CrossEventTypeY[1][CrosstalkDistance+8]=1;
                                            }
                                            if(CrosstalkDistance<0)
                                            {
                                                CrossEventTypeY[1][CrosstalkDistance+8]=1;
                                            }
                                            cutgCut=cutgTimeEnergy->IsInside(PomicniczyTriggerTime, DepozytPomocniczy);
                                            if(cutgCut==0)
                                            {
                                                CrosstalkEnergyDepositMinus1CUTGY->Fill( DepozytPomocniczy );
                                                HistogramCrosstalkDistanceMinus1CUTGY->Fill( CrosstalkDistance );
                                                if(RealPeakEnergyResult[1]>1)
                                                {
                                                    CrosstalkEnergyPercentageMinus1CUTGY->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[1] );
                                                }
                                                if(CrosstalkDistance==1 || CrosstalkDistance==-1)
                                                {
                                                    CrosstalkEnergyDepositMinus1OneCubeCUTGY->Fill(DepozytPomocniczy);
                                                }
                                                if(CrosstalkDistance==2 || CrosstalkDistance==-2)
                                                {
                                                    CrosstalkEnergyDepositMinus1TwoCubesCUTGY->Fill(DepozytPomocniczy);
                                                }
                                            }
                                        }
                                        if(MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] == RealPeakNumberY[1])
                                        {
                                            WierdTestY[1][WierdLicznikY[1]][0]=PomicniczyTriggerTime;
                                            WierdTestY[1][WierdLicznikY[1]][1]=DepozytPomocniczy;                                     
                                            WierdLicznikY[1]++;
                                        }
                                    }
                                    if ( PomocniczyNumerKostki == RealPeakNumber-15 && RealPeakEnergyY[2]>40 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000 && RealPeakNumber>15)// zmiana 0 and 10000, Middle of detector
                                    {
                                        CrosstalkDistance = MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] - RealPeakNumberY[2];
                                        if(MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] != RealPeakNumberY[2])
                                        {
                                            CrosstalkEnergyDepositMiddleY->Fill( DepozytPomocniczy );
                                            HistogramCrosstalkDistanceMiddleY->Fill(CrosstalkDistance);
                                            EnergyTrigTimeMiddleY->Fill(PomicniczyTriggerTime, DepozytPomocniczy);
                                            if(CrosstalkDistance==1 || CrosstalkDistance==-1)
                                            {
                                                CrosstalkEnergyDepositMiddleOneCubeY->Fill( DepozytPomocniczy );
                                                if(RealPeakEnergyResult[2]>1)
                                                {
                                                    CrosstalkEnergyPercentageMiddleOneCubeY->Fill(100*DepozytPomocniczy/RealPeakEnergyResult[2]);
                                                }
                                            }
                                            if(CrosstalkDistance==2 || CrosstalkDistance==-2)
                                            {
                                                CrosstalkEnergyDepositMiddleTwoCubesY->Fill( DepozytPomocniczy );
                                                if(RealPeakEnergyResult[2]>1)
                                                {
                                                    CrosstalkEnergyPercentageMiddleTwoCubesY->Fill(100*DepozytPomocniczy/RealPeakEnergyResult[2]);
                                                }
                                            }
                                            if(RealPeakEnergyResult[2]>1)
                                            {
                                                CrosstalkEnergyPercentageMiddleY->Fill(100*DepozytPomocniczy/RealPeakEnergyResult[2]);
                                            }
                                            if(CrosstalkDistance>0)
                                            {
                                                CrossEventTypeY[2][CrosstalkDistance+8]=1;
                                            }
                                            if(CrosstalkDistance<0)
                                            {
                                                CrossEventTypeY[2][CrosstalkDistance+8]=1;
                                            }
                                            cutgCut=cutgTimeEnergy->IsInside(PomicniczyTriggerTime, DepozytPomocniczy);
                                            if(cutgCut==0)
                                            {
                                                CrosstalkEnergyDepositMiddleCUTGY->Fill( DepozytPomocniczy );
                                                HistogramCrosstalkDistanceMiddleCUTGY->Fill( CrosstalkDistance );
                                                if(RealPeakEnergyResult[2]>1)
                                                {
                                                    CrosstalkEnergyPercentageMiddleCUTGY->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[2] );
                                                }
                                                if(CrosstalkDistance==1 || CrosstalkDistance==-1)
                                                {
                                                    CrosstalkEnergyDepositMiddleOneCubeCUTGY->Fill(DepozytPomocniczy);
                                                }
                                                if(CrosstalkDistance==2 || CrosstalkDistance==-2)
                                                {
                                                    CrosstalkEnergyDepositMiddleTwoCubesCUTGY->Fill(DepozytPomocniczy);
                                                }
                                            }
                                        }
                                        if(MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] == RealPeakNumberY[2])
                                        {
                                            WierdTestY[2][WierdLicznikY[2]][0]=PomicniczyTriggerTime;
                                            WierdTestY[2][WierdLicznikY[2]][1]=DepozytPomocniczy;
                                            WierdLicznikY[2]++;
                                        }
                                    }
                                }
                                else //Plaszczyzna XZ
                                {
                                    PomocniczyNumerKostki = MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)];
                                    PomicniczyTriggerTime=FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime;
                                    DepozytPomocniczy=FEB[FEBs[i]].hitCharge_pe->at(check);
                                    if( PomocniczyNumerKostki == RealPeakNumber && RealPeakEnergyX[0]>40 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000) //zmiana 0 and 10000
                                    {
                                        CrosstalkDistance = MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] - RealPeakNumberX[0];
                                        if( abs(CrosstalkDistance)==2 || abs(CrosstalkDistance)==1)
                                        {
                                             CrosstalkEnergyDepositRestrictedX->Fill( DepozytPomocniczy );
                                        }
                                        if(PomicniczyTriggerTime > -40 && DepozytPomocniczy > 200)
                                        {
//cout<<"X Time "<<PomicniczyTriggerTime<<" Numer Z "<<RealPeakNumber<<" Numer X "<<MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]<<" Energia "<<DepozytPomocniczy<<endl;
                                        }
                                        if(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] == RealPeakNumberX[0])
                                        {
                                            WierdTestX[0][WierdLicznikX[0]][0]=PomicniczyTriggerTime;
                                            WierdTestX[0][WierdLicznikX[0]][1]=DepozytPomocniczy;
                                            WierdLicznikX[0]++;
                                        }
                                        if(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] != RealPeakNumberX[0])
                                        {
                                            CrosstalkEnergyDepositX->Fill( DepozytPomocniczy );
                                            HistogramCrosstalkDistanceX->Fill(CrosstalkDistance);
                                            if(RealPeakEnergyResult[0]>1)
                                            {
                                                CrosstalkEnergyDepositPercentageX->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[0] );
                                            }
                                            
                                            EnergyTrigTimeCrosstalkX->Fill(PomicniczyTriggerTime, DepozytPomocniczy);
                                            EnergyTrigTimeX->Fill(PomicniczyTriggerTime, DepozytPomocniczy);
                                            if(CrosstalkDistance==1 || CrosstalkDistance==-1)
                                            {
                                                CrosstalkEnergyDepositOneCubeX->Fill( DepozytPomocniczy );
                                                if(RealPeakEnergyResult[0]>1)
                                                {
                                                    CrosstalkEnergyDepositPercentageOneCubeX->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[0] );
                                                }
                                            }
                                            if(CrosstalkDistance==2 || CrosstalkDistance==-2)
                                            {
                                                CrosstalkEnergyDepositTwoCubesX->Fill( DepozytPomocniczy );
                                                if(RealPeakEnergyResult[0]>1)
                                                {
                                                    CrosstalkEnergyDepositPercentageTwoCubesX->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[0] );
                                                }
                                            }
                                            if(CrosstalkDistance==2 && CrosstalkFirstCubeValue[0][1]>1)
                                            {
                                                CrosstalkEnergyDepositPercentageSecondCubeNewX->Fill(100*DepozytPomocniczy/CrosstalkFirstCubeValue[0][1]);
                                            }
                                            if(CrosstalkDistance==-2 && CrosstalkFirstCubeValue[0][0]>1)
                                            {
                                                CrosstalkEnergyDepositPercentageSecondCubeNewX->Fill(100*DepozytPomocniczy/CrosstalkFirstCubeValue[0][0]);
                                            }
                                            if(CrosstalkDistance>0)
                                            {
                                                CrossEventTypeX[0][CrosstalkDistance+24]=1;
                                            }
                                            if(CrosstalkDistance<0)
                                            {
                                                CrossEventTypeX[0][CrosstalkDistance+24]=1;
                                            }
                                            cutgCut=cutgTimeEnergy->IsInside(PomicniczyTriggerTime,DepozytPomocniczy);
                                            if(cutgCut==0)
                                            {
                                                EnergyTrigTimeCUTGX->Fill(PomicniczyTriggerTime, DepozytPomocniczy);
                                                CrosstalkEnergyDepositCUTGX->Fill(DepozytPomocniczy);
                                                HistogramCrosstalkDistanceCUTGX->Fill(CrosstalkDistance);
                                                if(RealPeakEnergyResult[0]>1)
                                                {
                                                    CrosstalkEnergyDepositPercentageCUTGX->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[0] );
                                                }
                                                if(CrosstalkDistance==1 || CrosstalkDistance==-1)
                                                {
                                                    CrosstalkEnergyDepositOneCubeCUTGX->Fill(DepozytPomocniczy);
                                                }
                                                if(CrosstalkDistance==2 || CrosstalkDistance==-2)
                                                {
                                                    CrosstalkEnergyDepositTwoCubesCUTGX->Fill(DepozytPomocniczy);
                                                }
                                            }
                                        }
                                        if(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] != RealPeakNumberX[0] && DepozytPomocniczy>50)
                                        {
                                            HistogramCrosstalkDistanceEnergyHigherThanX->Fill( CrosstalkDistance );
                                        }
                                        if(DepozytPomocniczy>1)
                                        {
                                            HistogramCrosstalkDistanceCutX->Fill( CrosstalkDistance );
                                        }
                                    }
                                    if( PomocniczyNumerKostki == RealPeakNumber-1 && RealPeakEnergyX[1]>40 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000) //zmiana 0 and 10000, one cube backward
                                    {
                                        CrosstalkDistance = MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] - RealPeakNumberX[1];
                                        
                                        if(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] != RealPeakNumberX[1])
                                        {
                                            CrosstalkEnergyDepositMinus1X->Fill( DepozytPomocniczy );
                                            HistogramCrosstalkDistanceMinus1X->Fill(CrosstalkDistance);
                                            EnergyTrigTimeMinus1X->Fill(PomicniczyTriggerTime, DepozytPomocniczy);
                                            if(CrosstalkDistance==1 || CrosstalkDistance==-1)
                                            {
                                                CrosstalkEnergyDepositMinus1OneCubeX->Fill( DepozytPomocniczy );
                                                if(RealPeakEnergyResult[1]>1)
                                                {
                                                    CrosstalkEnergyPercentageMinus1OneCubeX->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[1] );
                                                }
                                            }
                                            if(CrosstalkDistance==2 || CrosstalkDistance==-2)
                                            {
                                                CrosstalkEnergyDepositMinus1TwoCubesX->Fill( DepozytPomocniczy );
                                                if(RealPeakEnergyResult[1]>1)
                                                {
                                                    CrosstalkEnergyPercentageMinus1TwoCubesX->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[1] );
                                                }
                                            }
                                            if(CrosstalkDistance==2 && CrosstalkFirstCubeValue[1][1]>1)
                                            {
                                                CrosstalkEnergyDepositPercentageMinus1SecondCubeNewX->Fill(100*DepozytPomocniczy/CrosstalkFirstCubeValue[1][1]);
                                            }
                                            if(CrosstalkDistance==-2 && CrosstalkFirstCubeValue[1][0]>1)
                                            {
                                                CrosstalkEnergyDepositPercentageMinus1SecondCubeNewX->Fill(100*DepozytPomocniczy/CrosstalkFirstCubeValue[1][0]);
                                            }
                                            if(RealPeakEnergyResult[1]>1)
                                            {
                                                CrosstalkEnergyPercentageMinus1X->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[1] );
                                            }
                                            if(CrosstalkDistance>0)
                                            {
                                                CrossEventTypeX[1][CrosstalkDistance+24]=1;
                                            }
                                            if(CrosstalkDistance<0)
                                            {
                                                CrossEventTypeX[1][CrosstalkDistance+24]=1;
                                            }
                                            cutgCut=cutgTimeEnergy->IsInside(PomicniczyTriggerTime,DepozytPomocniczy);
                                            if(cutgCut==0)
                                            {
                                                CrosstalkEnergyDepositMinus1CUTGX->Fill(DepozytPomocniczy);
                                                HistogramCrosstalkDistanceMinus1CUTGX->Fill(CrosstalkDistance);
                                                if(RealPeakEnergyResult[1]>1)
                                                {
                                                    CrosstalkEnergyPercentageMinus1CUTGX->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[1] );
                                                }
                                                if(CrosstalkDistance==1 || CrosstalkDistance==-1)
                                                {
                                                    CrosstalkEnergyDepositMinus1OneCubeCUTGX->Fill(DepozytPomocniczy);
                                                }
                                                if(CrosstalkDistance==2 || CrosstalkDistance==-2)
                                                {
                                                    CrosstalkEnergyDepositMinus1TwoCubesCUTGX->Fill(DepozytPomocniczy);
                                                }
                                            }
                                        }
                                        if( MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] == RealPeakNumberX[1] )
                                        {
                                            WierdTestX[1][WierdLicznikX[1]][0]=PomicniczyTriggerTime;
                                            WierdTestX[1][WierdLicznikX[1]][1]=DepozytPomocniczy;
                                            WierdLicznikX[1]++;
                                        }
                                    }
                                    if( PomocniczyNumerKostki == RealPeakNumber-15 && RealPeakEnergyX[2]>40 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000 && RealPeakNumber>15) //zmiana 0 and 10000, Middle of detector
                                    {
                                        CrosstalkDistance = MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] - RealPeakNumberX[2];
                                        if(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] != RealPeakNumberX[2])
                                        {
                                            CrosstalkEnergyDepositMiddleX->Fill( DepozytPomocniczy );
                                            HistogramCrosstalkDistanceMiddleX->Fill(CrosstalkDistance);
                                            EnergyTrigTimeMiddleX->Fill(PomicniczyTriggerTime, DepozytPomocniczy);
                                            if(CrosstalkDistance==1 || CrosstalkDistance==-1)
                                            {
                                                CrosstalkEnergyDepositMiddleOneCubeX->Fill( DepozytPomocniczy );
                                                if(RealPeakEnergyResult[2]>1)
                                                {
                                                    CrosstalkEnergyPercentageMiddleOneCubeX->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[2] );
                                                }
                                            }
                                            if(CrosstalkDistance==2 || CrosstalkDistance==-2)
                                            {
                                                CrosstalkEnergyDepositMiddleTwoCubesX->Fill( DepozytPomocniczy );
                                                if(RealPeakEnergyResult[2]>1)
                                                {
                                                    CrosstalkEnergyPercentageMiddleTwoCubesX->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[2] );
                                                }
                                            }
                                            if(CrosstalkDistance==2 && CrosstalkFirstCubeValue[2][1]>1)
                                            {
                                                CrosstalkEnergyDepositPercentageMiddleSecondCubeNewX->Fill(100*DepozytPomocniczy/CrosstalkFirstCubeValue[2][1]);
                                            }
                                            if(CrosstalkDistance==-2 && CrosstalkFirstCubeValue[2][0]>1)
                                            {
                                                CrosstalkEnergyDepositPercentageMiddleSecondCubeNewX->Fill(100*DepozytPomocniczy/CrosstalkFirstCubeValue[2][0]);
                                            }
                                            if(RealPeakEnergyResult[2]>1)
                                            {
                                                CrosstalkEnergyPercentageMiddleX->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[2] );
                                            }
                                            if(CrosstalkDistance>0)
                                            {
                                                CrossEventTypeX[2][CrosstalkDistance+24]=1;
                                            }
                                            if(CrosstalkDistance<0)
                                            {
                                                CrossEventTypeX[2][CrosstalkDistance+24]=1;
                                            }
                                            cutgCut=cutgTimeEnergy->IsInside(PomicniczyTriggerTime,DepozytPomocniczy);
                                            if(cutgCut==0)
                                            {
                                                CrosstalkEnergyDepositMiddleCUTGX->Fill(DepozytPomocniczy);
                                                HistogramCrosstalkDistanceMiddleCUTGX->Fill(CrosstalkDistance);
                                                if(RealPeakEnergyResult[2]>1)
                                                {
                                                    CrosstalkEnergyPercentageMiddleCUTGX->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[2] );
                                                }
                                                if(CrosstalkDistance == 1 || CrosstalkDistance == -1)
                                                {
                                                    CrosstalkEnergyDepositMiddleOneCubeCUTGX->Fill(DepozytPomocniczy);
                                                }
                                                if(CrosstalkDistance == 2 || CrosstalkDistance == -2)
                                                {
                                                    CrosstalkEnergyDepositMiddleTwoCubesCUTGX->Fill(DepozytPomocniczy);
                                                }
                                            }
                                        }
                                        if( MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] == RealPeakNumberX[2] )
                                        {
                                            WierdTestX[2][WierdLicznikX[2]][0]=PomicniczyTriggerTime;
                                            WierdTestX[2][WierdLicznikX[2]][1]=DepozytPomocniczy;
                                            WierdLicznikX[2]++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                } 
                for(int ib=0; ib<48; ib++)
                {
                    if(CrossEventTypeX[0][ib]==1)
                    {
                        CrossEventTypeCounterX[0]+=CrossEventTypeX[0][ib];
                    }
                    CrossEventTypeX[0][ib]=0;
                }
                for(int ib=0; ib<16; ib++)
                {
                    if(CrossEventTypeY[0][ib]==1)
                    {
                        CrossEventTypeCounterY[0]+=CrossEventTypeY[0][ib];
                    }
                    CrossEventTypeY[0][ib]=0;
                }
                if(energyDepZ[RealPeakNumber-1]>0)
                {
                    for(int ib=0; ib<48; ib++)
                    {
                        if(CrossEventTypeX[1][ib]==1)
                        {
                            CrossEventTypeCounterX[1]+=CrossEventTypeX[1][ib];
                        }
                        CrossEventTypeX[1][ib]=0;
                    }
                    for(int ib=0; ib<16; ib++)
                    {
                        if(CrossEventTypeY[1][ib]==1)
                        {  
                            CrossEventTypeCounterY[1]+=CrossEventTypeY[1][ib];
                        }
                        CrossEventTypeY[1][ib]=0;
                    }
                }
                if(energyDepZ[RealPeakNumber-15]>0 && RealPeakNumber>15)
                {
                    for(int ib=0; ib<48; ib++)
                    {
                        if(CrossEventTypeX[2][ib]==1)
                        {
                            CrossEventTypeCounterX[2]+=CrossEventTypeX[2][ib];
                        }
                        CrossEventTypeX[2][ib]=0;
                    }
                    for(int ib=0; ib<16; ib++)
                    {
                        if(CrossEventTypeY[2][ib]==1)
                        {
                            CrossEventTypeCounterY[2]+=CrossEventTypeY[2][ib];
                        }
                        CrossEventTypeY[2][ib]=0;
                    }
                }
            //////
                if(RealPeakEnergyX[0]>40)
                {
                    HistogramCrosstalkDistanceTypeX->Fill(CrossEventTypeCounterX[0]);
                }
                if(RealPeakEnergyY[0]>40)
                {
                    HistogramCrosstalkDistanceTypeY->Fill(CrossEventTypeCounterY[0]);
                }
                if(energyDepZ[RealPeakNumber-1]>0)
                {
                    if(RealPeakEnergyResult[1]>40)
                    {
                        HistogramRealPeakEnergyDepositMinus1->Fill(RealPeakEnergyResult[1]);
                    }
                    if(RealPeakEnergyX[1]>40)
                    {
                        HistogramCrosstalkDistanceTypeMinus1X->Fill(CrossEventTypeCounterX[1]);
                    }
                    if(RealPeakEnergyY[1]>40)
                    {
                        HistogramCrosstalkDistanceTypeMinus1Y->Fill(CrossEventTypeCounterY[1]);
                    }
                }
                if(energyDepZ[RealPeakNumber-15]>0 && RealPeakNumber>15)
                {
                    if(RealPeakEnergyResult[2]>40)
                    {
                        HistogramRealPeakEnergyDepositMiddle->Fill(RealPeakEnergyResult[2]);
                    }
                    if(RealPeakEnergyX[2]>40)
                    {
                        HistogramCrosstalkDistanceTypeMiddleX->Fill(CrossEventTypeCounterX[2]);
                    }
                    if(RealPeakEnergyY[2]>40)
                    {
                        HistogramCrosstalkDistanceTypeMiddleY->Fill(CrossEventTypeCounterY[2]);
                    }
                }

                for(int hk=0; hk<3; hk++)
                {
                    if(WierdLicznikX[hk]==2)
                    {
                        double TemporaryEnergy=0;
                        TemporaryEnergy=WierdTestX[hk][0][1];
                        if(WierdTestX[hk][1][1]>TemporaryEnergy)
                        {
                            TemporaryEnergy=WierdTestX[hk][1][1];
                        }
                        double TemporaryTime=0;
                        TemporaryTime=WierdTestX[hk][0][0];
                        if(TemporaryTime>WierdTestX[hk][1][0])
                        {
                            TemporaryTime=WierdTestX[hk][1][0];
                        }
                        if(hk==0 && RealPeakEnergyX[0]>40)
                        {
                            EnergyTrigTimeTestX->Fill(WierdTestX[0][0][0],WierdTestX[0][0][1]);
                            EnergyTrigTimeTestX->Fill(WierdTestX[0][1][0],WierdTestX[0][1][1]);
                        
                            EnergyTrigTimeSignalX->Fill(TemporaryTime, TemporaryEnergy);
                            EnergyTrigTimeX->Fill(TemporaryTime, TemporaryEnergy);
                            EnergyTrigTimeTestUpgradeX->Fill(TemporaryTime, TemporaryEnergy);
                        }
                        if(hk==1 && RealPeakEnergyX[1]>40)
                        {
                            EnergyTrigTimeMinus1X->Fill(TemporaryTime, TemporaryEnergy);
                        }
                        if(hk==2 && RealPeakNumber>15 && RealPeakEnergyX[2]>40)
                        {
                            EnergyTrigTimeMiddleX->Fill(TemporaryTime, TemporaryEnergy);
                        }
                    }
                    if(WierdLicznikY[hk]==2)
                    {
                        double TemporaryEnergy=0;
                        TemporaryEnergy=WierdTestY[hk][0][1];
                        if(WierdTestY[hk][1][1]>TemporaryEnergy)
                        {
                            TemporaryEnergy=WierdTestY[hk][1][1];
                        }
                        double TemporaryTime=0;
                        TemporaryTime=WierdTestY[hk][0][0];
                        if(TemporaryTime>WierdTestY[hk][1][0])
                        {
                            TemporaryTime=WierdTestY[hk][1][0];
                        }
                        if(hk==0 && RealPeakEnergyY[1]>40)
                        {
                            EnergyTrigTimeTestY->Fill(WierdTestY[0][0][0],WierdTestY[0][0][1]);
                            EnergyTrigTimeTestY->Fill(WierdTestY[0][1][0],WierdTestY[0][1][1]);
                        
                            EnergyTrigTimeSignalY->Fill(TemporaryTime, TemporaryEnergy);
                            EnergyTrigTimeY->Fill(TemporaryTime, TemporaryEnergy);
                            EnergyTrigTimeTestUpgradeY->Fill(TemporaryTime, TemporaryEnergy);
                        }
                        if(hk==1 && RealPeakEnergyY[1]>40)
                        {
                            EnergyTrigTimeMinus1Y->Fill(TemporaryTime, TemporaryEnergy);
                        }
                        if(hk==2 && RealPeakNumber>15 && RealPeakEnergyY[2]>40)
                        {
                           EnergyTrigTimeMiddleY->Fill(TemporaryTime, TemporaryEnergy);
                        }
                    }
                }
                if(WierdLicznikX[0]==1)
                {
                    EnergyTrigTimeSignalX->Fill(WierdTestX[0][0][0], WierdTestX[0][0][1]);
                    EnergyTrigTimeX->Fill(WierdTestX[0][0][0], WierdTestX[0][0][1]);
                    if(WierdTestX[0][0][1]<40)
                    {
                        EnergyTrigTimeTestLowX->Fill(WierdTestX[0][0][0],WierdTestX[0][0][1]); 
                    }
                }
                if(WierdLicznikX[1]==1 && RealPeakEnergyX[1]>0)
                {
                    EnergyTrigTimeMinus1X->Fill(WierdTestX[1][0][0], WierdTestX[1][0][1]);
                }
                if(WierdLicznikX[2]==1 && RealPeakNumber>15 && RealPeakEnergyX[2]>0)
                {
                    EnergyTrigTimeMiddleX->Fill(WierdTestX[2][0][0], WierdTestX[2][0][1]);
                }
                if(WierdLicznikY[0]==1)
                {
                    EnergyTrigTimeSignalY->Fill(WierdTestY[0][0][0], WierdTestY[0][0][1]);
                    EnergyTrigTimeY->Fill(WierdTestY[0][0][0], WierdTestY[0][0][1]);
                    if(WierdTestY[0][0][1]<40)
                    {
                        EnergyTrigTimeTestLowY->Fill(WierdTestY[0][0][0],WierdTestY[0][0][1]);
                    }
                }
                if(WierdLicznikY[1]==1 && RealPeakEnergyY[1]>0)
                {
                   EnergyTrigTimeMinus1Y->Fill(WierdTestY[1][0][0], WierdTestY[1][0][1]);
                }
                if(WierdLicznikY[2]==1 && RealPeakNumber>15 && RealPeakEnergyY[2]>0)
                {
                    EnergyTrigTimeMiddleY->Fill(WierdTestY[2][0][0], WierdTestY[2][0][1]);
                }
                
                StoppingPointLocation->Fill(RealPeakNumber);
                HistogramHighestEnergyDeposit->Fill(PeakEnergy);
                HistogramRealPeakEnergyDeposit->Fill(RealPeakEnergyResult[0]);
                
                cout <<"licznik "<<licznik<<" sigma " << sigma <<" RealPeakNumber "<<RealPeakNumber<<endl;
                cout <<"licznik "<<licznik<<" RealPeakEnergyX "<< RealPeakEnergyX[0]<<" RealPeakEnergyY "<<RealPeakEnergyY[0]<<endl;
                cout <<"licznik "<<licznik<<" RealPeakNumberX "<< RealPeakNumberX[0]<<" RealPeakNumberY "<<RealPeakNumberY[0]<<endl;
                if(energyDepZ[RealPeakNumber-15]>0 && RealPeakNumber>15)
                {
                    cout <<"licznik "<<licznik<<" RealPeakNumber-15: "<<RealPeakNumber-15<<" RealPeakEnergy-15: "<<energyDepZ[RealPeakNumber-15]<<endl;
                }
                licznik++;
                
                DisplayCanvas->Clear();    
                CrossEnergyCanvas->Clear();
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
    
    CrosstalkEnergyDepositOneCubeX->Write();
    CrosstalkEnergyDepositOneCubeY->Write();
    
    CrosstalkEnergyDepositTwoCubesX->Write();
    CrosstalkEnergyDepositTwoCubesY->Write();
    
    CrosstalkEnergyDepositPercentageX->Write();
    CrosstalkEnergyDepositPercentageY->Write();
    
    CrosstalkEnergyDepositPercentageOneCubeX->Write();
    CrosstalkEnergyDepositPercentageOneCubeY->Write();
    
    CrosstalkEnergyDepositPercentageTwoCubesX->Write();
    CrosstalkEnergyDepositPercentageTwoCubesY->Write(); 
    
    CrosstalkEnergyDepositPercentageSecondCubeNewX->Write();
    
    CrosstalkEnergyDepositCUTGX->Write();
    CrosstalkEnergyDepositCUTGY->Write();
    
    CrosstalkEnergyDepositOneCubeCUTGX->Write();
    CrosstalkEnergyDepositOneCubeCUTGY->Write();
    
    CrosstalkEnergyDepositTwoCubesCUTGX->Write();
    CrosstalkEnergyDepositTwoCubesCUTGY->Write();
    
    CrosstalkEnergyDepositRestrictedX->Write();
    CrosstalkEnergyDepositRestrictedY->Write();

    HistogramCrosstalkDistanceX->Write();
    HistogramCrosstalkDistanceY->Write();
    
    HistogramCrosstalkDistanceEnergyHigherThanX->Write();
    HistogramCrosstalkDistanceEnergyHigherThanY->Write();
    
    HistogramCrosstalkDistanceCutX->Write();
    HistogramCrosstalkDistanceCutY->Write();
    
    HistogramCrosstalkDistanceCUTGX->Write();
    HistogramCrosstalkDistanceCUTGY->Write();
    
    CrosstalkEnergyDepositPercentageCUTGX->Write();
    CrosstalkEnergyDepositPercentageCUTGY->Write();
    
    HistogramCrosstalkDistanceTypeX->Write();
    HistogramCrosstalkDistanceTypeY->Write();
    
    EnergyTrigTimeX->Write();
    EnergyTrigTimeY->Write();
    
    EnergyTrigTimeCrosstalkX->Write();
    EnergyTrigTimeCrosstalkY->Write();
    
    EnergyTrigTimeSignalX->Write();
    EnergyTrigTimeSignalY->Write();
    
    EnergyTrigTimeCUTGX->Write();
    EnergyTrigTimeCUTGY->Write();
    
    CrosstalkEnergyDepositMinus1X->Write();
    CrosstalkEnergyDepositMinus1Y->Write();
    
    CrosstalkEnergyDepositMinus1OneCubeX->Write();
    CrosstalkEnergyDepositMinus1OneCubeY->Write();
    
    CrosstalkEnergyDepositMinus1TwoCubesX->Write();
    CrosstalkEnergyDepositMinus1TwoCubesY->Write();
    
    CrosstalkEnergyPercentageMinus1X->Write();
    CrosstalkEnergyPercentageMinus1Y->Write();
    
    CrosstalkEnergyPercentageMinus1OneCubeX->Write();
    CrosstalkEnergyPercentageMinus1OneCubeY->Write();
    
    CrosstalkEnergyPercentageMinus1TwoCubesX->Write();
    CrosstalkEnergyPercentageMinus1TwoCubesY->Write();
    
    CrosstalkEnergyDepositPercentageMinus1SecondCubeNewX->Write();
    
    HistogramCrosstalkDistanceMinus1X->Write();
    HistogramCrosstalkDistanceMinus1Y->Write();
    
    HistogramRealPeakEnergyDepositMinus1->Write();
    
    HistogramCrosstalkDistanceTypeMinus1X->Write();
    HistogramCrosstalkDistanceTypeMinus1Y->Write();
    
    CrosstalkEnergyDepositMinus1CUTGX->Write();
    CrosstalkEnergyDepositMinus1CUTGY->Write();
    
    CrosstalkEnergyDepositMinus1OneCubeCUTGX->Write();
    CrosstalkEnergyDepositMinus1OneCubeCUTGY->Write();
    
    CrosstalkEnergyDepositMinus1TwoCubesCUTGX->Write();
    CrosstalkEnergyDepositMinus1TwoCubesCUTGY->Write();
    
    CrosstalkEnergyPercentageMinus1CUTGX->Write();
    CrosstalkEnergyPercentageMinus1CUTGY->Write();
    
    HistogramCrosstalkDistanceMinus1CUTGX->Write();
    HistogramCrosstalkDistanceMinus1CUTGY->Write();
    
    EnergyTrigTimeMinus1X->Write();
    EnergyTrigTimeMinus1Y->Write();
    
    CrosstalkEnergyDepositMiddleX->Write();
    CrosstalkEnergyDepositMiddleY->Write();

    CrosstalkEnergyDepositMiddleOneCubeX->Write();
    CrosstalkEnergyDepositMiddleOneCubeY->Write();
    
    CrosstalkEnergyDepositMiddleTwoCubesX->Write();
    CrosstalkEnergyDepositMiddleTwoCubesY->Write();
    
    CrosstalkEnergyPercentageMiddleX->Write();
    CrosstalkEnergyPercentageMiddleY->Write();
    
    CrosstalkEnergyPercentageMiddleOneCubeX->Write();
    CrosstalkEnergyPercentageMiddleOneCubeY->Write();
    
    CrosstalkEnergyPercentageMiddleTwoCubesX->Write();
    CrosstalkEnergyPercentageMiddleTwoCubesY->Write();
    
    CrosstalkEnergyDepositPercentageMiddleSecondCubeNewX->Write();
    
    HistogramCrosstalkDistanceMiddleX->Write();
    HistogramCrosstalkDistanceMiddleY->Write();
    
    HistogramCrosstalkDistanceTypeMiddleX->Write();
    HistogramCrosstalkDistanceTypeMiddleY->Write();
    
    CrosstalkEnergyDepositMiddleCUTGX->Write();
    CrosstalkEnergyDepositMiddleCUTGY->Write();
    
    CrosstalkEnergyDepositMiddleOneCubeCUTGX->Write();
    CrosstalkEnergyDepositMiddleOneCubeCUTGY->Write();
    
    CrosstalkEnergyDepositMiddleTwoCubesCUTGX->Write();
    CrosstalkEnergyDepositMiddleTwoCubesCUTGY->Write();
    
    CrosstalkEnergyPercentageMiddleCUTGX->Write();
    CrosstalkEnergyPercentageMiddleCUTGY->Write();
    
    HistogramCrosstalkDistanceMiddleCUTGX->Write();
    HistogramCrosstalkDistanceMiddleCUTGY->Write();
    
    HistogramRealPeakEnergyDepositMiddle->Write();
        
    EnergyTrigTimeMiddleX->Write();
    EnergyTrigTimeMiddleY->Write();
    
    EnergyTrigTimeTestX->Write();
    EnergyTrigTimeTestY->Write();
    
    EnergyTrigTimeTestUpgradeX->Write();
    EnergyTrigTimeTestUpgradeY->Write();
    
    EnergyTrigTimeTestLowX->Write();
    EnergyTrigTimeTestLowY->Write();
    
    wfile.Close();
    FileInput->Close();
    return 0;
}
