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
    
    TH1F *CrosstalkEnergyDepositPercentageOneCubeImprovedX = new TH1F("CrosstalkEnergyDepositPercentageOneCubeImprovedX", "Crosstalk energy divided by main deposit in X plain, one cube,after correction",200,0,100);
    CrosstalkEnergyDepositPercentageOneCubeImprovedX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageOneCubeImprovedX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositPercentageOneCubeImprovedY = new TH1F("CrosstalkEnergyDepositPercentageOneCubeImprovedY", "Crosstalk energy divided by main deposit in Y plain, one cube, after correction",200,0,100);
    CrosstalkEnergyDepositPercentageOneCubeImprovedY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageOneCubeImprovedY->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositPercentageTwoCubesX = new TH1F("CrosstalkEnergyDepositPercentageTwoCubesX", "Crosstalk energy divided by main deposit in X plain,  two cubes",100,0,100);
    CrosstalkEnergyDepositPercentageTwoCubesX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageTwoCubesX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositPercentageTwoCubesY = new TH1F("CrosstalkEnergyDepositPercentageTwoCubesY", "Crosstalk energy divided by main deposit in Y plain,  one cube",100,0,100);
    CrosstalkEnergyDepositPercentageTwoCubesY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageTwoCubesY->GetXaxis()->SetTitle("Percentage %");
        
    TH1F *StoppingPointLocation = new TH1F("StoppingPointLocation", "Location of stopping point",48,0,48);
    StoppingPointLocation->GetYaxis()->SetTitle("Number of events");
    StoppingPointLocation->GetXaxis()->SetTitle("Z detector axis [cm]");

    TH1F *HistogramCrosstalkDistanceX= new TH1F("HistogramCrosstalkDistanceX", "Cube distance of energy deposit from peak X axis",10,-5,5);
    HistogramCrosstalkDistanceX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceX->GetXaxis()->SetTitle("X detector axis [cm]");
    
    TH1F *HistogramCrosstalkDistanceY = new TH1F("HistogramCrosstalkDistanceY", "Cube distance of energy deposit from peak Y axis",10,-5,5);
    HistogramCrosstalkDistanceY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceY->GetXaxis()->SetTitle("Y detector axis [cm]");
    
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
    
    TH1F *CrosstalkEnergyDepositPercentageMinus1OneCubeImprovedX = new TH1F("CrosstalkEnergyDepositPercentageMinus1OneCubeImprovedX", "Crosstalk energy divided by main deposit in X plain, one cube backward, one cube,after correction",200,0,100);
    CrosstalkEnergyDepositPercentageMinus1OneCubeImprovedX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageMinus1OneCubeImprovedX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositPercentageMinus1OneCubeImprovedY = new TH1F("CrosstalkEnergyDepositPercentageMinus1OneCubeImprovedY", "Crosstalk energy divided by main deposit in Y plain, one cube backward, one cube, after correction",200,0,100);
    CrosstalkEnergyDepositPercentageMinus1OneCubeImprovedY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageMinus1OneCubeImprovedY->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyPercentageMinus1TwoCubesX = new TH1F("CrosstalkEnergyPercentageMinus1TwoCubesX", "Crosstalk divided by main deposit in X plain, one cube backward, two cubes.",100,0,100);
    CrosstalkEnergyPercentageMinus1TwoCubesX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMinus1TwoCubesX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyPercentageMinus1TwoCubesY = new TH1F("CrosstalkEnergyPercentageMinus1TwoCubesY", "Crosstalk divided by main deposit in Y plain, one cube backward, two cubes.",100,0,100);
    CrosstalkEnergyPercentageMinus1TwoCubesY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMinus1TwoCubesY->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *HistogramCrosstalkDistanceMinus1X= new TH1F("HistogramCrosstalkDistanceMinus1X", "Cube distance of energy deposit from peak X axis, one cube backward",10,-5,5);
    HistogramCrosstalkDistanceMinus1X->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMinus1X->GetXaxis()->SetTitle("X detector axis [cm]");
    
    TH1F *HistogramCrosstalkDistanceMinus1Y = new TH1F("HistogramCrosstalkDistanceMinus1Y", "Cube distance of energy deposit from peak Y axis, one cube backward",10,-5,5);
    HistogramCrosstalkDistanceMinus1Y->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMinus1Y->GetXaxis()->SetTitle("Y detector axis [cm]");
    
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
    
    TH1F *CrosstalkEnergyDepositPercentageMiddleOneCubeImprovedX = new TH1F("CrosstalkEnergyDepositPercentageMiddleOneCubeImprovedX", "Crosstalk energy divided by main deposit in X plain, 15 cubes backward, one cube,after correction",200,0,100);
    CrosstalkEnergyDepositPercentageMiddleOneCubeImprovedX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageMiddleOneCubeImprovedX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositPercentageMiddleOneCubeImprovedY = new TH1F("CrosstalkEnergyDepositPercentageMiddleOneCubeImprovedY", "Crosstalk energy divided by main deposit in Y plain, 15 cubes backward, one cube, after correction",200,0,100);
    CrosstalkEnergyDepositPercentageMiddleOneCubeImprovedY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageMiddleOneCubeImprovedY->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyPercentageMiddleTwoCubesX = new TH1F("CrosstalkEnergyPercentageMiddleTwoCubesX", "Crosstalk energy divided by main deposit in X plain, 15 cubes away from stopping poin, two cubes.",100,0,100);
    CrosstalkEnergyPercentageMiddleTwoCubesX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMiddleTwoCubesX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyPercentageMiddleTwoCubesY = new TH1F("CrosstalkEnergyPercentageMiddleTwoCubesY", "Crosstalk energy divided by main deposit in Y plain, 15 cubes away from stopping poin, two cubes.",100,0,100);
    CrosstalkEnergyPercentageMiddleTwoCubesY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMiddleTwoCubesY->GetXaxis()->SetTitle("Percentage %"); 
    
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
    ////////TODO nowe zabawy!!!!!!!////////
    TH1F *StopXz= new TH1F("StopXz", "StopXz",100,0,2500);
    TH1F *StopXz1= new TH1F("StopXz1", "StopXz1",100,0,2500);
    TH1F *StopXz25= new TH1F("StopXz25", "StopXz25",100,0,2500);
    
    TH1F *StopYz= new TH1F("StopYz", "StopYz",100,0,2500);
    TH1F *StopYz1= new TH1F("StopYz1", "StopYz1",100,0,2500);
    TH1F *StopYz25= new TH1F("StopYz25", "StopYz25",100,0,2500);
