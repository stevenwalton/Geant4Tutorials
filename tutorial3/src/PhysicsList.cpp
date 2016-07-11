#include "PhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"

PhysicsList::PhysicsList()
  : G4VModularPhysicsList()
{
  RegisterPhysics(new G4DecayPhysics());
  RegisterPhysics(new G4RadioactiveDecayPhysics());
  RegisterPhysics(new G4EmStandardPhysics());
}

PhysicsList::~PhysicsList()
{}

void PhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}
