#include "EventAction.hh"
#include "RunAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>
#include "G4HCofThisEvent.hh"

EventAction::EventAction()
    : G4UserEventAction(),
      totalEnergy(0.),
      effDose(0.)
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* event)
{
    totalEnergy = 0.;
    effDose = 0.;
}

void EventAction::EndOfEventAction(const G4Event* event)
{
    //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
   
    G4int eventID = event -> GetEventID();
    fEventID = eventID;
    fHCE = event -> GetHCofThisEvent();
    //totalEnergy = event -> GetTotalEnergy();
    G4int printModulo = G4RunManager::GetRunManager() -> GetPrintProgress();
    //G4cout << "\n\n----------> End of Event Action <----------\n" << G4endl;
    if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) )
    {
        G4cout << "\n\n---> End of Event: " << eventID << G4endl;

        G4cout << " Total deposited energy: " << std::setw(7)
                                              << G4BestUnit(totalEnergy, "Energy")
               << "\n Effective Dose: "       << effDose << " Sv"
                                              << G4endl;
    }
    //else
    //{
    //    G4cout << "PrintModulo is: " << printModulo << "\nAnd eventID: " << eventID << G4endl;
    //    G4cout << "Edep: " << G4BestUnit(totalEnergy, "Energy") << G4endl;
    //}
}
