#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4UserEventAction.hh"
#include "globals.hh"

class DetectorConstruction;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
    public:
        SteppingAction(const DetectorConstruction* detConst, EventAction* event);
        virtual ~SteppingAction();

        virtual void UserSteppingAction(const G4Step*);
        inline G4double GetEffectiveDose() { return effectiveDose;}

    private:
        const DetectorConstruction* fDetConst;
        EventAction* fEvent;
        G4double effectiveDose;

};

#endif
