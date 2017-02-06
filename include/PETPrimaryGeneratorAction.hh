#ifndef PETPRIMARYGENERATORACTION_H
#define PETPRIMARYGENERATORACTION_H

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4SingleParticleSource.hh"
#include "PETPrimaryGeneratorActionMessenger.hh"

class G4Event;

class PETPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{

public:
    PETPrimaryGeneratorAction();
    ~PETPrimaryGeneratorAction();

    void GeneratePrimaries(G4Event* event);

    void SetEnergy(G4double energy);

private:
    G4SingleParticleSource* CircleSource;
    G4SPSEneDistribution* Energy;
    PETPrimaryGeneratorActionMessenger* Messenger;
};

#endif


