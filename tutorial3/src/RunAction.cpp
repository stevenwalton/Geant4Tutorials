/* NEW FILE
 * Here we need to control our output. Most of this file is to handle the 
 * dosage output
 */
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "Run.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleGun.hh"

RunAction::RunAction()
  : G4UserRunAction()
{

  // We need the units for the dosages
  const G4double milligray = 1.e-3 * gray;
  const G4double microgray = 1.e-6 * gray;
  const G4double nanogray  = 1.e-9 * gray;
  const G4double picogray  = 1.e-12* gray;

  // We really want units that are more easily read
  new G4UnitDefinition("milligray", "milliGy", "Dose", milligray);
  new G4UnitDefinition("microgray", "microGy", "Dose", microgray);
  new G4UnitDefinition("nanogray" , "nanoGy" , "Dose", nanogray);
  new G4UnitDefinition("picogray" , "picoGy" , "Dose", picogray);
}

RunAction::~RunAction()
{}

G4Run* RunAction::GenerateRun()
{
  return new Run;
}

void RunAction::BeginOfRunAction(const G4Run* run)
{
  G4cout << "### Run " << run -> GetRunID() << " start." << G4endl;

  // We need to inform the run manager to save the random number seed
  G4RunManager::GetRunManager() -> SetRandomNumberStore(false);
}

void RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run -> GetNumberOfEvent();
  if (nofEvents == 0) return;

  // Our run conditions
  const PrimaryGeneratorAction* generatorAction 
    = static_cast<const PrimaryGeneratorAction*>
    (G4RunManager::GetRunManager() -> GetUserPrimaryGeneratorAction());
  G4String partName;
  
  if (generatorAction)
  {
    G4ParticleDefinition* particle 
      = generatorAction -> GetParticleGun() -> GetParticleDefinition();
    partName = particle -> GetParticleName();
  }

  // Get our results \ o /
  const Run* tRun = static_cast<const Run*>(run);
  G4double sumDose = tRun -> GetSumDose();

  // And print the data
  if (IsMaster())
  {
    G4cout << G4endl
           << "--------------- End of Global Run --------------"
           << G4endl
           << " The run was " << nofEvents << "events ";
  }
  else
  {
    G4cout << G4endl
           << "--------------- End of Local Run ---------------"
           << G4endl
           << " The run was " << nofEvents << " " << partName;
  }
  G4cout << G4endl
         << "Total dose to the plate : " << G4BestUnit(sumDose, "Dose") 
         << G4endl
         << "--------------------------------------------------"
         << G4endl
         << G4endl;
}
    
