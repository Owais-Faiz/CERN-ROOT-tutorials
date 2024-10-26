#include "TMinuit.h"
#include <fstream>
#include "TMath.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLatex.h"

// Fitting macro based on the correct equation and parameter adjustments
Double_t pi = TMath::Pi();
double m0=1.18936;

// Corrected function based on the provided document
Double_t fEqn(const Double_t *x, const Double_t *p) {
    Double_t pt = x[0];
    
    Double_t C = p[0];          // Normalization constant
    Double_t beta_T = p[1];     // <beta_T>
    Double_t n = p[2];          // exponent
    Double_t T0 = p[3];         // Temperature parameter
    
    Double_t gamma_T = 1/(TMath::Sqrt(1-p[1]*p[1]));    // <gamma_T>

    Double_t mt = TMath::Sqrt(pt*pt + m0*m0); // Transverse mass calculated using mt = sqrt(pt^2 + m0^2)

    // Updated fitting function as per the document
    Double_t fit_fun = 2 * pi * pt * C * TMath::Power(1 + (gamma_T / n) * ((mt - pt * beta_T) / T0), -n);

    return fit_fun;
}

void plotpPb() {
    TCanvas *c1 = new TCanvas("c1", "positive", 500, 400);
    c1->SetFillColor(0);
    c1->SetLogy(1);
    c1->SetLogx(0);

    gStyle->SetOptTitle(0);

    TGraphErrors *gr[4];
    TF1 *fEquation[4];

    gStyle->SetOptFit(1111);

    for (int i = 0; i < 4; i++) {
        gr[i] = new TGraphErrors(Form("pPb%d.dat", i)); // Adjust the file names accordingly
        fEquation[i] = new TF1("fEquation", fEqn, 0, 8.2, 4);
        fEquation[i]->SetParNames("C", "beta_T", "n", "T0");
        
/*        //m0=0.9, 2.36, and 7 TeV
        
	if (i==0){
	double m0=900;
	}
	
	if (i==1){
	double m0=2360;
	}
	
	if (i==2){
	double m0=7000;
	}
	*/
	
        // Adjusted initial parameter values and limits based on the document and image
        fEquation[i]->SetParameter(0, 10);   // C (Normalization constant)
        //fEquation[i]->SetParameter(1, 2);   // gamma_T (<gamma_T>)
        fEquation[i]->SetParameter(1, 0.74);   // beta_T (<beta_T>)
        fEquation[i]->SetParameter(2, 10.3);   // n (Exponent)
        fEquation[i]->SetParameter(3, 0.1);  // T0 (GeV)
  
        fEquation[i]->SetParLimits(1, 0.0001,1);
        fEquation[i]->SetParLimits(2, 5,15);
        fEquation[i]->SetParLimits(3, 0.100,0.200);
        //fEquation[i]->SetParLimits(0, 0.0001,3);
	
        fEquation[i]->SetLineWidth(3);
        fEquation[i]->SetMarkerColor(600 + 32 * i);
        fEquation[i]->SetLineColor(600 + 32 * i);

        if (i == 0) {
            fEquation[i]->SetMarkerColor(kRed); // red
            fEquation[i]->SetLineColor(kRed);
        }

        if (i == 1) {
            fEquation[i]->SetMarkerColor(kBlue); // blue
            fEquation[i]->SetLineColor(kBlue);
        }

        if (i == 2) {
            fEquation[i]->SetMarkerColor(kMagenta); // magenta
            fEquation[i]->SetLineColor(kMagenta);
        }
        
        if (i == 3) {
            fEquation[i]->SetMarkerColor(kGreen); // magenta
            fEquation[i]->SetLineColor(kGreen);
        }

        //gr[i]->SetMinimum(0.00001);
        //gr[i]->SetMaximum(100);
        gr[i]->GetXaxis()->SetRangeUser(0, 10);
        gr[i]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
        gr[i]->GetXaxis()->SetTitleColor(1);
        gr[i]->GetXaxis()->CenterTitle();
        gr[i]->GetYaxis()->CenterTitle();
        gr[i]->GetYaxis()->SetTitle("1/N_{ev}#frac{d^{2}N}{dp_{T}dy} (GeV/c)^{-1}");
        gr[i]->GetYaxis()->SetTitleOffset(1.40);
        gr[i]->SetMarkerSize(1.3);
       
        
        if (i==0){
        gr[i]->Fit(fEquation[i], "REM+");
        }
        else{
        gr[i]->Fit(fEquation[i], "REM+");
        }
        
        // Print fit parameters and chi-squared value
    	Double_t chi2 = fEquation[i]->GetChisquare();
    	Double_t ndf = fEquation[i]->GetNDF();
    	Double_t chi2_per_ndf = (ndf > 0) ? chi2 / ndf : 0;
        printf("Fit results for iteration number:%d  ",i);
	//printf("Chi2 = %f\n", chi2);
	//printf("NDF = %f\n", ndf);
	printf("Chi2/ndf = %f\n", chi2_per_ndf);
	
    }

    gr[0]->SetMarkerColor(kRed);
    gr[0]->SetMarkerStyle(20);
    gr[0]->Draw("AP");

    gr[1]->SetMarkerColor(kBlue);
    gr[1]->SetMarkerStyle(21);
    gr[1]->Draw("P");

    gr[2]->SetMarkerColor(kMagenta);
    gr[2]->SetMarkerStyle(22);
    gr[2]->Draw("P");
    
    gr[3]->SetMarkerColor(kGreen);
    gr[3]->SetMarkerStyle(23);
    gr[3]->Draw("P");

    
}

