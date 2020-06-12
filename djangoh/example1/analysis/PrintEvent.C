R__LOAD_LIBRARY(libeicsmear);

void PrintEvent(){
     TFile *f1 = new TFile("../outfiles/djangoh_ep_20_250_noRC_Q2_0_evt.root","READ");
     TTree *T = (TTree *)f1->Get("EICTree");

     int Ee = 20;
     int Ep = 250;

     //Event Class
     erhic::EventDjangoh *event(NULL); //Note that I use Pointer
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

     Double_t eta_cut[8]={-5,-4,-3,-2,-1,0,1,5};

     int nn=0;
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
/*            if(id==11){
	       eta=0; pp=0;
	       e.SetPxPyPzE(particle->px,particle->py,particle->pz,particle->E);
	       eta = e.Eta();
	       pp = e.P();
	       if(pp<=20 && pp>19.9 && eta<eta_cut[1] && eta>eta_cut[0]){
	 	cout<<"----------- event "<<ii<<" --------------"<<endl;
		T->Show(ii);
		cout<<endl;
		cout<<endl;
		nn++;
	       }
	    }
*/           if(id==-11){
	       eta=0; pp=0;
	       positron.SetPxPyPzE(particle->px,particle->py,particle->pz,particle->E);
	       eta = e.Eta();
	       pp = e.P();
	       if(pp<=20 && pp>19.9 && eta<eta_cut[1] && eta>eta_cut[0]){
	 	cout<<"----------- event "<<ii<<" --------------"<<endl;
		T->Show(ii);
		cout<<endl;
		cout<<endl;
	       }
	    }
	  }
	}
     }
	
     cout<<"nevents:  "<<nn<<endl; 

}
