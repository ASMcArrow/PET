#include "PETPrimaryGeneratorActionMessenger.hh"
#include "PETPrimaryGeneratorAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

using namespace CLHEP;

PETPrimaryGeneratorActionMessenger::PETPrimaryGeneratorActionMessenger(PETPrimaryGeneratorAction *primaryGeneratorAction)
    :G4UImessenger(), PrimaryGeneratorAction(primaryGeneratorAction)
{
    Directory = new G4UIdirectory("/Source/");
    Directory->SetGuidance("The source of particles");

    SetEnergyCmd = new G4UIcmdWithADoubleAndUnit("/Source/setEnergy", this);
    SetEnergyCmd->SetGuidance("Set energy of source (in MeV)");
    SetEnergyCmd->SetParameterName("Energy", false);
    SetEnergyCmd->SetUnitCategory("Energy");
    SetEnergyCmd->SetDefaultUnit("MeV");
    SetEnergyCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

PETPrimaryGeneratorActionMessenger::~PETPrimaryGeneratorActionMessenger()
{
    delete Directory;
}

void PETPrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if(command == SetEnergyCmd)
    {
        G4double energy = (SetEnergyCmd->ConvertToDimensionedDouble(newValue));
        G4cout << "ENERGY IS " << energy/MeV << G4endl;
        PrimaryGeneratorAction->SetEnergy(energy);
    }
}
