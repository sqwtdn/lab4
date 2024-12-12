#include "MyRunAction.hh"

MyRunAction::MyRunAction(TupleID *tupleID): tupleID(tupleID)
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run *aRun)
{
    G4UserRunAction::BeginOfRunAction(aRun);
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile("PiDecay.root");
    tupleID->analysisManager = analysisManager;

    int leftCalID = analysisManager->CreateNtuple("LC", "Left Calorimeter");
    for(int iSegment = 0; iSegment < calorimeter_number_of_segment; ++iSegment)
    {
        analysisManager->CreateNtupleDColumn("LC_" + std::to_string(iSegment));
    }
    analysisManager->FinishNtuple(leftCalID);

    int rightCalID = analysisManager->CreateNtuple("RC", "Right Calorimeter");
    for(int iSegment = 0; iSegment < calorimeter_number_of_segment; ++iSegment)
    {
        analysisManager->CreateNtupleDColumn("RC_" + std::to_string(iSegment));
    }
    analysisManager->FinishNtuple(rightCalID);

    tupleID->leftCalID = leftCalID;
    tupleID->rightCalID = rightCalID;

    int leftTrackID = analysisManager->CreateNtuple("LT", "Left tracking detector");
    analysisManager->CreateNtupleDColumn("xL");
    analysisManager->CreateNtupleDColumn("yL");
    analysisManager->CreateNtupleDColumn("zL");
    analysisManager->CreateNtupleDColumn("tL");
    analysisManager->FinishNtuple(leftTrackID);

    int rightTrackID = analysisManager->CreateNtuple("RT", "Right tracking detector");
    analysisManager->CreateNtupleDColumn("xR");
    analysisManager->CreateNtupleDColumn("yR");
    analysisManager->CreateNtupleDColumn("zR");
    analysisManager->CreateNtupleDColumn("tR");
    analysisManager->FinishNtuple(rightTrackID);

    tupleID->leftTrackID = leftTrackID;
    tupleID->rightTrackID = rightTrackID;
}

void MyRunAction::EndOfRunAction(const G4Run *aRun)
{
    G4UserRunAction::EndOfRunAction(aRun);
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    analysisManager->Write();
    analysisManager->CloseFile(true);
}