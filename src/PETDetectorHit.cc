#include "PETDetectorHit.hh"

#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4ThreadLocal G4Allocator<PETDetectorHit>* PETDetectorHitAllocator = 0;

PETDetectorHit::PETDetectorHit()
{
    ReplicaNumI = 0;
    ReplicaNumJ = 0;
    ReplicaNumK = 0;
    Position.set(0,0,0);
    EnergyDeposit = 0;
}

PETDetectorHit::~PETDetectorHit()
{}

PETDetectorHit::PETDetectorHit(const PETDetectorHit &right)
    :G4VHit()
{
    Position = right.Position;
    ReplicaNumI = right.ReplicaNumI;
    ReplicaNumJ = right.ReplicaNumJ;
    ReplicaNumK = right.ReplicaNumK;
    EnergyDeposit = right.EnergyDeposit;
}

const PETDetectorHit&
PETDetectorHit::operator=(const PETDetectorHit &right)
{
    Position = right.Position;
    ReplicaNumI = right.ReplicaNumI;
    ReplicaNumJ = right.ReplicaNumJ;
    ReplicaNumK = right.ReplicaNumK;
    EnergyDeposit = right.EnergyDeposit;

    return *this;
}

int PETDetectorHit::operator==(const PETDetectorHit &right) const
{
    return((Position==right.Position)&&(ReplicaNumI==right.ReplicaNumI)&&
           (ReplicaNumJ==right.ReplicaNumJ)&&(ReplicaNumK==right.ReplicaNumK)&&
           (EnergyDeposit==right.EnergyDeposit));
}
