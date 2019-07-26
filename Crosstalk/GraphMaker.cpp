#include <TH2F.h>
#include <fstream>
#include <iostream>
#include "TStyle.h"
#include <TGraphPainter.h>


void GraphMaker()
{
    gStyle->SetOptStat(1111);
    //gStyle->SetOptFit(111);
    gStyle->SetPalette(1,0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetOptStat(0);
    
    char filename[200];
    sprintf(filename,"/Users/kolos/Desktop/Studia/CIS/Crosstalk/StoppingProton/Data/MergedCrosstalk.root");
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
    delete Canvas1;
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
    delete Canvas2;
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
    
    PercentageGraphX->Fit("pol0");
    PercentageGraphY->Fit("pol0");
    TF1 *fukcja = PercentageGraphY->GetListOfFunctions()->FindObject("pol0");
    fukcja->SetLineColor(4);
    
    TCanvas *Canvas3 = new TCanvas("Canvas3","Canvas3", 1400, 1000);
    
    TMultiGraph *mg2=new TMultiGraph();
    mg2->Add(PercentageGraphX);
    mg2->Add(PercentageGraphY);

    mg2->Draw("AP");
    mg2->GetXaxis()->SetTitle("Position from stopping point [cm]");
    mg2->GetYaxis()->SetTitle("Percentage %");
    mg2->GetYaxis()->SetRangeUser(0,4);
    gPad->Modified();

    auto legend3 = new TLegend(0.65,0.8,0.9,0.9);
    legend3->AddEntry(PercentageGraphX,"X Axis","pe");
    legend3->AddEntry(PercentageGraphY,"Y Axis","pe");
    legend3->Draw();
    
    Canvas3->Print("/Users/kolos/Desktop/Studia/CIS/OutputGraph/PercentageGraph.pdf");
    delete Canvas3;
    //////////
    TH1F* CrosstalkEnergyDepositOneCubeX = (TH1F*) file->Get("CrosstalkEnergyDepositOneCubeX");
    CrosstalkEnergyDepositOneCubeX->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositOneCubeX->GetXaxis()->SetRangeUser(0., Range);
    TH1F* CrosstalkEnergyDepositOneCubeY = (TH1F*) file->Get("CrosstalkEnergyDepositOneCubeY");
    CrosstalkEnergyDepositOneCubeY->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositOneCubeY->GetXaxis()->SetRangeUser(0., Range);
    TH1F* CrosstalkEnergyDepositMinus1OneCubeX = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1OneCubeX");
    CrosstalkEnergyDepositMinus1OneCubeX->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositMinus1OneCubeX->GetXaxis()->SetRangeUser(0., Range);
    TH1F* CrosstalkEnergyDepositMinus1OneCubeY = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1OneCubeY");
    CrosstalkEnergyDepositMinus1OneCubeY->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositMinus1OneCubeY->GetXaxis()->SetRangeUser(0., Range);
    TH1F* CrosstalkEnergyDepositMiddleOneCubeX = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleOneCubeX");
    CrosstalkEnergyDepositMiddleOneCubeX->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositMiddleOneCubeX->GetXaxis()->SetRangeUser(0., Range);
    TH1F* CrosstalkEnergyDepositMiddleOneCubeY = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleOneCubeY");
    CrosstalkEnergyDepositMiddleOneCubeY->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositMiddleOneCubeY->GetXaxis()->SetRangeUser(0., Range);
    
    double MeanCrosstalkOne[2][3];//[X AND Y][Z=0,Z-1,Z-15]
    double RMScrosstalkOne[2][3];//[X AND Y][Z=0,Z-1,Z-15]
    
    MeanCrosstalkOne[0][0]=CrosstalkEnergyDepositOneCubeX->GetMean(1);
    RMScrosstalkOne[0][0]=CrosstalkEnergyDepositOneCubeX->GetMean(11);
    
    MeanCrosstalkOne[0][1]=CrosstalkEnergyDepositMinus1OneCubeX->GetMean(1);
    RMScrosstalkOne[0][1]=CrosstalkEnergyDepositMinus1OneCubeX->GetMean(11);
    
    MeanCrosstalkOne[0][2]=CrosstalkEnergyDepositMiddleOneCubeX->GetMean(1);
    RMScrosstalkOne[0][2]=CrosstalkEnergyDepositMiddleOneCubeX->GetMean(11);
    
    MeanCrosstalkOne[1][0]=CrosstalkEnergyDepositOneCubeY->GetMean(1);
    RMScrosstalkOne[1][0]=CrosstalkEnergyDepositOneCubeY->GetMean(11);
    
    MeanCrosstalkOne[1][1]=CrosstalkEnergyDepositMinus1OneCubeY->GetMean(1);
    RMScrosstalkOne[1][1]=CrosstalkEnergyDepositMinus1OneCubeY->GetMean(11);
    
    MeanCrosstalkOne[1][2]=CrosstalkEnergyDepositMiddleOneCubeY->GetMean(1);
    RMScrosstalkOne[1][2]=CrosstalkEnergyDepositMiddleOneCubeY->GetMean(11);
    
    TGraphErrors* CrosstalkOneGraphX = new TGraphErrors(3, Distance, MeanCrosstalkOne[0], 0, RMScrosstalkOne[0]);
    CrosstalkOneGraphX->GetXaxis()->SetRangeUser(-2,20);
    CrosstalkOneGraphX->SetLineColor(kRed);
    CrosstalkOneGraphX->SetLineWidth(2);
    CrosstalkOneGraphX->SetMarkerStyle(20);
    CrosstalkOneGraphX->SetMarkerSize(1);
    CrosstalkOneGraphX->SetMarkerColor(kRed);

    TGraphErrors* CrosstalkOneGraphY = new TGraphErrors(3, Distance, MeanCrosstalkOne[1], 0, RMScrosstalkOne[1]);
    CrosstalkOneGraphY->GetXaxis()->SetRangeUser(-2,20);
    CrosstalkOneGraphY->SetLineColor(kBlue);
    CrosstalkOneGraphY->SetLineWidth(2);
    CrosstalkOneGraphY->SetMarkerStyle(20);
    CrosstalkOneGraphY->SetMarkerSize(1);
    CrosstalkOneGraphY->SetMarkerColor(kBlue);
    
    TCanvas *Canvas4 = new TCanvas("Canvas4","Canvas4", 1400, 1000);
    
    TMultiGraph *mg3=new TMultiGraph();
    mg3->Add(CrosstalkOneGraphX);
    mg3->Add(CrosstalkOneGraphY);

    mg3->Draw("AP");
    mg3->GetXaxis()->SetTitle("Position from stopping point [cm]");
    mg3->GetYaxis()->SetTitle("Deposit [p.e.]");
    gPad->Modified();

    auto legend4 = new TLegend(0.65,0.8,0.9,0.9);
    legend4->AddEntry(CrosstalkOneGraphX,"X Axis","pe");
    legend4->AddEntry(CrosstalkOneGraphY,"Y Axis","pe");
    legend4->Draw();
    
    Canvas4->Print("/Users/kolos/Desktop/Studia/CIS/OutputGraph/CrosstalkOneGraph.pdf");
    delete Canvas4;
    /////////
    TH1F* CrosstalkEnergyDepositTwoCubesX = (TH1F*) file->Get("CrosstalkEnergyDepositTwoCubesX");
    CrosstalkEnergyDepositTwoCubesX->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositTwoCubesX->GetXaxis()->SetRangeUser(0., Range);
    TH1F* CrosstalkEnergyDepositTwoCubesY = (TH1F*) file->Get("CrosstalkEnergyDepositTwoCubesY");
    CrosstalkEnergyDepositTwoCubesY->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositTwoCubesY->GetXaxis()->SetRangeUser(0., Range);
    TH1F* CrosstalkEnergyDepositMinus1TwoCubesX = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1TwoCubesX");
    CrosstalkEnergyDepositMinus1TwoCubesX->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositMinus1TwoCubesX->GetXaxis()->SetRangeUser(0., Range);
    TH1F* CrosstalkEnergyDepositMinus1TwoCubesY = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1TwoCubesY");
    CrosstalkEnergyDepositMinus1TwoCubesY->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositMinus1TwoCubesY->GetXaxis()->SetRangeUser(0., Range);
    TH1F* CrosstalkEnergyDepositMiddleTwoCubesX = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleTwoCubesX");
    CrosstalkEnergyDepositMiddleTwoCubesX->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositMiddleTwoCubesX->GetXaxis()->SetRangeUser(0., Range);
    TH1F* CrosstalkEnergyDepositMiddleTwoCubesY = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleTwoCubesY");
    CrosstalkEnergyDepositMiddleTwoCubesY->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositMiddleTwoCubesY->GetXaxis()->SetRangeUser(0., Range);
    
    double MeanCrosstalkTwo[2][3];//[X AND Y][Z=0,Z-1,Z-15]
    double RMScrosstalkTwo[2][3];//[X AND Y][Z=0,Z-1,Z-15]
    
    MeanCrosstalkTwo[0][0]=CrosstalkEnergyDepositTwoCubesX->GetMean(1);
    RMScrosstalkTwo[0][0]=CrosstalkEnergyDepositTwoCubesX->GetMean(11);
    
    MeanCrosstalkTwo[0][1]=CrosstalkEnergyDepositMinus1TwoCubesX->GetMean(1);
    RMScrosstalkTwo[0][1]=CrosstalkEnergyDepositMinus1TwoCubesX->GetMean(11);
    
    MeanCrosstalkTwo[0][2]=CrosstalkEnergyDepositMiddleTwoCubesX->GetMean(1);
    RMScrosstalkTwo[0][2]=CrosstalkEnergyDepositMiddleTwoCubesX->GetMean(11);
    
    MeanCrosstalkTwo[1][0]=CrosstalkEnergyDepositTwoCubesY->GetMean(1);
    RMScrosstalkTwo[1][0]=CrosstalkEnergyDepositTwoCubesY->GetMean(11);
    
    MeanCrosstalkTwo[1][1]=CrosstalkEnergyDepositMinus1TwoCubesY->GetMean(1);
    RMScrosstalkTwo[1][1]=CrosstalkEnergyDepositMinus1TwoCubesY->GetMean(11);
    
    MeanCrosstalkTwo[1][2]=CrosstalkEnergyDepositMiddleTwoCubesY->GetMean(1);
    RMScrosstalkTwo[1][2]=CrosstalkEnergyDepositMiddleTwoCubesY->GetMean(11);
    
    TGraphErrors* CrosstalkTwoGraphX = new TGraphErrors(3, Distance, MeanCrosstalkTwo[0], 0, RMScrosstalkTwo[0]);
    CrosstalkTwoGraphX->GetXaxis()->SetRangeUser(-2,20);
    CrosstalkTwoGraphX->SetLineColor(kRed);
    CrosstalkTwoGraphX->SetLineWidth(2);
    CrosstalkTwoGraphX->SetMarkerStyle(20);
    CrosstalkTwoGraphX->SetMarkerSize(1);
    CrosstalkTwoGraphX->SetMarkerColor(kRed);

    TGraphErrors* CrosstalkTwoGraphY = new TGraphErrors(3, Distance, MeanCrosstalkTwo[1], 0, RMScrosstalkTwo[1]);
    CrosstalkTwoGraphY->GetXaxis()->SetRangeUser(-2,20);
    CrosstalkTwoGraphY->SetLineColor(kBlue);
    CrosstalkTwoGraphY->SetLineWidth(2);
    CrosstalkTwoGraphY->SetMarkerStyle(20);
    CrosstalkTwoGraphY->SetMarkerSize(1);
    CrosstalkTwoGraphY->SetMarkerColor(kBlue);
    
    TCanvas *Canvas5 = new TCanvas("Canvas5","Canvas5", 1400, 1000);
    
    TMultiGraph *mg4=new TMultiGraph();
    mg4->Add(CrosstalkTwoGraphX);
    mg4->Add(CrosstalkTwoGraphY);

    mg4->Draw("AP");
    mg4->GetXaxis()->SetTitle("Position from stopping point [cm]");
    mg4->GetYaxis()->SetTitle("Deposit [p.e.]");
    gPad->Modified();

    auto legend5 = new TLegend(0.65,0.8,0.9,0.9);
    legend5->AddEntry(CrosstalkTwoGraphX,"X Axis","pe");
    legend5->AddEntry(CrosstalkTwoGraphY,"Y Axis","pe");
    legend5->Draw();
    
    Canvas5->Print("/Users/kolos/Desktop/Studia/CIS/OutputGraph/CrosstalkTwoGraph.pdf");
    delete Canvas5;
    delete CrosstalkEnergyDepositTwoCubesX;
    delete CrosstalkEnergyDepositTwoCubesY;
    delete CrosstalkEnergyDepositMiddleTwoCubesX;
    ///////
    TH1F* CrosstalkEnergyDepositPercentageOneCubeX = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageOneCubeX");
    CrosstalkEnergyDepositPercentageOneCubeX->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositPercentageOneCubeX->GetXaxis()->SetRangeUser(0., SecondRange);
    TH1F* CrosstalkEnergyDepositPercentageOneCubeY = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageOneCubeY");
    CrosstalkEnergyDepositPercentageOneCubeY->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositPercentageOneCubeY->GetXaxis()->SetRangeUser(0., SecondRange);
    TH1F* CrosstalkEnergyPercentageMinus1OneCubeX = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1OneCubeX");
    CrosstalkEnergyPercentageMinus1OneCubeX->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyPercentageMinus1OneCubeX->GetXaxis()->SetRangeUser(0., SecondRange);
    TH1F* CrosstalkEnergyPercentageMinus1OneCubeY = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1OneCubeY");
    CrosstalkEnergyPercentageMinus1OneCubeY->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyPercentageMinus1OneCubeY->GetXaxis()->SetRangeUser(0., SecondRange);
    TH1F* CrosstalkEnergyPercentageMiddleOneCubeX = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleOneCubeX");
    CrosstalkEnergyPercentageMiddleOneCubeX->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyPercentageMiddleOneCubeX->GetXaxis()->SetRangeUser(0., SecondRange);
    TH1F* CrosstalkEnergyPercentageMiddleOneCubeY = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleOneCubeY");
    CrosstalkEnergyPercentageMiddleOneCubeY->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyPercentageMiddleOneCubeY->GetXaxis()->SetRangeUser(0., SecondRange);
    
    double MeanPercentageOne[2][3];//[X AND Y][Z=0,Z-1,Z-15]
    double RMSPercentageOne[2][3];//[X AND Y][Z=0,Z-1,Z-15]
    
    MeanPercentageOne[0][0]=CrosstalkEnergyDepositPercentageOneCubeX->GetMean(1);
    RMSPercentageOne[0][0]=CrosstalkEnergyDepositPercentageOneCubeX->GetMean(11);
    
    MeanPercentageOne[0][1]=CrosstalkEnergyPercentageMinus1OneCubeX->GetMean(1);
    RMSPercentageOne[0][1]=CrosstalkEnergyPercentageMinus1OneCubeX->GetMean(11);
    
    MeanPercentageOne[0][2]=CrosstalkEnergyPercentageMiddleOneCubeX->GetMean(1);
    RMSPercentageOne[0][2]=CrosstalkEnergyPercentageMiddleOneCubeX->GetMean(11);
    
    MeanPercentageOne[1][0]=CrosstalkEnergyDepositPercentageOneCubeY->GetMean(1);
    RMSPercentageOne[1][0]=CrosstalkEnergyDepositPercentageOneCubeY->GetMean(11);
    
    MeanPercentageOne[1][1]=CrosstalkEnergyPercentageMinus1OneCubeY->GetMean(1);
    RMSPercentageOne[1][1]=CrosstalkEnergyPercentageMinus1OneCubeY->GetMean(11);
    
    MeanPercentageOne[1][2]=CrosstalkEnergyPercentageMiddleOneCubeY->GetMean(1);
    RMSPercentageOne[1][2]=CrosstalkEnergyPercentageMiddleOneCubeY->GetMean(11);
    
    TGraphErrors* PercentageOneGraphX = new TGraphErrors(3, Distance, MeanPercentageOne[0], 0, RMSPercentageOne[0]);
    PercentageOneGraphX->GetXaxis()->SetRangeUser(-2,24);
    PercentageOneGraphX->SetLineColor(kRed);
    PercentageOneGraphX->SetLineWidth(2);
    PercentageOneGraphX->SetMarkerStyle(20);
    PercentageOneGraphX->SetMarkerSize(1);
    PercentageOneGraphX->SetMarkerColor(kRed);

    TGraphErrors* PercentageOneGraphY = new TGraphErrors(3, Distance, MeanPercentage[1], 0, RMSPercentage[1]);
    PercentageOneGraphY->GetXaxis()->SetRangeUser(-2,24);
    PercentageOneGraphY->SetLineColor(kBlue);
    PercentageOneGraphY->SetLineWidth(2);
    PercentageOneGraphY->SetMarkerStyle(20);
    PercentageOneGraphY->SetMarkerSize(1);
    PercentageOneGraphY->SetMarkerColor(kBlue);
    
    PercentageOneGraphX->Fit("pol0");
    PercentageOneGraphY->Fit("pol0");
    TF1 *fukcja1 = PercentageOneGraphY->GetListOfFunctions()->FindObject("pol0");
    fukcja1->SetLineColor(4);
    
    TCanvas *Canvas6 = new TCanvas("Canvas6","Canvas6", 1400, 1000);
    
    TMultiGraph *mg5=new TMultiGraph();
    mg5->Add(PercentageOneGraphX);
    mg5->Add(PercentageOneGraphY);

    mg5->Draw("AP");
    mg5->GetXaxis()->SetTitle("Position from stopping point [cm]");
    mg5->GetYaxis()->SetTitle("Percentage %");
    mg5->GetYaxis()->SetRangeUser(0,4);
    gPad->Modified();

    auto legend6 = new TLegend(0.65,0.8,0.9,0.9);
    legend6->AddEntry(PercentageOneGraphX,"X Axis","pe");
    legend6->AddEntry(PercentageOneGraphY,"Y Axis","pe");
    legend6->Draw();
    
    Canvas6->Print("/Users/kolos/Desktop/Studia/CIS/OutputGraph/PercentageOneGraph.pdf");
    delete Canvas6;
    ///////
    TH1F* CrosstalkEnergyDepositPercentageTwoCubesX = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageTwoCubesX");
    CrosstalkEnergyDepositPercentageTwoCubesX->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositPercentageTwoCubesX->GetXaxis()->SetRangeUser(0., SecondRange);
    TH1F* CrosstalkEnergyDepositPercentageTwoCubesY = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageTwoCubesY");
    CrosstalkEnergyDepositPercentageTwoCubesY->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyDepositPercentageTwoCubesY->GetXaxis()->SetRangeUser(0., SecondRange);
    TH1F* CrosstalkEnergyPercentageMinus1TwoCubesX = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1TwoCubesX");
    CrosstalkEnergyPercentageMinus1TwoCubesX->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyPercentageMinus1TwoCubesX->GetXaxis()->SetRangeUser(0., SecondRange);
    TH1F* CrosstalkEnergyPercentageMinus1TwoCubesY = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1TwoCubesY");
    CrosstalkEnergyPercentageMinus1TwoCubesY->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyPercentageMinus1TwoCubesY->GetXaxis()->SetRangeUser(0., SecondRange);
    TH1F* CrosstalkEnergyPercentageMiddleTwoCubesX = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleTwoCubesX");
    CrosstalkEnergyPercentageMiddleTwoCubesX->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyPercentageMiddleTwoCubesX->GetXaxis()->SetRangeUser(0., SecondRange);
    TH1F* CrosstalkEnergyPercentageMiddleTwoCubesY = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleTwoCubesY");
    CrosstalkEnergyPercentageMiddleTwoCubesY->GetYaxis()->SetTitleOffset(1.4);
    CrosstalkEnergyPercentageMiddleTwoCubesY->GetXaxis()->SetRangeUser(0., SecondRange);
    
    double MeanPercentageTwo[2][3];//[X AND Y][Z=0,Z-1,Z-15]
    double RMSPercentageTwo[2][3];//[X AND Y][Z=0,Z-1,Z-15]
    
    MeanPercentageTwo[0][0]=CrosstalkEnergyDepositPercentageTwoCubesX->GetMean(1);
    RMSPercentageTwo[0][0]=CrosstalkEnergyDepositPercentageTwoCubesX->GetMean(11);
    
    MeanPercentageTwo[0][1]=CrosstalkEnergyPercentageMinus1TwoCubesX->GetMean(1);
    RMSPercentageTwo[0][1]=CrosstalkEnergyPercentageMinus1TwoCubesX->GetMean(11);
    
    MeanPercentageTwo[0][2]=CrosstalkEnergyPercentageMiddleTwoCubesX->GetMean(1);
    RMSPercentageTwo[0][2]=CrosstalkEnergyPercentageMiddleTwoCubesX->GetMean(11);
    
    MeanPercentageTwo[1][0]=CrosstalkEnergyDepositPercentageTwoCubesY->GetMean(1);
    RMSPercentageTwo[1][0]=CrosstalkEnergyDepositPercentageTwoCubesY->GetMean(11);
    
    MeanPercentageTwo[1][1]=CrosstalkEnergyPercentageMinus1TwoCubesY->GetMean(1);
    RMSPercentageTwo[1][1]=CrosstalkEnergyPercentageMinus1TwoCubesY->GetMean(11);
    
    MeanPercentageTwo[1][2]=CrosstalkEnergyPercentageMiddleTwoCubesY->GetMean(1);
    RMSPercentageTwo[1][2]=CrosstalkEnergyPercentageMiddleTwoCubesY->GetMean(11);
    
    TGraphErrors* PercentageTwoGraphX = new TGraphErrors(3, Distance, MeanPercentageTwo[0], 0, RMSPercentageTwo[0]);
    PercentageTwoGraphX->GetXaxis()->SetRangeUser(-2,24);
    PercentageTwoGraphX->SetLineColor(kRed);
    PercentageTwoGraphX->SetLineWidth(2);
    PercentageTwoGraphX->SetMarkerStyle(20);
    PercentageTwoGraphX->SetMarkerSize(1);
    PercentageTwoGraphX->SetMarkerColor(kRed);

    TGraphErrors* PercentageTwoGraphY = new TGraphErrors(3, Distance, MeanPercentageTwo[1], 0, RMSPercentageTwo[1]);
    PercentageTwoGraphY->GetXaxis()->SetRangeUser(-2,24);
    PercentageTwoGraphY->SetLineColor(kBlue);
    PercentageTwoGraphY->SetLineWidth(2);
    PercentageTwoGraphY->SetMarkerStyle(20);
    PercentageTwoGraphY->SetMarkerSize(1);
    PercentageTwoGraphY->SetMarkerColor(kBlue);
    
    PercentageTwoGraphX->Fit("pol0");
    PercentageTwoGraphY->Fit("pol0");
    TF1 *fukcja4 = PercentageTwoGraphX->GetListOfFunctions()->FindObject("pol0");
    TF1 *fukcja2 = PercentageTwoGraphY->GetListOfFunctions()->FindObject("pol0");
    fukcja2->SetLineColor(4);
    
    TCanvas *Canvas7 = new TCanvas("Canvas7","Canvas7", 1400, 1000);
    
    TMultiGraph *mg6=new TMultiGraph();
    mg6->Add(PercentageTwoGraphX);
    mg6->Add(PercentageTwoGraphY);

    mg6->Draw("AP");
    mg6->GetXaxis()->SetTitle("Position from stopping point [cm]");
    mg6->GetYaxis()->SetTitle("Percentage %");
    mg6->GetYaxis()->SetRangeUser(0,4);
    gPad->Modified();

    auto legend7 = new TLegend(0.65,0.8,0.9,0.9);
    legend7->AddEntry(PercentageTwoGraphX,"X Axis","pe");
    legend7->AddEntry(PercentageTwoGraphY,"Y Axis","pe");
    legend7->Draw();
    
    Canvas7->Print("/Users/kolos/Desktop/Studia/CIS/OutputGraph/PercentageTwoGraph.pdf");
    delete Canvas7;
    /////////////
    
    float XYconverter=(MeanPercentageOne[1][0]/MeanPercentageOne[0][0]+MeanPercentageOne[1][1]/MeanPercentageOne[0][1]+MeanPercentageOne[1][2]/MeanPercentageOne[0][2])/3;
    
    float XYconverterErrorSquared=
     pow(RMSPercentageOne[1][0]/MeanPercentageOne[0][0],2)+pow(MeanPercentageOne[1][0]*RMSPercentageOne[0][0]/pow(MeanPercentageOne[0][0],2), 2)
    +pow(RMSPercentageOne[1][1]/MeanPercentageOne[0][1],2)+pow(MeanPercentageOne[1][1]*RMSPercentageOne[0][1]/pow(MeanPercentageOne[0][1],2), 2)
    +pow(RMSPercentageOne[1][2]/MeanPercentageOne[0][2],2)+pow(MeanPercentageOne[1][2]*RMSPercentageOne[0][2]/pow(MeanPercentageOne[0][2],2), 2);
    float XYconverterError=sqrt(XYconverterErrorSquared)/3;
    
    //cout <<"KURWA"<< XYconverter<<" "<<XYconverterError<<endl;
    
    TH1F* CrosstalkEnergyDepositTwoCubesX = (TH1F*) file->Get("CrosstalkEnergyDepositTwoCubesX");
    CrosstalkEnergyDepositTwoCubesX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositMinus1TwoCubesX = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1TwoCubesX");
    CrosstalkEnergyDepositMinus1TwoCubesX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositMiddleTwoCubesX = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleTwoCubesX");
    CrosstalkEnergyDepositMiddleTwoCubesX->GetYaxis()->SetTitleOffset(1.4);
    
    TH1F *CrosstalkEnergyDepositTwoCubesYConverted = (TH1F*)(CrosstalkEnergyDepositTwoCubesX->Clone("CrosstalkEnergyDepositTwoCubesYConverted"));
    TH1F *CrosstalkEnergyDepositMinus1TwoCubesYConverted = (TH1F*)(CrosstalkEnergyDepositMinus1TwoCubesX->Clone("CrosstalkEnergyDepositMinus1TwoCubesYConverted"));
    TH1F *CrosstalkEnergyDepositMiddleTwoCubesYConverted = (TH1F*)(CrosstalkEnergyDepositMiddleTwoCubesX->Clone("CrosstalkEnergyDepositMiddleTwoCubesYConverted"));
    
    CrosstalkEnergyDepositTwoCubesYConverted->SetNameTitle("CrosstalkEnergyDepositTwoCubesYConverted","Crosstalk energy in Y stopping point, two cube");
    CrosstalkEnergyDepositMinus1TwoCubesYConverted->SetNameTitle("CrosstalkEnergyDepositMinus1TwoCubesYConverted","Crosstalk energy in Y plain, one cube backward, two cubes away.");
    CrosstalkEnergyDepositMiddleTwoCubesYConverted->SetNameTitle("CrosstalkEnergyDepositMiddleTwoCubesYConverted","Crosstalk energy in Y plain, 15 cubes away from stopping poin, two cubes.");
    
    CrosstalkEnergyDepositTwoCubesYConverted->Scale(0);
    CrosstalkEnergyDepositMinus1TwoCubesYConverted->Scale(0);
    CrosstalkEnergyDepositMiddleTwoCubesYConverted->Scale(0);
    
    int binowanie=CrosstalkEnergyDepositTwoCubesX->GetNbinsX();
    double PomocniczyDepozyt[3];
    for(int i=1;i<=binowanie;i++)
    {
        PomocniczyDepozyt[0]=XYconverter*CrosstalkEnergyDepositTwoCubesX->GetBinContent(i);
        PomocniczyDepozyt[1]=XYconverter*CrosstalkEnergyDepositMinus1TwoCubesX->GetBinContent(i);
        PomocniczyDepozyt[2]=XYconverter*CrosstalkEnergyDepositMiddleTwoCubesX->GetBinContent(i);
        
        CrosstalkEnergyDepositTwoCubesYConverted->SetBinContent(i*XYconverter, CrosstalkEnergyDepositTwoCubesX->GetBinContent(i));
        CrosstalkEnergyDepositMinus1TwoCubesYConverted->SetBinContent(i*XYconverter, CrosstalkEnergyDepositMinus1TwoCubesX->GetBinContent(i));
        CrosstalkEnergyDepositMiddleTwoCubesYConverted->SetBinContent(i*XYconverter, CrosstalkEnergyDepositMiddleTwoCubesX->GetBinContent(i));
        //cout<<i<<" "<<i*XYconverter<<" "<<CrosstalkEnergyDepositTwoCubesX->GetBinContent(i)<<endl;
        
        PomocniczyDepozyt[0]=0;
        PomocniczyDepozyt[1]=0;
        PomocniczyDepozyt[2]=0;
    }
    CrosstalkEnergyDepositTwoCubesYConverted->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositTwoCubesYConverted->SetLineWidth(1.5);
    
    CrosstalkEnergyDepositMinus1TwoCubesYConverted->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyDepositMinus1TwoCubesYConverted->SetLineWidth(1.5);
    
    CrosstalkEnergyDepositMiddleTwoCubesYConverted->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyDepositMiddleTwoCubesYConverted->SetLineWidth(1.5);
    
    TCanvas *Canvas8 = new TCanvas("Canvas8","Canvas8", 1400, 1000);
    
    CrosstalkEnergyDepositTwoCubesYConverted->Draw("");
    CrosstalkEnergyDepositMiddleTwoCubesYConverted->Draw("SAME");
    CrosstalkEnergyDepositMinus1TwoCubesYConverted->Draw("SAME");
    
    
    TLegend *legend9 = new TLegend(0.65,0.8,0.9,0.9);
    legend9->AddEntry(CrosstalkEnergyDepositTwoCubesYConverted,"Stopping Point","l");
    legend9->AddEntry(CrosstalkEnergyDepositMinus1TwoCubesYConverted,"One Cube Backward","l");
    legend9->AddEntry(CrosstalkEnergyDepositMiddleTwoCubesYConverted,"15 Cubes Backward","l");
    legend9->Draw();
    
    Canvas8->Print("/Users/kolos/Desktop/Studia/CIS/OutputGraph/TwoCubesYconverted.pdf");
    delete Canvas8;
    
    ///////
    double MeanConvrtedPercentageTwoY[3];//[Z=0,Z-1,Z-15]
    double RMSConvertedPercentageTwoY[3];//[Z=0,Z-1,Z-15]
    
    MeanConvrtedPercentageTwoY[0]=MeanPercentageTwo[0][0]*XYconverter;
    MeanConvrtedPercentageTwoY[1]=MeanPercentageTwo[0][1]*XYconverter;
    MeanConvrtedPercentageTwoY[2]=MeanPercentageTwo[0][2]*XYconverter;
    
    RMSConvertedPercentageTwoY[0]=sqrt( pow(MeanPercentageTwo[0][0]*XYconverterError,2) + pow(RMSPercentageTwo[0][0]*XYconverter,2) );
    RMSConvertedPercentageTwoY[1]=sqrt( pow(MeanPercentageTwo[0][1]*XYconverterError,2) + pow(RMSPercentageTwo[0][1]*XYconverter,2) );
    RMSConvertedPercentageTwoY[2]=sqrt( pow(MeanPercentageTwo[0][2]*XYconverterError,2) + pow(RMSPercentageTwo[0][2]*XYconverter,2) );
    
    
    TGraphErrors* PercentageConvertedTwoGraphY = new TGraphErrors(3, Distance, MeanConvrtedPercentageTwoY, 0, RMSConvertedPercentageTwoY);
    PercentageConvertedTwoGraphY->GetXaxis()->SetRangeUser(-2,24);
    PercentageConvertedTwoGraphY->SetLineColor(kBlue);
    PercentageConvertedTwoGraphY->SetLineWidth(2);
    PercentageConvertedTwoGraphY->SetMarkerStyle(20);
    PercentageConvertedTwoGraphY->SetMarkerSize(1);
    PercentageConvertedTwoGraphY->SetMarkerColor(kBlue);
    
    PercentageConvertedTwoGraphY->Fit("pol0");
    TF1 *fukcja3 = PercentageConvertedTwoGraphY->GetListOfFunctions()->FindObject("pol0");
    fukcja3->SetLineColor(4);
     
    TCanvas *Canvas9 = new TCanvas("Canvas9","Canvas9", 1400, 1000);
    
    fukcja4->Draw("");
    fukcja3->Draw("SAME");
    fukcja4->GetXaxis()->SetTitle("Position from stopping point [cm]");
    fukcja4->GetYaxis()->SetTitle("Percentage %");
    fukcja4->GetYaxis()->SetRangeUser(0,4);
    gPad->Modified();

    auto legend10 = new TLegend(0.65,0.8,0.9,0.9);
    legend10->AddEntry(fukcja4,"X Axis","l");
    legend10->AddEntry(fukcja3,"Y Axis","l");
    legend10->Draw();
    
    Canvas9->Print("/Users/kolos/Desktop/Studia/CIS/OutputGraph/PercentageConvertedTwoGraph.pdf");
}
