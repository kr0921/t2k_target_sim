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
/// \file T2K_EventAction.cc
/// \brief Implementation of the T2K_EventAction class

#include "T2K_EventAction.hh"
#include "T2K_Analysis.hh"


#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

using std::array;
using std::vector;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T2K_EventAction::T2K_EventAction()
: G4UserEventAction()
  //fHodHCID  {{ -1, -1 }},
  //fDriftHCID{{ -1, -1 }},
  //fCalHCID  {{ -1, -1 }},
  //fDriftHistoID{{ {{ -1, -1 }}, {{ -1, -1 }} }},
  //fCalEdep{{ vector<G4double>(kNofEmCells, 0.), vector<G4double>(kNofHadCells, 0.) }}
      // std::array<T, N> is an aggregate that contains a C array.
      // To initialize it, we need outer braces for the class itself
      // and inner braces for the C array
{
  // set printing per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T2K_EventAction::~T2K_EventAction()
{}

G4int T2K_EventAction::GetTrajPIDById(const G4Event* event, const int id) {
  auto TrajCont = event->GetTrajectoryContainer();

  if (!TrajCont)
    return -1;

  for (uint trajID = 0; trajID < TrajCont->entries(); ++trajID) {
    auto traj = (T2K_Trajectory*)(*TrajCont)[trajID];
    if (!traj)
      continue;
    if (traj->GetTrackID() == id) {
      G4int particle_PDG = traj->GetPDGEncoding();
      return particle_PDG;
    }
  }
  return -1;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void T2K_EventAction::EndOfEventAction(const G4Event* event)
{
  //
  // Fill histograms & ntuple
  //
  (void)event;
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  if(event->GetNumberOfPrimaryVertex()==0) {
    G4cout << "Event is empty." << G4endl;
    return;
  }

  // study how often pions/kaons leave the target
  auto TrajCont = event->GetTrajectoryContainer();

  if (!TrajCont)
    return;

  for (uint trajID = 0; trajID < TrajCont->entries(); ++trajID) {
    auto traj = (T2K_Trajectory*)(*TrajCont)[trajID];
    if (!traj)
      continue;
    auto particle_PDG = traj->GetPDGEncoding();

    // interested only in neutral particles
    if (traj->GetCharge() != 0 &&  abs(particle_PDG) != 211)
      continue;
    // suppress photons
    if (particle_PDG == 22)
      continue;

    // suppress neutrons
    if (abs(particle_PDG) == 2112)
      continue;

    G4ThreeVector Mom     = traj->GetInitialMomentum();
    G4ThreeVector MomDir  = Mom;
    if (MomDir.mag())
      MomDir /= MomDir.mag();
    else
      MomDir = G4ThreeVector(0., 0., 0.);

    G4ThreeVector Position = traj->GetInitialPosition();
    G4int parent = traj->GetParentID();
    G4String process = traj->GetInitialProcessName();



    // Fill tree
    analysisManager->FillNtupleDColumn(0, 0, Mom.mag());
    analysisManager->FillNtupleDColumn(0, 1, particle_PDG);
    analysisManager->FillNtupleDColumn(0, 2, MomDir.x());
    analysisManager->FillNtupleDColumn(0, 3, MomDir.y());
    analysisManager->FillNtupleDColumn(0, 4, MomDir.z());
    analysisManager->FillNtupleDColumn(0, 5, Position.x());
    analysisManager->FillNtupleDColumn(0, 6, Position.y());
    analysisManager->FillNtupleDColumn(0, 7, Position.z());
    analysisManager->FillNtupleDColumn(0, 8, parent);
    analysisManager->FillNtupleSColumn(0, 9, process);

    G4int parent_pid = GetTrajPIDById(event, parent);
    analysisManager->FillNtupleDColumn(0, 10, parent_pid);

    analysisManager->AddNtupleRow(0);
  } // loop over trajectories in the event
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
