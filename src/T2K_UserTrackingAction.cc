////////////////////////////////////////////////////////////
// $Id: T2K_UserTrackingAction.cc,v 1.6 2007/01/01 05:32:49 mcgrew Exp $
//

#include "globals.hh"
#include "G4Track.hh"
#include "G4TrackingManager.hh"
#include "G4RunManager.hh"

#include "T2K_UserTrackingAction.hh"
#include "T2K_Trajectory.hh"
#include "T2K_Analysis.hh"

T2K_UserTrackingAction::T2K_UserTrackingAction() {}

T2K_UserTrackingAction::~T2K_UserTrackingAction() {}

void T2K_UserTrackingAction::PreUserTrackingAction(const G4Track* trk) {
 // fill production tree
  auto particle_PDG = trk->GetParticleDefinition()->GetPDGEncoding();

  if (trk->GetParticleDefinition()->GetPDGCharge() != 0 &&  abs(particle_PDG) != 211 && abs(particle_PDG) != 321)
      return;
   if (particle_PDG == 22 || particle_PDG == 2112)
      return;

  auto process_name = trk->GetCreatorProcess()->GetProcessName();

  auto analysisManager = G4AnalysisManager::Instance();
  auto Mom = trk->GetMomentum();
  auto MomDir = Mom;
  if (MomDir.mag() != 0)
    MomDir /= MomDir.mag();

  auto Position = trk->GetPosition();
  auto volume = trk->GetVolume()->GetName();

  auto parent_pid = -1;
  auto parent = trk->GetParentID();

  // std::cout << particle_PDG << "\t prod in\t" << volume << "\tin\t" << process_name << "\t with mom\t" << Mom.mag() << std::endl;

  // Fill decay tree
  analysisManager->FillNtupleDColumn(0, 0, Mom.mag());
  analysisManager->FillNtupleDColumn(0, 1, particle_PDG);
  analysisManager->FillNtupleDColumn(0, 2, MomDir.x());
  analysisManager->FillNtupleDColumn(0, 3, MomDir.y());
  analysisManager->FillNtupleDColumn(0, 4, MomDir.z());
  analysisManager->FillNtupleDColumn(0, 5, Position.x());
  analysisManager->FillNtupleDColumn(0, 6, Position.y());
  analysisManager->FillNtupleDColumn(0, 7, Position.z());
  analysisManager->FillNtupleDColumn(0, 8, parent);
  analysisManager->FillNtupleSColumn(0, 9, process_name);

  // // G4int parent_pid = GetTrajPIDById(event, parent);
  analysisManager->FillNtupleDColumn(0, 10, parent_pid);
  analysisManager->FillNtupleSColumn(0, 11, volume);

  analysisManager->AddNtupleRow(0);

  return;
}

void T2K_UserTrackingAction::PostUserTrackingAction(const G4Track* trk) {
  // fill decay tree
  auto particle_PDG = trk->GetParticleDefinition()->GetPDGEncoding();
  auto point = trk->GetStep()->GetPostStepPoint();

  if (!point)
    return;

  auto process_name = point->GetProcessDefinedStep()->GetProcessName();
  if (process_name != "Decay")
    return;

  auto analysisManager = G4AnalysisManager::Instance();
  auto Mom = point->GetMomentum();
  auto MomDir = Mom;
  if (MomDir.mag() != 0)
    MomDir /= MomDir.mag();

  auto Position = point->GetPosition();
  auto volume = point->GetPhysicalVolume()->GetName();

  auto parent_pid = -1;
  auto parent = trk->GetParentID();

  // std::cout << particle_PDG << "\t decay in\t" << volume << "\tin\t" << process_name << "\twith mom\t" << Mom.mag() << std::endl;

  // Fill decay tree
  analysisManager->FillNtupleDColumn(1, 0, Mom.mag());
  analysisManager->FillNtupleDColumn(1, 1, particle_PDG);
  analysisManager->FillNtupleDColumn(1, 2, MomDir.x());
  analysisManager->FillNtupleDColumn(1, 3, MomDir.y());
  analysisManager->FillNtupleDColumn(1, 4, MomDir.z());
  analysisManager->FillNtupleDColumn(1, 5, Position.x());
  analysisManager->FillNtupleDColumn(1, 6, Position.y());
  analysisManager->FillNtupleDColumn(1, 7, Position.z());
  analysisManager->FillNtupleDColumn(1, 8, parent);
  analysisManager->FillNtupleSColumn(1, 9, process_name);

  // // G4int parent_pid = GetTrajPIDById(event, parent);
  analysisManager->FillNtupleDColumn(1, 10, parent_pid);
  analysisManager->FillNtupleSColumn(1, 11, volume);

  analysisManager->AddNtupleRow(1);
  return;
}

