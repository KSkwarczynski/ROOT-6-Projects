#include <TH1.h>
#include <TH2F.h>
#include <fstream>
#include <iostream>
#include "TStyle.h"
#include <TColor.h>
#include <TLatex.h>

void NEUTvsGENIE()
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
    gStyle->SetPadTickX(0);
    gStyle->SetPadTickY(0);

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
    const int NumberOfFiles = 2;
    bool CIS = false;
    
    TString Directory="/Users/kolos/Desktop/sFGD/Output/";
    TString DirectoryPlots="/Users/kolos/Desktop/sFGD/Plots/NG-Comparison/";

    TString FileName[NumberOfFiles]={"VertexAcivity_Output", "NeutVertexAcivity_Output"};
    TString VetrexString[5]={"1x1x1" , "3x3x3" , "5x5x5", "7x7x7", "9x9x9"};
    TString VertexName[5]={"VertexActivity1x1x1", "VertexActivity3x3x3", "VertexActivity5x5x5", "VertexActivity7x7x7", "VertexActivity9x9x9"};
    TString ParticleName[SizeOfParticleVector]={"Muon", "Pion+", "Proton", "Pion-"};        
    TString ParticleNameBranch[SizeOfParticleVector]={"Muon", "PionP", "Proton", "PionN"};
    TString TrackLenght[2]={"Short", "Long"};
    TString OppositeLenght[2]={"Long", "Short"};
    TString SelectionsName[SelectionNumber]={"1mu1p", "1mu", "1muNp", "CC1Pi", "CCOther"};
    TString ReactionName[ReacTypeNum]={"CCQE","2p2h", "RES", "DIS", "COH"};
    
    TFile *file[NumberOfFiles];
    TDirectory *FolderParticleSelections[SelectionNumber][NumberOfFiles];
    TDirectory *FolderReaction[ReacTypeNum][NumberOfFiles];
    TDirectory *FolderSplitedSelection[SelectionNumber][NumberOfFiles];
    TDirectory *FolderHist2D[NumberOfFiles];

    for(int i=0; i<NumberOfFiles; i++)
    {
        file[i] = new TFile( Form("%s%s.root", Directory.Data() , FileName[i].Data() ),"READ");
        if (file[i]->IsOpen() )
        {
            cout<<i+1<<" File opened successfully"<<endl;
        }  
        FolderHist2D[i] = (TDirectory*)file[i]->Get("FolderHist2D");
        
        for(int ic=0; ic<SelectionNumber; ic++) 
        {
            FolderParticleSelections[ic][i]= (TDirectory*)file[i]->Get( Form( "Folder%s", SelectionsName[ic].Data() ) );
        }
        /*
        for(int ir=0; ir<ReacTypeNum; ir++) 
        {
            FolderReaction[ir][i]= (TDirectory*)file[i]->Get( Form( "Folder%s", ReactionName[ir].Data() ) );
        }
        for(int ic=0; ic<SelectionNumber; ic++)
        {
            FolderSplitedSelection[ic][i]= (TDirectory*)file[i]->Get( Form( "FolderSplited%s", SelectionsName[ic].Data() ) );
        }
        */
    }
    TH1F *hVertexActivity[5][NumberOfFiles]; //[vertexBox]
    TH1F *h_nuMom[NumberOfFiles];
    TH1F *hprotonMomentum[NumberOfFiles];
    
    TH1F *hVertexPosX[NumberOfFiles];
    TH1F *hVertexPosY[NumberOfFiles];
    TH1F *hVertexPosZ[NumberOfFiles];
    
    TH2F *hEnergyPeVsRange[SizeOfParticleVector][NumberOfFiles];
    
    TH1F *hVertexActivitySelections[SelectionNumber][5][NumberOfFiles];
    for(int i=0; i<NumberOfFiles; i++)
    {
        for(int ik=0; ik<5; ik++)
        {
            hVertexActivity[ik][i] = (TH1F*) file[i]->Get( VertexName[ik].Data());
            for(int ic=0; ic<SelectionNumber; ic++)
            {
                hVertexActivitySelections[ic][ik][i]= (TH1F*) FolderParticleSelections[ic][i]->Get(  Form("VA%s_%s", VetrexString[ik].Data(), SelectionsName[ic].Data() ) );
            }
        }
         h_nuMom[i] = (TH1F*) file[i]->Get( "h_nuMom" );
         hprotonMomentum[i] = (TH1F*) file[i]->Get( "protonMomentum" );
         
         hVertexPosX[i] = (TH1F*) file[i]->Get( "hVertexPosX" );
         hVertexPosY[i] = (TH1F*) file[i]->Get( "hVertexPosY" );
         hVertexPosZ[i] = (TH1F*) file[i]->Get( "hVertexPosZ" );
        for(int ig=0; ig<SizeOfParticleVector; ig++)
        {
            hEnergyPeVsRange[ig][i] = (TH2F*) FolderHist2D[i]->Get( Form("EnergyPeVsRange_%s", ParticleName[ig].Data()) );
            hEnergyPeVsRange[ig][i]->GetYaxis()->SetTitleOffset(1.4);
        }
    }
    TCanvas *Canvas[300];
    TLegend *legend[300];
    int canvasCounter=0;
    int norma=1;
    Double_t norm;
