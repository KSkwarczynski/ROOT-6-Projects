#include <TH2F.h>
#include <fstream>
#include <iostream>
#include "TStyle.h"

void HitSubstractComparisonPlot()
{
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(111);
    gStyle->SetPalette(1,0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetOptStat(0);
    
    const int NumberOfFiles = 3; //we only consider those files with substracted deposits, default one is alway included
    TString Directory="/Users/kolos/Desktop/sFGD/Output/";
    TString DirectoryPlots="/Users/kolos/Desktop/sFGD/Plots/GENIE/Hits/";
    //TString Directory="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/Output/";
    //TString DirectoryPlots="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/PlotOutput/VertexActivity/GENIE/";
    TString FileName[4]={"VertexAcivityHits_Output", "VertexAcivityHits_SubstractedMu_Output", "VertexAcivityHits_SubstractedPi+_Output", "VertexAcivityHits_SubstractedProton_Output" };
    TString VetrexString[5]={"1x1x1" , "3x3x3" , "5x5x5", "7x7x7", "9x9x9"};
    TFile *file[4];
    
    TH1F *hVertexActivityXY[NumberOfFiles+1][5];
    TH1F *hVertexActivityXZ[NumberOfFiles+1][5];
    TH1F *hVertexActivityYZ[NumberOfFiles+1][5];
    
    TString ParticleName[3]={"Muon", "Pion+", "Proton"};
    TString VertexName[5]={"VertexActivity1x1", "VertexActivity3x3", "VertexActivity5x5", "VertexActivity7x7", "VertexActivity9x9"};
    
    TTree *t1[NumberOfFiles+1];
    for(int i=0; i<NumberOfFiles+1; i++)
    {
        file[i] = new TFile( Form("%s%s.root", Directory.Data() , FileName[i].Data()) ,"READ");
        //cout<<Form("%s%s.root", Directory.Data() , FileName[i].Data())<<endl;
        if (file[i]->IsOpen() )
        {
            printf("File opened successfully\n");
        }  
        file[i]->cd();
        for(int ik=0; ik<5; ik++)
        {
            hVertexActivityXY[i][ik] = (TH1F*) file[i]->Get( Form("%s_XY",VertexName[ik].Data() ) );
            hVertexActivityXY[i][ik]->GetYaxis()->SetTitleOffset(1.4);
            
            hVertexActivityXZ[i][ik] = (TH1F*) file[i]->Get( Form("%s_XZ",VertexName[ik].Data() ) );
            hVertexActivityXZ[i][ik]->GetYaxis()->SetTitleOffset(1.4);
         
            hVertexActivityYZ[i][ik] = (TH1F*) file[i]->Get( Form("%s_YZ",VertexName[ik].Data() ) );
            hVertexActivityYZ[i][ik]->GetYaxis()->SetTitleOffset(1.4);
        }
    }
    TCanvas *Canvas[300];
    TLegend *legend[300];
    int canvasCounter=0;

    for(int ik=0; ik<5; ik++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        hVertexActivityXY[0][ik]->SetLineColorAlpha(kRed, 1);
        hVertexActivityXY[0][ik]->SetLineWidth(1.5);
            
        hVertexActivityXY[1][ik]->SetLineColorAlpha(kBlue, 1);
        hVertexActivityXY[1][ik]->SetLineWidth(1.5);
            
        hVertexActivityXY[2][ik]->SetLineColorAlpha(kGreen, 1);
        hVertexActivityXY[2][ik]->SetLineWidth(1.5);
        
        hVertexActivityXY[3][ik]->SetLineColorAlpha(kMagenta, 1);
        hVertexActivityXY[3][ik]->SetLineWidth(1.5);
        
        hVertexActivityXY[1][ik]->Draw("");
        hVertexActivityXY[0][ik]->Draw("SAME");
        hVertexActivityXY[2][ik]->Draw("SAME");
        hVertexActivityXY[3][ik]->Draw("SAME");
           
        legend[canvasCounter] = new TLegend(0.55,0.6,0.9,0.9);
        legend[canvasCounter]->AddEntry(hVertexActivityXY[0][ik],"VA_Default","l");
        legend[canvasCounter]->AddEntry(hVertexActivityXY[1][ik], Form( "VA_Subtracted%s", ParticleName[0].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivityXY[2][ik], Form( "VA_Subtracted%s", ParticleName[1].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivityXY[3][ik], Form( "VA_Subtracted%s", ParticleName[2].Data() ),"l");
        legend[canvasCounter]->SetTextSize(0.035);
        legend[canvasCounter]->Draw();
            
        gPad->Modified();
        Canvas[canvasCounter]->Print(Form("%sXYComparisonAll_%s.pdf",DirectoryPlots.Data(), VertexName[ik].Data() )); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    for(int ik=0; ik<5; ik++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        hVertexActivityXZ[0][ik]->SetLineColorAlpha(kRed, 1);
        hVertexActivityXZ[0][ik]->SetLineWidth(1.5);
            
        hVertexActivityXZ[1][ik]->SetLineColorAlpha(kBlue, 1);
        hVertexActivityXZ[1][ik]->SetLineWidth(1.5);
            
        hVertexActivityXZ[2][ik]->SetLineColorAlpha(kGreen, 1);
        hVertexActivityXZ[2][ik]->SetLineWidth(1.5);
        
        hVertexActivityXZ[3][ik]->SetLineColorAlpha(kMagenta, 1);
        hVertexActivityXZ[3][ik]->SetLineWidth(1.5);
        
        hVertexActivityXZ[1][ik]->Draw("");
        hVertexActivityXZ[0][ik]->Draw("SAME");
        hVertexActivityXZ[2][ik]->Draw("SAME");
        hVertexActivityXZ[3][ik]->Draw("SAME");
           
        legend[canvasCounter] = new TLegend(0.55,0.6,0.9,0.9);
        legend[canvasCounter]->AddEntry(hVertexActivityXZ[0][ik],"VA_Default","l");
        legend[canvasCounter]->AddEntry(hVertexActivityXZ[1][ik], Form( "VA_Subtracted%s", ParticleName[0].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivityXZ[2][ik], Form( "VA_Subtracted%s", ParticleName[1].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivityXZ[3][ik], Form( "VA_Subtracted%s", ParticleName[2].Data() ),"l");
        legend[canvasCounter]->SetTextSize(0.035);
        legend[canvasCounter]->Draw();
            
        gPad->Modified();
        Canvas[canvasCounter]->Print(Form("%sXZComparisonAll_%s.pdf",DirectoryPlots.Data(), VertexName[ik].Data() )); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    for(int ik=0; ik<5; ik++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        hVertexActivityYZ[0][ik]->SetLineColorAlpha(kRed, 1);
        hVertexActivityYZ[0][ik]->SetLineWidth(1.5);
            
        hVertexActivityYZ[1][ik]->SetLineColorAlpha(kBlue, 1);
        hVertexActivityYZ[1][ik]->SetLineWidth(1.5);
            
        hVertexActivityYZ[2][ik]->SetLineColorAlpha(kGreen, 1);
        hVertexActivityYZ[2][ik]->SetLineWidth(1.5);
        
        hVertexActivityYZ[3][ik]->SetLineColorAlpha(kMagenta, 1);
        hVertexActivityYZ[3][ik]->SetLineWidth(1.5);
        
        hVertexActivityYZ[1][ik]->Draw("");
        hVertexActivityYZ[0][ik]->Draw("SAME");
        hVertexActivityYZ[2][ik]->Draw("SAME");
        hVertexActivityYZ[3][ik]->Draw("SAME");
           
        legend[canvasCounter] = new TLegend(0.55,0.6,0.9,0.9);
        legend[canvasCounter]->AddEntry(hVertexActivityYZ[0][ik],"VA_Default","l");
        legend[canvasCounter]->AddEntry(hVertexActivityYZ[1][ik], Form( "VA_Subtracted%s", ParticleName[0].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivityYZ[2][ik], Form( "VA_Subtracted%s", ParticleName[1].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivityYZ[3][ik], Form( "VA_Subtracted%s", ParticleName[2].Data() ),"l");
        legend[canvasCounter]->SetTextSize(0.035);
        legend[canvasCounter]->Draw();
            
        gPad->Modified();
        Canvas[canvasCounter]->Print(Form("%sYZComparisonAll_%s.pdf",DirectoryPlots.Data(), VertexName[ik].Data() )); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
}
