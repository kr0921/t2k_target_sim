////////////////////////////////////////////////////////////
// $Id: T2K_UserTrackingAction.cc,v 1.6 2007/01/01 05:32:49 mcgrew Exp $
//

#include "globals.hh"
#include "G4Track.hh"
#include "G4TrackingManager.hh"

#include "T2K_UserTrackingAction.hh"
#include "T2K_Trajectory.hh"

T2K_UserTrackingAction::T2K_UserTrackingAction() {}

T2K_UserTrackingAction::~T2K_UserTrackingAction() {}

void T2K_UserTrackingAction::PreUserTrackingAction(const G4Track* trk) {
  auto traj = new T2K_Trajectory(trk);
  fpTrackingManager->SetTrajectory(traj);

  auto PDG = traj->GetPDGEncoding();

  // if ((traj->GetCharge() == 0 || abs(PDG) == 211) &&
  //     PDG != 22 && abs(PDG) != 2112) {
    fpTrackingManager->SetStoreTrajectory(true);
    fpTrackingManager->SetTrajectory(new T2K_Trajectory(trk));
    return;
  // } else
  //   fpTrackingManager->SetStoreTrajectory(false);
}