///////////////////////////////// DRAWING PART STARTS HERE///////////////////////////// 
    /*
    int binowanieVA[5]={};
    long double normalizacjaVA[5][NumberOfFiles];
    for(int ik=0; ik<5; ik++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        
        binowanieVA[ik]=hVertexActivity[ik][0]->GetNbinsX();
        for(int i=0; i<NumberOfFiles; i++)
        {
            for(int ib=0;ib<=binowanieVA[ik];ib++)
            {
                    normalizacjaVA[ik][i]+= hVertexActivity[ik][i]->GetBinContent(ib);
            }
            hVertexActivity[ik][i]->Scale(norma/normalizacjaVA[ik][i]);
            //hVertexActivity[ik][i]->Scale(100/hVertexActivity[ik][i]->Integral("width"));
        }
    
        hVertexActivity[ik][0]->SetLineColorAlpha(kBlue, 1);
        hVertexActivity[ik][0]->SetLineWidth(1.5);
        
        hVertexActivity[ik][1]->SetLineColorAlpha(kRed, 1);
        hVertexActivity[ik][1]->SetLineWidth(1.5);
    
        hVertexActivity[ik][0]->Draw("");
        hVertexActivity[ik][1]->Draw("SAME");
    
        legend[canvasCounter] = new TLegend(0.55,0.65,0.9,0.9);
        legend[canvasCounter]->AddEntry(hVertexActivity[ik][0], Form( "VA%s_GENIE", VetrexString[ik].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivity[ik][1], Form( "VA%s_NEUT", VetrexString[ik].Data() ),"l");
        legend[canvasCounter]->SetTextSize(0.04);
        legend[canvasCounter]->Draw();
    
        gPad->Modified();
        Canvas[canvasCounter]->Print( Form("%sVA%sNG.pdf", DirectoryPlots.Data(), VetrexString[ik].Data() ) ); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }

    Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
    
    int binowanieNuMom=h_nuMom[0]->GetNbinsX();
    long double normalizacjaNuMom[NumberOfFiles];  
    
    for(int i=0; i<NumberOfFiles; i++)
    {
        for(int ib=0;ib<=binowanieNuMom;ib++)
        {
                normalizacjaNuMom[i]+=h_nuMom[i]->GetBinContent(ib);
        }
        h_nuMom[i]->Scale(norma/normalizacjaNuMom[i]);
    }
            
    h_nuMom[0]->SetLineColorAlpha(kBlue, 1);
    h_nuMom[0]->SetLineWidth(1.5);
    
    h_nuMom[1]->SetLineColorAlpha(kRed, 1);
    h_nuMom[1]->SetLineWidth(1.5);

    h_nuMom[1]->Draw("");
    h_nuMom[0]->Draw("SAME");

    legend[canvasCounter] = new TLegend(0.55,0.65,0.9,0.9);
    legend[canvasCounter]->AddEntry(h_nuMom[0], "GENIE","l");
    legend[canvasCounter]->AddEntry(h_nuMom[1], "NEUT","l");
    legend[canvasCounter]->SetTextSize(0.04);
    legend[canvasCounter]->Draw();

    gPad->Modified();
    Canvas[canvasCounter]->Print( Form("%sNuMomNG.pdf", DirectoryPlots.Data() ) ); 
    delete Canvas[canvasCounter];
    canvasCounter++;
    
    
    
    Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
    
    int binowaniePrMom=hprotonMomentum[0]->GetNbinsX();
    long double normalizacjaPrMom[NumberOfFiles];  
    
    for(int i=0; i<NumberOfFiles; i++)
    {
        for(int ib=0;ib<=binowaniePrMom;ib++)
        {
                normalizacjaPrMom[i]+=hprotonMomentum[i]->GetBinContent(ib);
        }
        hprotonMomentum[i]->Scale(norma/normalizacjaPrMom[i]);
    }
            
    hprotonMomentum[0]->SetLineColorAlpha(kBlue, 1);
    hprotonMomentum[0]->SetLineWidth(1.5);
    
    hprotonMomentum[1]->SetLineColorAlpha(kRed, 1);
    hprotonMomentum[1]->SetLineWidth(1.5);

    hprotonMomentum[1]->Draw("");
    hprotonMomentum[0]->Draw("SAME");

    legend[canvasCounter] = new TLegend(0.55,0.65,0.9,0.9);
    legend[canvasCounter]->AddEntry(hprotonMomentum[0], "GENIE","l");
    legend[canvasCounter]->AddEntry(hprotonMomentum[1], "NEUT","l");
    legend[canvasCounter]->SetTextSize(0.04);
    legend[canvasCounter]->Draw();

    gPad->Modified();
    Canvas[canvasCounter]->Print( Form("%sProtonMomNG.pdf", DirectoryPlots.Data() ) ); 
    delete Canvas[canvasCounter];
    canvasCounter++;
    
    
    Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
    
    int binowaniePosX=hVertexPosX[0]->GetNbinsX();
    long double normalizacjaPosX[NumberOfFiles];  
    
    for(int i=0; i<NumberOfFiles; i++)
    {
        for(int ib=0;ib<=binowaniePosX;ib++)
        {
                normalizacjaPosX[i]+=hVertexPosX[i]->GetBinContent(ib);
        }
        hVertexPosX[i]->Scale(norma/normalizacjaPosX[i]);
    }
            
    hVertexPosX[0]->SetLineColorAlpha(kBlue, 1);
    hVertexPosX[0]->SetLineWidth(1.5);
    
    hVertexPosX[1]->SetLineColorAlpha(kRed, 1);
    hVertexPosX[1]->SetLineWidth(1.5);

    hVertexPosX[1]->Draw("");
    hVertexPosX[0]->Draw("SAME");

    legend[canvasCounter] = new TLegend(0.55,0.2,0.9,0.4);
    legend[canvasCounter]->AddEntry(hVertexPosX[0], "GENIE","l");
    legend[canvasCounter]->AddEntry(hVertexPosX[1], "NEUT","l");
    legend[canvasCounter]->SetTextSize(0.04);
    legend[canvasCounter]->Draw();

    gPad->Modified();
    Canvas[canvasCounter]->Print( Form("%sVertexPosX.pdf", DirectoryPlots.Data() ) ); 
    delete Canvas[canvasCounter];
    canvasCounter++;
    
    Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
    
    int binowaniePosY=hVertexPosY[0]->GetNbinsX();
    long double normalizacjaPosY[NumberOfFiles];  
    
    for(int i=0; i<NumberOfFiles; i++)
    {
        for(int ib=0;ib<=binowaniePosY;ib++)
        {
                normalizacjaPosY[i]+=hVertexPosY[i]->GetBinContent(ib);
        }
        hVertexPosY[i]->Scale(norma/normalizacjaPosX[i]);
    }
            
    hVertexPosY[0]->SetLineColorAlpha(kBlue, 1);
    hVertexPosY[0]->SetLineWidth(1.5);
    
    hVertexPosY[1]->SetLineColorAlpha(kRed, 1);
    hVertexPosY[1]->SetLineWidth(1.5);

    hVertexPosY[0]->Draw("");
    hVertexPosY[1]->Draw("SAME");
    

    legend[canvasCounter] = new TLegend(0.55,0.2,0.9,0.4);
    legend[canvasCounter]->AddEntry(hVertexPosY[0], "GENIE","l");
    legend[canvasCounter]->AddEntry(hVertexPosY[1], "NEUT","l");
    legend[canvasCounter]->SetTextSize(0.04);
    legend[canvasCounter]->Draw();

    gPad->Modified();
    Canvas[canvasCounter]->Print( Form("%sVertexPosY.pdf", DirectoryPlots.Data() ) ); 
    delete Canvas[canvasCounter];
    canvasCounter++;
    
    Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
    
    int binowaniePosZ=hVertexPosZ[0]->GetNbinsX();
    long double normalizacjaPosZ[NumberOfFiles];  
    
    for(int i=0; i<NumberOfFiles; i++)
    {
        for(int ib=0;ib<=binowaniePosZ;ib++)
        {
                normalizacjaPosZ[i]+=hVertexPosZ[i]->GetBinContent(ib);
        }
        hVertexPosZ[i]->Scale(norma/normalizacjaPosX[i]);
    }
            
    hVertexPosZ[0]->SetLineColorAlpha(kBlue, 1);
    hVertexPosZ[0]->SetLineWidth(1.5);
    
    hVertexPosZ[1]->SetLineColorAlpha(kRed, 1);
    hVertexPosZ[1]->SetLineWidth(1.5);

    hVertexPosZ[0]->Draw("");
    hVertexPosZ[1]->Draw("SAME");

    legend[canvasCounter] = new TLegend(0.55,0.2,0.9,0.4);
    legend[canvasCounter]->AddEntry(hVertexPosZ[0], "GENIE","l");
    legend[canvasCounter]->AddEntry(hVertexPosZ[1], "NEUT","l");
    legend[canvasCounter]->SetTextSize(0.04);
    legend[canvasCounter]->Draw();

    gPad->Modified();
    Canvas[canvasCounter]->Print( Form("%sVertexPosZ.pdf", DirectoryPlots.Data() ) ); 
    delete Canvas[canvasCounter];
    canvasCounter++;
    */
    /*
    Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
    
    norm = 1/hEnergyPeVsRange[2][0]->Integral();
    hEnergyPeVsRange[2][0]->Scale(norm);
    norm = 1/hEnergyPeVsRange[2][1]->Integral();
    hEnergyPeVsRange[2][1]->Scale(norm);
        
    hEnergyPeVsRange[2][1]->Add(hEnergyPeVsRange[2][0],-1);
    hEnergyPeVsRange[2][1]->GetYaxis()->SetRangeUser(0, 50);
    hEnergyPeVsRange[2][1]->GetXaxis()->SetRangeUser(0, 300.);
    //hEnergyPeVsRange[2][1]->GetZaxis()->SetRangeUser(-0.15, 0.04.);
    
    hEnergyPeVsRange[2][1]->Draw("COLZ");
    
    //gPad->SetLogz();
    gPad->Modified();
    Canvas[canvasCounter]->Print(Form("%sEnergyPeVsRange_NGsub.pdf",DirectoryPlots.Data() )); 
    delete Canvas[canvasCounter];
    canvasCounter++;
    */
    
    
    /*
    double normalizationFactorProton= (hprotonMomentum[1]->GetEntries() )*(h_nuMom[0]->GetEntries() )/h_nuMom[1]->GetEntries();
    
    Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
    
    int binowaniePrMom=hprotonMomentum[0]->GetNbinsX();
    long double normalizacjaPrMom;  
    
    for(int ib=0;ib<=binowaniePrMom;ib++)
    {
            normalizacjaPrMom+=hprotonMomentum[1]->GetBinContent(ib);
    }
    hprotonMomentum[1]->Scale(normalizationFactorProton/normalizacjaPrMom);
            
    hprotonMomentum[0]->SetLineColorAlpha(kBlue, 1);
    hprotonMomentum[0]->SetLineWidth(1.5);
    
    hprotonMomentum[1]->SetLineColorAlpha(kRed, 1);
    hprotonMomentum[1]->SetLineWidth(1.5);

    hprotonMomentum[1]->Draw("");
    hprotonMomentum[0]->Draw("SAME");

    legend[canvasCounter] = new TLegend(0.55,0.65,0.9,0.9);
    legend[canvasCounter]->AddEntry(hprotonMomentum[0], "GENIE","l");
    legend[canvasCounter]->AddEntry(hprotonMomentum[1], "NEUT","l");
    legend[canvasCounter]->SetTextSize(0.04);
    legend[canvasCounter]->Draw();

    gPad->Modified();
    Canvas[canvasCounter]->Print( Form("%sProtonMomNGnewNormalization.pdf", DirectoryPlots.Data() ) ); 
    delete Canvas[canvasCounter];
    canvasCounter++;
     */
    
    
    int binowanieselVA[SelectionNumber][5]={};
    long double normalizacjaselVA[SelectionNumber][5][NumberOfFiles];
    for(int ik=1; ik<2; ik++)
    {
        for(int ic=0; ic<SelectionNumber; ic++)
        {
            Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
            
            binowanieselVA[ic][ik]=hVertexActivitySelections[ic][ik][0]->GetNbinsX();
            for(int i=0; i<NumberOfFiles; i++)
            {
                for(int ib=0;ib<=binowanieselVA[ic][ik];ib++)
                {
                        normalizacjaselVA[ic][ik][i]+= hVertexActivitySelections[ic][ik][i]->GetBinContent(ib);
                }
                hVertexActivitySelections[ic][ik][i]->Scale(norma/normalizacjaselVA[ic][ik][i]);
                //hVertexActivity[ik][i]->Scale(100/hVertexActivity[ik][i]->Integral("width"));
            }
        
            hVertexActivitySelections[ic][ik][0]->SetLineColorAlpha(kBlue, 1);
            hVertexActivitySelections[ic][ik][0]->SetLineWidth(1.5);
            
            hVertexActivitySelections[ic][ik][1]->SetLineColorAlpha(kRed, 1);
            hVertexActivitySelections[ic][ik][1]->SetLineWidth(1.5);
        
            hVertexActivitySelections[ic][ik][0]->Draw("");
            hVertexActivitySelections[ic][ik][1]->Draw("SAME");
        
            legend[canvasCounter] = new TLegend(0.55,0.65,0.9,0.9);
            legend[canvasCounter]->AddEntry(hVertexActivitySelections[ic][ik][0], Form( "VA%s_GENIE", VetrexString[ik].Data() ),"l");
            legend[canvasCounter]->AddEntry(hVertexActivitySelections[ic][ik][1], Form( "VA%s_NEUT", VetrexString[ik].Data() ),"l");
            legend[canvasCounter]->SetTextSize(0.04);
            legend[canvasCounter]->Draw();
        
            gPad->Modified();
            Canvas[canvasCounter]->Print( Form("%sVA%s_%s_NG.pdf", DirectoryPlots.Data(), VetrexString[ik].Data(), SelectionsName[ic].Data() ) ); 
            delete Canvas[canvasCounter];
            canvasCounter++;
        }
    }
    
   
    
}
