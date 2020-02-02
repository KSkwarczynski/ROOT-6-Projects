//
//
// César Jesús-Valls    (cjesus@ifae.es)
// Kamil Skwarczyński   (kamil.janusz.skwarczynski@cern.ch)
//

#define THIS_NAME VertexActivity
#define NOINTERACTIVE_OUTPUT           
#define OVERRIDE_OPTIONS 

#include "../src/tools/global_header.hh"

//____DEFINE_GLOBAL_SCOPE_VARIABLES____: this needs to be declared before global_tools!
bool    batch          = false;
bool    IsMC           = true; 
int     maxEvents      = std::numeric_limits<int>::max();;
int     maxSelEvents   = std::numeric_limits<int>::max();;
int     selEvents      = 0;
float   start_time     = clock();
bool    RM_CROSSTALK   = false;
bool    SHOW_TRUE      = true;
bool    SHOW_RECO      = true;
TString fileOut        = "/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/Output/VertexAcivity_Output.root";
TString fileIn         = "/mnt/home/kskwarczynski/t2k-nd280-upgrade/Output/Reconstructed_SFGD_MC_0.root"; //VertexActInput SubstractedReco_SFGD_MC_0
int IsPrototype        = false;
int SFGD_X             = 204;
int SFGD_Y             = 56;
int SFGD_Z             = 188;
bool useClean          = false;
bool useNN             = false;
int dTimeIni           = -100;
int dTimeFin           = -100;
int evtIni             = 0;
int evtFin             = 0;

TFile*          FileInput;
TFile*          FileOutput;
TTree*          dataOut;
TTree*          data;
ND280SFGDEvent* inputEvent;
ND280SFGDEvent* recoEvent;
TBranch*        recoBranch; 
TBranch*        inputBranch;
int             nEvents;
Event*          unpackEvent;

#include "../src/tools/global_tools.cc" 
#include "../src/tools/reconstruction_methods.hh" 

