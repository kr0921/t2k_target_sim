#ifndef T2K_DetectorConstruction_h
#define T2K_DetectorConstruction_h

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4RotationMatrix.hh"
#include "G4FieldManager.hh"

#include <vector>

//class T2K_MagneticField;

class G4VPhysicalVolume;
class G4Material;
class G4VSensitiveDetector;
class G4VisAttributes;
class G4GenericMessenger;

/// Detector construction

class T2K_DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    T2K_DetectorConstruction();
    virtual ~T2K_DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    //virtual void ConstructSDandField();

    void ConstructMaterials();

  private:
    void DefineCommands();

    G4GenericMessenger* fMessenger;

    //static G4ThreadLocal T2K_MagneticField* fMagneticField;
    //static G4ThreadLocal G4FieldManager* fFieldMgr;

    std::vector<G4VisAttributes*> fVisAttributes;


    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
};

#endif
