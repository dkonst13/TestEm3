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
// $Id: Em3RunActionMessenger.cc,v 1.11 2003-04-01 10:40:21 maire Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "Em3RunActionMessenger.hh"

#include "Em3RunAction.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4ios.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Em3RunActionMessenger::Em3RunActionMessenger(Em3RunAction* run)
:Em3Run(run)
{    
  HistoCmd = new G4UIcommand("/testem/run/setHisto",this);
  HistoCmd->SetGuidance("Set histo Edep/Ebeam in absorber k");
  HistoCmd->SetGuidance("  histo=absor number : from 0 to NbOfAbsor-1");
  HistoCmd->SetGuidance("  number of bins; Emin/Ebeam; Emax/Ebeam");
  //
  G4UIparameter* AbsNbPrm = new G4UIparameter("AbsorNb",'i',false);
  AbsNbPrm->SetGuidance("histo=absor number : from 0 to NbOfAbsor-1");
  AbsNbPrm->SetParameterRange("AbsorNb>=0");
  HistoCmd->SetParameter(AbsNbPrm);
  //
  G4UIparameter* NbinPrm = new G4UIparameter("Nbin",'i',false);
  NbinPrm->SetGuidance("number of bins");
  NbinPrm->SetParameterRange("Nbin>=0");
  HistoCmd->SetParameter(NbinPrm);  
  //    
  G4UIparameter* VminPrm = new G4UIparameter("Vmin",'d',false);
  VminPrm->SetGuidance("Vmin=Emin/Ebeam");
  VminPrm->SetParameterRange("Vmin>=0.&&Vmin<=1.1");
  HistoCmd->SetParameter(VminPrm);
  //    
  G4UIparameter* VmaxPrm = new G4UIparameter("Vmax",'d',false);
  VmaxPrm->SetGuidance("Vmax=Emax/Ebeam");
  VmaxPrm->SetParameterRange("Vmax>=0.&&Vmax<=1.1");
  HistoCmd->SetParameter(VmaxPrm);  
  //
  HistoCmd->AvailableForStates(G4State_Idle);    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Em3RunActionMessenger::~Em3RunActionMessenger()
{
  delete HistoCmd;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Em3RunActionMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{   
  if (command == HistoCmd)
   { G4int idh,nbins; G4double vmin,vmax;
     const char* t = newValue;
     G4std::istrstream is((char*)t);
     is >> idh >> nbins >> vmin >> vmax;
     Em3Run->SetHisto (idh,nbins,vmin,vmax);
   }         
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
