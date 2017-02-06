#include "PETRunAction.hh"
#include "PETRun.hh"

#include "G4RunManager.hh"
#include "PETDetectorConstruction.hh"
#include "G4THitsMap.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Run.hh"
#include "G4HadronicInteraction.hh"
#include "G4HadronicInteractionRegistry.hh"
#include "G4CascadeInterface.hh"
#include "G4BinaryCascade.hh"
#include "G4AblaInterface.hh"
#include "G4INCLXXInterface.hh"
#include "G4INCLXXInterfaceStore.hh"
#include "G4FermiBreakUp.hh"
#include "G4NistManager.hh"
#include "G4Evaporation.hh"

#include <fstream>
#define _USE_MATH_DEFINES

PETRunAction::PETRunAction(const G4String detectorName) : G4UserRunAction()
{
    DetectorName = detectorName;

    CurrentName.push_back("115MeV");
    CurrentName.push_back("120MeV");
    CurrentName.push_back("125MeV");
    CurrentName.push_back("130MeV");

    times = 0;
}

PETRunAction::~PETRunAction()
{}

G4Run* PETRunAction::GenerateRun()
{
    return new PETRun(DetectorName, 0);
}

void PETRunAction::BeginOfRunAction(const G4Run* aRun)
{}

void PETRunAction::EndOfRunAction(const G4Run* aRun)
{
    if(!IsMaster()) return;

    PETRun* run = (PETRun*)aRun;
    std::vector<G4double*>* collections = run->GetHCollections();

    std::ofstream eDepFile(G4String("PET_EnergyDistribution_")+CurrentName[times]+G4String(".txt"));

    for (int i = 0; i < 100; i++)
    {
        eDepFile << i << " " << (*collections)[0][i]/MeV << "\n";
    }

    std::ofstream C11File(G4String("PET_C11Distribution_")+CurrentName[times]+G4String(".txt"));

    for (int i = 0; i < 100; i++)
    {
        C11File << i << " " << (*collections)[1][i] << "\n";
    }

    std::ofstream C10File(G4String("PET_C10Distribution_")+CurrentName[times]+G4String(".txt"));

    for (int i = 0; i < 100; i++)
    {
        C10File << i << " " << (*collections)[2][i] << "\n";
    }

    std::ofstream O15File(G4String("PET_O15Distribution_")+CurrentName[times]+G4String(".txt"));

    for (int i = 0; i < 100; i++)
    {
        O15File << i << " " << (*collections)[3][i] << "\n";
    }

    times++;
}
