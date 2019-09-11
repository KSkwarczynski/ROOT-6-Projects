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
#include <math.h> 

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
    rootFileOutput+="_MuonCrosstalk.root";
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
    for(int i = 0; i < NumberOfEB; i++){
        if(nentries[i] < minEn && nentries[i]>0){
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
  
    TH1F *TrackDepositX = new TH1F("TrackDepositX", "Energy deposit by track X axis",500,0,500);
    TrackDepositX->GetYaxis()->SetTitle("Number of events");
    TrackDepositX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *TrackDepositY = new TH1F("TrackDepositY", "Energy deposit by track Y axis",500,0,500);
    TrackDepositY->GetYaxis()->SetTitle("Number of events");
    TrackDepositY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositLeftX = new TH1F("CrosstalkEnergyDepositLeftX", "Crosstalk energy left from track deposit, in X plain",200,0,50);
    CrosstalkEnergyDepositLeftX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositLeftX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositRightX = new TH1F("CrosstalkEnergyDepositRightX", "Crosstalk energy right from track deposit in X plain",200,0,50);
    CrosstalkEnergyDepositRightX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositRightX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositLeftY = new TH1F("CrosstalkEnergyDepositLeftY", "Crosstalk energy left from track deposit, in Y plain",200,0,50);
    CrosstalkEnergyDepositLeftY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositLeftY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositRightY = new TH1F("CrosstalkEnergyDepositRightY", "Crosstalk energy right from track deposit in Y plain",200,0,50);
    CrosstalkEnergyDepositRightY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositRightY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TDirectory *events2D = wfile.mkdir("events2D");
    TDirectory *Type2D = wfile.mkdir("Type2D");
    TDirectory *Energy2D = wfile.mkdir("Energy2D");
    int NumberEvDis = 20000; //10000
  
    ostringstream sEventnum;
    string sEvent;
    TH2F *event_XY[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "event_XY"+sEventnum.str();
        event_XY[ih] = new TH2F(sEvent.c_str(),sEvent.c_str(), 24,0,24, 8,0,8);
        event_XY[ih]->GetXaxis()->SetTitle("X axis [cm]");
        event_XY[ih]->GetYaxis()->SetTitle("Y axis [cm]");
    }
    TH2F *event_YZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "event_YZ"+sEventnum.str();
        event_YZ[ih] = new TH2F(sEvent.c_str(),sEvent.c_str(), 48,0,48, 8,0,8);
        event_YZ[ih]->GetXaxis()->SetTitle("Z axis [cm]");
        event_YZ[ih]->GetYaxis()->SetTitle("Y axis [cm]");
    }
  
    TH2F *event_XZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "event_XZ"+sEventnum.str();
        event_XZ[ih] = new TH2F(sEvent.c_str(),sEvent.c_str(), 24,0,24, 48,0,48);
        event_XZ[ih]->GetXaxis()->SetTitle("X axis [cm]");
        event_XZ[ih]->GetYaxis()->SetTitle("Z axis [cm]");
    }
    TH1F *energy_Z[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "energy_Z"+sEventnum.str();
        energy_Z[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(),48,0,48);
        energy_Z[ih]->GetXaxis()->SetTitle("Z axis [cm]");
        energy_Z[ih]->GetYaxis()->SetTitle("Energy deposit [p.e.]");
    }
    TH2F *event_type_YZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "event_type_YZ"+sEventnum.str();
        event_type_YZ[ih] = new TH2F(sEvent.c_str(),sEvent.c_str(), 48,0,48, 8,0,8);
        event_type_YZ[ih]->GetXaxis()->SetTitle("Z axis [cm]");
        event_type_YZ[ih]->GetYaxis()->SetTitle("Y axis [cm]");
    }
    TH2F *event_type_XZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "event_type_XZ"+sEventnum.str();
        event_type_XZ[ih] = new TH2F(sEvent.c_str(),sEvent.c_str(), 24,0,24, 48,0,48);
        event_type_XZ[ih]->GetXaxis()->SetTitle("X axis [cm]");
        event_type_XZ[ih]->GetYaxis()->SetTitle("Z axis [cm]");
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
    double energyDepZ[48];
    double energyDepX_XZ[24];
    double energyDepY_YZ[8];
    
    double energy_XZ[24][48];
    double energy_YZ[48][8];
                
    int EventType_XZ[24][48];
    int EventType_YZ[48][8];
    
    double HighestDepositEnergyX[48];
    double HighestDepositEnergyY[48];
    int HighestDepositPositionX[48];
    int HighestDepositPositionY[48];
        
    int eventNum=0;
    bool LargehitTimeDif = 0;
    double DepozytPomocniczy=0;
    
    double Pid=0;
    int EventCounter=0;

    TCanvas *DisplayCanvas = new TCanvas("DisplayCanvas","DisplayCanvas", 1400, 1000);
    TCanvas *TypeCanvas = new TCanvas("TypeCanvas","TypeCanvas", 1400, 1000);
    TCanvas *CrossEnergyCanvas = new TCanvas("CrossEnergyCanvas","CrossEnergyCanvas", 1400, 1000);
    bool SpillMised = false;
    for (Int_t subSpill = 0; subSpill<minEn; subSpill++)
    {
        Int_t SpillNumber = subSpill;
        
        cout <<"Getting Spill Number "<< SpillNumber+1 <<endl;
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
            for(int TOFtrigger = 0; TOFtrigger < FEB[12].FEBSN->size(); TOFtrigger++)
            {
            if(FEB[12].hitTimeDif->at(TOFtrigger) > 0 && NumberEvDis > eventNum)
            {
                for (int ik=0;ik<48;ik++) //zerowanie tablic przechowujace dane, Z
                {
                    energyDepZ[ik]=0;
                    HighestDepositEnergyX[ik]=0;
                    HighestDepositEnergyY[ik]=0;
                    HighestDepositPositionX[ik]=0;
                    HighestDepositPositionY[ik]=0;
                    for(int hk = 0; hk<24; hk++)
                    {
                        energy_XZ[hk][ik]=0;
                        EventType_XZ[hk][ik]=0;
                        if(ik==0)
                        {
                            energyDepX_XZ[hk]=0;
                        }
                    }
                    for(int hk = 0; hk<8; hk++)
                    {
                       energy_YZ[ik][hk]=0;
                       EventType_YZ[ik][hk]=0;
                       if(ik==0)
                        {
                            energyDepY_YZ[hk]=0;
                        }
                    }
                }    
                LargehitTimeDif=0;
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
                            LargehitTimeDif = 1; // Mozliwe ze trzeba zmieniec
                        }
                        
                        Pid = FEB[12].hitsChannel->at(TOFtrigger);
                        
                        if ( FEBs[i] == 0 || FEBs[i] == 16) //Plaszczyzna XY
                        {
                            DepozytPomocniczy=FEB[FEBs[i]].hitCharge_pe->at(check);
                            event_XY[eventNum]-> Fill( MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)], DepozytPomocniczy);
                            EventsMap_XY->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],1);
                            }
                        else if ( FEBs[i] == 1 || FEBs[i] == 2 || FEBs[i] == 17 || FEBs[i] ==  24) //Plaszczyzna YZ
                        {
                            DepozytPomocniczy=FEB[FEBs[i]].hitCharge_pe->at(check);
                            event_YZ[eventNum]->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)], MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)], DepozytPomocniczy);
                            EventsMap_YZ->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)], 1);
                            if (DepozytPomocniczy>0 && DepozytPomocniczy<10000 && MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]<48 && MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]>=0 && MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]<8 && MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]>=0)
                            {
                                energyDepZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]]+=DepozytPomocniczy;
                                energy_YZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]][MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]]+=DepozytPomocniczy;
                                energyDepY_YZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]]+=DepozytPomocniczy;
                            }
                        }
                        else //Plaszczyzna XZ
                        {
                            DepozytPomocniczy=FEB[FEBs[i]].hitCharge_pe->at(check);
                            event_XZ[eventNum]->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)], DepozytPomocniczy);
                            EventsMap_XZ->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)], 1);
                            if (DepozytPomocniczy>0 && DepozytPomocniczy<10000 && MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]<24 && MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]>=0 && MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]<48 && MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]>=0)
                            {
                                energyDepZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]]+=DepozytPomocniczy;
                                energy_XZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]][MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]]+=DepozytPomocniczy;
                                energyDepX_XZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]]+=DepozytPomocniczy;
                            }
                        }
                    }
                }
            }
        }
            double MainDepositThreshold=15; //!!! wartosc testowa pewnie trzeba bedzie zwiekszyc
            int MainDepositCounter=0;
            
            double MeanPosition[2]={};          //0-X, 1-Y
            double MeanPositionReal[2]={};      //0-X, 1-Y
            double MeanPostionCounter[2]={};    //0-X, 1-Y
            int DistanceThreshold[2]={4,4};     //0-X, 1-Y
            
            double Crosstalk[2][2]; //[X or Y][ain value and sigma]
            Crosstalk[0][0]=2.38; //values insererted from preiuous study on stopping proton
            Crosstalk[0][1]=0.02;
            Crosstalk[1][0]=1.42;
            Crosstalk[1][1]=0.02;
            int SigmaNumber=50;
            for(int ik = 0; ik < 48; ik++) //searching for muon deposits
            {
                energy_Z[eventNum]->Fill(ik, energyDepZ[ik]);

                for(int hk=0; hk<24; hk++)
                {
                    if(energy_XZ[hk][ik]>HighestDepositEnergyX[ik])
                    {
                        HighestDepositEnergyX[ik]=energy_XZ[hk][ik];
                        HighestDepositPositionX[ik]=hk;
                    }
                }
                if(HighestDepositEnergyX[ik]>MainDepositThreshold) 
                {
                    EventType_XZ[HighestDepositPositionX[ik]][ik]=1; //1 means muon deposit
                    MainDepositCounter+=1;
                    
                    MeanPosition[0]+=HighestDepositPositionX[ik];
                    MeanPostionCounter[0]+=1;
                    
                }
                for(int hk=0; hk<8;hk++)
                {
                    if(energy_YZ[ik][hk]>HighestDepositEnergyY[ik])
                    {
                        HighestDepositEnergyY[ik]=energy_YZ[ik][hk];
                        HighestDepositPositionY[ik]=hk;
                    }
                }
                if(HighestDepositEnergyY[ik]>MainDepositThreshold)
                {
                    EventType_YZ[ik][HighestDepositPositionY[ik]]=1; //1 means muon deposit
                    MainDepositCounter+=1;
                    
                    MeanPosition[1]+=HighestDepositPositionY[ik];
                    MeanPostionCounter[1]+=1;
                }
            }
