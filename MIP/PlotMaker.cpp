#include <TH2F.h>
#include <fstream>
#include <iostream>
#include "TStyle.h"
#include "TCutG.h"

void PlotMaker()
{
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(111);
    gStyle->SetPalette(1,0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetOptStat(0);
    
    char filename[200];
    sprintf(filename,"/Users/kolos/Desktop/Studia/CIS/Crosstalk/MIP/Data/1September_18_MCR0_hadrons_2Gev_0pt2T_4trigg_0deg___MuonCrosstalk.root");
    TFile *file = new TFile(filename,"READ");
    if ( file->IsOpen() )
    {
        printf("File opened successfully\n");
    }  
    
    file->cd();
    
    TH1F* CrosstalkEnergyDepositLeftX = (TH1F*) file->Get("CrosstalkEnergyDepositLeftX");
    CrosstalkEnergyDepositLeftX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositRightX = (TH1F*) file->Get("CrosstalkEnergyDepositRightX");
    CrosstalkEnergyDepositRightX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositLeftY = (TH1F*) file->Get("CrosstalkEnergyDepositLeftY");
    CrosstalkEnergyDepositLeftY->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositRightY = (TH1F*) file->Get("CrosstalkEnergyDepositRightY");
    CrosstalkEnergyDepositRightY->GetYaxis()->SetTitleOffset(1.4);


////////////////////////////////
    CrosstalkEnergyDepositLeftX->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositLeftX->GetXaxis()->SetTitleSize(0.04);
    CrosstalkEnergyDepositLeftX->GetYaxis()->SetTitleSize(0.04);
    
    CrosstalkEnergyDepositRightX->GetYaxis()->SetTitleOffset(1.3);
    CrosstalkEnergyDepositRightX->GetXaxis()->SetTitleSize(0.04);
    CrosstalkEnergyDepositRightX->GetYaxis()->SetTitleSize(0.04);
    
    CrosstalkEnergyDepositLeftX->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositLeftX->SetLineWidth(1.5);
    CrosstalkEnergyDepositRightX->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyDepositRightX->SetLineWidth(1.5);
    
    TCanvas *Canvas = new TCanvas("Canvas","Canvas", 1400, 1000);
    
    CrosstalkEnergyDepositLeftX->Draw("");
    CrosstalkEnergyDepositRightX->Draw("SAME");
        
    TLegend *legend1 = new TLegend(0.65,0.6,1.0,0.9);
    legend1->AddEntry(CrosstalkEnergyDepositLeftX,"Crosstalk on the left","l");
    legend1->AddEntry(CrosstalkEnergyDepositRightX,"Crosstalk on the right","l");
    legend1->SetTextSize(0.03);
    legend1->Draw();
    
    gPad->Modified();
    Canvas->Print("/Users/kolos/Desktop/Studia/CIS/Crosstalk/MIP/Output/CrosstalkDistributionX.pdf");
    delete Canvas;
    delete legend1;
////////////////////////////////    
     CrosstalkEnergyDepositLeftY->GetYaxis()->SetTitleOffset(1.3);
    CrosstalkEnergyDepositLeftY->GetXaxis()->SetTitleSize(0.04);
    CrosstalkEnergyDepositLeftY->GetYaxis()->SetTitleSize(0.04);
    
    CrosstalkEnergyDepositRightY->GetYaxis()->SetTitleOffset(1.3);
    CrosstalkEnergyDepositRightY->GetXaxis()->SetTitleSize(0.04);
    CrosstalkEnergyDepositRightY->GetYaxis()->SetTitleSize(0.04);
    
    CrosstalkEnergyDepositLeftY->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositLeftY->SetLineWidth(1.5);
    CrosstalkEnergyDepositRightY->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyDepositRightY->SetLineWidth(1.5);
    
    TCanvas *Canvas2 = new TCanvas("Canvas2","Canvas2", 1400, 1000);
    
    CrosstalkEnergyDepositLeftY->Draw("");
    CrosstalkEnergyDepositRightY->Draw("SAME");
        
    TLegend *legend2 = new TLegend(0.65,0.6,1.0,0.9);
    legend2->AddEntry(CrosstalkEnergyDepositLeftY,"Crosstalk on the left","l");
    legend2->AddEntry(CrosstalkEnergyDepositRightY,"Crosstalk on the right","l");
    legend2->SetTextSize(0.03);
    legend2->Draw();
    
    gPad->Modified();
    Canvas2->Print("/Users/kolos/Desktop/Studia/CIS/Crosstalk/MIP/Output/CrosstalkDistributionY.pdf");
    delete Canvas2;
    delete legend2;
    
}
