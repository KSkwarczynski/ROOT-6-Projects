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
    const int SelectionNumber = 4;
    const int ReacTypeNum = 5;
    const int NumberOfFiles = 7;
    bool CIS = false;
    
    TString Directory="/Users/kolos/Desktop/sFGD/Output/DistanceOutput/";
    TString DirectoryPlots="/Users/kolos/Desktop/sFGD/Plots/DistancePlots/";
    
    if(CIS)
    {
        Directory="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/Output/";
        DirectoryPlots="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/PlotOutput/VertexActivity/"; //TODO dodaj nowy foldr
    }
    
    TString FileName="VertexAcivity_Output";
    TString VetrexString[5]={"1x1x1" , "3x3x3" , "5x5x5", "7x7x7", "9x9x9"};
    TString VertexName[5]={"VertexActivity1x1x1", "VertexActivity3x3x3", "VertexActivity5x5x5", "VertexActivity7x7x7", "VertexActivity9x9x9"};
    TString ParticleName[SizeOfParticleVector]={"Muon", "Pion+", "Proton", "Pion-"};        
    TString ParticleNameBranch[SizeOfParticleVector]={"Muon", "PionP", "Proton", "PionN"};
    TString TrackLenght[2]={"Short", "Long"};
    TString OppositeLenght[2]={"Long", "Short"};
    TString SelectionsName[SelectionNumber]={"CC0Pi", "CC0p0Pi", "CC1Pi", "CCOther"};
    TString ReactionName[ReacTypeNum]={"CCQE", "RES", "DIS", "COH", "NC"};
    
    TFile *file[NumberOfFiles];
    TDirectory *FolderParticleSelections[SelectionNumber][NumberOfFiles];
    TDirectory *FolderReaction[ReacTypeNum][NumberOfFiles];
    
    for(int i=0; i<NumberOfFiles; i++)
    {
        file[i] = new TFile(Form("%sVA_%icm_Output.root", Directory.Data() , i+1 ),"READ");
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
    }
    TH1F *hParticleMomentumReactions[SizeOfParticleVector][ReacTypeNum][NumberOfFiles];
    for(int i=0; i<NumberOfFiles; i++)
    {
        for(int ig=0; ig<SizeOfParticleVector; ig++)
        {
            for(int ir=0; ir<ReacTypeNum; ir++)
            {
                hParticleMomentumReactions[ig][ir][i] = (TH1F*) FolderReaction[ir][i]->Get( Form("Short_%s_mom_%s", ParticleName[ig].Data(), ReactionName[ir].Data() ) );
            }
        }
    }
    TCanvas *Canvas[300];
    TLegend *legend[300];
    int canvasCounter=0;
///////////////////////////////// DRAWING PART STARTS HERE/////////////////////////////  
    for(int ir=0; ir<ReacTypeNum-1; ir++)
    {
        for(int ig=1; ig<SizeOfParticleVector; ig++) //start from 1 since we don't want muons
        {
            Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        
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
            
            hParticleMomentumReactions[ig][ir][0]->Draw("");
            hParticleMomentumReactions[ig][ir][1]->Draw("SAME");
            hParticleMomentumReactions[ig][ir][2]->Draw("SAME");
            hParticleMomentumReactions[ig][ir][3]->Draw("SAME");
            hParticleMomentumReactions[ig][ir][4]->Draw("SAME");
           
            legend[canvasCounter] = new TLegend(0.55,0.6,0.9,0.9);
            for(int i=0; i<5 /*NumberOfFiles*/; i++)
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
}
