/* Need our required Detector construction header */
#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4MultiFunctionalDetector.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    inline const G4VPhysicalVolume* GetAbsorberPV() const { return platePV;}

  private:
    G4LogicalVolume* plate_log;
    G4VPhysicalVolume* platePV;
};
#endif
