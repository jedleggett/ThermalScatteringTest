#ifndef ThermalScatteringTestPhysicsList_h
#define ThermalScatteringTestPhysicsList_h 1

#include "G4VModularPhysicsList.hh"

/// Modular physics list
///

class ThermalScatteringTestPhysicsList: public G4VModularPhysicsList
{
public:
  ThermalScatteringTestPhysicsList();
  virtual ~ThermalScatteringTestPhysicsList();
  
  virtual void SetCuts();
};

#endif

