#include "ThermalScatteringTestRunAction.hh"
#include "ThermalScatteringTestRunActionMessenger.hh"
#include "ThermalScatteringTestAnalysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4Timer.hh"


ThermalScatteringTestRunAction::ThermalScatteringTestRunAction()
: G4UserRunAction()
{
    fMessenger = new ThermalScatteringTestRunActionMessenger(this);

    if (IsMaster()) {
        timer = new G4Timer();
    }
    
    ELow = 1.0e-10;
    EHigh = 10.;
    nBins = 220;

    G4double dlog = (std::log10(EHigh) - std::log10(ELow))/nBins;
    G4double dx = std::pow(10, dlog);
    G4double binValue = ELow;

    // Set Bin Edges for Logarithmically Binned Histogram
    while ( G4int(Edges.size()) <= nBins ) {
        Edges.push_back(binValue);
        binValue *= dx;
    }    
    
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    G4int HistID;
    
    HistID = analysisManager->CreateH1("PlaneEnergySpectrum", "Energy Spectrum of Neutrons Through Plane Above Target", Edges, "MeV");
    Spectrum_Hist = analysisManager->GetH1(HistID);
    
    HistID = analysisManager->CreateH1("normalization", "Normalization for Energy Spectrum", Edges, "MeV");
    Norm_Hist = analysisManager->GetH1(HistID);
    
    HistID = analysisManager->CreateH1("PlaneEnergySpectrumNorm", "Energy Spectrum of Neutrons Through Plane Above Target", Edges, "MeV");
    Spectrum_Hist_Norm = analysisManager->GetH1(HistID);
    
    HistID = analysisManager->CreateH2("primaryPos", "Position of Primary Neutrons", 300, -15., 15., 300, -15., 15.);
    
    // Set correct normalization for energy spectrum
    G4double HighEdge, LowEdge, Middle, Width;
    std::vector<G4double>::const_iterator it;
    for (it = Edges.begin(); it != (Edges.end()-1); it++ )
    {
        LowEdge = *it;
        HighEdge = *(it+1);
        Width = HighEdge - LowEdge;
        Middle = (HighEdge + LowEdge)/2.;
        Norm_Hist->fill(Middle, Width);
    }
    

}

ThermalScatteringTestRunAction::~ThermalScatteringTestRunAction()
{
    delete fMessenger;
    delete G4AnalysisManager::Instance();
    delete timer;

}

void ThermalScatteringTestRunAction::BeginOfRunAction(const G4Run* run)
{
    
    if (IsMaster()){
        G4cout << "### Run " << run->GetRunID() << " start." << G4endl;
        timer->Start();
    }
    
    //inform the runManager to save random number seed
    G4RunManager::GetRunManager()->SetRandomNumberStore(false);
    
    // Open an output file
    //
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    if(fileName==""){fileName = "ThermalScatteringTest";}
    analysisManager->OpenFile(fileName);
    
}

void ThermalScatteringTestRunAction::EndOfRunAction(const G4Run* aRun)
{
    
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    //Output filename
    fileName = analysisManager->GetFileName();
    G4cout << "Filename = " << fileName << G4endl;
    
    // Make a Copy of Energy Spectrum Histogram and set correct Normalization
    tools::histo::histo_data<double, unsigned int, double> Spectrum_Data = Spectrum_Hist->get_histo_data();
    Spectrum_Hist_Norm->copy_from_data(Spectrum_Data );
    
    Spectrum_Hist_Norm->divide((const tools::histo::h1<double, unsigned int, double, double>)*Norm_Hist);
    
    // save histograms
    //
    analysisManager->Write();
    analysisManager->CloseFile();
    
    if (IsMaster()){
        timer->Stop();
        G4cout << "*****G4 RUN TIMER*****" << G4endl;
        G4cout << *timer << G4endl;

    }
    

}

