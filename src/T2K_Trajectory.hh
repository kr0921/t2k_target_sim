#ifndef T2K_Trajectory_h
#define T2K_Trajectory_h 1

#include "G4Trajectory.hh"
#include "G4Allocator.hh"
#include "G4ios.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4TrajectoryPoint.hh"
#include "G4Track.hh"
#include "G4Step.hh"

class G4Polyline;                   // Forward declaration.

class T2K_Trajectory : public G4Trajectory
{
  public:

    T2K_Trajectory();
    T2K_Trajectory(const G4Track* aTrack);
    T2K_Trajectory(T2K_Trajectory &);
    virtual ~T2K_Trajectory();

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    //G4int GetPDG() {return PDG;}
    //G4float GetInitialEnergy() {return InitialEnergy;}
    G4float GetFinalEnergy() {return FinalEnergy;}

    //G4ThreeVector GetInitialMomentum() {return InitialMomentum;}
    G4ThreeVector GetFinalMomentum() {return FinalMomentum;}

    G4ThreeVector GetInitialPosition() {return InitialPosition;}
    G4ThreeVector GetFinalPosition() {return FinalPosition;}

    G4String GetFinalProcessName() {return FinalProcessName;}
    G4String GetFinalVolumeName() {return FinalVolumeName;}
    G4String GetInitialVolumeName() {return InitialVolumeName;}

    void SetInitialPosition(G4ThreeVector vect) {InitialPosition = vect;}
    void SetFinalPosition(G4ThreeVector vect) {FinalPosition = vect;}

    void SetFinalMomentum(G4ThreeVector vect) {FinalMomentum = vect;}

    void SetFinalEnergy(G4float e) {FinalEnergy = e;}

    void SetFinalProcessName(G4String s) {FinalProcessName = s;}
    void SetFinalVolumeName(G4String s) {FinalVolumeName = s;}
    void SetInitialVolumeName(G4String s) {InitialVolumeName = s;}

  private:
    //G4int PDG;

    //G4float InitialEnergy;
    G4float FinalEnergy;

    //G4ThreeVector InitialMomentum;
    G4ThreeVector FinalMomentum;

    G4ThreeVector InitialPosition;
    G4ThreeVector FinalPosition;

    G4String FinalProcessName;

    G4String InitialVolumeName;
    G4String FinalVolumeName;
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