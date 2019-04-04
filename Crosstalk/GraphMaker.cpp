#include <TH2F.h>
#include <fstream>
#include <iostream>
#include "TStyle.h"
#include <TGraphPainter.h>


void GraphMaker()
{
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(111);
    gStyle->SetPalette(1,0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    
    char filename[200];
    sprintf(filename,"/Users/kolos/Desktop/Studia/CIS/Data/27August_1_MCR0_hadrons_0pt8Gev_0pt0T_Beam___Crosstalk.root");
    TFile *file = new TFile(filename,"READ");
    if ( file->IsOpen() )
    {
        printf("File opened successfully\n");
    }  
    
    file->cd();
    const double Range = 60; 
    TH1F* CrosstalkEnergyDepositX = (TH1F*) file->Get("CrosstalkEnergyDepositX");
    CrosstalkEnergyDepositX->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositX->GetXaxis()->SetRangeUser(0., Range);
    TH1F* CrosstalkEnergyDepositY = (TH1F*) file->Get("CrosstalkEnergyDepositY");
    CrosstalkEnergyDepositY->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositY->GetXaxis()->SetRangeUser(0., Range);
    TH1F* CrosstalkEnergyDepositMinus1X = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1X");
    CrosstalkEnergyDepositMinus1X->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositMinus1X->GetXaxis()->SetRangeUser(0., Range);
    TH1F* CrosstalkEnergyDepositMinus1Y = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1Y");
    CrosstalkEnergyDepositMinus1Y->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositMinus1Y->GetXaxis()->SetRangeUser(0., Range);
    TH1F* CrosstalkEnergyDepositMiddleX = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleX");
    CrosstalkEnergyDepositMiddleX->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositMiddleX->GetXaxis()->SetRangeUser(0., Range);
    TH1F* CrosstalkEnergyDepositMiddleY = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleY");
    CrosstalkEnergyDepositMiddleY->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositMiddleY->GetXaxis()->SetRangeUser(0., Range);
    
    double MeanCrosstalk[2][3];//[X AND Y][Z=0,Z-1,Z-15]
    double RMScrosstalk[2][3];//[X AND Y][Z=0,Z-1,Z-15]
    double Distance[3]={0, 1, 15};
    
    
    MeanCrosstalk[0][0]=CrosstalkEnergyDepositX->GetMean(1);
    RMScrosstalk[0][0]=CrosstalkEnergyDepositX->GetMean(11);
    
    MeanCrosstalk[0][1]=CrosstalkEnergyDepositMinus1X->GetMean(1);
    RMScrosstalk[0][1]=CrosstalkEnergyDepositMinus1X->GetMean(11);
    
    MeanCrosstalk[0][2]=CrosstalkEnergyDepositMiddleX->GetMean(1);
    RMScrosstalk[0][2]=CrosstalkEnergyDepositMiddleX->GetMean(11);
    
    MeanCrosstalk[1][0]=CrosstalkEnergyDepositY->GetMean(1);
    RMScrosstalk[1][0]=CrosstalkEnergyDepositY->GetMean(11);
    
    MeanCrosstalk[1][1]=CrosstalkEnergyDepositMinus1Y->GetMean(1);
    RMScrosstalk[1][1]=CrosstalkEnergyDepositMinus1Y->GetMean(11);
    
    MeanCrosstalk[1][2]=CrosstalkEnergyDepositMiddleY->GetMean(1);
    RMScrosstalk[1][2]=CrosstalkEnergyDepositMiddleY->GetMean(11);
    
    TGraphErrors* CrosstalkGraphX = new TGraphErrors(3, Distance, MeanCrosstalk[0], 0, RMScrosstalk[0]);
    CrosstalkGraphX->GetXaxis()->SetRangeUser(-2,20);
    CrosstalkGraphX->SetLineColor(kRed);
    CrosstalkGraphX->SetLineWidth(2);
    CrosstalkGraphX->SetMarkerStyle(20);
    CrosstalkGraphX->SetMarkerSize(1);
    CrosstalkGraphX->SetMarkerColor(kRed);

    TGraphErrors* CrosstalkGraphY = new TGraphErrors(3, Distance, MeanCrosstalk[1], 0, RMScrosstalk[1]);
    CrosstalkGraphY->GetXaxis()->SetRangeUser(-2,20);
    CrosstalkGraphY->SetLineColor(kBlue);
    CrosstalkGraphY->SetLineWidth(2);
    CrosstalkGraphY->SetMarkerStyle(20);
    CrosstalkGraphY->SetMarkerSize(1);
    CrosstalkGraphY->SetMarkerColor(kBlue);
    
    TCanvas *Canvas1 = new TCanvas("Canvas1","Canvas1", 1400, 1000);
    
    TMultiGraph *mg1=new TMultiGraph();
    mg1->Add(CrosstalkGraphX);
    mg1->Add(CrosstalkGraphY);

    mg1->Draw("AP");
    mg1->GetXaxis()->SetTitle("Position from stopping point [cm]");
    mg1->GetYaxis()->SetTitle("Deposit [p.e.]");
    gPad->Modified();

    auto legend1 = new TLegend(0.65,0.8,0.9,0.9);
    legend1->AddEntry(CrosstalkGraphX,"X Axis","pe");
    legend1->AddEntry(CrosstalkGraphY,"Y Axis","pe");
    legend1->Draw();
    
    Canvas1->Print("/Users/kolos/Desktop/Studia/CIS/OutputGraph/CrosstalkGraph.pdf");
    
    //////////////
    
    TH1F* HistogramRealPeakEnergyDeposit = (TH1F*) file->Get("HistogramRealPeakEnergyDeposit");
    HistogramRealPeakEnergyDeposit->GetYaxis()->SetTitleOffset(1.4);
    TH1F* HistogramRealPeakEnergyDepositMinus1 = (TH1F*) file->Get("HistogramRealPeakEnergyDepositMinus1");
    HistogramRealPeakEnergyDepositMinus1->GetYaxis()->SetTitleOffset(1.4);
    TH1F* HistogramRealPeakEnergyDepositMiddle = (TH1F*) file->Get("HistogramRealPeakEnergyDepositMiddle");
    HistogramRealPeakEnergyDepositMiddle->GetYaxis()->SetTitleOffset(1.4);
    
    double MeanDeposit[3];//[Z=0,Z-1,Z-15]
    double RMSDeposit[3];//[Z=0,Z-1,Z-15]
    
    MeanDeposit[0]=HistogramRealPeakEnergyDeposit->GetMean(1);
    RMSDeposit[0]=HistogramRealPeakEnergyDeposit->GetMean(11);
    
    MeanDeposit[1]=HistogramRealPeakEnergyDepositMinus1->GetMean(1);
    RMSDeposit[1]=HistogramRealPeakEnergyDepositMinus1->GetMean(11);
    
    MeanDeposit[2]=HistogramRealPeakEnergyDepositMiddle->GetMean(1);
    RMSDeposit[2]=HistogramRealPeakEnergyDepositMiddle->GetMean(11);
    
    TCanvas *Canvas2 = new TCanvas("Canvas2","Canvas2", 1400, 1000);
     
    TGraphErrors* DepositGraphX = new TGraphErrors(3, Distance, MeanDeposit, 0, RMSDeposit);
    DepositGraphX->GetXaxis()->SetRangeUser(-2,20);
    DepositGraphX->SetLineColor(kRed);
    DepositGraphX->SetLineWidth(2);
    DepositGraphX->SetMarkerStyle(20);
    DepositGraphX->SetMarkerSize(1);
    DepositGraphX->SetMarkerColor(kRed);

    DepositGraphX->Draw("AP");
    DepositGraphX->GetXaxis()->SetTitle("Position from stopping point [cm]");
    DepositGraphX->GetYaxis()->SetTitle("Deposit [p.e.]");
    gPad->Modified();
    
    
    Canvas2->Print("/Users/kolos/Desktop/Studia/CIS/OutputGraph/DepositGraph.pdf");
    
    ////////
    const double SecondRange = 8;
    
    TH1F* CrosstalkEnergyDepositPercentageX = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageX");
    CrosstalkEnergyDepositPercentageX->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositPercentageX->GetXaxis()->SetRangeUser(0., SecondRange);
    TH1F* CrosstalkEnergyDepositPercentageY = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageY");
    CrosstalkEnergyDepositPercentageY->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositPercentageY->GetXaxis()->SetRangeUser(0., SecondRange);
    TH1F* CrosstalkEnergyPercentageMinus1X = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1X");
    CrosstalkEnergyPercentageMinus1X->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyPercentageMinus1X->GetXaxis()->SetRangeUser(0., SecondRange);
    TH1F* CrosstalkEnergyPercentageMinus1Y = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1Y");
    CrosstalkEnergyPercentageMinus1Y->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyPercentageMinus1Y->GetXaxis()->SetRangeUser(0., SecondRange);
    TH1F* CrosstalkEnergyPercentageMiddleX = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleX");
    CrosstalkEnergyPercentageMiddleX->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyPercentageMiddleX->GetXaxis()->SetRangeUser(0., SecondRange);
    TH1F* CrosstalkEnergyPercentageMiddleY = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleY");
    CrosstalkEnergyPercentageMiddleY->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyPercentageMiddleY->GetXaxis()->SetRangeUser(0., SecondRange);
    
    double MeanPercentage[2][3];//[X AND Y][Z=0,Z-1,Z-15]
    double RMSPercentage[2][3];//[X AND Y][Z=0,Z-1,Z-15]
    double Distance[3]={0, 1, 15};
    
    
    MeanPercentage[0][0]=CrosstalkEnergyDepositPercentageX->GetMean(1);
    RMSPercentage[0][0]=CrosstalkEnergyDepositPercentageX->GetMean(11);
    
    MeanPercentage[0][1]=CrosstalkEnergyPercentageMinus1X->GetMean(1);
    RMSPercentage[0][1]=CrosstalkEnergyPercentageMinus1X->GetMean(11);
    
    MeanPercentage[0][2]=CrosstalkEnergyPercentageMiddleX->GetMean(1);
    RMSPercentage[0][2]=CrosstalkEnergyPercentageMiddleX->GetMean(11);
    
    MeanPercentage[1][0]=CrosstalkEnergyDepositPercentageY->GetMean(1);
    RMSPercentage[1][0]=CrosstalkEnergyDepositPercentageY->GetMean(11);
    
    MeanPercentage[1][1]=CrosstalkEnergyPercentageMinus1Y->GetMean(1);
    RMSPercentage[1][1]=CrosstalkEnergyPercentageMinus1Y->GetMean(11);
    
    MeanPercentage[1][2]=CrosstalkEnergyPercentageMiddleY->GetMean(1);
    RMSPercentage[1][2]=CrosstalkEnergyPercentageMiddleY->GetMean(11);
    
    TGraphErrors* PercentageGraphX = new TGraphErrors(3, Distance, MeanPercentage[0], 0, RMSPercentage[0]);
    PercentageGraphX->GetXaxis()->SetRangeUser(-2,24);
    PercentageGraphX->SetLineColor(kRed);
    PercentageGraphX->SetLineWidth(2);
    PercentageGraphX->SetMarkerStyle(20);
    PercentageGraphX->SetMarkerSize(1);
    PercentageGraphX->SetMarkerColor(kRed);

    TGraphErrors* PercentageGraphY = new TGraphErrors(3, Distance, MeanPercentage[1], 0, RMSPercentage[1]);
    PercentageGraphY->GetXaxis()->SetRangeUser(-2,24);
    PercentageGraphY->SetLineColor(kBlue);
    PercentageGraphY->SetLineWidth(2);
    PercentageGraphY->SetMarkerStyle(20);
    PercentageGraphY->SetMarkerSize(1);
    PercentageGraphY->SetMarkerColor(kBlue);
    
    TCanvas *Canvas3 = new TCanvas("Canvas3","Canvas3", 1400, 1000);
    
    TMultiGraph *mg2=new TMultiGraph();
    mg2->Add(PercentageGraphX);
    mg2->Add(PercentageGraphY);

    mg2->Draw("AP");
    mg2->GetXaxis()->SetTitle("Position from stopping point [cm]");
    mg2->GetYaxis()->SetTitle("Deposit [p.e.]");
    mg2->GetYaxis()->SetRangeUser(0,4);
    gPad->Modified();

    auto legend3 = new TLegend(0.65,0.8,0.9,0.9);
    legend3->AddEntry(PercentageGraphX,"X Axis","pe");
    legend3->AddEntry(PercentageGraphY,"Y Axis","pe");
    legend3->Draw();
    
    Canvas3->Print("/Users/kolos/Desktop/Studia/CIS/OutputGraph/PercentageGraph.pdf");
    
    
    
    
}
