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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
namespace {
    void PrintUsage() {
        G4cerr << " Usage: " << G4endl;
        G4cerr << " LightTest [-m macro ] [-u UIsession] [-t nThreads] [-r seed] "
        << G4endl;
        G4cerr << "   note: -t option is available only for multi-threaded mode."
        << G4endl;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


int main(int argc,char** argv)
{
    // Evaluate arguments
    //
    if ( argc > 9 ) {
        PrintUsage();
        return 1;
    }
    
    G4String macro;
    G4String session;
#ifdef G4MULTITHREADED
    G4int nThreads = 0;
#endif
    
    G4long myseed = 345354;
    for ( G4int i=1; i<argc; i=i+2 ) {
        if      ( G4String(argv[i]) == "-m" ) macro   = argv[i+1];
        else if ( G4String(argv[i]) == "-u" ) session = argv[i+1];
        else if ( G4String(argv[i]) == "-r" ) myseed  = atoi(argv[i+1]);
#ifdef G4MULTITHREADED
        else if ( G4String(argv[i]) == "-t" ) {
            nThreads = G4UIcommand::ConvertToInt(argv[i+1]);
        }
#endif
        else {
            PrintUsage();
            return 1;
        }
    }
    
    // Choose the Random engine
    //
    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    
    // Construct the default run manager
    //
#ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    if ( nThreads > 0 ) runManager->SetNumberOfThreads(nThreads);
    //runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());
    runManager->SetVerboseLevel(0);
#else
    G4RunManager* runManager = new G4RunManager;
#endif
    
    // Seed the random number generator manually
    G4Random::setTheSeed(myseed);
    
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
    
    if ( macro.size() ) {
        // Batch mode
        G4String command = "/control/execute ";
        UImanager->ApplyCommand(command+macro);
    }
    
    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    // owned and deleted by the run manager, so they should not be deleted
    // in the main() program !
    
    delete runManager;
    
    return 0;
}