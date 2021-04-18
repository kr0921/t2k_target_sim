#ifndef T2K_UserTrackingAction_h
#define T2K_UserTrackingAction_h

#include "G4UserTrackingAction.hh"
class G4Track;

class T2K_UserTrackingAction : public G4UserTrackingAction
{
  public:
    T2K_UserTrackingAction();
    virtual ~T2K_UserTrackingAction();

    virtual void PreUserTrackingAction(const G4Track*);
    virtual void PostUserTrackingAction(const G4Track*) {;}

};
#endif
