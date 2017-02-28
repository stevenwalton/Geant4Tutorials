#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include <cmath>

SteppingAction::SteppingAction(const DetectorConstruction* detConst, EventAction* event)
    : G4UserSteppingAction(),
      fDetConst(detConst),
      fEvent(event),
      effectiveDose(0.)
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
        G4double eng = step -> GetTotalEnergyDeposit();
        G4double edep = (eng/eV) * ( 1.60218e-19 );
        G4double nonIon = step -> GetNonIonizingEnergyDeposit();
        G4double dose = (edep - nonIon) / mass;
        G4String particleName = step -> GetTrack() -> GetDynamicParticle() -> GetDefinition() -> GetParticleName();
        G4double siv = 0.;
        if ( particleName == "gamma" || particleName == "e-" || particleName == "e+" )
        {
            siv = dose/gray;
            if ( particleName == "gamma" )
                fEvent -> addGammDose(siv);
            else
                fEvent -> addBetaDose(siv);
        }
        else if ( particleName == "proton" )
        {
            siv = 2* (dose/gray);
            fEvent -> addProtDose(siv);
        }
        else if ( particleName == "alpha" /* or fission fragments */ )
        {
            siv = 20 * (dose/gray);
            fEvent -> addAlphDose(siv);
        }
        // Weights from ICRP 103
        else if ( particleName == "neutron" )
        {
            G4double weight = 0.;
            if ( eng < 1*MeV )
                weight = 2.5 + (18.2*exp(-1 * pow(log(eng/MeV),2)/6));
            else if ( eng < 50 * MeV )
                weight = 5.0 + (17.0 * exp(-1 * pow(log(2*eng/MeV),2)/6));
            else // E_n > 50 MeV
                weight = 2.5 + (3.25 * exp(-1 * pow(log(0.04*eng/MeV),2)/6));
            siv = weight * (dose/gray);
            fEvent -> addNeutDose(siv);
        }
        else
            siv = -1. *(dose/gray);

        effectiveDose += siv;
        //G4cout << particleName << " hit with " << dose/gray << " Gy with effective dose: " << siv << " sieverts" << G4endl;
        //G4cout << particleName << ": " << dose/gray << " Gy " << eng/MeV << " MeV " << siv << " Sv" << G4endl;
        //G4cout << "EffectiveDose: " << effectiveDose << G4endl;
        fEvent -> addEffectiveDose(effectiveDose);
    }
    
}
