void 1DHistogram()
{
	TH1F *hist = new TH1F("hist", "Histogram",100,0,100);
	
	for (int i=0; i<100000; i++){	
		
		hist->Fill(rand()%200);
	}

	
	hist->GetXaxis()-> SetTitle("x");
	hist->GetYaxis()->SetTitle("y");
	
	TCanvas *c1 = new TCanvas();
	hist->Draw("bar");

}
