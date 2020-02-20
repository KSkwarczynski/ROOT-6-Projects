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

void VertexActivity() 
{
    //TODO zrobic jakis oddzielny program/liste wczytujace stale parametry jak fiducial vollume itd
    parseArguments();
    linkFilesToTTrees();

    bool VERBOSE = true;
    std::vector<ND280SFGDHit*> mppc_hits;
        
    TString VertexName[5]={"VertexActivity1x1x1", "VertexActivity3x3x3", "VertexActivity5x5x5", "VertexActivity7x7x7", "VertexActivity9x9x9"};
    TString VertexNameShifted[3]={"X", "Y", "Z"};
    TString VetrexString[5]={"1x1x1" , "3x3x3" , "5x5x5", "7x7x7", "9x9x9"};
    TString ParticleName[3]={"Muon", "Pion+", "Proton"};
    TString ParticleNameBranch[3]={"Muon", "PionP", "Proton"};
    TString TrackLenght[2]={"Short", "Long"};
    
    TDirectory *FolderEnergyLoss = FileOutput->mkdir("FolderEnergyLoss");
    TDirectory *FolderEnergyLossNonZero = FileOutput->mkdir("FolderEnergyLossNonZero");
    TDirectory *FolderSubtracted = FileOutput->mkdir("FolderSubtracted");
    TDirectory *FolderSubtractedTrackLength = FileOutput->mkdir("FolderSubtractedTrackLength");
    TDirectory *FolderSubtractedTrackLengthCondition = FileOutput->mkdir("FolderSubtractedTrackLengthCondition");
    TDirectory *FolderSubtractedTrackLengthAll = FileOutput->mkdir("FolderSubtractedTrackLengthAll");
    TDirectory *FolderSubtractedTrackLengthAllShell = FileOutput->mkdir("FolderSubtractedTrackLengthAllShell");
    TDirectory *FolderShift = FileOutput->mkdir("FolderShift");
    TDirectory *FolderCut = FileOutput->mkdir("FolderCut");
    TDirectory *FolderGarbage = FileOutput->mkdir("FolderGarbage");
    TDirectory *Other = FileOutput->mkdir("Other");
    
    double VertexBox[5]={0., 1., 2., 3., 4.}; // 1x1x1, 3x3x3, 5x5x5 and so on...
    int VAshiftVector[2]={1, -1}; //Adjust position of vertex
    const int SizeOfShiftVector= (sizeof(VAshiftVector)/sizeof(*VAshiftVector));
    const int SizeOfParticleVector = (sizeof(ParticleName)/sizeof(*ParticleName));
    const int ParticleNumberGO = 3; //Number of particles we put condition on, starting from 0
    
    int ParticleNumberCut[7]={0, 1, 2, 3, 4, 5, 6};
    int ParticlePDG[SizeOfParticleVector]={13, 211, 2212}; //muon, pion+, proton
    double ShortTrack = 3.0;    //threshold for short tracks
    double epsilon = 0.0001;   // value neccesary for comparing floating numbers
    int FiducialVolume = 3;   //set how far from detector boundries we want to study Vertex Activity
    int LongOrShort = 1;     //Set if you are interested in subtracting long and short [0] or just long [1]
    
    TH1F *h_nuMom = new TH1F("h_nuMom", "h_nuMom", 50,0,6000);
    h_nuMom->GetXaxis()->SetTitle("MeV?");
    
    TH1F *hVertexActivity[5]; //[vertexBox]
    TH1F *hVertexActivityShell[4]; //[vertexBox-1]
    TH1F *hVertexActivitySubtractedParticle[SizeOfParticleVector][5]; //[substracted particle][vertexBox]
    TH1F *hVertexActivitySubTrackLengtParticle[2][SizeOfParticleVector][5]; //[0-short, long][substracted particle][vertexBox]
    TH1F *hVertexActivitySubTrackLengtParticleCondition[2][SizeOfParticleVector][5]; //[0-short, long][substracted particle][vertexBox]
    TH1F *hVertexActivityOnlyIfTrackLenght[2][SizeOfParticleVector][5]; //[0-short, long][substracted particle][vertexBox]
    
    TH1F *hVertexActivitySubTrackLengtAllCondition[2][5]; 
    TH1F *hVertexActivityOnlyIfTrackLenghtAll[2][5]; //[0-short, long][vertexBox]
    
    TH1F *hVertexActivitySubTrackLengtAllConditionShell[2][4]; 
    TH1F *hVertexActivityOnlyIfTrackLenghtAllShell[2][4]; //[0-short, long][vertexBox]
    TH1F *hVertexActivityOnlyLongShell[4]; //[vertexBox-1]
    
    TH1F *hEnergyDepoParticle[SizeOfParticleVector][5]; //[particle][vertexBox]
    TH1F *hEnergyDepoParticleWithCuts[ParticleNumberGO][2][SizeOfParticleVector][5]; //[condition][particle with cut][particle studied][vertexBox]
    TH1F *hEnergyDepoParticleNonZero[5]; //[vertexBox]
    TH1F *hEnergyDepoParticleWithCutsNonZero[ParticleNumberGO][2][SizeOfParticleVector-1][5]; //[condition][particle with cut][particle studied][vertexBox]
   
    TH1F *hVertexActivityShifted[SizeOfShiftVector][3][5]; // Which array represent what [VAshiftVector][X,Y,Z][VetrexString]
    TH1F *hVertexActivityParticleCuts[SizeOfParticleVector-1][ParticleNumberGO][5]; // [particle][condition][vertexBox]
    TH1F *hVertexActivityTrackLength[2][5]; //[0-no short track, 1-no long track][vertexBox] tyczy sie tylko trackow z wierzcholka!!!!
    
    TH1F *hMeanScatteringRange[SizeOfParticleVector]; //[particle]
    TH1F *hVertexActivityByGarbage[5]; //[vertexBox]
    TH1F *hGarbagePDG[5]; //[vertexBox]
    for(int ik=0; ik<5; ik++)
    {
        hVertexActivity[ik] = new TH1F(VertexName[ik], VertexName[ik], 50, 0, 4000+ik*3000);  
        hVertexActivity[ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
                
        hEnergyDepoParticleNonZero[ik] = new TH1F( Form("%sEnergyDepo_%s_NonZero", ParticleName[0].Data(), VetrexString[ik].Data()), Form("%sEnergyDepo_%s_NonZero", ParticleName[0].Data(), VetrexString[ik].Data() ), 40, 0, 40+30*ik );  
        hEnergyDepoParticleNonZero[ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [MeV?]", VetrexString[ik].Data() ) );
        
        hVertexActivityByGarbage[ik] = new TH1F( Form("VA%sByGarbage", VetrexString[ik].Data()), Form("VA%sByGarbage", VetrexString[ik].Data()) , 40, 0, 40+30*ik );  
        hVertexActivityByGarbage[ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [MeV?]", VetrexString[ik].Data() ) );
        
        hGarbagePDG[ik] = new TH1F( Form("VA%sGarbagePDG", VetrexString[ik].Data()), Form("VA%sGarbagePDG", VetrexString[ik].Data()) , 6000, -3000, 3000 );  
        hGarbagePDG[ik]->GetXaxis()->SetTitle("PDG");
        if(ik>0)
        {
            hVertexActivityShell[ik-1] = new TH1F( Form("%sShell",VertexName[ik].Data()) , Form("%sShell",VertexName[ik].Data()), 50, 0, 8000);  
            hVertexActivityShell[ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
            
            hVertexActivityOnlyLongShell[ik-1] = new TH1F( Form("%sShell_OnlyLong",VertexName[ik].Data()) , Form("%sShell_OnlyLong",VertexName[ik].Data()), 50, 0, 8000); 
            hVertexActivityOnlyLongShell[ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
        }
        for(int ig=0; ig<3; ig++)
        {
            for(int ih=0; ih<SizeOfShiftVector; ih++)
            {
                hVertexActivityShifted[ih][ig][ik] = new TH1F( Form("%sShifted_%d_%s",VertexName[ik].Data(), VAshiftVector[ih], VertexNameShifted[ig].Data()) ,Form("%sShifted_%d_%s",VertexName[ik].Data(), VAshiftVector[ih] ,VertexNameShifted[ig].Data()), 50, 0, 4000+ik*3000);  
                hVertexActivityShifted[ih][ig][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
            }
            hEnergyDepoParticle[ig][ik] = new TH1F( Form("%sEnergyDepo_%s", ParticleName[ig].Data(), VetrexString[ik].Data()), Form("%sEnergyDepo_%s", ParticleName[ig].Data(), VetrexString[ik].Data()), 40, 0, 40+30*ik);  
            hEnergyDepoParticle[ig][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [MeV?]",VetrexString[ik].Data() ) );
        }
        for(int ig=0; ig<SizeOfParticleVector; ig++)//loop over studied particle
        {
            hVertexActivitySubtractedParticle[ig][ik] = new TH1F( Form("VA%sSubtracted_%s", VetrexString[ik].Data(), ParticleName[ig].Data()), Form("VA%sSubtracted_%s", VetrexString[ik].Data(), ParticleName[ig].Data()), 50, 0, 4000+ik*3000);  
            hVertexActivitySubtractedParticle[ig][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data() ) );
            
            for(int il=0; il<2; il++) //loop over short long track
            {
                hVertexActivitySubTrackLengtParticle[il][ig][ik] = new TH1F( Form("VA%sSubtracted_%s_%s", VetrexString[ik].Data(), TrackLenght[il].Data(), ParticleName[ig].Data()), Form("VA%sSubtracted_%s_%s", VetrexString[ik].Data(), TrackLenght[il].Data(), ParticleName[ig].Data()), 50, 0, 4000+ik*3000);  
                hVertexActivitySubTrackLengtParticle[il][ig][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data() ) );
                
                hVertexActivitySubTrackLengtParticleCondition[il][ig][ik] = new TH1F( Form("VA%sSubCondition_%s_%s", VetrexString[ik].Data(), TrackLenght[il].Data(), ParticleName[ig].Data()), Form("VA%sSubCondition_%s_%s", VetrexString[ik].Data(), TrackLenght[il].Data(), ParticleName[ig].Data()), 50, 0, 4000+ik*3000);  
                hVertexActivitySubTrackLengtParticleCondition[il][ig][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data() ) );
                
                hVertexActivityOnlyIfTrackLenght[il][ig][ik] = new TH1F( Form("VA%sIfThereAre_%s_%s", VetrexString[ik].Data(), TrackLenght[il].Data(), ParticleName[ig].Data()), Form("VA%sIfThereAre_%s_%s", VetrexString[ik].Data(), TrackLenght[il].Data(), ParticleName[ig].Data()), 50, 0, 4000+ik*3000);  
                hVertexActivityOnlyIfTrackLenght[il][ig][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data() ) );
                
                if(ig==0) //For substracting all we don't need loop over particels
                {
                    hVertexActivitySubTrackLengtAllCondition[il][ik] = new TH1F( Form("VA%sSubCondition_%s_All", VetrexString[ik].Data(), TrackLenght[il].Data()), Form("VA%sSubCondition_%s_All", VetrexString[ik].Data(), TrackLenght[il].Data()), 50, 0, 4000+ik*3000);  
                    hVertexActivitySubTrackLengtAllCondition[il][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data() ) );
                    
                    hVertexActivityOnlyIfTrackLenghtAll[il][ik] = new TH1F( Form("VA%sIfThereAre_%s_All", VetrexString[ik].Data(), TrackLenght[il].Data()), Form("VA%sIfThereAre_%s_All", VetrexString[ik].Data(), TrackLenght[il].Data()), 50, 0, 4000+ik*3000);  
                    hVertexActivityOnlyIfTrackLenghtAll[il][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data() ) );
                    if(ik>0) //for shell we don't need 1x1x1 box
                    {
                        hVertexActivitySubTrackLengtAllConditionShell[il][ik-1] = new TH1F( Form("VA%sSubCondition_%s_All_Shell", VetrexString[ik].Data(), TrackLenght[il].Data()), Form("VA%sSubCondition_%s_All", VetrexString[ik].Data(), TrackLenght[il].Data()), 50, 0, 8000);  
                        hVertexActivitySubTrackLengtAllConditionShell[il][ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data() ) );
                    
                        hVertexActivityOnlyIfTrackLenghtAllShell[il][ik-1] = new TH1F( Form("VA%sIfThereAre_%s_All_Shell", VetrexString[ik].Data(), TrackLenght[il].Data()), Form("VA%sIfThereAre_%s_All", VetrexString[ik].Data(), TrackLenght[il].Data()), 50, 0, 8000);  
                        hVertexActivityOnlyIfTrackLenghtAllShell[il][ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data() ) );
                    }
                }
            }
            for(int is=0; is<SizeOfParticleVector-1; is++) //loop over conditioned particle
            {
                for(int il=0; il<ParticleNumberGO; il++) //loop over condition
                {
                    hEnergyDepoParticleWithCuts[il][is][ig][ik] = new TH1F( Form("VA%s_%s_EnergyDepo_IfNumOf%s=%i",VetrexString[ik].Data(), ParticleName[ig].Data(),ParticleName[is+1].Data(), il), Form("VA%s_%s_EnergyDepo_IfNumOf%s=%i",VetrexString[ik].Data(), ParticleName[ig].Data(), ParticleName[is+1].Data(), il), 40, 0, 40+30*ik);
                    hEnergyDepoParticleWithCuts[il][is][ig][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [MeV?]",VetrexString[ik].Data() ) );
                    
                    if(ig>0) //we don't want muon
                    {
                        hEnergyDepoParticleWithCutsNonZero[il][is][ig-1][ik] = new TH1F( Form("VA%s_%s_EnergyDepo_IfNumOf%s=%i_NonZero",VetrexString[ik].Data(), ParticleName[ig].Data(), ParticleName[is+1].Data(), il), Form("VA%s_%s_EnergyDepo_IfNumOf%s=%i_NonZero",VetrexString[ik].Data(), ParticleName[ig].Data(), ParticleName[is+1].Data(), il), 40, 0, 40+30*ik);
                        hEnergyDepoParticleWithCutsNonZero[il][is][ig-1][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [MeV?]",VetrexString[ik].Data() ) );
                    }
                }
            }
        }
        for(int is=0; is<2; is++)
        {
            hVertexActivityTrackLength[is][ik] = new TH1F( Form("%sIfNo%sTracks", VertexName[ik].Data(), TrackLenght[is].Data()), Form("%sIfNo%sTracks", VertexName[ik].Data(), TrackLenght[is].Data()), 50, 0, 4000+ik*3000);  
            hVertexActivityTrackLength[is][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
        }
        for(int ih=0; ih<ParticleNumberGO; ih++)
        {
            for(int ig=0; ig<SizeOfParticleVector-1; ig++)
            {
                hVertexActivityParticleCuts[ig][ih][ik] = new TH1F( Form("VA%sIfNumOf_%s=%i", VetrexString[ik].Data(), ParticleName[ig+1].Data(), ih) , Form("VA%sIfNumOf_%s=%i", VetrexString[ik].Data(), ParticleName[ig+1].Data() , ih), 50, 0, 4000+ik*3000);  
                hVertexActivityParticleCuts[ig][ih][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
            }
        }
    }
    for(int ig=0; ig<SizeOfParticleVector; ig++)
    {
        hMeanScatteringRange[ig] = new TH1F( Form("%sScatteringDistance", ParticleName[ig].Data() ), Form("%sScatteringDistance", ParticleName[ig].Data() ) , 50, 0, 300 );  
        hMeanScatteringRange[ig]->GetXaxis()->SetTitle( "Distance [cm]" );
    }
    TH2F *hMomentumVsRange[SizeOfParticleVector];
    TH2F *hEenrgyVsRange[SizeOfParticleVector];
    TH2F *hEenrgyVsRangeRestricted[SizeOfParticleVector];
    TH2F *hEenrgyPeVsRange[SizeOfParticleVector];
    TH2F *hScatteringPathVsMomentum[SizeOfParticleVector];
    for(int ig=0; ig<SizeOfParticleVector; ig++)
    {
        hMomentumVsRange[ig] = new TH2F( Form("MomentumVsRange_%s", ParticleName[ig].Data()), Form("MomentumVsRange_%s", ParticleName[ig].Data()),50., 0., 5000., 50., 0., 300.);  
        hMomentumVsRange[ig]->GetXaxis()->SetTitle("True Momentum [MeV/c]");
        hMomentumVsRange[ig]->GetYaxis()->SetTitle("Range [cm]");
        
        hEenrgyVsRange[ig] = new TH2F( Form("EnergyVsRange_%s", ParticleName[ig].Data()), Form("EnergyVsRange_%s", ParticleName[ig].Data()),50., 0., 1000., 50., 0., 300.);  
        hEenrgyVsRange[ig]->GetXaxis()->SetTitle("Deposited energy [MeV?]");
        hEenrgyVsRange[ig]->GetYaxis()->SetTitle("Range [cm]");
        
        hEenrgyVsRangeRestricted[ig] = new TH2F( Form("EnergyVsRange_Restricted_%s", ParticleName[ig].Data()), Form("EnergyVsRange_Restricted_%s", ParticleName[ig].Data()),50., 0., 1000., 50., 0., 300.);  
        hEenrgyVsRangeRestricted[ig]->GetXaxis()->SetTitle("Deposited energy [MeV?]");
        hEenrgyVsRangeRestricted[ig]->GetYaxis()->SetTitle("Range [cm]");
        
        hEenrgyPeVsRange[ig] = new TH2F( Form("EnergyPeVsRange_%s", ParticleName[ig].Data()), Form("EnergyPeVsRange_%s", ParticleName[ig].Data()),50., 0., 1000., 50., 0., 300.);  
        hEenrgyPeVsRange[ig]->GetXaxis()->SetTitle("Deposited energy [p.e./100]");
        hEenrgyPeVsRange[ig]->GetYaxis()->SetTitle("Range [cm]");
        
        hScatteringPathVsMomentum[ig] = new TH2F( Form("ScatteringPathVsMomentum_%s", ParticleName[ig].Data()), Form("ScatteringPathVsMomentum_%s", ParticleName[ig].Data()), 50., 0., 5000., 50., 0., 300.);  
        hScatteringPathVsMomentum[ig]->GetXaxis()->SetTitle("True Momentum [MeV/c]");
        hScatteringPathVsMomentum[ig]->GetYaxis()->SetTitle("Range [cm]");
    }
    
    if(VERBOSE) cout<< "\033[1;34mNumber of all events\033[0m" <<evtFin<<endl;

    TTree t1("t1","Tree");    
    Float_t VertexBranch[5];
    Int_t ParticleCounterBranch[SizeOfParticleVector];
    for(int ik=0; ik<5; ik++)
    {
        t1.Branch( Form("VertexBranch%s" , VetrexString[ik].Data() ), &VertexBranch[ik], Form("VertexBranch%s/F",VetrexString[ik].Data() ) );
    }
    for(int ig=0; ig<SizeOfParticleVector; ig++)
    {
        t1.Branch( Form("%sCounterBranch" , ParticleNameBranch[ig].Data() ), &ParticleCounterBranch[ig], Form("%sCounterBranch/I", ParticleNameBranch[ig].Data()) );
    }
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
        if(VERBOSE) cout<<selEvents+1<<" Vertex position  X "<<VertexPosition[0]<<" Y "<< VertexPosition[1] <<" Z "<< VertexPosition[2]<<endl;
        
        double VertexDeposit[5][2]={}; //[VertexBox][0-PE, 1-MeV]
        double VertexDepositSubtracted[SizeOfParticleVector][5][2]={}; //[studied particle][VertexBox][0-PE, 1-MeV]
        double VertexDepositSubtractedLength[2][SizeOfParticleVector][5][2]={}; //[0-short, 1-long][studied particle][VertexBox][0-PE, 1-MeV]
        double VertexDepositSubtractedLengthAll[2][5][2]={}; //[0-short, 1-long][VertexBox][0-PE, 1-MeV]
        
        double VertexDepositShifted[SizeOfShiftVector][3][5][2]={}; //[VAshiftVector][X,Y,Z][VertexBox][0-PE, 1-MeV]
        double VertexParticleDeposit[3][5][2]={}; //[0-muon, 1-pion, 2-proton][VertexBox][0-PE, 1-MeV]
        double VertexGarbageDeposit[5][2]={}; //[VertexBox][0-PE, 1-MeV]
        
        bool VetrexInDetector=true; //sometimes vertex is outside  detector boundries/fiducial volume
        if( VertexPosition[0]<FiducialVolume ||  VertexPosition[1]<FiducialVolume || VertexPosition[2]<FiducialVolume || VertexPosition[0]>SFGD_X-FiducialVolume ||  VertexPosition[1]>SFGD_Y-FiducialVolume || VertexPosition[2]>SFGD_Z-FiducialVolume)
        {
            VetrexInDetector=false;
            if(VERBOSE) cout<<"\033[1;31mOut of detector FV\033[0m"<<endl;
        }
        if(!VetrexInDetector) continue;
        int MuonCounter=0;
        for(auto t:inputEvent->GetTrueTracks()) 
        {
            if( t->GetPDG() == 13 && t->GetParentID()==0 && t->GetMaxEuclDist()>ShortTrack )
            {
                if(VERBOSE) cout<<"True track PDG= "<<t->GetPDG()<<" range "<<t->GetMaxEuclDist()<<" mom "<<t->GetMomentum()<<" cosTheta "<<t->GetCosTheta()<<endl;
                MuonCounter++;
            }
        }
        if(MuonCounter==0)
        {
            if(VERBOSE) cout<<"\033[1;31mNo muon from vertex\033[0m"<<endl;
            continue;
        } 
        double Edep=0;
        double EdepPE=0;
        int ParticleCounter[SizeOfParticleVector]={}; // [0-muon, 1-pion, 2-proton]
        int TrackLengthParticleCounter[2][SizeOfParticleVector-1]={}; // [0-short track, 1-long track][1-pion, 2-proton]
        std::vector<int> TrackIdLengthParticle[2][SizeOfParticleVector];
        std::vector<int> TrackIdLengthAll[2];
        std::vector<int> TrackIdConditionLengthParticle[2];
        
        std::vector<int> ParticleTrackId[SizeOfParticleVector][2];//[particle of interes][0-original, 1-after scaterring]
        std::vector<int> GarbageTrackId;
        std::vector<int> GarbageTrackCounter[5]; //neccesary to pinpoint PDG of garbage track in VA box
        
        for(auto t:inputEvent->GetTrueTracks())
        {
            double TrackDistance=t->GetMaxEuclDist();
            if( t->GetParentID()!=0 ) 
            {
                GarbageTrackId.push_back( t->GetTrackID() );
                for(int ik=0; ik<5; ik++)
                {
                    GarbageTrackCounter[ik].push_back(1);
                }
            }
            if(TrackDistance < ShortTrack)  TrackIdConditionLengthParticle[0].push_back( t->GetTrackID() );
            if(TrackDistance >= ShortTrack) TrackIdConditionLengthParticle[1].push_back( t->GetTrackID() );

            for(int ig=0; ig<SizeOfParticleVector; ig++) //loop over studied particles
            {
                if( t->GetPDG() == ParticlePDG[ig] && t->GetParentID()==0)
                {
                    int OutGoingCounter=0; //counts particles after scattering
                    double momentumTemp=0;
                    ParticleTrackId[ig][0].push_back( t->GetTrackID() );
                    for(auto track:inputEvent->GetTrueTracks())
                    {
                        if( track->GetParentID()==t->GetTrackID() && track->GetPDG()==t->GetPDG() )
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
                    if(ParticleTrackId[ig][1].at( ParticleTrackId[ig][1].size()-1 ) != -999)
                    {
                        hMeanScatteringRange[ig]->Fill(TrackDistance);
                        hScatteringPathVsMomentum[ig]->Fill( t->GetMomentum(), TrackDistance );
                    }
                    hMomentumVsRange[ig]->Fill(t->GetMomentum(), TrackDistance );
                    for(auto voxel:inputEvent->GetVoxels())
                    {
                        if(voxel->GetTrueTrackIDs()[0] == t->GetTrackID()) {Edep+=voxel->GetTrueEdep(); EdepPE+=voxel->GetTruePE();}
                    }
                    hEenrgyVsRange[ig]->Fill(Edep, TrackDistance );
                    hEenrgyPeVsRange[ig]->Fill(EdepPE/100, TrackDistance );
                    ParticleCounter[ig]++;
                    if(ig>0 && TrackDistance <ShortTrack)  TrackLengthParticleCounter[0][ig-1]++; //short track
                    if(ig>0 && TrackDistance >=ShortTrack) TrackLengthParticleCounter[1][ig-1]++; //long track
                    
                    if(t->GetCosTheta()>0.7 || t->GetCosTheta()<-0.7) hEenrgyVsRangeRestricted[ig]->Fill(Edep, TrackDistance );
                    Edep=0;
                    EdepPE=0;
                }
                TrackIdLengthParticle[0][ig].push_back( t->GetTrackID() );
                TrackIdLengthParticle[1][ig].push_back( t->GetTrackID() );

                if( t->GetPDG() == ParticlePDG[ig] && TrackDistance <= ShortTrack)
                {
                    TrackIdLengthParticle[0][ig].pop_back();
                }
                if( t->GetPDG() == ParticlePDG[ig] && TrackDistance > ShortTrack)
                {
                    TrackIdLengthParticle[1][ig].pop_back();
                }
            }
            TrackIdLengthAll[0].push_back( t->GetTrackID() );
            TrackIdLengthAll[1].push_back( t->GetTrackID() );
            //TODO moze da się to łądniej zrobić
            if(t->GetPDG() == ParticlePDG[0] || t->GetPDG() == ParticlePDG[1] || t->GetPDG() == ParticlePDG[2] || t->GetPDG() == -211) 
            {
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
        for(int ig=0; ig<SizeOfParticleVector; ig++){ ParticleCounterBranch[ig]=ParticleCounter[ig]; }
        for(auto voxel:inputEvent->GetVoxels())
        {   
            for(int ik=0; ik<5; ik++)
            {
                //A->DistToVoxel(B);
                bool StudiedShape[3]={}; //[X, Y, Z] Could be in one if() but this seems to give more flexibility
                if( abs(VertexPosition[0]-voxel->GetX() ) <= VertexBox[ik]) StudiedShape[0]=true;
                if( abs(VertexPosition[1]-voxel->GetY() ) <= VertexBox[ik]) StudiedShape[1]=true;
                if( abs(VertexPosition[2]-voxel->GetZ() ) <= VertexBox[ik]) StudiedShape[2]=true;                
                if( StudiedShape[0] && StudiedShape[1] && StudiedShape[2] )
                {
                    VertexDeposit[ik][0]+=voxel->GetTruePE();
                    VertexDeposit[ik][1]+=voxel->GetTrueEdep();
                    
                    for(int ig=0; ig<SizeOfParticleVector; ig++)
                    {
                        if(voxel->GetTruePDGs()[0]!=ParticlePDG[ig])
                        {
                            VertexDepositSubtracted[ig][ik][0]+=voxel->GetTruePE();
                            VertexDepositSubtracted[ig][ik][1]+=voxel->GetTrueEdep();
                        }
                        for(int io=0; io<2; io++) //loop over short long DrawTrueTracks
                        {
                            for(int il=0; il<TrackIdLengthParticle[io][ig].size(); il++)
                            {
                                if( voxel->GetTrueTrackIDs()[0]==TrackIdLengthParticle[io][ig].at(il) )
                                {
                                    VertexDepositSubtractedLength[io][ig][ik][0]+=voxel->GetTruePE();
                                    VertexDepositSubtractedLength[io][ig][ik][1]+=voxel->GetTrueEdep();
                                }
                            }
                        }
                    }
                    for(int io=0; io<2; io++) //loop over short long DrawTrueTracks
                    {
                        for(int il=0; il<TrackIdLengthAll[io].size(); il++)
                        {
                            if( voxel->GetTrueTrackIDs()[0]==TrackIdLengthAll[io].at(il) )
                            {
                                VertexDepositSubtractedLengthAll[io][ik][0]+=voxel->GetTruePE();
                                VertexDepositSubtractedLengthAll[io][ik][1]+=voxel->GetTrueEdep();
                            }
                        }
                    }
                    for(int ig=0; ig<GarbageTrackId.size(); ig++)
                    {
                        if(voxel->GetTrueTrackIDs()[0]==GarbageTrackId.at(ig)) 
                        {
                            VertexGarbageDeposit[ik][0]+=voxel->GetTruePE();
                            VertexGarbageDeposit[ik][1]+=voxel->GetTrueEdep(); 
                            
                            if(voxel->GetTruePE()>epsilon && GarbageTrackCounter[ik].at(ig)==1)
                            {
                                hGarbagePDG[ik]->Fill(voxel->GetTruePDGs()[0]);
                                GarbageTrackCounter[ik].at(ig)=0;
                            }
                        }
                    }
                    for(int ig=0; ig<SizeOfParticleVector; ig++)
                    {
                        for(int io=0; io<ParticleTrackId[ig][0].size(); io++)
                        {
                            if(ParticleTrackId[ig][0].at(io)==voxel->GetTrueTrackIDs()[0] || ParticleTrackId[ig][1].at(io)==voxel->GetTrueTrackIDs()[0]) //we take those from directly from vertex or after scatering
                            {
                                VertexParticleDeposit[ig][ik][0]+=voxel->GetTruePE();
                                VertexParticleDeposit[ig][ik][1]+=voxel->GetTrueEdep();
                            }
                        }
                    }
                }
                bool StudiedShapeShifted[SizeOfShiftVector][3]={}; //[VAshiftVector][X, Y, Z]
                for(int ih=0; ih<SizeOfShiftVector; ih++)
                {
                    if( abs(VertexPosition[0]+VAshiftVector[ih]-voxel->GetX() ) <= VertexBox[ik]) StudiedShapeShifted[ih][0]=true;
                    if( abs(VertexPosition[1]+VAshiftVector[ih]-voxel->GetY() ) <= VertexBox[ik]) StudiedShapeShifted[ih][1]=true;
                    if( abs(VertexPosition[2]+VAshiftVector[ih]-voxel->GetZ() ) <= VertexBox[ik]) StudiedShapeShifted[ih][2]=true;
                
                    if(StudiedShapeShifted[ih][0] && StudiedShape[1] && StudiedShape[2]) //Shifted in X
                    {
                        VertexDepositShifted[ih][0][ik][0]+=voxel->GetTruePE();
                        VertexDepositShifted[ih][0][ik][1]+=voxel->GetTrueEdep();
                    }
                    if(StudiedShape[0] && StudiedShapeShifted[ih][1] && StudiedShape[2]) //Shifted in Y
                    {
                        VertexDepositShifted[ih][1][ik][0]+=voxel->GetTruePE();
                        VertexDepositShifted[ih][1][ik][1]+=voxel->GetTrueEdep();
                    }
                    if(StudiedShape[0] && StudiedShape[1] && StudiedShapeShifted[ih][2]) //Shifted in Z
                    {
                        VertexDepositShifted[ih][2][ik][0]+=voxel->GetTruePE();
                        VertexDepositShifted[ih][2][ik][1]+=voxel->GetTrueEdep();
                    }
                }
            }
        }
        double nuMom = inputEvent->GetNuMom();
        h_nuMom->Fill(nuMom);
        
        for(int ik=0; ik<5; ik++) //Filling histograms starts here
        {
            hVertexActivity[ik]->Fill(VertexDeposit[ik][0]); 
            VertexBranch[ik]=VertexDeposit[ik][1];
            if(ik>0) hVertexActivityShell[ik-1]->Fill(VertexDeposit[ik][0]-VertexDeposit[ik-1][0]);
            if(TrackLengthParticleCounter[0][0]==0 && TrackLengthParticleCounter[0][1]==0) hVertexActivityTrackLength[0][ik]->Fill(VertexDeposit[ik][0]); 
            if(TrackLengthParticleCounter[1][0]==0 && TrackLengthParticleCounter[1][1]==0) hVertexActivityTrackLength[1][ik]->Fill(VertexDeposit[ik][0]);
            if(VertexGarbageDeposit[ik][1]>epsilon) hVertexActivityByGarbage[ik]->Fill( VertexGarbageDeposit[ik][1] );
            
            for(int ig=0; ig<SizeOfParticleVector; ig++)
            {
                hVertexActivitySubtractedParticle[ig][ik]->Fill(VertexDepositSubtracted[ig][ik][0]);
                hEnergyDepoParticle[ig][ik]->Fill( VertexParticleDeposit[ig][ik][1] );
                if(ig==0 && VertexParticleDeposit[0][0][1]>) hEnergyDepoParticleNonZero[ik]->Fill( VertexParticleDeposit[ig][ik][1] );
                for(int is=0; is<2; is++) //loop over condition particle
                {
                    for(int il=0; il<ParticleNumberGO; il++) //loop over # of condition particles
                    {
                        if(ParticleCounter[is+1]==ParticleNumberCut[il]) hEnergyDepoParticleWithCuts[il][is][ig][ik]->Fill( VertexParticleDeposit[ig][ik][1] );
                        if(ParticleCounter[is+1]==ParticleNumberCut[il] && ig>0 && VertexParticleDeposit[ig][0][1]>epsilon)
                        {
                            hEnergyDepoParticleWithCutsNonZero[il][is][ig-1][ik]->Fill( VertexParticleDeposit[ig][ik][1] );
                        }
                    }
                }
                for(int il=0; il<2; il++)
                {
                    hVertexActivitySubTrackLengtParticle[il][ig][ik]->Fill(VertexDepositSubtractedLength[il][ig][ik][0]);
                    if( abs( VertexDeposit[ik][0]-VertexDepositSubtractedLength[il][ig][ik][0])>epsilon )
                    //TODO mozna pomyśleć zmienic [ik]->[4]
                    {
                        hVertexActivitySubTrackLengtParticleCondition[il][ig][ik]->Fill( VertexDepositSubtractedLength[il][ig][ik][0] );
                        hVertexActivityOnlyIfTrackLenght[il][ig][ik]->Fill( VertexDeposit[ik][0] );
                    }
                    if(ig==0 && abs( VertexDeposit[ik][0]-VertexDepositSubtractedLengthAll[0][ik][0] )> epsilon )
                    {
                        hVertexActivitySubTrackLengtAllCondition[il][ik]->Fill( VertexDepositSubtractedLengthAll[il][ik][0] );
                        hVertexActivityOnlyIfTrackLenghtAll[il][ik]->Fill( VertexDeposit[ik][0] ); 
                        
                        if(ik>0) //TODO pomyśl nad warunkiem zeby porownywac to samo
                        {
                            hVertexActivitySubTrackLengtAllConditionShell[il][ik-1]->Fill( VertexDepositSubtractedLengthAll[il][ik][0] - VertexDepositSubtractedLengthAll[il][ik-1][0] );
                            hVertexActivityOnlyIfTrackLenghtAllShell[il][ik-1]->Fill(VertexDeposit[ik][0]-VertexDeposit[ik-1][0] ); 
                        }
                    }
                }
            }
            if(ik>0 && abs( VertexDeposit[ik][0]-VertexDepositSubtractedLengthAll[0][ik][0] )<= epsilon )
            {
                hVertexActivityOnlyLongShell[ik-1]->Fill(VertexDeposit[ik][0]-VertexDeposit[ik-1][0] );
            }
            for(int ih=0; ih<SizeOfShiftVector; ih++)
            {
                for(int ig=0; ig<3; ig++)
                {
                    hVertexActivityShifted[ih][ig][ik]->Fill(VertexDepositShifted[ih][ig][ik][0]);
                }
            }
            for(int ig=0; ig<SizeOfParticleVector-1; ig++) //loop over conditioned particle/ no muon(-1)
            {
                for(int ih=0; ih<ParticleNumberGO; ih++) //how many given particle
                {
                    if(ParticleCounter[ig+1]==ParticleNumberCut[ih]) hVertexActivityParticleCuts[ig][ih][ik]->Fill(VertexDeposit[ik][0]);
                }
            }
        }
        t1.Fill();
        selEvents++; 
        //inputEvent->DrawTrueTracks(true,"trueTracks");
    } //End of loop over events
    if (FileOutput->IsOpen())
    {
        FileOutput->cd();
        h_nuMom->Write("",TObject::kOverwrite); 
        //// Could be in one loop but for convinience in reading output file this is advisable
        for(int ik=0; ik<5; ik++)
        {
            hVertexActivity[ik]->Write("",TObject::kOverwrite); 
        }
        for(int ik=0; ik<4; ik++)
        {
            hVertexActivityShell[ik]->Write("",TObject::kOverwrite); 
        }
        for(int ig=0; ig<SizeOfParticleVector; ig++)
        {
            hMomentumVsRange[ig]->Write("",TObject::kOverwrite);
        }
        for(int ig=0; ig<SizeOfParticleVector; ig++)
        {
            hEenrgyVsRange[ig]->Write("",TObject::kOverwrite);
        }
        for(int ig=0; ig<SizeOfParticleVector; ig++)
        {
            hEenrgyPeVsRange[ig]->Write("",TObject::kOverwrite);
        }
        for(int ig=0; ig<SizeOfParticleVector; ig++)
        {
            hEenrgyVsRangeRestricted[ig]->Write("",TObject::kOverwrite);
        }
        for(int ig=0; ig<SizeOfParticleVector; ig++)
        {
            hScatteringPathVsMomentum[ig]->Write("",TObject::kOverwrite);
        }
        FolderEnergyLoss->cd();
        for(int ig=0; ig<SizeOfParticleVector; ig++)
        {
            for(int ik=0; ik<5; ik++)
            {
                hEnergyDepoParticle[ig][ik]->Write("",TObject::kOverwrite);
            }
        }
        for(int ih=0; ih<SizeOfParticleVector-1; ih++)
        {
            for(int is=0; is<ParticleNumberGO; is++)
            {
                for(int ig=0; ig<SizeOfParticleVector; ig++)
                {
                    for(int ik=0; ik<5; ik++)
                    {
                        hEnergyDepoParticleWithCuts[is][ih][ig][ik]->Write("",TObject::kOverwrite); 
                    }
                }
            }
        }
        FolderEnergyLossNonZero->cd();
        for(int ik=0; ik<5; ik++)
        {
            hEnergyDepoParticleNonZero[ik]->Write("",TObject::kOverwrite);
        }
        for(int ih=0; ih<SizeOfParticleVector-1; ih++)
        {
            for(int is=0; is<ParticleNumberGO; is++)
            {
                for(int ig=0; ig<SizeOfParticleVector-1; ig++)
                {
                    for(int ik=0; ik<5; ik++)
                    {
                        hEnergyDepoParticleWithCutsNonZero[is][ih][ig][ik]->Write("",TObject::kOverwrite); 
                    }
                }
            }
        }
        FolderSubtracted->cd();
        for(int ig=0; ig<SizeOfParticleVector; ig++)
        {
            for(int ik=0; ik<5; ik++)
            {
                hVertexActivitySubtractedParticle[ig][ik]->Write("",TObject::kOverwrite); 
            }
        }
        FolderSubtractedTrackLength->cd();
        for(int il=LongOrShort; il<2; il++)
        {
            for(int ig=0; ig<SizeOfParticleVector; ig++)
            {
                for(int ik=0; ik<5; ik++)
                {
                    hVertexActivitySubTrackLengtParticle[il][ig][ik]->Write("",TObject::kOverwrite); 
                }
            }
        }
        FolderSubtractedTrackLengthCondition->cd();
        for(int il=LongOrShort; il<2; il++)
        {
            for(int ig=0; ig<SizeOfParticleVector; ig++)
            {
                for(int ik=0; ik<5; ik++)
                {
                    hVertexActivityOnlyIfTrackLenght[il][ig][ik]->Write("",TObject::kOverwrite); 
                }
            }
            for(int ig=0; ig<SizeOfParticleVector; ig++)
            {
                for(int ik=0; ik<5; ik++)
                {
                    hVertexActivitySubTrackLengtParticleCondition[il][ig][ik]->Write("",TObject::kOverwrite); 
                }
            }
        }
        FolderSubtractedTrackLengthAll->cd();
        for(int il=LongOrShort; il<2; il++)
        {
            for(int ik=0; ik<5; ik++)
            {
                hVertexActivitySubTrackLengtAllCondition[il][ik]->Write("",TObject::kOverwrite); 
            }
            for(int ik=0; ik<5; ik++)
            {
                hVertexActivityOnlyIfTrackLenghtAll[il][ik]->Write("",TObject::kOverwrite); 
            }
        }
        FolderSubtractedTrackLengthAllShell->cd();
        for(int il=LongOrShort; il<2; il++)
        {
            for(int ik=0; ik<4; ik++)
            {
                hVertexActivitySubTrackLengtAllConditionShell[il][ik]->Write("",TObject::kOverwrite); 
            }
            for(int ik=0; ik<4; ik++)
            {
                hVertexActivityOnlyIfTrackLenghtAllShell[il][ik]->Write("",TObject::kOverwrite); 
            }
        }
        for(int ik=0; ik<4; ik++)
        {
            hVertexActivityOnlyLongShell[ik]->Write("",TObject::kOverwrite); 
        }
        FolderShift->cd();
        for(int ik=0; ik<5; ik++)
        {
            for(int ih=0; ih<SizeOfShiftVector; ih++)
            {
                for(int ic=0; ic<3; ic++) //loop over coordiantes XYZ
                {
                    hVertexActivityShifted[ih][ic][ik]->Write("",TObject::kOverwrite); 
                }
            }
        }
        FolderCut->cd();
        for(int ik=0; ik<5; ik++)
        {
            for(int ig=0; ig<SizeOfParticleVector-1; ig++)
            {
                for(int ih=0; ih<ParticleNumberGO; ih++)
                {
                    hVertexActivityParticleCuts[ig][ih][ik]->Write("",TObject::kOverwrite); 
                }
            }
        }
        FolderGarbage->cd();
        for(int ik=0; ik<5; ik++)
        {
            hVertexActivityByGarbage[ik]->Write("",TObject::kOverwrite);
        }
        for(int ik=0; ik<5; ik++)
        {
            hGarbagePDG[ik]->Write("",TObject::kOverwrite);
        }
        Other->cd();
        for(int ig=0; ig<2; ig++)
        {
            for(int ik=0; ik<5; ik++)
            {
                hVertexActivityTrackLength[ig][ik]->Write("",TObject::kOverwrite);
            }
        }
        for(int ig=0; ig<SizeOfParticleVector; ig++)
        {
            hMeanScatteringRange[ig]->Write("",TObject::kOverwrite);
        }
        FileOutput->cd();
        t1.Write();
        FileOutput->Close();
    }    
    cout << endl << "\033[1;32mGenerated output: \033[0m" << fileOut.Data() << endl;
    handleEndOfExecution();
}
