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
#include "G4SubtractionSolid.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4GenericMessenger.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

#include "G4MultiUnion.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"


//******************************************************************************
T2K_DetectorConstruction::T2K_DetectorConstruction()
  : G4VUserDetectorConstruction(),
  fVisAttributes(),
  fCheckOverlaps(true) {
//******************************************************************************

}

//******************************************************************************
T2K_DetectorConstruction::~T2K_DetectorConstruction() {
//******************************************************************************
  for (auto visAttributes: fVisAttributes) {
    delete visAttributes;
  }
}

//******************************************************************************
G4VPhysicalVolume* T2K_DetectorConstruction::Construct() {
//******************************************************************************
  ConstructMaterials();

  // Get materials
  auto defaultMaterial  = G4Material::GetMaterial("Vacuum");
  auto carbonMaterial   = G4Material::GetMaterial("Carbon");
  // Beryllium
  auto berylliumMaterial   = G4Material::GetMaterial("Beryllium");
  // G4Material* berylliumMaterial = G4Material::GetMaterial("Beryllium");
  auto heliumMaterial  =  G4Material::GetMaterial("G4_He");

  auto ironMaterial = G4Material::GetMaterial("Iron");

  auto sandMaterial = G4Material::GetMaterial("Ground");

  struct Experiment {
    G4double target_length;
    G4double target_diameter;

    G4double decay_length;
    G4double decay_width;
    G4double decay_height;

    G4double beam_dump_length;
    G4double beam_dump_width;
    G4double beam_dump_height;

    G4Material* beam_dump_material;
    G4Material* decay_material;
    G4Material* target_material;
  };

  Experiment T2K;
  T2K.target_length = 914.;
  T2K.target_diameter = 26.;

  T2K.decay_length = 96. * m;
  T2K.decay_width = 3. * m;
  T2K.decay_height = 5. * m;

  T2K.beam_dump_length  = 3.174 * m;
  T2K.beam_dump_width = 1.94 * m;
  T2K.beam_dump_height = 4.69 * m;

  T2K.beam_dump_material = carbonMaterial;
  T2K.decay_material = heliumMaterial;
  T2K.target_material = carbonMaterial;

  Experiment PS191;
  PS191.target_length = 800. * mm;
  PS191.target_diameter = 6. * mm;

  PS191.decay_length = 49.1 * m;
  PS191.decay_width = 2.8 * m;
  PS191.decay_height = 5. * m;

  PS191.beam_dump_length  = 5. * m;
  PS191.beam_dump_width = 2.8 * m;
  PS191.beam_dump_height = 5. * m;

  PS191.beam_dump_material = ironMaterial;
  PS191.decay_material = heliumMaterial;
  PS191.target_material = berylliumMaterial;


  Experiment working_exp = PS191;

  // Eps
  G4double eps = 0.001;

  // Geometry parameters
  auto  worldSizeXY = 25 * m;
  auto  worldSizeZ  = 300 * m;

  // Target
  // G4double target_length  = 800.;
  // G4double target_length  = 914.;
  // G4double target_diameter = 26.;

  // Helium cylinder volume
  G4double he_diameter = 30.;
  G4double he_length   = 2238.13;


  // Baffle
  G4double baffle_lengthX = 290.;
  G4double baffle_lengthY = 400.;
  G4double baffle_lengthZ = 1711.45;

  // Baffle hole
  G4double baffle_hole_diameter = he_diameter;

  // Distance between baffle downstream end and target
  G4double baffle_target_distance = 526.68;

  // decay volume
  // G4double decay_length = 49.1 * m;
  // G4double decay_width = 2.8 * m;
  // G4double decay_height = 5. * m;

  // G4double decay_length = 96 * m;
  // G4double decay_width = 3 * m;
  // G4double decay_height = 5. * m;


  // beam dump
  // G4double beam_dump_length = 5. * m;
  // G4double beam_dump_width = 2.8 * m;
  // G4double beam_dump_height = 5. * m;
  //
  // G4double beam_dump_length = 3.174 * m;
  // G4double beam_dump_width = 1.94 * m;
  // G4double beam_dump_height = 4.69 * m;



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


  auto sand = new G4Box("sand",           // its name
                        worldSizeXY/2-10 * cm, worldSizeXY/2-10 * cm, worldSizeZ/2-10 * cm); // its size
  // Carbon buffle with a hole

  // auto baffle_box  = new G4Box("baffle", baffle_lengthX/2., baffle_lengthY/2., baffle_lengthZ/2.);

  // auto baffle_hole_cylinder
  //   = new G4Tubs("hole",                          // its name
  //       0.,
  //       baffle_hole_diameter/2. + eps, baffle_lengthZ/2. + eps, // its size
  //       0.0 * deg,  360.0 * deg);                   // its segment


  // auto baffle_with_hole = new G4SubtractionSolid("baffle_with_hole", baffle_box, baffle_hole_cylinder);


  // auto baffle_LV
  //   = new G4LogicalVolume(
  //       baffle_with_hole,      // its solid
  //       carbonMaterial,  // its material
  //       "BAFFLE");       // its name

  // new G4PVPlacement(
  //     0,                 // no rotation
  //     G4ThreeVector(0., 0., -(baffle_lengthZ/2. + baffle_target_distance)),  // at (0,0,h/2)
  //     baffle_LV,         // its logical volume
  //     "BAFFLE",          // its name
  //     worldLV,           // its mother  volume
  //     false,             // no boolean operation
  //     0,                 // copy number
  //     fCheckOverlaps);   // checking overlaps

  // // Helium cylinder

  // auto he_cylinder
  //   = new G4Tubs("he_volume",                                // its name
  //       0., he_diameter/2., he_length/2.,  // its size
  //       0.0 * deg,  360.0 * deg);                // its segment

  // auto he_LV
  //   = new G4LogicalVolume(
  //       he_cylinder,      // its solid
  //       heliumMaterial,       // its material
  //       "HE_VOLUME");            // its name

  // new G4PVPlacement(
  //     0,                 // no rotation
  //     G4ThreeVector(0., 0., -(he_length/2. + eps)),  // at (0,0,h/2)
  //     he_LV,         // its logical volume
  //     "HE_VOLUME",          // its name
  //     worldLV,           // its mother  volume
  //     false,             // no boolean operation
  //     0,                 // copy number
  //     fCheckOverlaps);   // checking overlaps



  // Carbon target

  auto target_cylinder
    = new G4Tubs("target",                                // its name
        0., working_exp.target_diameter/2., working_exp.target_length/2.,  // its size
        0.0 * deg,  360.0 * deg);                // its segment

  auto target_LV
    = new G4LogicalVolume(
        target_cylinder,      // its solid
        working_exp.target_material,       // its material
        "TARGET");            // its name

  new G4PVPlacement(
      0,                 // no rotation
      G4ThreeVector(0., 0., working_exp.target_length/2.),  // at (0,0,h/2)
      target_LV,         // its logical volume
      "TARGET",          // its name
      worldLV,           // its mother  volume
      false,             // no boolean operation
      0,                 // copy number
      fCheckOverlaps);   // checking overlaps

  // Decay volume
  auto decay_volume = new G4Box("decay_volume",
                                working_exp.decay_height/2.,
                                working_exp.decay_width/2.,
                                working_exp.decay_length/2.
                                );

  auto decay_LV = new G4LogicalVolume(decay_volume,
                                      working_exp.decay_material,
                                      "DECAY_VOLUME"
                                      );

  new G4PVPlacement(0,
                  G4ThreeVector(0., 0., working_exp.decay_length/2. + working_exp.target_length),
                  decay_LV,
                  "DECAY_VOLUME",
                  worldLV,
                  false,
                  0,
                  fCheckOverlaps
                  );

  // Beam Dump
  auto beam_dump = new G4Box("beam_dump",
                             working_exp.beam_dump_height/2.,
                             working_exp.beam_dump_width/2.,
                             working_exp.beam_dump_length/2.
                             );

  auto dump_LV = new G4LogicalVolume(beam_dump,
                                     working_exp.beam_dump_material,
                                     "BEAM_DUMP_VOLUME"
                                     );

  new G4PVPlacement(0,
                    G4ThreeVector(0., 0., working_exp.beam_dump_length/2. + working_exp.decay_length + working_exp.target_length),
                    dump_LV,
                    "BEAM_DUMP_VOLUME",
                    worldLV,
                    false,
                    0,
                    fCheckOverlaps
                    );

  auto noSandUnion = new G4MultiUnion("no_sand");
  G4RotationMatrix rot = G4RotationMatrix();
  auto tr = G4Transform3D(rot, // rotation
                          G4ThreeVector(0, 0, working_exp.target_length/2.) //position
                          );

  auto target_hall = new G4Box("target_hall",
                               working_exp.decay_height/2.,
                               working_exp.decay_width/2.,
                               working_exp.target_length/2.
                               );
  noSandUnion->AddNode(*target_hall, tr);
  tr = G4Transform3D(rot, // rotation
                      G4ThreeVector(0, 0, working_exp.decay_length/2. + working_exp.target_length) //position
                      );
  noSandUnion->AddNode(*decay_volume, tr);
    tr = G4Transform3D(rot, // rotation
                      G4ThreeVector(0, 0, working_exp.beam_dump_length/2. + working_exp.decay_length + working_exp.target_length) //position
                      );
  noSandUnion->AddNode(*beam_dump, tr);
  noSandUnion->Voxelize();
  auto sand_subtr = new G4SubtractionSolid("sand_with_holes", sand, noSandUnion);
  auto sand_LV
    = new G4LogicalVolume(
        sand_subtr,           // its solid
        sandMaterial,  // its material
        "SAND_VOLUME");         // its name

  new G4PVPlacement(
        0,                // no rotation
        G4ThreeVector(),  // at (0,0,0)
        sand_LV,          // its logical volume
        "SAND_VOLUME",          // its name
        worldLV,                // its mother  volume
        false,            // no boolean operation
        0,                // copy number
        fCheckOverlaps);  // checking overlaps

  //
  // Visualization attributes
  //
  worldLV->SetVisAttributes (G4VisAttributes::GetInvisible());


  // visualization attributes ------------------------------------------------


  auto visAttributesCarbon = new G4VisAttributes(G4Colour(1., 1., 1.));   // white
  auto visAttributesHelium = new G4VisAttributes(G4Colour::Cyan());   // Cyan
  auto visAttributesSand = new G4VisAttributes(G4Colour::Yellow());   // Yellow
  auto visAttributesDecay = new G4VisAttributes(G4Colour(.5, .5, .5));   // gray
  auto visAttributesBeamDump = new G4VisAttributes(G4Colour(.9, .9, .9));   // gray

  // Carbon
  target_LV->SetVisAttributes(visAttributesCarbon);
  // baffle_LV->SetVisAttributes(visAttributesCarbon);

  // // Helium
  // he_LV->SetVisAttributes(visAttributesHelium);
  dump_LV->SetVisAttributes(visAttributesBeamDump);
  decay_LV->SetVisAttributes(visAttributesDecay);
  sand_LV->SetVisAttributes(visAttributesSand);


  fVisAttributes.push_back(visAttributesCarbon);
  fVisAttributes.push_back(visAttributesHelium);
  fVisAttributes.push_back(visAttributesSand);
  fVisAttributes.push_back(visAttributesDecay);
  fVisAttributes.push_back(visAttributesBeamDump);

  return worldPV;
}


