R__LOAD_LIBRARY(libeicsmear)

void make_tree(std::string filstr){

  erhic::DisKinematics::BoundaryWarning=false; //Need to comment this for eic account
  
  std::string dirstr = "rootfiles";
  std::string inputstr = "datafiles/"+filstr;
  BuildTree(inputstr,dirstr);
}
