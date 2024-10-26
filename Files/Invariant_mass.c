#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TMath.h>

// Constants for Kaon and Pion masses (in MeV/c^2)
const double m_K = 0493.677 ;
const double m_Pi = 0139.57018;

void Invariant_mass() {
    // Open the ROOT file and access the tree
    TFile *file = TFile::Open("B2HHH_MagnetDown.root");

    TTree *tree = (TTree*)file->Get("DecayTree");

    // Set up branch addresses
    double H1_PX, H1_PY, H1_PZ;
    double H2_PX, H2_PY, H2_PZ;
    double H3_PX, H3_PY, H3_PZ;
    
    tree->SetBranchAddress("H1_PX", &H1_PX);
    tree->SetBranchAddress("H1_PY", &H1_PY);
    tree->SetBranchAddress("H1_PZ", &H1_PZ);
    tree->SetBranchAddress("H2_PX", &H2_PX);
    tree->SetBranchAddress("H2_PY", &H2_PY);
    tree->SetBranchAddress("H2_PZ", &H2_PZ);
    tree->SetBranchAddress("H3_PX", &H3_PX);
    tree->SetBranchAddress("H3_PY", &H3_PY);
    tree->SetBranchAddress("H3_PZ", &H3_PZ);

    // Create histograms for invariant masses
    TH1F *h_M_inv = new TH1F("h_M_inv", "Invariant Mass of B->h+h-h+", 300, 0, 10000);
    
    double nentries = tree->GetEntries();
    cout<<nentries<<endl;
    //tree->Show(0);
   
 
    for (double i = 0; i < nentries; i++) {
        tree->GetEntry(i);

        // Construct TLorentzVectors for the decay products
        TLorentzVector h1(H1_PX, H1_PY, H1_PZ, sqrt(H1_PX*H1_PX + H1_PY*H1_PY + H1_PZ*H1_PZ + m_K*m_K));
        TLorentzVector h2(H2_PX, H2_PY, H2_PZ, sqrt(H2_PX*H2_PX + H2_PY*H2_PY + H2_PZ*H2_PZ + m_Pi*m_Pi));
        TLorentzVector h3(H3_PX, H3_PY, H3_PZ, sqrt(H3_PX*H3_PX + H3_PY*H3_PY + H3_PZ*H3_PZ + m_Pi*m_Pi));

        // Calculate the invariant mass of the B candidate
        TLorentzVector B_candidate = h1 + h2 + h3;
        double M_inv = B_candidate.M();
        //cout<<M_inv<<endl;
        // Fill the histogram with the invariant mass
        h_M_inv->Fill(M_inv);
    }

    // Draw the histogram
    TCanvas *c1 = new TCanvas("c1", "Invariant Mass of B->h+h-h+", 800, 600);
    h_M_inv->GetXaxis()->SetTitle("Invariant Mass (MeV/c^2)");
    h_M_inv->GetYaxis()->SetTitle("Events");
    //cout<<h_M_inv->GetMean();
    h_M_inv->Draw();

    c1->SaveAs("M_inv.png");
    // Close the file
    file->Close();
}


