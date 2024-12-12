#include "TrackerSensitiveDetector.hh"

using namespace std;

TrackerSensitiveDetector::TrackerSensitiveDetector(G4String name, TupleID *tupleID): G4VSensitiveDetector(name)
{
    this->tupleID = tupleID;
}

TrackerSensitiveDetector::~TrackerSensitiveDetector()
{}

G4bool TrackerSensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *history)
{
    auto aTrack = aStep->GetTrack();
    bool isThisParticlePrimary = aTrack->GetParentID() == 0;
    bool isThisParticleNotGamma = aTrack->GetDefinition() != G4Gamma::Definition();
    if(isThisParticlePrimary && isThisParticleNotGamma)
    {
        // cout << aTrack->GetVolume()->GetCopyNo() << " ";
        // cout << aTrack->GetTouchable()->GetVolume(1)->GetName() << " ";
        // cout << aTrack->GetTouchable()->GetVolume(2)->GetName() << " ";
        // cout << aTrack->GetTouchable()->GetVolume(3)->GetName() << endl;

        int detectorNumber = aTrack->GetTouchable()->GetVolume(3)->GetCopyNo();

        TrackerData trackerData;
        trackerData.detector = detectorNumber;
        trackerData.position = aTrack->GetPosition();
        trackerData.time = aTrack->GetGlobalTime();
        trackerData.energyDeposit = aStep->GetTotalEnergyDeposit();

        data.push_back(trackerData);
    }

    return true;
}

void TrackerSensitiveDetector::Initialize(G4HCofThisEvent *event)
{
    // cout << "This is a start of " << event << endl;
    G4VSensitiveDetector::Initialize(event);

    data.clear();
}

void TrackerSensitiveDetector::EndOfEvent(G4HCofThisEvent *event)
{
    // cout << "This is the end of " << event << endl;
    G4VSensitiveDetector::EndOfEvent(event);

    auto analysisManager = tupleID->analysisManager;
    for(int i = 0; i < data.size(); i++)
    {
        auto currentData = data[i];
        int ID;

        if(currentData.detector == 0)
        {
            ID = tupleID->rightTrackID;
        }
        else
            {
                ID = tupleID->leftTrackID;
            }
        
        cout << "____________" << ID << "___________\n";
        cout << currentData.time << endl;
        analysisManager->FillNtupleDColumn(ID, 0, currentData.position.getX());
        analysisManager->FillNtupleDColumn(ID, 1, currentData.position.getY());
        analysisManager->FillNtupleDColumn(ID, 2, currentData.position.getZ());
        analysisManager->FillNtupleDColumn(ID, 3, currentData.time);
        analysisManager->AddNtupleRow(ID);
    }

    analysisManager->AddNtupleRow(tupleID->leftTrackID);
    analysisManager->AddNtupleRow(tupleID->rightTrackID);
}