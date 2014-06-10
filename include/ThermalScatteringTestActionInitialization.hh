#ifndef ThermalScatteringTestActionInitialization_h
#define ThermalScatteringTestActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class ThermalScatteringTestDetectorConstruction;

class ThermalScatteringTestActionInitialization : public G4VUserActionInitialization
{
  public:
    ThermalScatteringTestActionInitialization(ThermalScatteringTestDetectorConstruction* det);
    virtual ~ThermalScatteringTestActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
    
private:
    ThermalScatteringTestDetectorConstruction* detector;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