void VertexActivity() 
{
    parseArguments();
    linkFilesToTTrees();

    std::vector<ND280SFGDHit*> mppc_hits;
        
    TString VertexName[5]={"VertexActivity1x1x1", "VertexActivity3x3x3", "VertexActivity5x5x5", "VertexActivity7x7x7", "VertexActivity9x9x9"};
    TString VertexNameShifted[3]={"X", "Y", "Z"};
    TString VetrexString[5]={"1x1x1" , "3x3x3" , "5x5x5", "7x7x7", "9x9x9"};
    
    double VertexBox[5]={0., 1., 2., 3., 4.}; // 1x1x1, 3x3x3, 5x5x5 and so on...
    int VAshiftVector[2]={1, -1}; //Adjust position of vertex
    const int SizeOfShiftVector= (sizeof(VAshiftVector)/sizeof(*VAshiftVector));
    
    TH1*  h_nuMom = new TH1F("h_nuMom", "h_nuMom", 50,0,6000);
    
    TH1F *hVertexActivity[5];
    TH1F *hVertexActivityShell[4];
    TH1F *hVertexActivityShifted[SizeOfShiftVector][3][5]; // Which array represent what [VAshiftVector][X,Y,Z][VetrexString]
    
    for(int ik=0; ik<5; ik++)
    {
        hVertexActivity[ik] = new TH1F(VertexName[ik], VertexName[ik], 50, 0, 4000+ik*2500);  
        hVertexActivity[ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
        
        if(ik>0)
        {
            hVertexActivityShell[ik-1] = new TH1F( Form("%sShell",VertexName[ik].Data()) , Form("%sShell",VertexName[ik].Data()), 50, 0, 4000+ik*2500);  
            hVertexActivityShell[ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
        }
        for(int ig=0; ig<3; ig++)
        {
            for(int ih=0; ih<SizeOfShiftVector; ih++)
            {
                hVertexActivityShifted[ih][ig][ik] = new TH1F( Form("%sShifted_%d_%s",VertexName[ik].Data(), VAshiftVector[ih], VertexNameShifted[ig].Data()) ,Form("%sShifted_%d_%s",VertexName[ik].Data(), VAshiftVector[ih] ,VertexNameShifted[ig].Data()), 50, 0, 4000+ik*2500);  
                hVertexActivityShifted[ih][ig][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
            }
        }
    }
    
    TH2F *hMomentumVsRange[3];
    TH2F *hEenrgyVsRange[3];
    TH2F *hEenrgyVsRangeRestricted[3];
    TH2F *hEenrgyPeVsRange[3];
    TString ParticleName[3]={"Muon", "Proton", "Pion"};
    for(int ik=0; ik<3; ik++)
    {
        hMomentumVsRange[ik] = new TH2F( Form("MomentumVsRange_%s", ParticleName[ik].Data()), Form("MomentumVsRange_%s", ParticleName[ik].Data()),50., 0., 5000., 50., 0., 300.);  
        hMomentumVsRange[ik]->GetXaxis()->SetTitle("True Momentum [MeV/c]");
        hMomentumVsRange[ik]->GetYaxis()->SetTitle("Range [cm]");
        
        hEenrgyVsRange[ik] = new TH2F( Form("EnergyVsRange_%s", ParticleName[ik].Data()), Form("EnergyVsRange_%s", ParticleName[ik].Data()),50., 0., 1000., 50., 0., 300.);  
        hEenrgyVsRange[ik]->GetXaxis()->SetTitle("Energy [MeV???]");
        hEenrgyVsRange[ik]->GetYaxis()->SetTitle("Range [cm]");
        
        hEenrgyVsRangeRestricted[ik] = new TH2F( Form("EnergyVsRange_Restricted_%s", ParticleName[ik].Data()), Form("EnergyVsRange_Restricted_%s", ParticleName[ik].Data()),50., 0., 1000., 50., 0., 300.);  
        hEenrgyVsRangeRestricted[ik]->GetXaxis()->SetTitle("Energy [MeV???]");
        hEenrgyVsRangeRestricted[ik]->GetYaxis()->SetTitle("Range [cm]");
        
        hEenrgyPeVsRange[ik] = new TH2F( Form("EnergyPeVsRange_%s", ParticleName[ik].Data()), Form("EnergyPeVsRange_%s", ParticleName[ik].Data()),50., 0., 1000., 50., 0., 300.);  
        hEenrgyPeVsRange[ik]->GetXaxis()->SetTitle("Energy [p.e./100]");
        hEenrgyPeVsRange[ik]->GetYaxis()->SetTitle("Range [cm]");
    }
    
    cout<< "\033[1;34mNumber of all events\033[0m"<<evtFin<<endl;

    TTree t1("t1","Tree");    
    Float_t VertexBranch[2];
    t1.Branch("VertexBranch1x1x1", &VertexBranch[0], "VertexBranch1x1x1/F");
    t1.Branch("VertexBranch3x3x3", &VertexBranch[1], "VertexBranch3x3x3/F");
    
    t1.SetDirectory(FileOutput);
    for (int iev=evtIni; iev<evtFin; iev++)
    {
        if(iev == maxEvents-1 or selEvents >= maxSelEvents) 
        //if(iev == maxEvents-1 or selEvents >= 3) //DEBUG MODE
        {   
            break;
        }
        
        mppc_hits = getEventMPPChits(iev); 
        
        // looking for vertex position
        convertVtxCoordiantes(inputEvent->GetTrueVertex());
        convertCoordinates(inputEvent->GetVoxels());

        recoEvent->SetHits(MergeHits(mppc_hits,0,true));
        recoEvent->SetVoxels(HitsToVoxels(recoEvent->GetHits(),0));
        FillTrueInformationInRecoEvent(inputEvent,recoEvent,0);
        
        ND280SFGDVoxel* trueVertex;
        trueVertex = inputEvent->GetTrueVertex();
        
        double VertexPosition[3]={}; //X-position, Y-position, Z-position
        VertexPosition[0] = trueVertex->GetX();
        VertexPosition[1] = trueVertex->GetY();
        VertexPosition[2] = trueVertex->GetZ();
        cout<<selEvents+1<<" Vertex position  X "<<VertexPosition[0]<<" Y "<< VertexPosition[1] <<" Z "<< VertexPosition[2]<<endl;
        
        double VertexDeposit[5]={}; //[VertexBox]
        double VertexDepositShifted[SizeOfShiftVector][3][5]={}; //[VAshiftVector][X,Y,Z][VertexBox]
        
        bool VetrexInDetector=true; //sometimes vertex is outside  detector boundries
        int FiducialVolume=1; //set how far from detector boundries we want to study Vertex Activity 
        if( VertexPosition[0]<FiducialVolume ||  VertexPosition[1]<FiducialVolume || VertexPosition[2]<FiducialVolume || VertexPosition[0]>SFGD_X-FiducialVolume ||  VertexPosition[1]>SFGD_Y-FiducialVolume || VertexPosition[2]>SFGD_Z-FiducialVolume)
        {
            VetrexInDetector=false;
            cout<<"\033[1;31mOut of detector FV\033[0m"<<endl;
        }
        if(!VetrexInDetector) continue;
        
        double VertexDepositCheck=0;
        for(auto AB:inputEvent->GetVoxels())
        { 
            if( abs(VertexPosition[0]-AB->GetX() )<= 0 && abs(VertexPosition[1]-AB->GetY())<= 0 && abs(VertexPosition[2]-AB->GetZ() )<= 0)
            {
                VertexDepositCheck+=AB->GetTruePE();
            }
        }
        /*
        if(VertexDepositCheck<1.)
        {
            cout<<"\033[1;31mNo deposit in vertex\033[0m"<<endl;
            continue;
        }  
        */
        double TrackParameters[4]={};
        int MuonCounter=0;
        for(auto t:inputEvent->GetTrueTracks()) 
        {
            if( t->GetPDG() == 13 && t->GetParentID()==0)
            {
                cout<<"True track PDG= "<<t->GetPDG()<<" range "<<t->GetMaxEuclDist()<<" mom "<<t->GetMomentum()<<" cosTheta "<<t->GetCosTheta()<<endl;
                if(MuonCounter==0 || t->GetMomentum()>TrackParameters[1]) //in case there are two muons we want with higher momentum
                {
                    TrackParameters[0]=t->GetMaxEuclDist();
                    TrackParameters[1]=t->GetMomentum();
                    TrackParameters[2]=t->GetCosTheta();
                }
                MuonCounter++;
            }
        }
        if(MuonCounter==0)
        {
            cout<<"\033[1;31mNo muon from vertex\033[0m"<<endl;
            continue;
        } 
        //std::vector<double> TrackRange;
        //std::vector<int> TrackID;
        double Edep=0;
        double EdepPE=0;
        int ParticlePDG[3]={13, 211, 2212};
        for(auto t:inputEvent->GetTrueTracks())
        {
            for(int ik=0; ik<3; ik++)
            {
                if(abs(t->GetPDG()) == ParticlePDG[ik] && t->GetParentID()==0) //muon
                {
                    hMomentumVsRange[ik]->Fill(t->GetMomentum(), t->GetMaxEuclDist() );
                    for(auto voxel:inputEvent->GetVoxels())
                    { 
                        //cout<<"track id "<<t->GetTrackID()<<" voxelid "<< voxel->GetTrueTrackIDs()[0]<<"  PDG "<<voxel->GetTruePDGs()[0]<<endl;
                        if(voxel->GetTrueTrackIDs()[0] == t->GetTrackID()) {Edep+=voxel->GetTrueEdep(); EdepPE+=voxel->GetTruePE();}
                    }
                    hEenrgyVsRange[ik]->Fill(Edep, t->GetMaxEuclDist() );
                    hEenrgyPeVsRange[ik]->Fill(EdepPE/100, t->GetMaxEuclDist() );
                    
                    if(t->GetCosTheta()>0.7 || t->GetCosTheta()<-0.7) hEenrgyVsRangeRestricted[ik]->Fill(Edep, t->GetMaxEuclDist() );
                    Edep=0;
                    EdepPE=0;
                }
            }
        }
        
        for(auto voxel:inputEvent->GetVoxels())
        {   
            for(int ik=0; ik<5; ik++)
            {
                //A->DistToVoxel(B);
                bool StudiedShape[3]={}; //[X, Y, Z]
                if( abs(VertexPosition[0]-voxel->GetX() ) <= VertexBox[ik]) StudiedShape[0]=true;
                if( abs(VertexPosition[1]-voxel->GetY() ) <= VertexBox[ik]) StudiedShape[1]=true;
                if( abs(VertexPosition[2]-voxel->GetZ() ) <= VertexBox[ik]) StudiedShape[2]=true;                
                if(StudiedShape[0] && StudiedShape[1]&& StudiedShape[2])
                {
                    VertexDeposit[ik]+=voxel->GetTruePE();
                }
                bool StudiedShapeShifted[SizeOfShiftVector][3]={}; //[VAshiftVector][X, Y, Z]
                for(int ih=0; ih<SizeOfShiftVector; ih++)
                {
                    if( abs(VertexPosition[0]+VAshiftVector[ih]-voxel->GetX() ) <= VertexBox[ik]) StudiedShapeShifted[ih][0]=true;
                    if( abs(VertexPosition[1]+VAshiftVector[ih]-voxel->GetY() ) <= VertexBox[ik]) StudiedShapeShifted[ih][1]=true;
                    if( abs(VertexPosition[2]+VAshiftVector[ih]-voxel->GetZ() ) <= VertexBox[ik]) StudiedShapeShifted[ih][2]=true;
                
                    if(StudiedShapeShifted[ih][0] && StudiedShape[1] && StudiedShape[2]) //Shifted in X
                    {
                        VertexDepositShifted[ih][0][ik]+=voxel->GetTruePE();
                    }
                    if(StudiedShape[0] && StudiedShapeShifted[ih][1] && StudiedShape[2]) //Shifted in Y
                    {
                        VertexDepositShifted[ih][1][ik]+=voxel->GetTruePE();
                    }
                    if(StudiedShape[0] && StudiedShape[1] && StudiedShapeShifted[ih][2]) //Shifted in Z
                    {
                        VertexDepositShifted[ih][2][ik]+=voxel->GetTruePE();
                    }
                }
            }
        }
        double nuMom = inputEvent->GetNuMom();
        h_nuMom->Fill(nuMom);
        for(int ik=0; ik<5; ik++)
        {
            hVertexActivity[ik]->Fill(VertexDeposit[ik]); 
            if(ik<2) VertexBranch[ik]=VertexDeposit[ik];
            if(ik>0) hVertexActivityShell[ik-1]->Fill(VertexDeposit[ik]-VertexDeposit[ik-1]);
            for(int ih=0; ih<SizeOfShiftVector; ih++)
            {
                for(int ig=0; ig<3; ig++)
                {
                    hVertexActivityShifted[ih][ig][ik]->Fill(VertexDepositShifted[ih][ig][ik]);
                }
            }
        }
        
        cout<<"  DEBUG !!! "<<VertexBranch[0]<<endl;
        t1.Fill();
        selEvents++;
    }
    
    if (FileOutput->IsOpen())
    {
        FileOutput->cd();
        
        h_nuMom->Write("",TObject::kOverwrite); 
        for(int ik=0; ik<5; ik++) //// Could be in one loop but for convinience in reading output file this is advisable
        {
            hVertexActivity[ik]->Write("",TObject::kOverwrite); 
        }
        for(int ik=0; ik<4; ik++)
        {
            hVertexActivityShell[ik]->Write("",TObject::kOverwrite); 
        }
        for(int ik=0; ik<3; ik++)
        {
            hMomentumVsRange[ik]->Write("",TObject::kOverwrite);
        }
        for(int ik=0; ik<3; ik++)
        {
            hEenrgyVsRange[ik]->Write("",TObject::kOverwrite);
        }
        for(int ik=0; ik<3; ik++)
        {
            hEenrgyPeVsRange[ik]->Write("",TObject::kOverwrite);
        }
        for(int ik=0; ik<3; ik++)
        {
            hEenrgyVsRangeRestricted[ik]->Write("",TObject::kOverwrite);
        }
        for(int ik=0; ik<5; ik++)
        {
            for(int ih=0; ih<SizeOfShiftVector; ih++)
            {
                for(int ig=0; ig<3; ig++)
                {
                    hVertexActivityShifted[ih][ig][ik]->Write("",TObject::kOverwrite); 
                }
            }
        }
        t1.Write();
        FileOutput->Close();
    }    
    cout << endl << "\033[1;32mGenerated output: \033[0m" << fileOut.Data() << endl;
    handleEndOfExecution();
}
