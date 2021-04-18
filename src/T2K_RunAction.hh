#ifndef T2K_RunAction_h
#define T2K_RunAction_h

#include "G4UserRunAction.hh"
#include "globals.hh"

class T2K_EventAction;

class G4Run;

/// Run action class

class T2K_RunAction : public G4UserRunAction
{
  public:
    T2K_RunAction();
    virtual ~T2K_RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

  private:
    T2K_EventAction* fEventAction;
};

#endif
