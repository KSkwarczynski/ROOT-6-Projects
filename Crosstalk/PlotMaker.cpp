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
    
    char filename[200];
    sprintf(filename,"/Users/kolos/Desktop/Studia/CIS/Data/27August_1_MCR0_hadrons_0pt8Gev_0pt0T_Beam___Crosstalk.root");
    TFile *file = new TFile(filename,"READ");
    file->IsOpen();
    
    file->cd();
    
    TH2F* EnergyTrigTimeX = (TH2F*) file->Get("EnergyTrigTimeX");
    EnergyTrigTimeX->GetYaxis()->SetTitleOffset(1.4);
    TH2F* EnergyTrigTimeY = (TH2F*) file->Get("EnergyTrigTimeY");
    EnergyTrigTimeY->GetYaxis()->SetTitleOffset(1.4);
    TH2F* EnergyTrigTimeCrosstalkX = (TH2F*) file->Get("EnergyTrigTimeCrosstalkX");
    EnergyTrigTimeCrosstalkX->GetYaxis()->SetTitleOffset(1.4);
    TH2F* EnergyTrigTimeCrosstalkY = (TH2F*) file->Get("EnergyTrigTimeCrosstalkY");
    EnergyTrigTimeCrosstalkY->GetYaxis()->SetTitleOffset(1.4);
    TH2F* EnergyTrigTimeSignalX = (TH2F*) file->Get("EnergyTrigTimeSignalX");
    EnergyTrigTimeSignalX->GetYaxis()->SetTitleOffset(1.4);
    TH2F* EnergyTrigTimeSignalY = (TH2F*) file->Get("EnergyTrigTimeSignalY");
    EnergyTrigTimeSignalY->GetYaxis()->SetTitleOffset(1.4);
    
    TH2F* EnergyTrigTimeTestX = (TH2F*) file->Get("EnergyTrigTimeTestX");
    EnergyTrigTimeTestX->GetYaxis()->SetTitleOffset(1.4);
    TH2F* EnergyTrigTimeTestY = (TH2F*) file->Get("EnergyTrigTimeTestY");
    EnergyTrigTimeTestY->GetYaxis()->SetTitleOffset(1.4);
    TH2F* EnergyTrigTimeTestUpgradeX = (TH2F*) file->Get("EnergyTrigTimeTestUpgradeX");
    EnergyTrigTimeTestUpgradeX->GetYaxis()->SetTitleOffset(1.4);
    TH2F* EnergyTrigTimeTestUpgradeY = (TH2F*) file->Get("EnergyTrigTimeTestUpgradeY");
    EnergyTrigTimeTestUpgradeY->GetYaxis()->SetTitleOffset(1.4);
    TH2F* EnergyTrigTimeTestLowX = (TH2F*) file->Get("EnergyTrigTimeTestLowX");
    EnergyTrigTimeTestLowX->GetYaxis()->SetTitleOffset(1.4);
    TH2F* EnergyTrigTimeTestLowY = (TH2F*) file->Get("EnergyTrigTimeTestLowY");
    EnergyTrigTimeTestLowY->GetYaxis()->SetTitleOffset(1.4);

    TH1F* CrosstalkEnergyDepositX = (TH1F*) file->Get("CrosstalkEnergyDepositX");
    CrosstalkEnergyDepositX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositY = (TH1F*) file->Get("CrosstalkEnergyDepositY");
    CrosstalkEnergyDepositY->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositMinus1X = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1X");
    CrosstalkEnergyDepositMinus1X->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositMinus1Y = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1Y");
    CrosstalkEnergyDepositMinus1Y->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositMiddleX = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleX");
    CrosstalkEnergyDepositMiddleX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositMiddleY = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleY");
    CrosstalkEnergyDepositMiddleY->GetYaxis()->SetTitleOffset(1.4);
    
    TH1F* HistogramRealPeakEnergyDeposit = (TH1F*) file->Get("HistogramRealPeakEnergyDeposit");
    HistogramRealPeakEnergyDeposit->GetYaxis()->SetTitleOffset(1.4);
    TH1F* HistogramRealPeakEnergyDepositMinus1 = (TH1F*) file->Get("HistogramRealPeakEnergyDepositMinus1");
    HistogramRealPeakEnergyDepositMinus1->GetYaxis()->SetTitleOffset(1.4);
    TH1F* HistogramRealPeakEnergyDepositMiddle = (TH1F*) file->Get("HistogramRealPeakEnergyDepositMiddle");
    HistogramRealPeakEnergyDepositMiddle->GetYaxis()->SetTitleOffset(1.4);
    
    TH1F* CrosstalkEnergyDepositPercentageX = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageX");
    CrosstalkEnergyDepositPercentageX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositPercentageY = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageY");
    CrosstalkEnergyDepositPercentageY->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyPercentageMinus1X = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1X");
    CrosstalkEnergyPercentageMinus1X->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyPercentageMinus1Y = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1Y");
    CrosstalkEnergyPercentageMinus1Y->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyPercentageMiddleX = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleX");
    CrosstalkEnergyPercentageMiddleX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyPercentageMiddleY = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleY");
    CrosstalkEnergyPercentageMiddleY->GetYaxis()->SetTitleOffset(1.4);
    
    TH1F* CrosstalkEnergyDepositCUTGX = (TH1F*) file->Get("CrosstalkEnergyDepositCUTGX");
    CrosstalkEnergyDepositCUTGX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositCUTGY = (TH1F*) file->Get("CrosstalkEnergyDepositCUTGY");
    CrosstalkEnergyDepositCUTGY->GetYaxis()->SetTitleOffset(1.4);
    TH2F* EnergyTrigTimeCUTGX = (TH2F*) file->Get("EnergyTrigTimeCUTGX");
    EnergyTrigTimeCUTGX->GetYaxis()->SetTitleOffset(1.4);
    TH2F* EnergyTrigTimeCUTGY = (TH2F*) file->Get("EnergyTrigTimeCUTGY");
    EnergyTrigTimeCUTGY->GetYaxis()->SetTitleOffset(1.4);
    
    TH1F* HistogramCrosstalkDistanceX = (TH1F*) file->Get("HistogramCrosstalkDistanceX");
    HistogramCrosstalkDistanceX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* HistogramCrosstalkDistanceY = (TH1F*) file->Get("HistogramCrosstalkDistanceY");
    HistogramCrosstalkDistanceY->GetYaxis()->SetTitleOffset(1.4);
    TH1F* HistogramCrosstalkDistanceCUTGX = (TH1F*) file->Get("HistogramCrosstalkDistanceCUTGX");
    HistogramCrosstalkDistanceCUTGX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* HistogramCrosstalkDistanceCUTGY = (TH1F*) file->Get("HistogramCrosstalkDistanceCUTGY");
    HistogramCrosstalkDistanceCUTGY->GetYaxis()->SetTitleOffset(1.4);
    
    TH1F* HistogramCrosstalkDistanceMinus1X = (TH1F*) file->Get("HistogramCrosstalkDistanceMinus1X");
    HistogramCrosstalkDistanceMinus1X->GetYaxis()->SetTitleOffset(1.4);
    TH1F* HistogramCrosstalkDistanceMinus1Y = (TH1F*) file->Get("HistogramCrosstalkDistanceMinus1Y");
    HistogramCrosstalkDistanceMinus1Y->GetYaxis()->SetTitleOffset(1.4);
    TH1F* HistogramCrosstalkDistanceMiddleX = (TH1F*) file->Get("HistogramCrosstalkDistanceMiddleX");
    HistogramCrosstalkDistanceMiddleX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* HistogramCrosstalkDistanceMiddleY = (TH1F*) file->Get("HistogramCrosstalkDistanceMiddleY");
    HistogramCrosstalkDistanceMiddleY->GetYaxis()->SetTitleOffset(1.4);
    
    TH1F* EnergyTrigTimeMinus1X = (TH1F*) file->Get("EnergyTrigTimeMinus1X");
    EnergyTrigTimeMinus1X->GetYaxis()->SetTitleOffset(1.4);
    TH1F* EnergyTrigTimeMinus1Y = (TH1F*) file->Get("EnergyTrigTimeMinus1Y");
    EnergyTrigTimeMinus1Y->GetYaxis()->SetTitleOffset(1.4);
    TH1F* EnergyTrigTimeMiddleX = (TH1F*) file->Get("EnergyTrigTimeMiddleX");
    EnergyTrigTimeMiddleX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* EnergyTrigTimeMiddleY = (TH1F*) file->Get("EnergyTrigTimeMiddleY");
    EnergyTrigTimeMiddleY->GetYaxis()->SetTitleOffset(1.4);
    
    TH1F* HistogramCrosstalkDistanceTypeX = (TH1F*) file->Get("HistogramCrosstalkDistanceTypeX");
    HistogramCrosstalkDistanceTypeX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* HistogramCrosstalkDistanceTypeY = (TH1F*) file->Get("HistogramCrosstalkDistanceTypeY");
    HistogramCrosstalkDistanceTypeY->GetYaxis()->SetTitleOffset(1.4);
    TH1F* HistogramCrosstalkDistanceTypeMinus1X = (TH1F*) file->Get("HistogramCrosstalkDistanceTypeMinus1X");
    HistogramCrosstalkDistanceTypeMinus1X->GetYaxis()->SetTitleOffset(1.4);
    TH1F* HistogramCrosstalkDistanceTypeMinus1Y = (TH1F*) file->Get("HistogramCrosstalkDistanceTypeMinus1Y");
    HistogramCrosstalkDistanceTypeMinus1Y->GetYaxis()->SetTitleOffset(1.4);
    TH1F* HistogramCrosstalkDistanceTypeMiddleX = (TH1F*) file->Get("HistogramCrosstalkDistanceTypeMiddleX");
    HistogramCrosstalkDistanceTypeMiddleX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* HistogramCrosstalkDistanceTypeMiddleY = (TH1F*) file->Get("HistogramCrosstalkDistanceTypeMiddleY");
    HistogramCrosstalkDistanceTypeMiddleY->GetYaxis()->SetTitleOffset(1.4);
    
    TH1F* CrosstalkEnergyDepositMinus1CUTGX = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1CUTGX");
    CrosstalkEnergyDepositMinus1CUTGX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositMinus1CUTGY = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1CUTGY");
    CrosstalkEnergyDepositMinus1CUTGY->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositMiddleCUTGX = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleCUTGX");
    CrosstalkEnergyDepositMiddleCUTGX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositMiddleCUTGY = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleCUTGY");
    CrosstalkEnergyDepositMiddleCUTGY->GetYaxis()->SetTitleOffset(1.4);
    
    TH1F* HistogramCrosstalkDistanceMinus1CUTGX = (TH1F*) file->Get("HistogramCrosstalkDistanceMinus1CUTGX");
    HistogramCrosstalkDistanceMinus1CUTGX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* HistogramCrosstalkDistanceMinus1CUTGY = (TH1F*) file->Get("HistogramCrosstalkDistanceMinus1CUTGY");
    HistogramCrosstalkDistanceMinus1CUTGY->GetYaxis()->SetTitleOffset(1.4);
    TH1F* HistogramCrosstalkDistanceMiddleCUTGX = (TH1F*) file->Get("HistogramCrosstalkDistanceMiddleCUTGX");
    HistogramCrosstalkDistanceMiddleCUTGX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* HistogramCrosstalkDistanceMiddleCUTGY = (TH1F*) file->Get("HistogramCrosstalkDistanceMiddleCUTGY");
    HistogramCrosstalkDistanceMiddleCUTGY->GetYaxis()->SetTitleOffset(1.4);
    
    TH1F* CrosstalkEnergyDepositPercentageCUTGX = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageCUTGX");
    CrosstalkEnergyDepositPercentageCUTGX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositPercentageCUTGY = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageCUTGY");
    CrosstalkEnergyDepositPercentageCUTGY->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyPercentageMinus1CUTGX = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1CUTGX");
    CrosstalkEnergyPercentageMinus1CUTGX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyPercentageMinus1CUTGY = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1CUTGY");
    CrosstalkEnergyPercentageMinus1CUTGY->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyPercentageMiddleCUTGX = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleCUTGX");
    CrosstalkEnergyPercentageMiddleCUTGX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyPercentageMiddleCUTGY = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleCUTGY");
    CrosstalkEnergyPercentageMiddleCUTGY->GetYaxis()->SetTitleOffset(1.4);
