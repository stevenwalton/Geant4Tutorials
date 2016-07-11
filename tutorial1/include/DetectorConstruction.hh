/* Need our required Detector construction header */
#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

// These two classes are called within the construct function
class G4VPhysicalVolume;
class G4LogicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction
{
   public:
      DetectorConstruction();
      virtual ~DetectorConstruction();
      virtual G4VPhysicalVolume* Construct();

   private:
      void DefineMaterials();
};
#endif
