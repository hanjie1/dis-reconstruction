R__LOAD_LIBRARY(libeicsmear);

void PlotPID(){
     int Ee = 5;
     int Ep = 50;
     
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
     TLorentzVector positron;
     TLorentzVector gamma;
     TLorentzVector p;
     Double_t eta,pp;

     TH1F *hE[7];
     TH1F *hPositron[7];
     TH1F *hP[7];
     TH1F *hGamma[7];
     TH1F *hEmP[7];

     for(int ii=0;ii<7;ii++){
	hE[ii] =new TH1F(Form("hE_%d",ii),Form("electron momentum distribution %d",ii),1000,0,50);
	hPositron[ii] =new TH1F(Form("hPositron_%d",ii),Form("positron momentum distribution %d",ii),1000,0,50);
	hGamma[ii] =new TH1F(Form("hGamma_%d",ii),Form("gamma momentum distribution %d",ii),1000,0,50);
	hP[ii] =new TH1F(Form("hP_%d",ii),Form("hadron momentum distribution %d",ii),1000,0,50);
     }

     Double_t eta_cut[8]={-5,-4,-3,-2,-1,0,1,5};
 
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
	       for(int kk=0; kk<7; kk++){
		if(eta<eta_cut[kk+1] && eta>eta_cut[kk]) hE[kk]->Fill(pp);
	       }
	    }
            if(id==-11){
	       eta=0; pp=0;
	       positron.SetPxPyPzE(particle->px,particle->py,particle->pz,particle->E);
	       eta = positron.Eta();
	       pp = positron.P();
	       for(int kk=0; kk<7; kk++){
		if(eta<eta_cut[kk+1] && eta>eta_cut[kk]) hPositron[kk]->Fill(pp);
	       }
	    }
            if(id==22){
	       eta=0; pp=0;
 	       gamma.SetPxPyPzE(particle->px,particle->py,particle->pz,particle->E);
	       eta = gamma.Eta();
	       pp = gamma.P();
	       for(int kk=0; kk<7; kk++){
		if(eta<eta_cut[kk+1] && eta>eta_cut[kk]) hGamma[kk]->Fill(pp);
	       }
	    }
            if((abs(id)==211) ||( abs(id)==321) || id==2212 || id==2112){
	       eta=0; pp=0;
	       p.SetPxPyPzE(particle->px,particle->py,particle->pz,particle->E);
	       eta = p.Eta();
	       pp = p.P();
	       for(int kk=0; kk<7; kk++){
		if(eta<eta_cut[kk+1] && eta>eta_cut[kk]) hP[kk]->Fill(pp);
	       }
	    }
	  }
	}
     }

     gStyle->SetOptStat(0);
     TCanvas *c1 = new TCanvas("c1","c1",2000,1500);
     c1->Divide(4,2);
     for(int ii=0; ii<7; ii++){
	c1->cd(ii+1);

	hEmP[ii] = (TH1F *)hE[ii]->Clone(Form("hEmP_%d",ii));
	hEmP[ii]->Add(hPositron[ii],-1);

	hE[ii]->SetLineColor(1);
	hE[ii]->SetLineWidth(3);
	hPositron[ii]->SetLineColor(8);
	hPositron[ii]->SetLineWidth(3);
	hGamma[ii]->SetLineColor(4);
	hGamma[ii]->SetLineWidth(3);
	hP[ii]->SetLineColor(2);
	hP[ii]->SetLineWidth(3);

	hEmP[ii]->SetLineColor(6);
	hEmP[ii]->SetLineWidth(3);

	Double_t n1 = hE[ii]->Integral();
	Double_t n4 = hPositron[ii]->Integral();
	Double_t n2 = hGamma[ii]->Integral();
	Double_t n3 = hP[ii]->Integral();
 
	if(n1>=n2 && n1>=n3 && n1>=n4){
	  hE[ii]->Draw();
	  hPositron[ii]->Draw("same");
	  hGamma[ii]->Draw("same");
	  hP[ii]->Draw("same");
	  hEmP[ii]->Draw("same");
	  hE[ii]->SetTitle(";momentum (GeV);");
	  hE[ii]->GetXaxis()->SetRangeUser(0.1,50);
        }
	if(n2>n1 && n2>=n3 && n2>=n4){
	  hGamma[ii]->Draw();
	  hE[ii]->Draw("same");
	  hPositron[ii]->Draw("same");
	  hP[ii]->Draw("same");
	  hEmP[ii]->Draw("same");
	  hGamma[ii]->SetTitle(";momentum (GeV);");
	  hGamma[ii]->GetXaxis()->SetRangeUser(0.1,50);
        }
	if(n3>n2 && n3>n1 && n3>=n4){
	  hP[ii]->Draw();
	  hE[ii]->Draw("same");
	  hPositron[ii]->Draw("same");
	  hGamma[ii]->Draw("same");
	  hEmP[ii]->Draw("same");
	  hP[ii]->SetTitle(";momentum (GeV);");
	  hP[ii]->GetXaxis()->SetRangeUser(0.1,50);
        }

	if(n4>n1 && n4>n2 && n4>n3){
	  hPositron[ii]->Draw();
	  hE[ii]->Draw("same");
	  hP[ii]->Draw("same");
	  hGamma[ii]->Draw("same");
	  hEmP[ii]->Draw("same");
	  hPositron[ii]->SetTitle(";momentum (GeV);");
	  hPositron[ii]->GetXaxis()->SetRangeUser(0.1,50);
        }


	TLatex tex;
	tex.SetNDC();
	tex.SetTextSize(0.05);
	tex.DrawLatex(0.7,0.7,Form("%.0f<#eta<%.0f",eta_cut[ii],eta_cut[ii+1]));

	gPad->SetLogy();
	gPad->SetLogx();
     }

     c1->cd(8);
     TLatex tex1;
     tex1.SetNDC();
     tex1.SetTextSize(0.05);
     tex1.DrawLatex(0.2,0.8,Form("%d GeV * %d GeV with Radiation on",Ee,Ep));
     tex1.DrawLatex(0.2,0.65,"#color[1]{electron}");
     tex1.DrawLatex(0.2,0.5,"#color[2]{hadron (#pi^{#pm}, K^{#pm}, p, n)}");
     tex1.DrawLatex(0.2,0.35,"#color[4]{photon}");
     tex1.DrawLatex(0.2,0.2,"#color[8]{positron}");
     tex1.DrawLatex(0.2,0.1,"#color[6]{electron - positron}");
	
     TH1F *hPE[7];
     TH1F *hGammaE[7];
     TH1F *hPositronE[7];

     TCanvas *c2 = new TCanvas("c2","c2",2000,1500);
     c2->Divide(4,2);
     for(int ii=0; ii<7; ii++){
	c2->cd(ii+1);

	hPE[ii] = (TH1F *)hP[ii]->Clone(Form("hPE_%d",ii));
	hPE[ii]->Divide(hEmP[ii]);

	hGammaE[ii] = (TH1F *)hGamma[ii]->Clone(Form("hGammaE_%d",ii));
	hGammaE[ii]->Divide(hEmP[ii]);

	hPositronE[ii] = (TH1F *)hPositron[ii]->Clone(Form("hPositronE_%d",ii));
	hPositronE[ii]->Divide(hE[ii]);

	hPE[ii]->SetLineColor(4);
	hPE[ii]->SetLineWidth(3);
	hGammaE[ii]->SetLineColor(1);
	hGammaE[ii]->SetLineWidth(3);
	hPositronE[ii]->SetLineColor(8);
	hPositronE[ii]->SetLineWidth(3);

	Double_t n1 = hPE[ii]->Integral();
	Double_t n2 = hGammaE[ii]->Integral();
	Double_t n3 = hPositronE[ii]->Integral();

	if(n1>=n2){
	  hPE[ii]->Draw();
	  hGammaE[ii]->Draw("same");
	  hPE[ii]->SetTitle(";momentum (GeV);");
	  hPE[ii]->GetXaxis()->SetRangeUser(0.1,50);
        }
	if(n2>n1){
	  hGammaE[ii]->Draw();
	  hPE[ii]->Draw("same");
	  hGammaE[ii]->SetTitle(";momentum (GeV);");
	  hGammaE[ii]->GetXaxis()->SetRangeUser(0.1,50);
        }


	TLatex tex;
	tex.SetNDC();
	tex.SetTextSize(0.05);
	tex.DrawLatex(0.7,0.7,Form("%.0f<#eta<%.0f",eta_cut[ii],eta_cut[ii+1]));

	gPad->SetLogy();
	gPad->SetLogx();
     }

     c2->cd(8);
     TLatex tex2;
     tex2.SetNDC();
     tex2.SetTextSize(0.05);
     tex2.DrawLatex(0.2,0.8,Form("%d GeV * %d GeV with Radiation on",Ee,Ep));
     tex2.DrawLatex(0.2,0.65,"#color[4]{hadron/electron  (#pi^{#pm}, K^{#pm}, p, n)}");
     tex2.DrawLatex(0.2,0.5,"#color[1]{photon/electron}");
/*
     TCanvas *c3 = new TCanvas("c3","c3",1500,1500);
     c3->Divide(4,2);
     for(int ii=0; ii<7; ii++){
	  c3->cd(ii+1);
	  hPositronE[ii]->Draw();
	  hPositronE[ii]->SetTitle("");
	  hPositronE[ii]->GetXaxis()->SetRangeUser(0.1,50);
	  gPad->SetLogx();

 	TLatex tex;
	tex.SetNDC();
	tex.SetTextSize(0.025);
	tex.DrawLatex(0.7,0.7,Form("%.0f<#eta<%.0f",eta_cut[ii],eta_cut[ii+1]));
     }

     c3->cd(8);
     TLatex tex3;
     tex3.SetNDC();
     tex3.SetTextSize(0.05);
     tex3.DrawLatex(0.2,0.8,Form("%d GeV * %d GeV with Radiation on",Ee,Ep));
     tex3.DrawLatex(0.2,0.65,"#color[8]{positron/electron}");
*/

}
