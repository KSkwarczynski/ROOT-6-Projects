using namespace std;

void ADCanalisis(){
///////CHOSING FILE NAME TO OPEN///////
    TFile *f1= TFile::Open("24August_13_MCR0_hadrons_0pt8Gev_0pt0T_Beam___all.root");
	TTree *FEB;
/////FEBnumber SECLECTS WHICH FEB (Front End Board) YOU WANT TO OPEN////
	int FEBnumber=0;
//////////kanalek - sets channel number you want in amplitude channel histogram///////
    int kanalek=48;
//Declaring how much data you want in ToT important later//
    const int TableSize=9;
//////[HG OR LG][RESULT ANDD ERROR][NUMBER OF DATA ToT]
    float constant[2][2][TableSize];
    float mean[2][2][TableSize];
    float sigma[2][2][TableSize];
    float TimeOverThreshold[TableSize];
///////////////////////////////////////
	f1->GetObject( Form("FEB_%d",FEBnumber),FEB);
    //creating vector<double> to set branch adress//
	vector<double>  amplituda;
	vector<double> *amplitude= &amplituda;
    vector<double>  amplitudaLG;
	vector<double> *amplitudeLG= &amplitudaLG;
    vector<double>  kanal;
	vector<double> *channel= &kanal;
    vector<double>  czas;
    vector<double> *ToT= &czas;
///////////setting branches/////////////////////
  	FEB->SetBranchAddress( Form("FEB_%d_hitAmpl",FEBnumber), &amplitude);
    FEB->SetBranchAddress( Form("FEB_%d_hitLGAmpl",FEBnumber), &amplitudeLG);
  	FEB->SetBranchAddress( Form("FEB_%d_hitsChannel",FEBnumber), &channel);
    FEB->SetBranchAddress( Form("FEB_%d_hitTimeDif",FEBnumber), &ToT);
/////////JUST TO LOOK NICE BUT FOR NOW DOESNT MATTER/////
    int Eventy = FEB->GetEntries();
//////////////////////////CREATING HISTOGRAM AMPLITUDE HG x ToT////////
    TH2F *AmplTimeHist=new TH2F( Form("AmplTimeHist_FEB_%d",FEBnumber), Form("Amplitude HG and ToT histogram for for channel %d FEB_%d",kanalek ,FEBnumber), 4501, 0, 4500, 51, 0, 50);
    AmplTimeHist->GetXaxis()->SetTitle("Amplitude HG");
    AmplTimeHist->GetYaxis()->SetTitle("ToT");
/////////////////////////CREATING HISTOGRAM AMPLITUDE LG x ToT////////
    TH2F *AmplLGTimeaHist=new TH2F( Form("AmplLGTimeHist_FEB_%d",FEBnumber), Form("Amplitude LG and ToT histogram for channel %d FEB_%d",kanalek ,FEBnumber), 4501, 0, 4500, 51, 0, 50);
    AmplLGTimeaHist->GetXaxis()->SetTitle("Amplitude LG");
    AmplLGTimeaHist->GetYaxis()->SetTitle("ToT");
////////There is only one GetEntry because there is only one "event" which is vector consisting of all real events//////
    FEB->GetEntry(0);

    double rozmiar = channel->size();
    int czasikCounter=0;
//////////////////////////////////////
    TFile *plik = new TFile("plots.root","RECREATE");
///////////wartosc startowa i koncowa do petli po ToT aby dobrze bylo tylko zmieniac "start" albo "TableSize"///////////
    int start=5;
    int limit=5*TableSize-start;
//////////Loop over given value of ToT/////
for(int czasik=start; czasik<=limit; czasik=czasik+5){
    //creating histogram for Amplitude HG
    TH1F *AmplHist = new TH1F( Form("AmplHist_FEB_%d_ToT_%d",FEBnumber,czasik), Form("Amplitude HG histogram for channel %d, ToT %d and FEB_%d",kanalek ,czasik, FEBnumber), 1000, 0, 4500);
    AmplHist->GetXaxis()->SetTitle("Amplitude HG");
    AmplHist->GetYaxis()->SetTitle("Number of Events");
    //creating histogram for Amplitude LG
    TH1F *AmplLGHist = new TH1F( Form("AmplLGHist_FEB_%d_ToT_%d",FEBnumber,czasik), Form("Amplitude LG histogram for channel %d, ToT %d and FEB_%d",kanalek ,czasik, FEBnumber), 1000, 0, 4500);
    AmplLGHist->GetXaxis()->SetTitle("Amplitude LG");
    AmplLGHist->GetYaxis()->SetTitle("Number of Events");
///////////////LOOP to fill TH2F HISTOGRAMS////////
    for(int i=0; i<rozmiar ;i++){
            if(channel->at(i)==kanalek){
                    if(amplitude->at(i)>0 && ToT->at(i)==czasik){
                        AmplHist->Fill( amplitude->at(i) );
                        AmplLGHist->Fill(amplitudeLG->at(i));
                    }
            }
        }
////////TABELA Z WARTOSCIAMI ToT POTRZEBNA DO PRZYSZLYCH GRAFOW////////
TimeOverThreshold[czasikCounter]=czasik;
///////////////////////FITOWANIE HG////////////////////////
TF1 *funcHG = new TF1("fitHG", "gaus");
double maksimumHG=AmplHist->GetMaximumBin();
//zrobione żeby działąło wartość związana ze stosunkiem przedziału histogramu do binowania
maksimumHG=maksimumHG*4.5;

AmplHist->Fit(funcHG,"q","",maksimumHG-150,maksimumHG+250);

////wyciągamy wartości z fitu//
constant[0][0][czasikCounter]= funcHG->GetParameter(0);
constant[0][1][czasikCounter]= funcHG->GetParError(0);

mean[0][0][czasikCounter]= funcHG->GetParameter(1);
mean[0][1][czasikCounter]= funcHG->GetParError(1);

sigma[0][0][czasikCounter]= funcHG->GetParameter(2);
sigma[0][1][czasikCounter]= funcHG->GetParError(2);

AmplHist->Write();

delete AmplHist;
///////////////////////FITOWANIE LG////////////////////////
TF1 *funcLG = new TF1("fitLG", "gaus");
double maksimumLG=AmplLGHist->GetMaximumBin();
//zrobione żeby działąło wartość związana ze stosunkiem przedziału histogramu do binowania
maksimumLG=maksimumLG*4.5;

AmplLGHist->Fit(funcLG,"q","",maksimumLG-150,maksimumLG+250);
//////wyciągamy wartości z fitu//
constant[1][0][czasikCounter]= funcLG->GetParameter(0);
constant[1][1][czasikCounter]= funcLG->GetParError(0);

mean[1][0][czasikCounter]= funcLG->GetParameter(1);
mean[1][1][czasikCounter]= funcLG->GetParError(1);

sigma[1][0][czasikCounter]= funcLG->GetParameter(2);
sigma[1][1][czasikCounter]= funcLG->GetParError(2);

AmplLGHist->Write();

delete AmplLGHist;

czasikCounter++;

cout<<czasik<<endl;
    } //end loop
/////////////////////
    for(int i=0; i<rozmiar ;i++){
        if(channel->at(i)==kanalek){
                AmplTimeHist->Fill(amplitude->at(i),ToT->at(i));
                AmplLGTimeaHist->Fill(amplitudeLG->at(i),ToT->at(i));
                    }
    }
////Values from pedestal search, pedestal search not finished, values hardcoded when done they should be from external file
int WojtekProgramDataHG=100;
int WojtekProgramDataLG=105;

//////[data and errors][table size]/////
double PhotoElectronsHG[2][TableSize];
double PhotoElectronsLG[2][TableSize];
/////CONV. FACTOR [ADC/p.e] FROM TABLE NOT FINAL SO VALUES ARD HADCODED NOT TAKEN FROM EXTERNAL FILE///
double ADChg=44;
double ADClg=4.5;
//////DEKLARACJA GRAPGOW//////
TGraphErrors *gr1 = new TGraphErrors();
    gr1->SetTitle( Form("Time over Threshold resolution in pe HG for FEB %d and Channel %d", FEBnumber, kanalek) );
    gr1->SetName(Form("ToT resolution PE HG for FEB %d and Channel %d", FEBnumber, kanalek));
    gr1->GetXaxis()->SetTitle("Time over Threshold");
    gr1->GetYaxis()->SetTitle("Photo Electrons");
    gr1->SetMarkerColor(2);
    gr1->SetMarkerSize(1.0);
    gr1->SetMarkerStyle(8);

TGraphErrors *gr2 = new TGraphErrors();
    gr2->SetTitle( Form("Time over Threshold resolution in pe LG for FEB %d and Channel %d", FEBnumber, kanalek) );
    gr2->SetName(Form("ToT resolution PE LG for FEB %d and Channel %d", FEBnumber, kanalek));
    gr2->GetXaxis()->SetTitle("Time over Threshold");
    gr2->GetYaxis()->SetTitle("Photo Electrons");
    gr2->SetMarkerColor(4);
    gr2->SetMarkerSize(1.0);
    gr2->SetMarkerStyle(21);

    for(int k=0; k<czasikCounter;k++){
/////////FILLING gr1 GRAPH FOR HG////
    float KrokPosredniHG=mean[0][0][k]-WojtekProgramDataHG;
    PhotoElectronsHG[0][k] =KrokPosredniHG/ADChg;
    gr1->SetPoint(k,TimeOverThreshold[k],PhotoElectronsHG[0][k]);

    PhotoElectronsHG[1][k]=sigma[0][1][k]/ADChg;
    gr1->SetPointError( k,0,PhotoElectronsHG[1][k] );

/////////FILLING gr2 GRAPH FOR LG////
    float KrokPosredniLG=mean[1][0][k]-WojtekProgramDataLG;
    PhotoElectronsLG[0][k] =KrokPosredniLG/ADClg;
    gr2->SetPoint(k,TimeOverThreshold[k],PhotoElectronsLG[0][k]);

    PhotoElectronsLG[1][k]=sigma[1][0][k]/ADClg;
    gr2->SetPointError( k,0,PhotoElectronsLG[1][k] );
    }
///////////////////////////
    TCanvas *c1 = new TCanvas(Form("AmplTimeHist_FEB_%d",FEBnumber), Form("Amplitude HG and ToT histogram for for channel %d FEB %d",kanalek ,FEBnumber));
    gROOT->SetStyle("Plain");
    gStyle->SetOptLogy(0);
    gStyle->SetOptStat(1110);
    c1->SetLogz();
/////////////DRAW AMPLITUDE HG TOT HISTOGRAM/////////////
    AmplTimeHist->Draw("COLZ");
    c1->Write();
    delete c1;
//////////////////////////////////////////////////////////////////////
    TCanvas *c2 = new TCanvas(Form("AmplLGTimeHist_FEB_%d",FEBnumber), Form("Amplitude LG and ToT histogram for for channel %d FEB %d",kanalek ,FEBnumber));
    gROOT->SetStyle("Plain");
    gStyle->SetOptLogy(0);
    gStyle->SetOptStat(1110);
    c2->SetLogz();
/////////DRAW APLITUDE LG CHANNEL HISTOGRAM//////////
    AmplLGTimeaHist->Draw("COLZ L");
    c2->Write();
    delete c2;
/////////////////////
    gr1->Write();
    gr2->Write();

    TCanvas *c3 = new TCanvas(Form("ToT over PE (HG and LG) FEB_%d and Channel_%d", FEBnumber, kanalek), Form("Time over Threshold resolution in pe HG and LG for FEB %d and Channel %d", FEBnumber, kanalek) );
    gROOT->SetStyle("Plain");
    gStyle->SetOptLogy(0);
    gStyle->SetOptStat(1110);

    TMultiGraph *mg = new TMultiGraph(Form("ToT over PE (HG and LG) FEB_%d and Channel_%d", FEBnumber, kanalek), Form("Time over Threshold resolution in pe HG and LG for FEB %d and Channel %d", FEBnumber, kanalek));
    mg->Add(gr1);
    mg->Add(gr2);

    mg->Draw("AP");
    mg->GetXaxis()->SetTitle("Time over Threshold");
    mg->GetYaxis()->SetTitle("Photo Electrons");

    auto legend = new TLegend(0.1,0.8,0.2,0.9);
    legend->SetHeader("Legend");
    legend->AddEntry(gr1,"High Gain","p");
    legend->AddEntry(gr2,"Low Gain","p");
    legend->Draw();

    c3->Write();
/////////DELETE EVERYTHING///////
    delete gr1;
    delete gr2;
    delete mg;
    delete c3;
    delete legend;

plik->Close();
delete plik;
}
