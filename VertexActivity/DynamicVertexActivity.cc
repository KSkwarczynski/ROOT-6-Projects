//
//
// César Jesús-Valls    (cjesus@ifae.es)
// Kamil Skwarczyński   (kamil.janusz.skwarczynski@cern.ch)
//

#define THIS_NAME DynamicVertexActivity
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
TString fileOut        = "/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/Output/DynamicVertexAcivity_Output.root";
TString fileIn         = "/mnt/home/kskwarczynski/t2k-nd280-upgrade/Output/Reconstructed_SFGD_MC_0.root"; //VertexActInput SubtractedReco_SFGD_MC_0
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

void DynamicVertexActivity() 
{
    parseArguments();
    linkFilesToTTrees();

    bool VERBOSE = true;
    std::vector<ND280SFGDHit*> mppc_hits;
        
    TString VertexName[5]={"VertexActivity1x1x1", "VertexActivity3x3x3", "VertexActivity5x5x5", "VertexActivity7x7x7", "VertexActivity9x9x9"};
    TString StringBox[3]={"Downstream", "Transverse", "Upstream"};
    TString ParticleName[3]={"Muon", "Pion+", "Proton"};
    TString VetrexString[5]={"1x1x1" , "3x3x3" , "5x5x5", "7x7x7", "9x9x9"};
    TString TrackLenght[2]={"Short", "Long"};
    
    TDirectory *FolderCut = FileOutput->mkdir("FolderCut");
    TDirectory *FolderSubtractedTrackLengthAll = FileOutput->mkdir("FolderSubtractedTrackLengthAll");
    TDirectory *FolderShift = FileOutput->mkdir("FolderShift");
    TDirectory *FolderSubtractedTrackLengthAllShell = FileOutput->mkdir("FolderSubtractedTrackLengthAllShell");
         
    //double VertexBox[5]={0., 1., 2., 3., 4.}; // 1x1x1, 3x3x3, 5x5x5 and so on...
    double VertexBoxNew[5]={0.5, 1.5, 2.5, 3.5, 4.5}; // used in Dynamic boxes
    
    const int SizeOfParticleVector = (sizeof(ParticleName)/sizeof(*ParticleName));
    const int ParticleNumberGO = 3; //Number of particles we put condition on, starting from 0
    const int AsymetricBox = 3;
    int FiducialVolume=3; //set how far from detector boundries we want to study Vertex Activity
    int ParticleNumberCut[7]={0, 1, 2, 3, 4, 5, 6};
    int ParticlePDG[SizeOfParticleVector]={13, 211, 2212}; //muon, pion+, proton
    double ShortTrack = 3.0;      //threshold for short tracks
    double epsilon = 0.0001;     // value neccesary for comparing floating numbers
    int LongOrShort = 1;        //Set if you are interested in subtracting long and short [0] or just long [1]

    TH1F *hVertexActivityDynamicCategory[AsymetricBox][5]; //[vertexboxShape][vertexBox]
    TH1F *hVertexActivityParticleCuts[AsymetricBox][SizeOfParticleVector-1][ParticleNumberGO][5]; // [vertexboxShape][particle][condition][vertexBox]
    TH1F *hVertexActivityDynamicCategoryShell[AsymetricBox][4]; //[vertexboxShape][vertexBox]
    
    TH1F *hVertexActivitySubTrackLengtAllCondition[AsymetricBox][2][5]; 
    TH1F *hVertexActivityOnlyIfTrackLenghtAll[AsymetricBox][2][5]; //[vertexboxShape][0-short, long][vertexBox]
    
    TH1F *hVertexActivitySubTrackLengtAllConditionShell[AsymetricBox][2][4]; 
    TH1F *hVertexActivityOnlyIfTrackLenghtAllShell[AsymetricBox][2][4]; //[vertexboxShape][0-short, long][vertexBox]
    TH1F *hVertexActivityOnlyLongShell[AsymetricBox][4]; //[vertexBox-1] //ZAMIEN VA NA STEP
    
    for(int ik=0; ik<5; ik++)
    {
        for(int ib=0; ib<AsymetricBox; ib++) //loop over box shape
        {
            hVertexActivityDynamicCategory[ib][ik] = new TH1F( Form("Step%iDynamic_Cat%s", ik ,StringBox[ib].Data()) , Form("Step%iDynamic_Cat%s", ik ,StringBox[ib].Data()), 50, 0, 4000+ik*3000);  
            hVertexActivityDynamicCategory[ib][ik]->GetXaxis()->SetTitle( Form("Energy deposit in step %i box [p.e.]", ik ) );
            if(ik>0)
            {
                hVertexActivityDynamicCategoryShell[ib][ik-1] = new TH1F( Form("Step%iDynamic_Cat%s_Shell", ik ,StringBox[ib].Data()) , Form("Step%iDynamic_Cat%s_Shell", ik ,StringBox[ib].Data()), 50, 0, 2000);  
                hVertexActivityDynamicCategoryShell[ib][ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in step %i box [p.e.]", ik ) );
                if(ik>0)
                {
                    hVertexActivityOnlyLongShell[ib][ik-1] = new TH1F( Form("%s_%s_Shell_OnlyLong",VertexName[ik].Data(), StringBox[ib].Data()) , Form("%s_%s_Shell_OnlyLong",VertexName[ik].Data(), StringBox[ib].Data()), 50, 0, 2000);
                    hVertexActivityOnlyLongShell[ib][ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in step %i box [p.e.]", ik ) );
                    
                }
            }
            for(int ih=0; ih<ParticleNumberGO; ih++)
            {
                for(int ig=0; ig<SizeOfParticleVector-1; ig++)
                {
                    hVertexActivityParticleCuts[ib][ig][ih][ik] = new TH1F( Form("Step%i_%s_IfNumOf_%s=%i", ik, StringBox[ib].Data(), ParticleName[ig+1].Data(), ih) , Form("Step%i_%s_IfNumOf_%s=%i", ik, StringBox[ib].Data(), ParticleName[ig+1].Data(), ih), 50, 0, 4000+ik*3000);  
                    hVertexActivityParticleCuts[ib][ig][ih][ik]->GetXaxis()->SetTitle( Form("Energy deposit in step %i box [p.e.]", ik ) );
                }
            }
            for(int il=0; il<2; il++) //loop over short long track
            {
                hVertexActivitySubTrackLengtAllCondition[ib][il][ik] = new TH1F( Form("Step%i_%s_SubCondition_%s_All", ik, StringBox[ib].Data(), TrackLenght[il].Data()), Form("Step%i_%s_SubCondition_%s_All", ik, StringBox[ib].Data(), TrackLenght[il].Data()), 50, 0, 4000+ik*3000);  
                hVertexActivitySubTrackLengtAllCondition[ib][il][ik]->GetXaxis()->SetTitle( Form("Energy deposit in step %i box [p.e.]", ik ) );
                    
                hVertexActivityOnlyIfTrackLenghtAll[ib][il][ik] = new TH1F( Form("Step%i_%s_IfThereAre_%s_All", ik, StringBox[ib].Data(), TrackLenght[il].Data()), Form("Step%i_%s_IfThereAre_%s_All", ik, StringBox[ib].Data(), TrackLenght[il].Data()), 50, 0, 4000+ik*3000);  
                hVertexActivityOnlyIfTrackLenghtAll[ib][il][ik]->GetXaxis()->SetTitle( Form("Energy deposit in step %i box [p.e.]", ik ) );
                
                if(ik>0)
                {
                    hVertexActivitySubTrackLengtAllConditionShell[ib][il][ik-1] = new TH1F( Form("Step%i_%s_SubCondition_%s_All_Shell", ik, StringBox[ib].Data(), TrackLenght[il].Data()), Form("Step%i_%s_SubCondition_%s_All_Shell", ik, StringBox[ib].Data(), TrackLenght[il].Data()), 50, 0, 2000);  
                    hVertexActivitySubTrackLengtAllConditionShell[ib][il][ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in step %i box [p.e.]", ik ) );
                    
                    hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][ik-1] = new TH1F( Form("Step%i_%s_IfThereAre_%s_All_Shell", ik, StringBox[ib].Data(), TrackLenght[il].Data()), Form("Step%i_%s_IfThereAre_%s_All_Shell", ik, StringBox[ib].Data(), TrackLenght[il].Data()), 50, 0, 2000);  
                    hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in step %i box [p.e.]", ik ) );
                    
                }
            }
        }
    }
    int DirtyTrick[5]={};
    DirtyTrick[0]=1;
    
    TTree t1("t1","Tree");    
    Float_t VertexBranch[3][5];
    for(int ib=0; ib<AsymetricBox; ib++)
    {
        for(int ik=0; ik<5; ik++)
        {
            t1.Branch( Form("VertexBranch%s%s", StringBox[ib].Data() , VetrexString[ik].Data() ), &VertexBranch[ib][ik], Form("VertexBranch%s%s/F", StringBox[ib].Data() , VetrexString[ik].Data() ) );
        }
    }
    t1.SetDirectory(FileOutput);
    
    cout<< "\033[1;34mNumber of all events\033[0m"<<evtFin<<endl;
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
        if(VERBOSE) cout<<selEvents+1<<" Vertex position  X "<<VertexPosition[0]<<" Y "<< VertexPosition[1] <<" Z "<< VertexPosition[2]<<endl;

        //double VertexDepositDynamic[5]={}; //[VertexBox]
        double VertexDepositDynamicCategory[AsymetricBox][5][2]={}; //[Dynamic box shape]VertexBox][0-p.e., 1-MeV]
        double VertexDepositSubtractedLengthAll[AsymetricBox][2][5][2]={}; //[Dynamic box shape][0-short, 1-long][VertexBox][0-PE, 1-MeV]
        
        int CounterDepositDynamicCategory[AsymetricBox][5]={}; //[VertexBox] TODO narazie nie ma celu moze w przyszlosci, ma liczyć zliczenia kostki aby normalizować
        
        bool VetrexInDetector=true; //sometimes vertex is outside  detector boundries 
        if( VertexPosition[0]<FiducialVolume ||  VertexPosition[1]<FiducialVolume || VertexPosition[2]<FiducialVolume || VertexPosition[0]>SFGD_X-FiducialVolume ||  VertexPosition[1]>SFGD_Y-FiducialVolume || VertexPosition[2]>SFGD_Z-FiducialVolume)
        {
            VetrexInDetector=false;
          if(VERBOSE)  cout<<"\033[1;31mOut of detector FV\033[0m"<<endl;
        }
        if(!VetrexInDetector) continue;
        int MuonCounter=0;
        for(auto t:inputEvent->GetTrueTracks()) 
        {
            if( t->GetPDG() == 13 && t->GetParentID()==0 && t->GetMaxEuclDist()>ShortTrack)
            {
                MuonCounter++;
            }
        }
        if(MuonCounter==0)
        {
           if(VERBOSE) cout<<"\033[1;31mNo muon from vertex\033[0m"<<endl;
            continue;
        }
        std::vector<int> TrackIdLengthAll[2];
        for(auto t:inputEvent->GetTrueTracks())
        {
            TrackIdLengthAll[0].push_back( t->GetTrackID() );
            TrackIdLengthAll[1].push_back( t->GetTrackID() );
            //TODO moze da się to łądniej zrobić
            if(t->GetPDG() == ParticlePDG[0] || t->GetPDG() == ParticlePDG[1] || t->GetPDG() == ParticlePDG[2] || t->GetPDG() == -211) 
            {
                double TrackDistance=t->GetMaxEuclDist();
                if( TrackDistance <= ShortTrack )
                {
                    TrackIdLengthAll[0].pop_back();
                }
                if( TrackDistance > ShortTrack )
                {
                    TrackIdLengthAll[1].pop_back();
                }
            }
        }
        int ParticleCounter[SizeOfParticleVector]={}; // [0-muon, 1-pion, 2-proton]
        std::vector<int> ParticleTrackId[SizeOfParticleVector][2];//[particle of interes][0-original, 1-after scaterring]
        
        for(auto t:inputEvent->GetTrueTracks()) 
        {
            for(int ig=0; ig<SizeOfParticleVector; ig++) //loop over studied particles
            {
                if( t->GetPDG() == ParticlePDG[ig] && t->GetParentID()==0)
                {
                    int OutGoingCounter=0;
                    
                    double momentumTemp=0;
                    ParticleTrackId[ig][0].push_back(t->GetTrackID());
                    for(auto track:inputEvent->GetTrueTracks())
                    {
                        if(track->GetParentID()==t->GetTrackID() && track->GetPDG()==t->GetPDG())
                        {
                            if(OutGoingCounter==0)
                            {
                                ParticleTrackId[ig][1].push_back(track->GetTrackID());
                                momentumTemp=track->GetMomentum();
                            }
                            if(OutGoingCounter==1 && track->GetMomentum()>momentumTemp) //For two particles from scatering we want higher momentum one
                            {
                                ParticleTrackId[ig][1].at( ParticleTrackId[ig][1].size()-1 ) = track->GetTrackID();
                            }
                            OutGoingCounter++;
                        }
                    }
                    if(OutGoingCounter==0) ParticleTrackId[ig][1].push_back( -999 );
                    ParticleCounter[ig]++;
                }
            }
        }
        for(auto voxel:inputEvent->GetVoxels())
        {   
            for(int ik=0; ik<5; ik++)
            {
                bool StudiedShapeDynamic[AsymetricBox][3]={}; //["Downstream", "Transverse", "Upstream"][X, Y, Z]
                bool StudiedBoxCondition[AsymetricBox]={}; //["Downstream", "Transverse", "Upstream"]
                //"Downstream"
                if(voxel->GetX()<VertexPosition[0]+VertexBoxNew[ik]-1+DirtyTrick[ik] && voxel->GetX()>VertexPosition[0]-VertexBoxNew[ik]+1-DirtyTrick[ik]) StudiedShapeDynamic[0][0]=true;
                if(voxel->GetY()<VertexPosition[1]+VertexBoxNew[ik]-1+DirtyTrick[ik] && voxel->GetY()>VertexPosition[1]-VertexBoxNew[ik]+1-DirtyTrick[ik]) StudiedShapeDynamic[0][1]=true;
                if(voxel->GetZ()<VertexPosition[2]+VertexBoxNew[ik]+2 && voxel->GetZ()>VertexPosition[2]-VertexBoxNew[0]) StudiedShapeDynamic[0][2]=true;
                if(StudiedShapeDynamic[0][0] && StudiedShapeDynamic[0][1] && StudiedShapeDynamic[0][2]) StudiedBoxCondition[0]=true;
                //"Transverse"
                if(voxel->GetX()<VertexPosition[0]+VertexBoxNew[ik]+1 && voxel->GetX()>VertexPosition[0]-VertexBoxNew[ik]-1) StudiedShapeDynamic[1][0]=true;
                if(voxel->GetY()<VertexPosition[1]+VertexBoxNew[ik]+1 && voxel->GetY()>VertexPosition[1]-VertexBoxNew[ik]-1) StudiedShapeDynamic[1][1]=true;
                if(voxel->GetZ()<VertexPosition[2]+VertexBoxNew[ik]-1+DirtyTrick[ik] && voxel->GetZ()>VertexPosition[2]-VertexBoxNew[ik]+1-DirtyTrick[ik]) StudiedShapeDynamic[1][2]=true; 
                if(StudiedShapeDynamic[1][0] && StudiedShapeDynamic[1][1] && StudiedShapeDynamic[1][2]) StudiedBoxCondition[1]=true;
                //"Upstream"
                if(voxel->GetX()<VertexPosition[0]+VertexBoxNew[ik]-1+DirtyTrick[ik] && voxel->GetX()>VertexPosition[0]-VertexBoxNew[ik]+1-DirtyTrick[ik]) StudiedShapeDynamic[2][0]=true;
                if(voxel->GetY()<VertexPosition[1]+VertexBoxNew[ik]-1+DirtyTrick[ik]&& voxel->GetY()>VertexPosition[1]-VertexBoxNew[ik]+1-DirtyTrick[ik]) StudiedShapeDynamic[2][1]=true;
                if(voxel->GetZ()<VertexPosition[2]+VertexBoxNew[0] && voxel->GetZ()>VertexPosition[2]-VertexBoxNew[ik]-2) StudiedShapeDynamic[2][2]=true; 
                if(StudiedShapeDynamic[2][0] && StudiedShapeDynamic[2][1] && StudiedShapeDynamic[2][2]) StudiedBoxCondition[2]=true;
                
                for(int ib=0; ib<AsymetricBox; ib++)
                {
                    if(StudiedBoxCondition[ib])
                    {
                        VertexDepositDynamicCategory[ib][ik][0]+=voxel->GetTruePE();
                        VertexDepositDynamicCategory[ib][ik][1]+=voxel->GetTrueEdep();
                        if(voxel->GetTruePE()> epsilon) CounterDepositDynamicCategory[ib][ik]++;
                        
                        for(int io=0; io<2; io++) //loop over short long DrawTrueTracks
                        {
                            for(int il=0; il<TrackIdLengthAll[io].size(); il++)
                            {
                                if( voxel->GetTrueTrackIDs()[0]==TrackIdLengthAll[io].at(il) )
                                {
                                    VertexDepositSubtractedLengthAll[ib][io][ik][0]+=voxel->GetTruePE();
                                    VertexDepositSubtractedLengthAll[ib][io][ik][1]+=voxel->GetTrueEdep();
                                }
                            }
                        }
                    }
                }
            }
        }
        for(int ik=0; ik<5; ik++)
        {
            for(int ib=0; ib<AsymetricBox; ib++)
            {
                hVertexActivityDynamicCategory[ib][ik]->Fill(VertexDepositDynamicCategory[ib][ik][0]);
                VertexBranch[ib][ik]=VertexDepositDynamicCategory[ib][ik][0];
                
                if(ik>0)
                {
                    hVertexActivityDynamicCategoryShell[ib][ik-1]->Fill(VertexDepositDynamicCategory[ib][ik][0]-VertexDepositDynamicCategory[ib][ik-1][0]);
                }
                for(int ig=0; ig<SizeOfParticleVector-1; ig++) //loop over conditioned particle/ no muon(-1)
                {
                    for(int ih=0; ih<ParticleNumberGO; ih++) //how many given particle
                    {
                        if(ParticleCounter[ig+1]==ParticleNumberCut[ih]) hVertexActivityParticleCuts[ib][ig][ih][ik]->Fill(VertexDepositDynamicCategory[ib][ik][0]);
                    }
                }
                for(int il=0; il<2; il++)
                {
                    if( abs( VertexDepositDynamicCategory[ib][ik][0]-VertexDepositSubtractedLengthAll[ib][0][ik][0])> epsilon )
                    {
                        hVertexActivitySubTrackLengtAllCondition[ib][il][ik]->Fill( VertexDepositSubtractedLengthAll[ib][il][ik][0] );
                        hVertexActivityOnlyIfTrackLenghtAll[ib][il][ik]->Fill( VertexDepositDynamicCategory[ib][ik][0] ); 
                        
                        if(ik>0)
                        {
                            hVertexActivitySubTrackLengtAllConditionShell[ib][il][ik-1]->Fill( VertexDepositSubtractedLengthAll[ib][il][ik][0] - VertexDepositSubtractedLengthAll[ib][il][ik-1][0]);
                            hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][ik-1]->Fill( VertexDepositDynamicCategory[ib][ik][0] -  VertexDepositDynamicCategory[ib][ik-1][0]  );
                        }
                    }
                }
                if(ik>0 && abs( VertexDepositDynamicCategory[ib][ik][0]-VertexDepositSubtractedLengthAll[ib][0][ik][0])<= epsilon)
                {
                    hVertexActivityOnlyLongShell[ib][ik-1]->Fill(VertexDepositDynamicCategory[ib][ik][0]-VertexDepositDynamicCategory[ib][ik-1][0]);
                }
            }
        }
        t1.Fill();
        selEvents++;
    }
    
    if (FileOutput->IsOpen())
    {
        FileOutput->cd();
        for(int ik=0; ik<5; ik++)
        {
            for(int ib=0; ib<AsymetricBox; ib++)
            {
                hVertexActivityDynamicCategory[ib][ik]->Write("",TObject::kOverwrite); 
            }
        }
        for(int ik=0; ik<4; ik++)
        {
            for(int ib=0; ib<AsymetricBox; ib++)
            {
                hVertexActivityDynamicCategoryShell[ib][ik]->Write("",TObject::kOverwrite); 
            }
        }
        FolderCut->cd();
        for(int ik=0; ik<5; ik++)
        {
            for(int ib=0; ib<3; ib++)
            {
                for(int ig=0; ig<SizeOfParticleVector-1; ig++)
                {
                    for(int ih=0; ih<ParticleNumberGO; ih++)
                    {
                        hVertexActivityParticleCuts[ib][ig][ih][ik]->Write("",TObject::kOverwrite); 
                    }
                } 
            }
        }
        FolderSubtractedTrackLengthAll->cd();
        for(int ib=0; ib<AsymetricBox; ib++)
        {
            for(int il=LongOrShort; il<2; il++)
            {
                for(int ik=0; ik<5; ik++)
                {
                    hVertexActivitySubTrackLengtAllCondition[ib][il][ik]->Write("",TObject::kOverwrite); 
                }
                for(int ik=0; ik<5; ik++)
                {
                    hVertexActivityOnlyIfTrackLenghtAll[ib][il][ik]->Write("",TObject::kOverwrite); 
                }
            }
        }
        FolderSubtractedTrackLengthAllShell->cd();
        for(int ib=0; ib<AsymetricBox; ib++)
        {
            for(int il=LongOrShort; il<2; il++)
            {
                for(int ik=0; ik<4; ik++)
                {
                    hVertexActivitySubTrackLengtAllConditionShell[ib][il][ik]->Write("",TObject::kOverwrite); 
                }
                for(int ik=0; ik<4; ik++)
                {
                    hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][ik]->Write("",TObject::kOverwrite); 
                }
            }
            for(int ik=0; ik<4; ik++)
            {
                hVertexActivityOnlyLongShell[ib][ik]->Write("",TObject::kOverwrite); 
            }
        }
        FileOutput->cd();
        t1.Write();
        FileOutput->Close();
    }
    cout << endl << "\033[1;32mGenerated output: \033[0m" << fileOut.Data() << endl;
    handleEndOfExecution();
}
