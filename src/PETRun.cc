#include "PETRun.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "PETDetectorHit.hh"

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
        PETDetectorHitsCollection* HC = (PETDetectorHitsCollection*)(HCE -> GetHC(CollectionID));
        if(HC!=NULL)
        {
            for (G4int i = 0; i < HC->entries(); i++)
            {
                PETDetectorHit *hit = (PETDetectorHit*)(HC->GetHit(i));
                if (Verbose)
                {
                    G4cout << "HitsVector Initial: " << "i = "<< i << " Energy deposition is " << hit->GetEdep()
                           << " Position is" << hit->GetReplicaNum() << G4endl;
                }
                G4int num = hit->GetReplicaNum();
                Cells[num] += hit->GetEdep();
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

