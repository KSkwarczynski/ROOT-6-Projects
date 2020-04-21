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
TString fileIn         = "/mnt/home/kskwarczynski/t2k-nd280-upgrade/Output/Reconstructed_SFGD_MC_0.root";
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
double ShortTrack      = 3.0;    //threshold for short tracks

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
    //TODO histo gdy mamy wieskzy depo w 9x9 niz 7x7 lub 5x5x5 na stopujace protony
    //TODO proton powinien byc 2 a nie pion to jest mylace i nie intuicyjne
    //TODO zmien reakcje zby odpowiadaly tym z highlanda czy cos
    parseArguments();
    linkFilesToTTrees();

    bool VERBOSE = true;
    std::vector<ND280SFGDHit*> mppc_hits;
    
    if(VERBOSE) cout<<"Short track definion  "<<ShortTrack<<endl;
    
    int VAshiftVector[2]={1, -1}; //Adjust position of vertex
    const int SizeOfShiftVector= (sizeof(VAshiftVector)/sizeof(*VAshiftVector));
    const int SizeOfParticleVector = 4;
    const int ParticleNumberGO = 2; //Number of particles we put condition on, starting from 0
    const int SelectionNumber = 5;
    const int ReacTypeNum = 5;
    
    TString VertexName[5]={"VertexActivity1x1x1", "VertexActivity3x3x3", "VertexActivity5x5x5", "VertexActivity7x7x7", "VertexActivity9x9x9"};
    TString VertexNameShifted[3]={"X", "Y", "Z"};
    TString VetrexString[5]={"1x1x1" , "3x3x3" , "5x5x5", "7x7x7", "9x9x9"};
    TString ParticleName[SizeOfParticleVector]={"Muon", "Pion+", "Proton", "Pion-"};
    TString ParticleNameBranch[SizeOfParticleVector]={"Muon", "PionP", "Proton", "PionN"};
    TString TrackLenght[2]={"Short", "Long"};
    TString OppositeLenght[2]={"Long", "Short"};
    TString SelectionsName[SelectionNumber]={"1mu1p", "1mu", "1muNp", "CC1Pi", "CCOther"};
    TString ReactionName[ReacTypeNum]={"CCQE","2p2h", "RES", "DIS", "COH"}; //We won't see NC due to applied cuts
    //TODO TODO bedzie trzebadodac 2p2h do reakcji jak juz beda wysmulowane
    TDirectory *FolderEnergyLoss = FileOutput->mkdir("FolderEnergyLoss");
    TDirectory *FolderEnergyLossNonZero = FileOutput->mkdir("FolderEnergyLossNonZero");
    TDirectory *FolderSubtracted = FileOutput->mkdir("FolderSubtracted");
    TDirectory *FolderSubtractedTrackLength = FileOutput->mkdir("FolderSubtractedTrackLength");
    TDirectory *FolderSubtractedTrackLengthCondition = FileOutput->mkdir("FolderSubtractedTrackLengthCondition");
    TDirectory *FolderSubtractedTrackLengthAll = FileOutput->mkdir("FolderSubtractedTrackLengthAll");
    TDirectory *FolderSubtractedTrackLengthAllShell = FileOutput->mkdir("FolderSubtractedTrackLengthAllShell");
    TDirectory *FolderHist2D = FileOutput->mkdir("FolderHist2D");
    TDirectory *FolderShift = FileOutput->mkdir("FolderShift");
    TDirectory *FolderCut = FileOutput->mkdir("FolderCut");
    TDirectory *FolderGarbage = FileOutput->mkdir("FolderGarbage");
    TDirectory *Other = FileOutput->mkdir("Other");
    
    TDirectory *FolderParticleSelections[SelectionNumber];
    for(int ic=0; ic<SelectionNumber; ic++)
    {
       FolderParticleSelections[ic]= FileOutput->mkdir( Form( "Folder%s", SelectionsName[ic].Data() ) );
    }
    TDirectory *FolderReaction[ReacTypeNum];
    for(int ir=0; ir<ReacTypeNum; ir++)
    {
       FolderReaction[ir]= FileOutput->mkdir( Form( "Folder%s", ReactionName[ir].Data() ) );
    }
    TDirectory *FolderSplitedSelection[SelectionNumber];
    for(int ic=0; ic<SelectionNumber; ic++)
    {
        FolderSplitedSelection[ic]= FileOutput->mkdir( Form( "FolderSplited%s", SelectionsName[ic].Data() ) );
    }
    double VertexBox[5]={0., 1., 2., 3., 4.}; // 1x1x1, 3x3x3, 5x5x5 and so on...
    int ParticleNumberCut[7]={0, 1, 2, 3, 4, 5, 6};
    int ParticlePDG[SizeOfParticleVector]={13, 211, 2212, -211}; //muon, pion+, proton
    double epsilon = 0.0001;   // value neccesary for comparing floating numbers
    int FiducialVolume = 3;   //set how far from detector boundries we want to study Vertex Activity
    int LongOrShort = 1;     //Set if you are interested in subtracting long and short [0] or just long [1]
    
    TH1F *h_nuMom = new TH1F("h_nuMom", "h_nuMom", 50,0,6000);
    h_nuMom->GetXaxis()->SetTitle("MeV?");
    TH1F *hprotonMomentum = new TH1F("protonMomentum", "protonMomentum", 100,0,3000);
    hprotonMomentum->GetXaxis()->SetTitle("MeV/c?");
    
    TH1F *hVertexActivity[5]; //[vertexBox]
    TH1F *hVertexActivityShell[4]; //[vertexBox-1]
    TH1F *hVertexActivitySubtractedParticle[SizeOfParticleVector][5]; //[substracted particle][vertexBox]
    
    TH1F *hVertexActivitySubTrackLengtParticle[2][SizeOfParticleVector][5]; //[0-short, 1-long][substracted particle][vertexBox]
    TH1F *hVASubTrackLengtParticleCondition[2][SizeOfParticleVector][5]; //[0-short, 1-long][substracted particle][vertexBox]
    TH1F *hVAOnlyIfTrackLenght[2][SizeOfParticleVector][5]; //[0-short, long][substracted particle][vertexBox]
    
    TH1F *hVertexActivitySelections[SelectionNumber][5]; //[vertexBox]
    TH1F *h_nuMomSelections[SelectionNumber];
    TH1F *hVertexActivityShellSelection[SelectionNumber][4]; //[vertexBox-1]
    TH1F *hVASubTrackLengtAllCondSelection[SelectionNumber][2][5]; //[Selection][0-short, 1-long][vertexBox]
    TH1F *hVAOnlyIfTrackLenghtAllSelection[SelectionNumber][2][5];
    TH1F *hVertexActivityOnlyIfTrackLenghtAllSelectionShell[SelectionNumber][2][4]; //[0-short, long][vertexBox]
    TH1F *hParticleMomentumSelections[SizeOfParticleVector][SelectionNumber];
    
    TH1F *hVertexActivityReaction[ReacTypeNum][5]; //[vertexBox]
    TH1F *h_nuMomReaction[ReacTypeNum];
    TH1F *hVertexActivityShellReaction[ReacTypeNum][4]; //[vertexBox-1]
    TH1F *hVASubTrackLengtAllCondReaction[ReacTypeNum][2][5]; //[0-short, 1-long][vertexBox]
    TH1F *hVAOnlyIfTrackLenghtAllReaction[ReacTypeNum][2][5];
    TH1F *hVertexActivityIfTrackLenghtAllReactionShell[ReacTypeNum][2][4]; //[0-short, 1-long][vertexBox]
    TH1F *hParticleMomentumReactions[SizeOfParticleVector][ReacTypeNum];
    
    /// \define SplittedSelections
    TH1F *hVASplitSelection[SelectionNumber][ReacTypeNum][5];
    TH1F *h_nuMomSplitSelections[SelectionNumber][ReacTypeNum];
    TH1F *hParticleMomentumSplitSelection[SizeOfParticleVector][SelectionNumber][ReacTypeNum];
    TH1F *hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[SelectionNumber][ReacTypeNum][2][4]; //[0-short, long][vertexBox]
    TH1F *hVertexActivitySubTrackLengtSplitSelection[SelectionNumber][ReacTypeNum][2][5]; 
    
    TH1F *hVertexActivitySubTrackLengtAllCondition[2][5]; 
    TH1F *hVertexActivityOnlyIfTrackLenghtAll[2][5]; //[0-short, long][vertexBox]
    
    TH1F *hVertexActivitySubTrackLengtAllConditionShell[2][4]; 
    TH1F *hVertexActivityOnlyIfTrackLenghtAllShell[2][4]; //[0-short, long][vertexBox]
    TH1F *hVertexActivityOnlyLongShell[4]; //[vertexBox-1]
    
    TH1F *hEnergyDepoParticle[SizeOfParticleVector][5]; //[particle][vertexBox]
    TH1F *hEnergyDepoParticleWithCuts[ParticleNumberGO][SizeOfParticleVector-1][SizeOfParticleVector][5]; //[condition][particle with cut][particle studied][vertexBox]
    TH1F *hEnergyDepoParticleNonZero[5]; //[vertexBox]
    TH1F *hEnergyDepoParticleWithCutsNonZero[ParticleNumberGO][SizeOfParticleVector-1][SizeOfParticleVector-1][5]; //[condition][particle with cut][particle studied][vertexBox]
   
    TH1F *hVertexActivityShifted[SizeOfShiftVector][3][5]; // Which array represent what [VAshiftVector][X,Y,Z][VetrexString]
    TH1F *hVertexActivityParticleCuts[SizeOfParticleVector-1][ParticleNumberGO][5]; // [particle][condition][vertexBox]
    TH1F *hVertexActivityTrackLength[2][5]; //[0-no short track, 1-no long track][vertexBox] tyczy sie tylko trackow z wierzcholka!!!!
    
    TH1F *hMeanScatteringRange[SizeOfParticleVector]; //[particle]
    TH1F *hVertexActivityByGarbage[5]; //[vertexBox]
    TH1F *hGarbagePDG[5]; //[vertexBox]
    
    TH1F *hRecParticleCounter[4]; //[particles]
    
    //WARNING
    TH1F *hVertexPosX= new TH1F("hVertexPosX", "hVertexPosX", SFGD_X, 0.5, SFGD_X+0.5);
    TH1F *hVertexPosY= new TH1F("hVertexPosY", "hVertexPosY", SFGD_Y, 0.5, SFGD_Y+0.5);
    TH1F *hVertexPosZ= new TH1F("hVertexPosZ", "hVertexPosZ", SFGD_Z, 0.5, SFGD_Z+0.5);
    
    TH2F *hVertexPosXY= new TH2F("hVertexPosXY", "hVertexPosXY", SFGD_X, 0.5, SFGD_X+0.5, SFGD_Y, 0.5, SFGD_Y+0.5);
    TH2F *hVertexPosXZ= new TH2F("hVertexPosXZ", "hVertexPosXZ", SFGD_X, 0.5, SFGD_X+0.5, SFGD_Z, 0.5, SFGD_Z+0.5);
    TH2F *hVertexPosYZ= new TH2F("hVertexPosYZ", "hVertexPosYZ", SFGD_Y, 0.5, SFGD_Y+0.5, SFGD_Z, 0.5, SFGD_Z+0.5);
    
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
            
            hVertexActivityOnlyLongShell[ik-1] = new TH1F( Form("%s_OnlyLong_Shell",VertexName[ik].Data()) , Form("%s_OnlyLong_Shell",VertexName[ik].Data()), 50, 0, 8000); 
            hVertexActivityOnlyLongShell[ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
        }
        for(int ic=0; ic<SelectionNumber; ic++)
        {
            for(int ir=0; ir<ReacTypeNum; ir++)
            {
                hVASplitSelection[ic][ir][ik] = new TH1F( Form("VA%s_%s_%s", VetrexString[ik].Data(), SelectionsName[ic].Data(), ReactionName[ir].Data() ), Form("VA%s_%s_%s", VetrexString[ik].Data(), SelectionsName[ic].Data(), ReactionName[ir].Data() ), 50, 0, 4000+ik*3000);  
                hVASplitSelection[ic][ir][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
                
                for(int il=0; il<2; il++) //loop over short long track
                {
                    hVertexActivitySubTrackLengtSplitSelection[ic][ir][il][ik] = new TH1F( Form("VA%sSubtract_%s_%s_%s", VetrexString[ik].Data(), TrackLenght[il].Data(), SelectionsName[ic].Data(), ReactionName[ir].Data()), Form("VA%sSubtract_%s_%s_%s", VetrexString[ik].Data(), TrackLenght[il].Data(), SelectionsName[ic].Data(), ReactionName[ir].Data()), 50, 0, 4000+ik*3000);  
                    if(ik>0)
                    {
                        hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][il][ik-1] = new TH1F( Form("VA%s_IfThereAre_%s__%s_%s_Shell", VetrexString[ik].Data(), OppositeLenght[il].Data(), SelectionsName[ic].Data(), ReactionName[ir].Data()), Form("VA%s_IfThereAre_%s__%s_%s_Shell", VetrexString[ik].Data(), OppositeLenght[il].Data(), SelectionsName[ic].Data(), ReactionName[ir].Data()), 50, 0, 8000);  
                        hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][il][ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data() ) );
                    }
                }
            }
        }
        for(int ir=0; ir<ReacTypeNum; ir++)
        {
            hVertexActivityReaction[ir][ik] = new TH1F( Form("VA%s_%s", VetrexString[ik].Data(), ReactionName[ir].Data() ), Form("VA%s_%s", VetrexString[ik].Data(), ReactionName[ir].Data() ), 50, 0, 4000+ik*3000);  
            hVertexActivityReaction[ir][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
            
            if(ik>0)
            {
                hVertexActivityShellReaction[ir][ik-1] = new TH1F( Form("VA%s_Shell_%s", VetrexString[ik].Data(), ReactionName[ir].Data() ) , Form("VA%s_Shell_%s", VetrexString[ik].Data(), ReactionName[ir].Data() ), 50, 0, 8000);
                hVertexActivityShellReaction[ir][ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
            }
            for(int il=0; il<2; il++) //loop over short long track
            {
                hVASubTrackLengtAllCondReaction[ir][il][ik] = new TH1F( Form("VA%sSubCondition_%s_%s_All", VetrexString[ik].Data(),ReactionName[ir].Data(), TrackLenght[il].Data()), Form("VA%sSubCondition_%s_%s_All", VetrexString[ik].Data(),ReactionName[ir].Data(), TrackLenght[il].Data()), 50, 0, 4000+ik*3000); 
                hVASubTrackLengtAllCondReaction[ir][il][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
                
                hVAOnlyIfTrackLenghtAllReaction[ir][il][ik]= new TH1F( Form("VA%s_IfThereAre_%s_%s_All", VetrexString[ik].Data(),OppositeLenght[il].Data(), ReactionName[ir].Data()), Form("VA%s_IfThereAre_%s_%s_All", VetrexString[ik].Data(), OppositeLenght[il].Data(), ReactionName[ir].Data()), 50, 0, 4000+ik*3000);  
                hVAOnlyIfTrackLenghtAllReaction[ir][il][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data() ) );
                
                if(ik>0)
                {
                    hVertexActivityIfTrackLenghtAllReactionShell[ir][il][ik-1] = new TH1F( Form("VA%s_IfThereAre_%s_%s_Shell", VetrexString[ik].Data(), OppositeLenght[il].Data(), ReactionName[ir].Data()), Form("VA%s_IfThereAre_%s_%s_Shell", VetrexString[ik].Data(), OppositeLenght[il].Data(), ReactionName[ir].Data()), 50, 0, 8000);  
                    hVertexActivityIfTrackLenghtAllReactionShell[ir][il][ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data() ) );
                }
            }
        }
        for(int ic=0; ic<SelectionNumber; ic++)
        {
            hVertexActivitySelections[ic][ik] = new TH1F( Form("VA%s_%s", VetrexString[ik].Data(), SelectionsName[ic].Data() ), Form("VA%s_%s", VetrexString[ik].Data(), SelectionsName[ic].Data() ), 50, 0, 4000+ik*3000);  
            hVertexActivitySelections[ic][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
            if(ik>0)
            {
                hVertexActivityShellSelection[ic][ik-1] = new TH1F( Form("VA%s_Shell_%s", VetrexString[ik].Data(), SelectionsName[ic].Data() ) , Form("VA%s_Shell_%s", VetrexString[ik].Data(), SelectionsName[ic].Data() ), 50, 0, 8000);
                hVertexActivityShellSelection[ic][ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
            }
            for(int il=0; il<2; il++) //loop over short long track
            {
                hVASubTrackLengtAllCondSelection[ic][il][ik] = new TH1F( Form("VA%sSubCondition_%s_%s_All", VetrexString[ik].Data(),SelectionsName[ic].Data(), TrackLenght[il].Data()), Form("VA%sSubCondition_%s_%s_All", VetrexString[ik].Data(),SelectionsName[ic].Data(), TrackLenght[il].Data()), 50, 0, 4000+ik*3000); 
                hVASubTrackLengtAllCondSelection[ic][il][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
                
                hVAOnlyIfTrackLenghtAllSelection[ic][il][ik]= new TH1F( Form("VA%s_IfThereAre_%s_%s_All", VetrexString[ik].Data(), OppositeLenght[il].Data(), SelectionsName[ic].Data()), Form("VA%s_IfThereAre_%s_%s_All", VetrexString[ik].Data(), OppositeLenght[il].Data(), SelectionsName[ic].Data()), 50, 0, 4000+ik*3000);  
                hVAOnlyIfTrackLenghtAllSelection[ic][il][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
                if(ik>0)
                {
                    hVertexActivityOnlyIfTrackLenghtAllSelectionShell[ic][il][ik-1] = new TH1F( Form("VA%s_IfThereAre_%s_%s_Shell", VetrexString[ik].Data(), OppositeLenght[il].Data(), SelectionsName[ic].Data()), Form("VA%s_IfThereAre_%s_%s_Shell", VetrexString[ik].Data(), OppositeLenght[il].Data(), SelectionsName[ic].Data()), 50, 0, 8000);  
                    hVertexActivityOnlyIfTrackLenghtAllSelectionShell[ic][il][ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data() ) );
                }
            }
        }
        for(int ig=0; ig<SizeOfParticleVector; ig++)
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
                
                hVASubTrackLengtParticleCondition[il][ig][ik] = new TH1F( Form("VA%sSubCondition_%s_%s", VetrexString[ik].Data(), TrackLenght[il].Data(), ParticleName[ig].Data()), Form("VA%sSubCondition_%s_%s", VetrexString[ik].Data(), TrackLenght[il].Data(), ParticleName[ig].Data()), 50, 0, 4000+ik*3000);  
                hVASubTrackLengtParticleCondition[il][ig][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data() ) );
                
                hVAOnlyIfTrackLenght[il][ig][ik] = new TH1F( Form("VA%s_IfThereAre_%s_%s", VetrexString[ik].Data(), OppositeLenght[il].Data(), ParticleName[ig].Data()), Form("VA%s_IfThereAre_%s_%s", VetrexString[ik].Data(), OppositeLenght[il].Data(), ParticleName[ig].Data()), 50, 0, 4000+ik*3000);  
                hVAOnlyIfTrackLenght[il][ig][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data() ) );
                
                if(ig==0) //For substracting all we don't need loop over particels
                {
                    hVertexActivitySubTrackLengtAllCondition[il][ik] = new TH1F( Form("VA%sSubCondition_%s_All", VetrexString[ik].Data(), TrackLenght[il].Data()), Form("VA%sSubCondition_%s_All", VetrexString[ik].Data(), TrackLenght[il].Data()), 50, 0, 4000+ik*3000);  
                    hVertexActivitySubTrackLengtAllCondition[il][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data() ) );
                    
                    hVertexActivityOnlyIfTrackLenghtAll[il][ik] = new TH1F( Form("VA%s_IfThereAre_%s_All", VetrexString[ik].Data(), OppositeLenght[il].Data()), Form("VA%s_IfThereAre_%s_All", VetrexString[ik].Data(), OppositeLenght[il].Data()), 50, 0, 4000+ik*3000);  
                    hVertexActivityOnlyIfTrackLenghtAll[il][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data() ) );
                    if(ik>0) //for shell we don't need 1x1x1 box
                    {
                        hVertexActivitySubTrackLengtAllConditionShell[il][ik-1] = new TH1F( Form("VA%sSubCondition_%s_All_Shell", VetrexString[ik].Data(), TrackLenght[il].Data()), Form("VA%sSubCondition_%s_All_Shell", VetrexString[ik].Data(), TrackLenght[il].Data()), 50, 0, 8000);  
                        hVertexActivitySubTrackLengtAllConditionShell[il][ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data() ) );
                    
                        hVertexActivityOnlyIfTrackLenghtAllShell[il][ik-1] = new TH1F( Form("VA%s_IfThereAre_%s_All_Shell", VetrexString[ik].Data(), OppositeLenght[il].Data()), Form("VA%s_IfThereAre_%s_All_Shell", VetrexString[ik].Data(), OppositeLenght[il].Data()), 50, 0, 8000);  
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
        for(int il=0; il<2; il++)
        {
            hVertexActivityTrackLength[il][ik] = new TH1F( Form("%sIfNo%sTracks", VertexName[ik].Data(), TrackLenght[il].Data()), Form("%sIfNo%sTracks", VertexName[ik].Data(), TrackLenght[il].Data()), 50, 0, 4000+ik*3000);  
            hVertexActivityTrackLength[il][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
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
        
        hRecParticleCounter[ig] = new TH1F( Form("NumberOfReconstructed%s", ParticleName[ig].Data() ), Form("NumberOfReconstructed%s", ParticleName[ig].Data() ) , 10, 0, 9 );  
        hRecParticleCounter[ig]->GetXaxis()->SetTitle( "Number of particles" );

        //TODO still in development
        for(int ic=0; ic<SelectionNumber; ic++)
        {
            for(int ir=0; ir<ReacTypeNum; ir++)
            {
                hParticleMomentumSplitSelection[ig][ic][ir] = new TH1F( Form("Short_%s_mom_%s_%s", ParticleName[ig].Data(), SelectionsName[ic].Data(), ReactionName[ir].Data() ), Form("Short_%s_mom_%s_%s", ParticleName[ig].Data(), SelectionsName[ic].Data(), ReactionName[ir].Data() ) , 50, 0, 1000); 
            }
        }
        for(int ic=0; ic<SelectionNumber; ic++)
        {
            hParticleMomentumSelections[ig][ic] = new TH1F( Form("Short_%s_mom_%s", ParticleName[ig].Data(), SelectionsName[ic].Data() ),Form("Short_%s_mom_%s", ParticleName[ig].Data(), SelectionsName[ic].Data() ) , 50,0,1000);
            hParticleMomentumSelections[ig][ic]->GetXaxis()->SetTitle("MeV/c");
        }
        for(int ir=0; ir<ReacTypeNum; ir++)
        {
            hParticleMomentumReactions[ig][ir] = new TH1F( Form("Short_%s_mom_%s", ParticleName[ig].Data(), ReactionName[ir].Data() ),Form("Short_%s_mom_%s", ParticleName[ig].Data(), ReactionName[ir].Data() ) , 50,0,1000);
            hParticleMomentumReactions[ig][ir]->GetXaxis()->SetTitle("MeV/c");
        }
        
    }
    for(int ic=0; ic<SelectionNumber; ic++)
    {
        for(int ir=0; ir<ReacTypeNum; ir++)
        {
            h_nuMomSplitSelections[ic][ir] = new TH1F( Form("nuMom%s_%s", SelectionsName[ic].Data(), ReactionName[ir].Data() ), Form("nuMom%s_%s", SelectionsName[ic].Data(), ReactionName[ir].Data() ), 50,0,6000);
        }
    }
    for(int ic=0; ic<SelectionNumber; ic++)
    {
        h_nuMomSelections[ic] = new TH1F( Form("nuMom%s", SelectionsName[ic].Data() ), Form("nuMom%s", SelectionsName[ic].Data() ), 50,0,6000);
        h_nuMomSelections[ic]->GetXaxis()->SetTitle( "MeV?" );
    }
    for(int ir=0; ir<ReacTypeNum; ir++)
    {
        h_nuMomReaction[ir] = new TH1F( Form("nuMom%s", ReactionName[ir].Data() ), Form("nuMom%s", ReactionName[ir].Data() ), 50,0,6000);
        h_nuMomReaction[ir]->GetXaxis()->SetTitle( "MeV?" );
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
        //if(iev == maxEvents-1 or selEvents >= 2000) //DEBUG MODE
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
        
        if(VERBOSE) cout<<"Interaction Mode "<<inputEvent->GetReactionType()<<endl;
        
        double VertexPosition[3]={}; //X-position, Y-position, Z-position
        VertexPosition[0] = trueVertex->GetX();
        VertexPosition[1] = trueVertex->GetY();
        VertexPosition[2] = trueVertex->GetZ();
        
        bool VetrexInDetector=true; //sometimes vertex is outside  detector boundries/fiducial volume
        bool TopologySelection[SelectionNumber]={}; 
        bool ReactionSelection[ReacTypeNum]={};  //CCQE 2p2h RES DIS COH
        
        if(VERBOSE) cout<<selEvents+1<<" Vertex position  X "<<VertexPosition[0]<<" Y "<< VertexPosition[1] <<" Z "<< VertexPosition[2]<<endl;
        
        if( VertexPosition[0]<FiducialVolume ||  VertexPosition[1]<FiducialVolume || VertexPosition[2]<FiducialVolume || VertexPosition[0]>SFGD_X-FiducialVolume ||  VertexPosition[1]>SFGD_Y-FiducialVolume || VertexPosition[2]>SFGD_Z-FiducialVolume)
        {
            VetrexInDetector=false;
            if(VERBOSE) cout<<"\033[1;31mOut of detector FV\033[0m"<<endl;
        }
        if(!VetrexInDetector) continue;
        
        //WARNING
        hVertexPosX->Fill(VertexPosition[0]);
        hVertexPosY->Fill(VertexPosition[1]);
        hVertexPosZ->Fill(VertexPosition[2]);
    
        hVertexPosXY->Fill(VertexPosition[0], VertexPosition[1]);
        hVertexPosXZ->Fill(VertexPosition[0], VertexPosition[2]);
        hVertexPosYZ->Fill(VertexPosition[1], VertexPosition[2]);
    
        double VertexDeposit[5][2]={}; //[VertexBox][0-PE, 1-MeV]
        double VertexDepositSubtracted[SizeOfParticleVector][5][2]={}; //[studied particle][VertexBox][0-PE, 1-MeV]
        double VertexDepositSubtractedLength[2][SizeOfParticleVector][5][2]={}; //[0-short, 1-long][studied particle][VertexBox][0-PE, 1-MeV]
        double VertexDepositSubtractedLengthAll[2][5][2]={}; //[0-short, 1-long][VertexBox][0-PE, 1-MeV]
        
        double VertexDepositShifted[SizeOfShiftVector][3][5][2]={}; //[VAshiftVector][X,Y,Z][VertexBox][0-PE, 1-MeV]
        double VertexParticleDeposit[SizeOfParticleVector][5][2]={}; //[particle][VertexBox][0-PE, 1-MeV]
        double VertexGarbageDeposit[5][2]={}; //[VertexBox][0-PE, 1-MeV]
        
        if(inputEvent->GetReactionType()==1) ReactionSelection[0]=true; //CCQE
        if(inputEvent->GetReactionType()==2) ReactionSelection[1]=true; //2p2h
        if( (inputEvent->GetReactionType() >=11 &&  inputEvent->GetReactionType()<=13 ) || inputEvent->GetReactionType()==17 || inputEvent->GetReactionType()==22 || inputEvent->GetReactionType()==23) ReactionSelection[2]=true; //RES
        if(inputEvent->GetReactionType()==26 || inputEvent->GetReactionType()==21) ReactionSelection[3]=true; //DIS
        if(inputEvent->GetReactionType()==16) ReactionSelection[4]=true; //COH
        //if(inputEvent->GetReactionType() >=31 && inputEvent->GetReactionType()<=46) ReactionSelection[4]=true; //TODO NC
        
        for(auto t:inputEvent->GetTrueTracks()) 
        {
            if( t->GetPDG() == 2212 && t->GetParentID()==0)
            {
                hprotonMomentum->Fill( t->GetMomentum() );
            }
        }

        int MuonCounter=0;
        for(auto t:inputEvent->GetTrueTracks()) 
        {
            if( t->GetPDG() == 13 && t->GetParentID()==0 && t->GetMaxEuclDist() > ShortTrack )
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
        int ParticleCounter[SizeOfParticleVector]={}; // [0-muon, 1-pion+, 2-proton, 3-pion-]
        int RecoParticleCounter[SizeOfParticleVector]={}; // [0-muon, 1-pion+, 2-proton, 3-pion-]
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
            if(TrackDistance <= ShortTrack)  TrackIdConditionLengthParticle[0].push_back( t->GetTrackID() );
            if(TrackDistance >  ShortTrack)  TrackIdConditionLengthParticle[1].push_back( t->GetTrackID() );

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
                    if(TrackDistance > ShortTrack) RecoParticleCounter[ig]++;
                    if(ig>0 && TrackDistance <= ShortTrack)  TrackLengthParticleCounter[0][ig-1]++; //short track
                    if(ig>0 && TrackDistance >  ShortTrack) TrackLengthParticleCounter[1][ig-1]++; //long track
                    
                    if(t->GetCosTheta()>0.7 || t->GetCosTheta()<-0.7) hEenrgyVsRangeRestricted[ig]->Fill(Edep, TrackDistance );
                    Edep=0;
                    EdepPE=0;
                }
                TrackIdLengthParticle[0][ig].push_back( t->GetTrackID() );
                TrackIdLengthParticle[1][ig].push_back( t->GetTrackID() );
                //We create vector keeping Id of either long or short tracks
                if( t->GetPDG() == ParticlePDG[ig] && TrackDistance <= ShortTrack) //if track short we get rid of him
                {
                    TrackIdLengthParticle[0][ig].pop_back();
                }
                if( t->GetPDG() == ParticlePDG[ig] && TrackDistance > ShortTrack) //if track long we get rid of him
                {
                    TrackIdLengthParticle[1][ig].pop_back();
                }
            }
            TrackIdLengthAll[0].push_back( t->GetTrackID() );
            TrackIdLengthAll[1].push_back( t->GetTrackID() );
            //TODO moze da się to łądniej zrobić
            if(t->GetPDG() == ParticlePDG[0] || t->GetPDG() == ParticlePDG[1] || t->GetPDG() == ParticlePDG[2] || t->GetPDG() == ParticlePDG[3]) 
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
        
        //This might be confusing but keep in mind [0-muon, 1-pion+, 2-proton, 3-pion-]
        if(RecoParticleCounter[0]==1 && RecoParticleCounter[1]==0 && RecoParticleCounter[2]==1 && RecoParticleCounter[3]==0) TopologySelection[0]=true;
        if(RecoParticleCounter[0]==1 && RecoParticleCounter[1]==0 && RecoParticleCounter[2]==0 && RecoParticleCounter[3]==0) TopologySelection[1]=true;
        if(RecoParticleCounter[0]==1 && RecoParticleCounter[1]==0 && RecoParticleCounter[2]>1 &&  RecoParticleCounter[3]==0 ) TopologySelection[2]=true;
        if(RecoParticleCounter[0]==1 && RecoParticleCounter[2]==1 && RecoParticleCounter[1]==1 && RecoParticleCounter[3]==0 ) TopologySelection[3]=true;
        if(!TopologySelection[0] && !TopologySelection[3]) TopologySelection[4]=true;
        
        for(auto t:inputEvent->GetTrueTracks())
        {
            for(int ig=0; ig<SizeOfParticleVector; ig++)
            {
                if(t->GetPDG() == ParticlePDG[ig] && t->GetMaxEuclDist() <= ShortTrack && t->GetParentID()==0)
                {
                    for(int ic=0; ic<SelectionNumber; ic++)
                    {
                        for(int ir=0; ir<ReacTypeNum; ir++)
                        {
                            if( TopologySelection[ic] && ReactionSelection[ir]) hParticleMomentumSplitSelection[ig][ic][ir]->Fill( t->GetMomentum() );
                        }
                    }
                    for(int ic=0; ic<SelectionNumber; ic++)
                    {
                        if( TopologySelection[ic] ) hParticleMomentumSelections[ig][ic]->Fill( t->GetMomentum() );
                    }
                    for(int ir=0; ir<ReacTypeNum; ir++)
                    {
                        if( ReactionSelection[ir] ) hParticleMomentumReactions[ig][ir]->Fill( t->GetMomentum() );
                    }
                }
            }
        }
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
                        for(int il=0; il<2; il++) //loop over short long DrawTrueTracks
                        {
                            for(int io=0; io<TrackIdLengthParticle[il][ig].size(); io++)
                            {
                                if( voxel->GetTrueTrackIDs()[0]==TrackIdLengthParticle[il][ig].at(io) )
                                {
                                    VertexDepositSubtractedLength[il][ig][ik][0]+=voxel->GetTruePE();
                                    VertexDepositSubtractedLength[il][ig][ik][1]+=voxel->GetTrueEdep();
                                }
                            }
                        }
                    }
                    for(int il=0; il<2; il++) //loop over short long DrawTrueTracks
                    {
                        for(int io=0; io<TrackIdLengthAll[il].size(); io++)
                        {
                            if( voxel->GetTrueTrackIDs()[0]==TrackIdLengthAll[il].at(io) )
                            {
                                VertexDepositSubtractedLengthAll[il][ik][0]+=voxel->GetTruePE();
                                VertexDepositSubtractedLengthAll[il][ik][1]+=voxel->GetTrueEdep();
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
        
        for(int ic=0; ic<SelectionNumber; ic++)
        {
            if(TopologySelection[ic]) h_nuMomSelections[ic]->Fill( nuMom );
        }
        for(int ir=0; ir<ReacTypeNum; ir++)
        {
            if( ReactionSelection[ir] ) h_nuMomReaction[ir]->Fill( nuMom );
        }
        for(int ic=0; ic<SelectionNumber; ic++)
        {
            for(int ir=0; ir<ReacTypeNum; ir++)
            {
               if(TopologySelection[ic] && ReactionSelection[ir]) h_nuMomSplitSelections[ic][ir]->Fill( nuMom );
            }
        }
        for(int ik=0; ik<5; ik++) //Filling histograms starts here
        {
            hVertexActivity[ik]->Fill(VertexDeposit[ik][0]); 
            VertexBranch[ik]=VertexDeposit[ik][1];
            if(ik>0) hVertexActivityShell[ik-1]->Fill(VertexDeposit[ik][0]-VertexDeposit[ik-1][0]);
            if(TrackLengthParticleCounter[0][0]==0 && TrackLengthParticleCounter[0][1]==0) hVertexActivityTrackLength[0][ik]->Fill(VertexDeposit[ik][0]); 
            if(TrackLengthParticleCounter[1][0]==0 && TrackLengthParticleCounter[1][1]==0) hVertexActivityTrackLength[1][ik]->Fill(VertexDeposit[ik][0]);
            if(VertexGarbageDeposit[ik][1] > epsilon) hVertexActivityByGarbage[ik]->Fill( VertexGarbageDeposit[ik][1] );
            
            for(int ic=0; ic<SelectionNumber; ic++) //TODO still in development
            {
                if(TopologySelection[ic])
                {
                    hVertexActivitySelections[ic][ik]->Fill(VertexDeposit[ik][0]);
                    if(ik>0) hVertexActivityShellSelection[ic][ik-1]->Fill( VertexDeposit[ik][0]-VertexDeposit[ik-1][0]);
                    for(int il=0; il<2; il++)
                    {
                        if( abs( VertexDeposit[ik][0]-VertexDepositSubtractedLengthAll[0][ik][0] ) > epsilon ) //If non zero we have short tracks
                        {
                            hVASubTrackLengtAllCondSelection[ic][il][ik]->Fill( VertexDepositSubtractedLengthAll[il][ik][0] );
                            hVAOnlyIfTrackLenghtAllSelection[ic][il][ik]->Fill( VertexDeposit[ik][0] );
                            if(ik>0) //TODO pomyśl nad warunkiem zeby porownywac to samo
                            {
                                hVertexActivityOnlyIfTrackLenghtAllSelectionShell[ic][il][ik-1]->Fill(VertexDeposit[ik][0]-VertexDeposit[ik-1][0] ); 
                            }
                        }
                    }
                }
            }
            for(int ir=0; ir<ReacTypeNum; ir++) //TODO still in development
            {
                if( ReactionSelection[ir])
                {
                    hVertexActivityReaction[ir][ik]->Fill(VertexDeposit[ik][0]);
                    if(ik>0) hVertexActivityShellReaction[ir][ik-1]->Fill( VertexDeposit[ik][0]-VertexDeposit[ik-1][0]);
                    for(int il=0; il<2; il++)
                    {
                        if( abs( VertexDeposit[ik][0]-VertexDepositSubtractedLengthAll[0][ik][0] ) > epsilon )
                        {
                            hVASubTrackLengtAllCondReaction[ir][il][ik]->Fill( VertexDepositSubtractedLengthAll[il][ik][0] );
                            hVAOnlyIfTrackLenghtAllReaction[ir][il][ik]->Fill( VertexDeposit[ik][0] );
                            if(ik>0) //TODO pomyśl nad warunkiem zeby porownywac to samo
                            {
                                hVertexActivityIfTrackLenghtAllReactionShell[ir][il][ik-1]->Fill(VertexDeposit[ik][0]-VertexDeposit[ik-1][0] ); 
                            }
                        }
                    }
                }
            }
            for(int ic=0; ic<SelectionNumber; ic++)
            {
                for(int ir=0; ir<ReacTypeNum; ir++)
                {
                    if(TopologySelection[ic] && ReactionSelection[ir])
                    {
                        hVASplitSelection[ic][ir][ik]->Fill(VertexDeposit[ik][0]);
                        for(int il=0; il<2; il++)
                        {   
                            hVertexActivitySubTrackLengtSplitSelection[ic][ir][il][ik-1]->Fill(VertexDepositSubtractedLengthAll[il][ik][0]);
                            if( abs( VertexDeposit[ik][0]-VertexDepositSubtractedLengthAll[0][ik][0] ) > epsilon )
                            {
                                if(ik>0) //TODO pomyśl nad warunkiem zeby porownywac to samo
                                {
                                    hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][il][ik-1]->Fill(VertexDeposit[ik][0]-VertexDeposit[ik-1][0] ); 
                                } 
                            }
                        }
                    }
                }
            }
            for(int ig=0; ig<SizeOfParticleVector; ig++)
            {
                hVertexActivitySubtractedParticle[ig][ik]->Fill(VertexDepositSubtracted[ig][ik][0]);
                hEnergyDepoParticle[ig][ik]->Fill( VertexParticleDeposit[ig][ik][1] );
                if(ig==0 && VertexParticleDeposit[0][0][1] > epsilon) hEnergyDepoParticleNonZero[ik]->Fill( VertexParticleDeposit[ig][ik][1] );
                for(int is=0; is<SizeOfParticleVector-1; is++) //loop over condition particle
                {
                    for(int il=0; il<ParticleNumberGO; il++) //loop over # of condition particles
                    {
                        if(ParticleCounter[is+1]==ParticleNumberCut[il]) hEnergyDepoParticleWithCuts[il][is][ig][ik]->Fill( VertexParticleDeposit[ig][ik][1] );
                        if(ParticleCounter[is+1]==ParticleNumberCut[il] && ig>0 && VertexParticleDeposit[ig][0][1] > epsilon)
                        {
                            hEnergyDepoParticleWithCutsNonZero[il][is][ig-1][ik]->Fill( VertexParticleDeposit[ig][ik][1] );
                        }
                    }
                }
                for(int il=0; il<2; il++)
                {
                    hVertexActivitySubTrackLengtParticle[il][ig][ik]->Fill(VertexDepositSubtractedLength[il][ig][ik][0]);
                    if( abs( VertexDeposit[ik][0]-VertexDepositSubtractedLength[il][ig][ik][0]) > epsilon )// if non zero we have short tracks
                    //TODO mozna pomyśleć zmienic [ik]->[4]
                    {
                        hVASubTrackLengtParticleCondition[il][ig][ik]->Fill( VertexDepositSubtractedLength[il][ig][ik][0] );
                        hVAOnlyIfTrackLenght[il][ig][ik]->Fill( VertexDeposit[ik][0] );
                    }
                    if(ig==0 && abs( VertexDeposit[ik][0]-VertexDepositSubtractedLengthAll[0][ik][0] ) > epsilon )
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
            if(ik>0 && abs( VertexDeposit[ik][0]-VertexDepositSubtractedLengthAll[0][ik][0] ) <= epsilon )
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
        for(int ig=0; ig<SizeOfParticleVector; ig++) //loop over conditioned particle/ no muon(-1)
        {
            hRecParticleCounter[ig]->Fill(RecoParticleCounter[ig]);
        }
        t1.Fill();
        selEvents++; 
        //inputEvent->DrawTrueTracks(true,"trueTracks");
    } //End of loop over events
    if (FileOutput->IsOpen())
    {
        FileOutput->cd();
        h_nuMom->Write("",TObject::kOverwrite); 
        hprotonMomentum->Write("",TObject::kOverwrite); 
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
            hRecParticleCounter[ig]->Write("",TObject::kOverwrite);
        }
        //WARNING
        hVertexPosX->Write("",TObject::kOverwrite);
        hVertexPosY->Write("",TObject::kOverwrite);
        hVertexPosZ->Write("",TObject::kOverwrite);
    
        hVertexPosXY->Write("",TObject::kOverwrite);
        hVertexPosXZ->Write("",TObject::kOverwrite);
        hVertexPosYZ->Write("",TObject::kOverwrite);
        
        FolderHist2D->cd();
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
                    hVAOnlyIfTrackLenght[il][ig][ik]->Write("",TObject::kOverwrite); 
                }
            }
            for(int ig=0; ig<SizeOfParticleVector; ig++)
            {
                for(int ik=0; ik<5; ik++)
                {
                    hVASubTrackLengtParticleCondition[il][ig][ik]->Write("",TObject::kOverwrite); 
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
                for(int iw=0; iw<3; iw++) //loop over coordiantes XYZ
                {
                    hVertexActivityShifted[ih][iw][ik]->Write("",TObject::kOverwrite); 
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
        for(int il=0; il<2; il++)
        {
            for(int ik=0; ik<5; ik++)
            {
                hVertexActivityTrackLength[il][ik]->Write("",TObject::kOverwrite);
            }
        }
        for(int ig=0; ig<SizeOfParticleVector; ig++)
        {
            hMeanScatteringRange[ig]->Write("",TObject::kOverwrite);
        }
        //////TODO still in development
        for(int ic=0; ic<SelectionNumber; ic++)
        {
            FolderParticleSelections[ic]->cd();
            h_nuMomSelections[ic]->Write("",TObject::kOverwrite);
            for(int ik=0; ik<5; ik++)
            {   
                hVertexActivitySelections[ic][ik]->Write("",TObject::kOverwrite);
            }
            for(int ik=0; ik<4; ik++)
            {   
                hVertexActivityShellSelection[ic][ik]->Write("",TObject::kOverwrite);
            }
            for(int ik=0; ik<5; ik++)
            { 
                for(int il=LongOrShort; il<2; il++)
                {
                    hVASubTrackLengtAllCondSelection[ic][il][ik]->Write("",TObject::kOverwrite);
                }
            }
            for(int ik=0; ik<5; ik++)
            { 
                for(int il=LongOrShort; il<2; il++)
                {
                    hVAOnlyIfTrackLenghtAllSelection[ic][il][ik]->Write("",TObject::kOverwrite);
                }
            }
            for(int ik=0; ik<4; ik++)
            { 
                for(int il=LongOrShort; il<2; il++)
                {
                    hVertexActivityOnlyIfTrackLenghtAllSelectionShell[ic][il][ik]->Write("",TObject::kOverwrite);
                }
            }
            for(int ig=0; ig<SizeOfParticleVector; ig++)
            {
                hParticleMomentumSelections[ig][ic]->Write("",TObject::kOverwrite);
            }
        }
        //////TODO still in development
        for(int ir=0; ir<ReacTypeNum; ir++)
        {
            FolderReaction[ir]->cd();
            h_nuMomReaction[ir]->Write("",TObject::kOverwrite);
            for(int ik=0; ik<5; ik++)
            {   
                hVertexActivityReaction[ir][ik]->Write("",TObject::kOverwrite);
            }
            for(int ik=0; ik<4; ik++)
            {   
                hVertexActivityShellReaction[ir][ik]->Write("",TObject::kOverwrite);
            }
            for(int ik=0; ik<5; ik++)
            { 
                for(int il=LongOrShort; il<2; il++)
                {
                    hVASubTrackLengtAllCondReaction[ir][il][ik]->Write("",TObject::kOverwrite);
                }
            }
            for(int ik=0; ik<5; ik++)
            { 
                for(int il=LongOrShort; il<2; il++)
                {
                    hVAOnlyIfTrackLenghtAllReaction[ir][il][ik]->Write("",TObject::kOverwrite);
                }
            }
            for(int ik=0; ik<4; ik++)
            { 
                for(int il=LongOrShort; il<2; il++)
                {
                    hVertexActivityIfTrackLenghtAllReactionShell[ir][il][ik]->Write("",TObject::kOverwrite);
                }
            }
            for(int ig=0; ig<SizeOfParticleVector; ig++)
            {
                hParticleMomentumReactions[ig][ir]->Write("",TObject::kOverwrite);
            }
        } 
        for(int ic=0; ic<SelectionNumber; ic++)
        {
            FolderSplitedSelection[ic]->cd();
            for(int ir=0; ir<ReacTypeNum; ir++)
            {
                h_nuMomSplitSelections[ic][ir]->Write("",TObject::kOverwrite);
            }
            for(int ir=0; ir<ReacTypeNum; ir++)
            {
                for(int ik=0; ik<5; ik++)
                {
                    hVASplitSelection[ic][ir][ik]->Write("",TObject::kOverwrite);
                }
            }
            for(int ig=0; ig<SizeOfParticleVector; ig++)
            {
                for(int ir=0; ir<ReacTypeNum; ir++)
                {
                    hParticleMomentumSplitSelection[ig][ic][ir]->Write("",TObject::kOverwrite);
                }
            }
            for(int ir=0; ir<ReacTypeNum; ir++)
            {
                for(int ik=0; ik<5; ik++)
                {
                    for(int il=LongOrShort; il<2; il++)
                    {
                        hVertexActivitySubTrackLengtSplitSelection[ic][ir][il][ik]->Write("",TObject::kOverwrite);
                    }
                }
            }
            for(int ir=0; ir<ReacTypeNum; ir++)
            {
                for(int ik=0; ik<4; ik++)
                {
                    for(int il=LongOrShort; il<2; il++)
                    {
                        hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][il][ik]->Write("",TObject::kOverwrite);
                    }
                }
            }
        }
        FileOutput->cd();
        t1.Write();
        FileOutput->Close();
    }    
    cout << endl << "\033[1;32mGenerated output: \033[0m" << fileOut.Data() << endl;
    handleEndOfExecution();
}
