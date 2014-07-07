#include "ThermalScatteringTestSteppingAction.hh"
#include "ThermalScatteringTestDetectorConstruction.hh"
#include "ThermalScatteringTestAnalysis.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"

#include "G4HadronicProcess.hh"
#include "G4SystemOfUnits.hh"

ThermalScatteringTestSteppingAction::ThermalScatteringTestSteppingAction(ThermalScatteringTestDetectorConstruction* detectorConstruction)
: G4UserSteppingAction(),
fDetConstruction(detectorConstruction)
{
}

ThermalScatteringTestSteppingAction::~ThermalScatteringTestSteppingAction()
{
}

void ThermalScatteringTestSteppingAction::UserSteppingAction(const G4Step* step)
{

#if 0
    G4double time = step->GetPreStepPoint()->GetGlobalTime();
    if (time>10000*s) {
        step->GetTrack()->SetTrackStatus(fStopAndKill);
        G4cout << "******Here*****" << G4endl;
        step->GetTrack()->GetDynamicParticle()->DumpInfo();
    }
#endif
    
    // Kill tracks at first step for analyzing input
#if 0
    step->GetTrack()->SetTrackStatus(fStopAndKill);
    return;
#endif
    
    //Turn all data collection On/Off
#if 1
    
    
    // Get the current track
    G4Track* track = step->GetTrack();
    if (!track) {
        G4cout << "***** No Track ***" << G4endl;
        return;
    }
    
    G4double PDG = track->GetParticleDefinition()->GetPDGEncoding();
    
    if (PDG==2112)
    {
        
        // Get step points at begining and end of step
        G4StepPoint* Prepoint = NULL;
        Prepoint = step->GetPreStepPoint();
        G4StepPoint* Postpoint = NULL;
        Postpoint = step->GetPostStepPoint();
        const G4VProcess* stepDefinedProcess = NULL;

        if (Postpoint) {
            // Get the process that limited the step
            stepDefinedProcess = Postpoint->GetProcessDefinedStep();
        }
        
        // Get type and subtype of process
        G4ProcessType stepProcessType = fNotDefined;
        G4int stepProcessSubType = 0;
        
        if(stepDefinedProcess)
        {stepProcessType = stepDefinedProcess->GetProcessType();
            stepProcessSubType = stepDefinedProcess->GetProcessSubType();}
        
        // Get the volume in which the step was taken
        G4LogicalVolume * StepVolume = step->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume();
        
        if (stepProcessType==fTransportation && StepVolume == fDetConstruction->GetScorerLV())
        {
            G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
            //analysisManager->FillNtupleDColumn(0, track->GetKineticEnergy());
            //analysisManager->AddNtupleRow();
            
            analysisManager->FillH1(0, track->GetKineticEnergy());

        }
        
    }
    
#endif
    
    
}

