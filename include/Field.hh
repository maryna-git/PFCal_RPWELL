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

#ifndef Field_H
#define Field_H 1

#include "globals.hh"
#include "G4MagneticField.hh"

class FieldMessenger;

class Field : public G4MagneticField
{
  public:
    Field();
    //Field(DetectorConstruction*);
    ~Field();

  void SetBfield(double Bx,double By,double Bz);
  void SetBfieldY(double By);

  void GetFieldValue( const  double Point[3], double *Bfield ) const;

  private:
  double Bx;
  double By;
  double Bz;
  FieldMessenger* messenger;
};

#endif

