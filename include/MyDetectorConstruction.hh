#ifndef MYDETECTORCONSTRUCTION_HH
#define MYDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4MagneticField.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4SDManager.hh"

#include "CalorimeterSensitiveDetector.hh"
#include "GeometrySize.hh"
#include "TrackerSensitiveDetector.hh"
#include "TupleID.hh"

class MyDetectorConstruction: public G4VUserDetectorConstruction
{
    public:
        MyDetectorConstruction(TupleID *tupleID);
        ~MyDetectorConstruction();

        virtual G4VPhysicalVolume *Construct();
        virtual void ConstructSDandField();

    private:
        void defineMaterials();
        void setupDetectors();

        G4Box *solidWorld;
        G4LogicalVolume *logicWorld, *detectorLogic, *magnetLogic, *plasticLogic, *siliconLogic, *CreateDetector(), *CreateCalorimeterSection(), *CreateTrackingLayer(), *CreateTrackingSection(), *CreateMagnet();
        G4PVPlacement *physWorld;

        G4Material *worldMat, *vacuum, *lead, *plastic, *silicon;

        TupleID *tupleID;
};

#endif