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
/// \file T2K_PrimaryGeneratorAction.hh
/// \brief Definition of the T2K_PrimaryGeneratorAction class

#ifndef T2K_PrimaryGeneratorAction_h
#define T2K_PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4GenericMessenger;
class G4Event;
class G4ParticleDefinition;

/// Primary generator
///
/// A single particle is generated.
/// User can select
/// - the initial momentum and angle
/// - the momentum and angle spreads
/// - random selection of a particle type from proton, kaon+, pi+, muon+, e+


class T2K_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    T2K_PrimaryGeneratorAction();
    virtual ~T2K_PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);

    void SetMomentum(G4double val) { fMomentum = val; }
    G4double GetMomentum() const { return fMomentum; }

    void SetSigmaMomentum(G4double val) { fSigmaMomentum = val; }
    G4double GetSigmaMomentum() const { return fSigmaMomentum; }

    void SetSigmaAngle(G4double val) { fSigmaAngle = val; }
    G4double GetSigmaAngle() const { return fSigmaAngle; }

    void SetRandomize(G4bool val) { fRandomizePrimary = val; }
    G4bool GetRandomize() const { return fRandomizePrimary; }
    
    void SetT2KGenerator(G4bool val) { fT2KGenerator = val; }
    G4bool GetT2KGenerator() const { return fT2KGenerator; }
    

  private:
    void DefineCommands();

    G4ParticleGun* fParticleGun;
    G4GenericMessenger* fMessenger;
    G4ParticleDefinition* fPositron;
    G4ParticleDefinition* fMuon;
    G4ParticleDefinition* fPion;
    G4ParticleDefinition* fKaon;
    G4ParticleDefinition* fProton;
    G4double fMomentum;
    G4double fSigmaMomentum;
    G4double fSigmaAngle;
    G4bool fRandomizePrimary;
    G4bool fT2KGenerator; // whether to control with T2K/generator
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
