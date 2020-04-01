#include <TH1.h>
#include <TH2F.h>
#include <fstream>
#include <iostream>
#include "TStyle.h"
#include <TColor.h>

void DynamicComparisonPlot()
{
// -- WhichStyle --
    // 1 = presentation large fonts
    // 2 = presentation small fonts
    // 3 = publication/paper
    Int_t WhichStyle = 1;
    
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
    
    TString Directory="/Users/kolos/Desktop/sFGD/Output/";
    TString DirectoryPlots="/Users/kolos/Desktop/sFGD/Plots/GENIE/Dynamic/";
    //TString Directory="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/Output/";
    //TString DirectoryPlots="/mnt/home/kskwarczynski/t2k-nd280-upgrade/sfgd_framework/analysis/PlotOutput/VertexActivity/GENIE/";
    
    TString FileName="DynamicVertexAcivity_Output";
    TString VertexName[5]={"VertexActivity1x1x1", "VertexActivity3x3x3", "VertexActivity5x5x5", "VertexActivity7x7x7", "VertexActivity9x9x9"};
    TString StringBox[3]={"Downstream", "Transverse", "Upstream"};
    TString ParticleName[3]={"Muon", "Pion+", "Proton"};
    TString VetrexString[5]={"1x1x1" , "3x3x3" , "5x5x5", "7x7x7", "9x9x9"};
    TString TrackLenght[2]={"Short", "Long"};
    int LongOrShort = 1; //Set if you are interested in subtracting long and short [0] or just long [1]
    
    TFile *file;
    TH1F *hVertexActivityDynamicCategory[3][5];
    TH1F *hVertexActivityDynamicCategoryShell[3][4]; //[vertexboxShape][vertexBox]
        
    TH1F *hVertexActivitySubTrackLengtAllCondition[3][2][5];
    TH1F *hVertexActivityOnlyIfTrackLenghtAll[3][2][5];

    TH1F *hVertexActivitySubTrackLengtAllConditionShell[3][2][4]; 
    TH1F *hVertexActivityOnlyIfTrackLenghtAllShell[3][2][4]; //[vertexboxShape][0-short, long][vertexBox]
    TH1F *hVertexActivityOnlyLongShell[3][4]; //[vertexBox-1]
    file = new TFile( Form("%s%s.root", Directory.Data() , FileName.Data()) ,"READ");
    if (file->IsOpen() )
    {
        printf("File opened successfully\n");
    }  
    
    TDirectory *FolderCut = (TDirectory*)file->Get("FolderCut"); 
    TDirectory *FolderSubtractedTrackLengthAll = (TDirectory*)file->Get("FolderSubtractedTrackLengthAll"); 
    TDirectory *FolderSubtractedTrackLengthAllShell = (TDirectory*)file->Get("FolderSubtractedTrackLengthAllShell"); 
    
    file->cd();
    for(int ik=0; ik<5; ik++)
    {
        for(int ib=0; ib<3; ib++) //loop over box shape
        {
            hVertexActivityDynamicCategory[ib][ik] = (TH1F*) file->Get( Form("Step%iDynamic_Cat%s", ik ,StringBox[ib].Data()) );
            hVertexActivityDynamicCategory[ib][ik]->GetYaxis()->SetTitleOffset(1.4);
            
            if(ik>0)
            {
                hVertexActivityDynamicCategoryShell[ib][ik-1] = (TH1F*) file->Get( Form("Step%iDynamic_Cat%s_Shell", ik ,StringBox[ib].Data()) );
                hVertexActivityDynamicCategoryShell[ib][ik-1]->GetYaxis()->SetTitleOffset(1.4);
                
                hVertexActivityOnlyLongShell[ib][ik-1] = (TH1F*) FolderSubtractedTrackLengthAllShell->Get( Form("Step%i_%s_Shell_OnlyLong",ik, StringBox[ib].Data()) );
                hVertexActivityOnlyLongShell[ib][ik-1]->GetYaxis()->SetTitleOffset(1.4);
            }
            for(int il=LongOrShort; il<2; il++) //loop over short or long track
            {
                hVertexActivitySubTrackLengtAllCondition[ib][il][ik] = (TH1F*) FolderSubtractedTrackLengthAll->Get( Form("Step%i_%s_SubCondition_%s_All", ik, StringBox[ib].Data(), TrackLenght[il].Data()) ); 
                hVertexActivitySubTrackLengtAllCondition[ib][il][ik]->GetYaxis()->SetTitleOffset(1.4);
               
                hVertexActivityOnlyIfTrackLenghtAll[ib][il][ik] = (TH1F*) FolderSubtractedTrackLengthAll->Get( Form("Step%i_%s_IfThereAre_%s_All", ik, StringBox[ib].Data(), TrackLenght[il].Data()) ); 
                hVertexActivityOnlyIfTrackLenghtAll[ib][il][ik]->GetYaxis()->SetTitleOffset(1.4);
                
                if(ik>0)
                {
                    hVertexActivitySubTrackLengtAllConditionShell[ib][il][ik-1] = (TH1F*) FolderSubtractedTrackLengthAllShell->Get( Form("Step%i_%s_SubCondition_%s_All_Shell", ik, StringBox[ib].Data(), TrackLenght[il].Data() ) ); 
                    hVertexActivitySubTrackLengtAllConditionShell[ib][il][ik-1]->GetYaxis()->SetTitleOffset(1.4);
               
                    hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][ik-1] = (TH1F*) FolderSubtractedTrackLengthAllShell->Get( Form("Step%i_%s_IfThereAre_%s_All_Shell", ik, StringBox[ib].Data(), TrackLenght[il].Data() ) ); 
                    hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][ik-1]->GetYaxis()->SetTitleOffset(1.4);
                }
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
            for(int il=LongOrShort; il<2; il++)
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
                Canvas[canvasCounter]->Print( Form("%sAll_%s_Subtracted_VA%s_%s.pdf", DirectoryPlots.Data(), StringBox[ib].Data(), VetrexString[ik].Data(), TrackLenght[il].Data()) ); 
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
                
            hVertexActivitySubTrackLengtAllCondition[0][il][ik]->SetLineColorAlpha(kRed, 1);
            hVertexActivitySubTrackLengtAllCondition[0][il][ik]->SetLineWidth(1.5);
            
            hVertexActivitySubTrackLengtAllCondition[2][il][ik]->SetLineColorAlpha(kBlue, 1);
            hVertexActivitySubTrackLengtAllCondition[2][il][ik]->SetLineWidth(1.5);
                
            hVertexActivitySubTrackLengtAllCondition[0][il][ik]->Draw("");
            hVertexActivitySubTrackLengtAllCondition[2][il][ik]->Draw("SAME");
                
            legend[canvasCounter] = new TLegend(0.55,0.7,0.9,0.9);
            legend[canvasCounter]->AddEntry(hVertexActivitySubTrackLengtAllCondition[0][il][ik], Form( "VA_Downstream" ),"l");
            legend[canvasCounter]->AddEntry(hVertexActivitySubTrackLengtAllCondition[2][il][ik], Form( "VA_Upstream"),"l");
            legend[canvasCounter]->SetTextSize(0.04);
            legend[canvasCounter]->Draw();
            
            gPad->Modified();
            Canvas[canvasCounter]->Print( Form("%sStream_Comparison_Step%i_Sub%s.pdf", DirectoryPlots.Data(), ik, TrackLenght[il].Data()) ); 
            delete Canvas[canvasCounter];
            canvasCounter++;
        }
    }
    for(int ib=0; ib<3; ib++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
            
        hVertexActivityDynamicCategoryShell[ib][0]->SetLineColorAlpha(kBlue, 1);
        hVertexActivityDynamicCategoryShell[ib][0]->SetLineWidth(1.5);
                
        hVertexActivityDynamicCategoryShell[ib][1]->SetLineColorAlpha(kRed, 1);
        hVertexActivityDynamicCategoryShell[ib][1]->SetLineWidth(1.5);
    
        hVertexActivityDynamicCategoryShell[ib][2]->SetLineColorAlpha(kGreen, 1);
        hVertexActivityDynamicCategoryShell[ib][2]->SetLineWidth(1.5);
    
        hVertexActivityDynamicCategoryShell[ib][3]->SetLineColorAlpha(kMagenta, 1);
        hVertexActivityDynamicCategoryShell[ib][3]->SetLineWidth(1.5);
                    
        hVertexActivityDynamicCategoryShell[ib][3]->GetXaxis()->SetTitle( "Energy deposit in step box [p.e.]" );
        
        hVertexActivityDynamicCategoryShell[ib][3]->Draw("");
        hVertexActivityDynamicCategoryShell[ib][1]->Draw("SAME");
        hVertexActivityDynamicCategoryShell[ib][2]->Draw("SAME");
        hVertexActivityDynamicCategoryShell[ib][0]->Draw("SAME");
      
        legend[canvasCounter] = new TLegend(0.60,0.7,0.9,0.9);
        legend[canvasCounter]->AddEntry(hVertexActivityDynamicCategoryShell[ib][0], Form("VA%s_Shell", VetrexString[1].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivityDynamicCategoryShell[ib][1], Form("VA%s_Shell", VetrexString[2].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivityDynamicCategoryShell[ib][2], Form("VA%s_Shell", VetrexString[3].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivityDynamicCategoryShell[ib][3], Form("VA%s_Shell", VetrexString[4].Data() ),"l");
        legend[canvasCounter]->SetTextSize(0.04);
        legend[canvasCounter]->Draw();
        
        gPad->Modified();
        Canvas[canvasCounter]->Print( Form("%sShellComparisonNormal_%s.pdf", DirectoryPlots.Data(), StringBox[ib].Data() ) ); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
    for(int il=LongOrShort; il<2; il++)
    {
        for(int ib=0; ib<3; ib++)
        {
            Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
                
            hVertexActivitySubTrackLengtAllConditionShell[ib][il][0]->SetLineColorAlpha(kBlue, 1);
            hVertexActivitySubTrackLengtAllConditionShell[ib][il][0]->SetLineWidth(1.5);
                    
            hVertexActivitySubTrackLengtAllConditionShell[ib][il][1]->SetLineColorAlpha(kRed, 1);
            hVertexActivitySubTrackLengtAllConditionShell[ib][il][1]->SetLineWidth(1.5);
          
            hVertexActivitySubTrackLengtAllConditionShell[ib][il][2]->SetLineColorAlpha(kGreen, 1);
            hVertexActivitySubTrackLengtAllConditionShell[ib][il][2]->SetLineWidth(1.5);
        
            hVertexActivitySubTrackLengtAllConditionShell[ib][il][3]->SetLineColorAlpha(kMagenta, 1);
            hVertexActivitySubTrackLengtAllConditionShell[ib][il][3]->SetLineWidth(1.5);
        
            hVertexActivitySubTrackLengtAllConditionShell[ib][il][1]->GetXaxis()->SetTitle( "Energy deposit in step box [p.e.]" );

            hVertexActivitySubTrackLengtAllConditionShell[ib][il][1]->Draw("");
            hVertexActivitySubTrackLengtAllConditionShell[ib][il][2]->Draw("SAME");
            hVertexActivitySubTrackLengtAllConditionShell[ib][il][3]->Draw("SAME");
            hVertexActivitySubTrackLengtAllConditionShell[ib][il][0]->Draw("SAME");
          
            legend[canvasCounter] = new TLegend(0.60,0.7,0.9,0.9);
            legend[canvasCounter]->AddEntry(hVertexActivitySubTrackLengtAllConditionShell[ib][il][0], Form("VA%s_Shell", VetrexString[1].Data() ),"l");
            legend[canvasCounter]->AddEntry(hVertexActivitySubTrackLengtAllConditionShell[ib][il][1], Form("VA%s_Shell", VetrexString[2].Data() ),"l");
            legend[canvasCounter]->AddEntry(hVertexActivitySubTrackLengtAllConditionShell[ib][il][2], Form("VA%s_Shell", VetrexString[3].Data() ),"l");
            legend[canvasCounter]->AddEntry(hVertexActivitySubTrackLengtAllConditionShell[ib][il][3], Form("VA%s_Shell", VetrexString[4].Data() ),"l");
            legend[canvasCounter]->SetTextSize(0.04);
            legend[canvasCounter]->Draw();
            
            gPad->Modified();
            Canvas[canvasCounter]->Print( Form("%sAll_Subtracted_%s_%s_Shell.pdf", DirectoryPlots.Data(), TrackLenght[il].Data(), StringBox[ib].Data() ) ); 
            delete Canvas[canvasCounter];
            canvasCounter++;
        }
    }
    for(int il=LongOrShort; il<2; il++)
    {  
        for(int ib=0; ib<3; ib++)
        {
            Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
                
            hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][0]->SetLineColorAlpha(kBlue, 1);
            hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][0]->SetLineWidth(1.5);
                
            hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][1]->SetLineColorAlpha(kRed, 1);
            hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][1]->SetLineWidth(1.5);
          
            hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][2]->SetLineColorAlpha(kGreen, 1);
            hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][2]->SetLineWidth(1.5);
        
            hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][3]->SetLineColorAlpha(kMagenta, 1);
            hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][3]->SetLineWidth(1.5);
        
            hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][3]->GetXaxis()->SetTitle( "Energy deposit in step box [p.e.]" );
            
            hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][3]->Draw("");
            hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][1]->Draw("SAME");
            hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][2]->Draw("SAME");
            hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][0]->Draw("SAME");
            
            legend[canvasCounter] = new TLegend(0.60,0.7,0.9,0.9);
            legend[canvasCounter]->AddEntry(hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][0], Form("VA%s_Shell", VetrexString[1].Data() ),"l");
            legend[canvasCounter]->AddEntry(hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][1], Form("VA%s_Shell", VetrexString[2].Data() ),"l");
            legend[canvasCounter]->AddEntry(hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][2], Form("VA%s_Shell", VetrexString[3].Data() ),"l");
            legend[canvasCounter]->AddEntry(hVertexActivityOnlyIfTrackLenghtAllShell[ib][il][3], Form("VA%s_Shell", VetrexString[4].Data() ),"l");
            legend[canvasCounter]->SetTextSize(0.04);
            legend[canvasCounter]->Draw();
            
            gPad->Modified();
            Canvas[canvasCounter]->Print( Form("%sAll_Not_Subtracted_%s_%s_Shell.pdf", DirectoryPlots.Data(), TrackLenght[il].Data(), StringBox[ib].Data()) ); 
            delete Canvas[canvasCounter];
            canvasCounter++;
        }
    }
    for(int ib=0; ib<3; ib++)
    {
        Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 1400, 1000);
        hVertexActivityOnlyLongShell[ib][0]->SetLineColorAlpha(kBlue, 1);
        hVertexActivityOnlyLongShell[ib][0]->SetLineWidth(1.5);
                
        hVertexActivityOnlyLongShell[ib][1]->SetLineColorAlpha(kRed, 1);
        hVertexActivityOnlyLongShell[ib][1]->SetLineWidth(1.5);
    
        hVertexActivityOnlyLongShell[ib][2]->SetLineColorAlpha(kGreen, 1);
        hVertexActivityOnlyLongShell[ib][2]->SetLineWidth(1.5);
    
        hVertexActivityOnlyLongShell[ib][3]->SetLineColorAlpha(kMagenta, 1);
        hVertexActivityOnlyLongShell[ib][3]->SetLineWidth(1.5);
                
        hVertexActivityOnlyLongShell[ib][3]->GetXaxis()->SetTitle( "Energy deposit in step box [p.e.]" );
        
        hVertexActivityOnlyLongShell[ib][3]->Draw("");
        hVertexActivityOnlyLongShell[ib][1]->Draw("SAME");
        hVertexActivityOnlyLongShell[ib][2]->Draw("SAME");
        hVertexActivityOnlyLongShell[ib][0]->Draw("SAME");
    
        legend[canvasCounter] = new TLegend(0.60,0.7,0.9,0.9);
        legend[canvasCounter]->AddEntry(hVertexActivityOnlyLongShell[ib][0], Form("VA%s_Shell", VetrexString[1].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivityOnlyLongShell[ib][1], Form("VA%s_Shell", VetrexString[2].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivityOnlyLongShell[ib][2], Form("VA%s_Shell", VetrexString[3].Data() ),"l");
        legend[canvasCounter]->AddEntry(hVertexActivityOnlyLongShell[ib][3], Form("VA%s_Shell", VetrexString[4].Data() ),"l");
        legend[canvasCounter]->SetTextSize(0.04);
        legend[canvasCounter]->Draw();
    
        gPad->Modified();
        cout<<Form("%sShellComparisonOnlyLong.pdf", DirectoryPlots.Data() )<<endl;
        Canvas[canvasCounter]->Print( Form("%sShellComparisonOnlyLong_%s.pdf", DirectoryPlots.Data(), StringBox[ib].Data() ) ); 
        delete Canvas[canvasCounter];
        canvasCounter++;
    }
}