////////////////////////////////
    TCanvas *Canvas = new TCanvas("Canvas","Canvas", 1400, 1000);
    Canvas->Divide(3,2);
    Canvas->cd(1);
    EnergyTrigTimeX->Draw("COLZ");
    Canvas->cd(2);
    EnergyTrigTimeCrosstalkX->Draw("COLZ");
    Canvas->cd(3);
    EnergyTrigTimeSignalX->Draw("COLZ");
    Canvas->cd(4);
    EnergyTrigTimeY->Draw("COLZ");
    Canvas->cd(5);
    EnergyTrigTimeCrosstalkY->Draw("COLZ");
    Canvas->cd(6);
    EnergyTrigTimeSignalY->Draw("COLZ");
    
    Canvas->Print("/Users/kolos/Desktop/Studia/CIS/Output/TimeTriggerEnergy.pdf");
    delete Canvas;
////////////////////////////////
    TCanvas *Canvas2 = new TCanvas("Canvas2","Canvas2", 1400, 1000);
    Canvas2->Divide(3,2);
    
    Canvas2->cd(1);
    EnergyTrigTimeTestX->Draw("COLZ");
    Canvas2->cd(2);
    EnergyTrigTimeTestLowX->Draw("COLZ");
    Canvas2->cd(3);
    EnergyTrigTimeTestUpgradeX->Draw("COLZ");
    Canvas2->cd(4);
    EnergyTrigTimeTestY->Draw("COLZ");
    Canvas2->cd(5);
    EnergyTrigTimeTestLowY->Draw("COLZ");
    Canvas2->cd(6);
    EnergyTrigTimeTestUpgradeY->Draw("COLZ");
    
    Canvas2->Print("/Users/kolos/Desktop/Studia/CIS/Output/WierdPlot.pdf");    
    delete Canvas2;
