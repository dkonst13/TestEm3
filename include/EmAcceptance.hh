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
//
// $Id: EmAcceptance.hh,v 1.1 2004-05-25 20:24:11 vnivanch Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//

#ifndef EmAcceptance_h
#define EmAcceptance_h 1

#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class EmAcceptance
{

public:
  EmAcceptance();
  ~EmAcceptance();

  void BeginOfAcceptance(const G4String& title, G4int stat);
  void EndOfAcceptance();

  void EmAcceptanceGauss(const G4String& title, G4int stat, 
                               G4double avr, G4double avr0, 
		               G4double rms, G4double limit);

private:

  // hide assignment operator
  EmAcceptance & operator=(const EmAcceptance &right);
  EmAcceptance(const EmAcceptance&);

  G4bool isAccepted;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
