#ifndef ThermalScatteringTestRunAction_h
#define ThermalScatteringTestRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "g4root.hh"

class G4Run;
class ThermalScatteringTestRunActionMessenger;
class G4Timer;


class ThermalScatteringTestRunAction : public G4UserRunAction
{
public:
    ThermalScatteringTestRunAction();
    virtual ~ThermalScatteringTestRunAction();
    
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
    
    void SetFileName(G4String name);
    
private:
    G4String fileName = "";
    
    ThermalScatteringTestRunActionMessenger*  fMessenger;   // messenger
    
    G4double nBins, ELow, EHigh;
    std::vector<G4double> Edges;
    G4AnaH1* Spectrum_Hist;
    G4AnaH1* Norm_Hist;
    G4AnaH1* Spectrum_Hist_Norm;
    
    G4Timer* timer;

};

inline void ThermalScatteringTestRunAction::SetFileName(G4String name)
{
    fileName = name;
}

#endif

