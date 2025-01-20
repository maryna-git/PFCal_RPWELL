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
// $Id: HistoManager.cc,v 1.18 2010/11/09 21:02:47 asaim Exp $
// GEANT4 tag $Name: geant4-09-04 $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "HistoManager.hh"
#include "G4UnitsTable.hh"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
  :rootFile(0),tree(0),hptype(0)
{
  fileName = "../rootfiles/uMSDHCAL_0GeV_0Tesla.root";
  rootFile = new TFile(fileName,"RECREATE");  

  hzstart = new TH1I("hzstart","Layer of first pion inelastic interaction",numOfLayer,0,numOfLayer);
  hptype = new TH1I("hptype","Particle spectrum - all calo",10001,-5000,5000);

  treename = "uMSDHCALtree";
  tree = new TTree(treename,"Showers in uMSDHCAL 2m3");
  
  tree->Branch("zStart",&zStart,"zStart/I");
  tree->Branch("nHit",&nHit,"nHit/I");
  tree->Branch("eTot",&eTot,"eTot/D");
  tree->Branch("eEm",&eEm,"eEm/D");
  tree->Branch("eBeam",&eBeam,"eBeam/D");
  tree->Branch("pBeam",&pBeam,"pBeam/I");  
  tree->Branch("thetaBeam",&thetaBeam,"thetaBeam/D");
  tree->Branch("phiBeam",&phiBeam,"phiBeam/D");

  tree->Branch("pHit",&pHit,"pHit[nHit]/I");
  tree->Branch("emHit",&emHit,"emHit[nHit]/I");
  tree->Branch("xHit",&xHit,"xHit[nHit]/D");
  tree->Branch("yHit",&yHit,"yHit[nHit]/D");
  tree->Branch("zHit",&zHit,"zHit[nHit]/D");
  tree->Branch("lHit",&lHit,"lHit[nHit]/I");
  tree->Branch("tHit",&tHit,"tHit[nHit]/D");
  tree->Branch("eHit",&eHit,"eHit[nHit]/D");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager(TString rootfilename)
  :rootFile(0),tree(0),hptype(0)
{
  rootFile = new TFile(rootfilename,"RECREATE");

  hzstart = new TH1I("hzstart","Layer of first pion inelastic interaction",numOfLayer,0,numOfLayer);
  hptype = new TH1I("hptype","Particle spectrum - all calo",10001,-5000,5000);

  treename = "uMSDHCALtree";
  tree = new TTree(treename,"Showers in uMSDHCAL 2m3");
  
  tree->Branch("zStart",&zStart,"zStart/I");
  tree->Branch("nHit",&nHit,"nHit/I");
  tree->Branch("pBeam",&pBeam,"pBeam/I");
  tree->Branch("eTot",&eTot,"eTot/D");
  tree->Branch("eEm",&eEm,"eEm/D");
  tree->Branch("eBeam",&eBeam,"eBEAM/D");
  tree->Branch("thetaBeam",&thetaBeam,"thetaBeam/D");
  tree->Branch("phiBeam",&phiBeam,"phiBeam/D");  

  tree->Branch("pHit",&pHit,"pHit[nHit]/I");
  tree->Branch("emHit",&emHit,"emHit[nHit]/I");
  tree->Branch("xHit",&xHit,"xHit[nHit]/D");
  tree->Branch("yHit",&yHit,"yHit[nHit]/D");
  tree->Branch("zHit",&zHit,"zHit[nHit]/D");
  tree->Branch("lHit",&lHit,"lHit[nHit]/I");
  tree->Branch("tHit",&tHit,"tHit[nHit]/D");
  tree->Branch("eHit",&eHit,"eHit[nHit]/D");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{ 
  rootFile->Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::fillHitTree(G4int phit,G4int emhit,G4double xhit,
                               G4double yhit,G4double zhit,G4int lhit,
                               G4double thit,G4double ehit)
{ 
  pHit[nHit] = phit;
  emHit[nHit] = emhit;

  xHit[nHit] = xhit;
  yHit[nHit] = yhit;
  zHit[nHit] = zhit;
  eHit[nHit] = ehit;

  lHit[nHit] = lhit;
  tHit[nHit] = thit;

  eTot += ehit;
  nHit++;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::fillHitTree(G4int originP, G4double originE, G4double originTheta, G4double originPhi)
{ 
  pBeam = originP;
  eBeam = originE;
  thetaBeam = originTheta;
  phiBeam = originPhi;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::fillEventTree()
{ 
  tree->Fill();

  //hzstart->Write("", TObject::kOverwrite);
  //hptype->Write("", TObject::kOverwrite);
  //tree->Write("", TObject::kOverwrite);
  //rootFile->Write("", TObject::kOverwrite);
	

  G4cout << " nGasInteraction = " << nHit << " eTot = " << eTot <<" keV " <<  "eBeam = " << eBeam << " GeV ; pBeam = " << pBeam<< G4endl;   
  zStart = -1;
  nHit   = 0;
  eTot   = 0;
  eEm    = 0;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::writeToRoot()
{ 
  hzstart->Write();
  hptype->Write();

  tree->Write();
  //rootFile->Write();

  G4cout<<" ROOTfile name = "<< rootFile->GetName()<<G4endl;

  rootFile->Close();
}


