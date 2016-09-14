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
    Cells = run->GetCells();

    std::ofstream PETFile("PET_DoseDistribution.txt");

    for (int j = 0; j < 100; j++)
    {
        PETFile << (1.0 + j*2) << " " << Cells[j]/1000 << "\n";
    }
}
