#include <TH1.h>
#include <TH2F.h>
#include <fstream>
#include <iostream>
#include "TStyle.h"
#include <TColor.h>

void DynamicComparisonPlot()
{
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(111);
    gStyle->SetPalette(1,0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetOptStat(0);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);

    TString Directory="/Users/kolos/Desktop/sFGD/Output/";
    TString DirectoryPlots="/Users/kolos/Desktop/sFGD/Plots/Dynamic/";
    //TString Directory="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/Output/";
    //TString DirectoryPlots="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/PlotOutput/VertexActivity/";
    
    TString FileName="DynamicVertexAcivity_Output";
    TString VertexName[5]={"VertexActivity1x1x1", "VertexActivity3x3x3", "VertexActivity5x5x5", "VertexActivity7x7x7", "VertexActivity9x9x9"};
    TString VetrexStringCategories[3]={"Front", "Transverse", "Back"};
    TString ParticleName[3]={"Muon", "Pion+", "Proton"};
    TString VetrexString[5]={"1x1x1" , "3x3x3" , "5x5x5", "7x7x7", "9x9x9"};
    TString TrackLenght[2]={"Short", "Long"};
    
    TFile *file;
        
    TH1F *hVertexActivityDynamicCategory[3][5];
    
    TH1F *hVertexActivitySubTrackLengtAllCondition[3][2][5];
    TH1F *hVertexActivityOnlyIfTrackLenghtAll[3][2][5];

    
    file = new TFile( Form("%s%s.root", Directory.Data() , FileName.Data()) ,"READ");
    if (file->IsOpen() )
    {
        printf("File opened successfully\n");
    }  
    
    TDirectory *FolderCut = (TDirectory*)file->Get("FolderCut"); 
    TDirectory *FolderSubstractedTrackLengthAll = (TDirectory*)file->Get("FolderSubstractedTrackLengthAll"); 
    file->cd();
    for(int ik=0; ik<5; ik++)
    {
        for(int ib=0; ib<3; ib++) //loop over box shape
        {
            hVertexActivityDynamicCategory[ib][ik] = (TH1F*) file->Get( Form("Step%iDynamic_Cat%s", ik ,VetrexStringCategories[ib].Data()) );
            hVertexActivityDynamicCategory[ib][ik]->GetYaxis()->SetTitleOffset(1.4);
            for(int il=0; il<2; il++) //loop over short or long track
            {
                hVertexActivitySubTrackLengtAllCondition[ib][il][ik] = (TH1F*) FolderSubstractedTrackLengthAll->Get( Form("Step%i_%s_SubCondition_%s_All", ik, VetrexStringCategories[ib].Data(), TrackLenght[il].Data()) ); 
                hVertexActivitySubTrackLengtAllCondition[ib][il][ik]->GetYaxis()->SetTitleOffset(1.4);
               
                hVertexActivityOnlyIfTrackLenghtAll[ib][il][ik] = (TH1F*) FolderSubstractedTrackLengthAll->Get( Form("Step%i_%s_IfThereAre_%s_All", ik, VetrexStringCategories[ib].Data(), TrackLenght[il].Data()) ); 
                hVertexActivityOnlyIfTrackLenghtAll[ib][il][ik]->GetYaxis()->SetTitleOffset(1.4);
                
            }
        }
    }
    
    TCanvas *Canvas[300];
    TLegend *legend[300];
    int canvasCounter=0;
 ///////////////////////////////// DRAWING PART STARTS HERE/////////////////////////////
    for(int ik=0; ik<5; ik++)
    {
        for(int ib=0; ib<3; ib++)
        {
            for(int il=0; il<2; il++)
            {  
                Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
                
                hVertexActivityOnlyIfTrackLenghtAll[ib][il][ik]->SetLineColorAlpha(kBlue, 1);
                hVertexActivityOnlyIfTrackLenghtAll[ib][il][ik]->SetLineWidth(1.5);
                
                hVertexActivitySubTrackLengtAllCondition[ib][il][ik]->SetLineColorAlpha(kRed, 1);
                hVertexActivitySubTrackLengtAllCondition[ib][il][ik]->SetLineWidth(1.5);
                
                hVertexActivitySubTrackLengtAllCondition[ib][il][ik]->Draw("");
                hVertexActivityOnlyIfTrackLenghtAll[ib][il][ik]->Draw("SAME");
                
                legend[canvasCounter] = new TLegend(0.55,0.7,0.9,0.9);
                legend[canvasCounter]->AddEntry(hVertexActivitySubTrackLengtAllCondition[ib][il][ik], Form( "VA_Subtracted_%s", TrackLenght[il].Data() ),"l");
                legend[canvasCounter]->AddEntry(hVertexActivityOnlyIfTrackLenghtAll[ib][il][ik], Form( "VA_Default" ),"l");
                legend[canvasCounter]->SetTextSize(0.04);
                legend[canvasCounter]->Draw();
            
                gPad->Modified();
                Canvas[canvasCounter]->Print( Form("%sAll_%s_Subtracted_VA%s_%s.pdf", DirectoryPlots.Data(), VetrexStringCategories[ib].Data(), VetrexString[ik].Data(), TrackLenght[il].Data()) ); 
                delete Canvas[canvasCounter];
                canvasCounter++;
            }
        } 
    }
}
