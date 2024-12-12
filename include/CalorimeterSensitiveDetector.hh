#ifndef CALORIMETERSENSITIVEDETECTOR_HH
#define CALORIMETERSENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"

#include "TupleID.hh"
#include "GeometrySize.hh"

class CalorimeterSensitiveDetector: public G4VSensitiveDetector
{
    public:
        CalorimeterSensitiveDetector(G4String name, TupleID *tupleID);
        ~CalorimeterSensitiveDetector();

        virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *history);
        virtual void Initialize(G4HCofThisEvent *event);
        virtual void EndOfEvent(G4HCofThisEvent *event);

    private:
        TupleID *tupleID;
        double right[calorimeter_number_of_segment];
        double left[calorimeter_number_of_segment];
};

#endif