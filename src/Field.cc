//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//

#include "Field.hh"
#include "FieldMessenger.hh"
#include "G4Tubs.hh"
#include "G4UnitsTable.hh"
#include "G4Box.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include <math.h>
#include "G4SystemOfUnits.hh"

Field::Field() : Bx(0.), By(0.),  Bz(0.)
{
  messenger = new FieldMessenger(this);
}

/*
Field::Field(DetectorConstruction* detector) : Bx(0.), By(0.),  Bz(0.) 
{

  fieldMessenger = new FieldMessenger(this);
  // Compute toroidal Magnet system
}
*/

Field::~Field()
{delete messenger;}




void Field::SetBfield(double _Bx,double _By,double _Bz)
{
 Bx = _Bx*tesla;
 By = _By*tesla;
 Bz = _Bz*tesla;
}

void Field::SetBfieldY(double _By)
{
 By = _By*tesla;
 G4cout<<"By = "<<_By<<" Tesla"<<G4endl;
 G4cout<<" Bx = "<<G4BestUnit(Bx,"Magnetic flux density")<<G4endl;
 G4cout<<" By = "<<G4BestUnit(By,"Magnetic flux density")<<G4endl;
 G4cout<<" Bz = "<<G4BestUnit(Bz,"Magnetic flux density")<<G4endl;
}


void Field::GetFieldValue(const double Point[3],double *Bfield) const
{
  Bfield[0] = Bx;
  Bfield[1] = By;
  Bfield[2] = Bz;
}

