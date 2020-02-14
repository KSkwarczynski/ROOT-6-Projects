#include <TH1.h>
#include <TH2F.h>
#include <fstream>
#include <iostream>
#include "TStyle.h"
#include <TColor.h>

void ComparisonPlot()
{
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(111);
    gStyle->SetPalette(1,0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetOptStat(0);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
  
    //const int NumberOfFiles = 0; //we only consider those files with substracted deposits, default one is alway included
    const int SizeOfParticleVector = 3;
    const int ParticleNumberGO = 3; //Number of particles we put condition on, starting from 0
    
    TString Directory="/Users/kolos/Desktop/sFGD/Output/";
    TString DirectoryPlots="/Users/kolos/Desktop/sFGD/Plots/";
    //TString Directory="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/Output/";
    //TString DirectoryPlots="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/PlotOutput/VertexActivity/";
    
    TString FileName[1]={"VertexAcivity_Output"};
    TString VetrexString[5]={"1x1x1" , "3x3x3" , "5x5x5", "7x7x7", "9x9x9"};
    TString VertexName[5]={"VertexActivity1x1x1", "VertexActivity3x3x3", "VertexActivity5x5x5", "VertexActivity7x7x7", "VertexActivity9x9x9"};
    TString ParticleName[SizeOfParticleVector]={"Muon", "Pion+", "Proton"};        
    TString ParticleNameBranch[SizeOfParticleVector]={"Muon", "PionP", "Proton"};
    TString TrackLenght[2]={"Short", "Long"};
    
    TFile *file;
    TTree *t1;
        
    TH1F *hVertexActivity[5];
    TH1F *hVertexActivitySubstractedParticle[SizeOfParticleVector][5];
    TH1F *hVertexActivityParticleCuts[SizeOfParticleVector-1][ParticleNumberGO][5];
    
    TH1F *hVertexActivitySubTrackLengtParticleCondition[2][SizeOfParticleVector][5];
    TH1F *hVertexActivityOnlyIfTrackLenght[2][SizeOfParticleVector][5];
    
    TH1F *hVertexActivitySubTrackLengtAllCondition[2][5];
    TH1F *hVertexActivityOnlyIfTrackLenghtAll[2][5];
  
    TH2F *hMomentumVsRange[SizeOfParticleVector];
    TH2F *hEnergyVsRange[SizeOfParticleVector];
    TH2F *hEenrgyVsRangehEenrgyVsRangeRestricted[SizeOfParticleVector];
    TH2F *hEnergyPeVsRange[SizeOfParticleVector];
    TH2F *hScatteringPathVsMomentum[SizeOfParticleVector];

    file = new TFile(Form("%s%s.root", Directory.Data() , FileName.Data()),"READ");
    if (file->IsOpen() )
    {
        printf("File opened successfully\n");
    }  
    
    TDirectory *FolderSubstracted = (TDirectory*)file->Get("FolderSubstracted"); 
    TDirectory *FolderCut = (TDirectory*)file->Get("FolderCut"); 
    TDirectory *FolderSubstractedTrackLengthCondition = (TDirectory*)file->Get("FolderSubstractedTrackLengthCondition"); 
    TDirectory *FolderSubstractedTrackLengthAll = (TDirectory*)file->Get("FolderSubstractedTrackLengthAll"); 
    file->cd();
    for(int ik=0; ik<5; ik++)
    {
        hVertexActivity[ik] = (TH1F*) file->Get(VertexName[ik]);
        hVertexActivity[ik]->GetYaxis()->SetTitleOffset(1.4);
        
        for(int ig=0; ig<SizeOfParticleVector; ig++)
        {
            hVertexActivitySubstractedParticle[ig][ik] = (TH1F*) FolderSubstracted->Get( Form("VA%sSubstracted_%s", VetrexString[ik].Data(), ParticleName[ig].Data()) );
            hVertexActivitySubstractedParticle[ig][ik]->GetYaxis()->SetTitleOffset(1.4);
        
            for(int il=0; il<2; il++) //loop over short or long track
            {
               hVertexActivitySubTrackLengtParticleCondition[il][ig][ik] = (TH1F*) FolderSubstractedTrackLengthCondition->Get( Form("VA%sSubCondition_%s_%s", VetrexString[ik].Data(), TrackLenght[il].Data(), ParticleName[ig].Data() ) ); 
               hVertexActivitySubTrackLengtParticleCondition[il][ig][ik]->GetYaxis()->SetTitleOffset(1.4);
               
               hVertexActivityOnlyIfTrackLenght[il][ig][ik] = (TH1F*) FolderSubstractedTrackLengthCondition->Get( Form("VA%sIfThereAre_%s_%s", VetrexString[ik].Data(), TrackLenght[il].Data(), ParticleName[ig].Data() ) ); 
               hVertexActivityOnlyIfTrackLenght[il][ig][ik]->GetYaxis()->SetTitleOffset(1.4);
            }
        }
        for(int il=0; il<2; il++) //loop over short or long track
        {
            hVertexActivitySubTrackLengtAllCondition[il][ik] = (TH1F*) FolderSubstractedTrackLengthAll->Get( Form("VA%sSubCondition_%s_All", VetrexString[ik].Data(), TrackLenght[il].Data()) ); 
            hVertexActivitySubTrackLengtAllCondition[il][ik]->GetYaxis()->SetTitleOffset(1.4);
               
            hVertexActivityOnlyIfTrackLenghtAll[il][ik] = (TH1F*) FolderSubstractedTrackLengthAll->Get( Form("VA%sIfThereAre_%s_All", VetrexString[ik].Data(), TrackLenght[il].Data()) ); 
            hVertexActivityOnlyIfTrackLenghtAll[il][ik]->GetYaxis()->SetTitleOffset(1.4);
        }
        for(int ih=0; ih<ParticleNumberGO; ih++)
        {
            for(int ig=0; ig<SizeOfParticleVector-1; ig++)
            {
                hVertexActivityParticleCuts[ig][ih][ik] = (TH1F*) FolderCut->Get( Form("VA%sIfNumOf_%s=%i", VetrexString[ik].Data(), ParticleName[ig+1].Data(), ih) );
                hVertexActivityParticleCuts[ig][ih][ik]->GetYaxis()->SetTitleOffset(1.4);
            }
        }
        
    }
    for(int ig=0; ig<SizeOfParticleVector; ig++)
    {
        hMomentumVsRange[ig] = (TH2F*) file->Get( Form("MomentumVsRange_%s", ParticleName[ig].Data() ) );
        hMomentumVsRange[ig]->GetYaxis()->SetTitleOffset(1.4);
            
        hEnergyVsRange[ig] = (TH2F*) file->Get( Form("EnergyVsRange_%s", ParticleName[ig].Data()) );
        hEnergyVsRange[ig]->GetYaxis()->SetTitleOffset(1.4);
                
        hEnergyPeVsRange[ig] = (TH2F*) file->Get( Form("EnergyPeVsRange_%s", ParticleName[ig].Data()) );
        hEnergyPeVsRange[ig]->GetYaxis()->SetTitleOffset(1.4);
                
        hEenrgyVsRangehEenrgyVsRangeRestricted[ig] = (TH2F*) file->Get( Form("EnergyVsRange_Restricted_%s", ParticleName[ig].Data()) );
        hEenrgyVsRangehEenrgyVsRangeRestricted[ig]->GetYaxis()->SetTitleOffset(1.4);
        
        hScatteringPathVsMomentum[ig] = (TH2F*) file->Get( Form("hScatteringPathVsMomentum_%s", ParticleName[ig].Data()) ); //TODO hScatte..->Scater...
        hScatteringPathVsMomentum[ig]->GetYaxis()->SetTitleOffset(1.4);
    }
    file->GetObject("t1",t1);
    
    TCanvas *Canvas[300];
    TLegend *legend[300];
    int canvasCounter=0;
 ///////////////////////////////// DRAWING PART STARTS HERE/////////////////////////////   
    
    for(int ig=0; ig<SizeOfParticleVector; ig++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        hMomentumVsRange[ig]->Draw("COLZ");
        
        gPad->Modified();
        Canvas[canvasCounter]->Print(Form("%sMomentumVsRange%s.pdf", DirectoryPlots.Data(), ParticleName[ig].Data(), ParticleName[ig].Data() )); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    for(int ig=0; ig<SizeOfParticleVector; ig++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        hEnergyVsRange[ig]->Draw("COLZ");
        
        gPad->Modified();
        Canvas[canvasCounter]->Print(Form("%sEnergyVsRange%s.pdf",DirectoryPlots.Data(), ParticleName[ig].Data() )); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    for(int ig=0; ig<SizeOfParticleVector; ig++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        hEnergyPeVsRange[ig]->Draw("COLZ");
        
        gPad->Modified();
        Canvas[canvasCounter]->Print(Form("%sEnergyPeVsRange_%s.pdf",DirectoryPlots.Data(), ParticleName[ig].Data() )); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    for(int ig=0; ig<SizeOfParticleVector; ig++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        hEenrgyVsRangehEenrgyVsRangeRestricted[ig]->Draw("COLZ");
        
        gPad->Modified();
        Canvas[canvasCounter]->Print(Form("%sEnergyVsRange_Restricted_%s.pdf",DirectoryPlots.Data(), ParticleName[ig].Data() )); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
        for(int ig=0; ig<SizeOfParticleVector; ig++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        hScatteringPathVsMomentum[ig]->Draw("COLZ");
        
        gPad->Modified();
        Canvas[canvasCounter]->Print(Form("%sScatteringPathVsMomentum_%s.pdf",DirectoryPlots.Data(), ParticleName[ig].Data() )); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    for(int ik=0; ik<5; ik++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        
        hVertexActivity[ik]->SetLineColorAlpha(kRed, 1);
        hVertexActivity[ik]->SetLineWidth(1.5);
            
        hVertexActivitySubstractedParticle[0][ik]->SetLineColorAlpha(kBlue, 1);
        hVertexActivitySubstractedParticle[0][ik]->SetLineWidth(1.5);
            
        hVertexActivitySubstractedParticle[1][ik]->SetLineColorAlpha(kGreen, 1);
        hVertexActivitySubstractedParticle[1][ik]->SetLineWidth(1.5);
        
        hVertexActivitySubstractedParticle[2][ik]->SetLineColorAlpha(kMagenta, 1);
        hVertexActivitySubstractedParticle[2][ik]->SetLineWidth(1.5);
        
        hVertexActivitySubstractedParticle[2][ik]->Draw("");
        hVertexActivity[ik]->Draw("SAME");
        hVertexActivitySubstractedParticle[0][ik]->Draw("SAME");
        hVertexActivitySubstractedParticle[1][ik]->Draw("SAME");
           
        legend[canvasCounter] = new TLegend(0.55,0.6,0.9,0.9);
        legend[canvasCounter]->AddEntry(hVertexActivity[ik],"VA_Default","l");
        legend[canvasCounter]->AddEntry(hVertexActivitySubstractedParticle[0][ik], Form( "VA_Subtracted_%s", ParticleName[0].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivitySubstractedParticle[1][ik], Form( "VA_Subtracted_%s", ParticleName[1].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivitySubstractedParticle[2][ik], Form( "VA_Subtracted_%s", ParticleName[2].Data() ),"l");
        legend[canvasCounter]->SetTextSize(0.035);
        legend[canvasCounter]->Draw();
            
        gPad->Modified();
        Canvas[canvasCounter]->Print(Form("%sComparisonAll_%s.pdf",DirectoryPlots.Data(), VertexName[ik].Data() )); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }

    for(int ik=0; ik<5; ik++) //TODO normalizacja by sie przydala
    {
        for(int ig=0; ig<SizeOfParticleVector-1; ig++)
        {
            Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
            
            hVertexActivityParticleCuts[ig][0][ik]->SetLineColorAlpha(kBlue, 1);
            hVertexActivityParticleCuts[ig][0][ik]->SetLineWidth(1.5);
            
            hVertexActivityParticleCuts[ig][1][ik]->SetLineColorAlpha(kGreen, 1);
            hVertexActivityParticleCuts[ig][1][ik]->SetLineWidth(1.5);
        
            hVertexActivityParticleCuts[ig][2][ik]->SetLineColorAlpha(kRed, 1);
            hVertexActivityParticleCuts[ig][2][ik]->SetLineWidth(1.5);
            
            hVertexActivityParticleCuts[ig][0][ik]->Draw("");
            hVertexActivityParticleCuts[ig][1][ik]->Draw("SAME");
            hVertexActivityParticleCuts[ig][2][ik]->Draw("SAME");
        
            legend[canvasCounter] = new TLegend(0.55,0.65,0.9,0.9);
            legend[canvasCounter]->AddEntry(hVertexActivityParticleCuts[ig][0][ik], Form( "VA_NumOf_%s_=0", ParticleName[ig+1].Data() ),"l");
            legend[canvasCounter]->AddEntry(hVertexActivityParticleCuts[ig][1][ik], Form( "VA_NumOf_%s_=1", ParticleName[ig+1].Data() ),"l");
            legend[canvasCounter]->AddEntry(hVertexActivityParticleCuts[ig][2][ik], Form( "VA_NumOf_%s_=2", ParticleName[ig+1].Data() ),"l");
            legend[canvasCounter]->SetTextSize(0.04);
            legend[canvasCounter]->Draw();
        
            gPad->Modified();
            Canvas[canvasCounter]->Print( Form("%sVA%sIfNumOf_%s=N.pdf", DirectoryPlots.Data(), VetrexString[ik].Data(), ParticleName[ig+1].Data()) ); 
            delete Canvas[canvasCounter];
            canvasCounter++;
        }
    }
    for(int ik=0; ik<5; ik++)
    {
        for(int ig=0; ig<SizeOfParticleVector; ig++)
        {
            for(int il=0; il<2; il++)
            {  
                Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
                
                hVertexActivitySubTrackLengtParticleCondition[il][ig][ik]->SetLineColorAlpha(kBlue, 1);
                hVertexActivitySubTrackLengtParticleCondition[il][ig][ik]->SetLineWidth(1.5);
                
                hVertexActivityOnlyIfTrackLenght[il][ig][ik]->SetLineColorAlpha(kRed, 1);
                hVertexActivityOnlyIfTrackLenght[il][ig][ik]->SetLineWidth(1.5);
                
                hVertexActivitySubTrackLengtParticleCondition[il][ig][ik]->Draw("");
                hVertexActivityOnlyIfTrackLenght[il][ig][ik]->Draw("SAME");
                
                legend[canvasCounter] = new TLegend(0.55,0.7,0.9,0.9);
                legend[canvasCounter]->AddEntry(hVertexActivitySubTrackLengtParticleCondition[il][ig][ik], Form( "VA_Sub_%s_%s",TrackLenght[il].Data(), ParticleName[ig].Data() ),"l");
                legend[canvasCounter]->AddEntry(hVertexActivityOnlyIfTrackLenght[il][ig][ik], Form( "VA_Default_If_%s_%s", TrackLenght[il].Data(), ParticleName[ig].Data() ),"l");
                legend[canvasCounter]->SetTextSize(0.03);
                legend[canvasCounter]->Draw();
            
                gPad->Modified();
                Canvas[canvasCounter]->Print( Form("%sSubtracted_VA%s_%s_%s.pdf", DirectoryPlots.Data(), VetrexString[ik].Data(), TrackLenght[il].Data(), ParticleName[ig].Data()) ); 
                delete Canvas[canvasCounter];
                canvasCounter++;
            }
        }
    }
    for(int ik=0; ik<5; ik++)
    {
        for(int il=0; il<2; il++)
        {  
            Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
                
            hVertexActivityOnlyIfTrackLenghtAll[il][ik]->SetLineColorAlpha(kBlue, 1);
            hVertexActivityOnlyIfTrackLenghtAll[il][ik]->SetLineWidth(1.5);
                
            hVertexActivitySubTrackLengtAllCondition[il][ik]->SetLineColorAlpha(kRed, 1);
            hVertexActivitySubTrackLengtAllCondition[il][ik]->SetLineWidth(1.5);
                
            hVertexActivitySubTrackLengtAllCondition[il][ik]->Draw("");
            hVertexActivityOnlyIfTrackLenghtAll[il][ik]->Draw("SAME");
                
            legend[canvasCounter] = new TLegend(0.55,0.7,0.9,0.9);
            legend[canvasCounter]->AddEntry(hVertexActivitySubTrackLengtAllCondition[il][ik], Form( "VA_Subtracted_%s", TrackLenght[il].Data() ),"l");
            legend[canvasCounter]->AddEntry(hVertexActivityOnlyIfTrackLenghtAll[il][ik], Form( "VA_Default" ),"l");
            legend[canvasCounter]->SetTextSize(0.04);
            legend[canvasCounter]->Draw();
            
            gPad->Modified();
            Canvas[canvasCounter]->Print( Form("%sAll_Subtracted_VA%s_%s.pdf", DirectoryPlots.Data(), VetrexString[ik].Data(), TrackLenght[il].Data()) ); 
            delete Canvas[canvasCounter];
            canvasCounter++;
        }
    } 
}
