#include "DetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"
#include "G4SDParticleFilter.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSNofSecondary.hh"
#include "G4VSDFilter.hh"

#include "Materials.hh"

DetectorConstruction::DetectorConstruction()
  : G4VUserDetectorConstruction(),
    platePV(0)
{
  DefineMaterials();
}

DetectorConstruction::~DetectorConstruction()
{} 

// Create our world and box
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  
  G4NistManager* man = G4NistManager::Instance();
  G4Material* default_mat = man -> FindOrBuildMaterial("Air");
  G4Material* box_mat = man -> FindOrBuildMaterial("lArgon");
  G4Material* water = man -> FindOrBuildMaterial("Water");

  /*** FIRST create the WORLD ***/
  G4double worldSize = 1. * m;
  G4Box* solidWorld = new G4Box("World", worldSize, worldSize, worldSize);
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, default_mat, "World");
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0);

  G4double Box_x = 0.5 * worldSize; 
  G4double Box_y = 0.5 * worldSize;
  G4double Box_z = 0.5 * worldSize;
  
  G4Box* testBox = new G4Box("testBox", // Name
                          Box_x,    // x length
                          Box_y,    // y length
                          Box_z);   // z length
  
  G4LogicalVolume* testBox_log = new G4LogicalVolume(testBox,         // Its solid (see the box we made)
                                                     box_mat,        // Its material 
                                                      "testBox");  // Its name
  
                                  // We can place this as part of the G4Logical Volume
                                 new G4PVPlacement(0,                 // Rotation
                                                     G4ThreeVector(),   // its location
                                                     testBox_log,       // the logical volume
                                                     "testBox",            // its name
                                                     logicWorld,        // its mother volume 
                                                     false,             // boolean operations
                                                     0);                // its copy number



  /* We are now going to create a thin plate and have it act as a detector. We'll place it at the edge of the world, opposite of the incoming rays. This means that
   * it will be located at the lowest value of x in our world. Remember that our particle gun was defined at 1.,0,0
   * */
  G4Box* plate = new G4Box("plate",
                              0.1 * m,
                              worldSize,
                              worldSize);

  /*G4LogicalVolume*/ plate_log = new G4LogicalVolume(plate,
                                                   water,
                                                   "plateLV");
                      platePV   = new G4PVPlacement(0,
                                                    G4ThreeVector(0.9 * worldSize,0,0),  // Remember that we have to account for the size of the box
                                                    plate_log,
                                                    "plate",
                                                    logicWorld,
                                                    false,
                                                    0);

      
  return physWorld; // Always return the world 
}

// We are now going to create the detector here
// Remember that we will have to edit our .hh file here
void DetectorConstruction::ConstructSDandField()
{
    G4SDManager* sdManage = G4SDManager::GetSDMpointer();
    sdManage -> SetVerboseLevel(1);
    G4String filterName, particleName;
    // Changed name to detector to be clearer
    G4MultiFunctionalDetector* det = new G4MultiFunctionalDetector("plate");
    sdManage -> AddNewDetector(det);
    G4VPrimitiveScorer* prim;
    prim = new G4PSDoseDeposit("dose");   // We want to record the dosage to the patient
    det -> RegisterPrimitive(prim);
    // Now we are going to apply filters to get the number of secondary particles
    // The way we order these filters will determine how we access them
    // We are keeping in line with the example RE06. We can access multiple detectors by changing
    // the i value where j specifies the filter
    // [i][j] = detector and filter
    // [0][0] = Protons
    G4SDParticleFilter* protonFilter = new G4SDParticleFilter(filterName="protonFilter", particleName="proton");
    prim = new G4PSNofSecondary("nProton");
    prim -> SetFilter(protonFilter);
    det -> RegisterPrimitive(prim);
    // [0][1] = e-
    G4SDParticleFilter* electronFilter = new G4SDParticleFilter("electronFilter", "e-");
    prim = new G4PSNofSecondary("nElectron");
    prim -> SetFilter(electronFilter);
    det -> RegisterPrimitive(prim);
    // [0][2] = e+
    G4SDParticleFilter* positronFilter = new G4SDParticleFilter("positronFilter", "e+");
    prim = new G4PSNofSecondary("nPositron");
    prim -> SetFilter(positronFilter);
    det -> RegisterPrimitive(prim);
    // [0][3] = n
    G4SDParticleFilter* neutronFilter = new G4SDParticleFilter("neutronFilter", "neutron");
    prim = new G4PSNofSecondary("nNeutron");
    prim -> SetFilter(neutronFilter);
    det -> RegisterPrimitive(prim);
    // Have to set as a sensitive detector and the logical volume we are pointing at 
    SetSensitiveDetector("plateLV", det);
}

