#include "Run.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsMap.hh"
#include "G4SystemOfUnits.hh"

Run::Run()
  : G4Run(),
    CollID_plate(-1),
    PrintModulo(10000),
    SumDose(0.)
{}

Run::~Run()
{}

void Run::RecordEvent(const G4Event* event)
{
  if (CollID_plate < 0) 
  {
    CollID_plate = G4SDManager::GetSDMpointer() -> GetCollectionID("plate/dose");
  }

  G4int evtNb = event -> GetEventID();

  if(evtNb%PrintModulo == 0)
  {
    G4cout << G4endl << "---> end of event: " << evtNb << G4endl;
  }

  // Collections of Hits
  G4HCofThisEvent* HCE = event -> GetHCofThisEvent();
  if(!HCE) return;

  // Dosage deposit in the plate
  G4double dose = 0.;

  G4THitsMap<G4double>*  evtMap = static_cast< G4THitsMap<G4double>*>(HCE -> GetHC(CollID_plate));

  std::map<G4int,G4double*>::iterator i;
  for (i = evtMap -> GetMap() -> begin(); i != evtMap -> GetMap() -> end(); i++)
  {
    dose = *(i -> second);
  }
  SumDose += dose;

  G4Run::RecordEvent(event);

}

void Run::Merge(const G4Run* aRun)
{
  const Run* localRun = static_cast<const Run*>(aRun);
  SumDose += localRun -> SumDose;

  G4Run::Merge(aRun);
}

