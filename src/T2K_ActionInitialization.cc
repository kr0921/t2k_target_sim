//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file T2K_ActionInitialization.cc
/// \brief Implementation of the T2K_ActionInitialization class

#include "T2K_ActionInitialization.hh"
#include "T2K_PrimaryGeneratorAction.hh"
#include "T2K_RunAction.hh"
#include "T2K_EventAction.hh"
#include "T2K_UserTrackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T2K_ActionInitialization::T2K_ActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T2K_ActionInitialization::~T2K_ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void T2K_ActionInitialization::BuildForMaster() const
{
  T2K_EventAction* eventAction = new T2K_EventAction;
  SetUserAction(new T2K_RunAction(eventAction));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void T2K_ActionInitialization::Build() const
{
  SetUserAction(new T2K_PrimaryGeneratorAction);

  auto eventAction = new T2K_EventAction;
  SetUserAction(eventAction);

  SetUserAction(new T2K_RunAction(eventAction));
  SetUserAction(new T2K_UserTrackingAction());
  // OBSOLETE. Was used for the first checks
  // SetUserAction(new T2K_SteppingAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
