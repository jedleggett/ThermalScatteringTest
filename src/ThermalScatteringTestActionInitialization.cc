#include "ThermalScatteringTestActionInitialization.hh"
#include "ThermalScatteringTestPrimaryGeneratorAction.hh"
#include "ThermalScatteringTestRunAction.hh"
#include "ThermalScatteringTestEventAction.hh"
#include "ThermalScatteringTestSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ThermalScatteringTestActionInitialization::ThermalScatteringTestActionInitialization(ThermalScatteringTestDetectorConstruction* det)
: G4VUserActionInitialization(), detector(det)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ThermalScatteringTestActionInitialization::~ThermalScatteringTestActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ThermalScatteringTestActionInitialization::BuildForMaster() const
{
  SetUserAction(new ThermalScatteringTestRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ThermalScatteringTestActionInitialization::Build() const
{
  SetUserAction(new ThermalScatteringTestPrimaryGeneratorAction);
  SetUserAction(new ThermalScatteringTestRunAction);
  
  SetUserAction(new ThermalScatteringTestEventAction);
  
  SetUserAction(new ThermalScatteringTestSteppingAction(detector));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
