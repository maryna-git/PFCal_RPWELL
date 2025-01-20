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
// $Id: DetectorConstruction.hh,v 1.13 2006/06/29 16:51:06 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class DetectorMessenger;

const G4int numOfLayer = 50;
const G4int numOfLayer_RPWELL = 50;



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........AoooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:

  DetectorConstruction();
  ~DetectorConstruction();

public:
  
  void SetWorldMaterial (const G4String&);

  G4VPhysicalVolume* Construct();

  void UpdateGeometry();
     
public:
  
  G4double GetWorldSize(){return worldSize;}; 

  G4double GetAbsorThick(){return absorThick;};
  G4double GetPcbThick(){return pcbThick;}; 
  //G4double GetSensorThick(){return sensorThick;}; 

  G4double GetCaloPitch(){return caloPitch;}

  const G4VPhysicalVolume* GetPhysiWorld()        {return physiWorld;};
  const G4Material*        GetWorldMaterial()     {return worldMaterial;};

  const G4Material* GetSensorMaterial(){return sensorMaterial;};

  const G4Material* GetAbsorMaterial(){return absorMaterial;};
  const G4Material* GetPcbMaterial(){return pcbMaterial;};
  const G4Material* GetThgemMaterial(){return thgemMaterial;};
  const G4Material* GetElectrodeMaterial(){return electrodeMaterial;};


  void PrintCalorParameters();

private:


  G4double caloPitch;

  //world

  G4double worldSize;
  G4Material* worldMaterial;

  G4Box*             solidWorld;
  G4LogicalVolume*   logicWorld;
  G4VPhysicalVolume* physiWorld;

  //absorber

  G4double absorSize;
  G4double absorThick;
  G4Material* absorMaterial;

  G4Box*             solidAbsor[numOfLayer];
  G4LogicalVolume*   logicAbsor[numOfLayer];
  G4VPhysicalVolume* physiAbsor[numOfLayer];

  //pcb

  G4double pcbSize;
  G4double pcbThick;
  G4Material* pcbMaterial;

  G4Box*             solidpcb[numOfLayer];
  G4LogicalVolume*   logicpcb[numOfLayer];
  G4VPhysicalVolume* physipcb[numOfLayer];

  //sensor  - conversion gas

  G4double sensorSize;
  G4double sensorThick;
  G4Material* sensorMaterial;

  G4Box*             solidsensor[numOfLayer];
  G4LogicalVolume*   logicsensor[numOfLayer];
  G4VPhysicalVolume* physisensor[numOfLayer];

    //cover  - Micromegas baseplate and cover

  G4double coverSize;
  G4double coverThick;
  G4Material* coverMaterial;

  G4Box*             solidcover[numOfLayer - numOfLayer_RPWELL];
  G4LogicalVolume*   logiccover[numOfLayer - numOfLayer_RPWELL];
  G4VPhysicalVolume* physicover[numOfLayer - numOfLayer_RPWELL];

  G4Box*             solidcover2[numOfLayer - numOfLayer_RPWELL];
  G4LogicalVolume*   logiccover2[numOfLayer - numOfLayer_RPWELL];
  G4VPhysicalVolume* physicover2[numOfLayer - numOfLayer_RPWELL];

  //airgap  

  G4double airgapSize;
  G4double airgapThick;
  G4Material* airgapMaterial;

  G4Box*             solidairgap1[numOfLayer];
  G4LogicalVolume*   logicairgap1[numOfLayer];
  G4VPhysicalVolume* physiairgap1[numOfLayer];

  G4Box*             solidairgap1_2[numOfLayer];
  G4LogicalVolume*   logicairgap1_2[numOfLayer];
  G4VPhysicalVolume* physiairgap1_2[numOfLayer];

  //airgap2  - Micromegas air gap

  G4double airgap2Size;
  G4double airgap2Thick;

  G4Box*             solidairgap2[numOfLayer - numOfLayer_RPWELL];
  G4LogicalVolume*   logicairgap2[numOfLayer - numOfLayer_RPWELL];
  G4VPhysicalVolume* physiairgap2[numOfLayer - numOfLayer_RPWELL];

  //mask 

  G4double maskSize;
  G4double maskThick;
  G4Material* maskMaterial;

  G4Box*             solidmask[numOfLayer_RPWELL];
  G4LogicalVolume*   logicmask[numOfLayer_RPWELL];
  G4VPhysicalVolume* physimask[numOfLayer_RPWELL];

  //THGEM 

  G4double thgemSize;
  G4double thgemThick;
  G4Material* thgemMaterial;

  G4Box*             solidthgem[numOfLayer_RPWELL];
  G4LogicalVolume*   logicthgem[numOfLayer_RPWELL];
  G4VPhysicalVolume* physithgem[numOfLayer_RPWELL];

  //Resistive Plate 

  G4double rpSize;
  G4double rpThick;
  G4Material* rpMaterial;

  G4Box*             solidrp[numOfLayer_RPWELL];
  G4LogicalVolume*   logicrp[numOfLayer_RPWELL];
  G4VPhysicalVolume* physirp[numOfLayer_RPWELL];

  //cathode - RPWELL cover

  G4double cathodeSize;
  G4double cathodeThick;
  G4Material* cathodeMaterial;

  G4Box*             solidcathode[numOfLayer_RPWELL];
  G4LogicalVolume*   logiccathode[numOfLayer_RPWELL];
  G4VPhysicalVolume* physicathode[numOfLayer_RPWELL];

  //electrode

  G4double electrodeSize;
  G4double electrodeThick;
  G4Material* electrodeMaterial;

  G4Box*             solidelectrode[numOfLayer_RPWELL];
  G4LogicalVolume*   logicelectrode[numOfLayer_RPWELL];
  G4VPhysicalVolume* physielectrode[numOfLayer_RPWELL];

  G4Box*             solidelectrode2[numOfLayer_RPWELL];
  G4LogicalVolume*   logicelectrode2[numOfLayer_RPWELL];
  G4VPhysicalVolume* physielectrode2[numOfLayer_RPWELL];

  G4Box*             solidelectrode3[numOfLayer_RPWELL];
  G4LogicalVolume*   logicelectrode3[numOfLayer_RPWELL];
  G4VPhysicalVolume* physielectrode3[numOfLayer_RPWELL];



  DetectorMessenger* detectorMessenger;


  
private:

  void DefineMaterials();
  G4VPhysicalVolume* ConstructCalorimeter();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

