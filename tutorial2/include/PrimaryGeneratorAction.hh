/* We have to have a .hh file for our primary generator action file */
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh" 

class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();  

  public:
    virtual void GeneratePrimaries(G4Event*);

    const G4ParticleGun* GetParticleGun() const { return particleGun;}
    

  private:
    G4ParticleGun* particleGun;

};

#endif
