#include <TH2F.h>
#include <fstream>
#include <iostream>
#include "TStyle.h"

void SubstractComparisonPlot()
{
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(111);
    gStyle->SetPalette(1,0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetOptStat(0);
    
    const int NumberOfFiles = 3; //we only consider those files with substracted deposits, default one is alway included
    TString Directory="/Users/kolos/Desktop/sFGD/Output/";
    TString DirectoryPlots="/Users/kolos/Desktop/sFGD/Plots/";
    //TString Directory="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/Output/";
    //TString DirectoryPlots="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/PlotOutput/VertexActivity/";
    TString FileName[4]={"VertexAcivity_Output", "VertexAcivity_SubstractedMu_Output", "VertexAcivity_SubstractedPi_Output", "VertexAcivity_SubstractedProton_Output" };
    TString VetrexString[5]={"1x1x1" , "3x3x3" , "5x5x5", "7x7x7", "9x9x9"};
    TFile *file[4];
    
    TH1F *hVertexActivity[NumberOfFiles+1][5];
    TH1F *hVertexActivityParticleCuts[2][3][5];
    TH2F *hMomentumVsRange[3];
    TH2F *hEnergyVsRange[3];
    TH2F *hEenrgyVsRangehEenrgyVsRangeRestricted[3];
    TH2F *hEnergyPeVsRange[3];
    
    TString ParticleName[3]={"Muon", "Pion", "Proton"};
    
    TString VertexName[5]={"VertexActivity1x1x1", "VertexActivity3x3x3", "VertexActivity5x5x5", "VertexActivity7x7x7", "VertexActivity9x9x9"};
    
    TTree *t1[NumberOfFiles+1];
    for(int i=0; i<NumberOfFiles+1; i++)
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
    TCanvas *Canvas[300];
    TLegend *legend[300];
    int canvasCounter=0;
    for(int ig=0; ig<NumberOfFiles; ig++)
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
    for(int ik=0; ik<5; ik++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        hVertexActivity[0][ik]->SetLineColorAlpha(kRed, 1);
        hVertexActivity[0][ik]->SetLineWidth(1.5);
            
        hVertexActivity[1][ik]->SetLineColorAlpha(kBlue, 1);
        hVertexActivity[1][ik]->SetLineWidth(1.5);
            
        hVertexActivity[2][ik]->SetLineColorAlpha(kGreen, 1);
        hVertexActivity[2][ik]->SetLineWidth(1.5);
        
        hVertexActivity[3][ik]->SetLineColorAlpha(kMagenta, 1);
        hVertexActivity[3][ik]->SetLineWidth(1.5);
        
        hVertexActivity[1][ik]->Draw("");
        hVertexActivity[0][ik]->Draw("SAME");
        hVertexActivity[2][ik]->Draw("SAME");
        hVertexActivity[3][ik]->Draw("SAME");
           
        legend[canvasCounter] = new TLegend(0.48,0.6,0.9,0.9);
        legend[canvasCounter]->AddEntry(hVertexActivity[0][ik],"VA_Default","l");
        legend[canvasCounter]->AddEntry(hVertexActivity[1][ik], Form( "VA_Substracted%s", ParticleName[0].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivity[2][ik], Form( "VA_Substracted%s", ParticleName[1].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivity[3][ik], Form( "VA_Substracted%s", ParticleName[2].Data() ),"l");
        legend[canvasCounter]->SetTextSize(0.02);
        legend[canvasCounter]->Draw();
            
        gPad->Modified();
        Canvas[canvasCounter]->Print(Form("%sComparisonAll_%s.pdf",DirectoryPlots.Data(), VertexName[ik].Data() )); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    for(int ik=0; ik<NumberOfFiles; ik++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        hMomentumVsRange[ik]->Draw("COLZ");
        
        gPad->Modified();
        Canvas[canvasCounter]->Print(Form("%sMomentumVsRange%s.pdf", DirectoryPlots.Data(), ParticleName[ik].Data(), ParticleName[ik].Data() )); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    for(int ik=0; ik<NumberOfFiles; ik++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        hEnergyVsRange[ik]->Draw("COLZ");
        
        gPad->Modified();
        Canvas[canvasCounter]->Print(Form("%sEnergyVsRange%s.pdf",DirectoryPlots.Data(), ParticleName[ik].Data() )); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    for(int ik=0; ik<NumberOfFiles; ik++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        hEnergyPeVsRange[ik]->Draw("COLZ");
        
        gPad->Modified();
        Canvas[canvasCounter]->Print(Form("%sEnergyPeVsRange_%s.pdf",DirectoryPlots.Data(), ParticleName[ik].Data() )); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    for(int ik=0; ik<NumberOfFiles; ik++)
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
    
    TLeaf *VertexLeaf[5][NumberOfFiles+1]; //[vertex][file]
    TLeaf *ParticleCounterLeaf[3];
    for(int ik=0; ik<5; ik++)
    {
        for(int i=0; i<4; i++)
        {
            VertexLeaf[ik][i] = t1[i]->GetLeaf(Form("VertexBranch%s", VetrexString[ik].Data() ) );
        }
    }
    for(int ik=0; ik<3; ik++)
    {
        ParticleCounterLeaf[ik] = t1[0]->GetLeaf( Form("%sCounterBranch" , ParticleName[ik].Data()) );
    }
    int max=t1[0]->GetEntries();
    TH1F *ParticleEnergyLoss[3][5]; //[Particle][VertexBox]
    TH1F *ParticleEnergyLossParticleCuts[2][3][5]; //[number of particles either one or two][Particle][VertexBox]
    for(int ig=0; ig<NumberOfFiles; ig++)
    {
        for(int ik=0; ik<5; ik++)
        {
            ParticleEnergyLoss[ig][ik] = new TH1F( Form("%sEnergyLoss_%s", ParticleName[ig].Data(), VetrexString[ik].Data() ), Form("%sEnergyLoss_%s", ParticleName[ig].Data(), VetrexString[ik].Data() ) , 20, 0, 40+40*ik);
            ParticleEnergyLoss[ig][ik]->GetXaxis()->SetTitle("Energy [MeV??]");
            for(int it=0; it<2; it++)
            {
                ParticleEnergyLossParticleCuts[it][ig][ik] = new TH1F( Form("%sEnergyLoss_%s_if_%i%s", ParticleName[ig].Data(), VetrexString[ik].Data(), it+1,ParticleName[ig].Data() ), Form("%sEnergyLoss_%s_if_%i%s", ParticleName[ig].Data(), VetrexString[ik].Data(), it+1,ParticleName[ig].Data() ) , 20, 0, 40+40*ik);
                ParticleEnergyLossParticleCuts[it][ig][ik]->GetXaxis()->SetTitle("Energy [MeV??]");
            }
        }
    }
    for(int i=0; i<max; i++) //loop over each event
    {
        for(int ic=0; ic<3; ic++)
        {
           ParticleCounterLeaf[ic]->GetBranch()->GetEntry(i);
        }
        for(int ic=0; ic<5; ic++) //loop over VA boxes
        {
            for(int ik=0; ik<NumberOfFiles; ik++) //loop over file number
            {
                VertexLeaf[ic][ik]->GetBranch()->GetEntry(i); 
            }
            for(int ig=0; ig<NumberOfFiles; ig++)
            {
                ParticleEnergyLoss[ig][ic]->Fill(VertexLeaf[ic][0]->GetValue()-VertexLeaf[ic][1+ig]->GetValue() );
                if(ig>0)
                {
                    for(int ip=1; ip<3; ip++) //one or two particles in events
                    {
                        if(ParticleCounterLeaf[ig]->GetValue()==ip && ig>0 )
                        {
                            ParticleEnergyLossParticleCuts[ip-1][ig][ic]->Fill(VertexLeaf[ic][0]->GetValue()-VertexLeaf[ic][1+ig]->GetValue() );
                        }
                    }
                }
                
            }
        }
    }
    for(int ig=0; ig<NumberOfFiles; ig++)
    {
        for(int ik=0; ik<5; ik++)
        {
            Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
            ParticleEnergyLoss[ig][ik]->Draw();
            gPad->Modified();
            Canvas[canvasCounter]->Print( Form("%s%sEnergyLoss_%s.pdf", DirectoryPlots.Data(), ParticleName[ig].Data(), VetrexString[ik].Data()) ); 
            delete Canvas[canvasCounter];
            canvasCounter++;
            if(ig>0)
            {
                for(int ic=0; ic<2; ic++)
                {
                    Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);  
                    ParticleEnergyLossParticleCuts[ic][ig][ik]->Draw();
                    Canvas[canvasCounter]->Print( Form("%s%sEnergyLoss_%sif_%i%s.pdf", DirectoryPlots.Data(), ParticleName[ig].Data(), VetrexString[ik].Data(),ic+1,ParticleName[ig].Data()) ); 
                    delete Canvas[canvasCounter];
                    canvasCounter++;
                }
            }
        }
    }
}
