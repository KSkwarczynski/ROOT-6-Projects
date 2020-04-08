#include <TH1.h>
#include <TH2F.h>
#include <fstream>
#include <iostream>
#include "TStyle.h"
#include <TColor.h>
#include <TLatex.h>

void ComparisonPlot()
{
    // -- WhichStyle --
    // 1 = presentation large fonts
    // 2 = presentation small fonts
    // 3 = publication/paper
    Int_t WhichStyle = 2;
    
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
    // use plain black on white colors
    gStyle->SetFrameBorderMode(0);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadBorderMode(0);
    gStyle->SetCanvasBorderSize(0);
    gStyle->SetFrameBorderSize(0);
    gStyle->SetDrawBorder(0);
    gStyle->SetTitleBorderSize(0);

    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetStatColor(0);
    gStyle->SetFillColor(0);

    gStyle->SetEndErrorSize(4);
    gStyle->SetStripDecimals(kFALSE);

    //gStyle->SetLegendBorderSize(0); //This option dsables legends borders
    gStyle->SetLegendFont(FontStyle);

    // set the paper & margin sizes
    gStyle->SetPaperSize(20, 26);
    gStyle->SetPadTopMargin(0.1);
    gStyle->SetPadBottomMargin(0.15);
    gStyle->SetPadRightMargin(0.13); // 0.075 -> 0.13 for colz option
    gStyle->SetPadLeftMargin(0.16);//to include both large/small font options

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

    // use bold lines and markers
    gStyle->SetMarkerStyle(20);
    gStyle->SetHistLineWidth( Width_t(2.5) );
    gStyle->SetLineStyleString(2, "[12 12]"); // postscript dashes

    // get rid of X error bars and y error bar caps
    gStyle->SetErrorX(0.001);

    // do not display any of the standard histogram decorations
    //gStyle->SetOptTitle(0); //Set 0 to disable histogram tittle
    gStyle->SetOptStat(0); //Set 0 to disable statystic box
    gStyle->SetOptFit(0);

    // put tick marks on top and RHS of plots
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);

    // -- color --
    // functions blue
    //gStyle->SetFuncColor(600-4);
    gStyle->SetFuncColor(2);
    gStyle->SetFuncWidth(2);

    gStyle->SetFillColor(1); // make color fillings (not white)
    // - color setup for 2D -
    // - "cold"/ blue-ish -
    Double_t red[]   = { 0.00, 0.00, 0.00 };
    Double_t green[] = { 1.00, 0.00, 0.00 };
    Double_t blue[]  = { 1.00, 1.00, 0.25 };
    // - "warm" red-ish colors -
    //  Double_t red[]   = {1.00, 1.00, 0.25 };
    //  Double_t green[] = {1.00, 0.00, 0.00 };
    //  Double_t blue[]  = {0.00, 0.00, 0.00 };

    Double_t stops[] = { 0.25, 0.75, 1.00 };
    const Int_t NRGBs = 3;
    const Int_t NCont = 500;

    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);

    // - Rainbow -
    gStyle->SetPalette(1);  // use the rainbow color set

    // -- axis --
    gStyle->SetStripDecimals(kFALSE); // don't do 1.0 -> 1
    //  TGaxis::SetMaxDigits(3); // doesn't have an effect
    // no supressed zeroes!
    gStyle->SetHistMinimumZero(kTRUE);    
