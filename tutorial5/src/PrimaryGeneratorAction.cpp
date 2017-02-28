/**
 * Remember to use the header file in the /include folder
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

//New
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
  : G4VUserPrimaryGeneratorAction(),
    particleGun(0),
    EnvelopeBox(0)
{
  G4int n_particle = 1;   
  particleGun = new G4ParticleGun(n_particle); 

  // Here we'll load the whole particle table to be able to call a lookup
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable -> FindParticle(particleName="gamma");

  particleGun -> SetParticleDefinition(particle); 
  particleGun -> SetParticleEnergy(6.0 * MeV);  

  //particleGun -> SetParticlePosition(G4ThreeVector(-1.*m, 0.*m, 0.*m)); 
  particleGun -> SetParticleMomentumDirection(G4ThreeVector(1., 0., 0.));
}

// Create destructor
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

// Primary event
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
   /*
   * To avoid dependence on Detector Construction we will get an envelope volume
   * from the G4LogicalVolumeStore
   *
   * Here we will be assuming our box is sitting in a world where the radiation flux
   * is coming from the -x direction. Thus we will have a uniform random start location
   * through the YZ plane
   */
  G4double envSizeX = 0.;
  G4double envSizeYZ  = 0.;

  if ( !EnvelopeBox )
  {
     G4LogicalVolume* envLV = G4LogicalVolumeStore::GetInstance() -> GetVolume("World");
     if ( envLV ) EnvelopeBox = dynamic_cast<G4Box*>( envLV -> GetSolid() );
  }

  if ( EnvelopeBox ) 
  {
     envSizeYZ = EnvelopeBox -> GetYHalfLength() *2.;
     envSizeX  = EnvelopeBox -> GetXHalfLength() *2.;
  }
  else
  {
     G4ExceptionDescription msg;
     msg << "World volume of box shape is not found.\n";
     msg << "Perhaps you have changed the geometry.\n";
     msg << "\nWhere has the world gone?";
     G4Exception("PrimaryGeneratorAction::GeneratePrimaries()","Mycode0001",JustWarning,msg);
  }

  // We won't use the outer 10% edge
  G4double size = 0.9;
  // Since we are starting in the -x direction and firing in the x direction we want the
  // particles to come uniformly out of the YZ plane
  G4double x0 = 0.5 * envSizeX; 
  G4double y0 = size * envSizeYZ * (G4UniformRand() - 0.5);
  G4double z0 = size * envSizeYZ  * (G4UniformRand() - 0.5);

  particleGun -> SetParticlePosition(G4ThreeVector(-x0,y0,z0));
  //particleGun -> SetParticleMomentumDirection(G4ThreeVector(1.0,0.,0.));  // Pure x momentum
 
  particleGun -> GeneratePrimaryVertex(anEvent);  // creates the initial momentum
}
