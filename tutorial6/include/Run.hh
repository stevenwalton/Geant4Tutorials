#ifndef Run_h 
#define Run_h 1

#include "G4Run.hh"
#include "globals.hh"
#include "G4THitsMap.hh"
#include "G4UserEventAction.hh"
//#include "EventAction.hh"

//class EventAction;

class Run : public G4Run
            //public EventAction
{
  public:
    Run();
    virtual ~Run();

    virtual void RecordEvent(const G4Event* event/*, EventAction* fEvent*/);
    virtual void Merge(const G4Run*);

    G4double GetSumDose() const {return SumDose;}
    // New functions will pull values from map
    G4double GetNProtons() const    { return GetTotal(mapSum[0][0]); }
    G4double GetNElectrons() const  { return GetTotal(mapSum[0][1]); }
    G4double GetNPositrons() const  { return GetTotal(mapSum[0][2]); }
    G4double GetNNeutrons() const   { return GetTotal(mapSum[0][3]); }

    G4double GetEffectiveDose() const { return effectiveDosage; }
    inline void AddEffectiveDosage(G4double dose) { effectiveDosage += dose; }

  private:
    G4int CollID_plate;
    // We need ID values
    G4int nProton_ID;
    G4int nElectron_ID;
    G4int nPositron_ID;
    G4int nNeutron_ID;

    G4int PrintModulo;
    G4double SumDose;
    // Map well count the number of secondaries we have. We are just specifying the size 
    G4THitsMap<G4double> mapSum[2][3];
    // Function defined in the class file
    G4double GetTotal(const G4THitsMap<G4double> &map) const;

    G4double effectiveDosage;
};
#endif
