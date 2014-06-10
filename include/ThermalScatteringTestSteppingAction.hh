#ifndef ThermalScatteringTestSteppingAction_h
#define ThermalScatteringTestSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4ProcessType.hh"
#include "G4Types.hh"

class ThermalScatteringTestDetectorConstruction;

class ThermalScatteringTestSteppingAction : public G4UserSteppingAction
{
public:
  ThermalScatteringTestSteppingAction( ThermalScatteringTestDetectorConstruction* detectorConstruction);
  virtual ~ThermalScatteringTestSteppingAction();

  virtual void UserSteppingAction(const G4Step* step);
        
private:

  ThermalScatteringTestDetectorConstruction* fDetConstruction;
};

#endif
