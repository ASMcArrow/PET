#include "PETPrimaryGeneratorAction.hh"
#include "PETActionInitialization.hh"
#include "PETRunAction.hh"
#include "PETSteppingAction.hh"

PETActionInitialization::PETActionInitialization(PETDetectorConstruction *geometry)
    : G4VUserActionInitialization()
{}

PETActionInitialization::~PETActionInitialization()
{}

void PETActionInitialization::BuildForMaster() const
{
    SetUserAction(new PETRunAction("Detector"));
}

void PETActionInitialization::Build() const
{
    SetUserAction(new PETPrimaryGeneratorAction);
    SetUserAction(new PETRunAction("Detector"));
    SetUserAction(new PETSteppingAction);
}
