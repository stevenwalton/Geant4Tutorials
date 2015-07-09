/**
 * Remember to use the header file in the /include folder
 * This is the third REQUIRED file (Detector Const, and Phys list)
 */

#include "PrimaryGeneratorAction.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4IonTable.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

/* We'll use the Geantino (non-interacting particle) for the gun, can be changed. */
PrimaryGeneratorAction::PrimaryGeneratorAction()
  : G4VUserPrimaryGeneratorAction(),
    particleGun(0)
{
  G4int n_particle = 1;   // Number of particles fired per beamOn run
  particleGun = new G4ParticleGun(n_particle);  // creation of particle gun

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable -> FindParticle(particleName="gamma");
  particleGun -> SetParticleDefinition(particle); // Use Geantino as firing particle
  particleGun -> SetParticleMomentumDirection(G4ThreeVector(1., 0., 0.));
  particleGun -> SetParticleEnergy(6.0 * MeV);  // 1GeV energy of gun
  particleGun -> SetParticlePosition(G4ThreeVector(-1.*m, 0.*m, 0.*m));   // Set gun to be at furthest x in world (far left to standard orientation)
}

// Create destructor
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

// Primary event
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  particleGun -> SetParticleMomentumDirection(G4ThreeVector(1.0,0.,0.));  // Pure x momentum
 
  particleGun -> GeneratePrimaryVertex(anEvent);  // creates the initial momentum
}