////////////////////////////////
    TCanvas *Canvas3 = new TCanvas("Canvas3","Canvas3", 1400, 1000);
    gStyle->SetOptTitle(kFALSE);
    gStyle->SetOptStat(0);
    Canvas3->Divide(2,2);
        
    CrosstalkEnergyDepositX->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositX->SetLineWidth(1.5);
    CrosstalkEnergyDepositX->GetXaxis()->SetRangeUser(0., 100.);
    
    CrosstalkEnergyDepositMinus1X->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyDepositMinus1X->SetLineWidth(1.5);
    CrosstalkEnergyDepositMinus1X->GetXaxis()->SetRangeUser(0., 100.);
    
    CrosstalkEnergyDepositMiddleX->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyDepositMiddleX->SetLineWidth(1.5);
    CrosstalkEnergyDepositMiddleX->GetXaxis()->SetRangeUser(0., 100.);
    
    CrosstalkEnergyDepositY->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositY->SetLineWidth(1.5);
    CrosstalkEnergyDepositY->GetXaxis()->SetRangeUser(0., 100.);
    
    CrosstalkEnergyDepositMinus1Y->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyDepositMinus1Y->SetLineWidth(1.5);
    CrosstalkEnergyDepositMinus1Y->GetXaxis()->SetRangeUser(0., 100.);
    
    CrosstalkEnergyDepositMiddleY->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyDepositMiddleY->SetLineWidth(1.5);
    CrosstalkEnergyDepositMiddleY->GetXaxis()->SetRangeUser(0., 100.);
    
    HistogramRealPeakEnergyDeposit->SetLineColorAlpha(kRed, 1);
    HistogramRealPeakEnergyDeposit->SetLineWidth(1.5);
    
    HistogramRealPeakEnergyDepositMinus1->SetLineColorAlpha(kGreen, 1);
    HistogramRealPeakEnergyDepositMinus1->SetLineWidth(1.5);
    
    HistogramRealPeakEnergyDepositMiddle->SetLineColorAlpha(kBlue, 1);
    HistogramRealPeakEnergyDepositMiddle->SetLineWidth(1.5);
    
    Canvas3->cd(1);
    CrosstalkEnergyDepositX->Draw("");
    CrosstalkEnergyDepositMinus1X->Draw("SAME");
    CrosstalkEnergyDepositMiddleX->Draw("SAME");
    
    TLegend *legend1 = new TLegend(0.65,0.8,0.9,0.9);
    legend1->AddEntry(CrosstalkEnergyDepositX,"Stopping Point","l");
    legend1->AddEntry(CrosstalkEnergyDepositMinus1X,"One Cube Backward","l");
    legend1->AddEntry(CrosstalkEnergyDepositMiddleX,"Middle of Track","l");
    legend1->Draw();
    
    Canvas3->cd(2);
    CrosstalkEnergyDepositY->Draw("");
    CrosstalkEnergyDepositMinus1Y->Draw("SAME");
    CrosstalkEnergyDepositMiddleY->Draw("SAME");
    
    TLegend *legend2 = new TLegend(0.65,0.8,0.9,0.9);
    legend2->AddEntry(CrosstalkEnergyDepositY,"Stopping Point","l");
    legend2->AddEntry(CrosstalkEnergyDepositMinus1Y,"One Cube Backward","l");
    legend2->AddEntry(CrosstalkEnergyDepositMiddleY,"Middle of Track","l");
    legend2->Draw();
    
    Canvas3->cd(3);
    HistogramRealPeakEnergyDepositMiddle->Draw("");
    HistogramRealPeakEnergyDeposit->Draw("SAME");
    HistogramRealPeakEnergyDepositMinus1->Draw("SAME");

    
    TLegend *legend3 = new TLegend(0.65,0.8,0.9,0.9);
    legend3->AddEntry(HistogramRealPeakEnergyDeposit,"Stopping Point","l");
    legend3->AddEntry(HistogramRealPeakEnergyDepositMinus1,"One Cube Backward","l");
    legend3->AddEntry(HistogramRealPeakEnergyDepositMiddle,"Middle of Track","l");
    legend3->Draw();
    
    Canvas3->Print("/Users/kolos/Desktop/Studia/CIS/Output/CrosstalkComparison.pdf");
    delete Canvas3;
    ////////////////////////////////
    TCanvas *Canvas4 = new TCanvas("Canvas4","Canvas4", 1400, 1000);
    gStyle->SetOptTitle(kFALSE);
    gStyle->SetOptStat(0);
    Canvas4->Divide(2,2);
    
    CrosstalkEnergyDepositPercentageX->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositPercentageX->SetLineWidth(1.5);
    CrosstalkEnergyDepositPercentageX->GetXaxis()->SetRangeUser(0., 20.);
        
    CrosstalkEnergyDepositPercentageY->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositPercentageY->SetLineWidth(1.5);
    CrosstalkEnergyDepositPercentageY->GetXaxis()->SetRangeUser(0., 20.);
        
    CrosstalkEnergyPercentageMinus1X->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyPercentageMinus1X->SetLineWidth(1.5);
    CrosstalkEnergyPercentageMinus1X->GetXaxis()->SetRangeUser(0., 20.);
        
    CrosstalkEnergyPercentageMinus1Y->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyPercentageMinus1Y->SetLineWidth(1.5);
    CrosstalkEnergyPercentageMinus1Y->GetXaxis()->SetRangeUser(0., 20.);
        
    CrosstalkEnergyPercentageMiddleX->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyPercentageMiddleX->SetLineWidth(1.5);
    CrosstalkEnergyPercentageMiddleX->GetXaxis()->SetRangeUser(0., 20.);
        
    CrosstalkEnergyPercentageMiddleY->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyPercentageMiddleY->SetLineWidth(1.5);
    CrosstalkEnergyPercentageMiddleY->GetXaxis()->SetRangeUser(0., 20.);
    
    TH1F *CloneStoppingPercentageX = (TH1F*)(CrosstalkEnergyDepositPercentageX->Clone("CloneStoppingPercentageX"));
    TH1F *CloneMinus1ercentageX = (TH1F*)(CrosstalkEnergyPercentageMinus1X->Clone("CloneMinus1ercentageX"));
    TH1F *CloneMiddlercentageX = (TH1F*)(CrosstalkEnergyPercentageMiddleX->Clone("CloneMiddlercentageX"));
    TH1F *CloneStoppingPercentageY = (TH1F*)(CrosstalkEnergyDepositPercentageY->Clone("CloneStoppingPercentageY"));
    TH1F *CloneMinus1ercentageY = (TH1F*)(CrosstalkEnergyPercentageMinus1Y->Clone("CloneMinus1ercentageY"));
    TH1F *CloneMiddlercentageY = (TH1F*)(CrosstalkEnergyPercentageMiddleY->Clone("CloneMiddlercentageY"));
    
    long double normalizacja[6];
    for(int i=0;i<=5;i++)
    {
       normalizacja[i]=0;
    }
    int binowanie=CloneStoppingPercentageX->GetNbinsX();

    for(int i=1;i<=binowanie;i++)
    {
        normalizacja[0]+=CloneStoppingPercentageX->GetBinContent(i);
        normalizacja[1]+=CloneMinus1ercentageX->GetBinContent(i);
        normalizacja[2]+=CloneMiddlercentageX->GetBinContent(i);
        normalizacja[3]+=CloneStoppingPercentageY->GetBinContent(i);
        normalizacja[4]+=CloneMinus1ercentageY->GetBinContent(i);
        normalizacja[5]+=CloneMiddlercentageY->GetBinContent(i);
    }
    int norma=1000;
    CloneStoppingPercentageX->Scale(norma/normalizacja[0]);
    CloneMinus1ercentageX->Scale(norma/normalizacja[1]);
    CloneMiddlercentageX->Scale(norma/normalizacja[2]);
    CloneStoppingPercentageY->Scale(norma/normalizacja[3]);
    CloneMinus1ercentageY->Scale(norma/normalizacja[4]);
    CloneMiddlercentageY->Scale(norma/normalizacja[5]);
    
    Canvas4->cd(1);
    CrosstalkEnergyDepositPercentageX->Draw("");
    CrosstalkEnergyPercentageMiddleX->Draw("SAME");
    CrosstalkEnergyPercentageMinus1X->Draw("SAME");

    
    TLegend *legend11 = new TLegend(0.65,0.8,0.9,0.9);
    legend11->AddEntry(CrosstalkEnergyDepositPercentageX,"Stopping Point","l");
    legend11->AddEntry(CrosstalkEnergyPercentageMinus1X,"One Cube Backward","l");
    legend11->AddEntry(CrosstalkEnergyPercentageMiddleX,"Middle of Track","l");
    legend11->Draw();
    
    Canvas4->cd(2);
    CrosstalkEnergyDepositPercentageY->Draw("");
    CrosstalkEnergyPercentageMiddleY->Draw("SAME");
    CrosstalkEnergyPercentageMinus1Y->Draw("SAME");

    
    TLegend *legend12 = new TLegend(0.65,0.8,0.9,0.9);
    legend12->AddEntry(CrosstalkEnergyDepositPercentageY,"Stopping Point","l");
    legend12->AddEntry(CrosstalkEnergyPercentageMinus1Y,"One Cube Backward","l");
    legend12->AddEntry(CrosstalkEnergyPercentageMiddleY,"Middle of Track","l");
    legend12->Draw();
    
    Canvas4->cd(3);
    CloneMiddlercentageX->Draw("");
    CloneStoppingPercentageX->Draw("SAME");
    CloneMinus1ercentageX->Draw("SAME");
    
    
    TLegend *legend13 = new TLegend(0.65,0.8,0.9,0.9);
    legend13->AddEntry(CloneStoppingPercentageX,"Stopping Point","l");
    legend13->AddEntry(CloneMinus1ercentageX,"One Cube Backward","l");
    legend13->AddEntry(CloneMiddlercentageX,"Middle of Track","l");
    legend13->Draw();
    
    Canvas4->cd(4);
    CloneMiddlercentageY->Draw("");
    CloneStoppingPercentageY->Draw("SAME");
    CloneMinus1ercentageY->Draw("SAME");
   
    
    TLegend *legend14 = new TLegend(0.65,0.8,0.9,0.9);
    legend14->AddEntry(CloneStoppingPercentageY,"Stopping Point","l");
    legend14->AddEntry(CloneMinus1ercentageY,"One Cube Backward","l");
    legend14->AddEntry(CloneMiddlercentageY,"Middle of Track","l");
    legend14->Draw();
    
    Canvas4->Print("/Users/kolos/Desktop/Studia/CIS/Output/CrosstalkPercentageComparison.pdf");
    delete Canvas4;
    delete legend11; 
    delete legend12; 
    delete legend13; 
    delete legend14;
