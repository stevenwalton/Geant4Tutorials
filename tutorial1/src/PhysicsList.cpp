/* Second REQUIRED file (Detector Construction, Primary Generator Action) */
#include "PhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"

PhysicsList::PhysicsList()
  : G4VModularPhysicsList()
{
  //setVerboseLevel(1);

  // Default physics
  RegisterPhysics(new G4DecayPhysics());

  // Radioactive Decay
  RegisterPhysics(new G4RadioactiveDecayPhysics());

  // E&M physics
  RegisterPhysics(new G4EmStandardPhysics());
}

PhysicsList::~PhysicsList()
{}

void PhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}
