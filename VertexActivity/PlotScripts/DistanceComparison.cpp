#include <TH1.h>
#include <TH2F.h>
#include <fstream>
#include <iostream>
#include "TStyle.h"
#include <TColor.h>
#include <TLatex.h>

void DistanceComparison()
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
    const int NumberOfFiles = 7;
    bool CIS = false;
    bool NEUT = true;
    
    TString Directory="/Users/kolos/Desktop/sFGD/Output/DistanceOutput/";
    TString DirectoryPlots="/Users/kolos/Desktop/sFGD/Plots/GENIE/DistancePlots/";
    TString StartName="VA";
    if(CIS)
    {
        Directory="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/Output/";
        DirectoryPlots="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/PlotOutput/VertexActivity/GENIE/";
    }
    
    if(NEUT)
    {
        DirectoryPlots="/Users/kolos/Desktop/sFGD/Plots/NEUT/DistancePlots/";
        StartName = "NEUT_VA";
        if(CIS)
        {
            DirectoryPlots="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/PlotOutput/VertexActivity/NEUT/";
        }
    }
    TString FileName="VertexAcivity_Output";
    TString VetrexString[5]={"1x1x1" , "3x3x3" , "5x5x5", "7x7x7", "9x9x9"};
    TString VertexName[5]={"VertexActivity1x1x1", "VertexActivity3x3x3", "VertexActivity5x5x5", "VertexActivity7x7x7", "VertexActivity9x9x9"};
    TString ParticleName[SizeOfParticleVector]={"Muon", "Pion+", "Proton", "Pion-"};        
    TString ParticleNameBranch[SizeOfParticleVector]={"Muon", "PionP", "Proton", "PionN"};
    TString TrackLenght[2]={"Short", "Long"};
    TString OppositeLenght[2]={"Long", "Short"};
    TString SelectionsName[SelectionNumber]={"1mu1p", "1mu", "1muNp", "CC1Pi", "CCOther"};
    //TString SelectionsName[SelectionNumber]={"CC0Pi", "CC0p0Pi", "CCNp0Pi", "CC1Pi", "CCOther"};
    TString ReactionName[ReacTypeNum]={"CCQE","2p2h", "RES", "DIS", "COH"};
    
    TFile *file[NumberOfFiles];
    TDirectory *FolderParticleSelections[SelectionNumber][NumberOfFiles];
    TDirectory *FolderReaction[ReacTypeNum][NumberOfFiles];
    
    TDirectory *FolderSplitedSelection[SelectionNumber][NumberOfFiles];
    
    for(int i=0; i<NumberOfFiles; i++)
    {
        file[i] = new TFile( Form("%s%s_%icm_Output.root", Directory.Data() , StartName.Data(), i+1 ),"READ");
        if (file[i]->IsOpen() )
        {
            cout<<i+1<<"cm"<<" File opened successfully"<<endl;
        }  
        
        for(int ic=0; ic<SelectionNumber; ic++) 
        {
            FolderParticleSelections[ic][i]= (TDirectory*)file[i]->Get( Form( "Folder%s", SelectionsName[ic].Data() ) );
        }
        for(int ir=0; ir<ReacTypeNum; ir++) 
        {
            FolderReaction[ir][i]= (TDirectory*)file[i]->Get( Form( "Folder%s", ReactionName[ir].Data() ) );
        }
        for(int ic=0; ic<SelectionNumber; ic++)
        {
            FolderSplitedSelection[ic][i]= (TDirectory*)file[i]->Get( Form( "FolderSplited%s", SelectionsName[ic].Data() ) );
        }
    }
    TH1F *hVertexActivitySelections[SelectionNumber][5][NumberOfFiles]; //[vertexBox]
    TH1F *hVertexActivityReaction[ReacTypeNum][5][NumberOfFiles]; //[vertexBox]
    TH1F *hParticleMomentumReactions[SizeOfParticleVector][ReacTypeNum][NumberOfFiles];
    TH1F *hParticleMomentumSplitSelection[SizeOfParticleVector][SelectionNumber][ReacTypeNum][NumberOfFiles];
    TH1F *h_nuMomSplitSelections[SelectionNumber][ReacTypeNum][NumberOfFiles];
    TH1F *hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[SelectionNumber][ReacTypeNum][2][4][NumberOfFiles];
    for(int i=0; i<NumberOfFiles; i++)
    {
        for(int ig=0; ig<SizeOfParticleVector; ig++)
        {
            for(int ir=0; ir<ReacTypeNum; ir++)
            {
                hParticleMomentumReactions[ig][ir][i] = (TH1F*) FolderReaction[ir][i]->Get( Form("Short_%s_mom_%s", ParticleName[ig].Data(), ReactionName[ir].Data() ) );
            }
            for(int ic=0; ic<SelectionNumber; ic++)
            {
                for(int ir=0; ir<ReacTypeNum; ir++)
                {
                    hParticleMomentumSplitSelection[ig][ic][ir][i]= (TH1F*) FolderSplitedSelection[ic][i]->Get( Form("Short_%s_mom_%s_%s", ParticleName[ig].Data(), SelectionsName[ic].Data(), ReactionName[ir].Data() ) );
                }
            }
        }
        for(int ic=0; ic<SelectionNumber; ic++)
        {
            for(int ir=0; ir<ReacTypeNum; ir++)
            {
                h_nuMomSplitSelections[ic][ir][i]= (TH1F*) FolderSplitedSelection[ic][i]->Get( Form("nuMom%s_%s", SelectionsName[ic].Data(), ReactionName[ir].Data() ) );
                for(int il=LongOrShort; il<2; il++) //loop over short long track
                {
                    for(int ik=0; ik<4; ik++)
                    {                        
                        hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][il][ik][i] = (TH1F*) FolderSplitedSelection[ic][i]->Get( Form("VA%s_IfThereAre_%s__%s_%s_Shell", VetrexString[ik+1].Data(), OppositeLenght[il].Data(), SelectionsName[ic].Data(), ReactionName[ir].Data()) );
                    }
                }
            }
            for(int ik=0; ik<5; ik++)
            {
                hVertexActivitySelections[ic][ik][i]= (TH1F*) FolderParticleSelections[ic][i]->Get( Form("VA%s_%s", VetrexString[ik].Data(), SelectionsName[ic].Data()) );
            }
            
        }
        for(int ir=0; ir<ReacTypeNum; ir++)
        {
            for(int ik=0; ik<5; ik++)
            {
                hVertexActivityReaction[ir][ik][i]= (TH1F*) FolderReaction[ir][i]->Get( Form("VA%s_%s", VetrexString[ik].Data(), ReactionName[ir].Data() ) );
            }
        }
    }
    TCanvas *Canvas[300];
    TLegend *legend[300];
    int canvasCounter=0;
    int norma=1;
