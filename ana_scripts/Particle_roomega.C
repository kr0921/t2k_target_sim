#define Particle_cxx
#include "Particle.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Particle::Loop(double weight,TH1D* mom_hist,TH1D* theta_hist,TH2D* theta_mom_hist,double pid_0)
{
//   In a ROOT session, you can do:
//      root> .L Particle.C
//      root> Particle t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      //if(pid != 111) continue;
      if(pid != pid_0) continue;
      TVector3 vec(start_dir_x, start_dir_y, start_dir_z);
      
      mom_hist->Fill(start_mom/1000.,weight);
      theta_hist->Fill(vec.Theta(),weight);
      theta_mom_hist->Fill(start_mom/1000.,vec.Theta(),weight);
   }
   
}


void myrun_roomega(const char suf[]){
    
   //float pid_x = 113; //ro pid
   float pid_x = 223; //omega pid

   TString mom_hist_name("mom_");
   TString theta_hist_name("theta_");
   
   auto myfile = new TFile("hists_omega.root","RECREATE");
   auto mom_hist = new TH1D((mom_hist_name+suf).Data(),"momentum",100.,0.,30.);
   auto theta_hist = new TH1D((theta_hist_name+suf).Data(),"theta",100.,0.,3.1415927);
   auto theta_mom_hist = new TH2D((theta_hist_name+mom_hist_name+suf).Data(),"theta:momentum",3000.,0.,30.,3000.,0.,3.1415927);

   Particle t1("../genfiles_roomega/t2k_target_sim_run1-1000_roomega_p0-5_pot50e6.root");
   t1.Loop(100./50.,mom_hist,theta_hist,theta_mom_hist,pid_x);
   
   Particle t2("../genfiles_roomega/t2k_target_sim_run1-10000_roomega_p5-10_pot500e6.root");
   t2.Loop(100./500.,mom_hist,theta_hist,theta_mom_hist,pid_x);

   Particle t3("../genfiles_roomega/t2k_target_sim_run1-10000_roomega_p10-15_pot500e6.root");
   t3.Loop(100./(500.*2.),mom_hist,theta_hist,theta_mom_hist,pid_x);

   Particle t31("../genfiles_roomega/t2k_target_sim_run10001-20000_roomega_p10-15_pot500e6.root");
   t31.Loop(100./(500.*2.),mom_hist,theta_hist,theta_mom_hist,pid_x);

   //
   Particle t41("../genfiles_roomega/t2k_target_sim_run1-10000_roomega_p15-30_pot500e6.root");
   t41.Loop(100./(500.*12.),mom_hist,theta_hist,theta_mom_hist,pid_x);
   
   Particle t42("../genfiles_roomega/t2k_target_sim_run10001-20000_roomega_p15-30_pot500e6.root");
   t42.Loop(100./(500.*12.),mom_hist,theta_hist,theta_mom_hist,pid_x);
   
   Particle t43("../genfiles_roomega/t2k_target_sim_run20001-30000_roomega_p15-30_pot500e6.root");
   t43.Loop(100./(500.*12.),mom_hist,theta_hist,theta_mom_hist,pid_x);
   
   Particle t44("../genfiles_roomega/t2k_target_sim_run30001-40000_roomega_p15-30_pot500e6.root");
   t44.Loop(100./(500.*12.),mom_hist,theta_hist,theta_mom_hist,pid_x);
   
   Particle t45("../genfiles_roomega/t2k_target_sim_run40001-50000_roomega_p15-30_pot500e6.root");
   t45.Loop(100./(500.*12.),mom_hist,theta_hist,theta_mom_hist,pid_x);
   
   Particle t46("../genfiles_roomega/t2k_target_sim_run50001-60000_roomega_p15-30_pot500e6.root");
   t46.Loop(100./(500.*12.),mom_hist,theta_hist,theta_mom_hist,pid_x);
   
   Particle t47("../genfiles_roomega/t2k_target_sim_run60001-70000_roomega_p15-30_pot500e6.root");
   t47.Loop(100./(500.*12.),mom_hist,theta_hist,theta_mom_hist,pid_x);
   
   Particle t48("../genfiles_roomega/t2k_target_sim_run70001-80000_roomega_p15-30_pot500e6.root");
   t48.Loop(100./(500.*12.),mom_hist,theta_hist,theta_mom_hist,pid_x);
   
   Particle t49("../genfiles_roomega/t2k_target_sim_run80001-90000_roomega_p15-30_pot500e6.root");
   t49.Loop(100./(500.*12.),mom_hist,theta_hist,theta_mom_hist,pid_x);
   
   Particle t410("../genfiles_roomega/t2k_target_sim_run90001-100000_roomega_p15-30_pot500e6.root");
   t410.Loop(100./(500.*12.),mom_hist,theta_hist,theta_mom_hist,pid_x);
    
   Particle t411("../genfiles_roomega/t2k_target_sim_run100001-110000_roomega_p15-30_pot500e6.root");
   t411.Loop(100./(500.*12.),mom_hist,theta_hist,theta_mom_hist,pid_x);
    
   Particle t412("../genfiles_roomega/t2k_target_sim_run110001-120000_roomega_p15-30_pot500e6.root");
   t412.Loop(100./(500.*12.),mom_hist,theta_hist,theta_mom_hist,pid_x);
  
   
   
   
   myfile->cd(); 
   mom_hist->Write();
   theta_hist->Write();
   theta_mom_hist->Write();
   myfile->Close();
}



















