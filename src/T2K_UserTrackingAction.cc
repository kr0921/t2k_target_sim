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
    G4VTrajectory* traj = new T2K_Trajectory(trk);
    fpTrackingManager->SetTrajectory(traj);
    if (traj->GetCharge() == 0 && abs(traj->GetPDGEncoding() != 211)) {
      if (traj->GetPDGEncoding() == 22)
        return;
      if (abs(traj->GetPDGEncoding()) == 2112)
        return;

      fpTrackingManager->SetStoreTrajectory(true);
    }

    //G4cout << traj->GetPointEntries() << G4endl; //GetRange();
}

void T2K_UserTrackingAction::PostUserTrackingAction(const G4Track* trk) {
  T2K_Trajectory* trajectory =
    (T2K_Trajectory*)fpTrackingManager->GimmeTrajectory();

  auto step = trk->GetStep();

  auto TrackPoint = step->GetPreStepPoint();
  if (TrackPoint == NULL)
    return;

  G4String process_name_post = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();

  G4double energy_pre = TrackPoint->GetKineticEnergy();

  auto MomDir     = TrackPoint->GetMomentumDirection();
  MomDir /= MomDir.mag();
  auto Position   = TrackPoint->GetPosition();
  auto Momentum   = TrackPoint->GetMomentum();
  auto VolumeName = TrackPoint->GetPhysicalVolume()->GetName();

  trajectory->SetFinalPosition(Position);
  trajectory->SetFinalEnergy(energy_pre);
  trajectory->SetFinalMomentum(Momentum);
  trajectory->SetFinalProcessName(process_name_post);
  trajectory->SetFinalVolumeName(VolumeName);
}

