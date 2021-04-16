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
/// \file T2K_RunAction.cc
/// \brief Implementation of the T2K_RunAction class

#include "T2K_RunAction.hh"
#include "T2K_EventAction.hh"
#include "T2K_Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T2K_RunAction::T2K_RunAction()
 : G4UserRunAction()
{
  //G4RunManager::GetRunManager()->SetPrintProgress(1);
  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in T2K_Analysis.hh
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Default settings
  //analysisManager->SetNtupleMerging(true);
     // Note: merging ntuples is available only with Root output
  //analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName("T2K_Sim");

  // Creating ntuple
  //
  analysisManager->CreateNtuple("Particle_prod", "Particles production");
  analysisManager->CreateNtupleDColumn("mom");    // N_id = 0   column Id = 0
  analysisManager->CreateNtupleDColumn("pid");    // N_id = 0   column Id = 1
  analysisManager->CreateNtupleDColumn("dir_x");  // N_id = 0   column Id = 2
  analysisManager->CreateNtupleDColumn("dir_y");  // N_id = 0   column Id = 3
  analysisManager->CreateNtupleDColumn("dir_z");  // N_id = 0   column Id = 4
  analysisManager->CreateNtupleDColumn("pos_x");  // N_id = 0   column Id = 5
  analysisManager->CreateNtupleDColumn("pos_y");  // N_id = 0   column Id = 6
  analysisManager->CreateNtupleDColumn("pos_z");  // N_id = 0   column Id = 7
  analysisManager->CreateNtupleDColumn("parent"); // N_id = 0   column Id = 8
  analysisManager->CreateNtupleSColumn("process");// N_id = 0   column Id = 9
  analysisManager->CreateNtupleDColumn("parent_pdg");// N_id = 0   column Id = 10
  analysisManager->CreateNtupleSColumn("volume");  // N_id = 0   column Id = 11

  analysisManager->CreateNtuple("Particle_decay", "Particles decay");
  analysisManager->CreateNtupleDColumn("mom");    // N_id = 1   column Id = 0
  analysisManager->CreateNtupleDColumn("pid");    // N_id = 1   column Id = 1
  analysisManager->CreateNtupleDColumn("dir_x");  // N_id = 1   column Id = 2
  analysisManager->CreateNtupleDColumn("dir_y");  // N_id = 1   column Id = 3
  analysisManager->CreateNtupleDColumn("dir_z");  // N_id = 1   column Id = 4
  analysisManager->CreateNtupleDColumn("pos_x");  // N_id = 1   column Id = 5
  analysisManager->CreateNtupleDColumn("pos_y");  // N_id = 1   column Id = 6
  analysisManager->CreateNtupleDColumn("pos_z");  // N_id = 1   column Id = 7
  analysisManager->CreateNtupleDColumn("parent"); // N_id = 1   column Id = 8
  analysisManager->CreateNtupleSColumn("process");// N_id = 1   column Id = 9
  analysisManager->CreateNtupleDColumn("parent_pdg");// N_id = 1   column Id = 10
  analysisManager->CreateNtupleSColumn("volume");  // N_id = 1   column Id = 11

  analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T2K_RunAction::~T2K_RunAction()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void T2K_RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  // The default file name is set in T2K_RunAction::T2K_RunAction(),
  // it can be overwritten in a macro
  analysisManager->OpenFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void T2K_RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // save histograms & ntuple
  //
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