///////////////////////////////// DRAWING PART STARTS HERE/////////////////////////////  
    /*
    int binowanie=hParticleMomentumReactions[0][0][0]->GetNbinsX();
    long double normalizacja[SizeOfParticleVector][ReacTypeNum][NumberOfFiles];
   
    for(int ir=0; ir<ReacTypeNum; ir++)
    {
        for(int ig=1; ig<SizeOfParticleVector; ig++) //start from 1 since we don't want muons
        {
            Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
            for(int i=0; i<NumberOfFiles; i++)
            {
                for(int ib=0;ib<=binowanie;ib++)
                {
                    normalizacja[ig][ir][i]+=hParticleMomentumReactions[ig][ir][i]->GetBinContent(ib);
                }
                hParticleMomentumReactions[ig][ir][i]->Scale(norma/normalizacja[ig][ir][i]);
            }
            
            hParticleMomentumReactions[ig][ir][0]->SetLineColorAlpha(kRed, 1);
            hParticleMomentumReactions[ig][ir][0]->SetLineWidth(1.5);

            hParticleMomentumReactions[ig][ir][1]->SetLineColorAlpha(kGreen, 1);
            hParticleMomentumReactions[ig][ir][1]->SetLineWidth(1.5);
            
            hParticleMomentumReactions[ig][ir][2]->SetLineColorAlpha(kBlue, 1);
            hParticleMomentumReactions[ig][ir][2]->SetLineWidth(1.5);
            
            hParticleMomentumReactions[ig][ir][3]->SetLineColorAlpha(kMagenta, 1);
            hParticleMomentumReactions[ig][ir][3]->SetLineWidth(1.5);
        
            hParticleMomentumReactions[ig][ir][4]->SetLineColorAlpha(kCyan, 1);
            hParticleMomentumReactions[ig][ir][4]->SetLineWidth(1.5);
            
            hParticleMomentumReactions[ig][ir][5]->SetLineColorAlpha(kOrange, 1);
            hParticleMomentumReactions[ig][ir][5]->SetLineWidth(1.5);
            
            hParticleMomentumReactions[ig][ir][6]->SetLineColorAlpha(kYellow, 1);
            hParticleMomentumReactions[ig][ir][6]->SetLineWidth(1.5);
            
            
            hParticleMomentumReactions[ig][ir][0]->Draw("");
            hParticleMomentumReactions[ig][ir][1]->Draw("SAME");
            hParticleMomentumReactions[ig][ir][2]->Draw("SAME");
            hParticleMomentumReactions[ig][ir][3]->Draw("SAME");
            hParticleMomentumReactions[ig][ir][4]->Draw("SAME");
            hParticleMomentumReactions[ig][ir][5]->Draw("SAME");
            hParticleMomentumReactions[ig][ir][6]->Draw("SAME");
            legend[canvasCounter] = new TLegend(0.55,0.6,0.9,0.9);
            for(int i=0; i<NumberOfFiles; i++)
            {
                legend[canvasCounter]->AddEntry(hParticleMomentumReactions[ig][ir][i], Form( "%icm_%s", i+1, ParticleName[ig].Data() ),"l");
            }
            legend[canvasCounter]->SetTextSize(0.035);
            legend[canvasCounter]->Draw();
            
            gPad->Modified();
            Canvas[canvasCounter]->Print( Form("%s%sMom_%s.pdf", DirectoryPlots.Data(), ParticleName[ig].Data(), ReactionName[ir].Data() ) ); 
            delete Canvas[canvasCounter];
            canvasCounter++;
        }  
    }
    
    int binowanieReac[5];
    long double normalizacjaReac[ReacTypeNum][5][NumberOfFiles];  
    
    for(int ik=0; ik<5; ik++) //start from 1 since we don't want muons
    {
        binowanieReac[ik]=hVertexActivityReaction[0][ik][0]->GetNbinsX();
        for(int ir=0; ir<ReacTypeNum; ir++)
        {
            Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
            for(int i=0; i<NumberOfFiles; i++)
            {
                for(int ib=0;ib<=binowanieReac[ik];ib++)
                {
                    normalizacjaReac[ir][ik][i]+=hVertexActivityReaction[ir][ik][i]->GetBinContent(ib);
                }
                hVertexActivityReaction[ir][ik][i]->Scale(norma/normalizacjaReac[ir][ik][i]);
            }
            
            hVertexActivityReaction[ir][ik][0]->SetLineColorAlpha(kRed, 1);
            hVertexActivityReaction[ir][ik][0]->SetLineWidth(1.5);

            hVertexActivityReaction[ir][ik][1]->SetLineColorAlpha(kGreen, 1);
            hVertexActivityReaction[ir][ik][1]->SetLineWidth(1.5);
            
            hVertexActivityReaction[ir][ik][2]->SetLineColorAlpha(kBlue, 1);
            hVertexActivityReaction[ir][ik][2]->SetLineWidth(1.5);
            
            hVertexActivityReaction[ir][ik][3]->SetLineColorAlpha(kMagenta, 1);
            hVertexActivityReaction[ir][ik][3]->SetLineWidth(1.5);
        
            hVertexActivityReaction[ir][ik][4]->SetLineColorAlpha(kCyan, 1);
            hVertexActivityReaction[ir][ik][4]->SetLineWidth(1.5);
            
            hVertexActivityReaction[ir][ik][5]->SetLineColorAlpha(kOrange, 1);
            hVertexActivityReaction[ir][ik][5]->SetLineWidth(1.5);
            
            hVertexActivityReaction[ir][ik][6]->SetLineColorAlpha(kYellow, 1);
            hVertexActivityReaction[ir][ik][6]->SetLineWidth(1.5);
            
            hVertexActivityReaction[ir][ik][0]->Draw("");
            hVertexActivityReaction[ir][ik][1]->Draw("SAME");
            hVertexActivityReaction[ir][ik][2]->Draw("SAME");
            hVertexActivityReaction[ir][ik][3]->Draw("SAME");
            hVertexActivityReaction[ir][ik][4]->Draw("SAME");
            hVertexActivityReaction[ir][ik][5]->Draw("SAME");
            hVertexActivityReaction[ir][ik][6]->Draw("SAME");
            legend[canvasCounter] = new TLegend(0.55,0.6,0.9,0.9);
            for(int i=0; i<NumberOfFiles; i++)
            {
                legend[canvasCounter]->AddEntry(hVertexActivityReaction[ir][ik][i], Form( "%icm_VA%s", i+1, VertexString[ik].Data() ),"l");
            }
            legend[canvasCounter]->SetTextSize(0.035);
            legend[canvasCounter]->Draw();
            
            gPad->Modified();
            Canvas[canvasCounter]->Print( Form("%sVA%s_%s_Comparison.pdf", DirectoryPlots.Data(), VertexString[ik].Data(), ReactionName[ir].Data() ) ); 
            delete Canvas[canvasCounter];
            canvasCounter++;
        }  
    }
    */
    int binowanieSelec[5];
    long double normalizacjaSelec[SelectionNumber][5][NumberOfFiles];  
    //hVertexActivitySelections[4][1][6]->Draw();
    
    for(int ik=0; ik<5; ik++) //start from 1 since we don't want muons
    {
        binowanieSelec[ik]=hVertexActivitySelections[0][ik][0]->GetNbinsX();
        for(int ic=0; ic<SelectionNumber; ic++)
        {
            Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
            for(int i=0; i<NumberOfFiles; i++)
            {
                for(int ib=0;ib<=binowanieSelec[ik];ib++)
                {
                    normalizacjaSelec[ic][ik][i]+=hVertexActivitySelections[ic][ik][i]->GetBinContent(ib);
                }
                hVertexActivitySelections[ic][ik][i]->Scale(norma/normalizacjaSelec[ic][ik][i]);
            }
            
            hVertexActivitySelections[ic][ik][0]->SetLineColorAlpha(kRed, 1);
            hVertexActivitySelections[ic][ik][0]->SetLineWidth(1.5);

            hVertexActivitySelections[ic][ik][1]->SetLineColorAlpha(kGreen, 1);
            hVertexActivitySelections[ic][ik][1]->SetLineWidth(1.5);
            
            hVertexActivitySelections[ic][ik][2]->SetLineColorAlpha(kBlue, 1);
            hVertexActivitySelections[ic][ik][2]->SetLineWidth(1.5);
            
            hVertexActivitySelections[ic][ik][3]->SetLineColorAlpha(kMagenta, 1);
            hVertexActivitySelections[ic][ik][3]->SetLineWidth(1.5);
        
            hVertexActivitySelections[ic][ik][4]->SetLineColorAlpha(kCyan, 1);
            hVertexActivitySelections[ic][ik][4]->SetLineWidth(1.5);
            
            hVertexActivitySelections[ic][ik][5]->SetLineColorAlpha(kOrange, 1);
            hVertexActivitySelections[ic][ik][5]->SetLineWidth(1.5);
            
            hVertexActivitySelections[ic][ik][6]->SetLineColorAlpha(kYellow, 1);
            hVertexActivitySelections[ic][ik][6]->SetLineWidth(1.5);
            
            hVertexActivitySelections[ic][ik][0]->Draw("");
            hVertexActivitySelections[ic][ik][1]->Draw("SAME");
            hVertexActivitySelections[ic][ik][2]->Draw("SAME");
            hVertexActivitySelections[ic][ik][3]->Draw("SAME");
            hVertexActivitySelections[ic][ik][4]->Draw("SAME");
            hVertexActivitySelections[ic][ik][5]->Draw("SAME");
            hVertexActivitySelections[ic][ik][6]->Draw("SAME");
            legend[canvasCounter] = new TLegend(0.65,0.6,0.9,0.9);
            for(int i=0; i<NumberOfFiles; i++)
            {
                legend[canvasCounter]->AddEntry(hVertexActivitySelections[ic][ik][i], Form( "%icm_VA%s", i+1, VetrexString[ik].Data() ),"l");
            }
            legend[canvasCounter]->SetTextSize(0.035);
            legend[canvasCounter]->Draw();
            
            gPad->Modified();
            Canvas[canvasCounter]->Print( Form("%sVA%s_%s_Comparison.pdf", DirectoryPlots.Data(), VetrexString[ik].Data(), SelectionsName[ic].Data() ) ); 
            delete Canvas[canvasCounter];
            canvasCounter++;
        }  
    }
    /*
    int binowanieShell[4];
    long double normalizacjaShell[SelectionNumber][ReacTypeNum][4][NumberOfFiles];  

    for(int ik=0; ik<4; ik++) //start from 1 since we don't want muons
    {
        binowanieShell[ik]=hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[0][0][1][ik][0]->GetNbinsX();
        for(int ic=0; ic<SelectionNumber; ic++)
        {
            for(int ir=0; ir<ReacTypeNum; ir++)
            {
                Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
                for(int i=0; i<NumberOfFiles; i++)
                {
                    for(int ib=0;ib<=binowanieShell[ik];ib++)
                    {
                        normalizacjaShell[ic][ir][ik][i]+=hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][i]->GetBinContent(ib);
                    }
                    hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][i]->Scale(norma/normalizacjaShell[ic][ir][ik][i]);
                }
                
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][0]->SetLineColorAlpha(kRed, 1);
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][0]->SetLineWidth(1.5);

                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][1]->SetLineColorAlpha(kGreen, 1);
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][1]->SetLineWidth(1.5);
                
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][2]->SetLineColorAlpha(kBlue, 1);
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][2]->SetLineWidth(1.5);
                
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][3]->SetLineColorAlpha(kMagenta, 1);
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][3]->SetLineWidth(1.5);
            
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][4]->SetLineColorAlpha(kCyan, 1);
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][4]->SetLineWidth(1.5);
                
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][5]->SetLineColorAlpha(kOrange, 1);
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][5]->SetLineWidth(1.5);
                
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][6]->SetLineColorAlpha(kYellow, 1);
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][6]->SetLineWidth(1.5);
                
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][0]->Draw("");
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][1]->Draw("SAME");
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][2]->Draw("SAME");
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][3]->Draw("SAME");
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][4]->Draw("SAME");
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][5]->Draw("SAME");
                hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][6]->Draw("SAME");
                legend[canvasCounter] = new TLegend(0.55,0.6,0.9,0.9);
                for(int i=0; i<NumberOfFiles; i++)
                {
                    legend[canvasCounter]->AddEntry(hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][i], Form( "%icm_%s", i+1, VetrexString[ik].Data() ),"l");
                }
                legend[canvasCounter]->SetTextSize(0.035);
                legend[canvasCounter]->Draw();
                
                gPad->Modified();
                Canvas[canvasCounter]->Print( Form("%sVAShell%s_%s_%s.pdf", DirectoryPlots.Data(), VetrexString[ik+1].Data(), SelectionsName[ic].Data(), ReactionName[ir].Data() ) ); 
                delete Canvas[canvasCounter];
                canvasCounter++;
            }  
        }
    }

 
    fstream plik;
    plik.open( Form("%sParticleNumber.txt", DirectoryPlots.Data()), ios::out); 
    for(int ic=0; ic<SelectionNumber; ic++)
    {
        plik<<SelectionsName[ic].Data()<<endl;
        for(int ir=0; ir<ReacTypeNum; ir++)
        {
            plik<<ReactionName[ir].Data()<<" 1 "<<"2 "<<"3 "<<"4 "<<"5 "<<"6 "<<"7"<<endl;
            for(int ig=1; ig<SizeOfParticleVector; ig++) //start from 1 since we don't want muons
            {
                plik<<ParticleName[ig].Data()<<" "<< hParticleMomentumSplitSelection[ig][ic][ir][0]->GetEntries()<<" "<< hParticleMomentumSplitSelection[ig][ic][ir][1]->GetEntries()<<" "<<hParticleMomentumSplitSelection[ig][ic][ir][2]->GetEntries()<<" "<<hParticleMomentumSplitSelection[ig][ic][ir][3]->GetEntries()<<" "<<hParticleMomentumSplitSelection[ig][ic][ir][4]->GetEntries()<<" "<<hParticleMomentumSplitSelection[ig][ic][ir][5]->GetEntries()<<" "<<hParticleMomentumSplitSelection[ig][ic][ir][6]->GetEntries()<<endl;
            }
        }
    }
    plik.close();
    
    fstream FileContamination;
    FileContamination.open( Form("%sBeamContamination.txt", DirectoryPlots.Data()), ios::out); 
    double AllEvents[SelectionNumber][NumberOfFiles]={};
    
    for(int i=0; i<NumberOfFiles; i++)
    {
        for(int ic=0; ic<SelectionNumber; ic++)
        {
            for(int ir=0; ir<ReacTypeNum; ir++)
            {
                AllEvents[ic][i] =AllEvents[ic][i]+h_nuMomSplitSelections[ic][ir][i]->GetEntries();
            }
        }
    }
    for(int ic=0; ic<SelectionNumber; ic++)
    {
        FileContamination<<SelectionsName[ic].Data()<<" 1 "<<"2 "<<"3 "<<"4 "<<"5 "<<"6 "<<"7"<<endl;
        for(int ir=0; ir<ReacTypeNum; ir++)
        {
            FileContamination<<ReactionName[ir].Data()<<" "<< h_nuMomSplitSelections[ic][ir][0]->GetEntries()/AllEvents[ic][0]*100<<" "<< h_nuMomSplitSelections[ic][ir][1]->GetEntries()/AllEvents[ic][1]*100<<" "<<h_nuMomSplitSelections[ic][ir][2]->GetEntries()/AllEvents[ic][2]*100<<" "<<h_nuMomSplitSelections[ic][ir][3]->GetEntries()/AllEvents[ic][3]*100<<" "<<h_nuMomSplitSelections[ic][ir][4]->GetEntries()/AllEvents[ic][4]*100<<" "<<h_nuMomSplitSelections[ic][ir][5]->GetEntries()/AllEvents[ic][5]*100<<" "<<h_nuMomSplitSelections[ic][ir][6]->GetEntries()/AllEvents[ic][6]*100<<endl;
        }
    }
    FileContamination.close();

    fstream FileEventCounter;
    FileEventCounter.open( Form("%sEventCounter.txt", DirectoryPlots.Data()), ios::out); 
    
    for(int ic=0; ic<SelectionNumber; ic++)
    {
        FileEventCounter<<" 1 "<<"2 "<<"3 "<<"4 "<<"5 "<<"6 "<<"7"<<endl;
        FileEventCounter<<SelectionsName[ic].Data()<<" "<<AllEvents[ic][0]<<" "<<AllEvents[ic][1]<<" "<<AllEvents[ic][2]<<" "<<AllEvents[ic][3]<<" "<<AllEvents[ic][4]<<" "<<AllEvents[ic][5]<<" "<<AllEvents[ic][6]<<endl;
        for(int ir=0; ir<ReacTypeNum; ir++)
        {
           FileEventCounter<<ReactionName[ir].Data()<<" "<< h_nuMomSplitSelections[ic][ir][0]->GetEntries()<<" "<< h_nuMomSplitSelections[ic][ir][1]->GetEntries()<<" "<<h_nuMomSplitSelections[ic][ir][2]->GetEntries()<<" "<<h_nuMomSplitSelections[ic][ir][3]->GetEntries()<<" "<<h_nuMomSplitSelections[ic][ir][4]->GetEntries()<<" "<<h_nuMomSplitSelections[ic][ir][5]->GetEntries()<<" "<<h_nuMomSplitSelections[ic][ir][6]->GetEntries()<<endl; 
            
        }
    }
    FileEventCounter.close();
    
    fstream FileMeanShell;
    FileMeanShell.open( Form("%sMeanShell.txt", DirectoryPlots.Data()), ios::out); 
    for(int ic=0; ic<SelectionNumber; ic++)
    {
        FileMeanShell<<" 1 "<<"2 "<<"3 "<<"4 "<<"5 "<<"6 "<<"7"<<endl;
        FileMeanShell<<SelectionsName[ic].Data()<<endl;
        for(int ir=0; ir<ReacTypeNum; ir++)
        {
            FileMeanShell<<ReactionName[ir].Data()<<endl;
            for(int ik=0; ik<4; ik++)
            {
                FileMeanShell<<VetrexString [ik+1].Data()<<" "<<hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][0]->GetMean()<<" "<<hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][1]->GetMean()<<" "<<hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][2]->GetMean()<<" "<<hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][3]->GetMean()<<" "<<hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][4]->GetMean()<<" "<<hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][5]->GetMean()<<" "<<hVertexActivityOnlyIfTrackLenghtAllSplitSelectionShell[ic][ir][1][ik][6]->GetMean()<<endl;
            }
        }
    }
    FileMeanShell.close();
*/
}
