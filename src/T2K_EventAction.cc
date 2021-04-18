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

    auto parent = traj->GetParentID();
    analysisManager->FillNtupleDColumn(0, 21, parent);
    auto parent_pid = GetTrajPIDById(event, parent);
    analysisManager->FillNtupleDColumn(0, 20, parent_pid);

    analysisManager->FillNtupleDColumn(0, 19, traj->GetTrackLength());


    analysisManager->AddNtupleRow(0);




    // std::cout << "Traj #" << trajID << std::endl;
    // std::cout << "pid = \t" << traj->GetPDGEncoding() << std::endl;
    // std::cout << "Npoints: " << traj->GetPointEntries() << std::endl;
    // for (auto pId = 0; pId < traj->GetPointEntries(); ++pId) {
    //   auto point = dynamic_cast<T2KTrajectoryPoint*>(traj->GetPoint(pId));
    //   if (!point)
    //     continue;

    //   std::cout << "point " << pId << " at z " << point->GetPosition().z() << "\t" << point->GetMomentum().z() << std::endl;
    //   std::cout << "process\t" << point->GetProcessName() << "\tvol\t" << point->GetVolumeName() << std::endl;
    // }
  } // traj loop
}
