#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "Randomize.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "G4VModularPhysicsList.hh"
#include "G4PhysListFactory.hh"
#include "EventAction.hh"
#include "TrackingAction.hh"
#include "SteppingAction.hh"
#include "SteppingVerbose.hh"
#include "HistoManager.hh"
#include "PhysicsList.hh"


#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#include "G4VisExecutive.hh"
#include "G4VisManager.hh"


//#ifdef G4UI_USE
#include "G4UIExecutive.hh"
//#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv) {
  G4long seed1 = (long) time(NULL);
  G4long seed2 = (long) time(NULL) +5;
  G4cout << "argc: " << argc << G4endl;
  if (argc > 2) {
    G4String seedstr(argv[1]);
    int clpos = seedstr.find(":");
    G4cout << "Using seed string: " << seedstr << ",  position  " << clpos << G4endl;
    G4cout <<  seedstr.substr(0, clpos) << ",   " << seedstr.substr(clpos+1, seedstr.length()-clpos) << G4endl;
    seed1 = std::stol(seedstr.substr(0, clpos));
    seed2 = std::stol(seedstr.substr(clpos+1, seedstr.length()-clpos));
  }

//  G4long seeds[2] = {12345L, 5L};
  G4long seeds[2] = {seed1, seed2};
  G4cout << "Using user random seed: " <<  seeds[0] << ",  " << seeds[1]   << G4endl;

  G4Random::setTheEngine(new CLHEP::RanecuEngine());
  G4Random::setTheSeeds(seeds, 3);

  // ROOT random number set seed //
  //gRandom->SetSeed(seed);

  //choose the Random engine
//  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
  //G4long seed = (long) time(NULL);
 /* CLHEP::HepRandom::setTheSeed(seed);
  G4cout << "Seed: " << CLHEP::HepRandom::getTheSeed() << G4endl;  */

  //my Verbose output class
  G4VSteppingVerbose::SetInstance(new SteppingVerbose);

  /******RUN MANAGER************/
  G4RunManager * runManager = new G4RunManager;


  /*******DETECTOR******/
  DetectorConstruction* detector = new DetectorConstruction;
  runManager->SetUserInitialization(detector);

  G4cout << "Nlayer" << G4endl;


  detector->PrintCalorParameters();

  /*******PHYSIC LIST******/
  G4PhysListFactory factory;
  G4VModularPhysicsList* physicsList = factory.GetReferencePhysList("QGSP_BERT_EMZ");
