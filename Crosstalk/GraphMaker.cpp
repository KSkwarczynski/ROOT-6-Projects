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
    
    char filename[200];
    sprintf(filename,"/Users/kolos/Desktop/Studia/CIS/Data/27August_1_MCR0_hadrons_0pt8Gev_0pt0T_Beam___Crosstalk.root");
    TFile *file = new TFile(filename,"READ");
    if ( file->IsOpen() )
    {
        printf("File opened successfully\n");
    }  
    
    file->cd();
    

}
