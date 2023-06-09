#include "T2K_PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//******************************************************************************
T2K_PrimaryGeneratorAction::T2K_PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(nullptr), fMessenger(nullptr),
  fBeamMeanX(0.*mm),
  fBeamMeanY(0.*mm),
  fBeamSigmaX(0.*mm),
  fBeamSigmaY(0.*mm),
  fAngleX(0.*mrad),
  fAngleY(0.*mrad),
  fT2KGenerator(false) {
//******************************************************************************
  G4int nofParticles = 1;
  fParticleGun  = new G4ParticleGun(nofParticles);

  // default particle kinematics
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,-8.*m));

  // define commands for this class
  DefineCommands();
}

//******************************************************************************
T2K_PrimaryGeneratorAction::~T2K_PrimaryGeneratorAction() {
//******************************************************************************
  delete fParticleGun;
  delete fMessenger;
}

//******************************************************************************
void T2K_PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
//******************************************************************************

  if (!fT2KGenerator){
     fParticleGun->GeneratePrimaryVertex(event);
     return;
  }


  // auto pp = fMomentum + (G4UniformRand()-0.5)*fSigmaMomentum;
  // auto mass = particle->GetPDGMass();
  // auto ekin = std::sqrt(pp*pp+mass*mass)-mass;
  // fParticleGun->SetParticleEnergy(ekin);

  G4ThreeVector vec(0., 0., 1.);
  vec.setPhi(fAngleX);
  vec.setTheta(fAngleY);
  vec.setMag(1.);
  fParticleGun->SetParticleMomentumDirection(vec);

  fParticleGun->GeneratePrimaryVertex(event);


  G4RandGauss* x_rand = new G4RandGauss(G4Random::getTheEngine(), fBeamMeanX, fBeamSigmaX);
  G4RandGauss* y_rand = new G4RandGauss(G4Random::getTheEngine(), fBeamMeanY, fBeamSigmaY);

  float x = x_rand->fire();
  float y = y_rand->fire();
  float z = event->GetPrimaryVertex()->GetZ0();

  event->GetPrimaryVertex()->SetPosition(x, y, z);
}

//******************************************************************************
void T2K_PrimaryGeneratorAction::DefineCommands() {
//******************************************************************************
  // Define /T2K_/generator command directory using generic messenger class
  fMessenger
    = new G4GenericMessenger(this,
                             "/T2K/generator/",
                             "Primary generator control");

  auto& t2kGenCmd
    = fMessenger->DeclareProperty("T2KGenerator", fT2KGenerator);

  G4String guidanceT2KGen
    = "Boolean flag to give the control to T2K/generator \n";
  t2kGenCmd.SetGuidance(guidanceT2KGen);
  t2kGenCmd.SetParameterName("t2kgenflag", true);
  t2kGenCmd.SetDefaultValue("false");


  // BeamMeanX command
  auto& beamMeanX
    = fMessenger->DeclarePropertyWithUnit("BeamMeanX", "cm", fBeamMeanX,
        "Mean beam position");
  beamMeanX.SetParameterName("X_m", true);
  beamMeanX.SetDefaultValue("0.");

  // BeamMeanY command
  auto& beamMeanY
    = fMessenger->DeclarePropertyWithUnit("BeamMeanY", "cm", fBeamMeanY,
        "Mean beam position");
  beamMeanY.SetParameterName("Y_m", true);
  beamMeanY.SetDefaultValue("0.");

  // BeamSigmaX command
  auto& beamSigmaX
    = fMessenger->DeclarePropertyWithUnit("BeamSigmaX", "cm", fBeamSigmaX,
        "Mean beam position");
  beamSigmaX.SetParameterName("X_s", true);
  beamSigmaX.SetDefaultValue("0.");

  // BeamSigmaY command
  auto& beamSigmaY
    = fMessenger->DeclarePropertyWithUnit("BeamSigmaY", "cm", fBeamSigmaY,
        "Mean beam position");
  beamSigmaY.SetParameterName("Y_s", true);
  beamSigmaY.SetDefaultValue("0.");

  // Angle X command
  auto& beamAngleX
    = fMessenger->DeclarePropertyWithUnit("AngleX", "mrad", fAngleX,
        "Mean beam position");
  beamAngleX.SetParameterName("angleX", true);
  beamAngleX.SetDefaultValue("0.");

  // Angle Y command
  auto& beamAngleY
    = fMessenger->DeclarePropertyWithUnit("AngleY", "mrad", fAngleY,
        "Mean beam position");
  beamAngleY.SetParameterName("angleY", true);
  beamAngleY.SetDefaultValue("0.");
}
