#include <TH2F.h>
#include <fstream>
#include <iostream>
#include "TStyle.h"

void ComparisonPlot()
{
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(111);
    gStyle->SetPalette(1,0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetOptStat(0);
    
    TString Directory="/Users/kolos/Desktop/sFGD/Output/";
    TString DirectoryPlots="/Users/kolos/Desktop/sFGD/Plots/";
    TString FileName[4]={"VertexAcivity_Output", "VertexAcivity_SubstractedMu_Output", "VertexAcivity_SubstractedPi_Output", "VertexAcivity_SubstractedProton_Output" };
    TString VetrexString[5]={"1x1x1" , "3x3x3" , "5x5x5", "7x7x7", "9x9x9"};
    TFile *file[2];
    
    TH1F *hVertexActivity[4][5];
    TH2F *hMomentumVsRange[3];
    TH2F *hEnergyVsRange[3];
    TH2F *hEenrgyVsRangehEenrgyVsRangeRestricted[3];
    TH2F *hEnergyPeVsRange[3];
    
    TString ParticleName[3]={"Muon", "Pion", "Proton"};
    
    TString VertexName[5]={"VertexActivity1x1x1", "VertexActivity3x3x3", "VertexActivity5x5x5", "VertexActivity7x7x7", "VertexActivity9x9x9"};
    
    TTree *t1[4];
    for(int i=0; i<3; i++) ////ZAMIEN NA 4
    {
        file[i] = new TFile(Form("%s%s.root", Directory.Data() , FileName[i].Data()),"READ");
        if (file[i]->IsOpen() )
        {
            printf("File opened successfully\n");
        }  
        file[i]->cd();
        for(int ik=0; ik<5; ik++)
        {
            hVertexActivity[i][ik] = (TH1F*) file[i]->Get(VertexName[ik]);
            hVertexActivity[i][ik]->GetYaxis()->SetTitleOffset(1.4);
        }
        if(i==0)
        {
            for(int ik=0; ik<3; ik++)
            {
                hMomentumVsRange[ik] = (TH2F*) file[i]->Get( Form("MomentumVsRange_%s", ParticleName[ik].Data() ) );
                hMomentumVsRange[ik]->GetYaxis()->SetTitleOffset(1.4);
                
                hEnergyVsRange[ik] = (TH2F*) file[i]->Get( Form("EnergyVsRange_%s", ParticleName[ik].Data()) );
                hEnergyVsRange[ik]->GetYaxis()->SetTitleOffset(1.4);
                
                hEnergyPeVsRange[ik] = (TH2F*) file[i]->Get( Form("EnergyPeVsRange_%s", ParticleName[ik].Data()) );
                hEnergyPeVsRange[ik]->GetYaxis()->SetTitleOffset(1.4);
                
                hEenrgyVsRangehEenrgyVsRangeRestricted[ik] = (TH2F*) file[i]->Get( Form("EnergyVsRange_Restricted_%s", ParticleName[ik].Data()) );
                hEenrgyVsRangehEenrgyVsRangeRestricted[ik]->GetYaxis()->SetTitleOffset(1.4);
            }
        }
        
        file[i]->GetObject("t1",t1[i]);
    }
    TCanvas *Canvas[100];
    TLegend *legend[100];
    int canvasCounter=0;
    for(int ig=0; ig<2; ig++) /////ZAMIEN NA 3
    {
        for(int ik=0; ik<5; ik++)
        {
            Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        
            hVertexActivity[0][ik]->SetLineColorAlpha(kRed, 1);
            hVertexActivity[0][ik]->SetLineWidth(1.5);
            
            hVertexActivity[ig+1][ik]->SetLineColorAlpha(kBlue, 1);
            hVertexActivity[ig+1][ik]->SetLineWidth(1.5);
            
            
            hVertexActivity[ig+1][ik]->Draw("");
            hVertexActivity[0][ik]->Draw("SAME");
            
            legend[canvasCounter] = new TLegend(0.48,0.6,0.9,0.9);
            legend[canvasCounter]->AddEntry(hVertexActivity[0][ik],"VA_Default","l");
            legend[canvasCounter]->AddEntry(hVertexActivity[ig+1][ik], Form( "VA_Substracted%s", ParticleName[ig].Data() ),"l");
            legend[canvasCounter]->SetTextSize(0.05);
            legend[canvasCounter]->Draw();
            
            gPad->Modified();
            Canvas[canvasCounter]->Print(Form("%sComparisonForSub_%s_%s.pdf",DirectoryPlots.Data(), ParticleName[ig].Data(), VertexName[ik].Data() )); 
            delete Canvas[canvasCounter];
            canvasCounter++;
        }
    }
    for(int ik=0; ik<3; ik++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        hMomentumVsRange[ik]->Draw("COLZ");
        
        gPad->Modified();
        Canvas[canvasCounter]->Print(Form("%sMomentumVsRange%s.pdf", DirectoryPlots.Data(), ParticleName[ik].Data(), ParticleName[ik].Data() )); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    for(int ik=0; ik<3; ik++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        hEnergyVsRange[ik]->Draw("COLZ");
        
        gPad->Modified();
        Canvas[canvasCounter]->Print(Form("%sEnergyVsRange%s.pdf",DirectoryPlots.Data(), ParticleName[ik].Data() )); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    for(int ik=0; ik<3; ik++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        hEnergyPeVsRange[ik]->Draw("COLZ");
        
        gPad->Modified();
        Canvas[canvasCounter]->Print(Form("%sEnergyPeVsRange_%s.pdf",DirectoryPlots.Data(), ParticleName[ik].Data() )); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    for(int ik=0; ik<3; ik++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        hEenrgyVsRangehEenrgyVsRangeRestricted[ik]->Draw("COLZ");
        
        gPad->Modified();
        Canvas[canvasCounter]->Print(Form("%sEnergyVsRange_Restricted_%s.pdf",DirectoryPlots.Data(), ParticleName[ik].Data() )); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    /////
    gStyle->Reset(0);
    
    TLeaf *VertexLeaf1x1x1[4];
    TLeaf *VertexLeaf3x3x3[4];
    for(int i=0; i<3; i++)
    {
        VertexLeaf1x1x1[i] = t1[i]->GetLeaf("VertexBranch1x1x1");
        VertexLeaf3x3x3[i] = t1[i]->GetLeaf("VertexBranch3x3x3");
    }
    int max=t1[0]->GetEntries();
    TH1F *ParticleEnergyLoss[3][2]; //[Particle][VertexBox]
    for(int ig=0; ig<2; ig++)
    {
        for(int ik=0; ik<2; ik++)
        {
            ParticleEnergyLoss[ig][ik]=new TH1F( Form("%sEnergyLoss_%s", ParticleName[ig].Data(), VetrexString[ik].Data() ), Form("%sEnergyLoss_%s", ParticleName[ig].Data(), VetrexString[ik].Data() ) , 100, 0, 6000);
        }
    }
    for(int i=0; i<max; i++)
    {
        for(int ik=0; ik<3; ik++) ///zamien na 4
        {
            VertexLeaf1x1x1[ik]->GetBranch()->GetEntry(i); 
            VertexLeaf3x3x3[ik]->GetBranch()->GetEntry(i);
        }
        for(int ig=0; ig<2; ig++)
        {
            ParticleEnergyLoss[ig][0]->Fill(VertexLeaf1x1x1[0]->GetValue()-VertexLeaf1x1x1[1+ig]->GetValue() );
            ParticleEnergyLoss[ig][1]->Fill(VertexLeaf3x3x3[0]->GetValue()-VertexLeaf3x3x3[1+ig]->GetValue() );
        }
    }
    for(int ig=0; ig<2; ig++)
    {
        for(int ik=0; ik<2; ik++)
        {
            Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
            ParticleEnergyLoss[ig][ik]->Draw();
            gPad->Modified();
            Canvas[canvasCounter]->Print( Form("%s%sEnergyLoss_%s.pdf", DirectoryPlots.Data(), ParticleName[ig].Data(), VetrexString[ik].Data()) ); 
            delete Canvas[canvasCounter];
            canvasCounter++;
        }
    }
}
