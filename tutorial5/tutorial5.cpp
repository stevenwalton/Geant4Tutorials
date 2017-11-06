#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
//#include "PrimaryGeneratorAction.hh"
#include "ActionInitialization.hh"
#include "EventAction.hh"

int main(int argc, char** argv)
{ 
  // Initialize ui to a null value
  G4UIExecutive* ui = 0;
  // If we only have no arguments then we want a visual interface
  if ( argc == 1 )
      ui = new G4UIExecutive(argc, argv);

  G4RunManager* runManager = new G4RunManager;

  G4VisManager* visManager = new G4VisExecutive;
  visManager -> Initialize();

  DetectorConstruction* detConst = new DetectorConstruction;
  runManager -> SetUserInitialization(detConst);
  runManager -> SetUserInitialization(new PhysicsList);
  runManager -> SetUserInitialization(new ActionInitialization(detConst));

  runManager -> Initialize();

  G4UImanager* UI = G4UImanager::GetUIpointer();
  
  // We have given a number of macro commands, let's run them
  if ( !ui )
  {
      G4String command = "/control/execute ";
      // Loop through the macro commands. Remember that argv[1] is the first macro and argv[0] is the
      // command you ran ie: `./tutorial5`
      for ( int i = 1; i < argc; ++i )
      {
          G4String fileName = argv[i];
          UI -> ApplyCommand(command + fileName);
      }
  }
  else
  {
    // get pointer to UI manager and set verbosities
    UI -> ApplyCommand("/control/execute init_vis.mac");
    // Have to add this to get the gui command
    UI -> ApplyCommand("/control/execute gui.mac");
    ui -> SessionStart();
  
    delete ui;
  }

  // TERMINATE job
  delete runManager;
  delete visManager; 
  
  return 0;
}
