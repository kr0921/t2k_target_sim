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

//******************************************************************************
T2K_RunAction::T2K_RunAction()
 : G4UserRunAction() {
//******************************************************************************
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  analysisManager->SetFileName("T2K_Sim");

  // Creating ntuple
  //
  analysisManager->CreateNtuple("Particle", "Particles information");
  analysisManager->CreateNtupleDColumn("start_mom");      // N_id = 0   column Id = 0
  analysisManager->CreateNtupleDColumn("end_mom");        // N_id = 0   column Id = 1

  analysisManager->CreateNtupleDColumn("pid");            // N_id = 0   column Id = 2

  analysisManager->CreateNtupleDColumn("start_dir_x");    // N_id = 0   column Id = 3
  analysisManager->CreateNtupleDColumn("start_dir_y");    // N_id = 0   column Id = 4
  analysisManager->CreateNtupleDColumn("start_dir_z");    // N_id = 0   column Id = 5
  analysisManager->CreateNtupleDColumn("start_pos_x");    // N_id = 0   column Id = 6
  analysisManager->CreateNtupleDColumn("start_pos_y");    // N_id = 0   column Id = 7
  analysisManager->CreateNtupleDColumn("start_pos_z");    // N_id = 0   column Id = 8

  analysisManager->CreateNtupleDColumn("end_dir_x");      // N_id = 0   column Id = 9
  analysisManager->CreateNtupleDColumn("end_dir_y");      // N_id = 0   column Id = 10
  analysisManager->CreateNtupleDColumn("end_dir_z");      // N_id = 0   column Id = 11
  analysisManager->CreateNtupleDColumn("end_pos_x");      // N_id = 0   column Id = 12
  analysisManager->CreateNtupleDColumn("end_pos_y");      // N_id = 0   column Id = 13
  analysisManager->CreateNtupleDColumn("end_pos_z");      // N_id = 0   column Id = 14

  analysisManager->CreateNtupleSColumn("start_process");  // N_id = 0   column Id = 15
  analysisManager->CreateNtupleSColumn("end_process");    // N_id = 0   column Id = 16

  analysisManager->CreateNtupleSColumn("start_volume");   // N_id = 0   column Id = 17
  analysisManager->CreateNtupleSColumn("end_volume");     // N_id = 0   column Id = 18

  analysisManager->CreateNtupleDColumn("track_length");   // N_id = 0   column Id = 19

  analysisManager->CreateNtupleDColumn("parent_pid");     // N_id = 0   column Id = 20
  analysisManager->CreateNtupleDColumn("parent_id");      // N_id = 0   column Id = 21
  analysisManager->CreateNtupleDColumn("event");          // N_id = 0   column Id = 22

  analysisManager->FinishNtuple();
}

//******************************************************************************
T2K_RunAction::~T2K_RunAction() {
//******************************************************************************
  delete G4AnalysisManager::Instance();
}

//******************************************************************************
void T2K_RunAction::BeginOfRunAction(const G4Run* /*run*/) {
//******************************************************************************

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  analysisManager->OpenFile();
}

//******************************************************************************
void T2K_RunAction::EndOfRunAction(const G4Run* /*run*/) {
//******************************************************************************
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

}
