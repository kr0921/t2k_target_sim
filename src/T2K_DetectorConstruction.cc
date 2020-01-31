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
/// \file T2K_DetectorConstruction.cc
/// \brief Implementation of the T2K_DetectorConstruction class

#include "T2K_DetectorConstruction.hh"
//#include "T2K_MagneticField.hh"

#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4Mag_UsualEqRhs.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4MaterialTable.hh"
#include "G4NistManager.hh"

#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4PVReplica.hh"
#include "G4UserLimits.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4GenericMessenger.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//G4ThreadLocal T2K_MagneticField* T2K_DetectorConstruction::fMagneticField = 0;
//G4ThreadLocal G4FieldManager* T2K_DetectorConstruction::fFieldMgr = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T2K_DetectorConstruction::T2K_DetectorConstruction()
: G4VUserDetectorConstruction(),
  fVisAttributes(),
  fCheckOverlaps(true)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T2K_DetectorConstruction::~T2K_DetectorConstruction()
{
  for (auto visAttributes: fVisAttributes) {
    delete visAttributes;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* T2K_DetectorConstruction::Construct()
{

  ConstructMaterials();

  // Geometry parameters
  auto  worldSizeXY = 0.2 * m;
  auto  worldSizeZ  = 2 * m;

  float target_length    = 914.;
  float target_diameter   = 26.;


  // Get materials
  auto defaultMaterial = G4Material::GetMaterial("G4_AIR");
  auto carbonMaterial   = G4Material::GetMaterial("Carbon");

  if ( ! defaultMaterial || ! carbonMaterial ) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined.";
    G4Exception("T2K_DetectorConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }

  //
  // World
  //
  auto worldS
    = new G4Box("World",           // its name
                 worldSizeXY/2, worldSizeXY/2, worldSizeZ/2); // its size

  auto worldLV
    = new G4LogicalVolume(
                 worldS,           // its solid
                 defaultMaterial,  // its material
                 "World");         // its name

  auto worldPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 worldLV,          // its logical volume
                 "World",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps

  //
  // Cargon target
  //

  auto target_cylinder
    = new G4Tubs("target",                                // its name
                 0., target_diameter/2, target_length/2,  // its size
                 0.0 * deg,  360.0 * deg);                // its segment

  auto target_LV
    = new G4LogicalVolume(
                target_cylinder,      // its solid
                carbonMaterial,       // its material
                "TARGET");            // its name

  new G4PVPlacement(
               0,                 // no rotation
               G4ThreeVector(0., 0., target_length/2.),  // at (0,0,h/2)
               target_LV,         // its logical volume
               "TARGET",          // its name
               worldLV,           // its mother  volume
               false,             // no boolean operation
               0,                 // copy number
               fCheckOverlaps);   // checking overlaps


  //
  // Visualization attributes
  //
  worldLV->SetVisAttributes (G4VisAttributes::GetInvisible());


  // visualization attributes ------------------------------------------------


  auto visAttributes = new G4VisAttributes(G4Colour(0.9, 0.9, 0.9));   // LightGray
  target_LV->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);

  return worldPV;
}


void T2K_DetectorConstruction::ConstructMaterials()
{
  auto nistManager = G4NistManager::Instance();

  // Air
  nistManager->FindOrBuildMaterial("G4_AIR");

  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;
  G4double density;
  G4String symbol;
  G4int ncomp;

  // Carbon
  new G4Material("Carbon", z=6., a= 12.*g/mole, density= 1.8*g/cm3);

  auto d = 1.01*g/mole;
  G4Element* ele_H = new G4Element("Hydrogen", symbol="H", z=1., d);
  d = 16.00*g/mole;
  G4Element* ele_O = new G4Element("Oxygen", symbol="O", z=8., d);

  G4Material* H2O = new G4Material("Water", density=1.*g/cm3, ncomp=2);
  G4int natoms;
  H2O->AddElement(ele_H, natoms=2);
  H2O->AddElement(ele_O, natoms=1);


  G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

