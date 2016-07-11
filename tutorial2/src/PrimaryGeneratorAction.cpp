/**
 * Remember to use the header file in the /include folder
 * This is the third REQUIRED file (Detector Const, and Phys list)
 */

#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
#include "G4Geantino.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4int n_particle = 1;   
  particleGun = new G4ParticleGun(n_particle);  

  particleGun -> SetParticleDefinition(G4Geantino::GeantinoDefinition()); 
  particleGun -> SetParticleEnergy(1.0 * MeV);  
  particleGun -> SetParticlePosition(G4ThreeVector(-1.*m, 0.*m, 0.*m)); 
}

// Create destructor
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

// Primary event
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  particleGun -> SetParticleMomentumDirection(G4ThreeVector(1.0,0.,0.)); 
 
  particleGun -> GeneratePrimaryVertex(anEvent);  
}
