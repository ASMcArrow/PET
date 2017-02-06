#ifndef PETPRIMARYGENERATORACTIONMESSENGER_HH
#define PETPRIMARYGENERATORACTIONMESSENGER_HH

#include "G4UImessenger.hh"
#include "globals.hh"

class PETPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;

class PETPrimaryGeneratorActionMessenger: public G4UImessenger
{

public:
    PETPrimaryGeneratorActionMessenger(PETPrimaryGeneratorAction* primaryGeneratorAction);
    virtual ~PETPrimaryGeneratorActionMessenger();

    virtual void SetNewValue(G4UIcommand* command, G4String newValue);

private:
    PETPrimaryGeneratorAction* PrimaryGeneratorAction;
    G4UIdirectory* Directory;
    G4UIcmdWithADoubleAndUnit* SetEnergyCmd;

};

#endif // PETPRIMARYGENERATORACTIONMESSENGER_HH
