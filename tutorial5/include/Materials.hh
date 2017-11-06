#ifndef MATERIALS_hh
#define MATERIALS_hh 1

#include "G4NistManager.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

void DefineMaterials()
{
    G4NistManager* man = G4NistManager::Instance();
    G4bool isotopes = false;
    G4double density = 1.39 * g/cm3;
    G4double a = 39.95 * g/mole;
    G4Material* lAr = new G4Material("lArgon",
                                     18.,   // Z value
                                     a,     // atomic mass
                                     density);
    G4Element* H = man -> FindOrBuildElement("H", isotopes);
    G4Element* O = man -> FindOrBuildElement("O", isotopes);
    G4Material* H2O = new G4Material("Water",
                                     1.000 * g/cm3, // density
                                     2);            // Number of components
    H2O -> AddElement(H, 2);
    H2O -> AddElement(O, 1);
    
    G4Element* N = man -> FindOrBuildElement("N", isotopes);
    density = 1.290 * mg/cm3;
    G4Material* Air = new G4Material("Air", density, 2);
    Air -> AddElement(N, 70*perCent);
    Air -> AddElement(O, 30*perCent);
}
#endif

