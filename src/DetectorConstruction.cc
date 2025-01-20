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
// $Id: DetectorConstruction.cc,v 1.23 2009/03/04 18:49:17 maire Exp $
// GEANT4 tag $Name: geant4-09-03 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "Field.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4UniformMagField.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4UImanager.hh"
#include "G4UnitsTable.hh"
#include <iomanip>

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
:solidWorld(0),logicWorld(0),physiWorld(0)
{


  /***GEOMETRY****/

  //world
  worldSize = 20*m;

  //absorber
  absorSize = 100*cm;
  //absorThick = 20*mm;
  absorThick = 20*mm;

  //pcb
  pcbSize = 100*cm;
  pcbThick = 1.2*mm;

  //airgap 
  airgapSize = 100*cm;
  airgapThick = 1*mm;

  //sensor (gas)
  sensorSize = 100*cm;
  sensorThick = 3*mm;

  // **** Micromegas ***
  //airgap2 
  airgap2Size = 100*cm;
  airgap2Thick = 0.5*mm;

  //cover uM 
  coverSize = 100*cm;
  coverThick = 2.0*mm;

  // **** RPWELL ***
      
  //THGEM 
  thgemSize = 100*cm;
  thgemThick = 0.8*mm;

  //Resistive Plate
  rpSize = 100*cm;
  rpThick = 0.7*mm;

  //mask 
  maskSize = 100*cm;
  maskThick = 4*mm;
  //maskThick = 3*mm;
  
  //cathode 
  cathodeSize = 100*cm;
  cathodeThick = 3*mm;
  //cathodeThick = 1*mm;

  //electrode
  electrodeSize = 100*cm;
  electrodeThick = 0.04*mm;

  G4double rpwellThick = electrodeThick + cathodeThick + electrodeThick + sensorThick + electrodeThick + thgemThick + rpThick + pcbThick + maskThick;
  G4double mmThick = coverThick + sensorThick + pcbThick + airgap2Thick + coverThick;
  //caloPitch = mmThick + airgapThick + absorThick + airgapThick;
  caloPitch = rpwellThick + airgapThick + absorThick + airgapThick;


  /*****ELEMENTS & MOLECULES******/

  G4Material * g4_c = G4NistManager::Instance()->FindOrBuildMaterial("G4_C");
  G4Material * g4_h = G4NistManager::Instance()->FindOrBuildMaterial("G4_H");
  G4Material * g4_f = G4NistManager::Instance()->FindOrBuildMaterial("G4_F");
  G4Material * g4_s = G4NistManager::Instance()->FindOrBuildMaterial("G4_S");
  G4Material * g4_o = G4NistManager::Instance()->FindOrBuildMaterial("G4_O");
  G4Material * g4_si = G4NistManager::Instance()->FindOrBuildMaterial("G4_Si");
  G4Material * g4_k = G4NistManager::Instance()->FindOrBuildMaterial("G4_K");
  G4Material * g4_na = G4NistManager::Instance()->FindOrBuildMaterial("G4_Na");
  G4Material * g4_cu = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");
  G4Material * g4_ni = G4NistManager::Instance()->FindOrBuildMaterial("G4_Ni");
  G4Material * g4_cr = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cr");
  G4Material * g4_fe = G4NistManager::Instance()->FindOrBuildMaterial("G4_Fe");
  
  G4Material * g4_co2 = G4NistManager::Instance()->FindOrBuildMaterial("G4_CARBON_DIOXIDE");
  G4Material * g4_sio2 = G4NistManager::Instance()->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
  G4Material * g4_na2o = G4NistManager::Instance()->FindOrBuildMaterial("G4_SODIUM_MONOXIDE");
  G4Material * g4_b2o3 = G4NistManager::Instance()->FindOrBuildMaterial("G4_BORON_OXIDE");


  //steel
  G4Material * Steel = new G4Material("Steel",7.93*g/cm3,3);
  Steel->AddMaterial(g4_ni,0.11);
  Steel->AddMaterial(g4_cr,0.18);
  Steel->AddMaterial(g4_fe,0.71);


  //MM gas
  G4Material * ar_7co2_gas = new G4Material("ar_7co2_gas",0.001678*g/cm3,2);
  //Argon
  G4Material* g4_ar = new G4Material("ArgonGas",18,39.948*g/mole,0.00166201*g/cm3,kStateGas, 273.15*kelvin,1*atmosphere);
  //gas
  ar_7co2_gas->AddMaterial(g4_ar,0.93);
  ar_7co2_gas->AddMaterial(g4_co2,0.07);
 

  //PCB = epoxy + glass fiber
  G4Material * Pcb = new G4Material("Pcb",1.9*g/cm3,7);
  //epoxy
  Pcb->AddMaterial(g4_o,3.492e-02*0.9);
  Pcb->AddMaterial(g4_c,2.0284e-01*0.9);
  Pcb->AddMaterial(g4_h,2.0284e-01*0.9);
  //copper routing
  Pcb->AddMaterial(g4_cu,0.1);
  //glass fiber
  Pcb->AddMaterial(g4_sio2,4.53e-01*0.9);
  Pcb->AddMaterial(g4_na2o,3.36e-02*0.9);
  Pcb->AddMaterial(g4_b2o3,7.28e-02*0.9);

  //FR4 = epoxy + glass fiber
  G4Material * FR4 = new G4Material("FR4",1.9*g/cm3,6);
  //epoxy
  FR4->AddMaterial(g4_o,3.492e-02);
  FR4->AddMaterial(g4_c,2.0284e-01);
  FR4->AddMaterial(g4_h,2.0284e-01);
  //glass fiber
  FR4->AddMaterial(g4_sio2,4.53e-01);
  FR4->AddMaterial(g4_na2o,3.36e-02);
  FR4->AddMaterial(g4_b2o3,7.28e-02);

  //Mask = epoxy
  G4Material * Mask = new G4Material("Mask",1.9*g/cm3,3);
  //epoxy
  Mask->AddMaterial(g4_o,7.9256e-2);
  Mask->AddMaterial(g4_c,4.604e-1);
  Mask->AddMaterial(g4_h,4.604e-1);

  // Low resistivity silicate glass (SiO2)
  G4Element* elSi = new G4Element("Silicon" ,"Si" , 14., 28.09*g/mole);
  G4Element* elO = new G4Element("Oxygen" ,"O" , 8., 16.00*g/mole);

  G4Material* SiO2 = new G4Material("SiO2" , 2.2*g/cm3, 2);
  SiO2->AddElement(elSi, 1);
  SiO2->AddElement(elO, 2);


  /***MATERIALS****/

  //world
  new G4Material("Galactic",1,1.008*g/mole,universe_mean_density,kStateGas,2.73*kelvin,3.e-18*pascal);

  //world
  worldMaterial = G4NistManager::Instance()->FindOrBuildMaterial("Galactic");
  if (worldMaterial == NULL ){exit(-1);} 

  //absorber
  absorMaterial = G4NistManager::Instance()->FindOrBuildMaterial("Steel");
  if (absorMaterial == NULL ){exit(-1);} 

  //pcb
  pcbMaterial = G4NistManager::Instance()->FindOrBuildMaterial("Pcb");
  if (pcbMaterial == NULL ){exit(-1);} 

  //sensor 
  sensorMaterial = G4NistManager::Instance()->FindOrBuildMaterial("ar_7co2_gas");
  if (sensorMaterial == NULL ){exit(-1);} 

  //mask MM
  maskMaterial = G4NistManager::Instance()->FindOrBuildMaterial("Mask");
  if (maskMaterial == NULL ){exit(-1);} 

  //cover MM
  coverMaterial = G4NistManager::Instance()->FindOrBuildMaterial("Steel");
  if (coverMaterial == NULL ){exit(-1);} 

  //airgap MM
  airgapMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
  if (airgapMaterial == NULL ){exit(-1);} 

  //RP glass
  rpMaterial = G4NistManager::Instance()->FindOrBuildMaterial("SiO2");
  if (rpMaterial == NULL ){exit(-1);} 

  //THGEM
  thgemMaterial = G4NistManager::Instance()->FindOrBuildMaterial("FR4");
  if (thgemMaterial == NULL ){exit(-1);}

  //cathode
  cathodeMaterial = G4NistManager::Instance()->FindOrBuildMaterial("FR4");
  if (cathodeMaterial == NULL ){exit(-1);} 

  //electrode
  electrodeMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");
  if (electrodeMaterial == NULL ){exit(-1);} 


  // create commands for interactive definition of the calorimeter
  detectorMessenger = new DetectorMessenger(this);



  //MAGNETIC FIELD//

  static G4bool fieldIsInitialized = false;
  if(!fieldIsInitialized)
  {
  //  Field* myField = new Field(this);
    Field* myField = new Field();
    myField->SetBfield(0.,1.,0.);
    G4FieldManager* fieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
    fieldMgr->SetDetectorField(myField);
    fieldMgr->CreateChordFinder(myField);
    fieldIsInitialized = true;
  }

}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
  delete detectorMessenger;
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructCalorimeter();
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::PrintCalorParameters()
{
  G4cout << "\n-------------------------------------------------------------";

  G4cout << "\n ----> World       material: " << worldMaterial << G4endl;
  G4cout << "\n ----> Absorber    material: " << absorMaterial << G4endl;
  G4cout << "\n ----> PCB         material: " << pcbMaterial << G4endl;
  G4cout << "\n ----> Sensor      material: " << sensorMaterial << G4endl;
  G4cout << "\n-------------------------------------------------------------\n";
}






