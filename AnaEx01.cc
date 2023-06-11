//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file analysis/AnaEx01/AnaEx01.cc
/// \brief Main program of the analysis/AnaEx01 example
//
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

#include "G4RunManagerFactory.hh"

#include "G4UImanager.hh"

#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"

#include "G4ScoringManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "G4HadronPhysicsQGSP_BIC.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  G4String physListName;
  
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Construct the default run manager
  //
  auto* runManager = G4RunManagerFactory::CreateRunManager();
  G4int nThreads = 1;
  runManager->SetNumberOfThreads(nThreads);


  // Physics list factory
  G4PhysListFactory factory;
  G4VModularPhysicsList* physList = nullptr;
  //  runManager->SetUserInitialization(new FTFP_BERT);

  //use cases - reference physics lists
  //https://geant4.web.cern.ch/node/302
  //EM physics lists
  //https://geant4.web.cern.ch/node/146
  physListName = "FTFP_BERT";
  // Check if the name is known to the factory
  if ( physListName.size() &&  (! factory.IsReferencePhysList(physListName) ) ) {
    G4cerr << "Physics list " << physListName
           << " is not available in PhysListFactory." << G4endl;
    physListName.clear();
  }
   // Reference PhysicsList via its name
  physList = factory.GetReferencePhysList(physListName);

  // Set mandatory initialization classes
  //
  G4ScoringManager* scoringManager =  G4ScoringManager::GetScoringManager();
  DetectorConstruction* detector = new DetectorConstruction;
  runManager->SetUserInitialization(detector);
  runManager->SetUserInitialization(physList);

  // Set user action classes
  //
  runManager->SetUserInitialization(new ActionInitialization(detector));

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  //
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if ( ! ui ) {
    // batch mode
    UImanager->ApplyCommand("/run/initialize");
    UImanager->ApplyCommand("/run/verbose 2");
    UImanager->ApplyCommand("/event/verbose 2");
    UImanager->ApplyCommand("/track/verbose 2");
	UImanager->ApplyCommand("/score/create/boxMesh boxMesh_1");
    UImanager->ApplyCommand("/score/mesh/boxSize 15. 15. 15. cm");
    UImanager->ApplyCommand("/score/mesh/nBin 500 1 1");
    UImanager->ApplyCommand("/score/quantity/energyDeposit doseScorer");
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
	
	
	G4String str = "/score/dumpQuantityToFile boxMesh_1 doseScorer ";
	str.append(std::to_string(150)).append("-MEV-");
	str.append(std::to_string(50)).append("-EVTS.txt");
	UImanager->ApplyCommand(str);
    UImanager->ApplyCommand(str);
	UImanager->ApplyCommand("/score/close");
  }
  else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  delete visManager;
  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
