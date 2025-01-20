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
// $Id: FieldMessenger.cc,v 1.11 2006/06/29 16:52:26 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "FieldMessenger.hh"
#include "Field.hh"

#include <sstream>

#include "G4UIdirectory.hh"
#include "G4UnitsTable.hh"

#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FieldMessenger::FieldMessenger(Field * _field)
:Bfield(_field)
{ 
  FieldDir = new G4UIdirectory("/Bfield/");
  FieldDir->SetGuidance("Menu to manage Bfield");
  
  FieldCmd = new G4UIcmdWithADouble("/Bfield/setField",this);  
  FieldCmd->SetGuidance("Define magnetic field.");
  FieldCmd->SetGuidance("Magnetic field will be in Y direction.");
  FieldCmd->SetParameterName("By",false);
  //FieldCmd->SetUnitCategory("Magnetic flux density");
  //  FieldCmd->SetUnitCategory("T");
  FieldCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FieldMessenger::~FieldMessenger()
{
  delete FieldCmd;
  delete FieldDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FieldMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if( command == FieldCmd )
   {
	 Bfield->SetBfieldY( FieldCmd->GetNewDoubleValue(newValue));
   }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