///////////////////////////////////////////////////////////////////////////////
void myrun_eta(const char suf[]){
    
   float pid_eta = 221; //eta pid

   TString mom_hist_name("mom_");
   TString theta_hist_name("theta_");
   
   auto myfile = new TFile("hists_eta.root","RECREATE");
   auto mom_hist = new TH1D((mom_hist_name+suf).Data(),"momentum",100.,0.,30.);
   auto theta_hist = new TH1D((theta_hist_name+suf).Data(),"theta",100.,0.,3.1415927);
   auto theta_mom_hist = new TH2D((theta_hist_name+mom_hist_name+suf).Data(),"theta:momentum",3000.,0.,30.,3000.,0.,3.1415927);

   Particle t1("../../genfiles_eta/t2k_target_sim_run1-120_eta_p0-5_pot5e6.root");
   t1.Loop(1./5.,mom_hist,theta_hist,theta_mom_hist,pid_eta);
   
   Particle t2("../../genfiles_eta/t2k_target_sim_run1-840_eta_p5-10_pot42e6.root");
   t2.Loop(1./42.,mom_hist,theta_hist,theta_mom_hist,pid_eta);

   Particle t3("../../genfiles_eta/t2k_target_sim_run1-4440_eta_p10-15_pot222e6.root");
   t3.Loop(1./222.,mom_hist,theta_hist,theta_mom_hist,pid_eta);

   //
   Particle t41("../../genfiles_eta/t2k_target_sim_run1-10000_eta_p15-30_pot500e6.root");
   t41.Loop(1./(500.*10.),mom_hist,theta_hist,theta_mom_hist,pid_eta);
   
   Particle t42("../../genfiles_eta/t2k_target_sim_run10001-20000_eta_p15-30_pot500e6.root");
   t42.Loop(1./(500.*10.),mom_hist,theta_hist,theta_mom_hist,pid_eta);
   
   Particle t43("../../genfiles_eta/t2k_target_sim_run20001-30000_eta_p15-30_pot500e6.root");
   t43.Loop(1./(500.*10.),mom_hist,theta_hist,theta_mom_hist,pid_eta);
   
   Particle t44("../../genfiles_eta/t2k_target_sim_run30001-40000_eta_p15-30_pot500e6.root");
   t44.Loop(1./(500.*10.),mom_hist,theta_hist,theta_mom_hist,pid_eta);
   
   Particle t45("../../genfiles_eta/t2k_target_sim_run40001-50000_eta_p15-30_pot500e6.root");
   t45.Loop(1./(500.*10.),mom_hist,theta_hist,theta_mom_hist,pid_eta);
   
   Particle t46("../../genfiles_eta/t2k_target_sim_run50001-60000_eta_p15-30_pot500e6.root");
   t46.Loop(1./(500.*10.),mom_hist,theta_hist,theta_mom_hist,pid_eta);
   
   Particle t47("../../genfiles_eta/t2k_target_sim_run60001-70000_eta_p15-30_pot500e6.root");
   t47.Loop(1./(500.*10.),mom_hist,theta_hist,theta_mom_hist,pid_eta);
   
   Particle t48("../../genfiles_eta/t2k_target_sim_run70001-80000_eta_p15-30_pot500e6.root");
   t48.Loop(1./(500.*10.),mom_hist,theta_hist,theta_mom_hist,pid_eta);
   
   Particle t49("../../genfiles_eta/t2k_target_sim_run80001-90000_eta_p15-30_pot500e6.root");
   t49.Loop(1./(500.*10.),mom_hist,theta_hist,theta_mom_hist,pid_eta);
   
   Particle t410("../../genfiles_eta/t2k_target_sim_run90001-100000_eta_p15-30_pot500e6.root");
   t410.Loop(1./(500.*10.),mom_hist,theta_hist,theta_mom_hist,pid_eta);
   
   
   
   
   myfile->cd(); 
   mom_hist->Write();
   theta_hist->Write();
   theta_mom_hist->Write();
   myfile->Close();
}

////////////////////////////////
void myrun_pi0(const char suf[]){

   float pid_pi0 = 111; //pi0 pid

   TString mom_hist_name("mom_");
   TString theta_hist_name("theta_");
   
   auto myfile = new TFile("hists_pi0.root","RECREATE");
   auto mom_hist = new TH1D((mom_hist_name+suf).Data(),"momentum",100.,0.,30.);
   auto theta_hist = new TH1D((theta_hist_name+suf).Data(),"theta",100.,0.,3.1415927);
   auto theta_mom_hist = new TH2D((theta_hist_name+mom_hist_name+suf).Data(),"theta:momentum",3000.,0.,30.,3000.,0.,3.1415927);

   Particle t1("t2k_target_sim_run1-10_pi_p0-5_pot1e6.root");
   t1.Loop(1.,mom_hist,theta_hist,theta_mom_hist,pid_pi0);
   
   Particle t2("t2k_target_sim_run1-9_pi_p5-10_pot6e6.root");
   t2.Loop(1./6.,mom_hist,theta_hist,theta_mom_hist,pid_pi0);
   
   Particle t3("t2k_target_sim_run1-250_pi_p10-15_pot50e6.root");
   t3.Loop(1./50.,mom_hist,theta_hist,theta_mom_hist,pid_pi0);
   
   //Particle t4("t2k_target_sim_run1-670_pi_p15-30_pot134e6.root");
   //t4.Loop(1./134.,mom_hist,theta_hist,theta_mom_hist);
   Particle t4("t2k_target_sim_run1-1500_pi_p15-30_pot300e6.root");
   t4.Loop(1./300.,mom_hist,theta_hist,theta_mom_hist,pid_pi0);
    
   myfile->cd(); 
   mom_hist->Write();
   theta_hist->Write();
   theta_mom_hist->Write();
   myfile->Close();
}



