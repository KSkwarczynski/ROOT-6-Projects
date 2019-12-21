//
//
// César Jesús-Valls    (cjesus@ifae.es)
// Kamil Skwarczyński   (kamil.janusz.skwarczynski@cern.ch)
//

#define THIS_NAME vertexHitA
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
TString fileOut        = "/mnt/home/kskwarczynski/t2k-nd280-upgrade/Output/VertexAcivityHits_Output.root";
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
Hit*            unpackHit;
     
ND280SFGDVoxel* trueVertex;
ND280SFGDVoxel* recoVertex;

#include "../src/tools/global_tools.cc" 
#include "../src/tools/reconstruction_methods.hh" 

void vertexHitA() 
{
    parseArguments();
    linkFilesToTTrees();
    std::vector<ND280SFGDHit*> mppc_hits;

    TString VertexName[5]={"VertexActivity1x1", "VertexActivity3x3", "VertexActivity5x5", "VertexActivity7x7", "VertexActivity9x9"};
    TString VetrexString[5]={"1x1" , "3x3" , "5x5", "7x7", "9x9" };
    TString VertexNameShifted[3][2]={ {"X","Y"}, {"X","Z"}, {"Y","Z"} };
    double VertexBox[5]={0., 1., 2., 3., 4.};
    
    TH1F *hVertexActivityXY[5];
    TH1F *hVertexActivityXZ[5];
    TH1F *hVertexActivityYZ[5];
    
    TH1F *hVertexActivityShellXY[4];
    TH1F *hVertexActivityShellXZ[4];
    TH1F *hVertexActivityShellYZ[4];
    
    int VAshiftVector[2]={1, -1}; //Adjust position of vertex
    const int SizeOfShiftVector= (sizeof(VAshiftVector)/sizeof(*VAshiftVector));
    
    TH1F *hVertexActivityXYShifted[SizeOfShiftVector][2][5]; //[VAshiftVector][X,Y][VetrexString]
    TH1F *hVertexActivityXZShifted[SizeOfShiftVector][2][5]; //[VAshiftVector][X,Z][VetrexString]
    TH1F *hVertexActivityYZShifted[SizeOfShiftVector][2][5]; //[VAshiftVector][Y,Z][VetrexString]
    
    
    for(int ik=0; ik<5; ik++)
    {
        hVertexActivityXY[ik] = new TH1F( Form("%s_XY",VertexName[ik].Data() ) , Form("%s_XY",VertexName[ik].Data() ) , 50, 0, 2000+ik*2000);  
        hVertexActivityXY[ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
        
        hVertexActivityXZ[ik] = new TH1F( Form("%s_XZ",VertexName[ik].Data() ) , Form("%s_XZ",VertexName[ik].Data() ) , 50, 0, 2000+ik*2000);  
        hVertexActivityXZ[ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
        
        hVertexActivityYZ[ik] = new TH1F( Form("%s_YZ",VertexName[ik].Data() ) , Form("%s_YZ",VertexName[ik].Data() ) , 50, 0, 2000+ik*2000);  
        hVertexActivityYZ[ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
            
        if(ik>0)
        {
            hVertexActivityShellXY[ik-1] = new TH1F( Form("%sShell_XY",VertexName[ik].Data()) , Form("%sShell_XY",VertexName[ik].Data()), 50, 0, 2000+ik*2000);  
            hVertexActivityShellXY[ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
            
            hVertexActivityShellXZ[ik-1] = new TH1F( Form("%sShell_XZ",VertexName[ik].Data()) , Form("%sShell_XY",VertexName[ik].Data()), 50, 0, 2000+ik*2000);  
            hVertexActivityShellXZ[ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
            
            hVertexActivityShellYZ[ik-1] = new TH1F( Form("%sShell_YZ",VertexName[ik].Data()) , Form("%sShell_YZ",VertexName[ik].Data()), 50, 0, 2000+ik*2000);  
            hVertexActivityShellYZ[ik-1]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
        }
        
        for(int ig=0; ig<2; ig++)
        {
            for(int ih=0; ih<SizeOfShiftVector; ih++)
            {
                hVertexActivityXYShifted[ih][ig][ik] = new TH1F( Form("%s_XY_Shifted_%d_%s",VertexName[ik].Data(), VAshiftVector[ih], VertexNameShifted[0][ig].Data()) ,Form("%s_XY_Shifted_%d_%s",VertexName[ik].Data(), VAshiftVector[ih], VertexNameShifted[0][ig].Data()), 50, 0, 2000+ik*2000);  
                hVertexActivityXYShifted[ih][ig][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
                
                hVertexActivityXZShifted[ih][ig][ik] = new TH1F( Form("%s_XZ_Shifted_%d_%s",VertexName[ik].Data(), VAshiftVector[ih], VertexNameShifted[1][ig].Data()) ,Form("%s_XZ_Shifted_%d_%s",VertexName[ik].Data(), VAshiftVector[ih], VertexNameShifted[1][ig].Data()), 50, 0, 2000+ik*2000);  
                hVertexActivityXZShifted[ih][ig][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
                
                hVertexActivityYZShifted[ih][ig][ik] = new TH1F( Form("%s_YZ_Shifted_%d_%s",VertexName[ik].Data(), VAshiftVector[ih], VertexNameShifted[2][ig].Data()) ,Form("%s_YZ_Shifted_%d_%s",VertexName[ik].Data(), VAshiftVector[ih], VertexNameShifted[2][ig].Data()), 50, 0, 2000+ik*2000);  
                hVertexActivityYZShifted[ih][ig][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]",VetrexString[ik].Data() ) );
            }
        }
    }
    // loop over events
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

        bool VetrexInDetector=true; //sometimes vertex is outside  detector boundries
        int FiducialVolume=1; //set how far from detector boundries we want to study Vertex Activity 
        if( VertexPosition[0]<FiducialVolume ||  VertexPosition[1]<FiducialVolume || VertexPosition[2]<FiducialVolume || VertexPosition[0]>SFGD_X-FiducialVolume ||  VertexPosition[1]>SFGD_Y-FiducialVolume || VertexPosition[2]>SFGD_Z-FiducialVolume)
        {
            VetrexInDetector=false;
            cout<<"\033[1;31mOut of detector\033[0m"<<endl;
        }
        
        if(!VetrexInDetector) continue;
        
        double VertexDepositXY[5]={};
        double VertexDepositXZ[5]={};
        double VertexDepositYZ[5]={};
        
        double VertexDepositShiftedXY[SizeOfShiftVector][2][5]={};
        double VertexDepositShiftedXZ[SizeOfShiftVector][2][5]={};
        double VertexDepositShiftedYZ[SizeOfShiftVector][2][5]={};
        
        for(int ik=0; ik<5; ik++) //loop over boxes
        {
            for(UInt_t i=0; i<inputEvent->GetHits().size(); i++) // loop over hits
            {
                ND280SFGDHit* hit = inputEvent->GetHits()[i];
                bool StudiedShape[3][2]={}; //
                bool StudiedShapeShifted[SizeOfShiftVector][3][2]={};
                if(hit->GetView() == 0) //XY
                {
                    if( (abs(hit->GetX()-VertexPosition[0])<=VertexBox[ik]) ) StudiedShape[0][0]=true;
                    if( (abs(hit->GetY()-VertexPosition[1])<=VertexBox[ik]) ) StudiedShape[0][1]=true;
                    
                    if( StudiedShape[0][0] && StudiedShape[0][1] ) 
                    {
                        VertexDepositXY[ik]+=hit->GetPE();
                    }
                    for(int ih=0; ih<SizeOfShiftVector; ih++)
                    {
                        if( (abs(VertexPosition[0]+VAshiftVector[ih]-hit->GetX())<=VertexBox[ik]) ) StudiedShapeShifted[ih][0][0]=true;
                        if( (abs(VertexPosition[1]+VAshiftVector[ih]-hit->GetY())<=VertexBox[ik]) ) StudiedShapeShifted[ih][0][1]=true;
                       
                        if(  StudiedShapeShifted[ih][0][0] && StudiedShape[0][1]) //shift in X
                        {
                            VertexDepositShiftedXY[ih][0][ik]+=hit->GetPE();
                        }
                        if(  StudiedShape[0][0] && StudiedShapeShifted[ih][0][1]) //shift in Y
                        {
                            VertexDepositShiftedXY[ih][1][ik]+=hit->GetPE();
                        }
                    }
                }
                if(hit->GetView() == 1) //XZ
                {
                    if( (abs(hit->GetX()-VertexPosition[0])<=VertexBox[ik]) ) StudiedShape[1][0]=true;
                    if( (abs(hit->GetZ()-VertexPosition[2])<=VertexBox[ik]) ) StudiedShape[1][1]=true;
                    
                    if(  StudiedShape[1][0] && StudiedShape[1][1]  ) 
                    {
                        VertexDepositXZ[ik]+=hit->GetPE();
                    }
                    for(int ih=0; ih<SizeOfShiftVector; ih++)
                    {
                        if( (abs(VertexPosition[0]+VAshiftVector[ih]-hit->GetX())<=VertexBox[ik]) ) StudiedShapeShifted[ih][1][0]=true;
                        if( (abs(VertexPosition[2]+VAshiftVector[ih]-hit->GetZ())<=VertexBox[ik]) ) StudiedShapeShifted[ih][1][1]=true;
                       
                        if(  StudiedShapeShifted[ih][1][0] && StudiedShape[1][1]) //shift in X
                        {
                            VertexDepositShiftedXZ[ih][0][ik]+=hit->GetPE();
                        }
                        if(  StudiedShape[1][0] && StudiedShapeShifted[ih][1][1]) //shift in Z
                        {
                            VertexDepositShiftedXZ[ih][1][ik]+=hit->GetPE();
                        }
                    }
                }
                if(hit->GetView() == 2) //YZ
                {
                    if( (abs(hit->GetY()-VertexPosition[1])<=VertexBox[ik]) ) StudiedShape[2][0]=true;
                    if( (abs(hit->GetZ()-VertexPosition[2])<=VertexBox[ik]) ) StudiedShape[2][1]=true;
                    
                    if(  StudiedShape[2][0] && StudiedShape[2][1]) 
                    {
                        VertexDepositYZ[ik]+=hit->GetPE();
                    }
                    for(int ih=0; ih<SizeOfShiftVector; ih++)
                    {
                        if( (abs(VertexPosition[1]+VAshiftVector[ih]-hit->GetY())<=VertexBox[ik]) ) StudiedShapeShifted[ih][2][0]=true;
                        if( (abs(VertexPosition[2]+VAshiftVector[ih]-hit->GetZ())<=VertexBox[ik]) ) StudiedShapeShifted[ih][2][1]=true;
                       
                        if(  StudiedShapeShifted[ih][2][0] && StudiedShape[2][1]) //shift in Y
                        {
                            VertexDepositShiftedYZ[ih][0][ik]+=hit->GetPE();
                        }
                        if(  StudiedShape[2][0] && StudiedShapeShifted[ih][2][1]) //shift in Z
                        {
                            VertexDepositShiftedYZ[ih][1][ik]+=hit->GetPE();
                        }
                    }
                }
            } // end loop over hits

            hVertexActivityXY[ik]->Fill(VertexDepositXY[ik]);
            hVertexActivityXZ[ik]->Fill(VertexDepositXZ[ik]);
            hVertexActivityYZ[ik]->Fill(VertexDepositYZ[ik]);
            
            if(ik>0)
            {
                hVertexActivityShellXY[ik-1]->Fill(VertexDepositXY[ik]-VertexDepositXY[ik-1]);
                hVertexActivityShellXZ[ik-1]->Fill(VertexDepositXZ[ik]-VertexDepositXZ[ik-1]);
                hVertexActivityShellYZ[ik-1]->Fill(VertexDepositYZ[ik]-VertexDepositYZ[ik-1]);
            }
            for(int ih=0; ih<SizeOfShiftVector; ih++)
            {
                for(int ig=0; ig<2; ig++)
                {
                    hVertexActivityXYShifted[ih][ig][ik]->Fill(VertexDepositShiftedXY[ih][ig][ik]);
                    hVertexActivityXZShifted[ih][ig][ik]->Fill(VertexDepositShiftedXZ[ih][ig][ik]);
                    hVertexActivityYZShifted[ih][ig][ik]->Fill(VertexDepositShiftedYZ[ih][ig][ik]);
                }
            }
        } //end loop over boxes
        selEvents++;
    } //end loop over events
    
    if (FileOutput->IsOpen())
    {
        FileOutput->cd();
        for(int ik=0; ik<5; ik++)
        {
            hVertexActivityXY[ik]->Write("",TObject::kOverwrite); 
            hVertexActivityXZ[ik]->Write("",TObject::kOverwrite);
            hVertexActivityYZ[ik]->Write("",TObject::kOverwrite);
        }
        for(int ik=0; ik<4; ik++)
        {
            hVertexActivityShellXY[ik]->Write("",TObject::kOverwrite); 
            hVertexActivityShellXZ[ik]->Write("",TObject::kOverwrite); 
            hVertexActivityShellYZ[ik]->Write("",TObject::kOverwrite);
        }
        for(int ik=0; ik<5; ik++)
        {
            for(int ih=0; ih<SizeOfShiftVector; ih++)
            {
                //// Could be in one loop but for convinience in reading output file this is advisable
                for(int ig=0; ig<2; ig++)
                {
                    hVertexActivityXYShifted[ih][ig][ik]->Write("",TObject::kOverwrite); 
                }
                for(int ig=0; ig<2; ig++)
                {
                    hVertexActivityXZShifted[ih][ig][ik]->Write("",TObject::kOverwrite);
                }
                for(int ig=0; ig<2; ig++)
                {
                    hVertexActivityYZShifted[ih][ig][ik]->Write("",TObject::kOverwrite);
                }
            }
        }

        FileOutput->Close();
    }   
    
    cout << endl << "\033[1;32mGenerated output: \033[0m" << fileOut.Data() << endl;

    handleEndOfExecution();
}
