////////////////////////////////////////////////////////////
// $Id: T2K_UserTrackingAction.hh,v 1.3 2004/03/18 20:49:27 t2k Exp $
//
#ifndef T2K_UserTrackingAction_h
#define T2K_UserTrackingAction_h 1

#include "G4UserTrackingAction.hh"
class G4Track;

class T2K_UserTrackingAction : public G4UserTrackingAction
{
  public:
    T2K_UserTrackingAction();
    virtual ~T2K_UserTrackingAction();

    virtual void PreUserTrackingAction(const G4Track*);
    virtual void PostUserTrackingAction(const G4Track*);
};
#endif
