#include "PETParallelWorld.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4PVReplica.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"
#include "G4PVDivision.hh"
#include "G4PVParameterised.hh"
#include "G4PSDoseDeposit3D.hh"
#include "G4PSEnergyDeposit.hh"
#include "PETDetectorSD.hh"

PETParallelWorld::PETParallelWorld(G4String worldName)
    :G4VUserParallelWorld(worldName)
{}

PETParallelWorld::~PETParallelWorld()
{}

void PETParallelWorld::Construct()
{
    G4VisAttributes* visAttributes = new G4VisAttributes;
    visAttributes->SetColor(0,0,1);

    G4VPhysicalVolume *ghostWorld = GetWorld();
    G4LogicalVolume *worldLog = ghostWorld->GetLogicalVolume();

    // Place volumes in the parallel world

    G4Box* ghostDetector = new G4Box("GhostDetectorBox", 15.0*cm, 15.0*cm, 5.0*cm);
    G4LogicalVolume* ghostDetectorLog = new G4LogicalVolume(ghostDetector, 0, "GhostDetectorLog");
    new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, 5.0*cm), ghostDetectorLog, "GhostDetectorPhys", worldLog, 0, 0);
    ghostDetectorLog->SetVisAttributes(visAttributes);

    // Divide along Z coordinate

    G4Box* ghostLayer = new G4Box("GhostDetectorBox", 15.0*cm, 15.0*cm, 0.05*cm);
    GhostLayerLog = new G4LogicalVolume(ghostLayer, 0, "GhostLayerLog");
    new G4PVReplica("GhostLayerReplica", GhostLayerLog, ghostDetectorLog, kZAxis, 100, 0.1*cm);

//    G4Box* ghostRow = new G4Box("ghostRow", 15.0*cm, 0.5*cm, 0.5*cm);
//    G4LogicalVolume* ghostRowLog = new G4LogicalVolume(ghostRow, 0, "GhostRowLog");
//    new G4PVReplica("GhostRowPhys", ghostRowLog, ghostLayerLog, kYAxis, 30, 1*cm, 0);

//    G4Box* ghostVoxel = new G4Box("ghostVoxel", 0.5*cm, 0.5*cm, 0.5*cm);
//    GhostVoxelLog = new G4LogicalVolume(ghostVoxel, 0, "GhostVoxelLog");
//    new G4PVReplica("GhostVoxelPhys", GhostVoxelLog, ghostRowLog, kXAxis, 30, 1*cm, 0);
}

void PETParallelWorld::ConstructSD()
{
    G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

    G4CollectionNameVector* collections = new G4CollectionNameVector;
    collections->insert("EdepHitsCollection");
    collections->insert("C11HitsCollection");
    collections->insert("C10HitsCollection");
    collections->insert("O15HitsCollection");
//    collections->insert("PositronHitsCollection");

    G4VSensitiveDetector* isoDetector = new PETDetectorSD("Detector", collections);
    G4SDManager::GetSDMpointer()->AddNewDetector(isoDetector);
    SetSensitiveDetector(GhostLayerLog, isoDetector);
}
