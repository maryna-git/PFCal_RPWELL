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
// $Id: SteppingAction.cc,v 1.28 2008/05/29 16:59:27 vnivanch Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "TrackingAction.hh"
#include "HistoManager.hh"

#include "G4Step.hh"
#include "G4UnitsTable.hh"
#include "G4Positron.hh"
#include "G4RunManager.hh"

#include "G4VProcess.hh"

#include <set>


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(DetectorConstruction* det, RunAction* run, EventAction* evt, HistoManager* hist)
:G4UserSteppingAction(),detector(det),runAct(run),eventAct(evt),histoManager(hist) 
{
  eventAct->SetSteppingAction(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::ClearSet()
{
  //G4cout << "Set size before clear = "<<emSet.size() << G4endl;
  emSet.clear();
  //G4cout << "Set size after clear = "<<emSet.size() << G4endl;
}





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  //G4cout<<"  NEW STEP"<<G4endl;

  //track informations

  const G4StepPoint* prePoint = aStep->GetPreStepPoint();
  const G4Track* track = aStep->GetTrack();
  const G4ParticleDefinition* particle = track->GetDefinition();

  G4int ptype = particle->GetPDGEncoding();

  G4VPhysicalVolume* volume = prePoint->GetTouchableHandle()->GetVolume();

  G4Material* mat = volume->GetLogicalVolume()->GetMaterial();
  G4double pitch = detector->GetCaloPitch();

  G4double z = 0;
  G4int layer = 0;
  G4bool zstartId = eventAct->GetZstartId();


  //reset emSet on first particle
  //if (track->GetTrackID() == 1)
  //{
      //G4cout<<"set size before clear = "<<emSet.size()<<G4endl;
      //emSet.clear();
      //G4cout<<"set size after clear = "<<emSet.size()<<G4endl;
  //}


  //tag EM particles 

  G4int em = 0;
  G4double energy = 0;
  G4bool emfraction = 0;

  /*
  if (emfraction)
    {
      if (ptype == 111 || ptype == 221)
	{
	  emSet.insert(track->GetTrackID());

	  energy = track->GetKineticEnergy() * 1e3;
	  histoManager->IncreaseEmEnergy(energy);
	  G4cout << "Find pi0 with energy = " << G4BestUnit(track->GetKineticEnergy(),"Energy") << " trackid = " << track->GetTrackID() << " parentid = " << track->GetParentID() << G4endl;
	  
	  em = 1;
	}
      else
	{

	  std::set<G4int>::iterator iter;

	  //check if parent is EM
	  iter = emSet.find(track->GetParentID());

	  //if parent is EM particle -> parent is in the map
	  if (iter != emSet.end())
	    {
	      em = 1;

	      if (ptype==211 || ptype==-211)
		{
		  //G4cout << "CHARGED PIONS IN EM SHOWER!" << G4endl;
		}
	      
	      //if particle is not in the map yet -> insert it in the map
	      if (emSet.find(track->GetTrackID()) == emSet.end())
		{
		  //G4cout << "Insert em particle " << ptype << " - ID = " << track->GetTrackID() << " with parentID = " << track->GetParentID() << G4endl;
		  emSet.insert(track->GetTrackID());
		}
	      
	    }
	}
    }
  */


  //tag first nuclear interaction for shower start layer id


  G4String process = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
  if ((process == "PionMinusInelastic") && (zstartId == 0))
    {
      z = prePoint->GetPosition().z();
      layer = z / pitch + 1;

      histoManager->hzstart->Fill(layer);

      eventAct->SetZstartId(1);
      histoManager->SetZstart(layer);
    }




  //record interaction in gas

  if (mat == detector->GetSensorMaterial())
    {
      G4double edep = aStep->GetTotalEnergyDeposit()*1e3;

      if (edep != 0)
	{
	  G4double x = prePoint->GetPosition().x();
	  G4double y = prePoint->GetPosition().y();	  
	  G4double t = prePoint->GetLocalTime();
	  z = prePoint->GetPosition().z();
	  layer = z / pitch + 1;

	  x *= 0.1;
	  y *= 0.1;
	  z *= 0.1;

	  if (histoManager->GetnHitTree() < nHitMax)
	    {
	      histoManager->fillHitTree(ptype,em,x,y,z,layer,t,edep);
	    }
	}
    }
}
