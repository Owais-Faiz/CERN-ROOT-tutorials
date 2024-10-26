{
    // Step 1: Create a new ROOT file
    TFile *file = new TFile("example.root", "RECREATE");
    
    // Step 2: Create a directory in the file
    TDirectory *dir = file->mkdir("mydir");
    
    // Step 3: Create a tree and add branches
    // Switch to the directory
    dir->cd();
    
    // Create a tree
    TTree *tree = new TTree("mytree", "A simple tree");
    
    // Define variables to be stored in the tree
    float x, y, z;
    
    // Create branches in the tree
    tree->Branch("x", &x, "x/F");
    tree->Branch("y", &y, "y/F");
    tree->Branch("z", &z, "z/F");
    
    // Step 4: Fill the tree with data
    for (int i = 0; i < 100; ++i) {
        x = gRandom->Gaus(0, 1);
        y = gRandom->Gaus(0, 1);
        z = gRandom->Gaus(0, 1);
        tree->Fill();
    }
    
    // Step 5: Write the directory and tree to the file
    dir->Write();
    
    // Step 6: Close the ROOT file
    file->Close();
}
