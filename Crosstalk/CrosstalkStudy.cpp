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
            //std::cout<<sFEB<<" ";
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
            //std::cout << "Number of events = " <<FEB[ih].FEBSN->size()<<std::endl;
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
            //cout <<endl<< "FEB "<< FEBs[iFEB]<< " mapping"<<endl;
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

    TH1F *CrosstalkEnergyDepositX = new TH1F("CrosstalkEnergyDepositX", "CrosstalkEnergyDepositX",500,0,500);
    TH1F *CrosstalkEnergyDepositY = new TH1F("CrosstalkEnergyDepositY", "CrosstalkEnergyDepositY",500,0,500);

    TDirectory *events2D = wfile.mkdir("events2D");
    TDirectory *CrossEnergy = wfile.mkdir("CrossEnergy");
    TDirectory *CrossStep = wfile.mkdir("CrossStep");
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
        event_XY[ih]->GetYaxis()->SetTitle("Y axis");
        event_XY[ih]->GetXaxis()->SetTitle("X axis");
    }

    TH2F *event_YZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "event_YZ_"+sEventnum.str();
        event_YZ[ih] = new TH2F(sEvent.c_str(),sEvent.c_str(), 48,0,48, 8,0,8);
        event_YZ[ih]->GetYaxis()->SetTitle("Y axis");
        event_YZ[ih]->GetXaxis()->SetTitle("Z axis");
    }

    TH2F *event_XZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++){
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "event_XZ_"+sEventnum.str();
        event_XZ[ih] = new TH2F(sEvent.c_str(),sEvent.c_str(), 24,0,24, 48,0,48);
        event_XZ[ih]->GetYaxis()->SetTitle("Z axis");
        event_XZ[ih]->GetXaxis()->SetTitle("X axis");
    }

    TH1F *energy_Z[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "energy_Z_"+sEventnum.str();
        energy_Z[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(),48,0,48);
    }
///////////Energy
    TH1F *energyZ_XZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "energyZ_XZ_"+sEventnum.str();
        energyZ_XZ[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(),48,0,48);
    }

    TH1F *energyZ_YZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "energyZ_YZ_"+sEventnum.str();
        energyZ_YZ[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(),48,0,48);
    }

    TH1F *energyX_XZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "energyX_XZ_"+sEventnum.str();
        energyX_XZ[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(),24,0,24);
    }

    TH1F *energyY_YZ[NumberEvDis];
    for (Int_t ih=0; ih < NumberEvDis;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "energyY_YZ"+sEventnum.str();
        energyY_YZ[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(),8,0,8);
    }
