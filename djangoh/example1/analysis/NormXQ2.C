void NormXQ2(){
     TFile *f0 = new TFile("../outfiles/djangoh.ep.5x100.5Mevents.1.RadCor=1_evt.root");
     TTree *T = (TTree *) f0->Get("EICTree");

     TH2F *hXQ2 = new TH2F("hXQ2","Q2 vs. X distribution",100,0,1,100,0,100);
     T->Draw("dtrueQ2:dtrueX>>hXQ2");
     Double_t ntotal = hXQ2->Integral();

     hXQ2->Scale(ntotal);
     hXQ2->Draw("COLZ");
     
     cout<<"total events:  "<<ntotal<<endl;
}
