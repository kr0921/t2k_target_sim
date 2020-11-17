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

G4ThreadLocal G4Allocator<T2K_Trajectory>* T2K_TrajectoryAllocator = nullptr;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T2K_Trajectory::T2K_Trajectory()
  :G4Trajectory()
{
  //fParticleDefinition = nullptr;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T2K_Trajectory::T2K_Trajectory(const G4Track* aTrack)
  :G4Trajectory(aTrack)
{
  //fParticleDefinition=aTrack->GetDefinition();
  //PDG = aTrack->GetParticleDefinition()->GetPDGEncoding();
  InitialPosition = aTrack->GetPosition();
  InitialVolumeName = aTrack->GetVolume()->GetName();
  ParentID = aTrack->GetParentID();
  const G4VProcess* proc = aTrack->GetCreatorProcess();
  if (proc)
    process = proc->GetProcessName();
  else
    process = "primary";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T2K_Trajectory::T2K_Trajectory(T2K_Trajectory &right)
  :G4Trajectory(right)
{
  //fParticleDefinition=right.fParticleDefinition;
  //PDG = right.PDG;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T2K_Trajectory::~T2K_Trajectory() {}