#ifndef ThermalScatteringTestRunActionMessenger_h
#define ThermalScatteringTestRunActionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class ThermalScatteringTestRunAction;
class G4UIdirectory;
class G4UIcmdWithAString;
//class G4UIcmdWithADoubleAndUnit;


class ThermalScatteringTestRunActionMessenger: public G4UImessenger
{
  public:
    ThermalScatteringTestRunActionMessenger(ThermalScatteringTestRunAction* runAction);
    virtual ~ThermalScatteringTestRunActionMessenger();
    
    virtual void SetNewValue(G4UIcommand*, G4String);
    
  private:
    ThermalScatteringTestRunAction* 	 fRunAction;
    G4UIdirectory*           fDirectory;
    G4UIcmdWithAString*      fSetFileNameCmd;

//    G4UIcmdWithADoubleAndUnit* fSetFieldCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
