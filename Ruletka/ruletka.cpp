{
TRandom3 * losowa = new TRandom3(0);

double DlugoscBoku=2;
const int liczbabokow=3;
double bok[liczbabokow];
double pitagoras=0;
double pitagoraskwadrat=0;

double promien=0;
int liczbaprob=1000000;
int counter=0;
promien=DlugoscBoku/2;

for(int k=0;k<liczbaprob;k++){
    for(int i=0;i<liczbabokow;i++){
    bok[i]=losowa->Uniform(DlugoscBoku/(-2),DlugoscBoku/2);
    pitagoras+=bok[i]*bok[i];
    }

pitagoraskwadrat=TMath::Sqrt(pitagoras);
    if(pitagoraskwadrat <= promien ){
    counter++;
        }

pitagoras=0;
pitagoraskwadrat=0;
}

double pole=TMath::Power(DlugoscBoku,liczbabokow) *counter/liczbaprob;
cout<<"pole kola to "<<pole<<endl;

    delete losowa;
}
