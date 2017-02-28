#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4HCofThisEvent.hh"

class EventAction : public G4UserEventAction
{
    public:
        EventAction();
        virtual ~EventAction();

        virtual void BeginOfEventAction(const G4Event* event);
        virtual void   EndOfEventAction(const G4Event* event);

        inline void AddEnergy(G4double edep) {totalEnergy += edep;}
        inline G4double GetTotalEnergy() { return totalEnergy; }
        inline G4int GetfEventID() { return fEventID;}
        inline G4HCofThisEvent* GetHCofThisEvent() { return fHCE;}
        // Get the effective dosages
        inline void addEffectiveDose(G4double effectiveDose) { effDose += effectiveDose; }
        inline void addProtDose(G4double pDose) { protDose += pDose; }
        inline void addBetaDose(G4double bDose) { betaDose += bDose; }
        inline void addAlphDose(G4double aDose) { alphDose += aDose; }
        inline void addNeutDose(G4double nDose) { neutDose += nDose; }
        inline void addGammDose(G4double gDose) { gammaDose += gDose; }


    private:
        G4double totalEnergy;
        G4int fEventID;
        G4HCofThisEvent* fHCE;
        G4double effDose;
        G4double protDose;
        G4double betaDose;
        G4double alphDose;
        G4double neutDose;
        G4double gammaDose;
};

#endif
