#include "EventAction.hh"
#include "RunAction.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh" 
#include "Randomize.hh"
#include <iomanip>
#include "G4HCofThisEvent.hh"
#include "G4SystemOfUnits.hh"

EventAction::EventAction(RunAction* runAction)
    : G4UserEventAction(),
      fRunAction(runAction),
      totalEnergy(0.),
      effDose(0.)
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
    totalEnergy = 0.;
    effDose = 0.;
}

void EventAction::EndOfEventAction(const G4Event* event)
{
   
    G4int eventID = event -> GetEventID();
    fEventID = eventID;
    fHCE = event -> GetHCofThisEvent();
    G4int printModulo = G4RunManager::GetRunManager() -> GetPrintProgress();
    if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) )
    {
        fRunAction -> AddEffectiveDosage(effDose);
        G4cout << "\n\n---> End of Event: " << eventID << G4endl;

        G4cout << " Total deposited energy: " << std::setw(7)
                                              << G4BestUnit(totalEnergy, "Energy")
               << "\n Effective Dose: "       << effDose << " Sv"
                                              << G4endl;
    }
}
