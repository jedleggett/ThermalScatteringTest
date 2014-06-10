#include "ThermalScatteringTestRunActionMessenger.hh"
#include "ThermalScatteringTestRunAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"

ThermalScatteringTestRunActionMessenger::ThermalScatteringTestRunActionMessenger(ThermalScatteringTestRunAction* runAction)
 : G4UImessenger(),
   fRunAction(runAction),
   fDirectory(0),
   fSetFileNameCmd(0)
{
  fDirectory = new G4UIdirectory("/ThermalScatteringTest/run/");
  fDirectory->SetGuidance("run control");
   
  fSetFileNameCmd 
    = new G4UIcmdWithAString("/ThermalScatteringTest/run/setFileName",this);
  fSetFileNameCmd->SetGuidance("Set the analysis file name (default: ThermalScatteringTest");
  fSetFileNameCmd->SetParameterName("fileName",false);
  fSetFileNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

ThermalScatteringTestRunActionMessenger::~ThermalScatteringTestRunActionMessenger()
{
  delete fSetFileNameCmd;
  delete fDirectory;   
}

void ThermalScatteringTestRunActionMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if ( command == fSetFileNameCmd ) {
    fRunAction->SetFileName(newValue);
  }

}