////////////////////////
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
    Double_t energyDepZ[48];
    Double_t energyDepZ_XZ[48];
    Double_t energyDepZ_YZ[48];
    Double_t energyDepX_XZ[24];
    Double_t energyDepY_YZ[8];

    Double_t StepX_XZ[24];
    Double_t StepY_YZ[8];
    Double_t StepZ_XZ[48];
    Double_t StepZ_YZ[48];
    Double_t StepZ[48];
    Int_t eventNum=0;

    int licznik=1;
    bool LargehitTimeDif = 0;

    TCanvas *DisplayCanvas = new TCanvas("DisplayCanvas","DisplayCanvas", 1480, 1160);
    TCanvas *CrossEnergyCanvas = new TCanvas("CrossEnergyCanvas","CrossEnergyCanvas", 1480, 1160);
    TCanvas *CrossHitCanvas = new TCanvas("CrossHitCanvas","CrossHitCanvas", 1480, 1160);
    bool SpillMised = false;
    for (Int_t subSpill = 0; subSpill<minEn; subSpill++)
    {
    //for (Int_t subSpill = 0; subSpill<10; subSpill++) {
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
            //cout << "FEB_"<< FEBs[ik]<< " "<< FEB[FEBs[ik]].hitCharge_pe->size()<<endl;
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

                    StepZ_XZ[ik] = 0;
                    StepZ_YZ[ik] = 0;
                    StepZ[ik] = 0;
                }
                for (int ik = 0; ik < 24; ik++ ) //zerowanie tablic przechowujace dane, X
                {
                    energyDepX_XZ[ik] = 0;
                    StepX_XZ[ik] = 0;
                }
                for (int ik = 0; ik < 8; ik++ ) //zerowanie tablic przechowujace dane, X
                {
                    energyDepY_YZ[ik] = 0;
                    StepY_YZ[ik] = 0;
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
                            if ( FEBs[i] == 0 || FEBs[i] == 16) //Plaszczyzna XY
                            {
                                event_XY[eventNum]-> Fill( MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],FEB[FEBs[i]].hitCharge_pe->at(check) );
                                EventsMap_XY->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],1);
                            }
                            else if ( FEBs[i] == 1 || FEBs[i] == 2 || FEBs[i] == 17 || FEBs[i] ==  24) //Plaszczyzna YZ
                            {
                                event_YZ[eventNum]->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)], MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],FEB[FEBs[i]].hitCharge_pe->at(check));
                                EventsMap_YZ->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],1);

                                if (FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000)// zmiana 0 and 10000
                                {
                                    energyDepZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                    energyDepZ_YZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                    energyDepY_YZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);

                                    StepZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += 1;
                                    StepZ_YZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += 1;
                                    StepY_YZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += 1;
                                }
                            }
                            else //Plaszczyzna XZ
                            {
                                event_XZ[eventNum]->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],FEB[FEBs[i]].hitCharge_pe->at(check)); /////////////////////////////
                                EventsMap_XZ->Fill(MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],1);

                                if (FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000) //zmiana 0 and 10000
                                {
                                    energyDepZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                    energyDepZ_XZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                    energyDepX_XZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);

                                    StepZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += 1;
                                    StepZ_XZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += 1;
                                    StepX_XZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += 1;
                                }
                            }
                        }
                    }
                }
            }

            int StoppingParticle = 0; //ciecie usuwajace czastki które sie nie zatrzymaly
            if(energyDepZ[47]==0)
            {
                StoppingParticle=1;
            }
            double PeakEnergy=0;
            int PeakNumber=0;

            double HighestEnergyY=0;
            int HighestEnergyNumberY=0;

            double HighestEnergyX=0;
            int HighestEnergyNumberX=0;

            for (int ik = 0; ik < 48; ik++ )
            {
                energy_Z[eventNum]->Fill(ik,energyDepZ[ik]);
                energyZ_XZ[eventNum]->Fill(ik,energyDepZ_XZ[ik]);
                energyZ_YZ[eventNum]->Fill(ik,energyDepZ_YZ[ik]);

                StepCounterZ[eventNum]->Fill(ik,StepZ[ik]);
                StepCounterZ_XZ[eventNum]->Fill(ik,StepZ_XZ[ik]);
                StepCounterZ_YZ[eventNum]->Fill(ik,StepZ_YZ[ik]);
                if(energyDepZ[ik]>PeakEnergy)
                {
                    PeakEnergy=energyDepZ[ik];
                    PeakNumber=ik;
                }
            }
            for (int ik = 0; ik < 24; ik++ )
            {
                energyX_XZ[eventNum]->Fill(ik,energyDepX_XZ[ik]);
                StepCounterX_XZ[eventNum]->Fill(ik,StepX_XZ[ik]);
                if(energyDepX_XZ[ik]>HighestEnergyX)
                {
                    HighestEnergyX=energyDepX_XZ[ik];
                    HighestEnergyNumberX=ik;
                }
            }

            for (int ik = 0; ik < 8; ik++ )
            {
                energyY_YZ[eventNum]->Fill(ik,energyDepY_YZ[ik]);
                StepCounterY_YZ[eventNum]->Fill(ik,StepY_YZ[ik]);
                if(energyDepY_YZ[ik]>HighestEnergyY)
                {
                    HighestEnergyY=energyDepY_YZ[ik];
                    HighestEnergyNumberY=ik;
                }
            }

            int DiscontinuityCut=0; // maximally two layers before peak can have 0 deposit
            if(PeakNumber>3)
            {
                if(energyDepZ[PeakNumber-1]!=0 || energyDepZ[PeakNumber-2]!=0 || energyDepZ[PeakNumber-3]!=0)
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

                                    if (MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] == PeakNumber && FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000)// zmiana 0 and 10000
                                    {
                                    CrosstalkEnergyDepositY->Fill( FEB[FEBs[i]].hitCharge_pe->at(check) );
                                    }
                                }
                                else //Plaszczyzna XZ
                                {
                                    if(MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] == PeakNumber && FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000) //zmiana 0 and 10000
                                    {
                                    CrosstalkEnergyDepositX->Fill( FEB[FEBs[i]].hitCharge_pe->at(check) );
                                    }
                                }
                            }
                        }
                    }
                }

            }


            if(LargehitTimeDif == 0 && StoppingParticle==1 && PeakEnergy>250 && DiscontinuityCut==1 && TrackBeginningCut==1 && BorderCutY==1 && sigma < 2)
            {

                cout <<"licznik "<<licznik <<" sigma " << sigma <<endl;
                licznik++;

                DisplayCanvas->Clear();
                CrossEnergyCanvas->Clear();
                CrossHitCanvas->Clear();
                //if (event_XZ[eventNum]->GetEntries()>10)
                //{
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

            //}
        }
        delete event_XY[eventNum];
        delete event_YZ[eventNum];
        delete event_XZ[eventNum];
        delete energy_Z[eventNum];

        delete energyX_XZ[eventNum];
        delete energyY_YZ[eventNum];
        delete energyZ_XZ [eventNum];
        delete energyZ_YZ[eventNum];

        delete StepCounterX_XZ[eventNum];
        delete StepCounterY_YZ[eventNum];
        delete StepCounterZ[eventNum];
        delete StepCounterZ_XZ[eventNum];
        delete StepCounterZ_YZ[eventNum];

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

    CrosstalkEnergyDepositX->Write();
    CrosstalkEnergyDepositY->Write();

    wfile.Close();


    FileInput->Close();
    return 0;
}
