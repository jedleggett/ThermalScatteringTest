#include "ThermalScatteringTestPrimaryGeneratorAction.hh"
#include "ThermalScatteringTestEventAction.hh"
#include "ThermalScatteringTestAnalysis.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

ThermalScatteringTestPrimaryGeneratorAction::ThermalScatteringTestPrimaryGeneratorAction()
{
   particleGun = new G4GeneralParticleSource();
}

ThermalScatteringTestPrimaryGeneratorAction::~ThermalScatteringTestPrimaryGeneratorAction()
{
  delete particleGun;
}

void ThermalScatteringTestPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  particleGun->GeneratePrimaryVertex(anEvent);
    G4double primaryX, primaryZ;
    primaryX = anEvent->GetPrimaryVertex()->GetX0();
    primaryZ = anEvent->GetPrimaryVertex()->GetZ0();
    
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    //G4cout << "PrimaryX: " << primaryX/cm << "  PrimaryZ: " << primaryZ/cm << G4endl;
    analysisManager->FillH2(0, primaryX/cm, primaryZ/cm);
}
