#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    virtual ~RunAction();

    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

    inline void AddEffectiveDosage(G4double dose) { totalEffectiveDosage += dose; }

  private:
    G4double runEnergy;
    G4double totalEffectiveDosage;
};

#endif
