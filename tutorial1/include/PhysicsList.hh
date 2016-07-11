/* Our Physics List header */
#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"

/* G4VModularPhysicsList includes:
 * G4DecayPhysics (default)
 * G4RadioActiveDecayPhysics
 * G4EmStandardPhysics
 *
 * Which are used in the .cpp file
 */

class PhysicsList : public G4VModularPhysicsList
{
  public:
    PhysicsList();
    ~PhysicsList();
    
    virtual void SetCuts();

};
#endif
