void 2DHistogram()
{
TCanvas *c1 = new TCanvas();


TH3F *hist = new TH3F("hist", "Histogram", 100, -1,1,100,-1,1,100,-1,1);

TRandom *rand= new TRandom(10);

for (int i=0; i<100000;i++){
	double x= rand->Gaus();
	double y= rand->Gaus();
	double z= rand->Gaus();
	
	hist->Fill(x,y,z);
	
}

hist->GetXaxis()-> SetTitle("x");
hist->GetYaxis()->SetTitle("y");
hist->GetZaxis()->SetTitle("z");


hist->Draw("colz");

}
