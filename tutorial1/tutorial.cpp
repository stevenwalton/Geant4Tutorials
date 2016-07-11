/***** The most basic main file ****/

// Our required includes
#include "G4RunManager.hh"
#include "G4UImanager.hh"

// Classes we will be pulling from for our construction
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"

// add "int argc, char** argv" to int main if you'd like to run arguments
int main()
{
  // Construct the default run manager
  // App Dev Guide notes that this is the ONLY manager class in G4 kernel that should be explicitly constructed in main()
  G4RunManager* runManager = new G4RunManager;

  // Create visualization manager (Not NEEDED, but useful)
  //G4VisManager* visManager = VisManager;
  //visManager -> initialize();

  // Set MANDATORY initialization classes
  runManager -> SetUserInitialization(new DetectorConstruction);
  runManager -> SetUserInitialization(new PhysicsList);

  // Set MANDATORY user action class
  runManager -> SetUserAction(new PrimaryGeneratorAction);

  // Run the kernel
  runManager -> Initialize();
  
  // get pointer to UI manager and set verbosities
  G4UImanager* UI = G4UImanager::GetUIpointer();
  UI -> ApplyCommand("/run/verbose 1");
  UI -> ApplyCommand("/event/verbose 1");
  UI -> ApplyCommand("/tracking/verbose 1");

  // start a run
  int numberOfEvents = 3;
  runManager -> BeamOn(numberOfEvents);

  // TERMINATE job
  // Remember to always clean up. Any time we create something with new we should delete it
  delete runManager;
  //delete visManager; 
  return 0;
}
/*****************
* DETECTOR CONSTRUCTION specifies GEOMETRY, MATERIALS, SENSITIVE REGIONS, and READOUT schemes of sensitive regions
* PARTICLE LIST (from G4VUserPhysicsList) requires user define PARTICLES being used, RANGE CUTS for particles, and ALL PHYSICS PROCESSES to be simulated
*
* GEANT does not check for mandatory classes till initialize() and BeamOn() are invoked 
*
* OPTIONAL USER CLASSES
* UserRunAction, EventAction, StackingAction, TrackingAction, SteppingAction
******************/
