#include "ThermalScatteringTestDetectorConstruction.hh"
#include "ThermalScatteringTestPhysicsList.hh"
#include "ThermalScatteringTestActionInitialization.hh"

#include "ThermalScatteringTestRunAction.hh"
#include "ThermalScatteringTestEventAction.hh"
#include "ThermalScatteringTestPrimaryGeneratorAction.hh"
#include "ThermalScatteringTestSteppingAction.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"

#include "Randomize.hh"

int main(int argc,char** argv)
{
    // Choose the Random engine
    //
    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    
    // Construct the default run manager
    //
#ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());
    runManager->SetVerboseLevel(0);
#else
    G4RunManager* runManager = new G4RunManager;
#endif
    
    // Set mandatory initialization classes
    //
    // Detector construction
    ThermalScatteringTestDetectorConstruction* detConstruction = new ThermalScatteringTestDetectorConstruction();
    runManager->SetUserInitialization(detConstruction);
    
    // Physics list
    G4VModularPhysicsList* physicsList = new ThermalScatteringTestPhysicsList();
    physicsList->SetVerboseLevel(0);
    runManager->SetUserInitialization(physicsList);
    
    // User action initialization
    runManager->SetUserInitialization(new ThermalScatteringTestActionInitialization(detConstruction));
        
    // Initialize G4 kernel
    //
    runManager->Initialize();
    
    // Get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    
    if (argc!=1) {
        // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }
    
    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    // owned and deleted by the run manager, so they should not be deleted
    // in the main() program !
    
    delete runManager;
    
    return 0;
}