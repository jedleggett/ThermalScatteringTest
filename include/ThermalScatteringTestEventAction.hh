#ifndef ThermalScatteringTestEventAction_h
#define ThermalScatteringTestEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

class ThermalScatteringTestEventAction : public G4UserEventAction
{
public:
    ThermalScatteringTestEventAction();
    virtual ~ThermalScatteringTestEventAction();
    
    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void  EndOfEventAction(const G4Event* event);
    
private:
    
    G4int fPrintModulo;
    
};

#endif


