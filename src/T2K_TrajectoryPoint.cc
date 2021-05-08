#include "T2K_TrajectoryPoint.hh"

G4Allocator<T2KTrajectoryPoint> aT2KTrajectoryPointAllocator;

//******************************************************************************
T2KTrajectoryPoint::T2KTrajectoryPoint(const G4Step* aStep):
G4TrajectoryPoint(aStep->GetPostStepPoint()->GetPosition()) {
//******************************************************************************
  auto prePoint = aStep->GetPreStepPoint();
  if (prePoint)
    fMomentum = prePoint->GetMomentum();

  // auto postPoint = aStep->GetPostStepPoint();
  // if (postPoint)
    // fPosition = aStep->GetPostStepPoint()->GetPosition();
}

//******************************************************************************
T2KTrajectoryPoint::T2KTrajectoryPoint(const G4Track* aTrack):
  G4TrajectoryPoint(aTrack->GetPosition()) {
//******************************************************************************
  (void)aTrack;
  fMomentum = aTrack->GetMomentum();
}