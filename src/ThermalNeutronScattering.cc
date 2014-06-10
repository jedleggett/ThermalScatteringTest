//  ThermalNeutronScattering.cc
//
//  Created by Edward Leggett on 7/5/12.
//  Based on G4HadronElasticPhysicsHP
//  Added G4NeutronHPThermalScattering

#include "ThermalNeutronScattering.hh"

#include "G4SystemOfUnits.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4Neutron.hh"
#include "G4HadronicProcess.hh"
#include "G4HadronElastic.hh"
#include "G4NeutronHPElastic.hh"
#include "G4NeutronHPElasticData.hh"
#include "G4NeutronHPThermalScattering.hh"
#include "G4NeutronHPThermalScatteringData.hh"


ThermalNeutronScattering::ThermalNeutronScattering(G4int ver)
: G4VPhysicsConstructor("thermalNeutronScattering"), verbose(ver)
{
    if(verbose > 1) {
        G4cout << "### ThermalNeutronScattering: " << GetPhysicsName()
        << G4endl;
    }
    mainElasticBuilder = new G4HadronElasticPhysics(verbose);
}

ThermalNeutronScattering::~ThermalNeutronScattering()
{
    delete mainElasticBuilder;
}

void ThermalNeutronScattering::ConstructParticle()
{
    // gamma
    G4Gamma::Gamma();
    
    // G4cout << "G4HadronElasticPhysics::ConstructParticle" << G4endl;
    mainElasticBuilder->ConstructParticle();
}

void ThermalNeutronScattering::ConstructProcess()
{
    // Construct Elastic Scattering Processes for all Hadrons
    mainElasticBuilder->ConstructProcess();
    
    mainElasticBuilder->GetNeutronModel()->SetMinEnergy(19.5*MeV);
    
    G4HadronicProcess* hel = mainElasticBuilder->GetNeutronProcess();
    
    hel->AddDataSet(new G4NeutronHPElasticData() );
    hel->AddDataSet(new G4NeutronHPThermalScatteringData() );
    
    // Neutron HP Elasctic scattering > 4eV
    G4NeutronHPElastic* theNeutronElasticModel = new G4NeutronHPElastic();
    theNeutronElasticModel->SetMinEnergy ( 4.0*eV );
    
    // Neutron thermal Elasctic scattering < 4eV
    G4NeutronHPThermalScattering* theThermalModel = new G4NeutronHPThermalScattering();
    theThermalModel->SetMaxEnergy ( 4.0*eV );
    
    //register thermal and HP models
    hel->RegisterMe(theNeutronElasticModel);
    hel->RegisterMe(theThermalModel);
    
    if(verbose > 1) {
        G4cout << "### ThermalNeutronScattering is constructed "
        << G4endl;
    }
}
