/* NEW FILE
 * In this file we are mapping the dosages to the detector. We want to track the event ID
 */
#include "Run.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsMap.hh"
#include "G4SystemOfUnits.hh"


/* We want to set up the event with these parameters. Very important to set the Sum Dosage so that we don't stack the values from 
 * random points in memory */
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
  // Note how this relates to the condition above. We now can find the ID of the dose the plate gets
  if (CollID_plate < 0) 
  {
    CollID_plate = G4SDManager::GetSDMpointer() -> GetCollectionID("plate/dose");
  }

  // We also want to pull the ID for the event
  G4int evtNb = event -> GetEventID();

  // Every time an event ends we want to separate it from new events. We make this clear with our output
  if(evtNb%PrintModulo == 0)
  {
    G4cout << G4endl << "---> end of event: " << evtNb << G4endl;
  }

  // Collections of Hits
  G4HCofThisEvent* HCE = event -> GetHCofThisEvent();
  if(!HCE) return;

  // Dosage deposit in the plate
  G4double dose = 0.;

  // We need to preform a cast here to get the correct data type
  G4THitsMap<G4double>*  evtMap = static_cast< G4THitsMap<G4double>*>(HCE -> GetHC(CollID_plate));

  // Loop to map the events and add the dosages so that we get a total dose
  std::map<G4int,G4double*>::iterator i;
  for (i = evtMap -> GetMap() -> begin(); i != evtMap -> GetMap() -> end(); ++i)
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
