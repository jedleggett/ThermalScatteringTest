#ifndef ThermalScatteringTestPrimaryGeneratorAction_h
#define ThermalScatteringTestPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4GeneralParticleSource;
class G4Event;

class ThermalScatteringTestPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    ThermalScatteringTestPrimaryGeneratorAction();
    ~ThermalScatteringTestPrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event* anEvent);

  private:

    G4GeneralParticleSource* particleGun;

};

#endif


