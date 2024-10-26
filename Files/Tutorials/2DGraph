void 2DGraph(){

   TCanvas *c = new TCanvas("c","Graph2D example",0,0,700,600);
   double x, y, z, P = 6;
   int np = 1000;
   TGraph2D *dt = new TGraph2D();
   TRandom *r = new TRandom();

   for (int N=0; N<np; N++) {
      x = 2*P*(r->Rndm(N))-P;
      y = 2*P*(r->Rndm(N))-P;
      z = (sin(x)/x)*(sin(y)/y)+0.2;
      dt->SetPoint(N,x,y,z);
   }
   
   gStyle->SetPalette(55);
   dt->Draw("surf1");       
   
  
   }