/////////////////////////////////////////////////////////////////////  
/////////////////////////////////////////////////////////////////////     
/////////////////////////////////////////////////////////////////////  
    const int SizeOfParticleVector = 4;
    const int ParticleNumberGO = 2; //Number of particles we put condition on, starting from 0
    int LongOrShort = 1; //Set if you are interested in subtracting long and short [0] or just long [1]
    const int SelectionNumber = 5;
    const int ReacTypeNum = 5;
    bool CIS = false;
    bool NEUT = true;
    
    TString Directory="/Users/kolos/Desktop/sFGD/Output/";
    TString DirectoryPlots="/Users/kolos/Desktop/sFGD/Plots/GENIE/";
    TString DirectorySelePlots="/Users/kolos/Desktop/sFGD/Plots/GENIE/Selections/";
    TString DirectoryReacPlots="/Users/kolos/Desktop/sFGD/PlotsGENIE/GENIE/Reactions/";
    TString DirectorySplitSelectionsPlots="/Users/kolos/Desktop/sFGD/Plots/GENIE/SplitSelections/";
    
    TString FileName="VertexAcivity_Output";
    TString VetrexString[5]={"1x1x1" , "3x3x3" , "5x5x5", "7x7x7", "9x9x9"};
    TString VertexName[5]={"VertexActivity1x1x1", "VertexActivity3x3x3", "VertexActivity5x5x5", "VertexActivity7x7x7", "VertexActivity9x9x9"};
    TString ParticleName[SizeOfParticleVector]={"Muon", "Pion+", "Proton", "Pion-"};        
    TString ParticleNameBranch[SizeOfParticleVector]={"Muon", "PionP", "Proton", "PionN"};
    TString TrackLenght[2]={"Short", "Long"};
    TString OppositeLenght[2]={"Long", "Short"};
    TString SelectionsName[SelectionNumber]={"1mu1p", "1mu", "1muNp", "CC1Pi", "CCOther"};
    TString ReactionName[ReacTypeNum]={"CCQE", "2p2h", "RES", "DIS", "COH"};
    
    if(CIS)
    {
        Directory="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/Output/";
        DirectoryPlots="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/PlotOutput/VertexActivity/GENIE/";
        DirectorySelePlots="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/PlotOutput/VertexActivity/GENIE/Selections/";
        DirectoryReacPlots="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/PlotOutput/VertexActivity/GENIE/Reactions/";
        DirectorySplitSelectionsPlots="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/PlotOutput/VertexActivity/GENIE/SplitSelections/";
    }
    if(NEUT)
    {
        FileName="NeutVertexAcivity_Output";
        
        DirectoryPlots="/Users/kolos/Desktop/sFGD/Plots/NEUT/";
        DirectorySelePlots="/Users/kolos/Desktop/sFGD/Plots/NEUT/Selections/";
        DirectoryReacPlots="/Users/kolos/Desktop/sFGD/PlotsGENIE/NEUT/Reactions/";
        DirectorySplitSelectionsPlots="/Users/kolos/Desktop/sFGD/Plots/NEUT/SplitSelections/";
        
        if(CIS)
        {
            DirectoryPlots="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/PlotOutput/VertexActivity/NEUT/";
            DirectorySelePlots="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/PlotOutput/VertexActivity/NEUT/Selections/";
            DirectoryReacPlots="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/PlotOutput/VertexActivity/NEUT/Reactions/";
            DirectorySplitSelectionsPlots="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/PlotOutput/VertexActivity/NEUT/SplitSelections/";
        }
    }
    
    TFile *file;
    TTree *t1;

    TH1F *hVertexActivity[5];
    TH1F *hVertexActivityShell[4]; //[vertexBox-1]
    TH1F *hVertexActivitySubtractedParticle[SizeOfParticleVector][5];
    TH1F *hVertexActivityParticleCuts[SizeOfParticleVector-1][ParticleNumberGO][5];
    
    TH1F *hVASubTrackLengtParticleCondition[2][SizeOfParticleVector][5];
    TH1F *hVAOnlyIfTrackLenght[2][SizeOfParticleVector][5];
    
    TH1F *hVertexActivitySubTrackLengtAllCondition[2][5];
    TH1F *hVertexActivityOnlyIfTrackLenghtAll[2][5];
  
    TH1F *hVertexActivitySubTrackLengtAllConditionShell[2][4]; 
    TH1F *hVertexActivityOnlyIfTrackLenghtAllShell[2][4]; //[0-short, long][vertexBox]
    TH1F *hVertexActivityOnlyLongShell[4]; //[vertexBox-1]

    TH1F *hVertexActivitySelections[SelectionNumber][5]; //[SelectionNumber][vertexBox]
    TH1F *hVASubTrackLengtAllCondSelection[SelectionNumber][2][5];
    
    TH1F *hVertexActivityReaction[ReacTypeNum][5]; //[ReacTypeNum][vertexBox]
    TH1F *hVASubTrackLengtAllCondReaction[ReacTypeNum][2][5];
    
    //TODO SplitReactions
    TH1F *hVASplitSelection[SelectionNumber][ReacTypeNum][5];
    TH1F *h_nuMomSplitSelections[SelectionNumber][ReacTypeNum];
    
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
    TDirectory *FolderHist2D = (TDirectory*)file->Get("FolderHist2D");
    
    TDirectory *FolderParticleSelections[SelectionNumber];
    for(int ic=0; ic<SelectionNumber; ic++) 
    {
       FolderParticleSelections[ic]= (TDirectory*)file->Get( Form( "Folder%s", SelectionsName[ic].Data() ) );
    }
    TDirectory *FolderReaction[ReacTypeNum];
    for(int ir=0; ir<ReacTypeNum; ir++) 
    {
       FolderReaction[ir]= (TDirectory*)file->Get( Form( "Folder%s", ReactionName[ir].Data() ) );
    }
    TDirectory *FolderSplitedSelection[SelectionNumber];
    for(int ic=0; ic<SelectionNumber; ic++) 
    {
       FolderSplitedSelection[ic]= (TDirectory*)file->Get( Form( "FolderSplited%s", SelectionsName[ic].Data() ) );
    }
    file->cd();
    
    for(int ik=0; ik<5; ik++)
    {
        hVertexActivity[ik] = (TH1F*) file->Get(VertexName[ik]);
        hVertexActivity[ik]->GetYaxis()->SetTitleOffset(1.4);
        if(ik>0)
        {
            hVertexActivityShell[ik-1] = (TH1F*) file->Get( Form("%sShell",VertexName[ik].Data() ) );
            hVertexActivityShell[ik-1]->GetYaxis()->SetTitleOffset(1.4);
            
            hVertexActivityOnlyLongShell[ik-1] = (TH1F*) FolderSubtractedTrackLengthAllShell->Get( Form("%s_OnlyLong_Shell",VertexName[ik].Data() ) );
            hVertexActivityOnlyLongShell[ik-1]->GetYaxis()->SetTitleOffset(1.4);
        }
        for(int ic=0; ic<SelectionNumber; ic++)
        {
            for(int ir=0; ir<ReacTypeNum; ir++) 
            {
                hVASplitSelection[ic][ir][ik] = (TH1F*) FolderSplitedSelection[ic]->Get( Form("VA%s_%s_%s", VetrexString[ik].Data(), SelectionsName[ic].Data(), ReactionName[ir].Data() ) );
                
                if(ik==0)
                {
                    h_nuMomSplitSelections[ic][ir] = (TH1F*) FolderSplitedSelection[ic]->Get( Form("nuMom%s_%s", SelectionsName[ic].Data(), ReactionName[ir].Data() ) );
                }
            }
        }
        for(int ic=0; ic<SelectionNumber; ic++)
        {
            hVertexActivitySelections[ic][ik] = (TH1F*) FolderParticleSelections[ic]->Get(Form("VA%s_%s", VetrexString[ik].Data(), SelectionsName[ic].Data()));
            hVertexActivitySelections[ic][ik]->GetYaxis()->SetTitleOffset(1.4);
            
            for(int il=0; il<2; il++) //loop over short long track
            {
                hVASubTrackLengtAllCondSelection[ic][il][ik] = (TH1F*) FolderParticleSelections[ic]->Get( Form("VA%sSubCondition_%s_%s_All", VetrexString[ik].Data(), SelectionsName[ic].Data(), TrackLenght[il].Data()) );
                //hVASubTrackLengtAllCondSelection[ic][il][ik]->GetYaxis()->SetTitleOffset(1.4); //TODO dlaczego nie dizala
            }
            
        }
        for(int ir=0; ir<ReacTypeNum; ir++)
        {
            hVertexActivityReaction[ir][ik] = (TH1F*) FolderReaction[ir]->Get( Form("VA%s_%s", VetrexString[ik].Data(), ReactionName[ir].Data()) );
            hVertexActivityReaction[ir][ik]->GetYaxis()->SetTitleOffset(1.4);
            
            for(int il=0; il<2; il++) //loop over short long track
            {
                hVASubTrackLengtAllCondReaction[ir][il][ik] = (TH1F*) FolderReaction[ir]->Get( Form("VA%sSubCondition_%s_%s_All", VetrexString[ik].Data(),ReactionName[ir].Data(), TrackLenght[il].Data()) );
                //hVASubTrackLengtAllCondReaction[ir][il][ik]->GetYaxis()->SetTitleOffset(1.4); //TODO dlaczego nie dziala
            }
        }
        for(int ig=0; ig<SizeOfParticleVector; ig++)
        {
            hVertexActivitySubtractedParticle[ig][ik] = (TH1F*) FolderSubtracted->Get( Form("VA%sSubtracted_%s", VetrexString[ik].Data(), ParticleName[ig].Data()) );
            hVertexActivitySubtractedParticle[ig][ik]->GetYaxis()->SetTitleOffset(1.4);
        
            for(int il=LongOrShort; il<2; il++) //loop over short or long track
            {
               hVASubTrackLengtParticleCondition[il][ig][ik] = (TH1F*) FolderSubtractedTrackLengthCondition->Get( Form("VA%sSubCondition_%s_%s", VetrexString[ik].Data(), TrackLenght[il].Data(), ParticleName[ig].Data() ) ); 
               hVASubTrackLengtParticleCondition[il][ig][ik]->GetYaxis()->SetTitleOffset(1.4);
               
               hVAOnlyIfTrackLenght[il][ig][ik] = (TH1F*) FolderSubtractedTrackLengthCondition->Get( Form("VA%s_IfThereAre_%s_%s", VetrexString[ik].Data(), OppositeLenght[il].Data(), ParticleName[ig].Data() ) ); 
               hVAOnlyIfTrackLenght[il][ig][ik]->GetYaxis()->SetTitleOffset(1.4);
            }
        }
        for(int il=LongOrShort; il<2; il++) //loop over short or long track
        {
            hVertexActivitySubTrackLengtAllCondition[il][ik] = (TH1F*) FolderSubtractedTrackLengthAll->Get( Form("VA%sSubCondition_%s_All", VetrexString[ik].Data(), TrackLenght[il].Data()) ); 
            hVertexActivitySubTrackLengtAllCondition[il][ik]->GetYaxis()->SetTitleOffset(1.4);
               
            hVertexActivityOnlyIfTrackLenghtAll[il][ik] = (TH1F*) FolderSubtractedTrackLengthAll->Get( Form("VA%s_IfThereAre_%s_All", VetrexString[ik].Data(), OppositeLenght[il].Data()) ); 
            hVertexActivityOnlyIfTrackLenghtAll[il][ik]->GetYaxis()->SetTitleOffset(1.4);
            
            if(ik>0)
            {
                hVertexActivitySubTrackLengtAllConditionShell[il][ik-1] = (TH1F*) FolderSubtractedTrackLengthAllShell->Get( Form("VA%sSubCondition_%s_All_Shell", VetrexString[ik].Data(), TrackLenght[il].Data()) ); 
                hVertexActivitySubTrackLengtAllConditionShell[il][ik-1]->GetYaxis()->SetTitleOffset(1.4);
               
                hVertexActivityOnlyIfTrackLenghtAllShell[il][ik-1] = (TH1F*) FolderSubtractedTrackLengthAllShell->Get( Form("VA%s_IfThereAre_%s_All_Shell", VetrexString[ik].Data(), OppositeLenght[il].Data()) ); 
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
        hMomentumVsRange[ig] = (TH2F*) FolderHist2D->Get( Form("MomentumVsRange_%s", ParticleName[ig].Data() ) );
        hMomentumVsRange[ig]->GetYaxis()->SetTitleOffset(1.4);
            
        hEnergyVsRange[ig] = (TH2F*) FolderHist2D->Get( Form("EnergyVsRange_%s", ParticleName[ig].Data()) );
        hEnergyVsRange[ig]->GetYaxis()->SetTitleOffset(1.4);
                
        hEnergyPeVsRange[ig] = (TH2F*) FolderHist2D->Get( Form("EnergyPeVsRange_%s", ParticleName[ig].Data()) );
        hEnergyPeVsRange[ig]->GetYaxis()->SetTitleOffset(1.4);
                
        hEenrgyVsRangehEenrgyVsRangeRestricted[ig] = (TH2F*) FolderHist2D->Get( Form("EnergyVsRange_Restricted_%s", ParticleName[ig].Data()) );
        hEenrgyVsRangehEenrgyVsRangeRestricted[ig]->GetYaxis()->SetTitleOffset(1.4);
        
        hScatteringPathVsMomentum[ig] = (TH2F*) FolderHist2D->Get( Form("ScatteringPathVsMomentum_%s", ParticleName[ig].Data()) );
        hScatteringPathVsMomentum[ig]->GetYaxis()->SetTitleOffset(1.4);
    }
    file->GetObject("t1",t1);
    
    TCanvas *Canvas[300];
    TLegend *legend[300];
    int canvasCounter=0;
    
///////////////////////////////// DRAWING PART STARTS HERE/////////////////////////////   
    /*
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
    */
    Double_t norm;
    for(int ig=0; ig<SizeOfParticleVector; ig++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        norm = 1/hEnergyPeVsRange[ig]->Integral();
        hEnergyPeVsRange[ig]->Scale(norm);
        hEnergyPeVsRange[ig]->GetZaxis()->SetRangeUser(0., 0.15.); //WARNING
        hEnergyPeVsRange[ig]->Draw("COLZ");
        
        gPad->Modified();
        Canvas[canvasCounter]->Print(Form("%sEnergyPeVsRange_%s.pdf",DirectoryPlots.Data(), ParticleName[ig].Data() )); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    /*
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
    
    for(int ik=0; ik<5; ik++) //TODO normalizacja by sie przydala LOW PRIORITY
    {
        //TODO trzeba by dodac jakas ladna  petle abt ominac problemu zmiany badanych czastek LOW PRIORITY
        for(int ig=0; ig<SizeOfParticleVector-1; ig++)
        {
            Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
            
            hVertexActivityParticleCuts[ig][0][ik]->SetLineColorAlpha(kBlue, 1);
            hVertexActivityParticleCuts[ig][0][ik]->SetLineWidth(1.5);
            
            hVertexActivityParticleCuts[ig][1][ik]->SetLineColorAlpha(kGreen, 1);
            hVertexActivityParticleCuts[ig][1][ik]->SetLineWidth(1.5);
        
            //hVertexActivityParticleCuts[ig][2][ik]->SetLineColorAlpha(kRed, 1);
            //hVertexActivityParticleCuts[ig][2][ik]->SetLineWidth(1.5);
            
            hVertexActivityParticleCuts[ig][0][ik]->Draw("");
            hVertexActivityParticleCuts[ig][1][ik]->Draw("SAME");
            //hVertexActivityParticleCuts[ig][2][ik]->Draw("SAME");
        
            legend[canvasCounter] = new TLegend(0.55,0.65,0.9,0.9);
            legend[canvasCounter]->AddEntry(hVertexActivityParticleCuts[ig][0][ik], Form( "VA_NumOf_%s_=0", ParticleName[ig+1].Data() ),"l");
            legend[canvasCounter]->AddEntry(hVertexActivityParticleCuts[ig][1][ik], Form( "VA_NumOf_%s_=1", ParticleName[ig+1].Data() ),"l");
            //legend[canvasCounter]->AddEntry(hVertexActivityParticleCuts[ig][2][ik], Form( "VA_NumOf_%s_=2", ParticleName[ig+1].Data() ),"l");
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
                
                hVASubTrackLengtParticleCondition[il][ig][ik]->SetLineColorAlpha(kBlue, 1);
                hVASubTrackLengtParticleCondition[il][ig][ik]->SetLineWidth(1.5);
                
                hVAOnlyIfTrackLenght[il][ig][ik]->SetLineColorAlpha(kRed, 1);
                hVAOnlyIfTrackLenght[il][ig][ik]->SetLineWidth(1.5);
                
                hVASubTrackLengtParticleCondition[il][ig][ik]->Draw("");
                hVAOnlyIfTrackLenght[il][ig][ik]->Draw("SAME");
                
                legend[canvasCounter] = new TLegend(0.55,0.7,0.9,0.9);
                legend[canvasCounter]->AddEntry(hVASubTrackLengtParticleCondition[il][ig][ik], Form( "VA_Sub_%s_%s",TrackLenght[il].Data(), ParticleName[ig].Data() ),"l");
                legend[canvasCounter]->AddEntry(hVAOnlyIfTrackLenght[il][ig][ik], Form( "VA_Default_If_%s_%s", TrackLenght[il].Data(), ParticleName[ig].Data() ),"l");
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
    
    for(int ik=0; ik<5; ik++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        
        hVertexActivitySelections[0][ik]->SetLineColorAlpha(kBlue, 1);
        hVertexActivitySelections[0][ik]->SetLineWidth(1.5);
                
        hVertexActivitySelections[1][ik]->SetLineColorAlpha(kRed, 1);
        hVertexActivitySelections[1][ik]->SetLineWidth(1.5);
    
        hVertexActivitySelections[2][ik]->SetLineColorAlpha(kGreen, 1);
        hVertexActivitySelections[2][ik]->SetLineWidth(1.5);
    
        hVertexActivitySelections[3][ik]->SetLineColorAlpha(kMagenta, 1);
        hVertexActivitySelections[3][ik]->SetLineWidth(1.5);
            
        hVertexActivitySelections[0][ik]->Draw("");
        hVertexActivitySelections[1][ik]->Draw("SAME");
        hVertexActivitySelections[2][ik]->Draw("SAME");
        hVertexActivitySelections[3][ik]->Draw("SAME");
    
        legend[canvasCounter] = new TLegend(0.60,0.7,0.9,0.9);
        for(int ic=0; ic<SelectionNumber; ic++)
        {
            legend[canvasCounter]->AddEntry(hVertexActivitySelections[ic][ik], Form( "VA%s_%s", VetrexString[ik].Data(), SelectionsName[ic].Data() ),"l");
        }
        legend[canvasCounter]->SetTextSize(0.04);
        legend[canvasCounter]->Draw();
    
        gPad->Modified();
        Canvas[canvasCounter]->Print( Form("%sVA%s_Selections.pdf", DirectorySelePlots.Data(), VetrexString[ik].Data()) ); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    THStack *VAstackSelec[5];
    for(int ik=0; ik<5; ik++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        hVertexActivitySelections[0][ik]->SetFillColor(kRed);
        hVertexActivitySelections[0][ik]->SetMarkerStyle(21);
        hVertexActivitySelections[0][ik]->SetMarkerColor(kRed);

        hVertexActivitySelections[1][ik]->SetFillColor(kGreen);
        hVertexActivitySelections[1][ik]->SetMarkerStyle(21);
        hVertexActivitySelections[1][ik]->SetMarkerColor(kGreen);
        
        hVertexActivitySelections[2][ik]->SetFillColor(kBlue);
        hVertexActivitySelections[2][ik]->SetMarkerStyle(21);
        hVertexActivitySelections[2][ik]->SetMarkerColor(kBlue);
        
        hVertexActivitySelections[3][ik]->SetFillColor(kCyan);
        hVertexActivitySelections[3][ik]->SetMarkerStyle(21);
        hVertexActivitySelections[3][ik]->SetMarkerColor(kCyan);
        
        VAstackSelec[ik] = new THStack( Form("VAstackSelec%s",  VetrexString[ik].Data() ), Form("VAstackSelec%s",  VetrexString[ik].Data()) );
        VAstackSelec[ik]->Add( hVertexActivitySelections[0][ik] );
        VAstackSelec[ik]->Add( hVertexActivitySelections[1][ik] );
        VAstackSelec[ik]->Add( hVertexActivitySelections[2][ik] );
        VAstackSelec[ik]->Add( hVertexActivitySelections[3][ik] );
        
        VAstackSelec[ik]->Draw("");
        
        VAstackSelec[ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data()) );
        
        legend[canvasCounter] = new TLegend(0.60,0.7,0.9,0.9);
        for(int ir=0; ir<SelectionNumber; ir++)
        {
            legend[canvasCounter]->AddEntry(hVertexActivitySelections[ir][ik], Form( "VA%s_%s", VetrexString[ik].Data(), SelectionsName[ir].Data() ),"f");
        }
        legend[canvasCounter]->SetTextSize(0.04);
        legend[canvasCounter]->Draw();
        
        gPad->Modified();
        Canvas[canvasCounter]->Print( Form("%sVA%s_StackSelections.pdf", DirectorySelePlots.Data(), VetrexString[ik].Data()) ); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    THStack *VAstackSelectionsSubtract[5];
    for(int ik=0; ik<5; ik++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        hVASubTrackLengtAllCondSelection[0][1][ik]->SetFillColor(kRed);
        hVASubTrackLengtAllCondSelection[0][1][ik]->SetMarkerStyle(21);
        hVASubTrackLengtAllCondSelection[0][1][ik]->SetMarkerColor(kRed);

        hVASubTrackLengtAllCondSelection[1][1][ik]->SetFillColor(kGreen);
        hVASubTrackLengtAllCondSelection[1][1][ik]->SetMarkerStyle(21);
        hVASubTrackLengtAllCondSelection[1][1][ik]->SetMarkerColor(kGreen);
        
        hVASubTrackLengtAllCondSelection[2][1][ik]->SetFillColor(kBlue);
        hVASubTrackLengtAllCondSelection[2][1][ik]->SetMarkerStyle(21);
        hVASubTrackLengtAllCondSelection[2][1][ik]->SetMarkerColor(kBlue);
        
        hVASubTrackLengtAllCondSelection[3][1][ik]->SetFillColor(kCyan);
        hVASubTrackLengtAllCondSelection[3][1][ik]->SetMarkerStyle(21);
        hVASubTrackLengtAllCondSelection[3][1][ik]->SetMarkerColor(kCyan);
        
        VAstackSelectionsSubtract[ik] = new THStack( Form("VAstackSelectionsSubtract%s",  VetrexString[ik].Data() ), Form("VAstackSelectionsSubtract%s",  VetrexString[ik].Data()) );
        VAstackSelectionsSubtract[ik]->Add( hVASubTrackLengtAllCondSelection[0][1][ik] );
        VAstackSelectionsSubtract[ik]->Add( hVASubTrackLengtAllCondSelection[1][1][ik] );
        VAstackSelectionsSubtract[ik]->Add( hVASubTrackLengtAllCondSelection[2][1][ik] );
        VAstackSelectionsSubtract[ik]->Add( hVASubTrackLengtAllCondSelection[3][1][ik] );
        
        VAstackSelectionsSubtract[ik]->Draw("");
        VAstackSelectionsSubtract[ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data()) );
        
        legend[canvasCounter] = new TLegend(0.60,0.7,0.9,0.9);
        for(int ir=0; ir<SelectionNumber; ir++)
        {
            legend[canvasCounter]->AddEntry(hVASubTrackLengtAllCondSelection[ir][1][ik], Form( "VA%s_%s", VetrexString[ik].Data(), SelectionsName[ir].Data() ),"f");
        }
        legend[canvasCounter]->SetTextSize(0.04);
        legend[canvasCounter]->Draw();
        
        gPad->Modified();
        Canvas[canvasCounter]->Print( Form("%sVA%s_StackSelectionSubtract.pdf", DirectorySelePlots.Data(), VetrexString[ik].Data()) ); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    ////REACTIONS
    THStack *VAstackReac[5];
    for(int ik=0; ik<5; ik++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        //CCQE RES DIS COH NC
        hVertexActivityReaction[0][ik]->SetFillColor(kRed);
        hVertexActivityReaction[0][ik]->SetMarkerStyle(21);
        hVertexActivityReaction[0][ik]->SetMarkerColor(kRed);

        hVertexActivityReaction[1][ik]->SetFillColor(kGreen);
        hVertexActivityReaction[1][ik]->SetMarkerStyle(21);
        hVertexActivityReaction[1][ik]->SetMarkerColor(kGreen);
        
        hVertexActivityReaction[2][ik]->SetFillColor(kBlue);
        hVertexActivityReaction[2][ik]->SetMarkerStyle(21);
        hVertexActivityReaction[2][ik]->SetMarkerColor(kBlue);
        
        hVertexActivityReaction[3][ik]->SetFillColor(kCyan);
        hVertexActivityReaction[3][ik]->SetMarkerStyle(21);
        hVertexActivityReaction[3][ik]->SetMarkerColor(kCyan);
        
        VAstackReac[ik] = new THStack( Form("VAstackReac%s",  VetrexString[ik].Data() ), Form("VAstackReac%s",  VetrexString[ik].Data()) );
        VAstackReac[ik]->Add( hVertexActivityReaction[0][ik] );
        VAstackReac[ik]->Add( hVertexActivityReaction[1][ik] );
        VAstackReac[ik]->Add( hVertexActivityReaction[2][ik] );
        VAstackReac[ik]->Add( hVertexActivityReaction[3][ik] );
        
        VAstackReac[ik]->Draw("");
        
        VAstackReac[ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data()) );
        
        legend[canvasCounter] = new TLegend(0.60,0.7,0.9,0.9);
        for(int ir=0; ir<4; ir++)
        {
            legend[canvasCounter]->AddEntry(hVertexActivityReaction[ir][ik], Form( "VA%s_%s", VetrexString[ik].Data(), ReactionName[ir].Data() ),"f");
        }
        legend[canvasCounter]->SetTextSize(0.04);
        legend[canvasCounter]->Draw();
        
        gPad->Modified();
        Canvas[canvasCounter]->Print( Form("%sVA%s_StackReactions.pdf", DirectoryReacPlots.Data(), VetrexString[ik].Data()) ); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    
    THStack *VAstackReacSubtract[5];
    for(int ik=0; ik<5; ik++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        //CCQE RES DIS COH NC
        hVASubTrackLengtAllCondReaction[0][1][ik]->SetFillColor(kRed);
        hVASubTrackLengtAllCondReaction[0][1][ik]->SetMarkerStyle(21);
        hVASubTrackLengtAllCondReaction[0][1][ik]->SetMarkerColor(kRed);

        hVASubTrackLengtAllCondReaction[1][1][ik]->SetFillColor(kGreen);
        hVASubTrackLengtAllCondReaction[1][1][ik]->SetMarkerStyle(21);
        hVASubTrackLengtAllCondReaction[1][1][ik]->SetMarkerColor(kGreen);
        
        hVASubTrackLengtAllCondReaction[2][1][ik]->SetFillColor(kBlue);
        hVASubTrackLengtAllCondReaction[2][1][ik]->SetMarkerStyle(21);
        hVASubTrackLengtAllCondReaction[2][1][ik]->SetMarkerColor(kBlue);
        
        hVASubTrackLengtAllCondReaction[3][1][ik]->SetFillColor(kCyan);
        hVASubTrackLengtAllCondReaction[3][1][ik]->SetMarkerStyle(21);
        hVASubTrackLengtAllCondReaction[3][1][ik]->SetMarkerColor(kCyan);
        
        VAstackReacSubtract[ik] = new THStack( Form("VAstackReacSubtract%s",  VetrexString[ik].Data() ), Form("VAstackReacSubtract%s",  VetrexString[ik].Data()) );
        VAstackReacSubtract[ik]->Add( hVASubTrackLengtAllCondReaction[0][1][ik] );
        VAstackReacSubtract[ik]->Add( hVASubTrackLengtAllCondReaction[1][1][ik] );
        VAstackReacSubtract[ik]->Add( hVASubTrackLengtAllCondReaction[2][1][ik] );
        VAstackReacSubtract[ik]->Add( hVASubTrackLengtAllCondReaction[3][1][ik] );
        
        VAstackReacSubtract[ik]->Draw("");
        VAstackReacSubtract[ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data()) );
        
        legend[canvasCounter] = new TLegend(0.60,0.7,0.9,0.9);
        for(int ir=0; ir<4; ir++)
        {
            legend[canvasCounter]->AddEntry(hVASubTrackLengtAllCondReaction[ir][1][ik], Form( "VA%s_%s", VetrexString[ik].Data(), ReactionName[ir].Data() ),"f");
        }
        legend[canvasCounter]->SetTextSize(0.04);
        legend[canvasCounter]->Draw();
        
        gPad->Modified();
        Canvas[canvasCounter]->Print( Form("%sVA%s_StackReactionsSubtract.pdf", DirectoryReacPlots.Data(), VetrexString[ik].Data()) ); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    */



    /*
    //WARNING 2p2h may not be compatible with all MC
    THStack *VAstackSplit[SelectionNumber][5];
    for(int ik=0; ik<5; ik++)
    {
        for(int ic=0; ic<SelectionNumber; ic++)
        {
            Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
            //CCQE 2p2h RES DIS COH NC
            hVASplitSelection[ic][0][ik]->SetFillColor(kRed);
            hVASplitSelection[ic][0][ik]->SetMarkerStyle(21);
            hVASplitSelection[ic][0][ik]->SetMarkerColor(kRed);
            
            hVASplitSelection[ic][1][ik]->SetFillColor(kViolet);
            hVASplitSelection[ic][1][ik]->SetMarkerStyle(21);
            hVASplitSelection[ic][1][ik]->SetMarkerColor(kViolet);
            
            hVASplitSelection[ic][2][ik]->SetFillColor(kGreen);
            hVASplitSelection[ic][2][ik]->SetMarkerStyle(21);
            hVASplitSelection[ic][2][ik]->SetMarkerColor(kGreen);
        
            hVASplitSelection[ic][3][ik]->SetFillColor(kBlue);
            hVASplitSelection[ic][3][ik]->SetMarkerStyle(21);
            hVASplitSelection[ic][3][ik]->SetMarkerColor(kBlue);
        
            hVASplitSelection[ic][4][ik]->SetFillColor(kCyan);
            hVASplitSelection[ic][4][ik]->SetMarkerStyle(21);
            hVASplitSelection[ic][4][ik]->SetMarkerColor(kCyan);
        
            VAstackSplit[ic][ik] = new THStack( Form("VAstackSplit%s_%s",  VetrexString[ik].Data(),SelectionsName[ic].Data() ), Form("VAstackSplit%s", VetrexString[ik].Data()) );
            VAstackSplit[ic][ik]->Add( hVASplitSelection[ic][0][ik] );
            VAstackSplit[ic][ik]->Add( hVASplitSelection[ic][1][ik] );
            VAstackSplit[ic][ik]->Add( hVASplitSelection[ic][2][ik] );
            VAstackSplit[ic][ik]->Add( hVASplitSelection[ic][3][ik] );
            VAstackSplit[ic][ik]->Add( hVASplitSelection[ic][4][ik] );
        
            VAstackSplit[ic][ik]->Draw("");
        
            VAstackSplit[ic][ik]->GetXaxis()->SetTitle( Form("Energy deposit in box %s [p.e.]", VetrexString[ik].Data()) );
        
            legend[canvasCounter] = new TLegend(0.60,0.7,0.9,0.9);
            for(int ir=0; ir<ReacTypeNum; ir++)
            {
                legend[canvasCounter]->AddEntry(hVASplitSelection[ic][ir][ik], Form( "VA%s_%s", VetrexString[ik].Data(), ReactionName[ir].Data() ),"f");
            }
            legend[canvasCounter]->SetTextSize(0.04);
            legend[canvasCounter]->Draw();
        
            gPad->Modified();
            Canvas[canvasCounter]->Print( Form("%sVA%s_StackSplit_%s.pdf", DirectorySplitSelectionsPlots.Data(), VetrexString[ik].Data(), SelectionsName[ic].Data()) ); 
            delete Canvas[canvasCounter];
            canvasCounter++;
        }
    }
    THStack *VAstackSplitNuMom[SelectionNumber];
    for(int ic=0; ic<SelectionNumber; ic++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        //CCQE RES DIS COH NC
        h_nuMomSplitSelections[ic][0]->SetFillColor(kRed);
        h_nuMomSplitSelections[ic][0]->SetMarkerStyle(21);
        h_nuMomSplitSelections[ic][0]->SetMarkerColor(kRed);

        h_nuMomSplitSelections[ic][1]->SetFillColor(kViolet);
        h_nuMomSplitSelections[ic][1]->SetMarkerStyle(21);
        h_nuMomSplitSelections[ic][1]->SetMarkerColor(kViolet);
        
        h_nuMomSplitSelections[ic][2]->SetFillColor(kGreen);
        h_nuMomSplitSelections[ic][2]->SetMarkerStyle(21);
        h_nuMomSplitSelections[ic][2]->SetMarkerColor(kGreen);
    
        h_nuMomSplitSelections[ic][3]->SetFillColor(kBlue);
        h_nuMomSplitSelections[ic][3]->SetMarkerStyle(21);
        h_nuMomSplitSelections[ic][3]->SetMarkerColor(kBlue);
    
        h_nuMomSplitSelections[ic][4]->SetFillColor(kCyan);
        h_nuMomSplitSelections[ic][4]->SetMarkerStyle(21);
        h_nuMomSplitSelections[ic][4]->SetMarkerColor(kCyan);
    
        VAstackSplitNuMom[ic] = new THStack( Form("NuMomstackSplit_%s", SelectionsName[ic].Data() ), Form("NuMomstackSplit_%s", SelectionsName[ic].Data() ) );
        VAstackSplitNuMom[ic]->Add( h_nuMomSplitSelections[ic][0] );
        VAstackSplitNuMom[ic]->Add( h_nuMomSplitSelections[ic][1] );
        VAstackSplitNuMom[ic]->Add( h_nuMomSplitSelections[ic][2] );
        VAstackSplitNuMom[ic]->Add( h_nuMomSplitSelections[ic][3] );
        VAstackSplitNuMom[ic]->Add( h_nuMomSplitSelections[ic][3] );
    
        VAstackSplitNuMom[ic]->Draw("");
    
        VAstackSplitNuMom[ic]->GetXaxis()->SetTitle( "Momentum [MeV/c]");
    
        legend[canvasCounter] = new TLegend(0.60,0.7,0.9,0.9);
        for(int ir=0; ir<ReacTypeNum; ir++)
        {
            legend[canvasCounter]->AddEntry(h_nuMomSplitSelections[ic][ir], Form("%s", ReactionName[ir].Data() ),"f");
        }
        legend[canvasCounter]->SetTextSize(0.04);
        legend[canvasCounter]->Draw();
    
        gPad->Modified();
        Canvas[canvasCounter]->Print( Form("%sNuMom_StackSplit_%s.pdf", DirectorySplitSelectionsPlots.Data(), SelectionsName[ic].Data()) ); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    */
}