////////////////////////////////    
    TCanvas *Canvas5 = new TCanvas("Canvas5","Canvas5", 1400, 1000);
    Canvas5->Divide(2,2);
    
    Canvas5->cd(1);
    EnergyTrigTimeCUTGX->Draw("COLZ");
    Canvas5->cd(2);
    EnergyTrigTimeCUTGY->Draw("COLZ");
    Canvas5->cd(3);
    CrosstalkEnergyDepositCUTGX->Draw("HIST");
    Canvas5->cd(4);
    CrosstalkEnergyDepositCUTGY->Draw("HIST");
    
    Canvas5->Print("/Users/kolos/Desktop/Studia/CIS/Output/PlotsAfterCUTG.pdf");
    delete Canvas5;
////////////////////////////////    
    TCanvas *Canvas6 = new TCanvas("Canvas6","Canvas6", 1400, 1000);
    Canvas6->Divide(2,2);
    
    CrosstalkEnergyDepositX->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositX->SetLineWidth(1.5);
    CrosstalkEnergyDepositY->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositY->SetLineWidth(1.5);
    HistogramCrosstalkDistanceX->SetLineColorAlpha(kRed, 1);
    HistogramCrosstalkDistanceX->SetLineWidth(1.5);
    HistogramCrosstalkDistanceY->SetLineColorAlpha(kRed, 1);
    HistogramCrosstalkDistanceY->SetLineWidth(1.5);
    
    CrosstalkEnergyDepositCUTGX->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyDepositCUTGX->SetLineWidth(1.5);
    CrosstalkEnergyDepositCUTGY->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyDepositCUTGY->SetLineWidth(1.5);
    HistogramCrosstalkDistanceCUTGX->SetLineColorAlpha(kBlue, 1);
    HistogramCrosstalkDistanceCUTGX->SetLineWidth(1.5);
    HistogramCrosstalkDistanceCUTGY->SetLineColorAlpha(kBlue, 1);
    HistogramCrosstalkDistanceCUTGY->SetLineWidth(1.5);
    
    Canvas6->cd(1);
    CrosstalkEnergyDepositX->Draw("");
    CrosstalkEnergyDepositCUTGX->Draw("SAME");
    
    TLegend *legend21 = new TLegend(0.65,0.8,0.9,0.9);
    legend21->AddEntry(CrosstalkEnergyDepositX,"Before","l");
    legend21->AddEntry(CrosstalkEnergyDepositCUTGX,"After CUTG","l");
    legend21->Draw();
    
    Canvas6->cd(2);
    CrosstalkEnergyDepositY->Draw("");
    CrosstalkEnergyDepositCUTGY->Draw("SAME");
    
    TLegend *legend21 = new TLegend(0.65,0.8,0.9,0.9);
    legend21->AddEntry(CrosstalkEnergyDepositY,"Before","l");
    legend21->AddEntry(CrosstalkEnergyDepositCUTGY,"After CUTG","l");
    legend21->Draw();
    
    Canvas6->cd(3);
    HistogramCrosstalkDistanceX->Draw("");
    HistogramCrosstalkDistanceCUTGX->Draw("SAME");
    
    TLegend *legend21 = new TLegend(0.65,0.8,0.9,0.9);
    legend21->AddEntry(HistogramCrosstalkDistanceX,"Before","l");
    legend21->AddEntry(HistogramCrosstalkDistanceCUTGX,"After CUTG","l");
    legend21->Draw();
    
    Canvas6->cd(4);
    HistogramCrosstalkDistanceY->Draw("");
    HistogramCrosstalkDistanceCUTGY->Draw("SAME");
    
    TLegend *legend21 = new TLegend(0.65,0.8,0.9,0.9);
    legend21->AddEntry(HistogramCrosstalkDistanceY,"Before","l");
    legend21->AddEntry(HistogramCrosstalkDistanceCUTGY,"After CUTG","l");
    legend21->Draw();
    
    Canvas6->Print("/Users/kolos/Desktop/Studia/CIS/Output/CrosstalkComparisonAfterCUTG.pdf");

    delete Canvas6;
    TCanvas *Canvas7 = new TCanvas("Canvas7","Canvas7", 1400, 1000);
    Canvas7->Divide(2,1);
    
    for(int i=0;i<=5;i++)
    {
       normalizacja[i]=0;
    }
    int binowanie=HistogramCrosstalkDistanceX->GetNbinsX();
    for(int i=1;i<=binowanie;i++)
    {
        normalizacja[0]+=HistogramCrosstalkDistanceX->GetBinContent(i);
        normalizacja[1]+=HistogramCrosstalkDistanceMinus1X->GetBinContent(i);
        normalizacja[2]+=HistogramCrosstalkDistanceMiddleX->GetBinContent(i);
        normalizacja[3]+=HistogramCrosstalkDistanceY->GetBinContent(i);
        normalizacja[4]+=HistogramCrosstalkDistanceMinus1Y->GetBinContent(i);
        normalizacja[5]+=HistogramCrosstalkDistanceMiddleY->GetBinContent(i);
    }
    int norma=1000;
    HistogramCrosstalkDistanceX->Scale(norma/normalizacja[0]);
    HistogramCrosstalkDistanceMinus1X->Scale(norma/normalizacja[1]);
    HistogramCrosstalkDistanceMiddleX->Scale(norma/normalizacja[2]);
    HistogramCrosstalkDistanceY->Scale(norma/normalizacja[3]);
    HistogramCrosstalkDistanceMinus1Y->Scale(norma/normalizacja[4]);
    HistogramCrosstalkDistanceMiddleY->Scale(norma/normalizacja[5]);
    
    HistogramCrosstalkDistanceX->SetLineColorAlpha(kRed, 1);
    HistogramCrosstalkDistanceX->SetLineWidth(1.5);
    HistogramCrosstalkDistanceMinus1X->SetLineColorAlpha(kGreen, 1);
    HistogramCrosstalkDistanceMinus1X->SetLineWidth(1.5);
    HistogramCrosstalkDistanceMiddleX->SetLineColorAlpha(kBlue, 1);
    HistogramCrosstalkDistanceMiddleX->SetLineWidth(1.5);
    
    HistogramCrosstalkDistanceY->SetLineColorAlpha(kRed, 1);
    HistogramCrosstalkDistanceY->SetLineWidth(1.5);
    HistogramCrosstalkDistanceMinus1Y->SetLineColorAlpha(kGreen, 1);
    HistogramCrosstalkDistanceMinus1Y->SetLineWidth(1.5);
    HistogramCrosstalkDistanceMiddleY->SetLineColorAlpha(kBlue, 1);
    HistogramCrosstalkDistanceMiddleY->SetLineWidth(1.5);
    
    Canvas7->cd(1);
    HistogramCrosstalkDistanceMiddleX->Draw("");
    HistogramCrosstalkDistanceMinus1X->Draw("SAME");
    HistogramCrosstalkDistanceX->Draw("SAME");
        
    TLegend *legend31 = new TLegend(0.65,0.8,0.9,0.9);
    legend31->AddEntry(HistogramCrosstalkDistanceX,"Stopping Point","l");
    legend31->AddEntry(HistogramCrosstalkDistanceMinus1X,"One Cube Backward","l");
    legend31->AddEntry(HistogramCrosstalkDistanceMiddleX,"Middle of Track","l");
    legend31->Draw();
    
    Canvas7->cd(2);
    HistogramCrosstalkDistanceMiddleY->Draw("");
    HistogramCrosstalkDistanceMinus1Y->Draw("SAME");
    HistogramCrosstalkDistanceY->Draw("SAME");
        
    TLegend *legend32 = new TLegend(0.65,0.8,0.9,0.9);
    legend32->AddEntry(HistogramCrosstalkDistanceY,"Stopping Point","l");
    legend32->AddEntry(HistogramCrosstalkDistanceMinus1Y,"One Cube Backward","l");
    legend32->AddEntry(HistogramCrosstalkDistanceMiddleY,"Middle of Track","l");
    legend32->Draw();
    
    Canvas7->Print("/Users/kolos/Desktop/Studia/CIS/Output/CrosstalkDistanceComparison.pdf");
    delete Canvas7;
    
    TCanvas *Canvas8 = new TCanvas("Canvas8","Canvas8", 1400, 1000);
    Canvas8->Divide(3,2);
    
    Canvas8->cd(1);
    EnergyTrigTimeX->Draw("COLZ");
    Canvas8->cd(2);
    EnergyTrigTimeMinus1X->Draw("COLZ");
    Canvas8->cd(3);
    EnergyTrigTimeMiddleX->Draw("COLZ");
    Canvas8->cd(4);
    EnergyTrigTimeY->Draw("COLZ");
    Canvas8->cd(5);
    EnergyTrigTimeMinus1Y->Draw("COLZ");
    Canvas8->cd(6);
    EnergyTrigTimeMiddleY->Draw("COLZ");
    
    Canvas8->Print("/Users/kolos/Desktop/Studia/CIS/Output/EnergyTrigTimeAllComparison.pdf");
    delete Canvas8;
    
    /*
    TCanvas *CanvasCutG = new TCanvas("CanvasCutG","CanvasCutG", 1400, 1000);
    EnergyTrigTimeX->Draw("COLZ");
    TCutG *cutgTimeEnergy = new TCutG("cutgTimeEnergy",6);
    cutgTimeEnergy->SetVarX("");
    cutgTimeEnergy->SetVarY("");
    cutgTimeEnergy->SetTitle("Graph");
    cutgTimeEnergy->SetPoint(0,-100,10);
    cutgTimeEnergy->SetPoint(1,-70,120);
    cutgTimeEnergy->SetPoint(2,200,120);
    cutgTimeEnergy->SetPoint(3,200,2000);
    cutgTimeEnergy->SetPoint(4,-100,2000);
    cutgTimeEnergy->SetPoint(5,-100,10);    
    cutgTimeEnergy->SetLineColorAlpha(kRed, 1);
    cutgTimeEnergy->SetLineWidth(2);
    cutgTimeEnergy->Draw("l");
    CanvasCutG->Modified();
    CanvasCutG->cd();
    CanvasCutG->SetSelected(CanvasCutG);
    CanvasCutG->ToggleToolBar();
    */
    
    TCanvas *Canvas9 = new TCanvas("Canvas9","Canvas9", 1400, 1000);
    Canvas9->Divide(2,1);
    
    HistogramCrosstalkDistanceTypeX->SetLineColorAlpha(kRed, 1);
    HistogramCrosstalkDistanceTypeX->SetLineWidth(1.5);
    
    HistogramCrosstalkDistanceTypeMinus1X->SetLineColorAlpha(kBlue, 1);
    HistogramCrosstalkDistanceTypeMinus1X->SetLineWidth(1.5);
    
    HistogramCrosstalkDistanceTypeMiddleX->SetLineColorAlpha(kGreen, 1);
    HistogramCrosstalkDistanceTypeMiddleX->SetLineWidth(1.5);
    
    HistogramCrosstalkDistanceTypeY->SetLineColorAlpha(kRed, 1);
    HistogramCrosstalkDistanceTypeY->SetLineWidth(1.5);
    
    HistogramCrosstalkDistanceTypeMinus1Y->SetLineColorAlpha(kBlue, 1);
    HistogramCrosstalkDistanceTypeMinus1Y->SetLineWidth(1.5);
    
    HistogramCrosstalkDistanceTypeMiddleY->SetLineColorAlpha(kGreen, 1);
    HistogramCrosstalkDistanceTypeMiddleY->SetLineWidth(1.5);
    
    Canvas9->cd(1);
    HistogramCrosstalkDistanceTypeX->Draw("");
    HistogramCrosstalkDistanceTypeMinus1X->Draw("SAME");
    HistogramCrosstalkDistanceTypeMiddleX->Draw("SAME");
    
    TLegend *legend41 = new TLegend(0.65,0.8,0.9,0.9);
    legend41->AddEntry(HistogramCrosstalkDistanceTypeX,"Stopping Point","l");
    legend41->AddEntry(HistogramCrosstalkDistanceTypeMinus1X,"One Cube Backward","l");
    legend41->AddEntry(HistogramCrosstalkDistanceTypeMiddleX,"Middle of Track","l");
    legend41->Draw();
    
    Canvas9->cd(2);
    HistogramCrosstalkDistanceTypeY->Draw("");
    HistogramCrosstalkDistanceTypeMinus1Y->Draw("SAME");
    HistogramCrosstalkDistanceTypeMiddleY->Draw("SAME");
    
    TLegend *legend42 = new TLegend(0.65,0.8,0.9,0.9);
    legend42->AddEntry(HistogramCrosstalkDistanceTypeY,"Stopping Point","l");
    legend42->AddEntry(HistogramCrosstalkDistanceTypeMinus1Y,"One Cube Backward","l");
    legend42->AddEntry(HistogramCrosstalkDistanceTypeMiddleY,"Middle of Track","l");
    legend42->Draw();
    
    Canvas9->Print("/Users/kolos/Desktop/Studia/CIS/Output/CrosstalkTypeComparison.pdf");
    
    TCanvas *Canvas10 = new TCanvas("Canvas10","Canvas10", 1400, 1000);
    Canvas10->Divide(3,2);
    
    CrosstalkEnergyDepositCUTGX->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositCUTGX->SetLineWidth(1.5);
    CrosstalkEnergyDepositCUTGX->GetXaxis()->SetRangeUser(0., 100.);
    
    CrosstalkEnergyDepositMinus1CUTGX->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyDepositMinus1CUTGX->SetLineWidth(1.5);
    CrosstalkEnergyDepositMinus1CUTGX->GetXaxis()->SetRangeUser(0., 100.);
        
    CrosstalkEnergyDepositMiddleCUTGX->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyDepositMiddleCUTGX->SetLineWidth(1.5);
    CrosstalkEnergyDepositMiddleCUTGX->GetXaxis()->SetRangeUser(0., 100.);
        
    Canvas10->cd(1);
    CrosstalkEnergyDepositCUTGX->Draw("");
    CrosstalkEnergyDepositMinus1CUTGX->Draw("SAME");
    CrosstalkEnergyDepositMiddleCUTGX->Draw("SAME");
    
    TLegend *legend51 = new TLegend(0.65,0.8,0.9,0.9);
    legend51->AddEntry(CrosstalkEnergyDepositCUTGX,"Stopping Point","l");
    legend51->AddEntry(CrosstalkEnergyDepositMinus1CUTGX,"One Cube Backward","l");
    legend51->AddEntry(CrosstalkEnergyDepositMiddleCUTGX,"Middle of Track","l");
    legend51->Draw();
    
    HistogramCrosstalkDistanceCUTGX->SetLineColorAlpha(kRed, 1);
    HistogramCrosstalkDistanceCUTGX->SetLineWidth(1.5);
    
    HistogramCrosstalkDistanceMinus1CUTGX->SetLineColorAlpha(kBlue, 1);
    HistogramCrosstalkDistanceMinus1CUTGX->SetLineWidth(1.5);
    
    HistogramCrosstalkDistanceMiddleCUTGX->SetLineColorAlpha(kGreen, 1);
    HistogramCrosstalkDistanceMiddleCUTGX->SetLineWidth(1.5);
    
    long double normalizacja[6];
    for(int i=0;i<=5;i++)
    {
       normalizacja[i]=0;
    }
    int binowanie=HistogramCrosstalkDistanceCUTGX->GetNbinsX();

    for(int i=1;i<=binowanie;i++)
    {
        normalizacja[0]+=HistogramCrosstalkDistanceCUTGX->GetBinContent(i);
        normalizacja[1]+=HistogramCrosstalkDistanceMinus1CUTGX->GetBinContent(i);
        normalizacja[2]+=HistogramCrosstalkDistanceMiddleCUTGX->GetBinContent(i);
        normalizacja[3]+=HistogramCrosstalkDistanceCUTGY->GetBinContent(i);
        normalizacja[4]+=HistogramCrosstalkDistanceMinus1CUTGY->GetBinContent(i);
        normalizacja[5]+=HistogramCrosstalkDistanceMiddleCUTGY->GetBinContent(i);
    }
    int norma=1000;
    HistogramCrosstalkDistanceCUTGX->Scale(norma/normalizacja[0]);
    HistogramCrosstalkDistanceMinus1CUTGX->Scale(norma/normalizacja[1]);
    HistogramCrosstalkDistanceMiddleCUTGX->Scale(norma/normalizacja[2]);
    HistogramCrosstalkDistanceCUTGY->Scale(norma/normalizacja[3]);
    HistogramCrosstalkDistanceMinus1CUTGY->Scale(norma/normalizacja[4]);
    HistogramCrosstalkDistanceMiddleCUTGY->Scale(norma/normalizacja[5]);
    
    Canvas10->cd(2);
    HistogramCrosstalkDistanceMiddleCUTGX->Draw("");
    HistogramCrosstalkDistanceCUTGX->Draw("SAME");
    HistogramCrosstalkDistanceMinus1CUTGX->Draw("SAME");

    
    TLegend *legend52 = new TLegend(0.65,0.8,0.9,0.9);
    legend52->AddEntry(HistogramCrosstalkDistanceCUTGX,"Stopping Point","l");
    legend52->AddEntry(HistogramCrosstalkDistanceMinus1CUTGX,"One Cube Backward","l");
    legend52->AddEntry(HistogramCrosstalkDistanceMiddleCUTGX,"Middle of Track","l");
    legend52->Draw();
    
    CrosstalkEnergyDepositPercentageCUTGX->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositPercentageCUTGX->SetLineWidth(1.5);
    CrosstalkEnergyDepositPercentageCUTGX->GetXaxis()->SetRangeUser(0., 20.);
    
    CrosstalkEnergyPercentageMinus1CUTGX->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyPercentageMinus1CUTGX->SetLineWidth(1.5);
    CrosstalkEnergyPercentageMinus1CUTGX->GetXaxis()->SetRangeUser(0., 20.);
    
    CrosstalkEnergyPercentageMiddleCUTGX->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyPercentageMiddleCUTGX->SetLineWidth(1.5);
    CrosstalkEnergyPercentageMiddleCUTGX->GetXaxis()->SetRangeUser(0., 20.);
    long double normalizacja[6];
    for(int i=0;i<=5;i++)
    {
       normalizacja[i]=0;
    }
    int binowanie=CrosstalkEnergyDepositPercentageCUTGX->GetNbinsX();

    for(int i=1;i<=binowanie;i++)
    {
        normalizacja[0]+=CrosstalkEnergyDepositPercentageCUTGX->GetBinContent(i);
        normalizacja[1]+=CrosstalkEnergyPercentageMinus1CUTGX->GetBinContent(i);
        normalizacja[2]+=CrosstalkEnergyPercentageMiddleCUTGX->GetBinContent(i);
        normalizacja[3]+=CrosstalkEnergyDepositPercentageCUTGY->GetBinContent(i);
        normalizacja[4]+=CrosstalkEnergyPercentageMinus1CUTGY->GetBinContent(i);
        normalizacja[5]+=CrosstalkEnergyPercentageMiddleCUTGY->GetBinContent(i);
    }
    int norma=1000;
    CrosstalkEnergyDepositPercentageCUTGX->Scale(norma/normalizacja[0]);
    CrosstalkEnergyPercentageMinus1CUTGX->Scale(norma/normalizacja[1]);
    CrosstalkEnergyPercentageMiddleCUTGX->Scale(norma/normalizacja[2]);
    CrosstalkEnergyDepositPercentageCUTGY->Scale(norma/normalizacja[3]);
    CrosstalkEnergyPercentageMinus1CUTGY->Scale(norma/normalizacja[4]);
    CrosstalkEnergyPercentageMiddleCUTGY->Scale(norma/normalizacja[5]);
    
    Canvas10->cd(3);
    CrosstalkEnergyPercentageMiddleCUTGX->Draw("");
    CrosstalkEnergyDepositPercentageCUTGX->Draw("SAME");
    CrosstalkEnergyPercentageMinus1CUTGX->Draw("SAME");

    
    TLegend *legend53 = new TLegend(0.65,0.8,0.9,0.9);
    legend53->AddEntry(CrosstalkEnergyDepositPercentageCUTGX,"Stopping Point","l");
    legend53->AddEntry(CrosstalkEnergyPercentageMinus1CUTGX,"One Cube Backward","l");
    legend53->AddEntry(CrosstalkEnergyPercentageMiddleCUTGX,"Middle of Track","l");
    legend53->Draw();
    
    CrosstalkEnergyDepositCUTGY->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositCUTGY->SetLineWidth(1.5);
    CrosstalkEnergyDepositCUTGY->GetXaxis()->SetRangeUser(0., 100.);
        
    CrosstalkEnergyDepositMinus1CUTGY->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyDepositMinus1CUTGY->SetLineWidth(1.5);
    CrosstalkEnergyDepositMinus1CUTGY->GetXaxis()->SetRangeUser(0., 100.);
        
    CrosstalkEnergyDepositMiddleCUTGY->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyDepositMiddleCUTGY->SetLineWidth(1.5);
    CrosstalkEnergyDepositMiddleCUTGY->GetXaxis()->SetRangeUser(0., 100.);
        
    Canvas10->cd(4);
    CrosstalkEnergyDepositCUTGY->Draw("");
    CrosstalkEnergyDepositMinus1CUTGY->Draw("SAME");
    CrosstalkEnergyDepositMiddleCUTGY->Draw("SAME");
    
    TLegend *legend54 = new TLegend(0.65,0.8,0.9,0.9);
    legend54->AddEntry(CrosstalkEnergyDepositCUTGY,"Stopping Point","l");
    legend54->AddEntry(CrosstalkEnergyDepositMinus1CUTGY,"One Cube Backward","l");
    legend54->AddEntry(CrosstalkEnergyDepositMiddleCUTGY,"Middle of Track","l");
    legend54->Draw();
        
    HistogramCrosstalkDistanceCUTGY->SetLineColorAlpha(kRed, 1);
    HistogramCrosstalkDistanceCUTGY->SetLineWidth(1.5);
    
    HistogramCrosstalkDistanceMinus1CUTGY->SetLineColorAlpha(kBlue, 1);
    HistogramCrosstalkDistanceMinus1CUTGY->SetLineWidth(1.5);
    
    HistogramCrosstalkDistanceMiddleCUTGY->SetLineColorAlpha(kGreen, 1);
    HistogramCrosstalkDistanceMiddleCUTGY->SetLineWidth(1.5);
    
    Canvas10->cd(5);
    HistogramCrosstalkDistanceMiddleCUTGY->Draw("");
    HistogramCrosstalkDistanceCUTGY->Draw("SAME");
    HistogramCrosstalkDistanceMinus1CUTGY->Draw("SAME");

    TLegend *legend55 = new TLegend(0.65,0.8,0.9,0.9);
    legend55->AddEntry(HistogramCrosstalkDistanceCUTGY,"Stopping Point","l");
    legend55->AddEntry(HistogramCrosstalkDistanceMinus1CUTGY,"One Cube Backward","l");
    legend55->AddEntry(HistogramCrosstalkDistanceMiddleCUTGY,"Middle of Track","l");
    legend55->Draw();
    
    CrosstalkEnergyDepositPercentageCUTGY->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositPercentageCUTGY->SetLineWidth(1.5);
    CrosstalkEnergyDepositPercentageCUTGY->GetXaxis()->SetRangeUser(0., 20.);
    
    CrosstalkEnergyPercentageMinus1CUTGY->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyPercentageMinus1CUTGY->SetLineWidth(1.5);
    CrosstalkEnergyPercentageMinus1CUTGY->GetXaxis()->SetRangeUser(0., 20.);
    
    CrosstalkEnergyPercentageMiddleCUTGY->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyPercentageMiddleCUTGY->SetLineWidth(1.5);
    CrosstalkEnergyPercentageMiddleCUTGY->GetXaxis()->SetRangeUser(0., 20.);

    Canvas10->cd(6);
    CrosstalkEnergyDepositPercentageCUTGY->Draw("");
    CrosstalkEnergyPercentageMinus1CUTGY->Draw("SAME");
    CrosstalkEnergyPercentageMiddleCUTGY->Draw("SAME");
    
    TLegend *legend56 = new TLegend(0.65,0.8,0.9,0.9);
    legend56->AddEntry(CrosstalkEnergyDepositPercentageCUTGY,"Stopping Point","l");
    legend56->AddEntry(CrosstalkEnergyPercentageMinus1CUTGY,"One Cube Backward","l");
    legend56->AddEntry(CrosstalkEnergyPercentageMiddleCUTGY,"Middle of Track","l");
    legend56->Draw();
    
    Canvas10->Print("/Users/kolos/Desktop/Studia/CIS/Output/FullCrosstalkAfterCUTGComparison.pdf"); 
}

