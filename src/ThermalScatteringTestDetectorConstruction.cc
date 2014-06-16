#include "ThermalScatteringTestDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"

#include "G4RunManager.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"

#include "G4TransportationManager.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include <stdio.h>

ThermalScatteringTestDetectorConstruction::ThermalScatteringTestDetectorConstruction()
: fCheckOverlaps(true), flogicalWorld(NULL)
{
}

ThermalScatteringTestDetectorConstruction::~ThermalScatteringTestDetectorConstruction()
{
}

G4VPhysicalVolume* ThermalScatteringTestDetectorConstruction::Construct()
{
    // Define materials
    DefineMaterials();
    
    // Define volumes
    return DefineVolumes();
    
}

void ThermalScatteringTestDetectorConstruction::DefineMaterials()
{
    // Get nist material manager
    G4NistManager* nistManager = G4NistManager::Instance();
    
    // Define needed Nist Materials
    nistManager->FindOrBuildMaterial("G4_Galactic");
    nistManager->FindOrBuildMaterial("G4_lH2");
    //nistManager->FindOrBuildMaterial("G4_WATER");
    
    /*
    // Create materials from ground up
    G4String name, symbol;          // a=mass of a mole;
    G4double a, z, density;         // z=mean number of protons;
    
    G4int ncomponents, natoms;
    G4double temperature, pressure;
    
    // Hydrogen
    G4Element* elH1 = new G4Element(name="TS_H_of_Para_Hydrogen", symbol="H1", z=1, a=1.01*g/mole);
    
    G4Material* matH1 = new G4Material("TS_lH2", density=0.0708*g/cm3, ncomponents=1, kStateLiquid, temperature=20*kelvin, pressure=STP_Pressure);
    matH1->AddElement(elH1, natoms=1);
    */
}

G4VPhysicalVolume* ThermalScatteringTestDetectorConstruction::DefineVolumes()
{
    // Geometry parameters
    G4double worldSize = 1.0*m;
    G4double targetSize = 20.0*cm;
    G4double scorerDz = 1.*cm;
    G4double scorerZPos = targetSize/2. + 10.*cm + scorerDz/2.;
    
    // Get Material pointers
    G4Material* worldMaterial = G4Material::GetMaterial("G4_Galactic");
    G4Material* targetMaterial = G4Material::GetMaterial("G4_lH2");
    //G4Material* targetMaterial = G4Material::GetMaterial("TS_lH2");
    //G4Material* targetMaterial = G4Material::GetMaterial("G4_WATER");

    //
    // World
    //
    G4VSolid* solidWorld
    = new G4Box("World",                                // its name
                worldSize/2, worldSize/2, worldSize/2); // its size
    
    flogicalWorld
    = new G4LogicalVolume(
                          solidWorld,       // its solid
                          worldMaterial,    // its material
                          "World");         // its name
    
    G4VPhysicalVolume* physicalWorld
    = new G4PVPlacement(
                        0,                // no rotation
                        G4ThreeVector(),  // at (0,0,0)
                        flogicalWorld,    // its logical volume
                        "World",          // its name
                        0,                // its mother  volume
                        false,            // no boolean operation
                        0,                // copy number
                        fCheckOverlaps);  // checking overlaps
    
    // World Visualization attributes
    //
    G4VisAttributes* worldVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    worldVisAtt->SetVisibility(false);
    flogicalWorld->SetVisAttributes(worldVisAtt);
    
    //
    // Target
    //
    G4VSolid* targetS = new G4Box("Target", targetSize/2., targetSize/2., targetSize/2.);
    
    fLogicTarget
    = new G4LogicalVolume(
                          targetS,          // its solid
                          targetMaterial,   // its material
                          "Target");        // its name
    
    new G4PVPlacement(
                      0,                             // no rotation
                      G4ThreeVector(0.,0.,0.), // Position
                      fLogicTarget,                  // its logical volume
                      "Target",                      // its name
                      flogicalWorld,                 // its mother  volume
                      false,                         // no boolean operation
                      0,                             // copy number
                      fCheckOverlaps);               // checking overlaps
    
    // Target Visualization attributes
    //
    G4VisAttributes* targVisAtt = new G4VisAttributes(G4Colour(0.0,0.0,1.0));
    targVisAtt->SetVisibility(true);
    targVisAtt->SetForceSolid(true);
    fLogicTarget->SetVisAttributes(targVisAtt);
    
    
    //
    // Plane for Scoring
    //
    
    
    G4VSolid* scorerSolid
    = new G4Box("Scorer", targetSize/2., targetSize/2., scorerDz/2.);
    
    fLogicScorer
    = new G4LogicalVolume(
                          scorerSolid,       // its solid
                          worldMaterial,     // its material
                          "Scorer");         // its name
    
    new G4PVPlacement(
                      0,                 // no rotation
                      G4ThreeVector(0.,0.,scorerZPos),   // at (0,0,0)
                      fLogicScorer,      // its logical volume
                      "Scorer",          // its name
                      flogicalWorld,     // its mother  volume
                      false,             // no boolean operation
                      0,                 // copy number
                      fCheckOverlaps);   // checking overlaps
    
    // Scorer Visualization attributes
    //
    G4VisAttributes* sphereVisAtt = new G4VisAttributes(G4Colour(1.0,0.0,0.0));
    sphereVisAtt->SetVisibility(true);
    sphereVisAtt->SetForceWireframe(true);
    fLogicScorer->SetVisAttributes(sphereVisAtt);
    
    
    
    //
    // Always return the physical World
    //
    return physicalWorld;
}
