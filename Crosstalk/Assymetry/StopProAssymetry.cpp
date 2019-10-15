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
    rootFileOutput+="_CrosstalkAsymmetry.root";
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
    
    TH2F *EnergyTrigTimeX = new TH2F("EnergyTrigTimeX","Energy and Time of Trigger X axis stopping point + Crosstalk", 100,-100,100,500,0,1500);
    EnergyTrigTimeX->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeX->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH2F *EnergyTrigTimeY = new TH2F("EnergyTrigTimeY","Energy and Time of Trigger Y axis stopping point + Crosstalk", 100,-100,100,500,0,1500);
    EnergyTrigTimeY->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeY->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH1F *HistogramHighestEnergyDeposit = new TH1F("HistogramHighestEnergyDeposit", "Histogram of highest value deposit",100,0,2500);
    HistogramHighestEnergyDeposit->GetYaxis()->SetTitle("Number of events");
    HistogramHighestEnergyDeposit->GetXaxis()->SetTitle("Energy [p.e.]");
   
    TH1F *HistogramRealPeakEnergyDeposit = new TH1F("HistogramRealPeakEnergyDeposit", "Histogram of found stopping proton deposit",100,0,2500);
    HistogramRealPeakEnergyDeposit->GetYaxis()->SetTitle("Number of events");
    HistogramRealPeakEnergyDeposit->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *StoppingPointLocation = new TH1F("StoppingPointLocation", "Location of stopping point",48,0,48);
    StoppingPointLocation->GetYaxis()->SetTitle("Number of events");
    StoppingPointLocation->GetXaxis()->SetTitle("Z detector axis [cm]");
    
    TH1F *CrosstalkEnergyDepositX = new TH1F("CrosstalkEnergyDepositX", "Crosstalk energy in X plain",500,0,500);
    CrosstalkEnergyDepositX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositX->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositY = new TH1F("CrosstalkEnergyDepositY", "Crosstalk energy in Y plain",500,0,500);
    CrosstalkEnergyDepositY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkHistogramDifferenceX = new TH1F("CrosstalkHistogramDifferenceX", "Crosstalk right subtracted by crosstalk on the left in X plain",100.0,-50.0,50.0);
    CrosstalkHistogramDifferenceX->GetYaxis()->SetTitle("Number of events");
    CrosstalkHistogramDifferenceX->GetXaxis()->SetTitle("Fraction");
    
    TH1F *CrosstalkHistogramDifferenceY = new TH1F("CrosstalkHistogramDifferenceY", "Crosstalk right subtracted by crosstalk on the left in Y plain",100.0,-50.0,50.0);
    CrosstalkHistogramDifferenceY->GetYaxis()->SetTitle("Number of events");
    CrosstalkHistogramDifferenceY->GetXaxis()->SetTitle("Fraction");
    
    TDirectory *events2D = wfile.mkdir("events2D");
    TDirectory *CrossEnergy = wfile.mkdir("CrossEnergy");
    TDirectory *CrossEnergyPlain = wfile.mkdir("CrossEnergyPlain");
    int NumberEvDis = 14000; // zmiana 10000

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
    double Pid=0;
    
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

            double RealPeakEnergyX[3]={};   //0-StoppingPoint,1-OneCubeBackward,2-MiddleOfTrack
            int RealPeakNumberX[3]={};     //0-StoppingPoint,1-OneCubeBackward,2-MiddleOfTrack

            double RealPeakEnergyY[3]={}; //0-StoppingPoint,1-OneCubeBackward,2-MiddleOfTrack
            int RealPeakNumberY[3]={};   //0-StoppingPoint,1-OneCubeBackward,2-MiddleOfTrack
            
            double RealPeakEnergyResult[3]={};

            int CrosstalkDistance=0;
            int PomocniczyNumerKostki=0;
            double PomicniczyTriggerTime=0;
            
            int EnergeticEventsX[2]={};
            int EnergeticEventsY[2]={};
            
            
            double ProtonThreshold=-80; //Value to seperate protons from other hadrons (pions most likely)
            double TriggerTimeValue=0; 
            int TriggerTimerCounter=0;
            
            double CrosstalkDepositRightX=0;
            double CrosstalkDepositLeftX=0;
            
            double CrosstalkDepositRightY=0;
            double CrosstalkDepositLeftY=0;
            
            double CrosstalkSubtractedX=0;
            double CrosstalkSubtractedY=0;
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
            }
            bool DiscontinuityCut=0; // maximally two layers before peak can have 0 deposit
            if(RealPeakNumber>3)
            {
                if(energyDepZ[RealPeakNumber-1]>1 || energyDepZ[RealPeakNumber-2]>1 || energyDepZ[RealPeakNumber-3]>1)
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
                sigma = EnergyFitX->GetParameter(2); // We chose sigma to get rid of garbage

                delete EnergyFitX;
                if(sigma < 1.4) ///setting value for sigma cut
                {
                    sigmaCut=1;
                }
            }
            bool EventNumberCut=0; //to eleminate low deposit number events
            if(event_XZ[eventNum]->GetEntries()>10)
            {
                EventNumberCut=1;
            }
            ////////
            if(LargehitTimeDif == 0 && StoppingParticle==1 && PeakEnergy>250 && DiscontinuityCut==1 && TrackBeginningCut==1 && sigmaCut==1 && EventNumberCut==1)
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
                                    if(PomocniczyNumerKostki == RealPeakNumber-15 && RealPeakNumber>15 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000)// zmiana 0 and 10000
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
                                    if(PomocniczyNumerKostki == RealPeakNumber-15 && RealPeakNumber>15 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000) //zmiana 0 and 10000
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
                        if(hk==0 && energyDepX_XZ_Plain[0][ik]>60)
                        {
                            EnergeticEventsX[0]+=1;
                        }
                        if(hk==1 && energyDepX_XZ_Plain[1][ik]>60)
                        {
                            EnergeticEventsX[1]+=1;
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
                    }
                }
            }
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
            /*bool ProtonFlag=0;
            if(Pid==3) //0-all particles 1-Electrons 2-Muons/Pions 3-Protons || newer version Channel 0 -Electron 1-Muons/Pions Channel 3-all particles
            {
                ProtonFlag=1;
            }*/
            bool ProtonFlag=0;
            if( (TriggerTimeValue/TriggerTimerCounter) > ProtonThreshold)
            {
                ProtonFlag=1;
            }
            bool TwoSidedCrosstalkX=0;
            if(energyDepX_XZ_Plain[0][RealPeakNumberX[0]-1]>1 && energyDepX_XZ_Plain[0][RealPeakNumberX[0]+1]>1)
            {
                TwoSidedCrosstalkX=1;
            }
            bool TwoSidedCrosstalkY=0;
            if(energyDepY_YZ_Plain[0][RealPeakNumberY[0]-1]>1 && energyDepY_YZ_Plain[0][RealPeakNumberY[0]+1]>1)
            {
                TwoSidedCrosstalkY=1;
            }
            bool StraightStoppingPoint=0; //PROTON is in the same position in Stopping Point and SP-1
            if(RealPeakNumberX[0]==RealPeakNumberX[1])
            {
                StraightStoppingPoint=1;
            }
            if(LargehitTimeDif == 0 && StoppingParticle==1 && PeakEnergy>250 && DiscontinuityCut==1 && TrackBeginningCut==1 && BorderCutY==1 && BorderCutX && sigmaCut==1 && EventNumberCut==1 && EnergeticEventsX[0]==1 && EnergeticEventsX[1]==1 && EnergeticEventsY[0]==1 && EnergeticEventsY[1]==1 && ProtonFlag==1 && StraightStoppingPoint==1)
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
                                    PomicniczyTriggerTime=FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime;
                                    DepozytPomocniczy=FEB[FEBs[i]].hitCharge_pe->at(check);
                                    if ( PomocniczyNumerKostki == RealPeakNumber && RealPeakEnergyY[0]>40 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000)// zmiana 0 and 10000
                                    {
                                        CrosstalkDistance = MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] - RealPeakNumberY[0];
                                        EnergyTrigTimeY->Fill(PomicniczyTriggerTime, DepozytPomocniczy);
                                        if(MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] != RealPeakNumberY[0])
                                        {
                                            CrosstalkEnergyDepositY->Fill( DepozytPomocniczy );
                                        }
                                        if(CrosstalkDistance==1)
                                        {
                                            CrosstalkDepositRightY=DepozytPomocniczy;
                                        }
                                        if(CrosstalkDistance==-1)
                                        {
                                            CrosstalkDepositLeftY=DepozytPomocniczy;
                                        }
                                    }
                                }
                                else //Plaszczyzna XZ
                                {
                                    PomocniczyNumerKostki = MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)];
                                    PomicniczyTriggerTime=FEB[FEBs[i]].hitLeadTime->at(check)-TriggerTime;
                                    DepozytPomocniczy=FEB[FEBs[i]].hitCharge_pe->at(check);
                                    if( PomocniczyNumerKostki == RealPeakNumber && RealPeakEnergyX[0]>40 && DepozytPomocniczy > 0 && DepozytPomocniczy < 10000 && TwoSidedCrosstalkX==1) //zmiana 0 and 10000
                                    {
                                        CrosstalkDistance = MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] - RealPeakNumberX[0];
                                        EnergyTrigTimeX->Fill(PomicniczyTriggerTime, DepozytPomocniczy);
                                        if(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] != RealPeakNumberX[0])
                                        {
                                            CrosstalkEnergyDepositX->Fill( DepozytPomocniczy );
                                        }
                                        if(CrosstalkDistance==1)
                                        {
                                            CrosstalkDepositRightX=DepozytPomocniczy;
                                        }
                                        if(CrosstalkDistance==-1)
                                        {
                                            CrosstalkDepositLeftX=DepozytPomocniczy;
                                        }
                                    }
                                }
                            }
                        }
                    }
                } 
                //////
                CrosstalkSubtractedX=CrosstalkDepositRightX-CrosstalkDepositLeftX;
                CrosstalkSubtractedY=CrosstalkDepositRightY-CrosstalkDepositLeftY;
                
                StoppingPointLocation->Fill(RealPeakNumber);
                HistogramHighestEnergyDeposit->Fill(PeakEnergy);
                HistogramRealPeakEnergyDeposit->Fill(RealPeakEnergyResult[0]);
                if(TwoSidedCrosstalkX==1)
                {
                    CrosstalkHistogramDifferenceX->Fill(CrosstalkSubtractedX);
                }
                if(TwoSidedCrosstalkY==1)
                {
                    CrosstalkHistogramDifferenceY->Fill(CrosstalkSubtractedY);
                }
                cout <<"licznik "<<licznik<<" sigma " << sigma <<" RealPeakNumber "<<RealPeakNumber<<" PID "<<Pid<<endl;
                cout <<"licznik "<<licznik<<" RealPeakEnergyX "<< RealPeakEnergyX[0]<<" RealPeakEnergyY "<<RealPeakEnergyY[0]<<endl;
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
    wfile.Close();
    FileInput->Close();
    return 0;
}
