/* Second REQUIRED file (Detector Construction, Primary Generator Action) */
#include "PhysicsList.hh"

// Our basic physics packages needed to do simple decay
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"

PhysicsList::PhysicsList()
  : G4VModularPhysicsList()
{
  //setVerboseLevel(1);

  /*
   * All we have to do is tell GEANT4 that we are using these lists
   */
  // Default physics
  RegisterPhysics(new G4DecayPhysics());

  // Radioactive Decay
  RegisterPhysics(new G4RadioactiveDecayPhysics());

  // E&M physics
  RegisterPhysics(new G4EmStandardPhysics());
}

PhysicsList::~PhysicsList()
{}

/*
 * Cuts are a threshold value at which a secondary will not be created. From the 
 * documentation they note that this is because some of the elctromagnetic processes
 * will create infrared divergence if this is not set. There is also a max threshold
 * energy set at 10 GeV and can be changed by running "/cuts/setMaxCutEnergy" in the
 * command line of the run.
 *
 * We will just keep the defaults
 */
void PhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}