//  G4VModularPhysicsList* physicsList = factory.GetReferencePhysList("FTFP_BERT");
  
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);
  

  TString rootfilename = "uMSDHCAL.root";
  if (argc == 5)
    {
      rootfilename = argv[4];
    }
  if (argc == 6)
    {
      rootfilename = argv[4];
    }
  if (argc == 7)
    {
      rootfilename = argv[6];
    }


  /*******HISTOGRAMS**********/
  HistoManager* histo = new HistoManager(rootfilename);

 
  /*********PRIMARY GENERATOR**************/
  PrimaryGeneratorAction* primary = new PrimaryGeneratorAction(detector,histo);
  runManager->SetUserAction(primary);


  /********ACTIONS*************/
  RunAction*      runAct = new RunAction(detector,primary,histo);
  EventAction*    evtAct = new EventAction(detector,runAct,histo);
  TrackingAction* trkAct = new TrackingAction(detector,runAct,evtAct,histo);
  SteppingAction* stpAct = new SteppingAction(detector,runAct,evtAct,histo);

  runManager->SetUserAction(runAct);
  runManager->SetUserAction(evtAct);
  runManager->SetUserAction(trkAct);
  runManager->SetUserAction(stpAct);


  /********EVENT DISPLAY********/
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  G4UImanager* UI = G4UImanager::GetUIpointer();  


  G4cout<<""<<G4endl;
  G4cout<<"INITIALISATION"<<G4endl;
  UI->ApplyCommand("/run/initialize");  




  if (argc == 1)
    {
      G4cout<<""<<G4endl;
      G4cout<<"PARTICLES"<<G4endl;
  
      UI->ApplyCommand("/gun/particle pi-");
      UI->ApplyCommand("/gun/energy 10 GeV");
      UI->ApplyCommand("/run/beamOn 1000");
    }

  if (argc == 2)
    {
      G4UIExecutive * ui = new G4UIExecutive(argc,argv);
      ui->SessionStart();
      delete ui;
    }

  if (argc == 5)
    {
      TString bfield = argv[2];
      TString nevent = argv[3];

//      TString command0 = "/random/resetEngineFrom currentRun.rndm";
      TString command1 = "/Bfield/setField " + bfield;
      TString command2 = "/run/beamOn " + nevent;

      G4cout<<"*************************"<<G4endl;
      G4cout<<"  ENERGY  uniformly distributed 1-60 GeV"<<G4endl;
      G4cout<<"  BFIELD  "<<bfield<<G4endl;
      G4cout<<"  NEVENT  "<<nevent<<G4endl;
      G4cout<<"  ROOTFILE "<<rootfilename<<G4endl;
      G4cout<<"*************************"<<G4endl;

      UI->ApplyCommand("/gun/particle pi-");
//      UI->ApplyCommand(command0);
      UI->ApplyCommand(command1);
      UI->ApplyCommand(command2);
    }// ./uMSDHCAL 87576476  0 100 uMSDHCAL_100ev.root
  if (argc == 6)
    {
      TString bfield = argv[2];
      TString nevent = argv[3];
      TString beamparticle = argv[5];

      TString command_gun = "/gun/particle " + beamparticle;
      TString command0 = "/random/resetEngineFrom currentRun.rndm";
      TString command1 = "/Bfield/setField " + bfield;
      TString command2 = "/run/beamOn " + nevent;

      G4cout<<"*************************"<<G4endl;
      G4cout<<"  ENERGY  uniformly distributed 2-40 GeV"<<G4endl;
      G4cout<<"  BFIELD  "<<bfield<<G4endl;
      G4cout<<"  NEVENT  "<<nevent<<G4endl;
      G4cout<<"  ROOTFILE "<<rootfilename<<G4endl;
      G4cout<<"*************************"<<G4endl;

      UI->ApplyCommand(command_gun);
      UI->ApplyCommand(command0);
      UI->ApplyCommand(command1);
      UI->ApplyCommand(command2);
    }
  if (argc == 7)
    {
      TString energy = argv[2];
      TString bfield = argv[3];
      TString nevent = argv[4];
      TString beamparticle = argv[5];

      TString command_gun = "/gun/particle " + beamparticle;
//      TString command0 = "/random/resetEngineFrom currentRun.rndm";
      TString command1 = "/gun/energy " + energy + " GeV";
      TString command2 = "/Bfield/setField " + bfield;
      TString command3 = "/run/beamOn " + nevent;
     
      G4cout<<"*************************"<<G4endl;
      G4cout<<"  ENERGY  "<<energy<<G4endl;
      G4cout<<"  BFIELD  "<<bfield<<G4endl;
      G4cout<<"  NEVENT  "<<nevent<<G4endl;
      G4cout<<"  ROOTFILE "<<rootfilename<<G4endl;
      G4cout<<"*************************"<<G4endl;

      UI->ApplyCommand(command_gun);
//      UI->ApplyCommand(command0);
      UI->ApplyCommand(command1);
      UI->ApplyCommand(command2);
      UI->ApplyCommand(command3);

    } // ./uMSDHCAL 87576476  0 100 uMSDHCAL_100ev.root pi-
  


  // job termination
  /*seed = CLHEP::HepRandom::getTheSeed();
  CLHEP::HepRandom::setTheSeed(seed+1);
  G4cout << "next seed = "<< seed+1 << G4endl;
  G4cout << "setting next seed = " <<CLHEP::HepRandom::getTheSeed() << G4endl;
  G4cout<<""<<G4endl;*/
  G4cout<<"JOB TERMINATION"<<G4endl;
  delete histo;
  delete runManager;
  
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