//******************************************************************************
void T2K_DetectorConstruction::ConstructMaterials() {
//******************************************************************************
  auto nistManager = G4NistManager::Instance();

  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;
  G4double density;
  G4String symbol;
  G4int ncomp;

  // Air
  nistManager->FindOrBuildMaterial("G4_AIR");

  new G4Material("Vacuum", z=1., a=1.01 * g / mole,
                          density=1.e-25*gram/centimeter3);

  // Helium
  nistManager->FindOrBuildMaterial("G4_He");

  // Carbon
  new G4Material("Carbon", z=6., a= 12.*g/mole, density=1.8*g/cm3);

  // Be
  new G4Material("Beryllium", z=4.,  a=9.012182*g/mole, density=1.8480*g/cm3);

  // Ground
  new G4Material("Ground", z=14.,  a=28.0855*g/mole, density=1.8*g/cm3);

  // Water
  auto d = 1.01*g/mole;
  G4Element* ele_H = new G4Element("Hydrogen", symbol="H", z=1., d);
  d = 16.00*g/mole;
  G4Element* ele_O = new G4Element("Oxygen", symbol="O", z=8., d);

  G4Material* H2O = new G4Material("Water", density=1.*g/cm3, ncomp=2);
  G4int natoms;
  H2O->AddElement(ele_H, natoms=2);
  H2O->AddElement(ele_O, natoms=1);

  // Iron
  density = 7.87 * g/cm3;
  a = 55.85 * g/mole;
  new G4Material("Iron", z=26., a, density);
}

