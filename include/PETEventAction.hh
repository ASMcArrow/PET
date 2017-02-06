#ifndef PETEVENTACTION_HH
#define PETEVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4LogicalVolume.hh"
#include "globals.hh"

class PETEventAction : public G4UserEventAction
{

public:
    PETEventAction();
    ~PETEventAction();

    void BeginOfEventAction(const G4Event* event);
    void EndOfEventAction(const G4Event* event);
};

#endif // PETEVENTACTION_HH
