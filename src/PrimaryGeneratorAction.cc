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
// $Id: PrimaryGeneratorAction.cc,v 1.7 2006/06/29 16:53:00 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "PrimaryGeneratorAction.hh"

#include "PrimaryGeneratorMessenger.hh"
#include "DetectorConstruction.hh"
#include "HistoManager.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction* det, HistoManager* hist)
:Detector(det),histoManager(hist) 
{
  G4int n_particle = 1;
  particleGun  = new G4ParticleGun(n_particle);
  SetDefaultKinematic();
  rndmBeam = 0.;
  
  //create a messenger for this class
  gunMessenger = new PrimaryGeneratorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
  delete gunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::SetDefaultKinematic()
{
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="pi-"); // pi-// "neutron"
  particleGun->SetParticleDefinition(particle);
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  particleGun->SetParticleEnergy(40.*GeV);
  G4double position = -0.5*(Detector->GetWorldSize());
  particleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,position));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of event
  //
  //randomize the beam, if requested.
  rndmBeam = 1;
  if (rndmBeam > 0.) 
    {
      G4ThreeVector oldPosition = particleGun->GetParticlePosition();    

      /*Uniform beam*/
      /*
      G4double rbeam = 0.5;//0.5*(Detector->GetuMSizeX())*rndmBeam;
      G4double z0 = oldPosition.z();
      G4double y0 = G4UniformRand()*10;
      G4double x0 = G4UniformRand()*10;
      particleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
      */

      /*Point-like beam*/
      //G4double position = -0.5*(Detector->GetWorldSize());

      /*Point-like beam at the beginning of the ECAL*/
      //G4double position = -0.5*(numOfLayer * (Detector->GetAbsorThick() + Detector->GetSensorThick())) * 0.1;

      particleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,0.*cm));
      //particleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,-10.*cm));

      //Randomizing Particle angle
      // G4double theta_max = 30, phi_max = 360; // Maximum angles of the beam (you may need to specify these as 30*degree, 360*degree. Please check)
      // G4double theta_beam = theta_max*G4UniformRand();
      // G4double phi_beam = phi_max*G4UniformRand(); // Angles of the emerging beam. Randomly distributed between 0 - max angle

      G4double theta_beam = 0;
      G4double phi_beam = 0;

      G4double x_beam = sin(theta_beam*deg) * cos(phi_beam*deg);
      G4double y_beam = sin(theta_beam*deg) * sin(phi_beam*deg);
      G4double z_beam = cos(theta_beam*deg);

      particleGun->SetParticleMomentumDirection(G4ThreeVector(x_beam, y_beam, z_beam));
      
      // Randomizing beam energy
      G4int L_lim = 1;
      G4int U_lim = 60;
      G4double Energy = (L_lim + (U_lim - L_lim) * G4UniformRand());

      particleGun->SetParticleEnergy(Energy *GeV); 
      
      // Saving particlegun type and energy
      
      G4int pBeam = particleGun->GetParticleDefinition()->GetPDGEncoding();
      G4cout << "eBeam generator= " << Energy <<  " GeV ; pBeam generator = " << pBeam <<"; Theta = " << theta_beam << " deg; phi = " << phi_beam <<" deg" << G4endl; 
      histoManager->fillHitTree(pBeam, Energy, theta_beam, phi_beam);  

      particleGun->GeneratePrimaryVertex(anEvent);
      particleGun->SetParticlePosition(oldPosition); 
    }
  else  particleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
