#include "CalorimeterSensitiveDetector.hh"

using namespace std;

CalorimeterSensitiveDetector::CalorimeterSensitiveDetector(G4String name, TupleID *tupleID): G4VSensitiveDetector(name)
{
    this->tupleID = tupleID;
}

CalorimeterSensitiveDetector::~CalorimeterSensitiveDetector()
{}

G4bool CalorimeterSensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *history)
{
    auto aTrack = aStep->GetTrack();
    auto detectorNumber = aTrack->GetTouchable()->GetVolume(2)->GetCopyNo();
    auto segmentNumber = aTrack->GetTouchable()->GetVolume(1)->GetCopyNo();

    if(detectorNumber == 0)
    {
        right[segmentNumber] += aStep->GetTotalEnergyDeposit();
    }
    else
        {
            left[segmentNumber] += aStep->GetTotalEnergyDeposit();
        }

    return true;
}

void CalorimeterSensitiveDetector::Initialize(G4HCofThisEvent *event)
{
    G4VSensitiveDetector::Initialize(event);

    for(int iSegment = 0; iSegment < calorimeter_number_of_segment; ++iSegment)
    {
        right[iSegment] = 0;
        left[iSegment] = 0;
    }
}

void CalorimeterSensitiveDetector::EndOfEvent(G4HCofThisEvent *event)
{
    G4VSensitiveDetector::EndOfEvent(event);

    auto analysisManager = tupleID->analysisManager;
    for(int iSegment = 0; iSegment < calorimeter_number_of_segment; ++iSegment)
    {
        analysisManager->FillNtupleDColumn(tupleID->leftCalID, iSegment, left[iSegment]);
        analysisManager->FillNtupleDColumn(tupleID->rightCalID, iSegment, right[iSegment]);
    }

    analysisManager->AddNtupleRow(tupleID->leftCalID);
    analysisManager->AddNtupleRow(tupleID->rightCalID);
}