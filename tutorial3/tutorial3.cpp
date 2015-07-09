/***** The most basic main file ****/
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
//#include "PrimaryGeneratorAction.hh"
#include "ActionInitialization.hh"

// add "int argc, char** argv" to int main if you'd like to run arguments
int main(int argc, char** argv)
{
  // Construct the default run manager
  // App Dev Guide notes that this is the ONLY manager class in G4 kernel that should be explicitly constructed in main()
  G4RunManager* runManager = new G4RunManager;

  G4UIExecutive* ui = new G4UIExecutive(argc, argv);
  // Create visualization manager (Not NEEDED, but useful)
  G4VisManager* visManager = new G4VisExecutive;
  visManager -> Initialize();

  // Set MANDATORY initialization classes
  runManager -> SetUserInitialization(new DetectorConstruction);
  runManager -> SetUserInitialization(new PhysicsList);

  // Set MANDATORY user action class (Here we have AI call PGE)
  runManager -> SetUserInitialization(new ActionInitialization());

  // Run the kernel
  //runManager -> Initialize();
  
  // get pointer to UI manager and set verbosities
  G4UImanager* UI = G4UImanager::GetUIpointer();
  UI -> ApplyCommand("/control/execute init_vis.mac");
  ui -> SessionStart();
  delete ui;
  // start a run
  //int numberOfEvents = 3;
  //runManager -> BeamOn(numberOfEvents);

  // TERMINATE job
  delete runManager;
  delete visManager; 

  // This will output the materials defined in DetectorConstruction when exiting the program
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
  return 0;
}


// NOTES
// DETECTOR CONSTRUCTION specifies GEOMETRY, MATERIALS, SENSITIVE REGIONS, and READOUT schemes of sensitive regions
// PARTICLE LIST (from G4VUserPhysicsList) requires user define PARTICLES being used, RANGE CUTS for particles, and ALL PHYSICS PROCESSES to be simulated
//
// GEANT does not check for mandatory classes till initialize() and BeamOn() are invoked 
//
// OPTIONAL USER CLASSES
// UserRunAction, EventAction, StackingAction, TrackingAction, SteppingAction
