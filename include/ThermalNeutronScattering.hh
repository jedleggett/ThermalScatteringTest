//  ThermalNeutronScattering.hh
//
//  Created by Edward Leggett on 7/5/12.
//  Based on G4HadronElasticPhysicsHP
//  Added G4NeutronHPThermalScattering

#ifndef ThermalNeutronScattering_h
#define ThermalNeutronScattering_h 1

#include "globals.hh"
#include "G4VPhysicsConstructor.hh"

class G4HadronElasticPhysics;

class ThermalNeutronScattering : public G4VPhysicsConstructor
{
public: 
  
  ThermalNeutronScattering(G4int ver = 1); 
  
  virtual ~ThermalNeutronScattering();
  
  // This method will be invoked in the Construct() method. 
  // each particle type will be instantiated
  virtual void ConstructParticle();
  
  // This method will be invoked in the Construct() method.
  // each physics process will be instantiated and
  // registered to the process manager of each particle type 
  virtual void ConstructProcess();
  
private:
  ThermalNeutronScattering(ThermalNeutronScattering &);
  ThermalNeutronScattering & operator=(const ThermalNeutronScattering &right);
    
  G4int    verbose;
  G4HadronElasticPhysics* mainElasticBuilder;
};


#endif


