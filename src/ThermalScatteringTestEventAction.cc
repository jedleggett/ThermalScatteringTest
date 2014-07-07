#include "ThermalScatteringTestEventAction.hh"
#include "ThermalScatteringTestRunAction.hh"
#include "ThermalScatteringTestAnalysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

ThermalScatteringTestEventAction::ThermalScatteringTestEventAction()
 : G4UserEventAction(),
fPrintModulo(1000)
{
}

ThermalScatteringTestEventAction::~ThermalScatteringTestEventAction()
{
}

void ThermalScatteringTestEventAction::BeginOfEventAction(const G4Event* evt)
{  
  G4int eventID = evt->GetEventID();
  if ( eventID % fPrintModulo == 0 )  {
    G4cout << "\n---> Begin of event: " << eventID << G4endl;
  }
    
    //if (eventID==924436) {
    if (eventID==810985) {
        G4cout << "This Guy!!!" << G4endl;
    }
}

void ThermalScatteringTestEventAction::EndOfEventAction(const G4Event* evt)
{
}

