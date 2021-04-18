#ifndef T2K_TrajectoryPoint
#define T2K_TrajectoryPoint

#include "G4TrajectoryPoint.hh"
#include "G4ThreeVector.hh"
#include "G4Step.hh"


class G4Track;
class G4Step;
// class G4VProcess;

class T2KTrajectoryPoint : public G4TrajectoryPoint
{
public:
  T2KTrajectoryPoint() {;}
  T2KTrajectoryPoint(const G4Track* aTrack);
  T2KTrajectoryPoint(const G4Step* aStep);
  virtual ~T2KTrajectoryPoint() {;}

  inline void *operator new(size_t);
  inline void operator delete(void *aT2KTrajectoryPoint);
  inline int operator==(const T2KTrajectoryPoint& right) const
  { return (this==&right); };

  G4ThreeVector GetMomentum() {return fMomentum;}
  G4String GetProcessName() {return fProcessName;}
  G4String GetVolumeName() {return fVolumeName;}

  void SetProcessName(G4String var) {fProcessName = var;}
  void SetVolumeName(G4String var) {fVolumeName = var;}

private:
  G4ThreeVector fMomentum;
  G4String fProcessName;
  G4String fVolumeName;

};

#if defined G4TRACKING_ALLOC_EXPORT
extern G4DLLEXPORT G4Allocator<T2KTrajectoryPoint> aT2KTrajectoryPointAllocator;
#else
extern G4DLLIMPORT G4Allocator<T2KTrajectoryPoint> aT2KTrajectoryPointAllocator;
#endif

inline void* T2KTrajectoryPoint::operator new(size_t) {
  void *aTrajectoryPoint = (void *) aT2KTrajectoryPointAllocator.MallocSingle();
  return aTrajectoryPoint;
}

inline void T2KTrajectoryPoint::operator delete(void *aTrajectoryPoint) {
  aT2KTrajectoryPointAllocator.FreeSingle(
             (T2KTrajectoryPoint *) aTrajectoryPoint);
}
#endif
