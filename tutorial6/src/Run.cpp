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
#include "G4VPrimitiveScorer.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4String.hh"

/* We want to set up the event with these parameters. Very important to set the Sum Dosage so that we don't stack the values from 
 * random points in memory */
Run::Run()
  : G4Run(),
    CollID_plate(-1),
    nProton_ID(-1),
    nElectron_ID(-1),
    nPositron_ID(-1),
    nNeutron_ID(-1),
    PrintModulo(10000),
    SumDose(0.)
{
}

Run::~Run()
{
}

void Run::RecordEvent(const G4Event* event)//, EventAction* fEvent)
{
  // Note how this relates to the condition above. We now can find the ID of the dose the plate gets
  if (CollID_plate < 0) 
    CollID_plate = G4SDManager::GetSDMpointer() -> GetCollectionID("plate/dose");
  if ( nProton_ID < 0 )
    nProton_ID = G4SDManager::GetSDMpointer() -> GetCollectionID("plate/nProton");
  if (nElectron_ID < 0 )
    nElectron_ID = G4SDManager::GetSDMpointer() -> GetCollectionID("plate/nElectron");
  if ( nPositron_ID < 0 )
      nPositron_ID = G4SDManager::GetSDMpointer() -> GetCollectionID("plate/nPositron");
  if ( nNeutron_ID < 0 )
      nNeutron_ID = G4SDManager::GetSDMpointer() -> GetCollectionID("plate/nNeutron");

  // We also want to pull the ID for the event
  G4int evtNb = event -> GetEventID();

  // Every time an event ends we want to separate it from new events. We make this clear with our output
  if(evtNb%PrintModulo == 0)
  {
    G4cout << G4endl << "---> end of events: " << evtNb << G4endl;
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
    dose = *(i -> second);
  SumDose += dose;
  // We are using the maps to count the particles
  evtMap = (G4THitsMap<G4double>*)(HCE -> GetHC(nProton_ID));
  mapSum[0][0] += *evtMap; // Adds the Protons
  evtMap = (G4THitsMap<G4double>*)(HCE -> GetHC(nElectron_ID));
  mapSum[0][1] += *evtMap; // Adds the electrons
  evtMap = (G4THitsMap<G4double>*)(HCE -> GetHC(nPositron_ID));
  mapSum[0][2] += *evtMap; // Adds the positrons
  evtMap = (G4THitsMap<G4double>*)(HCE -> GetHC(nNeutron_ID));
  mapSum[0][3] += *evtMap; // Adds Neutrons

  G4Run::RecordEvent(event); // invoke base class method
}

// We need this function to get the total number from each map
G4double Run::GetTotal(const G4THitsMap<G4double> &map) const
{
    G4double tot = 0.;
    if ( map.GetSize() == 0 ) return tot;
    std::map<G4int,G4double*>::iterator itr;
    for (itr = map.GetMap() -> begin(); itr != map.GetMap() -> end(); ++itr )
        tot += *(itr -> second);
    return tot;
}

void Run::Merge(const G4Run* aRun)
{
  const Run* localRun = static_cast<const Run*>(aRun);
  SumDose += localRun -> SumDose;
  // Note that the order here is from the order we specified when creating the filters
  // Remember that each run is an independent event
  mapSum[0][0] += localRun -> mapSum[0][0]; // Protons
  mapSum[0][1] += localRun -> mapSum[0][1]; // Electrons
  mapSum[0][2] += localRun -> mapSum[0][2]; // Positrons
  mapSum[0][3] += localRun -> mapSum[0][3]; // Neutrons

  G4Run::Merge(aRun);
}

