#ifndef ThermalScatteringTestDetectorConstruction_h
#define ThermalScatteringTestDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4LogicalVolume;

class ThermalScatteringTestDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    ThermalScatteringTestDetectorConstruction();
    virtual ~ThermalScatteringTestDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    
    G4LogicalVolume* GetWorldLV();
    G4LogicalVolume* GetScorerLV();
    G4LogicalVolume* GetTargetLV();
    
     
  private:
    // Define methods
    //

    // Call all other Define functions here 
    G4VPhysicalVolume* DefineVolumes();

    // *** Materials
    void DefineMaterials();

    // data members
    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
  
    // World Logical Volume
    G4LogicalVolume* flogicalWorld;
    G4LogicalVolume* fLogicTarget;
    G4LogicalVolume* fLogicScorer;
};

inline G4LogicalVolume* ThermalScatteringTestDetectorConstruction::GetScorerLV()
{
    return fLogicScorer;
}

inline G4LogicalVolume* ThermalScatteringTestDetectorConstruction::GetTargetLV()
{
    return fLogicTarget;
}

inline G4LogicalVolume* ThermalScatteringTestDetectorConstruction::GetWorldLV()
{
    return flogicalWorld;
}

#endif

