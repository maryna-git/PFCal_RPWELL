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

const G4int numOfLayer = 10;			// 0 + 9  

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
  
  G4double GetWorldSize()           {return worldSize;}; 

  const G4VPhysicalVolume* GetPhysiWorld()        {return physiWorld;};
  const G4Material*        GetWorldMaterial()     {return worldMaterial;};

  const G4Material* GetSensorMaterial(){return sensorMaterial;};

  void PrintCalorParameters();

private:

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

  G4Box*             solidAbsor;
  G4LogicalVolume*   logicAbsor;
  G4VPhysicalVolume* physiAbsor;

  //sensor

  G4double sensorSize;
  G4double sensorThick;
  G4Material* sensorMaterial;

  G4Box*             solidSensor;
  G4LogicalVolume*   logicSensor;
  G4VPhysicalVolume* physiSensor;



  DetectorMessenger* detectorMessenger;

private:

  void DefineMaterials();
  G4VPhysicalVolume* ConstructCalorimeter();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

