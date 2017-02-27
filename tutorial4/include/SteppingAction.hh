#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"

class DetectorConstruction;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
    public:
        SteppingAction(const DetectorConstruction* detConst, EventAction* event);
        virtual ~SteppingAction();

    private:
        DetectorConstruction* fDetConst;
        EventAction* fEvent;

};

#endif
