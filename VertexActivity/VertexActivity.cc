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
TString fileOut        = "/mnt/home/kskwarczynski/t2k-nd280-upgrade/Output/VertexAcivity_Output.root";
TString fileIn         = "/mnt/home/kskwarczynski/t2k-nd280-upgrade/Output/VertexActInput.root";
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
    
    //TH3F *VoxelTruePE= new TH3F("VoxelTruePE","VoxelTruePE",SFGD_X, 0.5, SFGD_X+0.5, SFGD_Y, 0.5, SFGD_Y+0.5, SFGD_Z, 0.5, SFGD_Z+0.5);
    
    TString VertexName[5]={"VertexActivity1x1x1", "VertexActivity3x3x3", "VertexActivity5x5x5", "VertexActivity7x7x7", "VertexActivity9x9x9"};
    TString VertexNameShifted[3]={"X", "Y", "Z"};
    TString VetrexString[5]={"1x1x1" , "3x3x3" , "5x5x5", "7x7x7", "9x9x9"};
    TString VetrexStringCategories[3]={"Front", "Transverse", "Back"};
    
    double VertexBox[5]={0., 1., 2., 3., 4.}; // 1x1x1, 3x3x3, 5x5x5 and so on...
    double VertexBoxNew[5]={0.5, 1.5, 2.5, 3.5, 4.5}; // used in Dynamic boxes
    int VAshiftVector[2]={1, -1}; //Adjust position of vertex
    const int SizeOfShiftVector= (sizeof(VAshiftVector)/sizeof(*VAshiftVector));
    
    TH1F *hVertexActivity[5];
    TH1F *hVertexActivityShell[4];
    TH1F *hVertexActivityDynamic[5];
    TH1F *hVertexActivityDynamicCategory[3][5];
    TH1F *hVertexActivityShifted[SizeOfShiftVector][3][5]; // Which array represent what [VAshiftVector][X,Y,Z][VetrexString]
    
    for(int ik=0; ik<5; ik++)
    {
        hVertexActivity[ik] = new TH1F(VertexName[ik], VertexName[ik], 50, 0, 2500+ik*2500);  
        hVertexActivity[ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
        
        if(ik>0)
        {
            hVertexActivityShell[ik-1] = new TH1F( Form("%sShell",VertexName[ik].Data()) , Form("%sShell",VertexName[ik].Data()), 50, 0, 2500+ik*2500);  
            hVertexActivityShell[ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
        }
        hVertexActivityDynamic[ik] = new TH1F( Form("%sDynamic",VertexName[ik].Data()) , Form("%sDynamic",VertexName[ik].Data()), 50, 0, 2500+ik*2500);  
        hVertexActivityDynamic[ik]->GetXaxis()->SetTitle( Form("Energy deposit in Dynamicbox %s [p.e.]",VetrexString[ik].Data() ) );
            
        for(int ig=0; ig<3; ig++)
        {
            hVertexActivityDynamicCategory[ig][ik] = new TH1F( Form("Step%fDynamic_Cat%s", ik ,VetrexStringCategories[ig])) , Form("Step%fDynamic_Cat%s", ik ,VetrexStringCategories[ig])), 50, 0, 2500+ik*2500);  
            hVertexActivityDynamicCategory[ig][ik]->GetXaxis()->SetTitle( Form("Energy deposit in Dynamicbox %s [p.e.]",VetrexString[ik].Data() ) );
            for(int ih=0; ih<SizeOfShiftVector; ih++)
            {
                hVertexActivityShifted[ih][ig][ik] = new TH1F( Form("%sShifted_%d_%s",VertexName[ik].Data(), VAshiftVector[ih], VertexNameShifted[ig].Data()) ,Form("%sShifted_%d_%s",VertexName[ik].Data(), VAshiftVector[ih] ,VertexNameShifted[ig].Data()), 50, 0, 2500+ik*2500);  
                hVertexActivityShifted[ih][ig][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
            }
        }
    }
    
    int DirtyTrick[5]={};
    DirtyTrick[0]=1;
    for (int iev=evtIni; iev<evtFin; iev++)
    {
        if(iev == maxEvents-1 or selEvents >= maxSelEvents) 
        //if(iev == maxEvents-1 or selEvents >= 10) //DEBUG MODE
        {   
            break;
        }
        
        mppc_hits = getEventMPPChits(iev); 
        
        // looking for vertex position
        convertVtxCoordiantes(inputEvent->GetTrueVertex());
        convertCoordinates(inputEvent->GetVoxels());

        ND280SFGDVoxel* trueVertex;
        trueVertex = inputEvent->GetTrueVertex();
        
        double VertexPosition[3]={}; //X-position, Y-position, Z-position
        VertexPosition[0] = trueVertex->GetX();
        VertexPosition[1] = trueVertex->GetY();
        VertexPosition[2] = trueVertex->GetZ();
        cout<<selEvents<<" Vertex position  X "<<VertexPosition[0]<<" Y "<< VertexPosition[1] <<" Z "<< VertexPosition[2]<<endl;
        
        double VertexDeposit[5]={}; //[VertexBox]
        double VertexDepositDynamic[5]={}; //[VertexBox]
        double VertexDepositDynamicCategory[3][5]={}; //[VertexBox]
        double VertexDepositShifted[SizeOfShiftVector][3][5]={}; //[VAshiftVector][X,Y,Z][VertexBox]
        
        bool VetrexInDetector=true; //sometimes vertex is outside  detector boundries
        int FiducialVolume=1; //set how far from detector boundries we want to study Vertex Activity 
        if( VertexPosition[0]<FiducialVolume ||  VertexPosition[1]<FiducialVolume || VertexPosition[2]<FiducialVolume || VertexPosition[0]>SFGD_X-FiducialVolume ||  VertexPosition[1]>SFGD_Y-FiducialVolume || VertexPosition[2]>SFGD_Z-FiducialVolume)
        {
            VetrexInDetector=false;
            cout<<"\033[1;31mOut of detector\033[0m"<<endl;
        }
        if(!VetrexInDetector) continue;
        
        double TrackParameters[4]={};
        int MuonCounter=0;
        for(auto t:inputEvent->GetTrueTracks()) 
        {
            if( t->GetPDG() == 13)
            {
                cout<<"True track PDG= "<<t->GetPDG()<<" range "<<t->GetRange()<<" mom "<<t->GetMomentum()<<" cosTheta "<<t->GetCosTheta()<<endl;
                if(MuonCounter==0 || t->GetMomentum()>TrackParameters[1]) //in case there are two muons we want with higher momentum
                {
                    TrackParameters[0]=t->GetRange();
                    TrackParameters[1]=t->GetMomentum();
                    TrackParameters[2]=t->GetCosTheta();
                }
                MuonCounter++;
            }
        }
        for(auto voxel:inputEvent->GetVoxels())
        {   
            //VoxelTruePE->Fill(voxel->GetX(), voxel->GetY(), voxel->GetZ(), voxel->GetTruePE());
            for(int ik=0; ik<5; ik++)
            {
                //A->DistToVoxel(B);
                bool StudiedShape[3]={}; //[X, Y, Z]
                if( abs(VertexPosition[0]-voxel->GetX() ) <= VertexBox[ik]) StudiedShape[0]=true;
                if( abs(VertexPosition[1]-voxel->GetY() ) <= VertexBox[ik]) StudiedShape[1]=true;
                if( abs(VertexPosition[2]-voxel->GetZ() ) <= VertexBox[ik]) StudiedShape[2]=true;                
                //if(ik==0) cout<<"Voxel  X  "<<voxel->GetX()<< "  Y " <<voxel->GetY() <<"  Z  "<< voxel->GetZ()<<endl;
                //if(ik==0) cout<<"  X+1/2  "<<VertexPosition[0]+VertexBox[ik]<< "  X-1/2 " <<VertexPosition[0]-VertexBox[ik]<<endl;
                if(StudiedShape[0] && StudiedShape[1]&& StudiedShape[2])
                {
                    VertexDeposit[ik]+=voxel->GetTruePE();
                }
                bool StudiedShapeDynamic[3]={}; //[X, Y, Z]
                if(TrackParameters[2]>=0.5)
                {
                    if(voxel->GetX()<VertexPosition[0]+VertexBoxNew[ik]-1+DirtyTrick[ik] && voxel->GetX()>VertexPosition[0]-VertexBoxNew[ik]+1-DirtyTrick[ik]) StudiedShapeDynamic[0]=true;
                    if(voxel->GetY()<VertexPosition[1]+VertexBoxNew[ik]-1+DirtyTrick[ik] && voxel->GetY()>VertexPosition[1]-VertexBoxNew[ik]+1-DirtyTrick[ik]) StudiedShapeDynamic[1]=true;
                    if(voxel->GetZ()<VertexPosition[2]+VertexBoxNew[ik]+2 && voxel->GetZ()>VertexPosition[2]-VertexBoxNew[ik]) StudiedShapeDynamic[2]=true;
                    if(StudiedShapeDynamic[0] && StudiedShapeDynamic[1] && StudiedShapeDynamic[2])
                    {
                        VertexDepositDynamicCategory[0][ik]+=voxel->GetTruePE();
                    }
                }
                if(TrackParameters[2]<0.5 && TrackParameters[2]>=-0.5)
                {
                    if(voxel->GetX()<VertexPosition[0]+VertexBoxNew[ik]+1 && voxel->GetX()>VertexPosition[0]-VertexBoxNew[ik]-1) StudiedShapeDynamic[0]=true;
                    if(voxel->GetY()<VertexPosition[1]+VertexBoxNew[ik]+1 && voxel->GetY()>VertexPosition[1]-VertexBoxNew[ik]-1) StudiedShapeDynamic[1]=true;
                    if(voxel->GetZ()<VertexPosition[2]+VertexBoxNew[ik]-1+DirtyTrick[ik] && voxel->GetZ()>VertexPosition[2]-VertexBoxNew[ik]+1-DirtyTrick[ik]) StudiedShapeDynamic[2]=true; 
                    if(StudiedShapeDynamic[0] && StudiedShapeDynamic[1] && StudiedShapeDynamic[2])
                    {
                        VertexDepositDynamicCategory[1][ik]+=voxel->GetTruePE();
                    }
                }
                if(TrackParameters[2]<-0.5)
                {
                    if(voxel->GetX()<VertexPosition[0]+VertexBoxNew[ik]-1+DirtyTrick[ik] && voxel->GetX()>VertexPosition[0]-VertexBoxNew[ik]+1-DirtyTrick[ik]) StudiedShapeDynamic[0]=true;
                    if(voxel->GetY()<VertexPosition[1]+VertexBoxNew[ik]-1+DirtyTrick[ik]&& voxel->GetY()>VertexPosition[1]-VertexBoxNew[ik]+1-DirtyTrick[ik]) StudiedShapeDynamic[1]=true;
                    if(voxel->GetZ()<VertexPosition[2]+VertexBoxNew[ik] && voxel->GetZ()>VertexPosition[2]-VertexBoxNew[ik]-2) StudiedShapeDynamic[2]=true; 
                    if(StudiedShapeDynamic[0] && StudiedShapeDynamic[1] && StudiedShapeDynamic[2])
                    {
                        VertexDepositDynamicCategory[2][ik]+=voxel->GetTruePE();
                    }
                } 
                if(StudiedShapeDynamic[0] && StudiedShapeDynamic[1] && StudiedShapeDynamic[2])
                {
                    VertexDepositDynamic[ik]+=voxel->GetTruePE();
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
        for(int ik=0; ik<5; ik++)
        {
            hVertexActivity[ik]->Fill(VertexDeposit[ik]); 
            if(ik>0) hVertexActivityShell[ik-1]->Fill(VertexDeposit[ik]-VertexDeposit[ik-1]);
            hVertexActivityDynamic[ik]->Fill(VertexDepositDynamic[ik]); 
            for(int ig=0; ig<3; ig++)
            {
                if(VertexDepositDynamicCategory[ig][ik]>0) hVertexActivityDynamicCategory[ig][ik]->Fill(VertexDepositDynamicCategory[ig][ik]);
            }
            for(int ih=0; ih<SizeOfShiftVector; ih++)
            {
                for(int ig=0; ig<3; ig++)
                {
                    hVertexActivityShifted[ih][ig][ik]->Fill(VertexDepositShifted[ih][ig][ik]);
                }
            }
        }
        //inputEvent->DrawHitsAndVoxels(true,"event");
        //inputEvent->DrawVoxelsTruePE(true,"truePE");
        selEvents++;
    }
    //TCanvas* h3 = new TCanvas("h3", "3D display", 800, 600);
    //VoxelTruePE->Draw("BOX2");
    
    if (FileOutput->IsOpen())
    {
        FileOutput->cd();
        for(int ik=0; ik<5; ik++) //// Could be in one loop but for convinience in reading output file this is advisable
        {
            hVertexActivity[ik]->Write("",TObject::kOverwrite); 
        }
        for(int ik=0; ik<4; ik++)
        {
            hVertexActivityShell[ik]->Write("",TObject::kOverwrite); 
        }
        for(int ik=0; ik<5; ik++)
        {
            hVertexActivityDynamic[ik]->Write("",TObject::kOverwrite); 
        }
         for(int ik=0; ik<5; ik++)
        {
            for(int ig=0; ig<3; ig++)
            {
                hVertexActivityDynamicCategory[ig][ik]->Write("",TObject::kOverwrite); 
            }
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
        FileOutput->Close();
    }
    cout << endl << "\033[1;32mGenerated output: \033[0m" << fileOut.Data() << endl;
    handleEndOfExecution();
}
