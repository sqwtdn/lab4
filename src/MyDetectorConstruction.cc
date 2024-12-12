#include "MyDetectorConstruction.hh"

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();

    G4bool checkOverlaps = true;

    G4double worldsize_XY = 3*m;
    G4double worldsize_Z = 5*m;

    worldMat = nist->FindOrBuildMaterial("G4_AIR");

    solidWorld = new G4Box("World", 0.5*worldsize_XY, 0.5*worldsize_XY, 0.5*worldsize_Z);
    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");
    physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, checkOverlaps);

    detectorLogic = CreateDetector();

    auto rightDetector = new G4PVPlacement(0, G4ThreeVector(0, 0, detector_length/2 + 0.1*m), detectorLogic, "rightDetector", logicWorld, false, 0);
    auto rotation = new G4RotationMatrix(CLHEP::pi, CLHEP::pi, CLHEP::pi);
    auto leftDetector = new G4PVPlacement(rotation, G4ThreeVector(0, 0, -(detector_length/2 + 0.1*m)), detectorLogic, "leftDetector", logicWorld, false, 1);

    return physWorld;
}

MyDetectorConstruction::MyDetectorConstruction(TupleID *tupleID)
{
    this->tupleID = tupleID;
    defineMaterials();
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::defineMaterials()
{
    auto nist = G4NistManager::Instance();

    vacuum = nist->FindOrBuildMaterial("G4_Galactic");
    lead = nist->FindOrBuildMaterial("G4_Pb");
    plastic = nist->FindOrBuildMaterial("G4_POLYSTYRENE");
    silicon = nist->FindOrBuildMaterial("G4_Si");
}

G4LogicalVolume *MyDetectorConstruction::CreateCalorimeterSection()
{
    auto segmentSolid = new G4Box("segment", 0.5*detector_side_size, 0.5*detector_side_size, 0.5*(calorimeter_lead_thickness + calorimeter_plastic_thickness));
    auto segmentLogic = new G4LogicalVolume(segmentSolid, vacuum, "segment");

    auto leadSolid = new G4Box("lead", 0.5*detector_side_size, 0.5*detector_side_size, 0.5*calorimeter_lead_thickness);
    auto leadLogic = new G4LogicalVolume(leadSolid, lead, "lead");
    auto leadPhys = new G4PVPlacement(0, G4ThreeVector(0, 0, -calorimeter_lead_thickness/2), leadLogic, "lead", segmentLogic, false, 0);

    auto plasticSolid = new G4Box("plastic", 0.5*detector_side_size, 0.5*detector_side_size, 0.5*calorimeter_plastic_thickness);
    plasticLogic = new G4LogicalVolume(plasticSolid, plastic, "plastic");
    auto plasticPhys = new G4PVPlacement(0, G4ThreeVector(0, 0, calorimeter_plastic_thickness/2), plasticLogic, "plastic", segmentLogic, false, 0);

    return segmentLogic;
}

G4LogicalVolume *MyDetectorConstruction::CreateDetector()
{
    auto detectorSolid = new G4Box("detector", 0.5*detector_side_size, 0.5*detector_side_size, 0.5*detector_length);
    auto detector = new G4LogicalVolume(detectorSolid, vacuum, "detector");

    auto segmentLogic = CreateCalorimeterSection();

    for(int i = 0; i < calorimeter_number_of_segment; ++i)
    {
        std::string name = "segment_";
        name += std::to_string(i);

        auto segmentPhys = new G4PVPlacement(0, G4ThreeVector(0, 0, 10*cm + (calorimeter_plastic_thickness + calorimeter_lead_thickness)*i), segmentLogic, name, detector, false, i);
    }

    auto trackingSectionLogic = CreateTrackingSection();
    auto trackingLeftPhys = new G4PVPlacement(0, G4ThreeVector(0, 0, -0.5*m), trackingSectionLogic, "leftSectionLogic", detector, false, 0);
    auto trackingRightPhys = new G4PVPlacement(0, G4ThreeVector(0, 0, -0.5*m + distance_tracking_area), trackingSectionLogic, "rightSectionLogic", detector, false, 0);

    auto magnetLogic = CreateMagnet();
    auto magnetPhys = new G4PVPlacement(0, G4ThreeVector(0., 0., -0.5*m + 0.5*distance_tracking_area), magnetLogic, "magnet", detector, false, 0);

    return detector;
}

G4LogicalVolume *MyDetectorConstruction::CreateTrackingLayer()
{
    auto layerSolid = new G4Box("layer", 0.5*detector_side_size, 0.5*detector_side_size, 0.5*tracking_thickness);
    auto layerLogic = new G4LogicalVolume(layerSolid, vacuum, "layer");

    auto siliconSolid = new G4Box("siliconBox", 0.5*tracking_cell_size, 0.5*tracking_cell_size, 0.5*tracking_thickness);
    siliconLogic = new G4LogicalVolume(siliconSolid, silicon, "siliconBox");

    for(int i = 0; i < number_of_tracking_cell; ++i)
    {
        for(int j = 0; j < number_of_tracking_cell; ++j)
        {
            double x = tracking_cell_size/2 + i*tracking_cell_size - tracking_cell_size*(number_of_tracking_cell/2);
            double y = tracking_cell_size/2 + j*tracking_cell_size - tracking_cell_size*(number_of_tracking_cell/2);

            auto siliconPhys = new G4PVPlacement(0, G4ThreeVector(x, y, 0), siliconLogic, "siliconPhys", layerLogic, false, i*number_of_tracking_cell + j);
        }
    }

    return layerLogic;
}

G4LogicalVolume *MyDetectorConstruction::CreateTrackingSection()
{
    auto sectionSolid = new G4Box("segment", 0.5*detector_side_size, 0.5*detector_side_size, 0.5*(distance_tracking_layer + 2*tracking_thickness));
    auto sectionLogic = new G4LogicalVolume(sectionSolid, vacuum, "segment");

    auto layerLogic = CreateTrackingLayer();

    auto rightLayer = new G4PVPlacement(0, G4ThreeVector(0, 0, -0.5*(distance_tracking_layer + tracking_thickness)), layerLogic, "rightLayer", sectionLogic, false, 0);
    auto leftLayer = new G4PVPlacement(0, G4ThreeVector(0, 0, 0.5*(distance_tracking_layer + tracking_thickness)), layerLogic, "leftLayer", sectionLogic, false, 0);

    return sectionLogic;
}

G4LogicalVolume *MyDetectorConstruction::CreateMagnet()
{
    auto magnetSolid = new G4Box("magnet", 0.5*detector_side_size, 0.5*detector_side_size, 1*cm);
    magnetLogic = new G4LogicalVolume(magnetSolid, vacuum, "magnet");

    return magnetLogic;
}

void MyDetectorConstruction::ConstructSDandField()
{
    G4MagneticField *magneticField = new G4UniformMagField(G4ThreeVector(0., 70*kilogauss, 0.));
    
    auto fieldManager = new G4FieldManager();
    fieldManager->SetDetectorField(magneticField);
    fieldManager->CreateChordFinder(magneticField);
    magnetLogic->SetFieldManager(fieldManager, true);
    setupDetectors();
}

void MyDetectorConstruction::setupDetectors()
{
    auto sdman = G4SDManager::GetSDMpointer();
    auto calorimeterSensDet = new CalorimeterSensitiveDetector("CalorimeterSensitiveDetector", tupleID);
    
    sdman->AddNewDetector(calorimeterSensDet);
    plasticLogic->SetSensitiveDetector(calorimeterSensDet);

    // sdman->Activate("CalorimeterSensitiveDetector", false);

    auto trackerSensDet = new TrackerSensitiveDetector("TrackerSensitiveDetector", tupleID);
    sdman->AddNewDetector(trackerSensDet);
    siliconLogic->SetSensitiveDetector(trackerSensDet);
}