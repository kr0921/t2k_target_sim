//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Oct 12 16:57:08 2022 by ROOT version 6.22/03
// from TTree Particle/Particles information
// found on file: t2k_target_sim_run1-10_pi_pall_pot1e6.root
//////////////////////////////////////////////////////////

#ifndef Particle_h
#define Particle_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Particle {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        start_mom;
   Double_t        end_mom;
   Double_t        pid;
   Double_t        start_dir_x;
   Double_t        start_dir_y;
   Double_t        start_dir_z;
   Double_t        start_pos_x;
   Double_t        start_pos_y;
   Double_t        start_pos_z;
   Double_t        end_dir_x;
   Double_t        end_dir_y;
   Double_t        end_dir_z;
   Double_t        end_pos_x;
   Double_t        end_pos_y;
   Double_t        end_pos_z;
   Char_t          start_process[22];
   Char_t          end_process[22];
   Char_t          start_volume[7];
   Char_t          end_volume[7];
   Double_t        track_length;
   Double_t        parent_pid;
   Double_t        parent_id;
   Double_t        event;

   // List of branches
   TBranch        *b_start_mom;   //!
   TBranch        *b_end_mom;   //!
   TBranch        *b_pid;   //!
   TBranch        *b_start_dir_x;   //!
   TBranch        *b_start_dir_y;   //!
   TBranch        *b_start_dir_z;   //!
   TBranch        *b_start_pos_x;   //!
   TBranch        *b_start_pos_y;   //!
   TBranch        *b_start_pos_z;   //!
   TBranch        *b_end_dir_x;   //!
   TBranch        *b_end_dir_y;   //!
   TBranch        *b_end_dir_z;   //!
   TBranch        *b_end_pos_x;   //!
   TBranch        *b_end_pos_y;   //!
   TBranch        *b_end_pos_z;   //!
   TBranch        *b_start_process;   //!
   TBranch        *b_end_process;   //!
   TBranch        *b_start_volume;   //!
   TBranch        *b_end_volume;   //!
   TBranch        *b_track_length;   //!
   TBranch        *b_parent_pid;   //!
   TBranch        *b_parent_id;   //!
   TBranch        *b_event;   //!

   //Particle(TTree *tree=0);
   Particle(const char myfile[]);
   virtual ~Particle();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(double weight,TH1D* mom_hist,TH1D* theta_hist,TH2D* theta_mom_hist,double pid_0);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Particle_cxx
///Particle::Particle(TTree *tree) : fChain(0) 
Particle::Particle(const char myfile[]) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   TTree *tree;
   if (true /*tree == 0*/) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("t2k_target_sim_run1-10_pi_pall_pot1e6.root");
      if (!f || !f->IsOpen()) {
         //f = new TFile("t2k_target_sim_run1-10_pi_pall_pot1e6.root");
         f = new TFile(myfile);
      }
      f->GetObject("Particle",tree);

   }
   Init(tree);
}

Particle::~Particle()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Particle::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Particle::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Particle::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("start_mom", &start_mom, &b_start_mom);
   fChain->SetBranchAddress("end_mom", &end_mom, &b_end_mom);
   fChain->SetBranchAddress("pid", &pid, &b_pid);
   fChain->SetBranchAddress("start_dir_x", &start_dir_x, &b_start_dir_x);
   fChain->SetBranchAddress("start_dir_y", &start_dir_y, &b_start_dir_y);
   fChain->SetBranchAddress("start_dir_z", &start_dir_z, &b_start_dir_z);
   fChain->SetBranchAddress("start_pos_x", &start_pos_x, &b_start_pos_x);
   fChain->SetBranchAddress("start_pos_y", &start_pos_y, &b_start_pos_y);
   fChain->SetBranchAddress("start_pos_z", &start_pos_z, &b_start_pos_z);
   fChain->SetBranchAddress("end_dir_x", &end_dir_x, &b_end_dir_x);
   fChain->SetBranchAddress("end_dir_y", &end_dir_y, &b_end_dir_y);
   fChain->SetBranchAddress("end_dir_z", &end_dir_z, &b_end_dir_z);
   fChain->SetBranchAddress("end_pos_x", &end_pos_x, &b_end_pos_x);
   fChain->SetBranchAddress("end_pos_y", &end_pos_y, &b_end_pos_y);
   fChain->SetBranchAddress("end_pos_z", &end_pos_z, &b_end_pos_z);
   fChain->SetBranchAddress("start_process", start_process, &b_start_process);
   fChain->SetBranchAddress("end_process", end_process, &b_end_process);
   fChain->SetBranchAddress("start_volume", start_volume, &b_start_volume);
   fChain->SetBranchAddress("end_volume", end_volume, &b_end_volume);
   fChain->SetBranchAddress("track_length", &track_length, &b_track_length);
   fChain->SetBranchAddress("parent_pid", &parent_pid, &b_parent_pid);
   fChain->SetBranchAddress("parent_id", &parent_id, &b_parent_id);
   fChain->SetBranchAddress("event", &event, &b_event);
   Notify();
}

Bool_t Particle::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Particle::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Particle::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Particle_cxx
