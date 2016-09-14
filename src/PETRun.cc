#include "PETRun.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"

PETRun::PETRun(const G4String detectorName, G4bool verbose) : G4Run()
{
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    G4VSensitiveDetector* detector = SDman->FindSensitiveDetector(detectorName);

    CollName = detector->GetCollectionName(0);
    CollectionID = SDman->GetCollectionID(CollName);
    Verbose = verbose;

    Cells = new G4double[100];
    for (int i = 0; i < 100; i++)
    {
        Cells[i] = 0;
    }
}

PETRun::~PETRun() {}

void PETRun::RecordEvent(const G4Event* aEvent)
{
    numberOfEvent++;

    G4HCofThisEvent* HCE = aEvent->GetHCofThisEvent();
    if(HCE!=NULL)
    {
        G4THitsMap<G4double>* HC = static_cast<G4THitsMap<G4double>*>(HCE -> GetHC(CollectionID));
        G4int i = 0;
        G4int j = 0;
        if(HC!=NULL)
        {
            std::map<G4int, G4double*>::iterator it;
            for ( it = HC->GetMap()->begin(); it != HC->GetMap()->end(); it++)
            {
                i = it->first;
                Cells[i] += (*(it->second))/CLHEP::gray;
            }
        }
    }
}

void PETRun::Merge(const G4Run * aRun)
{
    const PETRun *localRun = static_cast<const PETRun*>(aRun);

    for (int i = 0; i < 100; i++)
    {
        Cells[i] += localRun->Cells[i];
    }

    G4Run::Merge(aRun);
}

