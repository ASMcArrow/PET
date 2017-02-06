#include "PETRun.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "PETDetectorHit.hh"

PETRun::PETRun(const G4String detectorName, G4bool verbose) : G4Run()
{
    CollNames = new std::vector<G4String>;
    CollIDs = new std::vector<G4int>;
    HCollections = new std::vector<G4double*>;

    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    G4VSensitiveDetector* detector = SDman->FindSensitiveDetector(detectorName);

    CollNum = detector->GetNumberOfCollections();
    for (G4int i = 0; i < CollNum; i++)
    {
        G4String collName =  detector->GetCollectionName(i);
        CollNames->push_back(collName);
        CollIDs->push_back(SDman->GetCollectionID(collName));

        G4double* collection = new double[100];
        for (int j = 0; j < 100; ++j)
        {
            collection[j] = 0;
        }

        HCollections->push_back(collection);
    }

    Verbose = verbose;
}

PETRun::~PETRun()
{
    for (G4int i = 0; i < CollNum; i++)
    {
        delete (*HCollections)[i];
    }

    delete HCollections;
    delete CollNames;
    delete CollIDs;
}

void PETRun::RecordEvent(const G4Event* aEvent)
{
    numberOfEvent++;

    G4HCofThisEvent* HCE = aEvent->GetHCofThisEvent();
    if(HCE!=NULL)
    {
        PETDetectorHitsCollection* HC = (PETDetectorHitsCollection*)(HCE -> GetHC((*CollIDs)[0]));
        if(HC!=NULL)
        {
            for (G4int i = 0; i < HC->entries(); i++)
            {
                PETDetectorHit *hit = (PETDetectorHit*)(HC->GetHit(i));
                if (Verbose)
                {
                    G4cout << "HitsVector Initial: " << "i = "<< i << " Energy deposition is " << hit->GetEdep()
                           << " Position is " << hit->GetReplicaNumK() << G4endl;

                }
                G4int numi = hit->GetReplicaNumI();
                G4double edep = hit->GetEdep();
                ((*HCollections)[0])[numi] += edep;
            }
        }

        for (G4int i = 1; i < CollNum; i++)
        {
            HC = (PETDetectorHitsCollection*)(HCE -> GetHC((*CollIDs)[i]));
            if(HC!=NULL)
            {
                for (G4int j = 0; j < HC->entries(); j++)
                {
                    PETDetectorHit *hit = (PETDetectorHit*)(HC->GetHit(j));
                    G4int numi = hit->GetReplicaNumI();
                    (*HCollections)[i][numi] += 1;
                }
            }
        }
    }
}

void PETRun::Merge(const G4Run * aRun)
{
    const PETRun *localRun = static_cast<const PETRun*>(aRun);
    std::vector<G4double*>* localcollection = localRun->HCollections;

    for (int num = 0; num < CollNum; num++)
    {
        for (int i = 0; i < 100; i++)
        {
            (*HCollections)[num][i] += (*localcollection)[num][i];
        }
    }

    G4Run::Merge(aRun);
}

