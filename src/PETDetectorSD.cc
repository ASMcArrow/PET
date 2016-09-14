#ifndef PETDETECTORSD_CC
#define PETDETECTORSD_CC

#include "PETDetectorSD.hh"
#include "PETDetectorHit.hh"

#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4VProcess.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4TrackVector.hh"

#include <cstdio>

PETDetectorSD::PETDetectorSD(G4String name, std::vector<G4String> *collnames):
    G4VSensitiveDetector(name)
{
    for (G4int i = 0; i < collnames->size(); i++)
    {
        collectionName.insert((*collnames)[i]);
    }

    EdepHitsCollection = NULL;
    C11HitsCollection = NULL;
    SensitiveDetectorName = name;
}

PETDetectorSD::~PETDetectorSD()
{}

void
PETDetectorSD::Initialize(G4HCofThisEvent*)
{
    EdepHitsCollection = new PETDetectorHitsCollection(SensitiveDetectorName,
                                                       collectionName[0]);
    EdepHitsCollection->SetColID(0);
    C11HitsCollection = new PETDetectorHitsCollection(SensitiveDetectorName,
                                                      collectionName[1]);
    C11HitsCollection->SetColID(1);
}

G4bool
PETDetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* obsolete)
{
    G4StepPoint* preStep = aStep->GetPreStepPoint();
    G4TouchableHistory* touchable = (G4TouchableHistory*)(preStep->GetTouchable());

    G4int i = touchable->GetReplicaNumber(0);
    G4double energyDeposit = aStep->GetTotalEnergyDeposit();

    if (aStep->GetTrack()->GetCreatorProcess() !=NULL)
        if ((aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "protonInelastic")&&
                (aStep->GetTrack()->GetParticleDefinition()->GetParticleName() == "C11"))
        {
            PETDetectorHit* detectorHit = new PETDetectorHit();
            detectorHit->SetReplicaNum(i);
            C11HitsCollection->insert(detectorHit);
        }


    if(energyDeposit != 0)
    {
        PETDetectorHit* detectorHit = new PETDetectorHit();
        detectorHit->SetEdep(energyDeposit);
        detectorHit->SetReplicaNum(i);
        EdepHitsCollection->insert(detectorHit);

        return true;
    }

    return false;
}

void
PETDetectorSD::EndOfEvent(G4HCofThisEvent* HCE)
{
    int HCID = GetCollectionID(0);
    HCE->AddHitsCollection(HCID, EdepHitsCollection);

    HCID = GetCollectionID(1);
    HCE->AddHitsCollection(HCID, C11HitsCollection);
}

#endif // PETDETECTORSD_CC
