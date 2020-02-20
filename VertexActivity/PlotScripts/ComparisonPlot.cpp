#include <TH1.h>
#include <TH2F.h>
#include <fstream>
#include <iostream>
#include "TStyle.h"
#include <TColor.h>

void ComparisonPlot()
{
    //TODO rozwinac to i zbadać
    Int_t WhichStyle = 1; 
    // -- WhichStyle --
    // 1 = presentation large fonts
    // 2 = presentation small fonts
    // 3 = publication/paper
    
    Int_t FontStyle = 22;
    Float_t FontSizeLabel = 0.035;
    Float_t FontSizeTitle = 0.05;
    Float_t YOffsetTitle = 1.3;

    switch(WhichStyle) 
    {
        case 1:
        FontStyle = 42;
        FontSizeLabel = 0.05;
        FontSizeTitle = 0.065;
        YOffsetTitle = 1.19;
        break;
        case 2:
        FontStyle = 42;
        FontSizeLabel = 0.035;
        FontSizeTitle = 0.05;
        YOffsetTitle = 1.6;
    break;
    case 3:
        FontStyle = 132;
        FontSizeLabel = 0.035;
        FontSizeTitle = 0.05;
        YOffsetTitle = 1.6;
        break;
    }
  
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(111);
    gStyle->SetPalette(1,0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetOptStat(0);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
  
    // Fonts, sizes, offsets
    gStyle->SetTextFont(FontStyle);
    gStyle->SetTextSize(0.08);

    gStyle->SetLabelFont(FontStyle, "x");
    gStyle->SetLabelFont(FontStyle, "y");
    gStyle->SetLabelFont(FontStyle, "z");
    gStyle->SetLabelFont(FontStyle, "t");
    gStyle->SetLabelSize(FontSizeLabel, "x");
    gStyle->SetLabelSize(FontSizeLabel, "y");
    gStyle->SetLabelSize(FontSizeLabel, "z");
    gStyle->SetLabelOffset(0.015, "x");
    gStyle->SetLabelOffset(0.015, "y");
    gStyle->SetLabelOffset(0.015, "z");

    gStyle->SetTitleFont(FontStyle, "x");
    gStyle->SetTitleFont(FontStyle, "y");
    gStyle->SetTitleFont(FontStyle, "z");
    gStyle->SetTitleFont(FontStyle, "t");
    gStyle->SetTitleSize(FontSizeTitle, "y");
    gStyle->SetTitleSize(FontSizeTitle, "x");
    gStyle->SetTitleSize(FontSizeTitle, "z");
    gStyle->SetTitleOffset(1.14, "x");
    gStyle->SetTitleOffset(YOffsetTitle, "y");
    gStyle->SetTitleOffset(1.2, "z");

    gStyle->SetTitleStyle(0);
    gStyle->SetTitleFontSize(0.06);//0.08
    gStyle->SetTitleFont(FontStyle, "pad");
    gStyle->SetTitleBorderSize(0);
    gStyle->SetTitleX(0.1f);
    gStyle->SetTitleW(0.8f);
  
    const int SizeOfParticleVector = 3;
    const int ParticleNumberGO = 3; //Number of particles we put condition on, starting from 0
    int LongOrShort = 1; //Set if you are interested in subtracting long and short [0] or just long [1]
    
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
    TH1F *hVertexActivityShell[4]; //[vertexBox-1]
    TH1F *hVertexActivitySubtractedParticle[SizeOfParticleVector][5];
    TH1F *hVertexActivityParticleCuts[SizeOfParticleVector-1][ParticleNumberGO][5];
    
    TH1F *hVertexActivitySubTrackLengtParticleCondition[2][SizeOfParticleVector][5];
    TH1F *hVertexActivityOnlyIfTrackLenght[2][SizeOfParticleVector][5];
    
    TH1F *hVertexActivitySubTrackLengtAllCondition[2][5];
    TH1F *hVertexActivityOnlyIfTrackLenghtAll[2][5];
  
    TH1F *hVertexActivitySubTrackLengtAllConditionShell[2][4]; 
    TH1F *hVertexActivityOnlyIfTrackLenghtAllShell[2][4]; //[0-short, long][vertexBox]
    TH1F *hVertexActivityOnlyLongShell[4]; //[vertexBox-1]
    
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
    
    TDirectory *FolderSubtracted = (TDirectory*)file->Get("FolderSubtracted"); 
    TDirectory *FolderCut = (TDirectory*)file->Get("FolderCut"); 
    TDirectory *FolderSubtractedTrackLengthCondition = (TDirectory*)file->Get("FolderSubtractedTrackLengthCondition"); 
    TDirectory *FolderSubtractedTrackLengthAll = (TDirectory*)file->Get("FolderSubtractedTrackLengthAll"); 
    TDirectory *FolderSubtractedTrackLengthAllShell = (TDirectory*)file->Get("FolderSubtractedTrackLengthAllShell");
    file->cd();
    for(int ik=0; ik<5; ik++)
    {
        hVertexActivity[ik] = (TH1F*) file->Get(VertexName[ik]);
        hVertexActivity[ik]->GetYaxis()->SetTitleOffset(1.4);
        if(ik>0)
        {
            hVertexActivityShell[ik-1] = (TH1F*) file->Get( Form("%sShell",VertexName[ik].Data() ) );
            hVertexActivityShell[ik-1]->GetYaxis()->SetTitleOffset(1.4);
            
            hVertexActivityOnlyLongShell[ik-1] = (TH1F*) FolderSubtractedTrackLengthAllShell->Get( Form("%sShell_OnlyLong",VertexName[ik].Data()) );
            hVertexActivityOnlyLongShell[ik-1]->GetYaxis()->SetTitleOffset(1.4);
        }
        
        for(int ig=0; ig<SizeOfParticleVector; ig++)
        {
            hVertexActivitySubtractedParticle[ig][ik] = (TH1F*) FolderSubtracted->Get( Form("VA%sSubtracted_%s", VetrexString[ik].Data(), ParticleName[ig].Data()) );
            hVertexActivitySubtractedParticle[ig][ik]->GetYaxis()->SetTitleOffset(1.4);
        
            for(int il=LongOrShort; il<2; il++) //loop over short or long track
            {
               hVertexActivitySubTrackLengtParticleCondition[il][ig][ik] = (TH1F*) FolderSubtractedTrackLengthCondition->Get( Form("VA%sSubCondition_%s_%s", VetrexString[ik].Data(), TrackLenght[il].Data(), ParticleName[ig].Data() ) ); 
               hVertexActivitySubTrackLengtParticleCondition[il][ig][ik]->GetYaxis()->SetTitleOffset(1.4);
               
               hVertexActivityOnlyIfTrackLenght[il][ig][ik] = (TH1F*) FolderSubtractedTrackLengthCondition->Get( Form("VA%sIfThereAre_%s_%s", VetrexString[ik].Data(), TrackLenght[il].Data(), ParticleName[ig].Data() ) ); 
               hVertexActivityOnlyIfTrackLenght[il][ig][ik]->GetYaxis()->SetTitleOffset(1.4);
            }
        }
        for(int il=LongOrShort; il<2; il++) //loop over short or long track
        {
            hVertexActivitySubTrackLengtAllCondition[il][ik] = (TH1F*) FolderSubtractedTrackLengthAll->Get( Form("VA%sSubCondition_%s_All", VetrexString[ik].Data(), TrackLenght[il].Data()) ); 
            hVertexActivitySubTrackLengtAllCondition[il][ik]->GetYaxis()->SetTitleOffset(1.4);
               
            hVertexActivityOnlyIfTrackLenghtAll[il][ik] = (TH1F*) FolderSubtractedTrackLengthAll->Get( Form("VA%sIfThereAre_%s_All", VetrexString[ik].Data(), TrackLenght[il].Data()) ); 
            hVertexActivityOnlyIfTrackLenghtAll[il][ik]->GetYaxis()->SetTitleOffset(1.4);
            
            if(ik>0)
            {
                hVertexActivitySubTrackLengtAllConditionShell[il][ik-1] = (TH1F*) FolderSubtractedTrackLengthAllShell->Get( Form("VA%sSubCondition_%s_All_Shell", VetrexString[ik].Data(), TrackLenght[il].Data()) ); 
                hVertexActivitySubTrackLengtAllConditionShell[il][ik-1]->GetYaxis()->SetTitleOffset(1.4);
               
                hVertexActivityOnlyIfTrackLenghtAllShell[il][ik-1] = (TH1F*) FolderSubtractedTrackLengthAllShell->Get( Form("VA%sIfThereAre_%s_All_Shell", VetrexString[ik].Data(), TrackLenght[il].Data()) ); 
                hVertexActivityOnlyIfTrackLenghtAllShell[il][ik-1]->GetYaxis()->SetTitleOffset(1.4);
            }
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
        
        hScatteringPathVsMomentum[ig] = (TH2F*) file->Get( Form("ScatteringPathVsMomentum_%s", ParticleName[ig].Data()) );
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
            
        hVertexActivitySubtractedParticle[0][ik]->SetLineColorAlpha(kBlue, 1);
        hVertexActivitySubtractedParticle[0][ik]->SetLineWidth(1.5);
            
        hVertexActivitySubtractedParticle[1][ik]->SetLineColorAlpha(kGreen, 1);
        hVertexActivitySubtractedParticle[1][ik]->SetLineWidth(1.5);
        
        hVertexActivitySubtractedParticle[2][ik]->SetLineColorAlpha(kMagenta, 1);
        hVertexActivitySubtractedParticle[2][ik]->SetLineWidth(1.5);
        
        hVertexActivitySubtractedParticle[2][ik]->Draw("");
        hVertexActivity[ik]->Draw("SAME");
        hVertexActivitySubtractedParticle[0][ik]->Draw("SAME");
        hVertexActivitySubtractedParticle[1][ik]->Draw("SAME");
           
        legend[canvasCounter] = new TLegend(0.55,0.6,0.9,0.9);
        legend[canvasCounter]->AddEntry(hVertexActivity[ik],"VA_Default","l");
        legend[canvasCounter]->AddEntry(hVertexActivitySubtractedParticle[0][ik], Form( "VA_Subtracted_%s", ParticleName[0].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivitySubtractedParticle[1][ik], Form( "VA_Subtracted_%s", ParticleName[1].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivitySubtractedParticle[2][ik], Form( "VA_Subtracted_%s", ParticleName[2].Data() ),"l");
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
            for(int il=LongOrShort; il<2; il++)
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
        for(int il=LongOrShort; il<2; il++)
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
    Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
            
    hVertexActivityShell[0]->SetLineColorAlpha(kBlue, 1);
    hVertexActivityShell[0]->SetLineWidth(1.5);
                
    hVertexActivityShell[1]->SetLineColorAlpha(kRed, 1);
    hVertexActivityShell[1]->SetLineWidth(1.5);
    
    hVertexActivityShell[2]->SetLineColorAlpha(kGreen, 1);
    hVertexActivityShell[2]->SetLineWidth(1.5);
    
    hVertexActivityShell[3]->SetLineColorAlpha(kMagenta, 1);
    hVertexActivityShell[3]->SetLineWidth(1.5);
                
    hVertexActivityShell[0]->Draw("");
    hVertexActivityShell[1]->Draw("SAME");
    hVertexActivityShell[2]->Draw("SAME");
    hVertexActivityShell[3]->Draw("SAME");
      
    legend[canvasCounter] = new TLegend(0.60,0.7,0.9,0.9);
    legend[canvasCounter]->AddEntry(hVertexActivityShell[0], Form("VA%s_Shell", VetrexString[1].Data() ),"l");
    legend[canvasCounter]->AddEntry(hVertexActivityShell[1], Form("VA%s_Shell", VetrexString[2].Data() ),"l");
    legend[canvasCounter]->AddEntry(hVertexActivityShell[2], Form("VA%s_Shell", VetrexString[3].Data() ),"l");
    legend[canvasCounter]->AddEntry(hVertexActivityShell[3], Form("VA%s_Shell", VetrexString[4].Data() ),"l");
    legend[canvasCounter]->SetTextSize(0.04);
    legend[canvasCounter]->Draw();
            
    gPad->Modified();
    Canvas[canvasCounter]->Print( Form("%sShellComparisonNormal.pdf", DirectoryPlots.Data() ) ); 
    delete Canvas[canvasCounter];
    canvasCounter++;

    for(int il=LongOrShort; il<2; il++)
    {  
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
                
        hVertexActivitySubTrackLengtAllConditionShell[il][0]->SetLineColorAlpha(kBlue, 1);
        hVertexActivitySubTrackLengtAllConditionShell[il][0]->SetLineWidth(1.5);
                
        hVertexActivitySubTrackLengtAllConditionShell[il][1]->SetLineColorAlpha(kRed, 1);
        hVertexActivitySubTrackLengtAllConditionShell[il][1]->SetLineWidth(1.5);
          
        hVertexActivitySubTrackLengtAllConditionShell[il][2]->SetLineColorAlpha(kGreen, 1);
        hVertexActivitySubTrackLengtAllConditionShell[il][2]->SetLineWidth(1.5);
        
        hVertexActivitySubTrackLengtAllConditionShell[il][3]->SetLineColorAlpha(kMagenta, 1);
        hVertexActivitySubTrackLengtAllConditionShell[il][3]->SetLineWidth(1.5);
        
        hVertexActivitySubTrackLengtAllConditionShell[il][0]->Draw("");
        hVertexActivitySubTrackLengtAllConditionShell[il][1]->Draw("SAME");
        hVertexActivitySubTrackLengtAllConditionShell[il][2]->Draw("SAME");
        hVertexActivitySubTrackLengtAllConditionShell[il][3]->Draw("SAME");
          
        legend[canvasCounter] = new TLegend(0.60,0.7,0.9,0.9);
        legend[canvasCounter]->AddEntry(hVertexActivitySubTrackLengtAllConditionShell[il][0], Form("VA%s_Shell", VetrexString[1].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivitySubTrackLengtAllConditionShell[il][1], Form("VA%s_Shell", VetrexString[2].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivitySubTrackLengtAllConditionShell[il][2], Form("VA%s_Shell", VetrexString[3].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivitySubTrackLengtAllConditionShell[il][3], Form("VA%s_Shell", VetrexString[4].Data() ),"l");
        legend[canvasCounter]->SetTextSize(0.04);
        legend[canvasCounter]->Draw();
            
        gPad->Modified();
        Canvas[canvasCounter]->Print( Form("%sAll_Subtracted_%s_Shell.pdf", DirectoryPlots.Data(), TrackLenght[il].Data()) ); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    for(int il=LongOrShort; il<2; il++)
    {  
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
                
        hVertexActivityOnlyIfTrackLenghtAllShell[il][0]->SetLineColorAlpha(kBlue, 1);
        hVertexActivityOnlyIfTrackLenghtAllShell[il][0]->SetLineWidth(1.5);
                
        hVertexActivityOnlyIfTrackLenghtAllShell[il][1]->SetLineColorAlpha(kRed, 1);
        hVertexActivityOnlyIfTrackLenghtAllShell[il][1]->SetLineWidth(1.5);
          
        hVertexActivityOnlyIfTrackLenghtAllShell[il][2]->SetLineColorAlpha(kGreen, 1);
        hVertexActivityOnlyIfTrackLenghtAllShell[il][2]->SetLineWidth(1.5);
        
        hVertexActivityOnlyIfTrackLenghtAllShell[il][3]->SetLineColorAlpha(kMagenta, 1);
        hVertexActivityOnlyIfTrackLenghtAllShell[il][3]->SetLineWidth(1.5);
        
        hVertexActivityOnlyIfTrackLenghtAllShell[il][0]->Draw("");
        hVertexActivityOnlyIfTrackLenghtAllShell[il][1]->Draw("SAME");
        hVertexActivityOnlyIfTrackLenghtAllShell[il][2]->Draw("SAME");
        hVertexActivityOnlyIfTrackLenghtAllShell[il][3]->Draw("SAME");
          
        legend[canvasCounter] = new TLegend(0.60,0.7,0.9,0.9);
        legend[canvasCounter]->AddEntry(hVertexActivityOnlyIfTrackLenghtAllShell[il][0], Form("VA%s_Shell", VetrexString[1].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivityOnlyIfTrackLenghtAllShell[il][1], Form("VA%s_Shell", VetrexString[2].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivityOnlyIfTrackLenghtAllShell[il][2], Form("VA%s_Shell", VetrexString[3].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivityOnlyIfTrackLenghtAllShell[il][3], Form("VA%s_Shell", VetrexString[4].Data() ),"l");
        legend[canvasCounter]->SetTextSize(0.04);
        legend[canvasCounter]->Draw();
            
        gPad->Modified();
        Canvas[canvasCounter]->Print( Form("%sAll_Not_Subtracted_%s_Shell.pdf", DirectoryPlots.Data(), TrackLenght[il].Data()) ); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    
    Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
    hVertexActivityOnlyLongShell[0]->SetLineColorAlpha(kBlue, 1);
    hVertexActivityOnlyLongShell[0]->SetLineWidth(1.5);
                
    hVertexActivityOnlyLongShell[1]->SetLineColorAlpha(kRed, 1);
    hVertexActivityOnlyLongShell[1]->SetLineWidth(1.5);
    
    hVertexActivityOnlyLongShell[2]->SetLineColorAlpha(kGreen, 1);
    hVertexActivityOnlyLongShell[2]->SetLineWidth(1.5);
    
    hVertexActivityOnlyLongShell[3]->SetLineColorAlpha(kMagenta, 1);
    hVertexActivityOnlyLongShell[3]->SetLineWidth(1.5);
                
    hVertexActivityOnlyLongShell[0]->Draw("");
    hVertexActivityOnlyLongShell[1]->Draw("SAME");
    hVertexActivityOnlyLongShell[2]->Draw("SAME");
    hVertexActivityOnlyLongShell[3]->Draw("SAME");
    
    legend[canvasCounter] = new TLegend(0.60,0.7,0.9,0.9);
    legend[canvasCounter]->AddEntry(hVertexActivityOnlyLongShell[0], Form("VA%s_Shell", VetrexString[1].Data() ),"l");
    legend[canvasCounter]->AddEntry(hVertexActivityOnlyLongShell[1], Form("VA%s_Shell", VetrexString[2].Data() ),"l");
    legend[canvasCounter]->AddEntry(hVertexActivityOnlyLongShell[2], Form("VA%s_Shell", VetrexString[3].Data() ),"l");
    legend[canvasCounter]->AddEntry(hVertexActivityOnlyLongShell[3], Form("VA%s_Shell", VetrexString[4].Data() ),"l");
    legend[canvasCounter]->SetTextSize(0.04);
    legend[canvasCounter]->Draw();
    
    gPad->Modified();
    cout<<Form("%sShellComparisonOnlyLong.pdf", DirectoryPlots.Data() )<<endl;
    Canvas[canvasCounter]->Print( Form("%sShellComparisonOnlyLong.pdf", DirectoryPlots.Data() ) ); 
    delete Canvas[canvasCounter];
    canvasCounter++;
}
