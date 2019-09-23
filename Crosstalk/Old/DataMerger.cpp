#include <TH2F.h>
#include <fstream>
#include <iostream>
#include "TStyle.h"
#include "TCutG.h"

void DataMerger()
{
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(111);
    gStyle->SetPalette(1,0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    
    const int NumberOfFiles=8;
    char filename[NumberOfFiles][200];
    sprintf(filename[0],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/StoppingProton/Data/27August_1_MCR0_hadrons_0pt8Gev_0pt0T_Beam___Crosstalk.root");
    sprintf(filename[1],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/StoppingProton/Data/26August_26_MCR0_hadrons_0pt8Gev_0pt0T_Beam___Crosstalk.root"); 
    sprintf(filename[2],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/StoppingProton/Data/27August_2_MCR0_hadrons_0pt8Gev_0pt0T_Beam___Crosstalk.root"); 
    sprintf(filename[3],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/StoppingProton/Data/26August_14_MCR0_hadrons_0pt8Gev_0pt0T_Beam___Crosstalk.root");
    sprintf(filename[4],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/StoppingProton/Data/26August_13_MCR0_hadrons_0pt8Gev_0pt0T_Beam___Crosstalk.root");
    sprintf(filename[5],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/StoppingProton/Data/26August_12_MCR0_hadrons_0pt8Gev_0pt0T_Beam___Crosstalk.root");
    sprintf(filename[6],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/StoppingProton/Data/26August_11_MCR0_hadrons_0pt8Gev_0pt0T_Beam___Crosstalk.root");
    sprintf(filename[7],"/Users/kolos/Desktop/Studia/CIS/Crosstalk/StoppingProton/Data/26August_9_MCR0_hadrons_0pt8Gev_0pt0T_Beam___Crosstalk.root");
    
    TH2F *NewEventsMap_XY = new TH2F("NewEventsMap_XY","NewEventsMap_XY",  24,0,24, 8,0,8);
    TH2F *NewEventsMap_YZ = new TH2F("NewEventsMap_YZ","NewEventsMap_YZ",  48,0,48, 8,0,8);
    TH2F *NewEventsMap_XZ = new TH2F("NewEventsMap_XZ","NewEventsMap_XZ",  24,0,24, 48,0,48);
    TH2F *NewEnergyTrigTimeAll = new TH2F("NewEnergyTrigTimeAll","Energy and Time of Trigger whole run", 100,-100,100,500,0,1500);
    
    TH1F *NewHistogramHighestEnergyDeposit = new TH1F("NewHistogramHighestEnergyDeposit", "Histogram of highest value deposit",100,0,2500);
    TH1F *NewHistogramRealPeakEnergyDeposit = new TH1F("NewHistogramRealPeakEnergyDeposit", "Histogram of found stopping proton deposit",100,0,2500);
    
    TH1F *NewCrosstalkEnergyDepositX = new TH1F("NewCrosstalkEnergyDepositX", "Crosstalk energy in X plain",500,0,500);
    TH1F *NewCrosstalkEnergyDepositY = new TH1F("NewCrosstalkEnergyDepositY", "Crosstalk energy in Y plain",500,0,500);

    TH1F *NewCrosstalkEnergyDepositOneCubeX = new TH1F("NewCrosstalkEnergyDepositOneCubeX", "Crosstalk energy in X stopping point, one cube",50,0,100);
    TH1F *NewCrosstalkEnergyDepositOneCubeY = new TH1F("NewCrosstalkEnergyDepositOneCubeY", "Crosstalk energy in Y stopping point, one cube",50,0,100);
    
    TH1F *NewCrosstalkEnergyDepositTwoCubesX = new TH1F("NewCrosstalkEnergyDepositTwoCubesX", "Crosstalk energy in X stopping point, two cube",50,0,100);
    TH1F *NewCrosstalkEnergyDepositTwoCubesY = new TH1F("NewCrosstalkEnergyDepositTwoCubesY", "Crosstalk energy in Y stopping point, two cubes",50,0,100);

    TH1F *NewCrosstalkEnergyDepositPercentageX = new TH1F("NewCrosstalkEnergyDepositPercentageX", "Crosstalk energy divided by main deposit in X plain",200,0,100);
    TH1F *NewCrosstalkEnergyDepositPercentageY = new TH1F("NewCrosstalkEnergyDepositPercentageY", "Crosstalk energy divided by main deposit in Y plain",200,0,100);
    
    TH1F *NewCrosstalkEnergyDepositPercentageOneCubeX = new TH1F("NewCrosstalkEnergyDepositPercentageOneCubeX", "Crosstalk energy divided by main deposit in X plain,  one cube",200,0,100);
    TH1F *NewCrosstalkEnergyDepositPercentageOneCubeY = new TH1F("NewCrosstalkEnergyDepositPercentageOneCubeY", "Crosstalk energy divided by main deposit in Y plain,  one cube",200,0,100);
    
    TH1F *NewCrosstalkEnergyDepositPercentageTwoCubesX = new TH1F("NewCrosstalkEnergyDepositPercentageTwoCubesX", "Crosstalk energy divided by main deposit in X plain,  two cubes",100,0,100);
    TH1F *NewCrosstalkEnergyDepositPercentageTwoCubesY = new TH1F("NewCrosstalkEnergyDepositPercentageTwoCubesY", "Crosstalk energy divided by main deposit in Y plain,  one cube",100,0,100);
    
    TH1F *NewCrosstalkEnergyDepositPercentageSecondCubeNewX = new TH1F("NewCrosstalkEnergyDepositPercentageSecondCubeNewX", "Crosstalk in second cube divided by crosstalk in first cube, in X plain, one cube backward",100,0,100);
    
    TH1F *NewCrosstalkEnergyDepositCUTGX = new TH1F("NewCrosstalkEnergyDepositCUTGX", "Crosstalk energy in X plain after CUTG",200,0,200);
    TH1F *NewCrosstalkEnergyDepositCUTGY = new TH1F("NewCrosstalkEnergyDepositCUTGY", "Crosstalk energy in Y plain",200,0,200);
    
    TH1F *NewCrosstalkEnergyDepositOneCubeCUTGX = new TH1F("NewCrosstalkEnergyDepositOneCubeCUTGX", "Crosstalk energy in X plain after CUTG, only one cube away",50,0,100);
    TH1F *NewCrosstalkEnergyDepositOneCubeCUTGY = new TH1F("NewCrosstalkEnergyDepositOneCubeCUTGY", "Crosstalk energy in Y plain after CUTG, only one cube away",50,0,100);

    TH1F *NewCrosstalkEnergyDepositTwoCubesCUTGX = new TH1F("NewCrosstalkEnergyDepositTwoCubesCUTGX", "Crosstalk energy in X plain after CUTG only, two cubes away",50,0,100);
    TH1F *NewCrosstalkEnergyDepositTwoCubesCUTGY = new TH1F("NewCrosstalkEnergyDepositTwoCubesCUTGY", "Crosstalk energy in Y plain after CUTG only, two cubes away",50,0,100);
    
    TH1F *NewStoppingPointLocation = new TH1F("NewStoppingPointLocation", "Location of stopping point",48,0,48);
    
    TH1F *NewHistogramCrosstalkDistanceX= new TH1F("NewHistogramCrosstalkDistanceX", "Cube distance of energy deposit from peak X axis",10,-5,5);
    TH1F *NewHistogramCrosstalkDistanceY = new TH1F("NewHistogramCrosstalkDistanceY", "Cube distance of energy deposit from peak Y axis",10,-5,5);
    
    TH1F *NewHistogramCrosstalkDistanceCUTGX= new TH1F("NewHistogramCrosstalkDistanceCUTGX", "Cube distance in stopping point plain from peak X axis, after CUTG",10,-5,5);
    TH1F *NewHistogramCrosstalkDistanceCUTGY = new TH1F("NewHistogramCrosstalkDistanceCUTGY", "Cube distance in stopping point plain from peak Y axis, after CUTG",10,-5,5);

    TH1F *NewCrosstalkEnergyDepositPercentageCUTGX = new TH1F("NewCrosstalkEnergyDepositPercentageCUTGX", "Crosstalk energy divided by main deposit in X plain, after CUTG.",200,0,100);
    TH1F *NewCrosstalkEnergyDepositPercentageCUTGY = new TH1F("NewCrosstalkEnergyDepositPercentageCUTGY", "Crosstalk energy divided by main deposit in Y plain, after CUTG.",200,0,100);
    
    TH1F *NewCrosstalkEnergyDepositRestrictedX= new TH1F("NewCrosstalkEnergyDepositRestrictedX", "Crosstalk energy in X plain maximaly 2 cubes from deposit",500,0,500);
    TH1F *NewCrosstalkEnergyDepositRestrictedY= new TH1F("NewCrosstalkEnergyDepositRestrictedY", "Crosstalk energy in Y plain maximaly 2 cubes from deposit",500,0,500);
    
    TH1F *NewHistogramCrosstalkDistanceEnergyHigherThanX= new TH1F("NewHistogramCrosstalkDistanceEnergyHigherThanX", "Cube distance of energy deposit from peak X axis if energy higher than 50",10,-5,5);
    TH1F *NewHistogramCrosstalkDistanceEnergyHigherThanY= new TH1F("NewHistogramCrosstalkDistanceEnergyHigherThanY", "Cube distance of energy deposit from peak Y axis if energy higher than 50",10,-5,5);
    
    TH1F *NewHistogramCrosstalkDistanceCutX= new TH1F("NewHistogramCrosstalkDistanceCutX", "Cube distance of energy deposit from peak X axis if energy higher than 1",10,-5,5);
    TH1F *NewHistogramCrosstalkDistanceCutY= new TH1F("NewHistogramCrosstalkDistanceCutY", "Cube distance of energy deposit from peak Y axis if energy higher than 1",10,-5,5);

    TH1F *NewHistogramCrosstalkDistanceTypeX= new TH1F("NewHistogramCrosstalkDistanceTypeX", "Number of cubes that recieved signal X axis, stopping point",48,0,48);
    TH1F *NewHistogramCrosstalkDistanceTypeY= new TH1F("NewHistogramCrosstalkDistanceTypeY", "Number of cubes that recieved signal Y axis, stopping point",16,0,16);
    
    TH2F *NewEnergyTrigTimeX = new TH2F("NewEnergyTrigTimeX","Energy and Time of Trigger X axis stopping point + Crosstalk", 100,-100,100,500,0,1500);
    TH2F *NewEnergyTrigTimeY = new TH2F("NewEnergyTrigTimeY","Energy and Time of Trigger Y axis stopping point + Crosstalk", 100,-100,100,500,0,1500);
    
    TH2F *NewEnergyTrigTimeCrosstalkX = new TH2F("NewEnergyTrigTimeCrosstalkX","Energy and Time of Trigger X axis only Crosstalk", 100,-100,100,500,0,1500);
    TH2F *NewEnergyTrigTimeCrosstalkY = new TH2F("NewEnergyTrigTimeCrosstalkY","Energy and Time of Trigger Y axis only Crosstalk", 100,-100,100,500,0,1500);
    
    TH2F *NewEnergyTrigTimeSignalX = new TH2F("NewEnergyTrigTimeSignalX","Energy and Time of Trigger X axis only Signal", 100,-100,100,500,0,1500);
    TH2F *NewEnergyTrigTimeSignalY = new TH2F("NewEnergyTrigTimeSignalY","Energy and Time of Trigger Y axis only Signal", 100,-100,100,500,0,1500);
    
    TH2F *NewEnergyTrigTimeCUTGX = new TH2F("NewEnergyTrigTimeCUTGX","Energy and Time of Trigger X axis after CUTG", 100,-100,100,500,0,1500);
    TH2F *NewEnergyTrigTimeCUTGY = new TH2F("NewEnergyTrigTimeCUTGY","Energy and Time of Trigger Y axis after CUTG", 100,-100,100,500,0,1500);
    
    TH1F *NewCrosstalkEnergyDepositMinus1X = new TH1F("NewCrosstalkEnergyDepositMinus1X", "Crosstalk energy in X plain, one cube backward.",500,0,500);
    TH1F *NewCrosstalkEnergyDepositMinus1Y = new TH1F("NewCrosstalkEnergyDepositMinus1Y", "Crosstalk energy in Y plain, one cube backward.",500,0,500);
    
    TH1F *NewCrosstalkEnergyDepositMinus1OneCubeX = new TH1F("NewCrosstalkEnergyDepositMinus1OneCubeX", "Crosstalk energy in X plain, one cube backward, one cube away.",50,0,100);
    TH1F *NewCrosstalkEnergyDepositMinus1OneCubeY = new TH1F("NewCrosstalkEnergyDepositMinus1OneCubeY", "Crosstalk energy in Y plain, one cube backward, one cube away..",50,0,100);
    
    TH1F *NewCrosstalkEnergyDepositMinus1TwoCubesX = new TH1F("NewCrosstalkEnergyDepositMinus1TwoCubesX", "Crosstalk energy in X plain, one cube backward, two cubes away.",50,0,100);
    TH1F *NewCrosstalkEnergyDepositMinus1TwoCubesY = new TH1F("NewCrosstalkEnergyDepositMinus1TwoCubesY", "Crosstalk energy in Y plain, one cube backward, two cubes away..",50,0,100);
    
    TH1F *NewCrosstalkEnergyPercentageMinus1X = new TH1F("NewCrosstalkEnergyPercentageMinus1X", "Crosstalk divided by main deposit in X plain, one cube backward.",200,0,100);
    TH1F *NewCrosstalkEnergyPercentageMinus1Y = new TH1F("NewCrosstalkEnergyPercentageMinus1Y", "Crosstalk divided by main deposit in Y plain, one cube backward.",200,0,100);

    TH1F *NewCrosstalkEnergyPercentageMinus1OneCubeX = new TH1F("NewCrosstalkEnergyPercentageMinus1OneCubeX", "Crosstalk divided by main deposit in X plain, one cube backward, one cube.",200,0,100);
    TH1F *NewCrosstalkEnergyPercentageMinus1OneCubeY = new TH1F("NewCrosstalkEnergyPercentageMinus1OneCubeY", "Crosstalk divided by main deposit in Y plain, one cube backward, one cube.",200,0,100);

    TH1F *NewCrosstalkEnergyPercentageMinus1TwoCubesX = new TH1F("NewCrosstalkEnergyPercentageMinus1TwoCubesX", "Crosstalk divided by main deposit in X plain, one cube backward, two cubes.",100,0,100);
    TH1F *NewCrosstalkEnergyPercentageMinus1TwoCubesY = new TH1F("NewCrosstalkEnergyPercentageMinus1TwoCubesY", "Crosstalk divided by main deposit in Y plain, one cube backward, two cubes.",100,0,100);
    
    TH1F *NewCrosstalkEnergyDepositPercentageMinus1SecondCubeNewX = new TH1F("NewCrosstalkEnergyDepositPercentageMinus1SecondCubeNewX", "Crosstalk in second cube divided by crosstalk in first cube, in X plain, one cube backward.",100,0,100);
    
    TH1F *NewHistogramCrosstalkDistanceMinus1X= new TH1F("NewHistogramCrosstalkDistanceMinus1X", "Cube distance of energy deposit from peak X axis, one cube backward",10,-5,5); 
    TH1F *NewHistogramCrosstalkDistanceMinus1Y = new TH1F("NewHistogramCrosstalkDistanceMinus1Y", "Cube distance of energy deposit from peak Y axis, one cube backward",10,-5,5);

    TH1F *NewCrosstalkEnergyDepositMinus1CUTGX = new TH1F("NewCrosstalkEnergyDepositMinus1CUTGX", "Crosstalk energy in X plain, one cube backward, after CUTG.",200,0,200);
    TH1F *NewCrosstalkEnergyDepositMinus1CUTGY = new TH1F("NewCrosstalkEnergyDepositMinus1CUTGY", "Crosstalk energy in Y plain, one cube backward, after CUTG.",200,0,200);
    
    TH1F *NewCrosstalkEnergyDepositMinus1OneCubeCUTGX = new TH1F("NewCrosstalkEnergyDepositMinus1OneCubeCUTGX", "Crosstalk energy in X plain, one cube backward, after CUTG only one cube away",50,0,100);
    TH1F *NewCrosstalkEnergyDepositMinus1OneCubeCUTGY = new TH1F("NewCrosstalkEnergyDepositMinus1OneCubeCUTGY", "Crosstalk energy in Y plain, one cube backward, after CUTG only, one cube away",50,0,100);

    TH1F *NewCrosstalkEnergyDepositMinus1TwoCubesCUTGX = new TH1F("NewCrosstalkEnergyDepositMinus1TwoCubesCUTGX", "Crosstalk energy in X plain, two cubes backward, after CUTG only one cube away",50,0,100);
    TH1F *NewCrosstalkEnergyDepositMinus1TwoCubesCUTGY = new TH1F("NewCrosstalkEnergyDepositMinus1TwoCubesCUTGY", "Crosstalk energy in Y plain, two cubes backward, after CUTG only, one cube away",50,0,100);
    
    TH1F *NewCrosstalkEnergyPercentageMinus1CUTGX = new TH1F("NewCrosstalkEnergyPercentageMinus1CUTGX", "Crosstalk divided by main deposit in X plain, one cube backward, after CUTG.",200,0,100);
    TH1F *NewCrosstalkEnergyPercentageMinus1CUTGY = new TH1F("NewCrosstalkEnergyPercentageMinus1CUTGY", "Crosstalk divided by main deposit in Y plain, one cube backward, after CUTG.",200,0,100);
    
    TH1F *NewHistogramCrosstalkDistanceMinus1CUTGX= new TH1F("NewHistogramCrosstalkDistanceMinus1CUTGX", "Cube distance of energy deposit from peak X axis, one cube backward, after CUTG",10,-5,5);
    TH1F *NewHistogramCrosstalkDistanceMinus1CUTGY = new TH1F("NewHistogramCrosstalkDistanceMinus1CUTGY", "Cube distance of energy deposit from peak Y axis, one cube backward after CUTG",10,-5,5);
    
    TH1F *NewHistogramRealPeakEnergyDepositMinus1 = new TH1F("NewHistogramRealPeakEnergyDepositMinus1", "Histogram of highest value deposit, 1 cubes away from stopping poin.",100,0,2500);
    
    TH1F *NewHistogramCrosstalkDistanceTypeMinus1X= new TH1F("NewHistogramCrosstalkDistanceTypeMinus1X", "Number of cubes that recieved signal X axis, one cube backward",48,0,48);
    TH1F *NewHistogramCrosstalkDistanceTypeMinus1Y= new TH1F("NewHistogramCrosstalkDistanceTypeMinus1Y", "Number of cubes that recieved signal Y axis, one cube backward",16,0,16);

    TH2F *NewEnergyTrigTimeMinus1X = new TH2F("NewEnergyTrigTimeMinus1X","Energy and Time of Trigger X axis, one cube backward", 100,-100,100,500,0,1500);
    TH2F *NewEnergyTrigTimeMinus1Y = new TH2F("NewEnergyTrigTimeMinus1Y","Energy and Time of Trigger Y axis, one cube backward", 100,-100,100,500,0,1500);

    TH1F *NewCrosstalkEnergyDepositMiddleX = new TH1F("NewCrosstalkEnergyDepositMiddleX", "Crosstalk energy in X plain, 15 cubes away from stopping poin.",500,0,500);
    TH1F *NewCrosstalkEnergyDepositMiddleY = new TH1F("NewCrosstalkEnergyDepositMiddleY", "Crosstalk energy in Y plain, 15 cubes away from stopping poin.",500,0,500);

    TH1F *NewCrosstalkEnergyDepositMiddleOneCubeX = new TH1F("NewCrosstalkEnergyDepositMiddleOneCubeX", "Crosstalk energy in X plain, 15 cubes away from stopping poin, one cube.",50,0,100);
    TH1F *NewCrosstalkEnergyDepositMiddleOneCubeY = new TH1F("NewCrosstalkEnergyDepositMiddleOneCubeY", "Crosstalk energy in Y plain, 15 cubes away from stopping poin, one cube.",50,0,100);

    TH1F *NewCrosstalkEnergyDepositMiddleTwoCubesX = new TH1F("NewCrosstalkEnergyDepositMiddleTwoCubesX", "Crosstalk energy in X plain, 15 cubes away from stopping poin, two cubes.",50,0,100);
    TH1F *NewCrosstalkEnergyDepositMiddleTwoCubesY = new TH1F("NewCrosstalkEnergyDepositMiddleTwoCubesY", "Crosstalk energy in Y plain, 15 cubes away from stopping poin, two cubes.",50,0,100);

    TH1F *NewCrosstalkEnergyPercentageMiddleX = new TH1F("NewCrosstalkEnergyPercentageMiddleX", "Crosstalk energy divided by main deposit in X plain, 15 cubes away from stopping poin.",200,0,100);
    TH1F *NewCrosstalkEnergyPercentageMiddleY = new TH1F("NewCrosstalkEnergyPercentageMiddleY", "Crosstalk energy divided by main deposit in Y plain, 15 cubes away from stopping poin..",200,0,100);
    
    TH1F *NewCrosstalkEnergyPercentageMiddleOneCubeX = new TH1F("NewCrosstalkEnergyPercentageMiddleOneCubeX", "Crosstalk energy divided by main deposit in X plain, 15 cubes away from stopping poin, one cube.",200,0,100);
    TH1F *NewCrosstalkEnergyPercentageMiddleOneCubeY = new TH1F("NewCrosstalkEnergyPercentageMiddleOneCubeY", "Crosstalk energy divided by main deposit in Y plain, 15 cubes away from stopping poin, one cube.",200,0,100);

    TH1F *NewCrosstalkEnergyPercentageMiddleTwoCubesX = new TH1F("NewCrosstalkEnergyPercentageMiddleTwoCubesX", "Crosstalk energy divided by main deposit in X plain, 15 cubes away from stopping poin, two cubes.",100,0,100);
    TH1F *NewCrosstalkEnergyPercentageMiddleTwoCubesY = new TH1F("NewCrosstalkEnergyPercentageMiddleTwoCubesY", "Crosstalk energy divided by main deposit in Y plain, 15 cubes away from stopping poin, two cubes.",100,0,100);
    
    TH1F *NewCrosstalkEnergyDepositPercentageMiddleSecondCubeNewX = new TH1F("NewCrosstalkEnergyDepositPercentageMiddleSecondCubeNewX", "Crosstalk in second cube divided by crosstalk in first cube, in X plain, 15 cubes backward.",100,0,100);
    
    TH1F *NewHistogramCrosstalkDistanceMiddleX= new TH1F("NewHistogramCrosstalkDistanceMiddleX", "Cube distance of energy deposit from peak X axis, 15 cubes away from stopping poin.",10,-5,5);
    TH1F *NewHistogramCrosstalkDistanceMiddleY = new TH1F("NewHistogramCrosstalkDistanceMiddleY", "Cube distance of energy deposit from peak Y axis, 15 cubes away from stopping poin.",10,-5,5);

    TH1F *NewHistogramRealPeakEnergyDepositMiddle = new TH1F("NewHistogramRealPeakEnergyDepositMiddle", "Histogram of highest value deposit, 15 cubes away from stopping poin.",100,0,2500);
    
    TH1F *NewHistogramCrosstalkDistanceTypeMiddleX= new TH1F("NewHistogramCrosstalkDistanceTypeMiddleX", "Number of cubes that recieved signal X axis, middle of track",48,0,48); 
    TH1F *NewHistogramCrosstalkDistanceTypeMiddleY= new TH1F("NewHistogramCrosstalkDistanceTypeMiddleY", "Number of cubes that recieved signal Y axis, middle of track",16,0,16);

    TH1F *NewCrosstalkEnergyDepositMiddleCUTGX = new TH1F("NewCrosstalkEnergyDepositMiddleCUTGX", "Crosstalk energy in X plain, 15 cubes away from stopping poin, after CUTG.",200,0,200);
    TH1F *NewCrosstalkEnergyDepositMiddleCUTGY = new TH1F("NewCrosstalkEnergyDepositMiddleCUTGY", "Crosstalk energy in Y plain, 15 cubes away from stopping point, after CUTG.",200,0,200);

    TH1F *NewCrosstalkEnergyDepositMiddleOneCubeCUTGX = new TH1F("NewCrosstalkEnergyDepositMiddleOneCubeCUTGX", "Crosstalk energy in X plain, 15 cube backward, after CUTG only one cube away",50,0,100);
    TH1F *NewCrosstalkEnergyDepositMiddleOneCubeCUTGY = new TH1F("NewCrosstalkEnergyDepositMiddleOneCubeCUTGY", "Crosstalk energy in Y plain, 15 cube backward, after CUTG only, one cube away",50,0,100);

    TH1F *NewCrosstalkEnergyDepositMiddleTwoCubesCUTGX = new TH1F("NewCrosstalkEnergyDepositMiddleTwoCubesCUTGX", "Crosstalk energy in X plain, 15 cube backward, after CUTG only two cubes away",50,0,100);
    TH1F *NewCrosstalkEnergyDepositMiddleTwoCubesCUTGY = new TH1F("NewCrosstalkEnergyDepositMiddleTwoCubesCUTGY", "Crosstalk energy in Y plain, 15 cube backward, after CUTG only, two cubes away",50,0,100);
    
    TH1F *NewCrosstalkEnergyPercentageMiddleCUTGX = new TH1F("NewCrosstalkEnergyPercentageMiddleCUTGX", "Crosstalk energy divided by main deposit in X plain, 15 cubes away from stopping point, after CUTG.",200,0,100);
    TH1F *NewCrosstalkEnergyPercentageMiddleCUTGY = new TH1F("NewCrosstalkEnergyPercentageMiddleCUTGY", "Crosstalk energy divided by main deposit in Y plain, 15 cubes away from stopping point, after CUTG.",200,0,100);
    
    TH1F *NewHistogramCrosstalkDistanceMiddleCUTGX= new TH1F("NewHistogramCrosstalkDistanceMiddleCUTGX", "Cube distance of energy deposit from peak X axis, 15 cubes away from stopping point, after CUTG.",10,-5,5);
    TH1F *NewHistogramCrosstalkDistanceMiddleCUTGY = new TH1F("NewHistogramCrosstalkDistanceMiddleCUTGY", "Cube distance of energy deposit from peak Y axis, 15 cubes away from stopping point, after CUTG.",10,-5,5);

    TH2F *NewEnergyTrigTimeMiddleX = new TH2F("NewEnergyTrigTimeMiddleX","Energy and Time of Trigger X axis, 15 cubes away from stopping point", 100,-100,100,500,0,1500);
    TH2F *NewEnergyTrigTimeMiddleY = new TH2F("NewEnergyTrigTimeMiddleY","Energy and Time of Trigger Y axis, 15 cubes away from stopping point", 100,-100,100,500,0,1500);
    
    TH2F *NewEnergyTrigTimeTestX = new TH2F("NewEnergyTrigTimeTestX","X", 100,-100,100,500,0,1500);
    TH2F *NewEnergyTrigTimeTestY = new TH2F("NewEnergyTrigTimeTestY","Y", 100,-100,100,500,0,1500);

    TH2F *NewEnergyTrigTimeTestUpgradeX = new TH2F("NewEnergyTrigTimeTestUpgradeX","Upgrade X", 100,-100,100,500,0,1500);
    TH2F *NewEnergyTrigTimeTestUpgradeY = new TH2F("NewEnergyTrigTimeTestUpgradeY","Upgrade Y", 100,-100,100,500,0,1500);
    
    TH2F *NewEnergyTrigTimeTestLowX = new TH2F("NewEnergyTrigTimeTestLowX","X low", 100,-100,100,500,0,1500);
    TH2F *NewEnergyTrigTimeTestLowY = new TH2F("NewEnergyTrigTimeTestLowY","Y low", 100,-100,100,500,0,1500);
    
    for(int i=0; i<NumberOfFiles; i++)
    {
        TFile *file = new TFile(filename[i],"READ");
        if ( file->IsOpen() )
        {
            printf("File opened successfully\n");
        }   
        //file->cd();
        
        TH2F* EventsMap_XYClone = (TH2F*) file->Get("EventsMap_XY");
        NewEventsMap_XY->Add(EventsMap_XYClone);
        TH2F* EventsMap_YZClone = (TH2F*) file->Get("EventsMap_YZ");
        NewEventsMap_YZ->Add(EventsMap_YZClone);
        TH2F* EventsMap_XZClone = (TH2F*) file->Get("EventsMap_XZ");
        NewEventsMap_XZ->Add(EventsMap_XZClone);

        TH2F* EnergyTrigTimeAllClone = (TH2F*) file->Get("EnergyTrigTimeAll");
        NewEnergyTrigTimeAll->Add(EnergyTrigTimeAllClone);
        
        TH1F* HistogramHighestEnergyDepositClone = (TH1F*) file->Get("HistogramHighestEnergyDeposit");
        NewHistogramHighestEnergyDeposit->Add(HistogramHighestEnergyDepositClone);
        TH1F* HistogramRealPeakEnergyDepositClone = (TH1F*) file->Get("HistogramRealPeakEnergyDeposit");
        NewHistogramRealPeakEnergyDeposit->Add(HistogramRealPeakEnergyDepositClone);
        
        TH1F* CrosstalkEnergyDepositXClone = (TH1F*) file->Get("CrosstalkEnergyDepositX");
        NewCrosstalkEnergyDepositX->Add(CrosstalkEnergyDepositXClone);
        TH1F* CrosstalkEnergyDepositYClone = (TH1F*) file->Get("CrosstalkEnergyDepositY");
        NewCrosstalkEnergyDepositY->Add(CrosstalkEnergyDepositYClone);
        
        TH1F* CrosstalkEnergyDepositOneCubeXClone = (TH1F*) file->Get("CrosstalkEnergyDepositOneCubeX");
        NewCrosstalkEnergyDepositOneCubeX->Add(CrosstalkEnergyDepositOneCubeXClone);
        TH1F* CrosstalkEnergyDepositOneCubeYClone = (TH1F*) file->Get("CrosstalkEnergyDepositOneCubeY");
        NewCrosstalkEnergyDepositOneCubeY->Add(CrosstalkEnergyDepositOneCubeYClone);
    
        TH1F* CrosstalkEnergyDepositTwoCubesXClone = (TH1F*) file->Get("CrosstalkEnergyDepositTwoCubesX");
        NewCrosstalkEnergyDepositTwoCubesX->Add(CrosstalkEnergyDepositTwoCubesXClone);
        TH1F* CrosstalkEnergyDepositTwoCubesYClone = (TH1F*) file->Get("CrosstalkEnergyDepositTwoCubesY");
        NewCrosstalkEnergyDepositTwoCubesY->Add(CrosstalkEnergyDepositTwoCubesYClone);
        
        TH1F* CrosstalkEnergyDepositPercentageXClone = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageX");
        NewCrosstalkEnergyDepositPercentageX->Add(CrosstalkEnergyDepositPercentageXClone);
        TH1F* CrosstalkEnergyDepositPercentageYClone = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageY");
        NewCrosstalkEnergyDepositPercentageY->Add(CrosstalkEnergyDepositPercentageYClone);
        
        TH1F* CrosstalkEnergyDepositPercentageOneCubeXClone = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageOneCubeX");
        NewCrosstalkEnergyDepositPercentageOneCubeX->Add(CrosstalkEnergyDepositPercentageOneCubeXClone);
        TH1F* CrosstalkEnergyDepositPercentageOneCubeYClone = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageOneCubeY");
        NewCrosstalkEnergyDepositPercentageOneCubeY->Add(CrosstalkEnergyDepositPercentageOneCubeYClone);
        
        TH1F* CrosstalkEnergyDepositPercentageTwoCubesXClone = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageTwoCubesX");
        NewCrosstalkEnergyDepositPercentageTwoCubesX->Add(CrosstalkEnergyDepositPercentageTwoCubesXClone);
        TH1F* CrosstalkEnergyDepositPercentageTwoCubesYClone = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageTwoCubesY");
        NewCrosstalkEnergyDepositPercentageTwoCubesY->Add(CrosstalkEnergyDepositPercentageTwoCubesY);
        
        TH1F* CrosstalkEnergyDepositPercentageSecondCubeNewXClone = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageSecondCubeNewX");
        NewCrosstalkEnergyDepositPercentageSecondCubeNewX->Add(CrosstalkEnergyDepositPercentageSecondCubeNewXClone);
        
        TH1F* CrosstalkEnergyDepositCUTGXClone = (TH1F*) file->Get("CrosstalkEnergyDepositCUTGX");
        NewCrosstalkEnergyDepositCUTGX->Add(CrosstalkEnergyDepositCUTGXClone);
        TH1F* CrosstalkEnergyDepositCUTGYClone = (TH1F*) file->Get("CrosstalkEnergyDepositCUTGY");
        NewCrosstalkEnergyDepositCUTGY->Add(CrosstalkEnergyDepositCUTGYClone);
        
        TH1F* CrosstalkEnergyDepositOneCubeCUTGXClone = (TH1F*) file->Get("CrosstalkEnergyDepositOneCubeCUTGX");
        NewCrosstalkEnergyDepositOneCubeCUTGX->Add(CrosstalkEnergyDepositOneCubeCUTGXClone);
        TH1F* CrosstalkEnergyDepositOneCubeCUTGYClone = (TH1F*) file->Get("CrosstalkEnergyDepositOneCubeCUTGY");
        NewCrosstalkEnergyDepositOneCubeCUTGY->Add(CrosstalkEnergyDepositOneCubeCUTGYClone);
        
        TH1F* CrosstalkEnergyDepositTwoCubesCUTGXClone = (TH1F*) file->Get("CrosstalkEnergyDepositTwoCubesCUTGX");
        NewCrosstalkEnergyDepositTwoCubesCUTGX->Add(CrosstalkEnergyDepositTwoCubesCUTGXClone);
        TH1F* CrosstalkEnergyDepositTwoCubesCUTGYClone = (TH1F*) file->Get("CrosstalkEnergyDepositTwoCubesCUTGY");
        NewCrosstalkEnergyDepositTwoCubesCUTGY->Add(CrosstalkEnergyDepositTwoCubesCUTGYClone);
        
        TH1F* StoppingPointLocationClone = (TH1F*) file->Get("StoppingPointLocation");
        NewStoppingPointLocation->Add(StoppingPointLocationClone);

        TH1F* HistogramCrosstalkDistanceXClone = (TH1F*) file->Get("HistogramCrosstalkDistanceX");
        NewHistogramCrosstalkDistanceX->Add(HistogramCrosstalkDistanceXClone);
        TH1F* HistogramCrosstalkDistanceYClone = (TH1F*) file->Get("HistogramCrosstalkDistanceY");
        NewHistogramCrosstalkDistanceY->Add(HistogramCrosstalkDistanceYClone);
        
        TH1F* HistogramCrosstalkDistanceCUTGXClone = (TH1F*) file->Get("HistogramCrosstalkDistanceCUTGX");
        NewHistogramCrosstalkDistanceCUTGX->Add(HistogramCrosstalkDistanceCUTGXClone);
        TH1F* HistogramCrosstalkDistanceCUTGYClone = (TH1F*) file->Get("HistogramCrosstalkDistanceCUTGY");
        NewHistogramCrosstalkDistanceCUTGY->Add(HistogramCrosstalkDistanceCUTGYClone);
        
        TH1F* CrosstalkEnergyDepositPercentageCUTGXClone = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageCUTGX");
        NewCrosstalkEnergyDepositPercentageCUTGX->Add(CrosstalkEnergyDepositPercentageCUTGXClone);
        TH1F* CrosstalkEnergyDepositPercentageCUTGYClone = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageCUTGY");
        NewCrosstalkEnergyDepositPercentageCUTGY->Add(CrosstalkEnergyDepositPercentageCUTGYClone);
        
        TH1F* CrosstalkEnergyDepositRestrictedXClone = (TH1F*) file->Get("CrosstalkEnergyDepositRestrictedX");
        NewCrosstalkEnergyDepositRestrictedX->Add(CrosstalkEnergyDepositRestrictedXClone);
        TH1F* CrosstalkEnergyDepositRestrictedYClone = (TH1F*) file->Get("CrosstalkEnergyDepositRestrictedY");
        NewCrosstalkEnergyDepositRestrictedY->Add(CrosstalkEnergyDepositRestrictedYClone);
        
        TH1F* HistogramCrosstalkDistanceEnergyHigherThanXClone = (TH1F*) file->Get("HistogramCrosstalkDistanceEnergyHigherThanX");
        NewHistogramCrosstalkDistanceEnergyHigherThanX->Add(HistogramCrosstalkDistanceEnergyHigherThanXClone);
        TH1F* HistogramCrosstalkDistanceEnergyHigherThanYClone = (TH1F*) file->Get("HistogramCrosstalkDistanceEnergyHigherThanY");
        NewHistogramCrosstalkDistanceEnergyHigherThanY->Add(HistogramCrosstalkDistanceEnergyHigherThanYClone);
        
        TH1F* HistogramCrosstalkDistanceCutXClone = (TH1F*) file->Get("HistogramCrosstalkDistanceCutX");
        NewHistogramCrosstalkDistanceCutX->Add(HistogramCrosstalkDistanceCutXClone);
        TH1F* HistogramCrosstalkDistanceCutYClone = (TH1F*) file->Get("HistogramCrosstalkDistanceCutY");
        NewHistogramCrosstalkDistanceCutY->Add(HistogramCrosstalkDistanceCutYClone);
        
        TH1F* HistogramCrosstalkDistanceTypeXClone = (TH1F*) file->Get("HistogramCrosstalkDistanceTypeX");
        NewHistogramCrosstalkDistanceTypeX->Add(HistogramCrosstalkDistanceTypeXClone);
        TH1F* HistogramCrosstalkDistanceTypeYClone = (TH1F*) file->Get("HistogramCrosstalkDistanceTypeY");
        NewHistogramCrosstalkDistanceTypeY->Add(HistogramCrosstalkDistanceTypeYClone);
        
        TH2F* EnergyTrigTimeXClone = (TH2F*) file->Get("EnergyTrigTimeX");
        NewEnergyTrigTimeX->Add(EnergyTrigTimeXClone);
        TH2F* EnergyTrigTimeYClone = (TH2F*) file->Get("EnergyTrigTimeY");
        NewEnergyTrigTimeY->Add(EnergyTrigTimeYClone);
        
        TH2F* EnergyTrigTimeCrosstalkXClone = (TH2F*) file->Get("EnergyTrigTimeCrosstalkX");
        NewEnergyTrigTimeCrosstalkX->Add(EnergyTrigTimeCrosstalkXClone);
        TH2F* EnergyTrigTimeCrosstalkYClone = (TH2F*) file->Get("EnergyTrigTimeCrosstalkY");
        NewEnergyTrigTimeCrosstalkY->Add(EnergyTrigTimeCrosstalkYClone);
        
        TH2F* EnergyTrigTimeSignalXClone = (TH2F*) file->Get("EnergyTrigTimeSignalX");
        NewEnergyTrigTimeSignalX->Add(EnergyTrigTimeSignalXClone);
        TH2F* EnergyTrigTimeSignalYClone = (TH2F*) file->Get("EnergyTrigTimeSignalY");
        NewEnergyTrigTimeSignalY->Add(EnergyTrigTimeSignalYClone);
        
        TH2F* EnergyTrigTimeCUTGXClone = (TH2F*) file->Get("EnergyTrigTimeCUTGX");
        NewEnergyTrigTimeCUTGX->Add(EnergyTrigTimeCUTGXClone);
        TH2F* EnergyTrigTimeCUTGYClone = (TH2F*) file->Get("EnergyTrigTimeCUTGY");
        NewEnergyTrigTimeCUTGY->Add(EnergyTrigTimeCUTGYClone);
        
        TH1F* CrosstalkEnergyDepositMinus1XClone = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1X");
        NewCrosstalkEnergyDepositMinus1X->Add(CrosstalkEnergyDepositMinus1XClone);
        TH1F* CrosstalkEnergyDepositMinus1YClone = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1Y");
        NewCrosstalkEnergyDepositMinus1Y->Add(CrosstalkEnergyDepositMinus1YClone);
        
        TH1F* CrosstalkEnergyDepositMinus1OneCubeXClone = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1OneCubeX");
        NewCrosstalkEnergyDepositMinus1OneCubeX->Add(CrosstalkEnergyDepositMinus1OneCubeXClone);
        TH1F* CrosstalkEnergyDepositMinus1OneCubeYClone = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1OneCubeY");
        NewCrosstalkEnergyDepositMinus1OneCubeY->Add(CrosstalkEnergyDepositMinus1OneCubeYClone);
        
        TH1F* CrosstalkEnergyDepositMinus1TwoCubesXClone = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1TwoCubesX");
        NewCrosstalkEnergyDepositMinus1TwoCubesX->Add(CrosstalkEnergyDepositMinus1TwoCubesXClone);
        TH1F* CrosstalkEnergyDepositMinus1TwoCubesYClone = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1TwoCubesY");
        NewCrosstalkEnergyDepositMinus1TwoCubesY->Add(CrosstalkEnergyDepositMinus1TwoCubesYClone);
        
        TH1F* CrosstalkEnergyPercentageMinus1XClone = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1X");
        NewCrosstalkEnergyPercentageMinus1X->Add(CrosstalkEnergyPercentageMinus1XClone);
        TH1F* CrosstalkEnergyPercentageMinus1YClone = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1Y");
        NewCrosstalkEnergyPercentageMinus1Y->Add(CrosstalkEnergyPercentageMinus1YClone);
        
        TH1F* CrosstalkEnergyPercentageMinus1OneCubeXClone = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1OneCubeX");
        NewCrosstalkEnergyPercentageMinus1OneCubeX->Add(CrosstalkEnergyPercentageMinus1OneCubeXClone);
        TH1F* CrosstalkEnergyPercentageMinus1OneCubeYClone = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1OneCubeY");
        NewCrosstalkEnergyPercentageMinus1OneCubeY->Add(CrosstalkEnergyPercentageMinus1OneCubeYClone);
        
        TH1F* CrosstalkEnergyPercentageMinus1TwoCubesXClone = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1TwoCubesX");
        NewCrosstalkEnergyPercentageMinus1TwoCubesX->Add(CrosstalkEnergyPercentageMinus1TwoCubesXClone);
        TH1F* CrosstalkEnergyPercentageMinus1TwoCubesYClone = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1TwoCubesY");
        NewCrosstalkEnergyPercentageMinus1TwoCubesY->Add(CrosstalkEnergyPercentageMinus1TwoCubesYClone);
        
        TH1F* CrosstalkEnergyDepositPercentageMinus1SecondCubeNewXClone = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageMinus1SecondCubeNewX");
        NewCrosstalkEnergyDepositPercentageMinus1SecondCubeNewX->Add(CrosstalkEnergyDepositPercentageMinus1SecondCubeNewXClone);
        
        TH1F* HistogramCrosstalkDistanceMinus1XClone = (TH1F*) file->Get("HistogramCrosstalkDistanceMinus1X");
        NewHistogramCrosstalkDistanceMinus1X->Add(HistogramCrosstalkDistanceMinus1XClone);
        TH1F* HistogramCrosstalkDistanceMinus1YClone = (TH1F*) file->Get("HistogramCrosstalkDistanceMinus1Y");
        NewHistogramCrosstalkDistanceMinus1Y->Add(HistogramCrosstalkDistanceMinus1YClone);
        
        TH1F* CrosstalkEnergyDepositMinus1CUTGXClone = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1CUTGX");
        NewCrosstalkEnergyDepositMinus1CUTGX->Add(CrosstalkEnergyDepositMinus1CUTGXClone);
        TH1F* CrosstalkEnergyDepositMinus1CUTGYClone = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1CUTGY");
        NewCrosstalkEnergyDepositMinus1CUTGY->Add(CrosstalkEnergyDepositMinus1CUTGYClone);
        
        TH1F* CrosstalkEnergyDepositMinus1OneCubeCUTGXClone = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1OneCubeCUTGX");
        NewCrosstalkEnergyDepositMinus1OneCubeCUTGX->Add(CrosstalkEnergyDepositMinus1OneCubeCUTGXClone);
        TH1F* CrosstalkEnergyDepositMinus1OneCubeCUTGYClone = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1OneCubeCUTGY");
        NewCrosstalkEnergyDepositMinus1OneCubeCUTGY->Add(CrosstalkEnergyDepositMinus1OneCubeCUTGYClone);
        
        TH1F* CrosstalkEnergyDepositMinus1TwoCubesCUTGXClone = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1TwoCubesCUTGX");
        NewCrosstalkEnergyDepositMinus1TwoCubesCUTGX->Add(CrosstalkEnergyDepositMinus1TwoCubesCUTGXClone);
        TH1F* CrosstalkEnergyDepositMinus1TwoCubesCUTGYClone = (TH1F*) file->Get("CrosstalkEnergyDepositMinus1TwoCubesCUTGY");
        NewCrosstalkEnergyDepositMinus1TwoCubesCUTGY->Add(CrosstalkEnergyDepositMinus1TwoCubesCUTGYClone);
        
        TH1F* CrosstalkEnergyPercentageMinus1CUTGXClone = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1CUTGX");
        NewCrosstalkEnergyPercentageMinus1CUTGX->Add(CrosstalkEnergyPercentageMinus1CUTGXClone);
        TH1F* CrosstalkEnergyPercentageMinus1CUTGYClone = (TH1F*) file->Get("CrosstalkEnergyPercentageMinus1CUTGY");
        NewCrosstalkEnergyPercentageMinus1CUTGY->Add(CrosstalkEnergyPercentageMinus1CUTGYClone);
        
        TH1F* HistogramCrosstalkDistanceMinus1CUTGXClone = (TH1F*) file->Get("HistogramCrosstalkDistanceMinus1CUTGX");
        NewHistogramCrosstalkDistanceMinus1CUTGX->Add(HistogramCrosstalkDistanceMinus1CUTGXClone);
        TH1F* HistogramCrosstalkDistanceMinus1CUTGYClone = (TH1F*) file->Get("HistogramCrosstalkDistanceMinus1CUTGY");
        NewHistogramCrosstalkDistanceMinus1CUTGY->Add(HistogramCrosstalkDistanceMinus1CUTGYClone);
        
        TH1F* HistogramRealPeakEnergyDepositMinus1Clone = (TH1F*) file->Get("HistogramRealPeakEnergyDepositMinus1");
        NewHistogramRealPeakEnergyDepositMinus1->Add(HistogramRealPeakEnergyDepositMinus1Clone);
        
        TH1F* HistogramCrosstalkDistanceTypeMinus1XClone = (TH1F*) file->Get("HistogramCrosstalkDistanceTypeMinus1X");
        NewHistogramCrosstalkDistanceTypeMinus1X->Add(HistogramCrosstalkDistanceTypeMinus1XClone);
        TH1F* HistogramCrosstalkDistanceTypeMinus1YClone = (TH1F*) file->Get("HistogramCrosstalkDistanceTypeMinus1Y");
        NewHistogramCrosstalkDistanceTypeMinus1Y->Add(HistogramCrosstalkDistanceTypeMinus1YClone);
        
        TH2F* EnergyTrigTimeMinus1XClone = (TH2F*) file->Get("EnergyTrigTimeMinus1X");
        NewEnergyTrigTimeMinus1X->Add(EnergyTrigTimeMinus1XClone);
        TH2F* EnergyTrigTimeMinus1YClone = (TH2F*) file->Get("EnergyTrigTimeMinus1Y");
        NewEnergyTrigTimeMinus1Y->Add(EnergyTrigTimeMinus1YClone);
        
        TH1F* CrosstalkEnergyDepositMiddleXClone = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleX");
        NewCrosstalkEnergyDepositMiddleX->Add(CrosstalkEnergyDepositMiddleXClone);
        TH1F* CrosstalkEnergyDepositMiddleYClone = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleY");
        NewCrosstalkEnergyDepositMiddleY->Add(CrosstalkEnergyDepositMiddleYClone);
        
        TH1F* CrosstalkEnergyDepositMiddleOneCubeXClone = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleOneCubeX");
        NewCrosstalkEnergyDepositMiddleOneCubeX->Add(CrosstalkEnergyDepositMiddleOneCubeXClone);
        TH1F* CrosstalkEnergyDepositMiddleOneCubeYClone = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleOneCubeY");
        NewCrosstalkEnergyDepositMiddleOneCubeY->Add(CrosstalkEnergyDepositMiddleOneCubeYClone);
        
        TH1F* CrosstalkEnergyDepositMiddleTwoCubesXClone = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleTwoCubesX");
        NewCrosstalkEnergyDepositMiddleTwoCubesX->Add(CrosstalkEnergyDepositMiddleTwoCubesXClone);
        TH1F* CrosstalkEnergyDepositMiddleTwoCubesYClone = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleTwoCubesY");
        NewCrosstalkEnergyDepositMiddleTwoCubesY->Add(CrosstalkEnergyDepositMiddleTwoCubesYClone);
        
        TH1F* CrosstalkEnergyPercentageMiddleXClone = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleX");
        NewCrosstalkEnergyPercentageMiddleX->Add(CrosstalkEnergyPercentageMiddleXClone);
        TH1F* CrosstalkEnergyPercentageMiddleYClone = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleY");
        NewCrosstalkEnergyPercentageMiddleY->Add(CrosstalkEnergyPercentageMiddleYClone);
        
        TH1F* CrosstalkEnergyPercentageMiddleOneCubeXClone = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleOneCubeX");
        NewCrosstalkEnergyPercentageMiddleOneCubeX->Add(CrosstalkEnergyPercentageMiddleOneCubeXClone);
        TH1F* CrosstalkEnergyPercentageMiddleOneCubeYClone = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleOneCubeY");
        NewCrosstalkEnergyPercentageMiddleOneCubeY->Add(CrosstalkEnergyPercentageMiddleOneCubeYClone);
        
        TH1F* CrosstalkEnergyPercentageMiddleTwoCubesXClone = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleTwoCubesX");
        NewCrosstalkEnergyPercentageMiddleTwoCubesX->Add(CrosstalkEnergyPercentageMiddleTwoCubesXClone);
        TH1F* CrosstalkEnergyPercentageMiddleTwoCubesYClone = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleTwoCubesY");
        NewCrosstalkEnergyPercentageMiddleTwoCubesY->Add(CrosstalkEnergyPercentageMiddleTwoCubesYClone);
        
        TH1F* CrosstalkEnergyDepositPercentageMiddleSecondCubeNewXClone = (TH1F*) file->Get("CrosstalkEnergyDepositPercentageMiddleSecondCubeNewX");
        NewCrosstalkEnergyDepositPercentageMiddleSecondCubeNewX->Add(CrosstalkEnergyDepositPercentageMiddleSecondCubeNewXClone);
        
        TH1F* HistogramCrosstalkDistanceMiddleXClone = (TH1F*) file->Get("HistogramCrosstalkDistanceMiddleX");
        NewHistogramCrosstalkDistanceMiddleX->Add(HistogramCrosstalkDistanceMiddleXClone);
        TH1F* HistogramCrosstalkDistanceMiddleYClone = (TH1F*) file->Get("HistogramCrosstalkDistanceMiddleY");
        NewHistogramCrosstalkDistanceMiddleY->Add(HistogramCrosstalkDistanceMiddleYClone);
        
        TH1F* NewHistogramRealPeakEnergyDepositMiddleClone = (TH1F*) file->Get("HistogramRealPeakEnergyDepositMiddle");
        NewHistogramRealPeakEnergyDepositMiddle->Add(NewHistogramRealPeakEnergyDepositMiddleClone);
        
        TH1F* HistogramCrosstalkDistanceTypeMiddleXClone = (TH1F*) file->Get("HistogramCrosstalkDistanceTypeMiddleX");
        NewHistogramCrosstalkDistanceTypeMiddleX->Add(HistogramCrosstalkDistanceTypeMiddleXClone);
        TH1F* HistogramCrosstalkDistanceTypeMiddleYClone = (TH1F*) file->Get("HistogramCrosstalkDistanceTypeMiddleY");
        NewHistogramCrosstalkDistanceTypeMiddleY->Add(HistogramCrosstalkDistanceTypeMiddleYClone);
        
        TH1F* CrosstalkEnergyDepositMiddleCUTGXClone = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleCUTGX");
        NewCrosstalkEnergyDepositMiddleCUTGX->Add(CrosstalkEnergyDepositMiddleCUTGXClone);
        TH1F* CrosstalkEnergyDepositMiddleCUTGYClone = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleCUTGY");
        NewCrosstalkEnergyDepositMiddleCUTGY->Add(CrosstalkEnergyDepositMiddleCUTGYClone);
        
        TH1F* CrosstalkEnergyDepositMiddleOneCubeCUTGXClone = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleOneCubeCUTGX");
        NewCrosstalkEnergyDepositMiddleOneCubeCUTGX->Add(CrosstalkEnergyDepositMiddleOneCubeCUTGXClone);
        TH1F* CrosstalkEnergyDepositMiddleOneCubeCUTGYClone = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleOneCubeCUTGY");
        NewCrosstalkEnergyDepositMiddleOneCubeCUTGY->Add(CrosstalkEnergyDepositMiddleOneCubeCUTGYClone);
        
        TH1F* CrosstalkEnergyDepositMiddleTwoCubesCUTGXClone = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleTwoCubesCUTGX");
        NewCrosstalkEnergyDepositMiddleTwoCubesCUTGX->Add(CrosstalkEnergyDepositMiddleTwoCubesCUTGXClone);
        TH1F* CrosstalkEnergyDepositMiddleTwoCubesCUTGYClone = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleTwoCubesCUTGY");
        NewCrosstalkEnergyDepositMiddleTwoCubesCUTGY->Add(CrosstalkEnergyDepositMiddleTwoCubesCUTGYClone);
        
        TH1F* CrosstalkEnergyPercentageMiddleCUTGXClone = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleCUTGX");
        NewCrosstalkEnergyPercentageMiddleCUTGX->Add(CrosstalkEnergyPercentageMiddleCUTGXClone);
        TH1F* CrosstalkEnergyPercentageMiddleCUTGYClone = (TH1F*) file->Get("CrosstalkEnergyPercentageMiddleCUTGY");
        NewCrosstalkEnergyPercentageMiddleCUTGY->Add(CrosstalkEnergyPercentageMiddleCUTGYClone);
        
        TH1F* HistogramCrosstalkDistanceMiddleCUTGXClone = (TH1F*) file->Get("HistogramCrosstalkDistanceMiddleCUTGX");
        NewHistogramCrosstalkDistanceMiddleCUTGX->Add(HistogramCrosstalkDistanceMiddleCUTGXClone);
        TH1F* HistogramCrosstalkDistanceMiddleCUTGYClone = (TH1F*) file->Get("HistogramCrosstalkDistanceMiddleCUTGY");
        NewHistogramCrosstalkDistanceMiddleCUTGY->Add(HistogramCrosstalkDistanceMiddleCUTGYClone);
        
        TH2F* EnergyTrigTimeMiddleXClone = (TH2F*) file->Get("EnergyTrigTimeMiddleX");
        NewEnergyTrigTimeMiddleX->Add(EnergyTrigTimeMiddleXClone);
        TH2F* EnergyTrigTimeMiddleYClone = (TH2F*) file->Get("EnergyTrigTimeMiddleY");
        NewEnergyTrigTimeMiddleY->Add(EnergyTrigTimeMiddleYClone);
        
        TH2F* EnergyTrigTimeTestXClone = (TH2F*) file->Get("EnergyTrigTimeTestX");
        NewEnergyTrigTimeTestX->Add(EnergyTrigTimeTestXClone);
        TH2F* EnergyTrigTimeTestYClone = (TH2F*) file->Get("EnergyTrigTimeTestY");
        NewEnergyTrigTimeTestY->Add(EnergyTrigTimeTestYClone);
        
        TH2F* EnergyTrigTimeTestUpgradeXClone = (TH2F*) file->Get("EnergyTrigTimeTestUpgradeX");
        NewEnergyTrigTimeTestUpgradeX->Add(EnergyTrigTimeTestUpgradeXClone);
        TH2F* EnergyTrigTimeTestUpgradeYClone = (TH2F*) file->Get("EnergyTrigTimeTestUpgradeY");
        NewEnergyTrigTimeTestUpgradeY->Add(EnergyTrigTimeTestUpgradeYClone);
        
        TH2F* EnergyTrigTimeTestLowXClone = (TH2F*) file->Get("EnergyTrigTimeTestLowX");
        NewEnergyTrigTimeTestLowX->Add(EnergyTrigTimeTestLowXClone);
        TH2F* EnergyTrigTimeTestLowYClone = (TH2F*) file->Get("EnergyTrigTimeTestLowY");
        NewEnergyTrigTimeTestLowY->Add(EnergyTrigTimeTestLowYClone);
        
        delete EventsMap_XYClone;
        delete EventsMap_YZClone;
        delete EventsMap_XZClone;
        delete EnergyTrigTimeAllClone;
        delete HistogramHighestEnergyDepositClone;
        delete HistogramRealPeakEnergyDepositClone;
        delete CrosstalkEnergyDepositXClone;
        delete CrosstalkEnergyDepositYClone;
        delete CrosstalkEnergyDepositOneCubeXClone;
        delete CrosstalkEnergyDepositOneCubeYClone;
        delete CrosstalkEnergyDepositTwoCubesXClone;
        delete CrosstalkEnergyDepositTwoCubesYClone;
        delete CrosstalkEnergyDepositPercentageXClone;
        delete CrosstalkEnergyDepositPercentageYClone;
        delete CrosstalkEnergyDepositPercentageOneCubeXClone;
        delete CrosstalkEnergyDepositPercentageOneCubeYClone;
        delete CrosstalkEnergyDepositPercentageTwoCubesXClone;
        delete CrosstalkEnergyDepositPercentageTwoCubesYClone;
        delete CrosstalkEnergyDepositPercentageSecondCubeNewXClone;
        delete CrosstalkEnergyDepositCUTGXClone;
        delete CrosstalkEnergyDepositCUTGYClone;
        delete CrosstalkEnergyDepositOneCubeCUTGXClone;
        delete CrosstalkEnergyDepositOneCubeCUTGYClone;
        delete CrosstalkEnergyDepositTwoCubesCUTGXClone;
        delete CrosstalkEnergyDepositTwoCubesCUTGYClone;
        delete StoppingPointLocationClone;
        delete HistogramCrosstalkDistanceXClone;
        delete HistogramCrosstalkDistanceYClone;
        delete HistogramCrosstalkDistanceCUTGXClone;
        delete HistogramCrosstalkDistanceCUTGYClone;
        delete CrosstalkEnergyDepositPercentageCUTGXClone;
        delete CrosstalkEnergyDepositPercentageCUTGYClone;
        delete CrosstalkEnergyDepositRestrictedXClone;
        delete CrosstalkEnergyDepositRestrictedYClone;
        delete HistogramCrosstalkDistanceEnergyHigherThanXClone;
        delete HistogramCrosstalkDistanceEnergyHigherThanYClone;
        delete HistogramCrosstalkDistanceCutXClone;
        delete HistogramCrosstalkDistanceCutYClone;
        delete HistogramCrosstalkDistanceTypeXClone;
        delete HistogramCrosstalkDistanceTypeYClone;
        delete EnergyTrigTimeXClone;
        delete EnergyTrigTimeYClone;
        delete EnergyTrigTimeCrosstalkXClone;
        delete EnergyTrigTimeCrosstalkYClone;
        delete EnergyTrigTimeSignalXClone;
        delete EnergyTrigTimeSignalYClone;
        delete EnergyTrigTimeCUTGXClone;
        delete EnergyTrigTimeCUTGYClone;
        delete CrosstalkEnergyDepositMinus1XClone;
        delete CrosstalkEnergyDepositMinus1YClone;
        delete CrosstalkEnergyDepositMinus1OneCubeXClone;
        delete CrosstalkEnergyDepositMinus1OneCubeYClone;
        delete CrosstalkEnergyDepositMinus1TwoCubesXClone;
        delete CrosstalkEnergyDepositMinus1TwoCubesYClone;
        delete CrosstalkEnergyPercentageMinus1XClone;
        delete CrosstalkEnergyPercentageMinus1YClone;
        delete CrosstalkEnergyPercentageMinus1OneCubeXClone;
        delete CrosstalkEnergyPercentageMinus1OneCubeYClone;
        delete CrosstalkEnergyPercentageMinus1TwoCubesXClone;
        delete CrosstalkEnergyPercentageMinus1TwoCubesYClone;
        delete CrosstalkEnergyDepositPercentageMinus1SecondCubeNewXClone;
        delete HistogramCrosstalkDistanceMinus1XClone;
        delete HistogramCrosstalkDistanceMinus1YClone;
        delete CrosstalkEnergyDepositMinus1CUTGXClone;
        delete CrosstalkEnergyDepositMinus1CUTGYClone;
        delete CrosstalkEnergyDepositMinus1OneCubeCUTGXClone;
        delete CrosstalkEnergyDepositMinus1OneCubeCUTGYClone;
        delete CrosstalkEnergyDepositMinus1TwoCubesCUTGXClone;
        delete CrosstalkEnergyDepositMinus1TwoCubesCUTGYClone;
        delete CrosstalkEnergyPercentageMinus1CUTGXClone;
        delete CrosstalkEnergyPercentageMinus1CUTGYClone;
        delete HistogramCrosstalkDistanceMinus1CUTGXClone;
        delete HistogramCrosstalkDistanceMinus1CUTGYClone;
        delete HistogramRealPeakEnergyDepositMinus1Clone;
        delete HistogramCrosstalkDistanceTypeMinus1XClone;
        delete HistogramCrosstalkDistanceTypeMinus1YClone;
        delete EnergyTrigTimeMinus1XClone;
        delete EnergyTrigTimeMinus1YClone;
        delete CrosstalkEnergyDepositMiddleXClone;
        delete CrosstalkEnergyDepositMiddleYClone;
        delete CrosstalkEnergyDepositMiddleOneCubeXClone;
        delete CrosstalkEnergyDepositMiddleOneCubeYClone;
        delete CrosstalkEnergyDepositMiddleTwoCubesXClone;
        delete CrosstalkEnergyDepositMiddleTwoCubesYClone;
        delete CrosstalkEnergyPercentageMiddleXClone;
        delete CrosstalkEnergyPercentageMiddleYClone;
        delete CrosstalkEnergyPercentageMiddleOneCubeXClone;
        delete CrosstalkEnergyPercentageMiddleOneCubeYClone;
        delete CrosstalkEnergyPercentageMiddleTwoCubesXClone;
        delete CrosstalkEnergyPercentageMiddleTwoCubesYClone;
        delete CrosstalkEnergyDepositPercentageMiddleSecondCubeNewXClone;
        delete HistogramCrosstalkDistanceMiddleXClone;
        delete HistogramCrosstalkDistanceMiddleYClone;
        delete NewHistogramRealPeakEnergyDepositMiddleClone;
        delete HistogramCrosstalkDistanceTypeMiddleXClone;
        delete HistogramCrosstalkDistanceTypeMiddleYClone;
        delete CrosstalkEnergyDepositMiddleCUTGXClone;
        delete CrosstalkEnergyDepositMiddleCUTGYClone;
        delete CrosstalkEnergyDepositMiddleOneCubeCUTGXClone;
        delete CrosstalkEnergyDepositMiddleOneCubeCUTGYClone;
        delete CrosstalkEnergyDepositMiddleTwoCubesCUTGXClone;
        delete CrosstalkEnergyDepositMiddleTwoCubesCUTGYClone;
        delete CrosstalkEnergyPercentageMiddleCUTGXClone;
        delete CrosstalkEnergyPercentageMiddleCUTGYClone;
        delete HistogramCrosstalkDistanceMiddleCUTGXClone;
        delete HistogramCrosstalkDistanceMiddleCUTGYClone;
        delete EnergyTrigTimeMiddleXClone;
        delete EnergyTrigTimeMiddleYClone;
        delete EnergyTrigTimeTestXClone;
        delete EnergyTrigTimeTestYClone;
        delete EnergyTrigTimeTestUpgradeXClone;
        delete EnergyTrigTimeTestUpgradeYClone;
        delete EnergyTrigTimeTestLowXClone;
        delete EnergyTrigTimeTestLowYClone;
        
        file->Close();
        delete file;
    }
    
    TH2F *EventsMap_XY = (TH2F*)(NewEventsMap_XY->Clone("EventsMap_XY"));
    TH2F *EventsMap_YZ = (TH2F*)(NewEventsMap_YZ->Clone("EventsMap_YZ"));
    TH2F *EventsMap_XZ = (TH2F*)(NewEventsMap_XZ->Clone("EventsMap_XZ"));

    TH2F *EnergyTrigTimeAll = (TH2F*)(NewEnergyTrigTimeAll->Clone("EnergyTrigTimeAll"));
    EnergyTrigTimeAll->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeAll->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH1F *HistogramHighestEnergyDeposit = (TH1F*)(NewHistogramHighestEnergyDeposit->Clone("HistogramHighestEnergyDeposit"));
    HistogramHighestEnergyDeposit->GetYaxis()->SetTitle("Number of events");
    HistogramHighestEnergyDeposit->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *HistogramRealPeakEnergyDeposit = (TH1F*)(NewHistogramRealPeakEnergyDeposit->Clone("HistogramRealPeakEnergyDeposit"));
    HistogramRealPeakEnergyDeposit->GetYaxis()->SetTitle("Number of events");
    HistogramRealPeakEnergyDeposit->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositX = (TH1F*)(NewCrosstalkEnergyDepositX->Clone("CrosstalkEnergyDepositX"));
    CrosstalkEnergyDepositX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositY = (TH1F*)(NewCrosstalkEnergyDepositY->Clone("CrosstalkEnergyDepositY"));
    CrosstalkEnergyDepositY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositOneCubeX = (TH1F*)(NewCrosstalkEnergyDepositOneCubeX->Clone("CrosstalkEnergyDepositOneCubeX"));
    CrosstalkEnergyDepositOneCubeX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositOneCubeX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositOneCubeY = (TH1F*)(NewCrosstalkEnergyDepositOneCubeY->Clone("CrosstalkEnergyDepositOneCubeY"));
    CrosstalkEnergyDepositOneCubeY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositOneCubeY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositTwoCubesX = (TH1F*)(NewCrosstalkEnergyDepositTwoCubesX->Clone("CrosstalkEnergyDepositTwoCubesX"));
    CrosstalkEnergyDepositTwoCubesX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositTwoCubesX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositTwoCubesY = (TH1F*)(NewCrosstalkEnergyDepositTwoCubesY->Clone("CrosstalkEnergyDepositTwoCubesY"));
    CrosstalkEnergyDepositTwoCubesY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositTwoCubesY->GetXaxis()->SetTitle("Energy [p.e.]");
      
    TH1F *CrosstalkEnergyDepositPercentageX = (TH1F*)(NewCrosstalkEnergyDepositPercentageX->Clone("CrosstalkEnergyDepositPercentageX"));
    CrosstalkEnergyDepositPercentageX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageX->GetXaxis()->SetTitle("Percentage %");
    TH1F *CrosstalkEnergyDepositPercentageY = (TH1F*)(NewCrosstalkEnergyDepositPercentageY->Clone("CrosstalkEnergyDepositPercentageY"));
    CrosstalkEnergyDepositPercentageY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageY->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositPercentageOneCubeX = (TH1F*)(NewCrosstalkEnergyDepositPercentageOneCubeX->Clone("CrosstalkEnergyDepositPercentageOneCubeX"));
    CrosstalkEnergyDepositPercentageOneCubeX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageOneCubeX->GetXaxis()->SetTitle("Percentage %");
    TH1F *CrosstalkEnergyDepositPercentageOneCubeY = (TH1F*)(NewCrosstalkEnergyDepositPercentageOneCubeY->Clone("CrosstalkEnergyDepositPercentageOneCubeY"));
    CrosstalkEnergyDepositPercentageOneCubeY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageOneCubeY->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositPercentageTwoCubesX = (TH1F*)(NewCrosstalkEnergyDepositPercentageTwoCubesX->Clone("CrosstalkEnergyDepositPercentageTwoCubesX"));
    CrosstalkEnergyDepositPercentageTwoCubesX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageTwoCubesX->GetXaxis()->SetTitle("Percentage %");
    TH1F *CrosstalkEnergyDepositPercentageTwoCubesY = (TH1F*)(NewCrosstalkEnergyDepositPercentageTwoCubesY->Clone("CrosstalkEnergyDepositPercentageTwoCubesY"));
    CrosstalkEnergyDepositPercentageTwoCubesY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageTwoCubesY->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositPercentageSecondCubeNewX = (TH1F*)(NewCrosstalkEnergyDepositPercentageSecondCubeNewX->Clone("CrosstalkEnergyDepositPercentageSecondCubeNewX"));
    CrosstalkEnergyDepositPercentageSecondCubeNewX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageSecondCubeNewX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositCUTGX = (TH1F*)(NewCrosstalkEnergyDepositCUTGX->Clone("CrosstalkEnergyDepositCUTGX"));
    CrosstalkEnergyDepositCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositCUTGX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositCUTGY = (TH1F*)(NewCrosstalkEnergyDepositCUTGY->Clone("CrosstalkEnergyDepositCUTGY"));
    CrosstalkEnergyDepositCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositCUTGY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositOneCubeCUTGX = (TH1F*)(NewCrosstalkEnergyDepositOneCubeCUTGX->Clone("CrosstalkEnergyDepositOneCubeCUTGX"));
    CrosstalkEnergyDepositOneCubeCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositOneCubeCUTGX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositOneCubeCUTGY = (TH1F*)(NewCrosstalkEnergyDepositOneCubeCUTGY->Clone("CrosstalkEnergyDepositOneCubeCUTGY"));
    CrosstalkEnergyDepositOneCubeCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositOneCubeCUTGY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositTwoCubesCUTGX = (TH1F*)(NewCrosstalkEnergyDepositTwoCubesCUTGX->Clone("CrosstalkEnergyDepositTwoCubesCUTGX"));
    CrosstalkEnergyDepositTwoCubesCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositTwoCubesCUTGX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositTwoCubesCUTGY = (TH1F*)(NewCrosstalkEnergyDepositTwoCubesCUTGY->Clone("CrosstalkEnergyDepositTwoCubesCUTGY"));
    CrosstalkEnergyDepositTwoCubesCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositTwoCubesCUTGY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *StoppingPointLocation = (TH1F*)(NewStoppingPointLocation->Clone("StoppingPointLocation"));
    StoppingPointLocation->GetYaxis()->SetTitle("Number of events");
    StoppingPointLocation->GetXaxis()->SetTitle("Z detector axis [cm]");
    
    TH1F *HistogramCrosstalkDistanceX = (TH1F*)(NewHistogramCrosstalkDistanceX->Clone("HistogramCrosstalkDistanceX"));
    HistogramCrosstalkDistanceX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceX->GetXaxis()->SetTitle("X detector axis [cm]");
    TH1F *HistogramCrosstalkDistanceY = (TH1F*)(NewHistogramCrosstalkDistanceY->Clone("HistogramCrosstalkDistanceY"));
    HistogramCrosstalkDistanceY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceY->GetXaxis()->SetTitle("Y detector axis [cm]");
    
    TH1F *HistogramCrosstalkDistanceCUTGX = (TH1F*)(NewHistogramCrosstalkDistanceCUTGX->Clone("HistogramCrosstalkDistanceCUTGX"));
    HistogramCrosstalkDistanceCUTGX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceCUTGX->GetXaxis()->SetTitle("X detector axis [cm]");
    TH1F *HistogramCrosstalkDistanceCUTGY = (TH1F*)(NewHistogramCrosstalkDistanceCUTGY->Clone("HistogramCrosstalkDistanceCUTGY"));
    HistogramCrosstalkDistanceCUTGY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceCUTGY->GetXaxis()->SetTitle("Y detector axis [cm]");
    
    TH1F *CrosstalkEnergyDepositPercentageCUTGX = (TH1F*)(NewCrosstalkEnergyDepositPercentageCUTGX->Clone("CrosstalkEnergyDepositPercentageCUTGX"));
    CrosstalkEnergyDepositPercentageCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageCUTGX->GetXaxis()->SetTitle("Percentage %");
    TH1F *CrosstalkEnergyDepositPercentageCUTGY = (TH1F*)(NewCrosstalkEnergyDepositPercentageCUTGY->Clone("CrosstalkEnergyDepositPercentageCUTGY"));
    CrosstalkEnergyDepositPercentageCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageCUTGY->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositRestrictedX = (TH1F*)(NewCrosstalkEnergyDepositRestrictedX->Clone("CrosstalkEnergyDepositRestrictedX"));
    CrosstalkEnergyDepositRestrictedX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositRestrictedX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositRestrictedY = (TH1F*)(NewCrosstalkEnergyDepositRestrictedY->Clone("CrosstalkEnergyDepositRestrictedY"));
    CrosstalkEnergyDepositRestrictedY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositRestrictedY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *HistogramCrosstalkDistanceEnergyHigherThanX = (TH1F*)(NewHistogramCrosstalkDistanceEnergyHigherThanX->Clone("HistogramCrosstalkDistanceEnergyHigherThanX"));
    HistogramCrosstalkDistanceEnergyHigherThanX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceEnergyHigherThanX->GetXaxis()->SetTitle("X detector axis [cm]");
    TH1F *HistogramCrosstalkDistanceEnergyHigherThanY = (TH1F*)(NewHistogramCrosstalkDistanceEnergyHigherThanY->Clone("HistogramCrosstalkDistanceEnergyHigherThanY"));
    HistogramCrosstalkDistanceEnergyHigherThanY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceEnergyHigherThanY->GetXaxis()->SetTitle("Y detector axis [cm]");
    
    TH1F *HistogramCrosstalkDistanceCutX = (TH1F*)(NewHistogramCrosstalkDistanceCutX->Clone("HistogramCrosstalkDistanceCutX"));
    HistogramCrosstalkDistanceCutX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceCutX->GetXaxis()->SetTitle("X detector axis [cm]"); 
    TH1F *HistogramCrosstalkDistanceCutY = (TH1F*)(NewHistogramCrosstalkDistanceCutY->Clone("HistogramCrosstalkDistanceCutY"));
    HistogramCrosstalkDistanceCutY->GetYaxis()->SetTitle("Y detector axis [cm]");
    HistogramCrosstalkDistanceCutY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *HistogramCrosstalkDistanceTypeX = (TH1F*)(NewHistogramCrosstalkDistanceTypeX->Clone("HistogramCrosstalkDistanceTypeX"));
    HistogramCrosstalkDistanceTypeX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceTypeX->GetXaxis()->SetTitle("X detector axis [cm]");
    TH1F *HistogramCrosstalkDistanceTypeY = (TH1F*)(NewHistogramCrosstalkDistanceTypeY->Clone("HistogramCrosstalkDistanceTypeY"));
    HistogramCrosstalkDistanceTypeY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceTypeY->GetXaxis()->SetTitle("Y detector axis [cm]"); 
    
    TH2F *EnergyTrigTimeX = (TH2F*)(NewEnergyTrigTimeX->Clone("EnergyTrigTimeX"));
    EnergyTrigTimeX->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeX->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    TH2F *EnergyTrigTimeY = (TH2F*)(NewEnergyTrigTimeY->Clone("EnergyTrigTimeY"));
    EnergyTrigTimeY->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeY->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH2F *EnergyTrigTimeCrosstalkX = (TH2F*)(NewEnergyTrigTimeCrosstalkX->Clone("EnergyTrigTimeCrosstalkX"));
    EnergyTrigTimeCrosstalkX->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeCrosstalkX->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    TH2F *EnergyTrigTimeCrosstalkY = (TH2F*)(NewEnergyTrigTimeCrosstalkY->Clone("EnergyTrigTimeCrosstalkY"));
    EnergyTrigTimeCrosstalkY->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeCrosstalkY->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH2F *EnergyTrigTimeSignalX = (TH2F*)(NewEnergyTrigTimeSignalX->Clone("EnergyTrigTimeSignalX"));
    EnergyTrigTimeSignalX->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeSignalX->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    TH2F *EnergyTrigTimeSignalY = (TH2F*)(NewEnergyTrigTimeSignalY->Clone("EnergyTrigTimeSignalY"));
    EnergyTrigTimeSignalY->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeSignalY->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH2F *EnergyTrigTimeCUTGX = (TH2F*)(NewEnergyTrigTimeCUTGX->Clone("EnergyTrigTimeCUTGX"));
    EnergyTrigTimeCUTGX->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeCUTGX->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    TH2F *EnergyTrigTimeCUTGY = (TH2F*)(NewEnergyTrigTimeCUTGY->Clone("EnergyTrigTimeCUTGY"));
    EnergyTrigTimeCUTGY->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeCUTGY->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH1F *CrosstalkEnergyDepositMinus1X = (TH1F*)(NewCrosstalkEnergyDepositMinus1X->Clone("CrosstalkEnergyDepositMinus1X"));
    CrosstalkEnergyDepositMinus1X->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1X->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositMinus1Y = (TH1F*)(NewCrosstalkEnergyDepositMinus1Y->Clone("CrosstalkEnergyDepositMinus1Y"));
    CrosstalkEnergyDepositMinus1Y->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1Y->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMinus1OneCubeX = (TH1F*)(NewCrosstalkEnergyDepositMinus1OneCubeX->Clone("CrosstalkEnergyDepositMinus1OneCubeX"));
    CrosstalkEnergyDepositMinus1OneCubeX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1OneCubeX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositMinus1OneCubeY = (TH1F*)(NewCrosstalkEnergyDepositMinus1OneCubeY->Clone("CrosstalkEnergyDepositMinus1OneCubeY"));
    CrosstalkEnergyDepositMinus1OneCubeY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1OneCubeY->GetXaxis()->SetTitle("Energy [p.e.]"); 
    
    TH1F *CrosstalkEnergyDepositMinus1TwoCubesX = (TH1F*)(NewCrosstalkEnergyDepositMinus1TwoCubesX->Clone("CrosstalkEnergyDepositMinus1TwoCubesX"));
    CrosstalkEnergyDepositMinus1TwoCubesX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1TwoCubesX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositMinus1TwoCubesY = (TH1F*)(NewCrosstalkEnergyDepositMinus1TwoCubesY->Clone("CrosstalkEnergyDepositMinus1TwoCubesY"));
    CrosstalkEnergyDepositMinus1TwoCubesY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1TwoCubesY->GetXaxis()->SetTitle("Energy [p.e.]"); 
    
    TH1F *CrosstalkEnergyPercentageMinus1X = (TH1F*)(NewCrosstalkEnergyPercentageMinus1X->Clone("CrosstalkEnergyPercentageMinus1X"));
    CrosstalkEnergyPercentageMinus1X->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMinus1X->GetXaxis()->SetTitle("Percentage %");
    TH1F *CrosstalkEnergyPercentageMinus1Y = (TH1F*)(NewCrosstalkEnergyPercentageMinus1Y->Clone("CrosstalkEnergyPercentageMinus1Y"));
    CrosstalkEnergyPercentageMinus1Y->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMinus1Y->GetXaxis()->SetTitle("Percentage %"); 
    
    TH1F *CrosstalkEnergyPercentageMinus1OneCubeX = (TH1F*)(NewCrosstalkEnergyPercentageMinus1OneCubeX->Clone("CrosstalkEnergyPercentageMinus1OneCubeX"));
    CrosstalkEnergyPercentageMinus1OneCubeX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMinus1OneCubeX->GetXaxis()->SetTitle("Percentage %");
    TH1F *CrosstalkEnergyPercentageMinus1OneCubeY = (TH1F*)(NewCrosstalkEnergyPercentageMinus1OneCubeY->Clone("CrosstalkEnergyPercentageMinus1OneCubeY"));
    CrosstalkEnergyPercentageMinus1OneCubeY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMinus1OneCubeY->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyPercentageMinus1TwoCubesX = (TH1F*)(NewCrosstalkEnergyPercentageMinus1TwoCubesX->Clone("CrosstalkEnergyPercentageMinus1TwoCubesX"));
    CrosstalkEnergyPercentageMinus1TwoCubesX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMinus1TwoCubesX->GetXaxis()->SetTitle("Percentage %");
    TH1F *CrosstalkEnergyPercentageMinus1TwoCubesY = (TH1F*)(NewCrosstalkEnergyPercentageMinus1TwoCubesY->Clone("CrosstalkEnergyPercentageMinus1TwoCubesY"));
    CrosstalkEnergyPercentageMinus1TwoCubesY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMinus1TwoCubesY->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositPercentageMinus1SecondCubeNewX = (TH1F*)(NewCrosstalkEnergyDepositPercentageMinus1SecondCubeNewX->Clone("CrosstalkEnergyDepositPercentageMinus1SecondCubeNewX"));
    CrosstalkEnergyDepositPercentageMinus1SecondCubeNewX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageMinus1SecondCubeNewX->GetXaxis()->SetTitle("Percentage %");
    
    
    TH1F *HistogramCrosstalkDistanceMinus1X = (TH1F*)(NewHistogramCrosstalkDistanceMinus1X->Clone("HistogramCrosstalkDistanceMinus1X"));
    HistogramCrosstalkDistanceMinus1X->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMinus1X->GetXaxis()->SetTitle("X detector axis [cm]");
    TH1F *HistogramCrosstalkDistanceMinus1Y = (TH1F*)(NewHistogramCrosstalkDistanceMinus1Y->Clone("HistogramCrosstalkDistanceMinus1Y"));
    HistogramCrosstalkDistanceMinus1Y->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMinus1Y->GetXaxis()->SetTitle("Y detector axis [cm]");
    
    TH1F *CrosstalkEnergyDepositMinus1CUTGX = (TH1F*)(NewCrosstalkEnergyDepositMinus1CUTGX->Clone("CrosstalkEnergyDepositMinus1CUTGX"));
    CrosstalkEnergyDepositMinus1CUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1CUTGX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositMinus1CUTGY = (TH1F*)(NewCrosstalkEnergyDepositMinus1CUTGY->Clone("CrosstalkEnergyDepositMinus1CUTGY"));
    CrosstalkEnergyDepositMinus1CUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1CUTGY->GetXaxis()->SetTitle("Energy [p.e.]"); 
    
    TH1F *CrosstalkEnergyDepositMinus1OneCubeCUTGX = (TH1F*)(NewCrosstalkEnergyDepositMinus1OneCubeCUTGX->Clone("CrosstalkEnergyDepositMinus1OneCubeCUTGX"));
    CrosstalkEnergyDepositMinus1OneCubeCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1OneCubeCUTGX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositMinus1OneCubeCUTGY = (TH1F*)(NewCrosstalkEnergyDepositMinus1OneCubeCUTGY->Clone("CrosstalkEnergyDepositMinus1OneCubeCUTGY"));
    CrosstalkEnergyDepositMinus1OneCubeCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1OneCubeCUTGY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMinus1TwoCubesCUTGX = (TH1F*)(NewCrosstalkEnergyDepositMinus1TwoCubesCUTGX->Clone("CrosstalkEnergyDepositMinus1TwoCubesCUTGX"));
    CrosstalkEnergyDepositMinus1TwoCubesCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1TwoCubesCUTGX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositMinus1TwoCubesCUTGY = (TH1F*)(NewCrosstalkEnergyDepositMinus1TwoCubesCUTGY->Clone("CrosstalkEnergyDepositMinus1TwoCubesCUTGY"));
    CrosstalkEnergyDepositMinus1TwoCubesCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMinus1TwoCubesCUTGY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyPercentageMinus1CUTGX = (TH1F*)(NewCrosstalkEnergyPercentageMinus1CUTGX->Clone("CrosstalkEnergyPercentageMinus1CUTGX"));
    CrosstalkEnergyPercentageMinus1CUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMinus1CUTGX->GetXaxis()->SetTitle("Percentage %");
    TH1F *CrosstalkEnergyPercentageMinus1CUTGY = (TH1F*)(NewCrosstalkEnergyPercentageMinus1CUTGY->Clone("CrosstalkEnergyPercentageMinus1CUTGY"));
    CrosstalkEnergyPercentageMinus1CUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMinus1CUTGY->GetXaxis()->SetTitle("Percentage %"); 
    
    TH1F *HistogramCrosstalkDistanceMinus1CUTGX = (TH1F*)(NewHistogramCrosstalkDistanceMinus1CUTGX->Clone("HistogramCrosstalkDistanceMinus1CUTGX"));
    HistogramCrosstalkDistanceMinus1CUTGX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMinus1CUTGX->GetXaxis()->SetTitle("X detector axis [cm]");
    TH1F *HistogramCrosstalkDistanceMinus1CUTGY = (TH1F*)(NewHistogramCrosstalkDistanceMinus1CUTGY->Clone("HistogramCrosstalkDistanceMinus1CUTGY"));
    HistogramCrosstalkDistanceMinus1CUTGY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMinus1CUTGY->GetXaxis()->SetTitle("Y detector axis [cm]");
    
    TH1F *HistogramRealPeakEnergyDepositMinus1 = (TH1F*)(NewHistogramRealPeakEnergyDepositMinus1->Clone("HistogramRealPeakEnergyDepositMinus1"));
    HistogramRealPeakEnergyDepositMinus1->GetYaxis()->SetTitle("Number of events");
    HistogramRealPeakEnergyDepositMinus1->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *HistogramCrosstalkDistanceTypeMinus1X = (TH1F*)(NewHistogramCrosstalkDistanceTypeMinus1X->Clone("HistogramCrosstalkDistanceTypeMinus1X"));
    HistogramCrosstalkDistanceTypeMinus1X->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceTypeMinus1X->GetXaxis()->SetTitle("X detector axis [cm]");
    TH1F *HistogramCrosstalkDistanceTypeMinus1Y = (TH1F*)(NewHistogramCrosstalkDistanceTypeMinus1Y->Clone("HistogramCrosstalkDistanceTypeMinus1Y"));
    HistogramCrosstalkDistanceTypeMinus1Y->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceTypeMinus1Y->GetXaxis()->SetTitle("Y detector axis [cm]"); 
    
    TH2F *EnergyTrigTimeMinus1X = (TH2F*)(NewEnergyTrigTimeMinus1X->Clone("EnergyTrigTimeMinus1X"));
    EnergyTrigTimeMinus1X->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeMinus1X->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    TH2F *EnergyTrigTimeMinus1Y = (TH2F*)(NewEnergyTrigTimeMinus1Y->Clone("EnergyTrigTimeMinus1Y"));
    EnergyTrigTimeMinus1Y->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeMinus1Y->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH1F *CrosstalkEnergyDepositMiddleX = (TH1F*)(NewCrosstalkEnergyDepositMiddleX->Clone("CrosstalkEnergyDepositMiddleX"));
    CrosstalkEnergyDepositMiddleX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositMiddleY = (TH1F*)(NewCrosstalkEnergyDepositMiddleY->Clone("CrosstalkEnergyDepositMiddleY"));
    CrosstalkEnergyDepositMiddleY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleY->GetXaxis()->SetTitle("Energy [p.e.]"); 
    
    TH1F *CrosstalkEnergyDepositMiddleOneCubeX = (TH1F*)(NewCrosstalkEnergyDepositMiddleOneCubeX->Clone("CrosstalkEnergyDepositMiddleOneCubeX"));
    CrosstalkEnergyDepositMiddleOneCubeX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleOneCubeX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositMiddleOneCubeY = (TH1F*)(NewCrosstalkEnergyDepositMiddleOneCubeY->Clone("CrosstalkEnergyDepositMiddleOneCubeY"));
    CrosstalkEnergyDepositMiddleOneCubeY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleOneCubeY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMiddleTwoCubesX = (TH1F*)(NewCrosstalkEnergyDepositMiddleTwoCubesX->Clone("CrosstalkEnergyDepositMiddleTwoCubesX"));
    CrosstalkEnergyDepositMiddleTwoCubesX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleTwoCubesX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositMiddleTwoCubesY = (TH1F*)(NewCrosstalkEnergyDepositMiddleTwoCubesY->Clone("CrosstalkEnergyDepositMiddleTwoCubesY"));
    CrosstalkEnergyDepositMiddleTwoCubesY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleTwoCubesY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyPercentageMiddleX = (TH1F*)(NewCrosstalkEnergyPercentageMiddleX->Clone("CrosstalkEnergyPercentageMiddleX"));
    CrosstalkEnergyPercentageMiddleX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMiddleX->GetXaxis()->SetTitle("Percentage %");
    TH1F *CrosstalkEnergyPercentageMiddleY = (TH1F*)(NewCrosstalkEnergyPercentageMiddleY->Clone("CrosstalkEnergyPercentageMiddleY"));
    CrosstalkEnergyPercentageMiddleY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMiddleY->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyPercentageMiddleOneCubeX = (TH1F*)(NewCrosstalkEnergyPercentageMiddleOneCubeX->Clone("CrosstalkEnergyPercentageMiddleOneCubeX"));
    CrosstalkEnergyPercentageMiddleOneCubeX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMiddleOneCubeX->GetXaxis()->SetTitle("Percentage %");
    TH1F *CrosstalkEnergyPercentageMiddleOneCubeY = (TH1F*)(NewCrosstalkEnergyPercentageMiddleOneCubeY->Clone("CrosstalkEnergyPercentageMiddleOneCubeY"));
    CrosstalkEnergyPercentageMiddleOneCubeY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMiddleOneCubeY->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyPercentageMiddleTwoCubesX = (TH1F*)(NewCrosstalkEnergyPercentageMiddleTwoCubesX->Clone("CrosstalkEnergyPercentageMiddleTwoCubesX"));
    CrosstalkEnergyPercentageMiddleTwoCubesX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMiddleTwoCubesX->GetXaxis()->SetTitle("Percentage %");
    TH1F *CrosstalkEnergyPercentageMiddleTwoCubesY = (TH1F*)(NewCrosstalkEnergyPercentageMiddleTwoCubesY->Clone("CrosstalkEnergyPercentageMiddleTwoCubesY"));
    CrosstalkEnergyPercentageMiddleTwoCubesY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMiddleTwoCubesY->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *CrosstalkEnergyDepositPercentageMiddleSecondCubeNewX = (TH1F*)(NewCrosstalkEnergyDepositPercentageMiddleSecondCubeNewX->Clone("CrosstalkEnergyDepositPercentageMiddleSecondCubeNewX"));
    CrosstalkEnergyDepositPercentageMiddleSecondCubeNewX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositPercentageMiddleSecondCubeNewX->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *HistogramCrosstalkDistanceMiddleX = (TH1F*)(NewHistogramCrosstalkDistanceMiddleX->Clone("HistogramCrosstalkDistanceMiddleX"));
    HistogramCrosstalkDistanceMiddleX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMiddleX->GetXaxis()->SetTitle("X detector axis [cm]");
    TH1F *HistogramCrosstalkDistanceMiddleY = (TH1F*)(NewHistogramCrosstalkDistanceMiddleY->Clone("HistogramCrosstalkDistanceMiddleY"));
    HistogramCrosstalkDistanceMiddleY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMiddleY->GetXaxis()->SetTitle("Y detector axis [cm]");
    
    TH1F *HistogramRealPeakEnergyDepositMiddle = (TH1F*)(NewHistogramRealPeakEnergyDepositMiddle->Clone("HistogramRealPeakEnergyDepositMiddle"));
     HistogramRealPeakEnergyDepositMiddle->GetYaxis()->SetTitle("Number of events");
    HistogramRealPeakEnergyDepositMiddle->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *HistogramCrosstalkDistanceTypeMiddleX = (TH1F*)(NewHistogramCrosstalkDistanceTypeMiddleX->Clone("HistogramCrosstalkDistanceTypeMiddleX"));
    HistogramCrosstalkDistanceTypeMiddleX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceTypeMiddleX->GetXaxis()->SetTitle("X detector axis [cm]");  
    TH1F *HistogramCrosstalkDistanceTypeMiddleY = (TH1F*)(NewHistogramCrosstalkDistanceTypeMiddleY->Clone("HistogramCrosstalkDistanceTypeMiddleY"));
    HistogramCrosstalkDistanceTypeMiddleY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceTypeMiddleY->GetXaxis()->SetTitle("Y detector axis [cm]"); 
    
    TH1F *CrosstalkEnergyDepositMiddleCUTGX = (TH1F*)(NewCrosstalkEnergyDepositMiddleCUTGX->Clone("CrosstalkEnergyDepositMiddleCUTGX"));
    CrosstalkEnergyDepositMiddleCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleCUTGX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositMiddleCUTGY = (TH1F*)(NewCrosstalkEnergyDepositMiddleCUTGY->Clone("CrosstalkEnergyDepositMiddleCUTGY"));
    CrosstalkEnergyDepositMiddleCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleCUTGY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMiddleOneCubeCUTGX = (TH1F*)(NewCrosstalkEnergyDepositMiddleOneCubeCUTGX->Clone("CrosstalkEnergyDepositMiddleOneCubeCUTGX"));
    CrosstalkEnergyDepositMiddleOneCubeCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleOneCubeCUTGX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositMiddleOneCubeCUTGY = (TH1F*)(NewCrosstalkEnergyDepositMiddleOneCubeCUTGY->Clone("CrosstalkEnergyDepositMiddleOneCubeCUTGY"));
    CrosstalkEnergyDepositMiddleOneCubeCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleOneCubeCUTGY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyDepositMiddleTwoCubesCUTGX = (TH1F*)(NewCrosstalkEnergyDepositMiddleTwoCubesCUTGX->Clone("CrosstalkEnergyDepositMiddleTwoCubesCUTGX"));
    CrosstalkEnergyDepositMiddleTwoCubesCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleTwoCubesCUTGX->GetXaxis()->SetTitle("Energy [p.e.]");
    TH1F *CrosstalkEnergyDepositMiddleTwoCubesCUTGY = (TH1F*)(NewCrosstalkEnergyDepositMiddleTwoCubesCUTGY->Clone("CrosstalkEnergyDepositMiddleTwoCubesCUTGY"));
    CrosstalkEnergyDepositMiddleTwoCubesCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyDepositMiddleTwoCubesCUTGY->GetXaxis()->SetTitle("Energy [p.e.]");
    
    TH1F *CrosstalkEnergyPercentageMiddleCUTGX = (TH1F*)(NewCrosstalkEnergyPercentageMiddleCUTGX->Clone("CrosstalkEnergyPercentageMiddleCUTGX"));
    CrosstalkEnergyPercentageMiddleCUTGX->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMiddleCUTGX->GetXaxis()->SetTitle("Percentage %");
    TH1F *CrosstalkEnergyPercentageMiddleCUTGY = (TH1F*)(NewCrosstalkEnergyPercentageMiddleCUTGY->Clone("CrosstalkEnergyPercentageMiddleCUTGY"));
    CrosstalkEnergyPercentageMiddleCUTGY->GetYaxis()->SetTitle("Number of events");
    CrosstalkEnergyPercentageMiddleCUTGY->GetXaxis()->SetTitle("Percentage %");
    
    TH1F *HistogramCrosstalkDistanceMiddleCUTGX = (TH1F*)(NewHistogramCrosstalkDistanceMiddleCUTGX->Clone("HistogramCrosstalkDistanceMiddleCUTGX"));
    HistogramCrosstalkDistanceMiddleCUTGX->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMiddleCUTGX->GetXaxis()->SetTitle("X detector axis [cm]");
    TH1F *HistogramCrosstalkDistanceMiddleCUTGY = (TH1F*)(NewHistogramCrosstalkDistanceMiddleCUTGY->Clone("HistogramCrosstalkDistanceMiddleCUTGY"));
    HistogramCrosstalkDistanceMiddleCUTGY->GetYaxis()->SetTitle("Number of events");
    HistogramCrosstalkDistanceMiddleCUTGY->GetXaxis()->SetTitle("Y detector axis [cm]");
    
    TH2F *EnergyTrigTimeMiddleX = (TH2F*)(NewEnergyTrigTimeMiddleX->Clone("EnergyTrigTimeMiddleX"));
    EnergyTrigTimeMiddleX->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeMiddleX->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    TH2F *EnergyTrigTimeMiddleY = (TH2F*)(NewEnergyTrigTimeMiddleY->Clone("EnergyTrigTimeMiddleY"));
    EnergyTrigTimeMiddleY->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeMiddleY->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH2F *EnergyTrigTimeTestX = (TH2F*)(NewEnergyTrigTimeTestX->Clone("EnergyTrigTimeTestX"));
    EnergyTrigTimeTestX->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeTestX->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    TH2F *EnergyTrigTimeTestY = (TH2F*)(NewEnergyTrigTimeTestY->Clone("EnergyTrigTimeTestY"));
    EnergyTrigTimeTestY->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeTestY->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH2F *EnergyTrigTimeTestUpgradeX = (TH2F*)(NewEnergyTrigTimeTestUpgradeX->Clone("EnergyTrigTimeTestUpgradeX"));
    EnergyTrigTimeTestUpgradeX->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeTestUpgradeX->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    TH2F *EnergyTrigTimeTestUpgradeY = (TH2F*)(NewEnergyTrigTimeTestUpgradeY->Clone("EnergyTrigTimeTestUpgradeY"));
    EnergyTrigTimeTestUpgradeY->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeTestUpgradeY->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TH2F *EnergyTrigTimeTestLowX = (TH2F*)(NewEnergyTrigTimeTestLowX->Clone("EnergyTrigTimeTestLowX"));
    EnergyTrigTimeTestLowX->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeTestLowX->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    TH2F *EnergyTrigTimeTestLowY = (TH2F*)(NewEnergyTrigTimeTestLowY->Clone("EnergyTrigTimeTestLowY"));
    EnergyTrigTimeTestLowY->GetYaxis()->SetTitle("Energy [p.e.]");
    EnergyTrigTimeTestLowY->GetXaxis()->SetTitle("Time from Trigger [2.5 ns]");
    
    TFile *fileout = new TFile("/Users/kolos/Desktop/Studia/CIS/Data/MergedCrosstalk.root","RECREATE");
    if ( fileout->IsOpen() )
    {
        printf("File opened successfully\n");
    }  
        
    fileout->cd();
    
    EventsMap_XY->Write();
    EventsMap_YZ->Write();
    EventsMap_XZ->Write();

    EnergyTrigTimeAll->Write();
    
    HistogramHighestEnergyDeposit->Write();
    HistogramRealPeakEnergyDeposit->Write();
    
    CrosstalkEnergyDepositX->Write();
    CrosstalkEnergyDepositY->Write();
    
    CrosstalkEnergyDepositOneCubeX->Write();
    CrosstalkEnergyDepositOneCubeY->Write();
    
    CrosstalkEnergyDepositTwoCubesX->Write();
    CrosstalkEnergyDepositTwoCubesY->Write();
    
    CrosstalkEnergyDepositPercentageX->Write();
    CrosstalkEnergyDepositPercentageY->Write();
    
    CrosstalkEnergyDepositPercentageOneCubeX->Write();
    CrosstalkEnergyDepositPercentageOneCubeY->Write();
    
    CrosstalkEnergyDepositPercentageTwoCubesX->Write();
    CrosstalkEnergyDepositPercentageTwoCubesY->Write();
    
    CrosstalkEnergyDepositPercentageSecondCubeNewX->Write();
    
    CrosstalkEnergyDepositCUTGX->Write();
    CrosstalkEnergyDepositCUTGY->Write();
   
    CrosstalkEnergyDepositOneCubeCUTGX->Write();
    CrosstalkEnergyDepositOneCubeCUTGY->Write();
    
    CrosstalkEnergyDepositTwoCubesCUTGX->Write();
    CrosstalkEnergyDepositTwoCubesCUTGY->Write();
    
    StoppingPointLocation->Write();

    HistogramCrosstalkDistanceX->Write();
    HistogramCrosstalkDistanceY->Write();
    
    HistogramCrosstalkDistanceCUTGX->Write();
    HistogramCrosstalkDistanceCUTGY->Write();
    
    CrosstalkEnergyDepositPercentageCUTGX->Write();
    CrosstalkEnergyDepositPercentageCUTGY->Write();
    
    CrosstalkEnergyDepositRestrictedX->Write();
    CrosstalkEnergyDepositRestrictedY->Write();
    
    HistogramCrosstalkDistanceEnergyHigherThanX->Write();
    HistogramCrosstalkDistanceEnergyHigherThanY->Write();
    
    HistogramCrosstalkDistanceCutX->Write();
    HistogramCrosstalkDistanceCutY->Write();
    
    HistogramCrosstalkDistanceTypeX->Write();
    HistogramCrosstalkDistanceTypeY->Write();
    
    EnergyTrigTimeX->Write();
    EnergyTrigTimeY->Write();
    
    EnergyTrigTimeCrosstalkX->Write();
    EnergyTrigTimeCrosstalkY->Write();
    
    EnergyTrigTimeSignalX->Write();
    EnergyTrigTimeSignalY->Write();
    
    EnergyTrigTimeCUTGX->Write();
    EnergyTrigTimeCUTGY->Write();
    
    CrosstalkEnergyDepositMinus1X->Write();
    CrosstalkEnergyDepositMinus1Y->Write();
    
    CrosstalkEnergyDepositMinus1OneCubeX->Write();
    CrosstalkEnergyDepositMinus1OneCubeY->Write();
    
    CrosstalkEnergyDepositMinus1TwoCubesX->Write();
    CrosstalkEnergyDepositMinus1TwoCubesY->Write();
    
    CrosstalkEnergyPercentageMinus1X->Write();
    CrosstalkEnergyPercentageMinus1Y->Write();
    
    CrosstalkEnergyPercentageMinus1OneCubeX->Write();
    CrosstalkEnergyPercentageMinus1OneCubeY->Write();
    
    CrosstalkEnergyPercentageMinus1TwoCubesX->Write();
    CrosstalkEnergyPercentageMinus1TwoCubesY->Write();
    
    CrosstalkEnergyDepositPercentageMinus1SecondCubeNewX->Write();
    
    HistogramCrosstalkDistanceMinus1X->Write();
    HistogramCrosstalkDistanceMinus1Y->Write();
    
    CrosstalkEnergyDepositMinus1CUTGX->Write();
    CrosstalkEnergyDepositMinus1CUTGY->Write();
    
    CrosstalkEnergyDepositMinus1OneCubeCUTGX->Write();
    CrosstalkEnergyDepositMinus1OneCubeCUTGY->Write();
    
    CrosstalkEnergyDepositMinus1TwoCubesCUTGX->Write();
    CrosstalkEnergyDepositMinus1TwoCubesCUTGY->Write();
    
    CrosstalkEnergyPercentageMinus1CUTGX->Write();
    CrosstalkEnergyPercentageMinus1CUTGY->Write();
    
    HistogramCrosstalkDistanceMinus1CUTGX->Write();
    HistogramCrosstalkDistanceMinus1CUTGY->Write();
    
    HistogramRealPeakEnergyDepositMinus1->Write();
    
    HistogramCrosstalkDistanceTypeMinus1X->Write();
    HistogramCrosstalkDistanceTypeMinus1Y->Write();
    
    EnergyTrigTimeMinus1X->Write();
    EnergyTrigTimeMinus1Y->Write();
    
    CrosstalkEnergyDepositMiddleX->Write();
    CrosstalkEnergyDepositMiddleY->Write();
    
    CrosstalkEnergyDepositMiddleOneCubeX->Write();
    CrosstalkEnergyDepositMiddleOneCubeY->Write();
    
    CrosstalkEnergyDepositMiddleTwoCubesX->Write();
    CrosstalkEnergyDepositMiddleTwoCubesY->Write();
    
    CrosstalkEnergyPercentageMiddleX->Write();
    CrosstalkEnergyPercentageMiddleY->Write();
    
    CrosstalkEnergyPercentageMiddleOneCubeX->Write();
    CrosstalkEnergyPercentageMiddleOneCubeY->Write();
    
    CrosstalkEnergyPercentageMiddleTwoCubesX->Write();
    CrosstalkEnergyPercentageMiddleTwoCubesY->Write();
    
    CrosstalkEnergyDepositPercentageMiddleSecondCubeNewX->Write();
    
    HistogramCrosstalkDistanceMiddleX->Write();
    HistogramCrosstalkDistanceMiddleY->Write();
    
    HistogramRealPeakEnergyDepositMiddle->Write();
    
    HistogramCrosstalkDistanceTypeMiddleX->Write();
    HistogramCrosstalkDistanceTypeMiddleY->Write();
    
    CrosstalkEnergyDepositMiddleCUTGX->Write();
    CrosstalkEnergyDepositMiddleCUTGY->Write();
    
    CrosstalkEnergyDepositMiddleOneCubeCUTGX->Write();
    CrosstalkEnergyDepositMiddleOneCubeCUTGY->Write();
    
    CrosstalkEnergyDepositMiddleTwoCubesCUTGX->Write();
    CrosstalkEnergyDepositMiddleTwoCubesCUTGY->Write();
    
    CrosstalkEnergyPercentageMiddleCUTGX->Write();
    CrosstalkEnergyPercentageMiddleCUTGY->Write();
    
    HistogramCrosstalkDistanceMiddleCUTGX->Write();
    HistogramCrosstalkDistanceMiddleCUTGY->Write();
    
    EnergyTrigTimeMiddleX->Write();
    EnergyTrigTimeMiddleY->Write();
    
    EnergyTrigTimeTestX->Write();
    EnergyTrigTimeTestY->Write();
    
    EnergyTrigTimeTestUpgradeX->Write();
    EnergyTrigTimeTestUpgradeY->Write();
    
    EnergyTrigTimeTestLowX->Write();
    EnergyTrigTimeTestLowY->Write();
    
    cout<<"udalo sie"<<endl;
    
    fileout->Close();
    delete fileout;
        
}
