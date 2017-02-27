#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

SteppingAction::SteppingAction(const DetectorConstruction* detConst, EventAction* event)
    : G4UserSteppingAction(),
      fDetConst(detConst),
      fEvent(event)
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    // Volume of current Step
    G4VPhysicalVolume* volume = step -> GetPreStepPoint() -> GetTouchableHandle() -> GetVolume();

    // Get Energy deposit
    G4double edep = step -> GetTotalEnergyDeposit();
    
    fEvent -> AddEnergy(edep);
}
