#ifndef PETDETECTORSD_CC
#define PETDETECTORSD_CC

#include "PETDetectorSD.hh"
#include "PETDetectorHit.hh"

#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4VProcess.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"

#include <cstdio>

PETDetectorSD::PETDetectorSD(G4String name, G4String collname):
    G4VSensitiveDetector(name)
{
    G4String HCname;
    collectionName.insert(HCname = collname);
    HitsCollection = NULL;
    SensitiveDetectorName = name;
}

PETDetectorSD::~PETDetectorSD()
{}

void
PETDetectorSD::Initialize(G4HCofThisEvent*)
{
    HitsCollection = new PETDetectorHitsCollection(SensitiveDetectorName,
                                                   collectionName[0]);
}

G4bool
PETDetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* obsolete)
{
    G4StepPoint* preStep = aStep->GetPreStepPoint();
    G4TouchableHistory* touchable = (G4TouchableHistory*)(preStep->GetTouchable());

    G4int i = touchable->GetReplicaNumber(0);
    G4double energyDeposit = aStep->GetTotalEnergyDeposit();

    if(energyDeposit != 0)
    {
        PETDetectorHit* detectorHit = new PETDetectorHit();
        detectorHit->SetEdep(energyDeposit);
        detectorHit->SetReplicaNum(i);
        HitsCollection->insert(detectorHit);

        return true;
    }

    return false;
}

void
PETDetectorSD::EndOfEvent(G4HCofThisEvent* HCE)
{
    int HCID = GetCollectionID(0);
    HCE->AddHitsCollection(HCID, HitsCollection);
}

#endif // PETDETECTORSD_CC
