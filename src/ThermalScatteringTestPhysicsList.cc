//
//  ThermalScatteringTestPhysicsList.cc
//  ThermalScatteringTest
//
//  Created by Edward Leggett on 7/5/12.
//  Updated for Geant4.10 on 6/06/14
//
//  Registers physics for QGSP_BERT_HP and changes neutron elastic physics
//  from NeutronHP to NeutronHPThermal for energies below 4 eV
//

#include <iomanip>

#include "ThermalScatteringTestPhysicsList.hh"

#include "globals.hh"
#include "G4ios.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4IonINCLXXPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "ThermalNeutronScattering.hh"

#include "G4DataQuestionaire.hh"
#include "G4HadronPhysicsINCLXX.hh"

#include "G4WarnPLStatus.hh"

ThermalScatteringTestPhysicsList::ThermalScatteringTestPhysicsList()
: G4VModularPhysicsList(){
    
    G4DataQuestionaire it(photon, neutron);
    G4cout << "<<< Geant4 Physics List simulation engine: QGSP_INCLXX Jed"<<G4endl;
    G4cout <<G4endl;
    
    this->defaultCutValue = 0.7*mm;
    this->SetVerboseLevel(0);
    G4cout << "Verbose Level: " << verboseLevel << G4endl;
    
    // EM Physics
    this->RegisterPhysics( new G4EmStandardPhysics(verboseLevel) );
    
    // Synchroton Radiation & GN Physics
    this->RegisterPhysics( new G4EmExtraPhysics(verboseLevel) );
    
    // Decays
    this->RegisterPhysics( new G4DecayPhysics(verboseLevel) );
    
    // Hadron Elastic scattering
    this->RegisterPhysics( new ThermalNeutronScattering(verboseLevel) );
    
    // Hadron Physics (does not include elastic scattering)
    G4bool quasiElastic=true;
    G4bool neutronHP=true;
    G4bool ftfp=false;
    G4VPhysicsConstructor* hadPhys = new  G4HadronPhysicsINCLXX("Jed_HadronPhysics", quasiElastic, neutronHP , ftfp);
    hadPhys->SetVerboseLevel(verboseLevel);
    this->RegisterPhysics( hadPhys );
    
    // Stopping Physics
    this->RegisterPhysics( new G4StoppingPhysics(verboseLevel) );
    
    // Ion Physics
    this->RegisterPhysics( new G4IonINCLXXPhysics(verboseLevel));
    
}

ThermalScatteringTestPhysicsList::~ThermalScatteringTestPhysicsList()
{
}

void ThermalScatteringTestPhysicsList::SetCuts()
{
    if (this->verboseLevel >1){
        G4cout << "ThermalScatteringTestPhysicsList::SetCuts:";
    }
    //  " G4VUserPhysicsList::SetCutsWithDefault" method sets
    //   the default cut value for all particle types
    
    this->SetCutsWithDefault();
    
    //  if (this->verboseLevel >0)
    //    G4VUserPhysicsList::DumpCutValuesTable();
}
