#ifndef T2K_PrimaryGeneratorAction_h
#define T2K_PrimaryGeneratorAction_h

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

    // void SetMomentum(G4double val) { fMomentum = val; }
    // G4double GetMomentum() const { return fMomentum; }

    // void SetSigmaMomentum(G4double val) { fSigmaMomentum = val; }
    // G4double GetSigmaMomentum() const { return fSigmaMomentum; }

    // void SetSigmaAngle(G4double val) { fSigmaAngle = val; }
    // G4double GetSigmaAngle() const { return fSigmaAngle; }

    // void SetRandomize(G4bool val) { fRandomizePrimary = val; }
    // G4bool GetRandomize() const { return fRandomizePrimary; }

    // void SetT2KGenerator(G4bool val) { fT2KGenerator = val; }
    // G4bool GetT2KGenerator() const { return fT2KGenerator; }


  private:
    void DefineCommands();

    G4ParticleGun* fParticleGun;
    G4GenericMessenger* fMessenger;
    G4double fBeamMeanX;
    G4double fBeamMeanY;
    G4double fBeamSigmaX;
    G4double fBeamSigmaY;
    G4double fAngleX;
    G4double fAngleY;
    G4double fSigmaAngle;
    G4bool fT2KGenerator; // whether to control with T2K/generator
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
