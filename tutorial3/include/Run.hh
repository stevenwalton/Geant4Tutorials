#ifndef Run_h 
#define Run_h 1

#include "G4Run.hh"
#include "globals.hh"

class Run : public G4Run
{
  public:
    Run();
    virtual ~Run();

    virtual void RecordEvent(const G4Event*);
    virtual void Merge(const G4Run*);

    G4double GetSumDose() const {return SumDose;}

  private:
    G4int CollID_plate;
    G4int PrintModulo;
    G4double SumDose;
};
#endif
