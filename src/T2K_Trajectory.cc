#include "T2K_Trajectory.hh"
#include "G4TrajectoryPoint.hh"
#include "G4Trajectory.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleTypes.hh"
#include "G4ThreeVector.hh"
#include "G4Polyline.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4VVisManager.hh"
#include "G4Polymarker.hh"
#include <G4VProcess.hh>

#include "T2K_TrajectoryPoint.hh"

G4ThreadLocal G4Allocator<T2K_Trajectory>* T2K_TrajectoryAllocator = nullptr;

//******************************************************************************
T2K_Trajectory::T2K_Trajectory():
   fPositionRecord(0),
   fTrackID(0),
   fParentID(0),
   fPDGEncoding(0),
   fPDGCharge(0),
   fInitialProcessName(""),
   fInitialMomentum(0),
   fInitialPosition(0),
   fInitialVolumeName(""),
   fTrackLength(0.)
   {
//******************************************************************************
  //fParticleDefinition = nullptr;
}

//******************************************************************************
T2K_Trajectory::T2K_Trajectory(const G4Track* aTrack) {
//******************************************************************************
  fPositionRecord = new TrajectoryPointContainer();
  auto point = new T2KTrajectoryPoint(aTrack);
  // Initial params
  const G4VProcess* proc = aTrack->GetCreatorProcess();
  if (proc)
    fInitialProcessName = proc->GetProcessName();
  else
    fInitialProcessName = "primary";
  fInitialPosition = aTrack->GetPosition();
  fInitialVolumeName = aTrack->GetVolume()->GetName();
  fParentID = aTrack->GetParentID();
  fInitialMomentum = aTrack->GetMomentum();


  point->SetProcessName(fInitialProcessName);
  point->SetVolumeName(fInitialVolumeName);
  fPositionRecord->push_back(point);

  fTrackID = aTrack->GetTrackID();
  fParentID = aTrack->GetParentID();
  fPDGEncoding = aTrack->GetParticleDefinition()->GetPDGEncoding();
  fPDGCharge = aTrack->GetParticleDefinition()->GetPDGCharge();

}

//******************************************************************************
T2K_Trajectory::T2K_Trajectory(T2K_Trajectory &right) {
//******************************************************************************
  //fParticleDefinition=right.fParticleDefinition;
  fTrackID = right.fTrackID;
  fParentID = right.fParentID;
  fPDGEncoding = right.fPDGEncoding;
  fPDGCharge = right.fPDGCharge;

  // initial
  fInitialProcessName = right.fInitialProcessName;
  fInitialMomentum = right.fInitialMomentum;
  fInitialPosition = right.fInitialPosition;
  fInitialVolumeName = right.fInitialVolumeName;

  // final
  fFinalProcessName = right.fFinalProcessName;
  fFinalMomentum = right.fFinalMomentum;
  fFinalPosition = right.fFinalPosition;
  fFinalVolumeName = right.fFinalVolumeName;

  fTrackLength = right.fTrackLength;
}

T2K_Trajectory::~T2K_Trajectory() {;}

//******************************************************************************
void T2K_Trajectory::AppendStep(const G4Step* aStep) {
//******************************************************************************
  auto T2K_point = new T2KTrajectoryPoint(aStep);
  // process in the final point is stored in postPoint
  // But the moomentum at post point is 0, so should use prePoint

  auto prePoint = aStep->GetPreStepPoint();
  auto postPoint = aStep->GetPostStepPoint();

  fTrackLength += aStep->GetStepLength();
  if (prePoint) {
    fFinalMomentum = prePoint->GetMomentum();
    if (prePoint->GetPhysicalVolume())
      T2K_point->SetVolumeName(prePoint->GetPhysicalVolume()->GetName());
  }

  if (postPoint) {
    auto process = postPoint->GetProcessDefinedStep();
    if (process)
      T2K_point->SetProcessName(process->GetProcessName());
    else
      T2K_point->SetProcessName("primary");
    if (postPoint->GetPhysicalVolume())
      T2K_point->SetVolumeName(postPoint->GetPhysicalVolume()->GetName());
    fFinalProcessName = T2K_point->GetProcessName();
    fFinalVolumeName = T2K_point->GetVolumeName();
    fFinalPosition = T2K_point->GetPosition();
  }

  fPositionRecord->push_back(T2K_point);
}
