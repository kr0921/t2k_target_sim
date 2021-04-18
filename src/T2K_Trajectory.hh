#ifndef T2K_Trajectory_h
#define T2K_Trajectory_h

#include "G4VTrajectory.hh"
#include "G4Allocator.hh"
#include "G4ios.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4TrajectoryPoint.hh"
#include "G4Track.hh"
#include "G4Step.hh"

#include "T2K_TrajectoryPoint.hh"

class G4Polyline;         // Forward declaration.

typedef std::vector<G4VTrajectoryPoint*>  TrajectoryPointContainer;

class T2K_Trajectory : public G4VTrajectory
{
public:

  T2K_Trajectory();
  T2K_Trajectory(const G4Track* aTrack);
  T2K_Trajectory(T2K_Trajectory &);
  virtual ~T2K_Trajectory();

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  G4int GetTrackID() const {return fTrackID;}
  G4int GetParentID() const {return fParentID;}
  G4String GetParticleName() const {return "";}
  G4double GetCharge() const {return fPDGCharge;}
  G4int GetPDGEncoding() const {return fPDGEncoding;}
  G4ThreeVector GetInitialMomentum() const {return fInitialMomentum;}
  G4ThreeVector GetFinalMomentum() const {return fFinalMomentum;}
  G4ThreeVector GetInitialPosition() const {return fInitialPosition;}
  G4ThreeVector GetFinalPosition() const {return fFinalPosition;}

  G4String GetInitialVolumeName() const {return fInitialVolumeName;}
  G4String GetFinalVolumeName() const { return fFinalVolumeName;}

  G4String GetInitialProcessName() const {return fInitialProcessName;}
  G4String GetFinalProcessName() const {return fFinalProcessName;}

  G4double GetTrackLength() const {return fTrackLength;}

  /// Override pure virtual functions from G4VTrajectory
  virtual const std::map<G4String,G4AttDef>* GetAttDefs() const
  { return 0; }
  virtual std::vector<G4AttValue>* CreateAttValues() const
  { return 0; }

  virtual void AppendStep(const G4Step* aStep);
  virtual void MergeTrajectory(G4VTrajectory* secondTrajectory) {
    (void)secondTrajectory;
    return;
  }

  /// Get the number of trajectory points saved with this trajectory.
  virtual int GetPointEntries() const {return fPositionRecord->size();}
  /// Get a particular trajectory point.
  virtual G4VTrajectoryPoint* GetPoint(G4int i) const {
    return (*fPositionRecord)[i];
  }

private:
  TrajectoryPointContainer* fPositionRecord;
  G4int                     fTrackID;
  G4int                     fParentID;
  G4int                     fPDGEncoding;
  G4double                  fPDGCharge;

  // production
  G4String                  fInitialProcessName;
  G4ThreeVector             fInitialMomentum;
  G4ThreeVector             fInitialPosition;
  G4String                  fInitialVolumeName;

  // final
  G4String                  fFinalProcessName;
  G4ThreeVector             fFinalMomentum;
  G4ThreeVector             fFinalPosition;
  G4String                  fFinalVolumeName;

  G4double                  fTrackLength;


  // end of the traj
};

extern G4ThreadLocal G4Allocator<T2K_Trajectory>* T2K_TrajectoryAllocator;

inline void* T2K_Trajectory::operator new(size_t)
{
  if(!T2K_TrajectoryAllocator)
  T2K_TrajectoryAllocator = new G4Allocator<T2K_Trajectory>;
  return (void*)T2K_TrajectoryAllocator->MallocSingle();
}

inline void T2K_Trajectory::operator delete(void* aTrajectory)
{
  T2K_TrajectoryAllocator->FreeSingle((T2K_Trajectory*)aTrajectory);
}

#endif