// #undef G4MULTITHREADED
#undef G4VIS_USE

#include <cstdio>
#include <ctime>

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#include "G4UImanager.hh"
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "PETPhysicsList.hh"
#include "PETDetectorConstruction.hh"
#include "PETPrimaryGeneratorAction.hh"
#include "PETActionInitialization.hh"
#include "PETParallelWorld.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4CsvAnalysisManager.hh"
#include "G4PathFinder.hh"
#include "G4Navigator.hh"
#include "G4PenelopeIonisationModel.hh"

#include <math.h>

int main(int argc,char** argv)
{
    // Set the custom seed for the random engine
    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    G4long seed = time(NULL);
    G4Random::setTheSeed(seed);

#ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(8);
#else
    G4RunManager* runManager = new G4RunManager;
#endif

    G4GeometryManager::GetInstance()->SetWorldMaximumExtent(3*m);
    G4PathFinder::GetInstance()->SetVerboseLevel(0);

    PETDetectorConstruction* massWorld = new PETDetectorConstruction;
    massWorld->RegisterParallelWorld(new PETParallelWorld("PETParallelWorld"));
    runManager->SetUserInitialization(massWorld);

    G4VModularPhysicsList* physicsList = new PETPhysicsList;
    physicsList->SetVerboseLevel(0);
    runManager->SetUserInitialization(physicsList);

    PETActionInitialization* actionInit = new PETActionInitialization(massWorld);
    runManager->SetUserInitialization(actionInit);
    runManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

#ifdef G4VIS_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
    delete visManager;

#else
    UImanager->ApplyCommand("/Source/setEnergy 115 MeV");
    runManager->BeamOn(10000000);
    UImanager->ApplyCommand("/Source/setEnergy 120 MeV");
    runManager->BeamOn(10000000);
    UImanager->ApplyCommand("/Source/setEnergy 125 MeV");
    runManager->BeamOn(10000000);
    UImanager->ApplyCommand("/Source/setEnergy 130 MeV");
    runManager->BeamOn(10000000);
#endif

    delete runManager;
    return 0;
}
