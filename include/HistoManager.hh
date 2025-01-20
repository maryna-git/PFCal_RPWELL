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
// $Id: HistoManager.hh,v 1.8 2007/11/12 17:04:55 maire Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TRandom.h"

//SI
#include "TH1I.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#include "DetectorConstruction.hh"

const G4int nHitMax = 100000;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HistoManager
{
  public:
  
  HistoManager();
  HistoManager(TString rootfilename);
  ~HistoManager();

  TH1I* hzstart;
  TH1I* hptype;

  TFile* rootFile;
  G4String fileName;

  void fillHitTree(G4int phit,G4int emHit,G4double xhit,G4double yhit,G4double zhit,G4int lhit,G4double thit,G4double ehit);
  void fillHitTree(G4int originP, G4double originE, G4double originTheta, G4double originPhi);
  void fillEventTree();
  G4int GetnHitTree(){return nHit;};
  void writeToRoot();

  void SetZstart(G4int z0){zStart = z0;}
  void IncreaseEmEnergy(G4double em_energy){eEm += em_energy;}

    
  private:

  G4int    zStart;
  G4int    nHit;
  G4double eTot;
  G4double eEm;
  G4double eBeam;
  G4int pBeam;
  G4double thetaBeam;
  G4double phiBeam;

  G4int    pHit[nHitMax];
  G4int    emHit[nHitMax];
  G4double xHit[nHitMax];
  G4double yHit[nHitMax];
  G4double zHit[nHitMax];
  G4double tHit[nHitMax];
  G4int    lHit[nHitMax];
  G4double eHit[nHitMax];

  TTree * tree;
  G4String treename;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

