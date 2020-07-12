#include <TH2F.h>
#include <fstream>
#include <iostream>
#include "TStyle.h"

void PlotMaker()
{
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(111);
    gStyle->SetPalette(1,0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetOptStat(0);
    
    char filename[200];
    sprintf(filename,"/Users/kolos/Desktop/Crosstalk/Data/DataMerged.root");
    TFile *file = new TFile(filename,"READ");
    if ( file->IsOpen() )
    {
        printf("File opened successfully\n");
    }  
    
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
    
    TH1F* HistogramCrosstalkDistanceX = (TH1F*) file->Get("HistogramCrosstalkDistanceX");
    HistogramCrosstalkDistanceX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* HistogramCrosstalkDistanceY = (TH1F*) file->Get("HistogramCrosstalkDistanceY");
    HistogramCrosstalkDistanceY->GetYaxis()->SetTitleOffset(1.4);
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
    
    TH1F* CrosstalkEnergyDepositOneCubeX = (TH1F*) file->Get("CrosstalkEnergyDepositOneCubeX");
    CrosstalkEnergyDepositOneCubeX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositOneCubeY = (TH1F*) file->Get("CrosstalkEnergyDepositOneCubeY");
    CrosstalkEnergyDepositOneCubeY->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositMinus1OneCubeX = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1OneCubeX");
    CrosstalkEnergyDepositMinus1OneCubeX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositMinus1OneCubeY = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1OneCubeY");
    CrosstalkEnergyDepositMinus1OneCubeY->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositMiddleOneCubeX = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleOneCubeX");
    CrosstalkEnergyDepositMiddleOneCubeX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositMiddleOneCubeY = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleOneCubeY");
    CrosstalkEnergyDepositMiddleOneCubeY->GetYaxis()->SetTitleOffset(1.4);
    
    TH1F* CrosstalkEnergyDepositTwoCubesX = (TH1F*) file->Get("CrosstalkEnergyDepositTwoCubesX");
    CrosstalkEnergyDepositTwoCubesX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositTwoCubesY = (TH1F*) file->Get("CrosstalkEnergyDepositTwoCubesY");
    CrosstalkEnergyDepositTwoCubesY->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositMinus1TwoCubesX = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1TwoCubesX");
    CrosstalkEnergyDepositMinus1TwoCubesX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositMinus1TwoCubesY = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1TwoCubesY");
    CrosstalkEnergyDepositMinus1TwoCubesY->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositMiddleTwoCubesX = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleTwoCubesX");
    CrosstalkEnergyDepositMiddleTwoCubesX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositMiddleTwoCubesY = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleTwoCubesY");
    CrosstalkEnergyDepositMiddleTwoCubesY->GetYaxis()->SetTitleOffset(1.4);
    
    TH1F* CrosstalkEnergyDepositPercentageOneCubeX = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageOneCubeX");
    CrosstalkEnergyDepositPercentageOneCubeX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositPercentageOneCubeY = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageOneCubeY");
    CrosstalkEnergyDepositPercentageOneCubeY->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyPercentageMinus1OneCubeX = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1OneCubeX");
    CrosstalkEnergyPercentageMinus1OneCubeX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyPercentageMinus1OneCubeY = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1OneCubeY");
    CrosstalkEnergyPercentageMinus1OneCubeY->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyPercentageMiddleOneCubeX = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleOneCubeX");
    CrosstalkEnergyPercentageMiddleOneCubeX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyPercentageMiddleOneCubeY = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleOneCubeY");
    CrosstalkEnergyPercentageMiddleOneCubeY->GetYaxis()->SetTitleOffset(1.4);

    TH1F* CrosstalkEnergyDepositPercentageTwoCubesX = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageTwoCubesX");
    CrosstalkEnergyDepositPercentageTwoCubesX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyDepositPercentageTwoCubesY = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageTwoCubesY");
    CrosstalkEnergyDepositPercentageTwoCubesY->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyPercentageMinus1TwoCubesX = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1TwoCubesX");
    CrosstalkEnergyPercentageMinus1TwoCubesX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyPercentageMinus1TwoCubesY = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1TwoCubesY");
    CrosstalkEnergyPercentageMinus1TwoCubesY->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyPercentageMiddleTwoCubesX = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleTwoCubesX");
    CrosstalkEnergyPercentageMiddleTwoCubesX->GetYaxis()->SetTitleOffset(1.4);
    TH1F* CrosstalkEnergyPercentageMiddleTwoCubesY = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleTwoCubesY");
    CrosstalkEnergyPercentageMiddleTwoCubesY->GetYaxis()->SetTitleOffset(1.4);
    
////////////////////////////////
    fstream plik;
    plik.open("/Users/kolos/Desktop/Crosstalk/Output/Probability.txt", ios::out);
    double main[3]={};
    double EventMapX[2][2][3]={}; //[1 away, 2 away][left,righ],[Z,Z-1,Z-15]
    double EventMapY[2][2][3]={}; //[1 away, 2 away][left,righ],[Z,Z-1,Z-15]
    
    main[0]=HistogramRealPeakEnergyDeposit->GetEntries();
    main[1]=HistogramRealPeakEnergyDepositMinus1->GetEntries();
    main[2]=HistogramRealPeakEnergyDepositMiddle->GetEntries();
    
    int BinTest = HistogramCrosstalkDistanceX->FindBin(-2);
    EventMapX[1][0][0]=HistogramCrosstalkDistanceX->GetBinContent(BinTest)/main[0]*100;
    int BinTest = HistogramCrosstalkDistanceX->FindBin(-1);
    EventMapX[0][0][0]=HistogramCrosstalkDistanceX->GetBinContent(BinTest)/main[0]*100;
    int BinTest = HistogramCrosstalkDistanceX->FindBin(1);
    EventMapX[0][1][0]=HistogramCrosstalkDistanceX->GetBinContent(BinTest)/main[0]*100;
    int BinTest = HistogramCrosstalkDistanceX->FindBin(2);
    EventMapX[1][1][0]=HistogramCrosstalkDistanceX->GetBinContent(BinTest)/main[0]*100;
    
    int BinTest = HistogramCrosstalkDistanceY->FindBin(-2);
    EventMapY[1][0][0]=HistogramCrosstalkDistanceY->GetBinContent(BinTest)/main[0]*100;
    int BinTest = HistogramCrosstalkDistanceY->FindBin(-1);
    EventMapY[0][0][0]=HistogramCrosstalkDistanceY->GetBinContent(BinTest)/main[0]*100;
    int BinTest = HistogramCrosstalkDistanceY->FindBin(1);
    EventMapY[0][1][0]=HistogramCrosstalkDistanceY->GetBinContent(BinTest)/main[0]*100;
    int BinTest = HistogramCrosstalkDistanceY->FindBin(2);
    EventMapY[1][1][0]=HistogramCrosstalkDistanceY->GetBinContent(BinTest)/main[0]*100;
    
    int BinTest = HistogramCrosstalkDistanceMinus1X->FindBin(-2);
    EventMapX[1][0][1]=HistogramCrosstalkDistanceMinus1X->GetBinContent(BinTest)/main[1]*100;
    int BinTest = HistogramCrosstalkDistanceMinus1X->FindBin(-1);
    EventMapX[0][0][1]=HistogramCrosstalkDistanceMinus1X->GetBinContent(BinTest)/main[1]*100;
    int BinTest = HistogramCrosstalkDistanceMinus1X->FindBin(1);
    EventMapX[0][1][1]=HistogramCrosstalkDistanceMinus1X->GetBinContent(BinTest)/main[1]*100;
    int BinTest = HistogramCrosstalkDistanceMinus1X->FindBin(2);
    EventMapX[1][1][1]=HistogramCrosstalkDistanceMinus1X->GetBinContent(BinTest)/main[1]*100;
    
    int BinTest = HistogramCrosstalkDistanceMinus1Y->FindBin(-2);
    EventMapY[1][0][1]=HistogramCrosstalkDistanceMinus1Y->GetBinContent(BinTest)/main[1]*100;
    int BinTest = HistogramCrosstalkDistanceMinus1Y->FindBin(-1);
    EventMapY[0][0][1]=HistogramCrosstalkDistanceMinus1Y->GetBinContent(BinTest)/main[1]*100;
    int BinTest = HistogramCrosstalkDistanceMinus1Y->FindBin(1);
    EventMapY[0][1][1]=HistogramCrosstalkDistanceMinus1Y->GetBinContent(BinTest)/main[1]*100;
    int BinTest = HistogramCrosstalkDistanceMinus1Y->FindBin(2);
    EventMapY[1][1][1]=HistogramCrosstalkDistanceMinus1Y->GetBinContent(BinTest)/main[1]*100;
    
    int BinTest = HistogramCrosstalkDistanceMiddleX->FindBin(-2);
    EventMapX[1][0][2]=HistogramCrosstalkDistanceMiddleX->GetBinContent(BinTest)/main[2]*100;
    int BinTest = HistogramCrosstalkDistanceMiddleX->FindBin(-1);
    EventMapX[0][0][2]=HistogramCrosstalkDistanceMiddleX->GetBinContent(BinTest)/main[2]*100;
    int BinTest = HistogramCrosstalkDistanceMiddleX->FindBin(1);
    EventMapX[0][1][2]=HistogramCrosstalkDistanceMiddleX->GetBinContent(BinTest)/main[2]*100;
    int BinTest = HistogramCrosstalkDistanceMiddleX->FindBin(2);
    EventMapX[1][1][2]=HistogramCrosstalkDistanceMiddleX->GetBinContent(BinTest)/main[2]*100;
    
    int BinTest = HistogramCrosstalkDistanceMiddleY->FindBin(-2);
    EventMapY[1][0][2]=HistogramCrosstalkDistanceMiddleY->GetBinContent(BinTest)/main[2]*100;
    int BinTest = HistogramCrosstalkDistanceMiddleY->FindBin(-1);
    EventMapY[0][0][2]=HistogramCrosstalkDistanceMiddleY->GetBinContent(BinTest)/main[2]*100;
    int BinTest = HistogramCrosstalkDistanceMiddleY->FindBin(1);
    EventMapY[0][1][2]=HistogramCrosstalkDistanceMiddleY->GetBinContent(BinTest)/main[2]*100;
    int BinTest = HistogramCrosstalkDistanceMiddleY->FindBin(2);
    EventMapY[1][1][2]=HistogramCrosstalkDistanceMiddleY->GetBinContent(BinTest)/main[2]*100;
    
    plik<<"X percetage stoppig point     : "<<EventMapX[1][0][0]<<" "<<EventMapX[0][0][0]<<" "<<EventMapX[0][1][0]<<" "<<EventMapX[1][1][0]<<endl;
    plik<<"Y percetage stoppig point     : "<<EventMapY[1][0][0]<<" "<<EventMapY[0][0][0]<<" "<<EventMapY[0][1][0]<<" "<<EventMapY[1][1][0]<<endl;
    plik<<"X percetage stoppig point-1   : "<<EventMapX[1][0][1]<<" "<<EventMapX[0][0][1]<<" "<<EventMapX[0][1][1]<<" "<<EventMapX[1][1][1]<<endl;
    plik<<"Y percetage stoppig point-1   : "<<EventMapY[1][0][1]<<" "<<EventMapY[0][0][1]<<" "<<EventMapY[0][1][1]<<" "<<EventMapY[1][1][1]<<endl;
    plik<<"X percetage stoppig point-15  : "<<EventMapX[1][0][2]<<" "<<EventMapX[0][0][2]<<" "<<EventMapX[0][1][2]<<" "<<EventMapX[1][1][2]<<endl;
    plik<<"Y percetage stoppig point-15  : "<<EventMapY[1][0][2]<<" "<<EventMapY[0][0][2]<<" "<<EventMapY[0][1][2]<<" "<<EventMapY[1][1][2]<<endl;
    
////////////////////////////////   
    
    
    EnergyTrigTimeX->GetYaxis()->SetTitleOffset(1.4);
    EnergyTrigTimeX->GetXaxis()->SetTitleSize(0.04);
    EnergyTrigTimeX->GetYaxis()->SetTitleSize(0.04);
    
    EnergyTrigTimeCrosstalkX->GetYaxis()->SetTitleOffset(1.3);
    EnergyTrigTimeCrosstalkX->GetXaxis()->SetTitleSize(0.04);
    EnergyTrigTimeCrosstalkX->GetYaxis()->SetTitleSize(0.04);
    
    EnergyTrigTimeSignalX->GetYaxis()->SetTitleOffset(1.3);
    EnergyTrigTimeSignalX->GetXaxis()->SetTitleSize(0.04);
    EnergyTrigTimeSignalX->GetYaxis()->SetTitleSize(0.04);
    
    EnergyTrigTimeX->GetYaxis()->SetTitleOffset(1.3);
    EnergyTrigTimeX->GetXaxis()->SetTitleSize(0.04);
    EnergyTrigTimeX->GetYaxis()->SetTitleSize(0.04);
        
    EnergyTrigTimeY->GetYaxis()->SetTitleOffset(1.3);
    EnergyTrigTimeY->GetXaxis()->SetTitleSize(0.04);
    EnergyTrigTimeY->GetYaxis()->SetTitleSize(0.04);
    
    EnergyTrigTimeCrosstalkY->GetYaxis()->SetTitleOffset(1.3);
    EnergyTrigTimeCrosstalkY->GetXaxis()->SetTitleSize(0.04);
    EnergyTrigTimeCrosstalkY->GetYaxis()->SetTitleSize(0.04);
    
    EnergyTrigTimeSignalY->GetYaxis()->SetTitleOffset(1.3);
    EnergyTrigTimeSignalY->GetXaxis()->SetTitleSize(0.04);
    EnergyTrigTimeSignalY->GetYaxis()->SetTitleSize(0.04);
    
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
    
    gPad->Modified();
    Canvas->Print("/Users/kolos/Desktop/Crosstalk/Output/TimeTriggerEnergy.pdf");
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
    
    gPad->Modified();
    Canvas2->Print("/Users/kolos/Desktop/Crosstalk/Output/WierdPlot.pdf");    
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
    HistogramRealPeakEnergyDeposit->GetXaxis()->SetRangeUser(0., 1200.);
    
    HistogramRealPeakEnergyDepositMinus1->SetLineColorAlpha(kBlue, 1);
    HistogramRealPeakEnergyDepositMinus1->SetLineWidth(1.5);
    HistogramRealPeakEnergyDepositMinus1->GetXaxis()->SetRangeUser(0., 1200.);
    
    HistogramRealPeakEnergyDepositMiddle->SetLineColorAlpha(kGreen, 1);
    HistogramRealPeakEnergyDepositMiddle->SetLineWidth(1.5);
    HistogramRealPeakEnergyDepositMiddle->GetXaxis()->SetRangeUser(0., 1200.);
        
    CrosstalkEnergyDepositX->GetYaxis()->SetTitleOffset(1.0);
    CrosstalkEnergyDepositX->GetXaxis()->SetTitleSize(0.05);
    CrosstalkEnergyDepositX->GetYaxis()->SetTitleSize(0.05);
    
    Canvas3->cd(1);
    CrosstalkEnergyDepositX->Draw("");
    CrosstalkEnergyDepositMinus1X->Draw("SAME");
    CrosstalkEnergyDepositMiddleX->Draw("SAME");
    
    TLegend *legend1 = new TLegend(0.48,0.6,0.9,0.9);
    legend1->AddEntry(CrosstalkEnergyDepositX,"Stopping Point","l");
    legend1->AddEntry(CrosstalkEnergyDepositMinus1X,"One Cube Backward","l");
    legend1->AddEntry(CrosstalkEnergyDepositMiddleX,"15 Cubes Backward","l");
    legend1->SetTextSize(0.05);
    legend1->Draw();
    
    CrosstalkEnergyDepositY->GetYaxis()->SetTitleOffset(1.0);
    CrosstalkEnergyDepositY->GetXaxis()->SetTitleSize(0.05);
    CrosstalkEnergyDepositY->GetYaxis()->SetTitleSize(0.05);
    
    Canvas3->cd(2);
    CrosstalkEnergyDepositY->Draw("");
    CrosstalkEnergyDepositMinus1Y->Draw("SAME");
    CrosstalkEnergyDepositMiddleY->Draw("SAME");
    
    TLegend *legend2 = new TLegend(0.48,0.6,0.9,0.9);
    legend2->AddEntry(CrosstalkEnergyDepositY,"Stopping Point","l");
    legend2->AddEntry(CrosstalkEnergyDepositMinus1Y,"One Cube Backward","l");
    legend2->AddEntry(CrosstalkEnergyDepositMiddleY,"15 Cubes Backward","l");
    legend2->SetTextSize(0.05);
    legend2->Draw();
    
    HistogramRealPeakEnergyDepositMiddle->GetYaxis()->SetTitleOffset(1.0);
    HistogramRealPeakEnergyDepositMiddle->GetXaxis()->SetTitleSize(0.05);
    HistogramRealPeakEnergyDepositMiddle->GetYaxis()->SetTitleSize(0.05);
    
    Canvas3->cd(3);
    HistogramRealPeakEnergyDeposit->Draw("");
    HistogramRealPeakEnergyDepositMinus1->Draw("SAME");
    HistogramRealPeakEnergyDepositMiddle->Draw("SAME");
    
    
    TLegend *legend3 = new TLegend(0.65,0.6,1.0,0.9);
    legend3->AddEntry(HistogramRealPeakEnergyDeposit,"Stopping Point","l");
    legend3->AddEntry(HistogramRealPeakEnergyDepositMinus1,"One Cube Backward","l");
    legend3->AddEntry(HistogramRealPeakEnergyDepositMiddle,"15 Cubes Backward","l");
    legend3->SetTextSize(0.04);
    legend3->Draw();
    
    gPad->Modified();
    Canvas3->Print("/Users/kolos/Desktop/Crosstalk/Output/CrosstalkComparison.pdf");
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
        
    CrosstalkEnergyPercentageMinus1X->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyPercentageMinus1X->SetLineWidth(1.5);
    CrosstalkEnergyPercentageMinus1X->GetXaxis()->SetRangeUser(0., 20.);
        
    CrosstalkEnergyPercentageMinus1Y->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyPercentageMinus1Y->SetLineWidth(1.5);
    CrosstalkEnergyPercentageMinus1Y->GetXaxis()->SetRangeUser(0., 20.);
        
    CrosstalkEnergyPercentageMiddleX->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyPercentageMiddleX->SetLineWidth(1.5);
    CrosstalkEnergyPercentageMiddleX->GetXaxis()->SetRangeUser(0., 20.);
        
    CrosstalkEnergyPercentageMiddleY->SetLineColorAlpha(kGreen, 1);
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
    
    CrosstalkEnergyDepositPercentageX->GetYaxis()->SetTitleOffset(1.0);
    CrosstalkEnergyDepositPercentageX->GetXaxis()->SetTitleSize(0.05);
    CrosstalkEnergyDepositPercentageX->GetYaxis()->SetTitleSize(0.05);
    
    Canvas4->cd(1);
    CrosstalkEnergyPercentageMinus1X->Draw("");
    CrosstalkEnergyDepositPercentageX->Draw("SAME");
    CrosstalkEnergyPercentageMiddleX->Draw("SAME");

    TLegend *legend11 = new TLegend(0.48,0.6,0.9,0.9);
    legend11->AddEntry(CrosstalkEnergyDepositPercentageX,"Stopping Point","l");
    legend11->AddEntry(CrosstalkEnergyPercentageMinus1X,"One Cube Backward","l");
    legend11->AddEntry(CrosstalkEnergyPercentageMiddleX,"15 Cubes Backward","l");
    legend11->SetTextSize(0.05);
    legend11->Draw();
    
    CrosstalkEnergyDepositPercentageY->GetYaxis()->SetTitleOffset(1.0);
    CrosstalkEnergyDepositPercentageY->GetXaxis()->SetTitleSize(0.05);
    CrosstalkEnergyDepositPercentageY->GetYaxis()->SetTitleSize(0.05);
    
    Canvas4->cd(2);
    CrosstalkEnergyDepositPercentageY->Draw("");
    CrosstalkEnergyPercentageMiddleY->Draw("SAME");
    CrosstalkEnergyPercentageMinus1Y->Draw("SAME");

    TLegend *legend12 = new TLegend(0.48,0.6,0.9,0.9);
    legend12->AddEntry(CrosstalkEnergyDepositPercentageY,"Stopping Point","l");
    legend12->AddEntry(CrosstalkEnergyPercentageMinus1Y,"One Cube Backward","l");
    legend12->AddEntry(CrosstalkEnergyPercentageMiddleY,"15 Cubes Backward","l");
    legend12->SetTextSize(0.05);
    legend12->Draw();
    
    CloneMiddlercentageX->GetYaxis()->SetTitleOffset(1.0);
    CloneMiddlercentageX->GetXaxis()->SetTitleSize(0.05);
    CloneMiddlercentageX->GetYaxis()->SetTitleSize(0.05);
    
    Canvas4->cd(3);
    CloneMinus1ercentageX->Draw("");
    CloneMiddlercentageX->Draw("SAME");
    CloneStoppingPercentageX->Draw("SAME");
    
    TLegend *legend13 = new TLegend(0.48,0.6,0.9,0.9);
    legend13->AddEntry(CloneStoppingPercentageX,"Stopping Point","l");
    legend13->AddEntry(CloneMinus1ercentageX,"One Cube Backward","l");
    legend13->AddEntry(CloneMiddlercentageX,"15 Cubes Backward","l");
    legend13->SetTextSize(0.05);
    legend13->Draw();
    
    CloneStoppingPercentageY->GetYaxis()->SetTitleOffset(1.0);
    CloneStoppingPercentageY->GetXaxis()->SetTitleSize(0.05);
    CloneStoppingPercentageY->GetYaxis()->SetTitleSize(0.05);
    
    Canvas4->cd(4);
    CloneStoppingPercentageY->Draw("");
    CloneMinus1ercentageY->Draw("SAME");
    CloneMiddlercentageY->Draw("SAME");
    
    TLegend *legend14 = new TLegend(0.48,0.6,0.9,0.9);
    legend14->AddEntry(CloneStoppingPercentageY,"Stopping Point","l");
    legend14->AddEntry(CloneMinus1ercentageY,"One Cube Backward","l");
    legend14->AddEntry(CloneMiddlercentageY,"15 Cubes Backward","l");
    legend14->SetTextSize(0.05);
    legend14->Draw();
    
    gPad->Modified();
    Canvas4->Print("/Users/kolos/Desktop/Crosstalk/Output/CrosstalkPercentageComparison.pdf");
    delete Canvas4;
    delete legend11; 
    delete legend12; 
    delete legend13; 
    delete legend14;

    //////////////////
    TCanvas *Canvas7 = new TCanvas("Canvas7","Canvas7", 1400, 1000);
    Canvas7->Divide(2,2);
    
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
    HistogramCrosstalkDistanceMinus1X->SetLineColorAlpha(kBlue, 1);
    HistogramCrosstalkDistanceMinus1X->SetLineWidth(1.5);
    HistogramCrosstalkDistanceMiddleX->SetLineColorAlpha(kGreen, 1);
    HistogramCrosstalkDistanceMiddleX->SetLineWidth(1.5);
    
    HistogramCrosstalkDistanceY->SetLineColorAlpha(kRed, 1);
    HistogramCrosstalkDistanceY->SetLineWidth(1.5);
    HistogramCrosstalkDistanceMinus1Y->SetLineColorAlpha(kBlue, 1);
    HistogramCrosstalkDistanceMinus1Y->SetLineWidth(1.5);
    HistogramCrosstalkDistanceMiddleY->SetLineColorAlpha(kGreen, 1);
    HistogramCrosstalkDistanceMiddleY->SetLineWidth(1.5);
    
    HistogramCrosstalkDistanceMiddleX->GetYaxis()->SetTitleOffset(1.0);
    HistogramCrosstalkDistanceMiddleX->GetXaxis()->SetTitleSize(0.05);
    HistogramCrosstalkDistanceMiddleX->GetYaxis()->SetTitleSize(0.05);
    
    Canvas7->cd(1);
    HistogramCrosstalkDistanceMiddleX->Draw("");
    HistogramCrosstalkDistanceMinus1X->Draw("SAME");
    HistogramCrosstalkDistanceX->Draw("SAME");
        
    TLegend *legend31 = new TLegend(0.1,0.6,0.40,0.9);
    legend31->AddEntry(HistogramCrosstalkDistanceX,"Stopping Point","l");
    legend31->AddEntry(HistogramCrosstalkDistanceMinus1X,"One Cube Backward","l");
    legend31->AddEntry(HistogramCrosstalkDistanceMiddleX,"15 Cubes Backward","l");
    legend31->SetTextSize(0.03);
    legend31->Draw();
    
    HistogramCrosstalkDistanceMiddleY->GetYaxis()->SetTitleOffset(1.0);
    HistogramCrosstalkDistanceMiddleY->GetXaxis()->SetTitleSize(0.05);
    HistogramCrosstalkDistanceMiddleY->GetYaxis()->SetTitleSize(0.05);
    
    Canvas7->cd(2);
    HistogramCrosstalkDistanceMiddleY->Draw("");
    HistogramCrosstalkDistanceMinus1Y->Draw("SAME");
    HistogramCrosstalkDistanceY->Draw("SAME");
        
    TLegend *legend32 = new TLegend(0.1,0.6,0.40,0.9);
    legend32->AddEntry(HistogramCrosstalkDistanceY,"Stopping Point","l");
    legend32->AddEntry(HistogramCrosstalkDistanceMinus1Y,"One Cube Backward","l");
    legend32->AddEntry(HistogramCrosstalkDistanceMiddleY,"15 Cubes Backward","l");
    legend32->SetTextSize(0.03);
    legend32->Draw();
    
    gPad->Modified();
    Canvas7->Print("/Users/kolos/Desktop/Studia/CIS/Crosstalk/StoppingProton/CrosstalkDistanceComparison.pdf");
    delete Canvas7;
    
    ///////
    
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
    
    gPad->Modified();
    Canvas8->Print("/Users/kolos/Desktop/Crosstalk/Output/EnergyTrigTimeAllComparison.pdf");
    delete Canvas8;
    
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
    legend41->AddEntry(HistogramCrosstalkDistanceTypeMiddleX,"15 Cubes Backward","l");
    legend41->Draw();
    
    Canvas9->cd(2);
    HistogramCrosstalkDistanceTypeMiddleY->Draw("");
    HistogramCrosstalkDistanceTypeY->Draw("SAME");
    HistogramCrosstalkDistanceTypeMinus1Y->Draw("SAME");

    
    TLegend *legend42 = new TLegend(0.65,0.8,0.9,0.9);
    legend42->AddEntry(HistogramCrosstalkDistanceTypeY,"Stopping Point","l");
    legend42->AddEntry(HistogramCrosstalkDistanceTypeMinus1Y,"One Cube Backward","l");
    legend42->AddEntry(HistogramCrosstalkDistanceTypeMiddleY,"15 Cubes Backward","l");
    legend42->Draw();
    
    gPad->Modified();
    Canvas9->Print("/Users/kolos/Desktop/Crosstalk/Output/CrosstalkTypeComparison.pdf");
    delete Canvas9;
////////////////////
    TCanvas *Canvas12 = new TCanvas("Canvas12","Canvas12", 1400, 1000);
    Canvas12->Divide(2,2);
    
    CrosstalkEnergyDepositOneCubeX->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositOneCubeX->SetLineWidth(1.5);
    
    CrosstalkEnergyDepositMinus1OneCubeX->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyDepositMinus1OneCubeX->SetLineWidth(1.5);
    
    CrosstalkEnergyDepositMiddleOneCubeX->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyDepositMiddleOneCubeX->SetLineWidth(1.5);
    
    CrosstalkEnergyDepositOneCubeY->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositOneCubeY->SetLineWidth(1.5);
    
    CrosstalkEnergyDepositMinus1OneCubeY->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyDepositMinus1OneCubeY->SetLineWidth(1.5);
    
    CrosstalkEnergyDepositMiddleOneCubeY->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyDepositMiddleOneCubeY->SetLineWidth(1.5);  
    
    ////
    
    CrosstalkEnergyDepositTwoCubesX->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositTwoCubesX->SetLineWidth(1.5);
        
    CrosstalkEnergyDepositMinus1TwoCubesX->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyDepositMinus1TwoCubesX->SetLineWidth(1.5);
        
    CrosstalkEnergyDepositMiddleTwoCubesX->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyDepositMiddleTwoCubesX->SetLineWidth(1.5);
        
    CrosstalkEnergyDepositTwoCubesY->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositTwoCubesY->SetLineWidth(1.5);
        
    CrosstalkEnergyDepositMinus1TwoCubesY->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyDepositMinus1TwoCubesY->SetLineWidth(1.5);
        
    CrosstalkEnergyDepositMiddleTwoCubesY->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyDepositMiddleTwoCubesY->SetLineWidth(1.5);
        
    CrosstalkEnergyDepositMinus1OneCubeX->GetYaxis()->SetTitleOffset(1.0);
    CrosstalkEnergyDepositMinus1OneCubeX->GetXaxis()->SetTitleSize(0.05);
    CrosstalkEnergyDepositMinus1OneCubeX->GetYaxis()->SetTitleSize(0.05);
    
    Canvas12->cd(1);
    CrosstalkEnergyDepositMinus1OneCubeX->Draw("");
    CrosstalkEnergyDepositOneCubeX->Draw("SAME");
    CrosstalkEnergyDepositMiddleOneCubeX->Draw("SAME");
    
    TLegend *legend71 = new TLegend(0.48,0.6,0.9,0.9);
    legend71->AddEntry(CrosstalkEnergyDepositOneCubeX,"Stopping Point","l");
    legend71->AddEntry(CrosstalkEnergyDepositMinus1OneCubeX,"One Cube Backward","l");
    legend71->AddEntry(CrosstalkEnergyDepositMiddleOneCubeX,"15 Cubes Backward","l");
    legend71->SetTextSize(0.05);
    legend71->Draw();
    
    CrosstalkEnergyDepositOneCubeY->GetYaxis()->SetTitleOffset(1.0);
    CrosstalkEnergyDepositOneCubeY->GetXaxis()->SetTitleSize(0.05);
    CrosstalkEnergyDepositOneCubeY->GetYaxis()->SetTitleSize(0.05);
    
    Canvas12->cd(2);
    CrosstalkEnergyDepositOneCubeY->Draw("");
    CrosstalkEnergyDepositMinus1OneCubeY->Draw("SAME");
    CrosstalkEnergyDepositMiddleOneCubeY->Draw("SAME");
    
    TLegend *legend72 = new TLegend(0.48,0.6,0.9,0.9);
    legend72->AddEntry(CrosstalkEnergyDepositOneCubeY,"Stopping Point","l");
    legend72->AddEntry(CrosstalkEnergyDepositMinus1OneCubeY,"One Cube Backward","l");
    legend72->AddEntry(CrosstalkEnergyDepositMiddleOneCubeY,"15 Cubes Backward","l");
    legend72->SetTextSize(0.05);
    legend72->Draw();
    
    CrosstalkEnergyDepositTwoCubesX->GetYaxis()->SetTitleOffset(1.0);
    CrosstalkEnergyDepositTwoCubesX->GetXaxis()->SetTitleSize(0.05);
    CrosstalkEnergyDepositTwoCubesX->GetYaxis()->SetTitleSize(0.05);
    
    Canvas12->cd(3);
    CrosstalkEnergyDepositTwoCubesX->Draw("");
    CrosstalkEnergyDepositMinus1TwoCubesX->Draw("SAME");
    CrosstalkEnergyDepositMiddleTwoCubesX->Draw("SAME");
    
    TLegend *legend73 = new TLegend(0.48,0.6,0.9,0.9);
    legend73->AddEntry(CrosstalkEnergyDepositTwoCubesX,"Stopping Point","l");
    legend73->AddEntry(CrosstalkEnergyDepositMinus1TwoCubesX,"One Cube Backward","l");
    legend73->AddEntry(CrosstalkEnergyDepositMiddleTwoCubesX,"15 Cubes Backward","l");
    legend73->SetTextSize(0.05);
    legend73->Draw();
    
    CrosstalkEnergyDepositTwoCubesY->GetYaxis()->SetTitleOffset(1.0);
    CrosstalkEnergyDepositTwoCubesY->GetXaxis()->SetTitleSize(0.05);
    CrosstalkEnergyDepositTwoCubesY->GetYaxis()->SetTitleSize(0.05);
    
    Canvas12->cd(4);
    CrosstalkEnergyDepositTwoCubesY->Draw("");
    CrosstalkEnergyDepositMinus1TwoCubesY->Draw("SAME");
    CrosstalkEnergyDepositMiddleTwoCubesY->Draw("SAME");
    
    TLegend *legend74 = new TLegend(0.48,0.6,0.9,0.9);
    legend74->AddEntry(CrosstalkEnergyDepositTwoCubesY,"Stopping Point","l");
    legend74->AddEntry(CrosstalkEnergyDepositMinus1TwoCubesY,"One Cube Backward","l");
    legend74->AddEntry(CrosstalkEnergyDepositMiddleTwoCubesY,"15 Cubes Backward","l");
    legend74->SetTextSize(0.05);
    legend74->Draw();
    
    gPad->Modified();
    Canvas12->Print("/Users/kolos/Desktop/Crosstalk/Output/CrosstalkCubeDistance.pdf");  
    delete Canvas12;
/////////////
    TCanvas *Canvas13 = new TCanvas("Canvas13","Canvas13", 1400, 1000);
    Canvas13->Divide(2,2);
    
    CrosstalkEnergyDepositPercentageOneCubeX->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositPercentageOneCubeX->SetLineWidth(1.5);
    CrosstalkEnergyDepositPercentageOneCubeX->GetXaxis()->SetRangeUser(0., 20.);
    
    CrosstalkEnergyPercentageMinus1OneCubeX->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyPercentageMinus1OneCubeX->SetLineWidth(1.5);
    CrosstalkEnergyPercentageMinus1OneCubeX->GetXaxis()->SetRangeUser(0., 20.);
    
    CrosstalkEnergyPercentageMiddleOneCubeX->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyPercentageMiddleOneCubeX->SetLineWidth(1.5);
    CrosstalkEnergyPercentageMiddleOneCubeX->GetXaxis()->SetRangeUser(0., 20.);
    
    CrosstalkEnergyDepositPercentageOneCubeY->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositPercentageOneCubeY->SetLineWidth(1.5);
    CrosstalkEnergyDepositPercentageOneCubeY->GetXaxis()->SetRangeUser(0., 20.);
    
    CrosstalkEnergyPercentageMinus1OneCubeY->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyPercentageMinus1OneCubeY->SetLineWidth(1.5);
    CrosstalkEnergyPercentageMinus1OneCubeY->GetXaxis()->SetRangeUser(0., 20.);
    
    CrosstalkEnergyPercentageMiddleOneCubeY->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyPercentageMiddleOneCubeY->SetLineWidth(1.5);
    CrosstalkEnergyPercentageMiddleOneCubeY->GetXaxis()->SetRangeUser(0., 20.);
    
    ///

    CrosstalkEnergyDepositPercentageTwoCubesX->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositPercentageTwoCubesX->SetLineWidth(1.5);
    CrosstalkEnergyDepositPercentageTwoCubesX->GetXaxis()->SetRangeUser(0., 20.);
    
    CrosstalkEnergyDepositPercentageTwoCubesY->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositPercentageTwoCubesY->SetLineWidth(1.5);
    CrosstalkEnergyDepositPercentageTwoCubesY->GetXaxis()->SetRangeUser(0., 20.);
    
    CrosstalkEnergyPercentageMinus1TwoCubesX->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyPercentageMinus1TwoCubesX->SetLineWidth(1.5);
    CrosstalkEnergyPercentageMinus1TwoCubesX->GetXaxis()->SetRangeUser(0., 20.);
    
    CrosstalkEnergyPercentageMinus1TwoCubesY->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyPercentageMinus1TwoCubesY->SetLineWidth(1.5);
    CrosstalkEnergyPercentageMinus1TwoCubesY->GetXaxis()->SetRangeUser(0., 20.);
    
    CrosstalkEnergyPercentageMiddleTwoCubesX->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyPercentageMiddleTwoCubesX->SetLineWidth(1.5);
    CrosstalkEnergyPercentageMiddleTwoCubesX->GetXaxis()->SetRangeUser(0., 20.);
    
    CrosstalkEnergyPercentageMiddleTwoCubesY->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyPercentageMiddleTwoCubesY->SetLineWidth(1.5);
    CrosstalkEnergyPercentageMiddleTwoCubesY->GetXaxis()->SetRangeUser(0., 20.);

    long double normalizacja2[12];
    for(int i=0;i<=11;i++)
    {
       normalizacja2[i]=0;
    }
    int binowanie=CrosstalkEnergyDepositPercentageOneCubeX->GetNbinsX();
    for(int i=1;i<=binowanie;i++)
    {
        normalizacja2[0]+=CrosstalkEnergyDepositPercentageOneCubeX->GetBinContent(i);
        normalizacja2[1]+=CrosstalkEnergyPercentageMinus1OneCubeX->GetBinContent(i);
        normalizacja2[2]+=CrosstalkEnergyPercentageMiddleOneCubeX->GetBinContent(i);
        normalizacja2[3]+=CrosstalkEnergyDepositPercentageOneCubeY->GetBinContent(i);
        normalizacja2[4]+=CrosstalkEnergyPercentageMinus1OneCubeY->GetBinContent(i);
        normalizacja2[5]+=CrosstalkEnergyPercentageMiddleOneCubeY->GetBinContent(i);
    }
    int binowanie=CrosstalkEnergyDepositPercentageTwoCubesX->GetNbinsX();
    for(int i=1;i<=binowanie;i++)
    {
        normalizacja2[6]+=CrosstalkEnergyDepositPercentageTwoCubesX->GetBinContent(i);
        normalizacja2[7]+=CrosstalkEnergyPercentageMinus1TwoCubesX->GetBinContent(i);
        normalizacja2[8]+=CrosstalkEnergyPercentageMiddleTwoCubesX->GetBinContent(i);
        normalizacja2[9]+=CrosstalkEnergyDepositPercentageTwoCubesY->GetBinContent(i);
        normalizacja2[10]+=CrosstalkEnergyPercentageMinus1TwoCubesY->GetBinContent(i);
        normalizacja2[11]+=CrosstalkEnergyPercentageMiddleTwoCubesY->GetBinContent(i);
    }
    
    int norma=1000;
    CrosstalkEnergyDepositPercentageOneCubeX->Scale(norma/normalizacja2[0]);
    CrosstalkEnergyPercentageMinus1OneCubeX->Scale(norma/normalizacja2[1]);
    CrosstalkEnergyPercentageMiddleOneCubeX->Scale(norma/normalizacja2[2]);
    CrosstalkEnergyDepositPercentageOneCubeY->Scale(norma/normalizacja2[3]);
    CrosstalkEnergyPercentageMinus1OneCubeY->Scale(norma/normalizacja2[4]);
    CrosstalkEnergyPercentageMiddleOneCubeY->Scale(norma/normalizacja2[5]);
    
    CrosstalkEnergyDepositPercentageTwoCubesX->Scale(norma/normalizacja2[6]);
    CrosstalkEnergyPercentageMinus1TwoCubesX->Scale(norma/normalizacja2[7]);
    CrosstalkEnergyPercentageMiddleTwoCubesX->Scale(norma/normalizacja2[8]);
    CrosstalkEnergyDepositPercentageTwoCubesY->Scale(norma/normalizacja2[9]);
    CrosstalkEnergyPercentageMinus1TwoCubesY->Scale(norma/normalizacja2[10]);
    CrosstalkEnergyPercentageMiddleTwoCubesY->Scale(norma/normalizacja2[11]);

    CrosstalkEnergyPercentageMinus1OneCubeX->GetYaxis()->SetTitleOffset(1.0);
    CrosstalkEnergyPercentageMinus1OneCubeX->GetXaxis()->SetTitleSize(0.05);
    CrosstalkEnergyPercentageMinus1OneCubeX->GetYaxis()->SetTitleSize(0.05);
    
    Canvas13->cd(1);
    CrosstalkEnergyPercentageMinus1OneCubeX->Draw("");
    CrosstalkEnergyDepositPercentageOneCubeX->Draw("SAME");
    CrosstalkEnergyPercentageMiddleOneCubeX->Draw("SAME");
    
    TLegend *legend81 = new TLegend(0.48,0.6,0.9,0.9);
    legend81->AddEntry(CrosstalkEnergyDepositPercentageOneCubeX,"Stopping Point","l");
    legend81->AddEntry(CrosstalkEnergyPercentageMinus1OneCubeX,"One Cube Backward","l");
    legend81->AddEntry(CrosstalkEnergyPercentageMiddleOneCubeX,"15 Cubes Backward","l");
    legend81->SetTextSize(0.05);
    legend81->Draw();
    
    CrosstalkEnergyDepositPercentageOneCubeY->GetYaxis()->SetTitleOffset(1.0);
    CrosstalkEnergyDepositPercentageOneCubeY->GetXaxis()->SetTitleSize(0.05);
    CrosstalkEnergyDepositPercentageOneCubeY->GetYaxis()->SetTitleSize(0.05);
    
    Canvas13->cd(2);
    CrosstalkEnergyDepositPercentageOneCubeY->Draw("");
    CrosstalkEnergyPercentageMinus1OneCubeY->Draw("SAME");
    CrosstalkEnergyPercentageMiddleOneCubeY->Draw("SAME");
    
    TLegend *legend82 = new TLegend(0.48,0.6,0.9,0.9);
    legend82->AddEntry(CrosstalkEnergyDepositPercentageOneCubeY,"Stopping Point","l");
    legend82->AddEntry(CrosstalkEnergyPercentageMinus1OneCubeY,"One Cube Backward","l");
    legend82->AddEntry(CrosstalkEnergyPercentageMiddleOneCubeY,"15 Cubes Backward","l");
    legend82->SetTextSize(0.05);
    legend82->Draw();
    
    CrosstalkEnergyDepositPercentageTwoCubesX->GetYaxis()->SetTitleOffset(1.0);
    CrosstalkEnergyDepositPercentageTwoCubesX->GetXaxis()->SetTitleSize(0.05);
    CrosstalkEnergyDepositPercentageTwoCubesX->GetYaxis()->SetTitleSize(0.05);
    
    Canvas13->cd(3);
    CrosstalkEnergyDepositPercentageTwoCubesX->Draw("");
    CrosstalkEnergyPercentageMinus1TwoCubesX->Draw("SAME");
    CrosstalkEnergyPercentageMiddleTwoCubesX->Draw("SAME");
    
    TLegend *legend83 = new TLegend(0.48,0.6,0.9,0.9);
    legend83->AddEntry(CrosstalkEnergyDepositPercentageTwoCubesX,"Stopping Point","l");
    legend83->AddEntry(CrosstalkEnergyPercentageMinus1TwoCubesX,"One Cube Backward","l");
    legend83->AddEntry(CrosstalkEnergyPercentageMiddleTwoCubesX,"15 Cubes Backward","l");
    legend83->SetTextSize(0.05);
    legend83->Draw();
    
    CrosstalkEnergyDepositPercentageTwoCubesY->GetYaxis()->SetTitleOffset(1.0);
    CrosstalkEnergyDepositPercentageTwoCubesY->GetXaxis()->SetTitleSize(0.05);
    CrosstalkEnergyDepositPercentageTwoCubesY->GetYaxis()->SetTitleSize(0.05);
    
    Canvas13->cd(4);
    CrosstalkEnergyDepositPercentageTwoCubesY->Draw("");
    CrosstalkEnergyPercentageMinus1TwoCubesY->Draw("SAME");
    CrosstalkEnergyPercentageMiddleTwoCubesY->Draw("SAME");
    
    TLegend *legend84 = new TLegend(0.48,0.6,0.9,0.9);
    legend84->AddEntry(CrosstalkEnergyDepositPercentageTwoCubesY,"Stopping Point","l");
    legend84->AddEntry(CrosstalkEnergyPercentageMinus1TwoCubesY,"One Cube Backward","l");
    legend84->AddEntry(CrosstalkEnergyPercentageMiddleTwoCubesY,"15 Cubes Backward","l");
    legend84->SetTextSize(0.05);
    legend84->Draw();
    
    gPad->Modified();
    Canvas13->Print("/Users/kolos/Desktop/Crosstalk/Output/CrosstalkPercentageDistance.pdf");  
    delete Canvas13;
    ///////////////
    TCanvas *Canvas15 = new TCanvas("Canvas15","Canvas15", 1400, 1000);
    Canvas15->Divide(3,2);
    
    CrosstalkEnergyDepositOneCubeX->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositMinus1OneCubeX->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositMiddleOneCubeX->SetLineColorAlpha(kRed, 1);
    ////
    CrosstalkEnergyDepositTwoCubesX->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyDepositMinus1TwoCubesX->SetLineColorAlpha(kBlue, 1);
    CrosstalkEnergyDepositMiddleTwoCubesX->SetLineColorAlpha(kBlue, 1);
     
    long double normalizacja[6];
    for(int i=0;i<=5;i++)
    {
       normalizacja[i]=0;
    }
    int binowanie=CrosstalkEnergyDepositOneCubeX->GetNbinsX();
    int binowanie2=CrosstalkEnergyDepositTwoCubesX->GetNbinsX();
    for(int i=1;i<=binowanie;i++)
    {
        normalizacja[0]+=CrosstalkEnergyDepositOneCubeX->GetBinContent(i);
        normalizacja[1]+=CrosstalkEnergyDepositMinus1OneCubeX->GetBinContent(i);
        normalizacja[2]+=CrosstalkEnergyDepositMiddleOneCubeX->GetBinContent(i);
    }
     for(int i=1;i<=binowanie2;i++)
    {
        normalizacja[3]+=CrosstalkEnergyDepositTwoCubesX->GetBinContent(i);
        normalizacja[4]+=CrosstalkEnergyDepositMinus1TwoCubesX->GetBinContent(i);
        normalizacja[5]+=CrosstalkEnergyDepositMiddleTwoCubesX->GetBinContent(i);
    }
    float normalization[3];
    normalization[0]=CrosstalkEnergyDepositTwoCubesX->GetEntries();
    normalization[1]=CrosstalkEnergyDepositMinus1TwoCubesX->GetEntries();
    normalization[2]=CrosstalkEnergyDepositMiddleTwoCubesX->GetEntries();
    
    CrosstalkEnergyDepositOneCubeX->Scale(normalization[0]/normalizacja[0]);
    CrosstalkEnergyDepositMinus1OneCubeX->Scale(normalization[1]/normalizacja[1]);
    CrosstalkEnergyDepositMiddleOneCubeX->Scale(normalization[2]/normalizacja[2]);
    CrosstalkEnergyDepositTwoCubesX->Scale(normalization[0]/normalizacja[3]);
    CrosstalkEnergyDepositMinus1TwoCubesX->Scale(normalization[1]/normalizacja[4]);
    CrosstalkEnergyDepositMiddleTwoCubesX->Scale(normalization[2]/normalizacja[5]);
    
    CrosstalkEnergyDepositTwoCubesX->GetYaxis()->SetTitleOffset(1.0);
    CrosstalkEnergyDepositTwoCubesX->GetXaxis()->SetTitleSize(0.05);
    CrosstalkEnergyDepositTwoCubesX->GetYaxis()->SetTitleSize(0.05);
    
    Canvas15->cd(1);
    CrosstalkEnergyDepositTwoCubesX->Draw("");
    CrosstalkEnergyDepositOneCubeX->Draw("SAME");
    
    
    TLegend *legend101 = new TLegend(0.48,0.75,0.9,0.9);
    legend101->AddEntry(CrosstalkEnergyDepositOneCubeX,"First Cube","l");
    legend101->AddEntry(CrosstalkEnergyDepositTwoCubesX,"Second Cube","l");
    legend101->SetTextSize(0.05);
    legend101->Draw();
    
    CrosstalkEnergyDepositMinus1TwoCubesX->GetYaxis()->SetTitleOffset(1.0);
    CrosstalkEnergyDepositMinus1TwoCubesX->GetXaxis()->SetTitleSize(0.05);
    CrosstalkEnergyDepositMinus1TwoCubesX->GetYaxis()->SetTitleSize(0.05);
    
    Canvas15->cd(2);
    CrosstalkEnergyDepositMinus1TwoCubesX->Draw("");
    CrosstalkEnergyDepositMinus1OneCubeX->Draw("SAME");
    
    
    TLegend *legend102 = new TLegend(0.48,0.75,0.9,0.9);
    legend102->AddEntry(CrosstalkEnergyDepositMinus1OneCubeX,"First Cube","l");
    legend102->AddEntry(CrosstalkEnergyDepositMinus1TwoCubesX,"Second Cube","l");
    legend102->SetTextSize(0.05);
    legend102->Draw();
    
    CrosstalkEnergyDepositMiddleTwoCubesX->GetYaxis()->SetTitleOffset(1.0);
    CrosstalkEnergyDepositMiddleTwoCubesX->GetXaxis()->SetTitleSize(0.05);
    CrosstalkEnergyDepositMiddleTwoCubesX->GetYaxis()->SetTitleSize(0.05);
    
    Canvas15->cd(3);
    CrosstalkEnergyDepositMiddleTwoCubesX->Draw("");
    CrosstalkEnergyDepositMiddleOneCubeX->Draw("SAME");
    
    
    TLegend *legend103 = new TLegend(0.48,0.75,0.9,0.9);
    legend103->AddEntry(CrosstalkEnergyDepositMiddleOneCubeX,"First Cube","l");
    legend103->AddEntry(CrosstalkEnergyDepositMiddleTwoCubesX,"Second Cube","l");
    legend103->SetTextSize(0.05);
    legend103->Draw();
    
    gPad->Modified();
    Canvas15->Print("/Users/kolos/Desktop/Crosstalk/Output/CrosstalkDepositFirstAndSecondCube.pdf");  
    delete Canvas15;
    
/////////////////////////////////////////////////////TODO
    Canvas201 = new TCanvas( "Canvas201", "Canvas201", 1400, 1000);
    TH1F* StopXz = (TH1F*) file->Get("StopXz");
    StopXz->GetYaxis()->SetTitleOffset(1.4);
    TH1F* StopXz1 = (TH1F*) file->Get("StopXz1");
    StopXz1->GetYaxis()->SetTitleOffset(1.4);
    TH1F* StopXz25 = (TH1F*) file->Get("StopXz25");
    StopXz25->GetYaxis()->SetTitleOffset(1.4);
        
    StopXz->SetLineColorAlpha(kRed, 1);
    StopXz->SetLineWidth(1.5);
    StopXz->GetXaxis()->SetRangeUser(0., 1200.);
    StopXz1->SetLineColorAlpha(kBlue, 1);
    StopXz1->SetLineWidth(1.5);
    StopXz1->GetXaxis()->SetRangeUser(0., 1200.);
    StopXz25->SetLineColorAlpha(kGreen, 1);
    StopXz25->SetLineWidth(1.5);
    StopXz25->GetXaxis()->SetRangeUser(0., 1200.);
    
    StopXz->GetYaxis()->SetTitleOffset(1.0);
    StopXz1->GetXaxis()->SetTitleSize(0.05);
    StopXz25->GetYaxis()->SetTitleSize(0.05);
    
    StopXz25->Draw("");
    StopXz->Draw("SAME");
    StopXz1->Draw("SAME");
    
    TLegend *legend201 = new TLegend(0.75,0.6,1.0,0.9);
    legend201->AddEntry(StopXz,"Stopping Point","l");
    legend201->AddEntry(StopXz1,"One Cube Backward","l");
    legend201->AddEntry(StopXz25,"25 Cubes Backward","l");
    legend201->SetTextSize(0.03);
    legend201->Draw();
    
    gPad->Modified();
    Canvas201->Print( "/Users/kolos/Desktop/Crosstalk/Output/NOWE_X_Depozyty.pdf" ); 
    delete Canvas201;
    
    Canvas202 = new TCanvas( "Canvas202", "Canvas202", 1400, 1000);
    
    TH1F* StopYz = (TH1F*) file->Get("StopYz");
    StopYz->GetYaxis()->SetTitleOffset(1.4);
    TH1F* StopYz1 = (TH1F*) file->Get("StopYz1");
    StopYz1->GetYaxis()->SetTitleOffset(1.4);
    TH1F* StopYz25 = (TH1F*) file->Get("StopYz25");
    StopYz25->GetYaxis()->SetTitleOffset(1.4);
    
    StopYz->SetLineColorAlpha(kRed, 1);
    StopYz->SetLineWidth(1.5);
    StopYz->GetXaxis()->SetRangeUser(0., 1200.);
    StopYz1->SetLineColorAlpha(kBlue, 1);
    StopYz1->SetLineWidth(1.5);
    StopYz1->GetXaxis()->SetRangeUser(0., 1200.);
    StopYz25->SetLineColorAlpha(kGreen, 1);
    StopYz25->SetLineWidth(1.5);
    StopYz25->GetXaxis()->SetRangeUser(0., 1200.);
    
    StopYz->GetYaxis()->SetTitleOffset(1.0);
    StopYz1->GetXaxis()->SetTitleSize(0.05);
    StopYz25->GetYaxis()->SetTitleSize(0.05);
    
    StopYz25->Draw("");
    StopYz->Draw("SAME");
    StopYz1->Draw("SAME");
    
    
    TLegend *legend202 = new TLegend(0.75,0.6,1.0,0.9);
    legend202->AddEntry(StopYz,"Stopping Point","l");
    legend202->AddEntry(StopYz1,"One Cube Backward","l");
    legend202->AddEntry(StopYz25,"25 Cubes Backward","l");
    legend202->SetTextSize(0.03);
    legend202->Draw();
    
    gPad->Modified();
    Canvas202->Print( "/Users/kolos/Desktop/Crosstalk/Output/NOWE_Y_Depozyty.pdf" ); 
    delete Canvas202;
    
///////////////////////////////////////////////////// TODO dodaj normalizacje
    Canvas203 = new TCanvas( "Canvas203", "Canvas203", 1400, 1000);
    TH1F* NewPercXz = (TH1F*) file->Get("NewPercXz");
    NewPercXz->GetYaxis()->SetTitleOffset(1.4);
    TH1F* NewPercXz1 = (TH1F*) file->Get("NewPercXz1");
    NewPercXz1->GetYaxis()->SetTitleOffset(1.4);
    TH1F* NewPercXz25 = (TH1F*) file->Get("NewPercXz25");
    NewPercXz25->GetYaxis()->SetTitleOffset(1.4);
        
    TH1F* NewPercYz = (TH1F*) file->Get("NewPercYz");
    NewPercYz->GetYaxis()->SetTitleOffset(1.4);
    TH1F* NewPercYz1 = (TH1F*) file->Get("NewPercYz1");
    NewPercYz1->GetYaxis()->SetTitleOffset(1.4);
    TH1F* NewPercYz25 = (TH1F*) file->Get("NewPercYz25");
    NewPercYz25->GetYaxis()->SetTitleOffset(1.4);
    
    for(int i=0;i<=5;i++)
    {
       normalizacja[i]=0;
    }
    int binowanie=HistogramCrosstalkDistanceX->GetNbinsX();
    for(int i=1;i<=binowanie;i++)
    {
        normalizacja[0]+=NewPercXz->GetBinContent(i);
        normalizacja[1]+=NewPercXz1->GetBinContent(i);
        normalizacja[2]+=NewPercXz25->GetBinContent(i);
        normalizacja[3]+=NewPercYz->GetBinContent(i);
        normalizacja[4]+=NewPercYz1->GetBinContent(i);
        normalizacja[5]+=NewPercYz25->GetBinContent(i);
    }
    int norma=1;
    NewPercXz->Scale(norma/normalizacja[0]);
    NewPercXz1->Scale(norma/normalizacja[1]);
    NewPercXz25->Scale(norma/normalizacja[2]);
    NewPercYz->Scale(norma/normalizacja[3]);
    NewPercYz1->Scale(norma/normalizacja[4]);
    NewPercYz25->Scale(norma/normalizacja[5]);

    NewPercXz->SetLineColorAlpha(kRed, 1);
    NewPercXz->SetLineWidth(1.5);
    NewPercXz->GetXaxis()->SetRangeUser(0., 20.);
    NewPercXz1->SetLineColorAlpha(kBlue, 1);
    NewPercXz1->SetLineWidth(1.5);
    NewPercXz1->GetXaxis()->SetRangeUser(0., 20.);
    NewPercXz25->SetLineColorAlpha(kGreen, 1);
    NewPercXz25->SetLineWidth(1.5);
    NewPercXz25->GetXaxis()->SetRangeUser(0., 20.);
    
    NewPercXz->GetYaxis()->SetTitleOffset(1.0);
    NewPercXz1->GetXaxis()->SetTitleSize(0.05);
    NewPercXz25->GetYaxis()->SetTitleSize(0.05);
    
    NewPercXz->Draw("");
    NewPercXz1->Draw("SAME");
    NewPercXz25->Draw("SAME");
    
    TLegend *legend203 = new TLegend(0.65,0.6,1.0,0.9);
    legend203->AddEntry(NewPercXz,"Stopping Point","l");
    legend203->AddEntry(NewPercXz1,"One Cube Backward","l");
    legend203->AddEntry(NewPercXz25,"25 Cubes Backward","l");
    legend203->SetTextSize(0.03);
    legend203->Draw();
    
    gPad->Modified();
    Canvas203->Print( "/Users/kolos/Desktop/Crosstalk/Output/NOWE_X_Procenty.pdf" ); 
    delete Canvas203;
    
    Canvas204 = new TCanvas( "Canvas204", "Canvas204", 1400, 1000);
        
    NewPercYz->SetLineColorAlpha(kRed, 1);
    NewPercYz->SetLineWidth(1.5);
    NewPercYz->GetXaxis()->SetRangeUser(0., 20.);
    NewPercYz1->SetLineColorAlpha(kBlue, 1);
    NewPercYz1->SetLineWidth(1.5);
    NewPercYz1->GetXaxis()->SetRangeUser(0., 20.);
    NewPercYz25->SetLineColorAlpha(kGreen, 1);
    NewPercYz25->SetLineWidth(1.5);
    NewPercYz25->GetXaxis()->SetRangeUser(0., 20.);
    
    NewPercYz->GetYaxis()->SetTitleOffset(1.0);
    NewPercYz1->GetXaxis()->SetTitleSize(0.05);
    NewPercYz25->GetYaxis()->SetTitleSize(0.05);
    
    NewPercYz->Draw("");
    NewPercYz1->Draw("SAME");
    NewPercYz25->Draw("SAME");
    
    TLegend *legend204 = new TLegend(0.65,0.6,1.0,0.9);
    legend204->AddEntry(NewPercYz,"Stopping Point","l");
    legend204->AddEntry(NewPercYz1,"One Cube Backward","l");
    legend204->AddEntry(NewPercYz25,"25 Cubes Backward","l");
    legend204->SetTextSize(0.03);
    legend204->Draw();
    
    gPad->Modified();
    Canvas204->Print( "/Users/kolos/Desktop/Crosstalk/Output/NOWE_Y_Procenty.pdf" ); 
    delete Canvas204;
     
}
