#include <TH2F.h>
#include <fstream>
#include <iostream>

void PlotMaker()
{
    char filename[200];
    sprintf(filename,"/Users/kolos/Desktop/Studia/CIS/Data/27August_1_MCR0_hadrons_0pt8Gev_0pt0T_Beam___Crosstalk.root");
    TFile *file = new TFile(filename,"READ");
    file->IsOpen();
    
    file->cd();
    
    TH2F* EnergyTrigTimeX = (TH2F*) file->Get("EnergyTrigTimeX");
    TH2F* EnergyTrigTimeY = (TH2F*) file->Get("EnergyTrigTimeY");
    TH2F* EnergyTrigTimeCrosstalkX = (TH2F*) file->Get("EnergyTrigTimeCrosstalkX");
    TH2F* EnergyTrigTimeCrosstalkY = (TH2F*) file->Get("EnergyTrigTimeCrosstalkY");
    TH2F* EnergyTrigTimeSignalX = (TH2F*) file->Get("EnergyTrigTimeSignalX");
    TH2F* EnergyTrigTimeSignalY = (TH2F*) file->Get("EnergyTrigTimeSignalY");
    
    TH2F* EnergyTrigTimeTestX = (TH2F*) file->Get("EnergyTrigTimeTestX");
    TH2F* EnergyTrigTimeTestY = (TH2F*) file->Get("EnergyTrigTimeTestY");
    TH2F* EnergyTrigTimeTestLowX = (TH2F*) file->Get("EnergyTrigTimeTestLowX");
    TH2F* EnergyTrigTimeTestLowY = (TH2F*) file->Get("EnergyTrigTimeTestLowY");

    TH1F* CrosstalkEnergyDepositX = (TH1F*) file->Get("CrosstalkEnergyDepositX");
    TH1F* CrosstalkEnergyDepositY = (TH1F*) file->Get("CrosstalkEnergyDepositY");
    TH1F* CrosstalkEnergyDepositMiddleX = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleX");
    TH1F* CrosstalkEnergyDepositMiddleY = (TH1F*) file->Get("CrosstalkEnergyDepositMiddleY");

    
    CrosstalkEnergyDepositX
    TCanvas *Canvas = new TCanvas("Canvas","Canvas", 1400, 1000);
    Canvas->Divide(3,2);
    Canvas -> cd(1);
    EnergyTrigTimeX->Draw("COLZ");
    Canvas -> cd(2);
    EnergyTrigTimeCrosstalkX->Draw("COLZ");
    Canvas -> cd(3);
    EnergyTrigTimeSignalX->Draw("COLZ");
    Canvas -> cd(4);
    EnergyTrigTimeY->Draw("COLZ");
    Canvas -> cd(5);
    EnergyTrigTimeCrosstalkY->Draw("COLZ");
    Canvas -> cd(6);
    EnergyTrigTimeSignalY->Draw("COLZ");
    
    Canvas->Print("/Users/kolos/Desktop/Studia/CIS/Data/Output/TimeTriggerEnergy.pdf");
    
    TCanvas *Canvas2 = new TCanvas("Canvas2","Canvas2", 1400, 1000);
    Canvas2->Divide(2,2);
    
    Canvas2 -> cd(1);
    EnergyTrigTimeTestX->Draw("COLZ");
    Canvas2 -> cd(2);
    EnergyTrigTimeTestY->Draw("COLZ");
    Canvas2 -> cd(3);
    EnergyTrigTimeTestLowX->Draw("COLZ");
    Canvas2 -> cd(4);
    EnergyTrigTimeTestLowY->Draw("COLZ");
    
    Canvas2->Print("/Users/kolos/Desktop/Studia/CIS/Data/Output/WierdPlot.pdf");
    
    TCanvas *Canvas3 = new TCanvas("Canvas3","Canvas3", 1400, 1000);
    Canvas3->Divide(2,1);
        
    CrosstalkEnergyDepositX->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositX->SetLineWidth(1.5);
    
    CrosstalkEnergyDepositMiddleX->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyDepositMiddleX->SetLineWidth(1.5);
    
    CrosstalkEnergyDepositY->SetLineColorAlpha(kRed, 1);
    CrosstalkEnergyDepositY->SetLineWidth(1.5);
    
    CrosstalkEnergyDepositMiddleY->SetLineColorAlpha(kGreen, 1);
    CrosstalkEnergyDepositMiddleY->SetLineWidth(1.5);
        
    Canvas3 -> cd(1);
    CrosstalkEnergyDepositX->Draw("");
    CrosstalkEnergyDepositMiddleX->Draw("SAME");
    
    TLegend *legend1 = new TLegend(0.7482117,0.6940452,0.9799714,0.9353183);
    legend1->AddEntry(CrosstalkEnergyDepositX,"CrosstalkEnergyDepositX","l");
    legend1->AddEntry(CrosstalkEnergyDepositMiddleX,"CrosstalkEnergyDepositMiddleX","l");
    
    Canvas2 -> cd(2);
    CrosstalkEnergyDepositY->Draw("");
    CrosstalkEnergyDepositMiddleY->Draw("SAME");
    
    TLegend *legend2 = new TLegend(0.7482117,0.6940452,0.9799714,0.9353183);
    legend2->AddEntry(CrosstalkEnergyDepositY,"CrosstalkEnergyDepositY","l");
    legend2->AddEntry(CrosstalkEnergyDepositMiddleY,"CrosstalkEnergyDepositMiddleY","l");
    
    Canvas3->Print("/Users/kolos/Desktop/Studia/CIS/Data/Output/CrosstalkComparison.pdf");
}
