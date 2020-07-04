R__LOAD_LIBRARY(libeicsmear);

void Ratio_Pie(){
     int Ee = 18;
     int Ep = 275;
     
     TFile *f1 = new TFile(Form("../outfiles/ep_%d_%d_rad.root",Ee,Ep),"READ");
     TTree *T = (TTree *)f1->Get("EICTree");

     //Event Class
     erhic::EventPythia *event(NULL); //Note that I use Pointer
     //Particle Class
     erhic::ParticleMC *particle(NULL);

     T->SetBranchAddress("event", &event);

     Int_t nentries = T->GetEntries();
     cout<<nentries<<endl;

     TLorentzVector e;
     TLorentzVector pi;
     Double_t eta,pp;

     TH1F *hE[8];
     TH1F *hPi[8];

     for(int ii=0;ii<8;ii++){
	hE[ii] =new TH1F(Form("hE_%d",ii),Form("electron momentum distribution %d",ii),1000,0,50);
	hPi[ii] =new TH1F(Form("hPi_%d",ii),Form("pion(-) momentum distribution %d",ii),1000,0,50);
     }

     Double_t eta_cut[9]={-5,-3.5,-2,-1,0,1,2,3.5,5};
 
     for(int ii=0; ii<nentries;ii++){
	T->GetEntry(ii);
       //Get Total Number of Particles
        Int_t nParticles = event->GetNTracks();
        for(int jj=0; jj<nParticles;jj++){
          particle = event->GetTrack(jj);
          Int_t Status = (Int_t) particle->GetStatus();
          Int_t id = (Int_t) particle->Id();

          // Get final state election
          if(Status==1){
            if(id==11){
	       eta=0; pp=0;
	       e.SetPxPyPzE(particle->px,particle->py,particle->pz,particle->E);
	       eta = e.Eta();
	       pp = e.P();
	       for(int kk=0; kk<8; kk++){
		if(eta<=eta_cut[kk+1] && eta>eta_cut[kk]) hE[kk]->Fill(pp);
	       }
	    }
            if(id==-211){
	       eta=0; pp=0;
	       pi.SetPxPyPzE(particle->px,particle->py,particle->pz,particle->E);
	       eta = pi.Eta();
	       pp = pi.P();
	       for(int kk=0; kk<8; kk++){
		if(eta<=eta_cut[kk+1] && eta>eta_cut[kk]) hPi[kk]->Fill(pp);
	       }
	    }
	  }
	}
     }

     gStyle->SetOptStat(0);
     TCanvas *c1 = new TCanvas("c1","c1",2000,1500);
     c1->Divide(3,3);
     for(int ii=0; ii<8; ii++){
	c1->cd(ii+1);

	hE[ii]->SetLineColor(1);
	hE[ii]->SetLineWidth(3);
	hPi[ii]->SetLineColor(4);
	hPi[ii]->SetLineWidth(3);

	Double_t n1 = hE[ii]->Integral();
	Double_t n2 = hPi[ii]->Integral();
 
	if(n1>=n2){
	  hE[ii]->Draw();
	  hPi[ii]->Draw("same");
	  hE[ii]->SetTitle(";momentum (GeV);");
	  hE[ii]->GetXaxis()->SetRangeUser(0.1,50);
        }
	if(n2>n1){
	  hPi[ii]->Draw();
	  hE[ii]->Draw("same");
	  hPi[ii]->SetTitle(";momentum (GeV);");
	  hPi[ii]->GetXaxis()->SetRangeUser(0.1,50);
        }

	TLatex tex;
	tex.SetNDC();
	tex.SetTextSize(0.05);
	tex.DrawLatex(0.7,0.7,Form("%.1f<#eta<%.1f",eta_cut[ii],eta_cut[ii+1]));

	gPad->SetLogy();
	gPad->SetLogx();
     }

     c1->cd(9);
     TLatex tex1;
     tex1.SetNDC();
     tex1.SetTextSize(0.05);
     tex1.DrawLatex(0.2,0.8,Form("%d GeV * %d GeV with Radiation on",Ee,Ep));
     tex1.DrawLatex(0.2,0.65,"#color[1]{electron}");
     tex1.DrawLatex(0.2,0.5,"#color[4]{#pi^{-}}");
	
     TH1F *hPiE[8];

     TCanvas *c2 = new TCanvas("c2","c2",2000,1500);
     c2->Divide(3,3);
     for(int ii=0; ii<8; ii++){
	c2->cd(ii+1);

	hPiE[ii] = (TH1F *)hPi[ii]->Clone(Form("hPiE_%d",ii));
	hPiE[ii]->Divide(hE[ii]);

	hPiE[ii]->SetLineColor(4);
	hPiE[ii]->SetLineWidth(3);

        hPiE[ii]->Draw();
	hPiE[ii]->SetTitle(";momentum (GeV);");
	hPiE[ii]->GetXaxis()->SetRangeUser(0.1,50);


	TLatex tex;
	tex.SetNDC();
	tex.SetTextSize(0.05);
	tex.DrawLatex(0.7,0.7,Form("%.1f<#eta<%.1f",eta_cut[ii],eta_cut[ii+1]));

	gPad->SetLogy();
	gPad->SetLogx();
     }

     c2->cd(9);
     TLatex tex2;
     tex2.SetNDC();
     tex2.SetTextSize(0.05);
     tex2.DrawLatex(0.2,0.8,Form("%d GeV * %d GeV with Radiation on",Ee,Ep));
     tex2.DrawLatex(0.2,0.65,"#color[4]{#pi^{-}/e}");

     c1->Print(Form("outfiles/ep_%d_%d_pie.pdf[",Ee,Ep));
     c1->Print(Form("outfiles/ep_%d_%d_pie.pdf",Ee,Ep));
     c2->Print(Form("outfiles/ep_%d_%d_pie.pdf",Ee,Ep));
     c2->Print(Form("outfiles/ep_%d_%d_pie.pdf]",Ee,Ep));


}
