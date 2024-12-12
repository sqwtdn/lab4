#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "QGSP_BERT.hh"

#include "MyDetectorConstruction.hh"
#include "MyPrimaryGenerator.hh"
#include "MyRunAction.hh"

int main(int argc, char** argv)
{
    G4RunManager *runManager = new G4RunManager();

    auto *tupleID = new TupleID;

    runManager->SetUserInitialization(new MyDetectorConstruction(tupleID));
    runManager->SetUserInitialization(new QGSP_BERT());
    runManager->SetUserAction(new MyPrimaryGenerator(true));
    runManager->SetUserAction(new MyRunAction(tupleID));
    runManager->Initialize();

    G4UIExecutive *ui = 0;

    if(argc == 1)
    {
        ui = new G4UIExecutive(argc, argv);
    }

    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialise();

    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    if(ui)
    {
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
    }
    else
        {
            G4String command = "/control/execute ";
            G4String fileName = argv[1];
            UImanager->ApplyCommand(command+fileName);
        }

    return 0;
}