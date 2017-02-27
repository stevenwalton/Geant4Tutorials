#include "EventAction.hh"
#include "RunAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

EventAction::EventAction()
    : G4UserEventAction,
      totalEnergy(0.)
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* event)
{
    totalEnergy = 0.;
}

void EventAction::EndOfEventAction(const G4Event* event)
{
    //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
   
    G4int eventID = event -> GetEventID();
    G4int printModulo = G4RunManager::GetRunManager() -> GetPrintProgress();
    if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) )
    {
        G4cout << "---> End of Event: " << eventID << G4endl;

        G4cout << " Total deposited energy: " << std::setw(7)
                                              << G4BestUnit(totalEnergy, "Energy")
                                              << G4endl;
    }
}
