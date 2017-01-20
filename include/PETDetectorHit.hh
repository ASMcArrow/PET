#ifndef PETDETECTORHIT_HH
#define PETDETECTORHIT_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class PETDetectorHit : public G4VHit
{

public:
    PETDetectorHit();
    ~PETDetectorHit();

    PETDetectorHit(const PETDetectorHit &right);
    const PETDetectorHit& operator = (const PETDetectorHit &right);
    int operator == (const PETDetectorHit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    // void Draw();
    // void Print() {} const;

    void SetPos(G4ThreeVector xyz)
    { Position = xyz; }

    void SetReplicaNumI(G4int i)
    { ReplicaNumI = i; }

    void SetReplicaNumJ(G4int j)
    { ReplicaNumJ = j; }

    void SetReplicaNumK(G4int k)
    { ReplicaNumK = k; }

    void SetEdep(G4double de)
    { EnergyDeposit = de; }

    G4ThreeVector GetPos() const
    { return Position; }

    G4int GetReplicaNumI()
    { return ReplicaNumI; }

    G4int GetReplicaNumJ()
    { return ReplicaNumJ; }

    G4int GetReplicaNumK()
    { return ReplicaNumK; }

    G4double GetEdep() const
    { return EnergyDeposit; }

private:
    G4ThreeVector Position; // Position
    G4int ReplicaNumI; // Number of replica I
    G4int ReplicaNumJ; // Number of replica J
    G4int ReplicaNumK; // Number of replica K
    G4double EnergyDeposit; // Energy deposit in volume
};

typedef G4THitsCollection<PETDetectorHit> PETDetectorHitsCollection;
extern G4ThreadLocal G4Allocator<PETDetectorHit>* PETDetectorHitAllocator;

inline void* PETDetectorHit::operator new(size_t)
{
    if(!PETDetectorHitAllocator)
        PETDetectorHitAllocator = new G4Allocator<PETDetectorHit>;

    return (void *)PETDetectorHitAllocator->MallocSingle();
}

inline void PETDetectorHit::operator delete(void *aHit)
{
    PETDetectorHitAllocator->FreeSingle((PETDetectorHit*) aHit);
}


#endif // PETDETECTORHIT_HH
