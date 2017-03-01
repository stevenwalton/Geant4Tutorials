#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include <cmath>

#include "G4UnitsTable.hh"

SteppingAction::SteppingAction(const DetectorConstruction* detConst, EventAction* event)
    : G4UserSteppingAction(),
      fDetConst(detConst),
      fEvent(event),
      effectiveDose(0.),
      energy(0.)
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    // Volume of current Step
    G4VPhysicalVolume* volume = step -> GetPreStepPoint() -> GetTouchableHandle() -> GetVolume();
    // Get Energy deposit
    // We only run next steps if the fEvent happens in the detector to save computation time
    if ( volume == fDetConst -> GetAbsorberPV() )
    {
        G4double mass = (step -> GetPreStepPoint() -> GetTouchableHandle() -> GetVolume() -> GetLogicalVolume() -> GetMass())/kg;
        energy = step -> GetTotalEnergyDeposit();
        fEvent -> AddEnergy(energy);
        // We want to convert to Sieverts. Which is J/kg
        G4double edep = (energy/MeV) * ( 1.60218e-13 ); // MeV = 1.602e-13 J
        G4double nonIon = step -> GetNonIonizingEnergyDeposit();
        G4double dose = (edep - nonIon) / mass;
        G4String particleName = step -> GetTrack() -> GetDynamicParticle() -> GetDefinition() -> GetParticleName();
        if ( particleName == "gamma" || particleName == "e-" || particleName == "e+" )
        {
            if ( particleName == "gamma" )
                fEvent -> addGammDose(dose);
            else
                fEvent -> addBetaDose(dose);
        }
        else if ( particleName == "proton" )
        {
            dose *= 2.;
            fEvent -> addProtDose(dose);
        }
        else if ( particleName == "alpha" /* or fission fragments */ )
        {
            dose *= 20.;
            fEvent -> addAlphDose(dose);
        }
        // Weights from ICRP 103
        else if ( particleName == "neutron" )
        {
            G4double weight = 0.;
            if ( energy < 1*MeV )
                weight = 2.5 + (18.2*exp(-1 * pow(log(energy),2)/6));
            else if ( energy< 50 * MeV )
                weight = 5.0 + (17.0 * exp(-1 * pow(log(2*energy),2)/6));
            else // E_n > 50 MeV
                weight = 2.5 + (3.25 * exp(-1 * pow(log(0.04*energy),2)/6));
            dose *= weight;
            fEvent -> addNeutDose(dose);
        }
        else
        {
            dose *= 0.;
            G4cout << "\nWARNING: WE DON'T HAVE WEIGHT FOR: " << particleName << G4endl;
        }

        effectiveDose += dose;
        fEvent -> addEffectiveDose(dose);
    }
    
}