//////////////////////Selection_Declaration/////////////////
            bool TrackBeginningCut=0; //ciecie usuwajace czastki bez depozytu na poczatku detektora
            if(energyDepZ[0]>1 || energyDepZ[1]>1 || energyDepZ[2]>1)
            {
                TrackBeginningCut=1;
            }
            //Fitowanie potrzebne do ciecia usuwajacego nie gausowe smieci
            for(int ik = 0; ik < 24; ik++ )
            {
                energyX_XZ[eventNum]->Fill(ik,energyDepX_XZ[ik]);
            }
            for(int ik = 0; ik < 8; ik++ )
            {
                energyY_YZ[eventNum]->Fill(ik,energyDepY_YZ[ik]);
            }
            double sigma=0;
            double sigmaThreshold=2; //setting value for sigma cut, still experimental!!!!
            bool sigmaCut=0;
            TF1 *EnergyFitX = new TF1("EnergyFitX", "gaus");
            energyX_XZ[eventNum]-> Fit(EnergyFitX,"q","",1 , 23);
            sigma = EnergyFitX->GetParameter(2); // We chose sigma to get rid of garbage

            delete EnergyFitX;
            if(sigma < sigmaThreshold) 
            {
                sigmaCut=1;
            }
            bool MuonTrigger=0;
            if(Pid==2) //0-all particles 1-Electrons 2-Muons/Pions 3-Protons || newer version Channel 0 -Electron 1-Muons/Pions Channel 3-all particles
            {
                MuonTrigger=1;
            }
            
        if(LargehitTimeDif == 0 && MainDepositCounter>40 && TrackBeginningCut==1 && sigmaCut==1 && MuonTrigger==1)
        {
            //////////Fixing Track////////
            double Distance=0;
            MeanPositionReal[0]=MeanPosition[0]/MeanPostionCounter[0];
            MeanPositionReal[1]=MeanPosition[1]/MeanPostionCounter[1];
            
            for(int ik = 0; ik < 48; ik++) //searching for muon deposits
            {
                for(int hk=0; hk<24; hk++)
                {
                    Distance=fabs(hk-MeanPositionReal[0]);
                    if(EventType_XZ[hk][ik]==1 && Distance>DistanceThreshold[0])
                    {
                        EventType_XZ[hk][ik]=0;
                        for(int gk=0; gk<24; gk++)
                        {
                            Distance=fabs(gk-MeanPositionReal[0]);
                            if(energy_XZ[gk][ik]>MainDepositThreshold && Distance<DistanceThreshold[0])
                            {
                                EventType_XZ[gk][ik]=1;
                                if(energy_XZ[gk][ik]>energy_XZ[gk-1][ik] && gk>0)
                                {
                                    EventType_XZ[gk-1][ik]=0;
                                }
                            }
                        }
                    }
                }
                for(int hk=0; hk<8;hk++)
                {
                    Distance=fabs(hk-MeanPositionReal[1]);
                    if(EventType_YZ[ik][hk]==1 && Distance>DistanceThreshold[1])
                    {
                        EventType_YZ[ik][hk]=0;
                        for(int gk=0; gk<8; gk++)
                        {
                            Distance=fabs(gk-MeanPositionReal[1]);
                            if(energy_YZ[ik][gk]>MainDepositThreshold && Distance<DistanceThreshold[1])
                            {
                                EventType_YZ[ik][gk]=1;
                            }
                            if(energy_YZ[ik][gk]>energy_YZ[ik][gk-1] && gk>0)
                            {
                                energy_YZ[ik][gk-1]=0;
                            }
                        }
                    }
                }
            }
            //////////////
            int PozycjaPomocnicza=0;
            double CrosstalkPomocniczy[2]={}; //0 is for + and 1 is for -
            for(int ik = 0; ik < 48; ik++) //assigning events as crosstalk
            {
                if(HighestDepositEnergyX[ik]>MainDepositThreshold) //////Checking X axis
                {
                    PozycjaPomocnicza=HighestDepositPositionX[ik];
                    CrosstalkPomocniczy[0]=Crosstalk[0][0]+Crosstalk[0][1]*SigmaNumber;
                    CrosstalkPomocniczy[1]=Crosstalk[0][0]-Crosstalk[0][1]*SigmaNumber;
                    if(energy_XZ[PozycjaPomocnicza-1][ik]<energy_XZ[PozycjaPomocnicza][ik]*CrosstalkPomocniczy[0]/100 && energy_XZ[PozycjaPomocnicza-1][ik]>energy_XZ[PozycjaPomocnicza][ik]*CrosstalkPomocniczy[1]/100 && PozycjaPomocnicza>0 && energy_XZ[PozycjaPomocnicza-1][ik]>1)
                    {
                        EventType_XZ[PozycjaPomocnicza-1][ik]=-2; //-2 means crosstalk on the left
                    }
                    if(energy_XZ[PozycjaPomocnicza+1][ik]<energy_XZ[PozycjaPomocnicza][ik]*CrosstalkPomocniczy[0]/100 && energy_XZ[PozycjaPomocnicza+1][ik]>energy_XZ[PozycjaPomocnicza][ik]*CrosstalkPomocniczy[1]/100 && PozycjaPomocnicza<23 && energy_XZ[PozycjaPomocnicza+1][ik]>1)
                    {
                        EventType_XZ[PozycjaPomocnicza+1][ik]=2; //2 means crosstalk on the right
                    }
                }
                if(HighestDepositEnergyY[ik]>MainDepositThreshold) //////Checking Y axis
                {          
                    PozycjaPomocnicza=HighestDepositPositionY[ik];
                    CrosstalkPomocniczy[0]=Crosstalk[1][0]+Crosstalk[1][1]*SigmaNumber;
                    CrosstalkPomocniczy[1]=Crosstalk[1][0]-Crosstalk[1][1]*SigmaNumber;
                    if(energy_YZ[ik][PozycjaPomocnicza-1]<energy_YZ[ik][PozycjaPomocnicza]*CrosstalkPomocniczy[0]/100 && energy_YZ[ik][PozycjaPomocnicza-1]>energy_YZ[ik][PozycjaPomocnicza]*CrosstalkPomocniczy[1]/100 && PozycjaPomocnicza>0 && energy_YZ[ik][PozycjaPomocnicza-1]>1)
                    {
                        EventType_YZ[ik][PozycjaPomocnicza-1]=-2; //-2 means crosstalk on the left
                    }
                    if(energy_YZ[ik][PozycjaPomocnicza+1]<energy_YZ[ik][PozycjaPomocnicza]*CrosstalkPomocniczy[0]/100 && energy_YZ[ik][PozycjaPomocnicza+1]>energy_YZ[ik][PozycjaPomocnicza]*CrosstalkPomocniczy[1]/100 && PozycjaPomocnicza<7 && energy_YZ[ik][PozycjaPomocnicza+1]>1)
                    {
                        EventType_YZ[ik][PozycjaPomocnicza+1]=2; //2 means crosstalk on the right
                    }
                }
            } 
            for(int ik = 0; ik < 48; ik++) //assigning events as crosstalk
            {
                for(int hk = 0; hk < 24; hk++)
                {
                    event_type_XZ[eventNum]->Fill(hk, ik, EventType_XZ[hk][ik]);
                    if(EventType_XZ[hk][ik]==1)
                    {
                        TrackDepositX->Fill(energy_XZ[hk][ik]);
                    }
                    if(EventType_XZ[hk][ik]==-2)
                    {
                        CrosstalkEnergyDepositLeftX->Fill(energy_XZ[hk][ik]);
                    }
                    if(EventType_XZ[hk][ik]==+2)
                    {
                        CrosstalkEnergyDepositRightX->Fill(energy_XZ[hk][ik]);
                    }
                }
                for(int hk = 0; hk < 8; hk++)
                {
                    event_type_YZ[eventNum]->Fill(ik, hk, EventType_YZ[ik][hk]);
                    if(EventType_YZ[ik][hk]==1)
                    {
                        TrackDepositY->Fill(energy_YZ[ik][hk]);
                    }
                    if(EventType_YZ[ik][hk]==-2)
                    {
                        CrosstalkEnergyDepositLeftY->Fill(energy_YZ[ik][hk]);
                    }
                    if(EventType_YZ[ik][hk]==+2)
                    {
                        CrosstalkEnergyDepositRightY->Fill(energy_YZ[ik][hk]);
                    }
                }
            }
            DisplayCanvas->Clear();
            TypeCanvas->Clear();
            CrossEnergyCanvas->Clear();
            
            DisplayCanvas->Divide(2,2);
            DisplayCanvas -> cd(1);
            event_XZ[eventNum]-> Draw("colorz");
        
            DisplayCanvas -> cd(2);
            event_YZ[eventNum]-> Draw("colorz");
        
            DisplayCanvas -> cd(3);
            event_XY[eventNum]->Draw("colorz");
        
            DisplayCanvas -> cd(4);
            energy_Z[eventNum]->Draw("HIST");
        
            DisplayCanvas->Update();
            events2D -> cd();
            DisplayCanvas->Write();

            TypeCanvas->Divide(2,2);
            TypeCanvas -> cd(1);
            event_XZ[eventNum]-> Draw("colorz");
        
            TypeCanvas -> cd(2);
            event_YZ[eventNum]-> Draw("colorz");
            
            TypeCanvas -> cd(3);
            event_type_XZ[eventNum]-> Draw("colorz");
        
            TypeCanvas -> cd(4);
            event_type_YZ[eventNum]-> Draw("colorz");
            
            TypeCanvas->Update();
            Type2D -> cd();
            TypeCanvas->Write();
            
            CrossEnergyCanvas->Divide(2,2);
            CrossEnergyCanvas -> cd(1);
            event_XZ[eventNum]->Draw("colorz");
        
            CrossEnergyCanvas -> cd(2);
            event_YZ[eventNum]->Draw("colorz");
            
            CrossEnergyCanvas->cd(3);
            energyX_XZ[eventNum]->Draw("HIST");
        
            CrossEnergyCanvas->cd(4);
            energyY_YZ[eventNum]->Draw("HIST");
           
            CrossEnergyCanvas->Update();
            Energy2D -> cd();
            CrossEnergyCanvas->Write();
            
            EventCounter++;
            cout<<"Event Counter "<<EventCounter<<" sigma " << sigma <<" PID "<< Pid <<endl;
        }
        delete event_XY[eventNum];
        delete event_YZ[eventNum];
        delete event_XZ[eventNum];
        delete energy_Z[eventNum];
        delete event_type_XZ[eventNum];
        delete event_type_YZ[eventNum];
        delete energyX_XZ[eventNum];
        delete energyY_YZ[eventNum];
        eventNum++;
    }
}
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
        }    
  }
    wfile.cd();
    EventsMap_XY->Write();
    EventsMap_YZ->Write();
    EventsMap_XZ->Write();
    
    TrackDepositX->Write();
    TrackDepositY->Write();
    CrosstalkEnergyDepositLeftX->Write();
    CrosstalkEnergyDepositRightX->Write();
    CrosstalkEnergyDepositLeftY->Write();
    CrosstalkEnergyDepositRightY->Write();
  
    wfile.Close();
    FileInput->Close();
    return 0;
}
