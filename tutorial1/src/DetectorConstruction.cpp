/******* We will create the most basics of a detector construction file  ********/
/*** 
 * To do this we will create a world box and place another box inside it and fill it. We need 
 * to create the logical volume, use the solid, and add other attributes (like composition)
 * ***/

#include "DetectorConstruction.hh"
#include "G4NistManager.hh"         // Contains the NIST data for particles
#include "G4Box.hh"                 // Needed to create box shapes
#include "G4LogicalVolume.hh"       // Will be required in every Detector construction file
#include "G4PVPlacement.hh"        
#include "G4RotationMatrix.hh"      
#include "G4Transform3D.hh"         
#include "G4PhysicalConstants.hh"   
#include "G4SystemOfUnits.hh"

// Our initial constructor 
DetectorConstruction::DetectorConstruction()
  : G4VUserDetectorConstruction() 
{
   DefineMaterials(); // Whenever we create a world and volume we want to have materials
}

// Create virtual
DetectorConstruction::~DetectorConstruction()
{}  // Don't need to destruct anything, but we keep good habits

void DetectorConstruction::DefineMaterials()
{
   G4NistManager* man = G4NistManager::Instance(); // Calls the NIST manager
   // The NIST manager will populate the materials in proportions of abundance. If we
   // want to work with pure materials then we should turn isotopes off
   G4bool isotopes = false;

   /**
    * G4Element class has properties: Atomic number, number of nucleons, atomic mass, shell energy, cross section per atom, etc 
    * G4Material has macroscopic properties: density, state, temperature, pressure, radiation length, mean free path, dE/dx, etc
    */
   
   /* Define simple material */
   // G4double density = 1.390 * g/cm3;
   // G4double a = 39.95 * g/mole;
   // G4Material* lAr = new G4Material("liquidArgon", // Name
   //                                   18.,          // Z value
   //                                   a,            // atomic mass
   //                                   density);     // That thing
   // 

   /* Define a simple molecule */
   // Here we are telling GEANT to do a lookup in the NIST tables for Hydrogen
   G4Element* H = man -> FindOrBuildElement("H", isotopes); // another way of adding elements.
   G4Element* O = man -> FindOrBuildElement("O", isotopes);
   
   // We will then want to create the water molecule with our defined properties
   G4Material* H2O = new G4Material("Water",         // name
                                     1.000 * g/cm3,  // density
                                     2);             // number of components
   // We then need to tell GEANT what elements are in the molecule and in what 
   // proportions
   H2O -> AddElement(H, 2);  
   H2O -> AddElement(O, 1);
   
   /* Define mixture by fractional mass */
   G4Element* N = man -> FindOrBuildElement("N", isotopes);
   G4double density = 1.290 * mg/cm3;
   G4Material* Air = new G4Material("Air", density, 2);
   Air -> AddElement(N, 70*perCent);
   Air -> AddElement(O, 30*perCent);
  // Note that GEANT already has predefined Air and Water that can be called so we don't
  // have to create them each time, but we're being explicit here
}



// Now we will be creating the actual world and object inside the world here
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  
   // Same as above
   G4NistManager* man = G4NistManager::Instance();
   // This time the manager will find the materials we created above
   G4Material* default_mat = man -> FindOrBuildMaterial("Air");
   G4Material* box_mat = man -> FindOrBuildMaterial("Water");

   /*** FIRST create the WORLD ***/
   G4double worldSize = 1 * m;
   G4Box* solidWorld = new G4Box("World", worldSize, worldSize, worldSize);
   G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, default_mat, "World");
   G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0);

   /* to create a solid box we do the following */
   G4double Box_x = 0.5*m;   // Note that these are HALF LENGTHS
   G4double Box_y = 0.5*m;
   G4double Box_z = 0.5*m;   
   // creates a 1x1x1 m box, from -0.5 to 0.5 on each side of the axies 
   
   // first we need to create outline
   G4Box* testBox = new G4Box("testBox", // Name
                           Box_x,    // x length
                           Box_y,    // y length
                           Box_z);   // z length
   
   /** Create a logical volume **/
   G4LogicalVolume* testBox_log = new G4LogicalVolume(testBox,         // Its solid (see the box we made)
                                                       box_mat,        // Its material 
                                                       "testBox");  // Its name
   
   /** Create the Physical Volume **/
   /** Physical volume is a placed instance of the logical volume. We'll place it in 
    * its mother logical volume **/
   G4VPhysicalVolume* testBox_phy = new G4PVPlacement(0,                 // Rotation
                                                      G4ThreeVector(),   // its location
                                                      testBox_log,       // the logical volume
                                                      "testBox",            // its name
                                                      logicWorld,        // its mother volume 
                                                      false,             // boolean operations
                                                      0);                // its copy number
   
   return physWorld; // Always return the world 
}
