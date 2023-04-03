#include "T2K_EventAction.hh"
#include "T2K_Analysis.hh"


#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

using std::vector;


//******************************************************************************
T2K_EventAction::T2K_EventAction()
: G4UserEventAction() {
//******************************************************************************
  // set printing per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);
}

//******************************************************************************
T2K_EventAction::~T2K_EventAction() {;}
//******************************************************************************

//******************************************************************************
G4int T2K_EventAction::GetTrajPIDById(const G4Event* event, const int id) {
//******************************************************************************
  auto TrajCont = event->GetTrajectoryContainer();

  if (!TrajCont)
    return -1;

  for (uint trajID = 0; trajID < TrajCont->entries(); ++trajID) {
    auto traj = (T2K_Trajectory*)(*TrajCont)[trajID];
    if (!traj)
      continue;
    if (traj->GetTrackID() == id) {
      G4int particle_PDG = traj->GetPDGEncoding();
      return particle_PDG;
    }
  }
  return -1;

}

//******************************************************************************
bool T2K_EventAction::GetParentChargeed(const G4Event* event, const int id) {
//******************************************************************************
  auto TrajCont = event->GetTrajectoryContainer();

  if (!TrajCont)
    return true;

  for (uint trajID = 0; trajID < TrajCont->entries(); ++trajID) {
    auto traj = (T2K_Trajectory*)(*TrajCont)[trajID];
    if (!traj)
      continue;
    // found parent
    if (traj->GetTrackID() == id) {
      if (traj->GetCharge() != 0)
        return true;
      else {
        auto parent = traj->GetParentID();
        // stop recursion at primary
        if (traj->GetTrackID() == 1)
          return false;
        return GetParentChargeed(event, parent);
      }
    }
  }
  return false;

}

//******************************************************************************
void T2K_EventAction::EndOfEventAction(const G4Event* event) {
//******************************************************************************
  //
  // Fill histograms & ntuple
  //
  auto TrajCont = event->GetTrajectoryContainer();
  auto analysisManager = G4AnalysisManager::Instance();

  if (!TrajCont)
    return;

  for (uint trajID = 0; trajID < TrajCont->entries(); ++trajID) {
    auto traj = (T2K_Trajectory*)(*TrajCont)[trajID];

    auto pid = traj->GetPDGEncoding();

    // skip photons/ e+-/ neutrons / protons
    if (pid == 22 || abs(pid) == 11 || pid > 100000 || pid == 2112 || pid == 2212)
      continue;
    
    //SI stuff
    //if ( !(pid==111 || pid==211 || pid==-211) ) continue; //want Pi0/+/- only
    //if ( !(pid==111 || pid==221) ) continue; //want Pi0/+/- and eta only
    
    //if ( pid!=221 ) continue; //eta only
    //auto p_mom = traj->GetInitialMomentum().mag();
    ////if(p_mom>5000.0) continue;
    ////if( !(p_mom>5000.0 && p_mom<=10000.0) ) continue;
    ////if( !(p_mom>10000.0 && p_mom<=15000.0) ) continue;
    ////if( !(p_mom>15000.0 && p_mom<=20000.0) ) continue;
    //if(p_mom<15000.0) continue;

    if ( !(pid==113 || pid==223) ) continue; //ro0 or omega only
    auto p_mom = traj->GetInitialMomentum().mag();
    //if(p_mom>5000.0) continue;
    //if( !(p_mom>5000.0 && p_mom<=10000.0) ) continue;
    //if( !(p_mom>10000.0 && p_mom<=15000.0) ) continue;
    if(p_mom<15000.0) continue;
   
    
    
    
    analysisManager->FillNtupleDColumn(0, 2, pid);

    auto MomDir = traj->GetInitialMomentum();
    if (MomDir.mag() != 0)
      MomDir /= MomDir.mag();
    else
      MomDir = G4ThreeVector(0., 0., 0.);

    auto MomDirEnd = traj->GetFinalMomentum();
    if (MomDirEnd.mag() != 0)
      MomDirEnd /= MomDirEnd.mag();
    else
      MomDirEnd = G4ThreeVector(0., 0., 0.);

    auto parent = traj->GetParentID();

    // WARNING v11 specific
     if (traj->GetInitialVolumeName() != "TARGET" &&\
         GetParentChargeed(event, parent))
       continue;

    analysisManager->FillNtupleDColumn(0, 0, traj->GetInitialMomentum().mag());

    analysisManager->FillNtupleDColumn(0, 3, MomDir.x());
    analysisManager->FillNtupleDColumn(0, 4, MomDir.y());
    analysisManager->FillNtupleDColumn(0, 5, MomDir.z());

    analysisManager->FillNtupleDColumn(0, 1, traj->GetFinalMomentum().mag());

    analysisManager->FillNtupleDColumn(0, 9, MomDirEnd.x());
    analysisManager->FillNtupleDColumn(0, 10, MomDirEnd.y());
    analysisManager->FillNtupleDColumn(0, 11, MomDirEnd.z());

    analysisManager->FillNtupleSColumn(0, 15, traj->GetInitialProcessName());
    analysisManager->FillNtupleSColumn(0, 16, traj->GetFinalProcessName());

    analysisManager->FillNtupleSColumn(0, 17, traj->GetInitialVolumeName());
    analysisManager->FillNtupleSColumn(0, 18, traj->GetFinalVolumeName());

    auto startPos = traj->GetInitialPosition();
    analysisManager->FillNtupleDColumn(0, 6, startPos.x());
    analysisManager->FillNtupleDColumn(0, 7, startPos.y());
    analysisManager->FillNtupleDColumn(0, 8, startPos.z());

    auto endPos = traj->GetFinalPosition();
    analysisManager->FillNtupleDColumn(0, 12, endPos.x());
    analysisManager->FillNtupleDColumn(0, 13, endPos.y());
    analysisManager->FillNtupleDColumn(0, 14, endPos.z());

    analysisManager->FillNtupleDColumn(0, 21, parent);
    auto parent_pid = GetTrajPIDById(event, parent);
    analysisManager->FillNtupleDColumn(0, 20, parent_pid);

    analysisManager->FillNtupleDColumn(0, 22, event->GetEventID());

    analysisManager->FillNtupleDColumn(0, 19, traj->GetTrackLength());


    analysisManager->AddNtupleRow(0);
  } // traj loop
}
