void Calc_Apv(){
     int eE = 18;
     int eP = 275;

     TString filename1 = Form("/w/halla-scifs17exp/triton/hanjie/EIC/dis-reconstruction/djangoh/PVDIS/rootfiles/djangoh_ep_%d_%d_norad_m_evt.root",eE,eP);
     TString filename2 = Form("/w/halla-scifs17exp/triton/hanjie/EIC/dis-reconstruction/djangoh/PVDIS/rootfiles/djangoh_ep_%d_%d_norad_p_evt.root",eE,eP);

     TFile *f1 = new TFile(filename1);
     TFile *f2 = new TFile(filename2);

     TTree *Tm = (TTree *)f1->Get("EICTree");
     TTree *Tp = (TTree *)f2->Get("EICTree");

     Double_t nevent_p = Tp->GetMaximum("number");
     Double_t totalXS_p = Tp->GetMaximum("sigTot");
   
     Double_t LUMP = nevent_p/totalXS_p;

     Double_t nevent_m = Tm->GetMaximum("number");
     Double_t totalXS_m = Tm->GetMaximum("sigTot");
  
     Double_t LUMM = nevent_m/totalXS_m;
 
     TCut PID = "particles.id==11 && particles.KS==1";
     Tp->Draw(">>electron_p",PID);
     TEventList *electron_p;
     gDirectory->GetObject("electron_p",electron_p);
     Tp->SetEventList(electron_p);

     Double_t xmin_p = Tp->GetMinimum("dX");     Double_t xmax_p = Tp->GetMaximum("dX");
     Double_t q2min_p = Tp->GetMinimum("dQ2");     Double_t q2max_p = Tp->GetMaximum("dQ2");
     Double_t w2min_p = Tp->GetMinimum("dW2");     Double_t w2max_p = Tp->GetMaximum("dW2");
     Double_t etamin_p = Tp->GetMinimum("particles.eta");     Double_t etamax_p = Tp->GetMaximum("particles.eta");

     Tm->Draw(">>electron_m",PID);
     TEventList *electron_m;
     gDirectory->GetObject("electron_m",electron_m);
     Tm->SetEventList(electron_m);

     Double_t xmin_m = Tm->GetMinimum("dX");     Double_t xmax_m = Tm->GetMaximum("dX");
     Double_t q2min_m = Tm->GetMinimum("dQ2");     Double_t q2max_m = Tm->GetMaximum("dQ2");
     Double_t w2min_m = Tm->GetMinimum("dW2");     Double_t w2max_m = Tm->GetMaximum("dW2");
     Double_t etamin_m = Tm->GetMinimum("particles.eta");     Double_t etamax_m = Tm->GetMaximum("particles.eta");

     Double_t xmin,xmax,q2min,q2max,w2min,w2max,etamin,etamax;
     if(xmin_p < xmin_m) xmin=xmin_p;
     else xmin = xmin_m;

     if(xmax_p > xmax_m) xmax=xmax_p;
     else xmax = xmax_m;

     if(q2min_p < q2min_m) q2min=q2min_p;
     else q2min = q2min_m;

     if(q2max_p > q2max_m) q2max=q2max_p;
     else q2max = q2max_m;

     if(w2min_p < w2min_m) w2min=w2min_p;
     else w2min = w2min_m;

     if(w2max_p > w2max_m) w2max=w2max_p;
     else w2max = w2max_m;

     if(etamin_p < etamin_m) etamin=etamin_p;
     else etamin = etamin_m;

     if(etamax_p > etamax_m) etamax=etamax_p;
     else etamax = etamax_m;

     TH2F *hxq2_p = new TH2F("hxq2_p","Q2 vs. x distribution(+)",500,xmin,xmax,500,q2min,q2max); 
     TH2F *hxeta_p = new TH2F("hxeta_p","x vs. eta distribution(+)",500,etamin,etamax,500,xmin,xmax); 
     TH2F *hq2eta_p = new TH2F("hq2eta_p","Q2 vs. eta distribution(+)",500,etamin,etamax,500,q2min,q2max); 
     TH2F *hw2eta_p = new TH2F("hw2eta_p","W2 vs. eta distribution(+)",500,etamin,etamax,500,w2min,w2max); 

     TH2F *hxq2_m = new TH2F("hxq2_m","Q2 vs. x distribution(-)",500,xmin,xmax,500,q2min,q2max); 
     TH2F *hxeta_m = new TH2F("hxeta_m","x vs. eta distribution(-)",500,etamin,etamax,500,xmin,xmax); 
     TH2F *hq2eta_m = new TH2F("hq2eta_m","Q2 vs. eta distribution(-)",500,etamin,etamax,500,q2min,q2max); 
     TH2F *hw2eta_m = new TH2F("hw2eta_m","W2 vs. eta distribution(-)",500,etamin,etamax,500,w2min,w2max); 



     TCanvas *c1= new TCanvas("c1","c1",1000,1500);
     c1->Divide(2,4);
     c1->cd(1); Tp->Draw("dQ2:dX>>hxq2_p",PID,"COLZ"); 
     c1->cd(2); Tm->Draw("dQ2:dX>>hxq2_m",PID,"COLZ"); 
     c1->cd(3); Tp->Draw("dX:particles.eta>>hxeta_p",PID,"COLZ"); 
     c1->cd(4); Tm->Draw("dX:particles.eta>>hxeta_m",PID,"COLZ"); 
     c1->cd(5); Tp->Draw("dQ2:particles.eta>>hq2eta_p",PID,"COLZ"); 
     c1->cd(6); Tm->Draw("dQ2:particles.eta>>hq2eta_m",PID,"COLZ"); 
     c1->cd(7); Tp->Draw("dW2:particles.eta>>hw2eta_p",PID,"COLZ"); 
     c1->cd(8); Tm->Draw("dW2:particles.eta>>hw2eta_m",PID,"COLZ"); 

     TH2F *hxq2_p_norm = (TH2F *)hxq2_p->Clone();
     hxq2_p_norm->Scale(1./LUMP); 
     TH2F *hxq2_m_norm = (TH2F *)hxq2_m->Clone();
     hxq2_m_norm->Scale(1./LUMM); 
     
     TH2F *hxq2_sum = (TH2F *)hxq2_p_norm->Clone();
     hxq2_sum->Add(hxq2_m_norm);

     TH2F *hxq2_diff = (TH2F *)hxq2_p_norm->Clone();
     hxq2_diff->Add(hxq2_m_norm,-1.);

     TH2F *hxq2_asym = (TH2F *)hxq2_diff->Clone();
     hxq2_asym->Divide(hxq2_sum);

     TCanvas *c2 = new TCanvas("c2","c2",1000,1000);
     hxq2_asym->Draw("COLZ");

     c1->Print(Form("Apv_%d_%d.pdf[",eE,eP));
     c1->Print(Form("Apv_%d_%d.pdf",eE,eP));
     c2->Print(Form("Apv_%d_%d.pdf",eE,eP));
     c2->Print(Form("Apv_%d_%d.pdf]",eE,eP));
}
