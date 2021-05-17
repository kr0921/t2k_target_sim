#ifndef T2K_EventAction_h
#define T2K_EventAction_h


#include "G4UserEventAction.hh"
#include "globals.hh"
#include "T2K_Trajectory.hh"

#include <vector>
// #include <array>

/// Event action

class T2K_EventAction : public G4UserEventAction
{
public:
    T2K_EventAction();
    virtual ~T2K_EventAction();

    virtual void BeginOfEventAction(const G4Event*) {;};
    virtual void EndOfEventAction(const G4Event*);
    G4int GetTrajPIDById(const G4Event* event, const int id);
    bool GetParentChargeed(const G4Event* event, const int id);

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
