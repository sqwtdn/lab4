#ifndef TRACKERSENSITIVEDETECTOR_HH
#define TRACKERSENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4Gamma.hh"

#include "TupleID.hh"

struct TrackerData
{
    int detector;
    double time, energyDeposit;
    G4ThreeVector position;
};

class TrackerSensitiveDetector: public G4VSensitiveDetector
{
    public:
        TrackerSensitiveDetector(G4String name, TupleID *tupleID);
        ~TrackerSensitiveDetector();

        virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *history);
        virtual void Initialize(G4HCofThisEvent *event);
        virtual void EndOfEvent(G4HCofThisEvent *event);

    private:
        std::vector<TrackerData> data;
        TupleID *tupleID;
};
#endif