//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::ConstructCalorimeter()
{

  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();



  // World
  solidWorld = new G4Box("World",worldSize/2,worldSize/2,worldSize/2);
  logicWorld = new G4LogicalVolume(solidWorld,worldMaterial,"World");
  physiWorld = new G4PVPlacement(0,			//no rotation
  				 G4ThreeVector(),	//at (0,0,0)
                                 logicWorld,		//its logical volume
                                 "World",		//its name
                                 0,			//its mother  volume
                                 false,			//no boolean operation
                                 0);			//copy number


  G4cout << "Nlayer = " << numOfLayer << G4endl;



  // Absorber, PCB and sensor
  //uM Chambers

  for (G4int k = 0 ; k < (numOfLayer - numOfLayer_RPWELL) ; k++)
    {

      G4cout <<""<< G4endl;
      G4cout << "Layer " << k+1 << G4endl;

      //ABSORBER

      G4double zposAbsor = caloPitch * k + absorThick/2;

      solidAbsor[k] = new G4Box("Absorber",absorSize/2,absorSize/2,absorThick/2);
      logicAbsor[k] = new G4LogicalVolume(solidAbsor[k],absorMaterial,"Absorber");
      physiAbsor[k] = new G4PVPlacement(0,			//no rotation
					G4ThreeVector(0,0,zposAbsor),	//at (0,0,0)
					logicAbsor[k],		//its logical volume
					"Absorber",		//its name
					logicWorld,		//its mother  volume
					false,			//no boolean operation
					k);			//copy number

      G4cout << "  zabsorber   = " << G4BestUnit(zposAbsor-absorThick/2,"Length") << G4endl;


      //CHAMBERS

      //airgap
      G4double zposairgap1 = caloPitch * k + absorThick + airgapThick/2;
      solidairgap1[k] = new G4Box("airgap",airgapSize/2,airgapSize/2,airgapThick/2);
      logicairgap1[k] = new G4LogicalVolume(solidairgap1[k],airgapMaterial,"airgap");
      physiairgap1[k] = new G4PVPlacement(0,			//no rotation
					     G4ThreeVector(0,0,zposairgap1),	//at (0,0,0)
					     logicairgap1[k],	//its logical volume
					     "airgap",		//its name
					     logicWorld,		//its mother  volume
					     false,		        //no boolean operation
					     k);			//copy number
      G4cout << "  zairgap1  = " << G4BestUnit(zposairgap1-airgapThick/2.,"Length") << G4endl;
	  
      //cover
      G4double zposcover1 = caloPitch * k + absorThick + airgapThick + coverThick/2;
      solidcover[k] = new G4Box("cover",coverSize/2,coverSize/2,coverThick/2);
      logiccover[k] = new G4LogicalVolume(solidcover[k],coverMaterial,"cover");
      physicover[k] = new G4PVPlacement(0,			//no rotation
					    G4ThreeVector(0,0,zposcover1),	//at (0,0,0)
					    logiccover[k],	//its logical volume
					    "cover",		//its name
					    logicWorld,		//its mother  volume
					    false,		        //no boolean operation
					    k);			//copy number

      G4cout << "  zcover1   = " << G4BestUnit(zposcover1-coverThick/2.,"Length") << G4endl;
      
      //airgap2
      G4double zposairgap2 = caloPitch * k + absorThick + airgapThick + coverThick + airgap2Thick/2;
      solidairgap2[k] = new G4Box("airgap",airgap2Size/2,airgap2Size/2,airgap2Thick/2);
      logicairgap2[k] = new G4LogicalVolume(solidairgap2[k],airgapMaterial,"airgap");
      physiairgap2[k] = new G4PVPlacement(0,			//no rotation
					     G4ThreeVector(0,0,zposairgap2),	//at (0,0,0)
					     logicairgap2[k],	//its logical volume
					     "airgap2",		//its name
					     logicWorld,		//its mother  volume
					     false,		        //no boolean operation
					     k);			//copy number
      G4cout << "  zairgap2  = " << G4BestUnit(zposairgap2-airgap2Thick/2.,"Length") << G4endl;

      //pcb
      G4double zpospcb = caloPitch * k + absorThick + airgapThick + coverThick + airgap2Thick + pcbThick/2;
      solidpcb[k] = new G4Box("pcb",pcbSize/2,pcbSize/2,pcbThick/2);
      logicpcb[k] = new G4LogicalVolume(solidpcb[k],pcbMaterial,"pcb");
      physipcb[k] = new G4PVPlacement(0,			//no rotation
					G4ThreeVector(0,0,zpospcb),	//at (0,0,0)
					logicpcb[k],	//its logical volume
					"pcb",		//its name
					logicWorld,		//its mother  volume
					false,		        //no boolean operation
					k);			//copy number
      
      G4cout << "  zpcb      = " << G4BestUnit(zpospcb-pcbThick/2.,"Length") << G4endl;
      
      //sensor
      G4double zpossensor = caloPitch * k + absorThick + airgapThick + coverThick + airgap2Thick + pcbThick + sensorThick/2;
      solidsensor[k] = new G4Box("sensor",sensorSize/2,sensorSize/2,sensorThick/2);
      logicsensor[k] = new G4LogicalVolume(solidsensor[k],sensorMaterial,"sensor");
      physisensor[k] = new G4PVPlacement(0,			//no rotation
					     G4ThreeVector(0,0,zpossensor),	//at (0,0,0)
					     logicsensor[k],	//its logical volume
					     "sensor",		//its name
					     logicWorld,		//its mother  volume
					     false,		        //no boolean operation
					     k);			//copy number
      
      G4cout << "  zsensor   = " << G4BestUnit(zpossensor-sensorThick/2.,"Length") << G4endl;
      
      //cover
      G4double zposcover2 = caloPitch * k + absorThick + airgapThick + coverThick + airgap2Thick + pcbThick + sensorThick + coverThick/2;
      solidcover2[k] = new G4Box("cover",coverSize/2,coverSize/2,coverThick/2);
      logiccover2[k] = new G4LogicalVolume(solidcover2[k],coverMaterial,"cover");
      physicover2[k] = new G4PVPlacement(0,			//no rotation
					    G4ThreeVector(0,0,zposcover2),	//at (0,0,0)
					    logiccover2[k],	//its logical volume
					    "cover",		//its name
					    logicWorld,		//its mother  volume
					    false,		        //no boolean operation
					    k);			//copy number
      
      G4cout << "  zcover2   = " << G4BestUnit(zposcover2-coverThick/2.,"Length") << G4endl;
      
      //airgap
      G4double zposairgap1_2 = caloPitch * k + absorThick + airgapThick + coverThick + airgap2Thick + pcbThick + sensorThick + coverThick + airgapThick/2;
      solidairgap1_2[k] = new G4Box("airgap",airgapSize/2,airgapSize/2,airgapThick/2);
      logicairgap1_2[k] = new G4LogicalVolume(solidairgap1_2[k],airgapMaterial,"airgap");
      physiairgap1_2[k] = new G4PVPlacement(0,			//no rotation
					     G4ThreeVector(0,0,zposairgap1_2),	//at (0,0,0)
					     logicairgap1_2[k],	//its logical volume
					     "airgap",		//its name
					     logicWorld,		//its mother  volume
					     false,		        //no boolean operation
					     k);			//copy number
      
      
      
      G4cout << "  zairgap2  = " << G4BestUnit(zposairgap1_2-airgapThick/2.,"Length") << G4endl;
    }


    // RPWELL chambers
    if (numOfLayer_RPWELL > 0){
      G4cout <<"Creating" << numOfLayer_RPWELL << "RPWELL layers"<< G4endl;
    }
    
    for (G4int k = 0 ; k < numOfLayer_RPWELL ; k++)
    {

      G4cout <<""<< G4endl;
      G4cout << "RPWELL Layer " << k+1 << G4endl;

      G4int l = numOfLayer - numOfLayer_RPWELL + k;

      //ABSORBER

      G4double zposAbsor = caloPitch * l + absorThick/2;

      solidAbsor[k] = new G4Box("Absorber",absorSize/2,absorSize/2,absorThick/2);
      logicAbsor[k] = new G4LogicalVolume(solidAbsor[k],absorMaterial,"Absorber");
      physiAbsor[k] = new G4PVPlacement(0,			//no rotation
					G4ThreeVector(0,0,zposAbsor),	//at (0,0,0)
					logicAbsor[k],		//its logical volume
					"Absorber",		//its name
					logicWorld,		//its mother  volume
					false,			//no boolean operation
					k);			//copy number

      G4cout << "  zabsorber   = " << G4BestUnit(zposAbsor-absorThick/2,"Length") << G4endl;


      //CHAMBERS

      //airgap
      G4double zposairgap1 = caloPitch * l + absorThick + airgapThick/2;
      solidairgap1[k] = new G4Box("airgap",airgapSize/2,airgapSize/2,airgapThick/2);
      logicairgap1[k] = new G4LogicalVolume(solidairgap1[k],airgapMaterial,"airgap");
      physiairgap1[k] = new G4PVPlacement(0,			//no rotation
					     G4ThreeVector(0,0,zposairgap1),	//at (0,0,0)
					     logicairgap1[k],	//its logical volume
					     "airgap",		//its name
					     logicWorld,		//its mother  volume
					     false,		        //no boolean operation
					     k);			//copy number
      G4cout << "  zairgap1  = " << G4BestUnit(zposairgap1-airgapThick/2.,"Length") << G4endl;
	  
      //mask
      G4double zposmask = caloPitch * l + absorThick + airgapThick + maskThick/2;
      solidmask[k] = new G4Box("mask",maskSize/2,maskSize/2,maskThick/2);
      logicmask[k] = new G4LogicalVolume(solidmask[k],maskMaterial,"mask");
      physimask[k] = new G4PVPlacement(0,			//no rotation
					   G4ThreeVector(0,0,zposmask),	//at (0,0,0)
					   logicmask[k],	//its logical volume
					   "mask",		//its name
					   logicWorld,		//its mother  volume
					   false,		        //no boolean operation
					   k);			//copy number
      G4cout << "  zmask     = " << G4BestUnit(zposmask-maskThick/2.,"Length") << G4endl;
      
      //pcb
      G4double zpospcb = caloPitch * l + absorThick + airgapThick + maskThick + pcbThick/2;
      solidpcb[k] = new G4Box("pcb",pcbSize/2,pcbSize/2,pcbThick/2);
      logicpcb[k] = new G4LogicalVolume(solidpcb[k],pcbMaterial,"pcb");
      physipcb[k] = new G4PVPlacement(0,			//no rotation
					G4ThreeVector(0,0,zpospcb),	//at (0,0,0)
					logicpcb[k],	//its logical volume
					"pcb",		//its name
					logicWorld,		//its mother  volume
					false,		        //no boolean operation
					k);			//copy number
      
      G4cout << "  zpcb      = " << G4BestUnit(zpospcb-pcbThick/2.,"Length") << G4endl;
      
      //Resistive Plate
      G4double zposrp = caloPitch * l + absorThick + airgapThick + maskThick + pcbThick + rpThick/2;
      solidrp[k] = new G4Box("rp",rpSize/2,rpSize/2,rpThick/2);
      logicrp[k] = new G4LogicalVolume(solidrp[k],rpMaterial,"rp");
      physirp[k] = new G4PVPlacement(0,			//no rotation
					G4ThreeVector(0,0,zposrp),	//at (0,0,0)
					logicrp[k],	//its logical volume
					"rp",		//its name
					logicWorld,		//its mother  volume
					false,		        //no boolean operation
					k);			//copy number
      
      G4cout << "  zrp      = " << G4BestUnit(zposrp-rpThick/2.,"Length") << G4endl;

      //THGEM
      G4double zposthgem = caloPitch * l + absorThick + airgapThick + maskThick + pcbThick + rpThick + thgemThick/2;
      solidthgem[k] = new G4Box("thgem",thgemSize/2,thgemSize/2,thgemThick/2);
      logicthgem[k] = new G4LogicalVolume(solidthgem[k],thgemMaterial,"thgem");
      physithgem[k] = new G4PVPlacement(0,			//no rotation
					G4ThreeVector(0,0,zposthgem),	//at (0,0,0)
					logicthgem[k],	//its logical volume
					"thgem",		//its name
					logicWorld,		//its mother  volume
					false,		        //no boolean operation
					k);			//copy number
      
      G4cout << "  zthgem      = " << G4BestUnit(zposthgem-thgemThick/2.,"Length") << G4endl;

      //electrode
      G4double zposelectrode1 = caloPitch * l + absorThick + airgapThick + maskThick + pcbThick + rpThick +\
                                thgemThick + electrodeThick/2;
      solidelectrode[k] = new G4Box("electrode",electrodeSize/2,electrodeSize/2,electrodeThick/2);
      logicelectrode[k] = new G4LogicalVolume(solidelectrode[k],electrodeMaterial,"electrode");
      physielectrode[k] = new G4PVPlacement(0,			//no rotation
					G4ThreeVector(0,0,zposelectrode1),	//at (0,0,0)
					logicelectrode[k],	//its logical volume
					"electrode",		//its name
					logicWorld,		//its mother  volume
					false,		        //no boolean operation
					k);			//copy number
      
      G4cout << "  zelectrode      = " << G4BestUnit(zposelectrode1-electrodeThick/2.,"Length") << G4endl;

      //sensor
      G4double zpossensor = caloPitch * l + absorThick + airgapThick + maskThick + pcbThick + rpThick +\
                            thgemThick + electrodeThick + sensorThick/2;
      solidsensor[k] = new G4Box("sensor",sensorSize/2,sensorSize/2,sensorThick/2);
      logicsensor[k] = new G4LogicalVolume(solidsensor[k],sensorMaterial,"sensor");
      physisensor[k] = new G4PVPlacement(0,			//no rotation
					     G4ThreeVector(0,0,zpossensor),	//at (0,0,0)
					     logicsensor[k],	//its logical volume
					     "sensor",		//its name
					     logicWorld,		//its mother  volume
					     false,		        //no boolean operation
					     k);			//copy number
      
      G4cout << "  zsensor   = " << G4BestUnit(zpossensor-sensorThick/2.,"Length") << G4endl;
      
      //electrode2
      G4double zposelectrode2 = caloPitch * l + absorThick + airgapThick + maskThick + pcbThick + rpThick +\
                               thgemThick + electrodeThick + sensorThick + electrodeThick/2;
      solidelectrode2[k] = new G4Box("electrode",electrodeSize/2,electrodeSize/2,electrodeThick/2);
      logicelectrode2[k] = new G4LogicalVolume(solidelectrode2[k],electrodeMaterial,"electrode");
      physielectrode2[k] = new G4PVPlacement(0,			//no rotation
					G4ThreeVector(0,0,zposelectrode2),	//at (0,0,0)
					logicelectrode2[k],	//its logical volume
					"electrode",		//its name
					logicWorld,		//its mother  volume
					false,		        //no boolean operation
					k);			//copy number
      
      G4cout << "  zelectrode      = " << G4BestUnit(zposelectrode2-electrodeThick/2.,"Length") << G4endl;
      
      //cathode
      G4double zposcathode2 = caloPitch * l + absorThick + airgapThick + maskThick + pcbThick + rpThick +\
                              thgemThick + electrodeThick + sensorThick + electrodeThick + cathodeThick/2;
      solidcathode[k] = new G4Box("cathode",cathodeSize/2,cathodeSize/2,cathodeThick/2);
      logiccathode[k] = new G4LogicalVolume(solidcathode[k],cathodeMaterial,"cathode");
      physicathode[k] = new G4PVPlacement(0,			//no rotation
					    G4ThreeVector(0,0,zposcathode2),	//at (0,0,0)
					    logiccathode[k],	//its logical volume
					    "cathode",		//its name
					    logicWorld,		//its mother  volume
					    false,		        //no boolean operation
					    k);			//copy number
      
      G4cout << "  zcathode2   = " << G4BestUnit(zposcathode2-cathodeThick/2.,"Length") << G4endl;
      
      //electrode3
      G4double zposelectrode3 = caloPitch * l + absorThick + airgapThick + maskThick + pcbThick + rpThick +\
                                thgemThick + electrodeThick + sensorThick + electrodeThick + cathodeThick + electrodeThick/2;
      solidelectrode3[k] = new G4Box("electrode",electrodeSize/2,electrodeSize/2,electrodeThick/2);
      logicelectrode3[k] = new G4LogicalVolume(solidelectrode3[k],electrodeMaterial,"electrode");
      physielectrode3[k] = new G4PVPlacement(0,			//no rotation
					G4ThreeVector(0,0,zposelectrode3),	//at (0,0,0)
					logicelectrode3[k],	//its logical volume
					"electrode",		//its name
					logicWorld,		//its mother  volume
					false,		        //no boolean operation
					k);			//copy number
      
      G4cout << "  zelectrode      = " << G4BestUnit(zposelectrode3-electrodeThick/2.,"Length") << G4endl;

      //airgap
      G4double zposairgap2 = caloPitch * l + absorThick + airgapThick + maskThick + pcbThick + rpThick +\
                             thgemThick + electrodeThick + sensorThick + electrodeThick + cathodeThick + electrodeThick + airgapThick/2;
      solidairgap1_2[k] = new G4Box("airgap",airgapSize/2,airgapSize/2,airgapThick/2);
      logicairgap1_2[k] = new G4LogicalVolume(solidairgap1_2[k],airgapMaterial,"airgap");
      physiairgap1_2[k] = new G4PVPlacement(0,			//no rotation
					     G4ThreeVector(0,0,zposairgap2),	//at (0,0,0)
					     logicairgap1_2[k],	//its logical volume
					     "airgap",		//its name
					     logicWorld,		//its mother  volume
					     false,		        //no boolean operation
					     k);			//copy number
      
      
      
      G4cout << "  zairgap2  = " << G4BestUnit(zposairgap2-airgapThick/2.,"Length") << G4endl;
    }

  //always return the physical World
  return physiWorld;
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4RunManager.hh"

void DetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructCalorimeter());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
