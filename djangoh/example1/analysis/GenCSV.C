R__LOAD_LIBRARY(libeicsmear);

void GenCSV(){

     TFile *f0 = new TFile("../outfiles/djangoh.ep.5x100.5Mevents.1.RadCor=1_evt.root");
     TTree *T = (TTree *) f0->Get("EICTree");

     //Event Class
     erhic::EventDjangoh *event(NULL); //Note that I use Pointer

     T->SetBranchAddress("event", &event);

     Int_t nentries = T->GetEntries();
     cout<<"Total events:  "<<nentries<<endl;

     //ofstream outfile;
     //outfile.open("djangoh_XYQ2W2.csv");

     Double32_t X,Y,W2,Q2;
     int nn=0;
     for(int ii=0;ii<nentries;ii++){
	T->GetEntry(ii);
	X = event->dtrueX;
	Y = event->dtrueY;
	Q2 = event->dtrueQ2;
	W2 = event->dtrueW2;
	//outfile<<ii+1<<","<<X<<","<<Y<<","<<Q2<<","<<W2<<endl;
	if(Y>0.95){
	   cout<<nn<<"  "<<Y<<endl;
	   nn++;
	}
     }
    // outfile.close();
     delete T;

}
