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
// $Id: Em3PrimaryGeneratorAction.hh,v 1.6 2001-10-22 10:58:50 maire Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef Em3PrimaryGeneratorAction_h
#define Em3PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4Event;
class Em3DetectorConstruction;
class Em3PrimaryGeneratorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class Em3PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    Em3PrimaryGeneratorAction(Em3DetectorConstruction*);    
   ~Em3PrimaryGeneratorAction();

  public:
    void SetDefaultKinematic();
    void SetRndmBeam(G4double val) { rndmBeam = val;} 
    void GeneratePrimaries(G4Event*);
    G4ParticleGun* GetParticleGun() {return particleGun;};
    
  private:
    G4ParticleGun*              particleGun;
    Em3DetectorConstruction*    Em3Detector;
    
    G4double rndmBeam;   //lateral random beam extension in fraction sizeYZ/2   
    
    Em3PrimaryGeneratorMessenger* gunMessenger; 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


