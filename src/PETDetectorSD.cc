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
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

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
    C10HitsCollection = NULL;
    O15HitsCollection = NULL;
    PositronHitsCollection = NULL;

    SensitiveDetectorName = name;

    PromptFile.open("PromptFile.txt", std::ios::app);
    PromptFile << "Energy (Mev)   x  y  z  Angle (deg)" << G4endl;
    PromptFile.close();
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

    C10HitsCollection = new PETDetectorHitsCollection(SensitiveDetectorName,
                                                      collectionName[2]);
    C10HitsCollection->SetColID(2);

    O15HitsCollection = new PETDetectorHitsCollection(SensitiveDetectorName,
                                                      collectionName[3]);
    O15HitsCollection->SetColID(3);

//    PositronHitsCollection = new PETDetectorHitsCollection(SensitiveDetectorName,
//                                                      collectionName[4]);
//    PositronHitsCollection->SetColID(4);
}

G4bool
PETDetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* obsolete)
{
    G4StepPoint* preStep = aStep->GetPreStepPoint();
    G4TouchableHistory* touchable = (G4TouchableHistory*)(preStep->GetTouchable());

    G4int i = touchable->GetReplicaNumber(0);
//    G4int j = touchable->GetReplicaNumber(1);
//    G4int k = touchable->GetReplicaNumber(2);

    G4double energyDeposit = aStep->GetTotalEnergyDeposit();

    if (aStep->GetTrack()->GetCreatorProcess() !=NULL)
        if ((aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "protonInelastic")&&(aStep->GetTrack()->GetCurrentStepNumber() == 1))
        {
            if (aStep->GetTrack()->GetParticleDefinition()->GetParticleName() == "C11")
            {
                PETDetectorHit* detectorHit = new PETDetectorHit();
                detectorHit->SetReplicaNumI(i);
//                detectorHit->SetReplicaNumJ(j);
//                detectorHit->SetReplicaNumK(k);
                // G4cout << i << " " << j << " " << k << G4endl;
                C11HitsCollection->insert(detectorHit);
            }

            if (aStep->GetTrack()->GetParticleDefinition()->GetParticleName() == "C10")
            {
                PETDetectorHit* detectorHit = new PETDetectorHit();
                detectorHit->SetReplicaNumI(i);
//                detectorHit->SetReplicaNumJ(j);
//                detectorHit->SetReplicaNumK(k);
                C10HitsCollection->insert(detectorHit);
            }

            if (aStep->GetTrack()->GetParticleDefinition()->GetParticleName() == "O15")
            {
                PETDetectorHit* detectorHit = new PETDetectorHit();
                detectorHit->SetReplicaNumI(i);
//                detectorHit->SetReplicaNumJ(j);
//                detectorHit->SetReplicaNumK(k);
                O15HitsCollection->insert(detectorHit);
            }
        }

//     if ((aStep->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma")&&(aStep->GetTrack()->GetCurrentStepNumber() == 1)&&
//             (aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "protonInelastic"))
//     {
//         PromptFile.open("PromptFile.txt", std::ios::app);
//         PromptFile << aStep->GetTrack()->GetTotalEnergy()/MeV << " " << i << " " << j << " " << k << " " << aStep->GetPreStepPoint()->GetMomentumDirection().getTheta()/deg << G4endl;
//         aStep->GetTrack()->SetTrackStatus(fStopAndKill);
//         PromptFile.close();
//     }


//    if ((aStep->GetTrack()->GetParticleDefinition()->GetParticleName() == "e+")
//            &&(aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "annihil")
//            &&(aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "RadioactiveDecay"))
//    {

//        PETDetectorHit* detectorHit = new PETDetectorHit();
//        detectorHit->SetReplicaNum(i);
//        PositronHitsCollection->insert(detectorHit);

//    }

    if(energyDeposit != 0)
    {
        PETDetectorHit* detectorHit = new PETDetectorHit();
        detectorHit->SetEdep(energyDeposit);
        detectorHit->SetReplicaNumI(i);
//        detectorHit->SetReplicaNumJ(j);
//        detectorHit->SetReplicaNumK(k);
        EdepHitsCollection->insert(detectorHit);
        // G4cout << "Energy deposit is " << energyDeposit << G4endl;

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

    HCID = GetCollectionID(2);
    HCE->AddHitsCollection(HCID, C10HitsCollection);

    HCID = GetCollectionID(3);
    HCE->AddHitsCollection(HCID, O15HitsCollection);

//    HCID = GetCollectionID(4);
//    HCE->AddHitsCollection(HCID, PositronHitsCollection);
}

#endif // PETDETECTORSD_CC