/////
    TH1F *NewPercXz= new TH1F("NewPercXz", "NewPercXz",200,0,100);
    TH1F *NewPercXz1= new TH1F("NewPercXz1", "NewPercXz1",200,0,100);
    TH1F *NewPercXz25= new TH1F("NewPercXz25", "NewPercXz25",200,0,100);
    
    TH1F *NewPercYz= new TH1F("NewPercYz", "NewPercYz",200,0,100);
    TH1F *NewPercYz1= new TH1F("NewPercYz1", "NewPercYz1",200,0,100);
    TH1F *NewPercYz25= new TH1F("NewPercYz25", "NewPercYz25",200,0,100);
/////
    TH1F *NewPercTwoXz= new TH1F("NewPercTwoXz", "NewPercTwoXz",200,0,100);
    TH1F *NewPercTwoXz1= new TH1F("NewPercTwoXz1", "NewPercTwoXz1",200,0,100);
    TH1F *NewPercTwoXz25= new TH1F("NewPercTwoXz25", "NewPercTwoXz25",200,0,100);
////
    TH2F *Multi1Xz= new TH2F("Multi1Xz", "Multi1Xz",24,0,24, 48,0,48);
    TH2F *Multi1Xz1= new TH2F("Multi1Xz1", "Multi1Xz1",24,0,24, 48,0,48);
    TH2F *Multi1Xz25= new TH2F("Multi1Xz25", "Multi1Xz25",24,0,24, 48,0,48);
    
    TH2F *Multi2Xz= new TH2F("Multi2Xz", "Multi2Xz",24,0,24, 48,0,48);
    TH2F *Multi2Xz1= new TH2F("Multi2Xz1", "Multi2Xz1",24,0,24, 48,0,48);
    TH2F *Multi2Xz25= new TH2F("Multi2Xz25", "Multi2Xz25",24,0,24, 48,0,48);
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
    int NumberEvDis = 12000; // zmiana 10000

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
    double Pid=0;
    double DepozytPomocniczy=0;

    double CrosstalkImprovedSum[3]={};
    
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
                for (int ik = 0; ik < 8; ik++ ) //zerowanie tablic przechowujace dane, Y
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
                            Pid = FEB[12].hitsChannel->at(TOFtrigger);
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

            double RealPeakEnergyX[3]={};       //0-StoppingPoint,1-OneCubeBackward,2-MiddleOfTrack
            int RealPeakNumberX[3]={};         //0-StoppingPoint,1-OneCubeBackward,2-MiddleOfTrack

            double RealPeakEnergyY[3]={};    //0-StoppingPoint,1-OneCubeBackward,2-MiddleOfTrack
            int RealPeakNumberY[3]={};      //0-StoppingPoint,1-OneCubeBackward,2-MiddleOfTrack
            
            double RealPeakEnergyResult[3]={};
            double RealPeakEnergyResultImproved[3]={};

            int CrosstalkDistance=0;
            int PomocniczyNumerKostki=0;
            double PomicniczyTriggerTime=0;
            
            int CrossEventTypeX[3][48]={}; //Z,Z-1,Z-15||24+24
            int CrossEventTypeY[3][16]={}; //Z,Z-1,Z-15||8+8
            
            int CrossEventTypeCounterX[3]={}; //Z,Z-1,Z-15
            int CrossEventTypeCounterY[3]={}; //Z,Z-1,Z-15
            
            double WierdTestX[3][2][2]={}; //[Pozycje][deposit][time]
            double WierdTestY[3][2][2]={}; //[Pozycje][deposit][time]
            
            int WierdLicznikX[3]={};//[Pozycje]
            int WierdLicznikY[3]={};//[Pozycje]
            
            int EnergeticEventsX[3]={}; //Z,Z-1,Z-15 to eliminate particle passing two cubes at the same time 
            int EnergeticEventsY[3]={}; //Z,Z-1,Z-15 to eliminate particle passing two cubes at the same time
            
            double CrosstalkFirstCubeValueX[3][2]; //[Pozycje][0-left,1-right]
            double CrosstalkFirstCubeValueY[3][2]; //[Pozycje][0-left,1-right]
            
            double ProtonThreshold=-80; //Value to seperate protons from other hadrons (pions most likely)
            double TriggerTimeValue=0; 
            int TriggerTimerCounter=0;
            
            int SecondCrosstalkFlag=0;
  ///////////Ciecia
            bool StoppingParticle = 0; //ciecie usuwajace czastki które sie nie zatrzymaly
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
            //TODO
            /*
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
            */
            bool StopingSignature = true; //TODO TODO
            //if(RealPeakNumber>30) StopingSignature= true;
            for(int ik = 0; ik < 24; ik++ )
            {
                energyX_XZ[eventNum]->Fill(ik,energyDepX_XZ[ik]);
            }
            for(int ik = 0; ik < 8; ik++ )
            {
                energyY_YZ[eventNum]->Fill(ik,energyDepY_YZ[ik]);
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
            //Fitting neccesary to elimate garbage events
            double sigma=0;
            bool sigmaCut=0;
            if ( LargehitTimeDif == 0 && StoppingParticle==1 && PeakEnergy>250 && DiscontinuityCut==1 && TrackBeginningCut==1 && StopingSignature==1)
            {
                TF1 *EnergyFitX = new TF1("EnergyFitX", "gaus");
                energyX_XZ[eventNum]-> Fit(EnergyFitX,"q","",1 , 23);
                sigma = energyX_XZ[eventNum]->GetStdDev(); // We chose sigma to get rid of garbage

                delete EnergyFitX;
                if(sigma < 1.4) ///setting value for sigma cut //TODO
                {
                    sigmaCut=1;
                }
            }
            double sigmaY=0;
            bool sigmaCutY=0;
            
            if ( LargehitTimeDif == 0 && StoppingParticle==1 && PeakEnergy>250 && DiscontinuityCut==1 && TrackBeginningCut==1 && StopingSignature==1)
            {
                TF1 *EnergyFitY = new TF1("EnergyFitY", "gaus");
                energyY_YZ[eventNum]-> Fit(EnergyFitY,"q","",1 , 7);
                sigmaY = energyY_YZ[eventNum]->GetStdDev(); // We chose sigma to get rid of garbage

                delete EnergyFitY;
                if(sigmaY < 1.4) ///setting value for sigma cut
                {
                    sigmaCutY=1;
                }
            }
            //Selecting Proton Events
            /*bool ProtonTrigger=0;
            if(Pid==3) //0-all particles 1-Electrons 2-Muons/Pions 3-Protons || newer version Channel 0 -Electron 1-Muons/Pions Channel 3-all particles
            {
                ProtonTrigger=1;
            }*/
            bool EventNumberCut=0; //to eleminate low deposit number events
            if(event_XZ[eventNum]->GetEntries()>10)
            {
                EventNumberCut=1;
            }
            if(LargehitTimeDif == 0 && StoppingParticle==1 && PeakEnergy>250 && DiscontinuityCut==1 && TrackBeginningCut==1 && sigmaCut==1 && sigmaCutY==1 && EventNumberCut==1 && StopingSignature==1)
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
                                    }
                                    if(PomocniczyNumerKostki == RealPeakNumber-1 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000)// zmiana 0 and 10000
                                    {
                                        energyDepY_YZ_Plain[1][MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += DepozytPomocniczy;
                                    }
                                    if(PomocniczyNumerKostki == RealPeakNumber-25 && RealPeakNumber>25 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000)// zmiana 0 and 10000
                                    {
                                        energyDepY_YZ_Plain[2][MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += DepozytPomocniczy;
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
                                    }
                                    if(PomocniczyNumerKostki == RealPeakNumber-1 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000) //zmiana 0 and 10000
                                    {
                                        energyDepX_XZ_Plain[1][MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += DepozytPomocniczy;
                                    }
                                    if(PomocniczyNumerKostki == RealPeakNumber-25 && RealPeakNumber>25 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000) //zmiana 0 and 10000
                                    {
                                        energyDepX_XZ_Plain[2][MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += DepozytPomocniczy;
                                    }
                                    TriggerTimeValue+=PomicniczyTriggerTime;
                                    TriggerTimerCounter+=1;
                                }
                            }
                        }
                    }
                }
                int LoopLimit=3; //poniewaz patrzymy na 3 punkty
                if(RealPeakNumber<=25) //jesli mamy za krotki tor to nie chcemy wyjsc poza tablice
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
                        if(hk==0 && energyDepX_XZ_Plain[0][ik]>60)
                        {
                            EnergeticEventsX[0]+=1;
                        }
                        if(hk==1 && energyDepX_XZ_Plain[1][ik]>60)
                        {
                            EnergeticEventsX[1]+=1;
                        }
                        if(hk==2 && energyDepX_XZ_Plain[2][ik]>60)
                        {
                            EnergeticEventsX[2]+=1;
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
                        if(hk==0 && energyDepY_YZ_Plain[0][ik]>60)
                        {
                            EnergeticEventsY[0]+=1;
                        }
                        if(hk==1 && energyDepY_YZ_Plain[1][ik]>60)
                        {
                            EnergeticEventsY[1]+=1;
                        }
                        if(hk==2 && energyDepY_YZ_Plain[2][ik]>60)
                        {
                            EnergeticEventsY[2]+=1;
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
            if(LargehitTimeDif == 0 && StoppingParticle==1 && PeakEnergy>250 && DiscontinuityCut==1 && TrackBeginningCut==1 && BorderCutY==1 && BorderCutX && sigmaCut==1 && sigmaCutY==1 && EventNumberCut==1 && StopingSignature==1 && ProtonFlag==1 && EnergeticEventsX[0]==1 && EnergeticEventsY[0]==1 && EnergeticEventsX[1]==1 && EnergeticEventsY[1]==1)
            {   
                //Sprawdzenie wartosci stopujacego protonu potrzebna do wykresow procentowych 
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
                    CrosstalkFirstCubeValueX[ip][0]=energyDepX_XZ_Plain[ip][RealPeakNumberX[ip]-1];
                    CrosstalkFirstCubeValueX[ip][1]=energyDepX_XZ_Plain[ip][RealPeakNumberX[ip]+1];
                    CrosstalkFirstCubeValueY[ip][0]=energyDepY_YZ_Plain[RealPeakNumberY[ip]-1][ip];
                    CrosstalkFirstCubeValueY[ip][1]=energyDepY_YZ_Plain[RealPeakNumberY[ip]-1][ip];
                }
                for(int ip=0; ip<3; ip++)
                {
                    CrosstalkImprovedSum[ip]=CrosstalkFirstCubeValueX[ip][0]+CrosstalkFirstCubeValueX[ip][1]+CrosstalkFirstCubeValueY[ip][0]+CrosstalkFirstCubeValueY[ip][1];
                    RealPeakEnergyResultImproved[ip]=RealPeakEnergyResult[ip]-CrosstalkImprovedSum[ip];
                }
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
                                    if ( PomocniczyNumerKostki == RealPeakNumber && RealPeakEnergyY[0]>20 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000)// zmiana 0 and 10000
                                    {
                                        CrosstalkDistance = MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] - RealPeakNumberY[0];
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
                                                    CrosstalkEnergyDepositPercentageOneCubeY->Fill(100*DepozytPomocniczy/RealPeakEnergyResult[0]);
                                                    CrosstalkEnergyDepositPercentageOneCubeImprovedY->Fill(100*DepozytPomocniczy/RealPeakEnergyResultImproved[0]);
                                                    NewPercYz->Fill( 100*DepozytPomocniczy/energyDepZ_YZ[RealPeakNumber]);
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
                                    if ( PomocniczyNumerKostki == RealPeakNumber-1 && RealPeakEnergyY[1]>20 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000)// zmiana 0 and 10000, one cube backward
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
                                                    CrosstalkEnergyDepositPercentageMinus1OneCubeImprovedY->Fill(100*DepozytPomocniczy/RealPeakEnergyResultImproved[1]);
                                                    NewPercYz1->Fill( 100*DepozytPomocniczy/energyDepZ_YZ[RealPeakNumber-1]);
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
                                        }
                                        if(MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] == RealPeakNumberY[1])
                                        {
                                            WierdTestY[1][WierdLicznikY[1]][0]=PomicniczyTriggerTime;
                                            WierdTestY[1][WierdLicznikY[1]][1]=DepozytPomocniczy;                                     
                                            WierdLicznikY[1]++;
                                        }
                                    }
                                    if ( PomocniczyNumerKostki == RealPeakNumber-25 && RealPeakEnergyY[2]>20 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000 && RealPeakNumber>25 && EnergeticEventsX[2]==1 && EnergeticEventsY[2]==1)// zmiana 0 and 10000, Middle of detector
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
                                                    CrosstalkEnergyDepositPercentageMiddleOneCubeImprovedY->Fill(100*DepozytPomocniczy/RealPeakEnergyResultImproved[2]);
                                                    NewPercYz25->Fill( 100*DepozytPomocniczy/energyDepZ_YZ[RealPeakNumber-25]);
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
                                    if( PomocniczyNumerKostki == RealPeakNumber && RealPeakEnergyX[0]>20 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000) //zmiana 0 and 10000
                                    {
                                        CrosstalkDistance = MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] - RealPeakNumberX[0];
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
                                                CrosstalkEnergyDepositPercentageX->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[0]);
                                                NewPercXz->Fill( 100*DepozytPomocniczy/energyDepZ_XZ[RealPeakNumber]);
                                            }
                                            
                                            EnergyTrigTimeCrosstalkX->Fill(PomicniczyTriggerTime, DepozytPomocniczy);
                                            EnergyTrigTimeX->Fill(PomicniczyTriggerTime, DepozytPomocniczy);
                                            if(CrosstalkDistance==1 || CrosstalkDistance==-1)
                                            {
                                                CrosstalkEnergyDepositOneCubeX->Fill( DepozytPomocniczy );
                                                if(RealPeakEnergyResult[0]>1)
                                                {
                                                    CrosstalkEnergyDepositPercentageOneCubeX->Fill(100*DepozytPomocniczy/RealPeakEnergyResult[0]);
                                                    CrosstalkEnergyDepositPercentageOneCubeImprovedX->Fill(100*DepozytPomocniczy/RealPeakEnergyResultImproved[0]);
                                                }
                                                //TODO
                                                Multi1Xz->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],1);
                                            }
                                            if(CrosstalkDistance==2 || CrosstalkDistance==-2)
                                            {
                                                CrosstalkEnergyDepositTwoCubesX->Fill( DepozytPomocniczy );
                                                if(RealPeakEnergyResult[0]>1)
                                                {
                                                    CrosstalkEnergyDepositPercentageTwoCubesX->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[0] );
                                                }
                                                SecondCrosstalkFlag+=1;
                                                //TODO
                                                Multi2Xz->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],1);
                                            }
                                            //TODO
                                            if(CrosstalkDistance==2 && CrosstalkFirstCubeValueX[0][1]>1)
                                            {
                                                NewPercTwoXz->Fill(100*DepozytPomocniczy/CrosstalkFirstCubeValueX[0][1]);
                                            }
                                            if(CrosstalkDistance==-2 && CrosstalkFirstCubeValueX[0][0]>1)
                                            {
                                                NewPercTwoXz->Fill(100*DepozytPomocniczy/CrosstalkFirstCubeValueX[0][0]);
                                            }
                                            
                                            if(CrosstalkDistance>0)
                                            {
                                                CrossEventTypeX[0][CrosstalkDistance+24]=1;
                                            }
                                            if(CrosstalkDistance<0)
                                            {
                                                CrossEventTypeX[0][CrosstalkDistance+24]=1;
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
                                    if( PomocniczyNumerKostki == RealPeakNumber-1 && RealPeakEnergyX[1]>20 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000) //zmiana 0 and 10000, one cube backward
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
                                                    CrosstalkEnergyPercentageMinus1OneCubeX->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[1]);
                                                    CrosstalkEnergyDepositPercentageMinus1OneCubeImprovedX->Fill(100*DepozytPomocniczy/RealPeakEnergyResultImproved[1]);
                                                    NewPercXz1->Fill( 100*DepozytPomocniczy/energyDepZ_XZ[RealPeakNumber-1]);
                                                }
                                                //TODO
                                                Multi1Xz1->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],1);
                                            }
                                            if(CrosstalkDistance==2 || CrosstalkDistance==-2)
                                            {
                                                CrosstalkEnergyDepositMinus1TwoCubesX->Fill( DepozytPomocniczy );
                                                if(RealPeakEnergyResult[1]>1)
                                                {
                                                    CrosstalkEnergyPercentageMinus1TwoCubesX->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[1]);
                                                }
                                                //TODO
                                                Multi2Xz1->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],1);
                                            }
                                            //TODO
                                            if(CrosstalkDistance==2 && CrosstalkFirstCubeValueX[0][1]>1)
                                            {
                                                NewPercTwoXz1->Fill(100*DepozytPomocniczy/CrosstalkFirstCubeValueX[1][1]);
                                            }
                                            if(CrosstalkDistance==-2 && CrosstalkFirstCubeValueX[0][0]>1)
                                            {
                                                NewPercTwoXz1->Fill(100*DepozytPomocniczy/CrosstalkFirstCubeValueX[1][0]);
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
                                        }
                                        if( MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] == RealPeakNumberX[1] )
                                        {
                                            WierdTestX[1][WierdLicznikX[1]][0]=PomicniczyTriggerTime;
                                            WierdTestX[1][WierdLicznikX[1]][1]=DepozytPomocniczy;
                                            WierdLicznikX[1]++;
                                        }
                                    }
                                    if( PomocniczyNumerKostki == RealPeakNumber-25 && RealPeakEnergyX[2]>20 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000 && RealPeakNumber>25 && EnergeticEventsX[2]==1 && EnergeticEventsY[2]==1) //zmiana 0 and 10000, Middle of detector
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
                                                    CrosstalkEnergyPercentageMiddleOneCubeX->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[2]);
                                                    CrosstalkEnergyDepositPercentageMiddleOneCubeImprovedX->Fill(100*DepozytPomocniczy/RealPeakEnergyResultImproved[2]);
                                                    NewPercXz25->Fill( 100*DepozytPomocniczy/energyDepZ_XZ[RealPeakNumber-25]);
                                                }
                                                //TODO
                                                Multi1Xz25->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],1);
                                            }
                                            if(CrosstalkDistance==2 || CrosstalkDistance==-2)
                                            {
                                                CrosstalkEnergyDepositMiddleTwoCubesX->Fill( DepozytPomocniczy );
                                                if(RealPeakEnergyResult[2]>1)
                                                {
                                                    CrosstalkEnergyPercentageMiddleTwoCubesX->Fill( 100*DepozytPomocniczy/RealPeakEnergyResult[2] );
                                                }
                                                //TODO
                                                Multi2Xz25->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],1);
                                            }
                                            //TODO
                                            if(CrosstalkDistance==2 && CrosstalkFirstCubeValueX[0][1]>1)
                                            {
                                                NewPercTwoXz25->Fill(100*DepozytPomocniczy/CrosstalkFirstCubeValueX[2][1]);
                                            }
                                            if(CrosstalkDistance==-2 && CrosstalkFirstCubeValueX[0][0]>1)
                                            {
                                                NewPercTwoXz25->Fill(100*DepozytPomocniczy/CrosstalkFirstCubeValueX[2][0]);
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
                if(energyDepZ[RealPeakNumber-25]>0 && RealPeakNumber>25 && EnergeticEventsX[2]==1 && EnergeticEventsY[2]==1)
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
                if(RealPeakEnergyX[0]>20)
                {
                    HistogramCrosstalkDistanceTypeX->Fill(CrossEventTypeCounterX[0]);
                    StopXz->Fill(energyDepZ_XZ[RealPeakNumber]);
                }
                if(RealPeakEnergyY[0]>20)
                {
                    HistogramCrosstalkDistanceTypeY->Fill(CrossEventTypeCounterY[0]);
                    StopYz->Fill(energyDepZ_YZ[RealPeakNumber]);
                }
                if(energyDepZ[RealPeakNumber-1]>0)
                {
                    if(RealPeakEnergyResult[1]>20)
                    {
                        HistogramRealPeakEnergyDepositMinus1->Fill(RealPeakEnergyResult[1]);
                    }
                    if(RealPeakEnergyX[1]>20)
                    {
                        HistogramCrosstalkDistanceTypeMinus1X->Fill(CrossEventTypeCounterX[1]);
                        StopXz1->Fill(energyDepZ_XZ[RealPeakNumber-1]);
                    }
                    if(RealPeakEnergyY[1]>20)
                    {
                        HistogramCrosstalkDistanceTypeMinus1Y->Fill(CrossEventTypeCounterY[1]);
                        StopYz1->Fill(energyDepZ_YZ[RealPeakNumber-1]);
                    }
                }
                if(energyDepZ[RealPeakNumber-25]>0 && RealPeakNumber>25 && EnergeticEventsX[2]==1 && EnergeticEventsY[2]==1)
                {
                    if(RealPeakEnergyResult[2]>20)
                    {
                        HistogramRealPeakEnergyDepositMiddle->Fill(RealPeakEnergyResult[2]);
                    }
                    if(RealPeakEnergyX[2]>20)
                    {
                        HistogramCrosstalkDistanceTypeMiddleX->Fill(CrossEventTypeCounterX[2]);
                        StopXz25->Fill(energyDepZ_XZ[RealPeakNumber-25]);
                    }
                    if(RealPeakEnergyY[2]>20)
                    {
                        HistogramCrosstalkDistanceTypeMiddleY->Fill(CrossEventTypeCounterY[2]);
                        StopYz25->Fill(energyDepZ_YZ[RealPeakNumber-25]);
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
                        if(hk==0 && RealPeakEnergyX[0]>20)
                        {
                            EnergyTrigTimeTestX->Fill(WierdTestX[0][0][0],WierdTestX[0][0][1]);
                            EnergyTrigTimeTestX->Fill(WierdTestX[0][1][0],WierdTestX[0][1][1]);
                        
                            EnergyTrigTimeSignalX->Fill(TemporaryTime, TemporaryEnergy);
                            EnergyTrigTimeX->Fill(TemporaryTime, TemporaryEnergy);
                            EnergyTrigTimeTestUpgradeX->Fill(TemporaryTime, TemporaryEnergy);
                        }
                        if(hk==1 && RealPeakEnergyX[1]>20)
                        {
                            EnergyTrigTimeMinus1X->Fill(TemporaryTime, TemporaryEnergy);
                        }
                        if(hk==2 && RealPeakNumber>25 && RealPeakEnergyX[2]>20 && EnergeticEventsX[2]==1 && EnergeticEventsY[2]==1)
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
                        if(hk==0 && RealPeakEnergyY[1]>20)
                        {
                            EnergyTrigTimeTestY->Fill(WierdTestY[0][0][0],WierdTestY[0][0][1]);
                            EnergyTrigTimeTestY->Fill(WierdTestY[0][1][0],WierdTestY[0][1][1]);
                        
                            EnergyTrigTimeSignalY->Fill(TemporaryTime, TemporaryEnergy);
                            EnergyTrigTimeY->Fill(TemporaryTime, TemporaryEnergy);
                            EnergyTrigTimeTestUpgradeY->Fill(TemporaryTime, TemporaryEnergy);
                        }
                        if(hk==1 && RealPeakEnergyY[1]>20)
                        {
                            EnergyTrigTimeMinus1Y->Fill(TemporaryTime, TemporaryEnergy);
                        }
                        if(hk==2 && RealPeakNumber>25 && RealPeakEnergyY[2]>20 && EnergeticEventsX[2]==1 && EnergeticEventsY[2]==1)
                        {
                           EnergyTrigTimeMiddleY->Fill(TemporaryTime, TemporaryEnergy);
                        }
                    }
                }
                if(WierdLicznikX[0]==1)
                {
                    EnergyTrigTimeSignalX->Fill(WierdTestX[0][0][0], WierdTestX[0][0][1]);
                    EnergyTrigTimeX->Fill(WierdTestX[0][0][0], WierdTestX[0][0][1]);
                    if(WierdTestX[0][0][1]<20)
                    {
                        EnergyTrigTimeTestLowX->Fill(WierdTestX[0][0][0],WierdTestX[0][0][1]); 
                    }
                }
                if(WierdLicznikX[1]==1 && RealPeakEnergyX[1]>0)
                {
                    EnergyTrigTimeMinus1X->Fill(WierdTestX[1][0][0], WierdTestX[1][0][1]);
                }
                if(WierdLicznikX[2]==1 && RealPeakNumber>25 && RealPeakEnergyX[2]>0 && EnergeticEventsX[2]==1 && EnergeticEventsY[2]==1)
                {
                    EnergyTrigTimeMiddleX->Fill(WierdTestX[2][0][0], WierdTestX[2][0][1]);
                }
                if(WierdLicznikY[0]==1)
                {
                    EnergyTrigTimeSignalY->Fill(WierdTestY[0][0][0], WierdTestY[0][0][1]);
                    EnergyTrigTimeY->Fill(WierdTestY[0][0][0], WierdTestY[0][0][1]);
                    if(WierdTestY[0][0][1]<20)
                    {
                        EnergyTrigTimeTestLowY->Fill(WierdTestY[0][0][0],WierdTestY[0][0][1]);
                    }
                }
                if(WierdLicznikY[1]==1 && RealPeakEnergyY[1]>0)
                {
                   EnergyTrigTimeMinus1Y->Fill(WierdTestY[1][0][0], WierdTestY[1][0][1]);
                }
                if(WierdLicznikY[2]==1 && RealPeakNumber>25 && RealPeakEnergyY[2]>0 && EnergeticEventsX[2]==1 && EnergeticEventsY[2]==1)
                {
                    EnergyTrigTimeMiddleY->Fill(WierdTestY[2][0][0], WierdTestY[2][0][1]);
                }
                
                StoppingPointLocation->Fill(RealPeakNumber);
                HistogramHighestEnergyDeposit->Fill(PeakEnergy);
                HistogramRealPeakEnergyDeposit->Fill(RealPeakEnergyResult[0]);
                
                cout <<"licznik "<<licznik<<" sigmaX " << sigma <<" sigmaY " << sigmaY <<" RealPeakNumber "<<RealPeakNumber<<" PID "<<Pid<<endl;
                cout <<"licznik "<<licznik<<" RealPeakEnergyX "<< RealPeakEnergyX[0]<<" RealPeakEnergyY "<<RealPeakEnergyY[0]<<endl;
                cout <<"licznik "<<licznik<<" RealPeakNumberX "<< RealPeakNumberX[0]<<" RealPeakNumberY "<<RealPeakNumberY[0]<<endl;
                if(energyDepZ[RealPeakNumber-25]>0 && RealPeakNumber>25 && EnergeticEventsX[2]==1 && EnergeticEventsY[2]==1)
                {
                    cout <<"licznik "<<licznik<<" RealPeakNumber-25: "<<RealPeakNumber-25<<" RealPeakEnergy-25: "<<energyDepZ[RealPeakNumber-25]<<endl;
                }
                if(SecondCrosstalkFlag>0)
                {
                    cout<<"licznik "<<licznik<<" crosstalk two cubes "<<endl;
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
        delete energyZ_XZ[eventNum];
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
    
    CrosstalkEnergyDepositPercentageOneCubeImprovedX->Write();
    CrosstalkEnergyDepositPercentageOneCubeImprovedY->Write();
    
    CrosstalkEnergyDepositPercentageTwoCubesX->Write();
    CrosstalkEnergyDepositPercentageTwoCubesY->Write(); 

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
    
    CrosstalkEnergyDepositMinus1OneCubeX->Write();
    CrosstalkEnergyDepositMinus1OneCubeY->Write();
    
    CrosstalkEnergyDepositMinus1TwoCubesX->Write();
    CrosstalkEnergyDepositMinus1TwoCubesY->Write();
    
    CrosstalkEnergyPercentageMinus1X->Write();
    CrosstalkEnergyPercentageMinus1Y->Write();
    
    CrosstalkEnergyPercentageMinus1OneCubeX->Write();
    CrosstalkEnergyPercentageMinus1OneCubeY->Write();
    
    CrosstalkEnergyDepositPercentageMinus1OneCubeImprovedX->Write();
    CrosstalkEnergyDepositPercentageMinus1OneCubeImprovedY->Write();
    
    CrosstalkEnergyPercentageMinus1TwoCubesX->Write();
    CrosstalkEnergyPercentageMinus1TwoCubesY->Write();
    
    HistogramCrosstalkDistanceMinus1X->Write();
    HistogramCrosstalkDistanceMinus1Y->Write();
    
    HistogramRealPeakEnergyDepositMinus1->Write();
    
    HistogramCrosstalkDistanceTypeMinus1X->Write();
    HistogramCrosstalkDistanceTypeMinus1Y->Write();
    
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
    
    CrosstalkEnergyDepositPercentageMiddleOneCubeImprovedX->Write();
    CrosstalkEnergyDepositPercentageMiddleOneCubeImprovedY->Write();
    
    CrosstalkEnergyPercentageMiddleTwoCubesX->Write();
    CrosstalkEnergyPercentageMiddleTwoCubesY->Write();
    
    HistogramCrosstalkDistanceMiddleX->Write();
    HistogramCrosstalkDistanceMiddleY->Write();
    
    HistogramCrosstalkDistanceTypeMiddleX->Write();
    HistogramCrosstalkDistanceTypeMiddleY->Write();
    
    HistogramRealPeakEnergyDepositMiddle->Write();
        
    EnergyTrigTimeMiddleX->Write();
    EnergyTrigTimeMiddleY->Write();
    
    EnergyTrigTimeTestX->Write();
    EnergyTrigTimeTestY->Write();
    
    EnergyTrigTimeTestUpgradeX->Write();
    EnergyTrigTimeTestUpgradeY->Write();
    
    EnergyTrigTimeTestLowX->Write();
    EnergyTrigTimeTestLowY->Write();
    ////////
    StopXz->Write();
    StopXz1->Write();
    StopXz25->Write();
   
    StopYz->Write();
    StopYz1->Write();
    StopYz25->Write();
    
    NewPercXz->Write();
    NewPercXz1->Write();
    NewPercXz25->Write();
    
    NewPercYz->Write();
    NewPercYz1->Write();
    NewPercYz25->Write();
    
    NewPercTwoXz->Write();
    NewPercTwoXz1->Write();
    NewPercTwoXz25->Write();
    
    Multi1Xz->Write();
    Multi1Xz1->Write();
    Multi1Xz25->Write();
    
    Multi2Xz->Write();
    Multi2Xz1->Write();
    Multi2Xz25->Write();
    
    wfile.Close();
    FileInput->Close();
    return 0;
}
