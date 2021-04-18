#include "T2K_ActionInitialization.hh"
#include "T2K_PrimaryGeneratorAction.hh"
#include "T2K_RunAction.hh"
#include "T2K_EventAction.hh"
#include "T2K_UserTrackingAction.hh"


//******************************************************************************
T2K_ActionInitialization::T2K_ActionInitialization()
 : G4VUserActionInitialization() {;}
//******************************************************************************

//******************************************************************************
T2K_ActionInitialization::~T2K_ActionInitialization() {;}
//******************************************************************************


//******************************************************************************
void T2K_ActionInitialization::BuildForMaster() const {
//******************************************************************************
  SetUserAction(new T2K_RunAction);
}


//******************************************************************************
void T2K_ActionInitialization::Build() const {
//******************************************************************************
  SetUserAction(new T2K_PrimaryGeneratorAction);
  SetUserAction(new T2K_RunAction);
  SetUserAction(new T2K_EventAction);
  SetUserAction(new T2K_UserTrackingAction);
}
