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
// $Id: EventAction.cc,v 1.7 2004-06-15 11:39:58 maire Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "EventAction.hh"

#include "RunAction.hh"
#include "EventActionMessenger.hh"
#include "HistoManager.hh"

#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"

#ifdef USE_AIDA
 #include "AIDA/IHistogram1D.h"
#endif

#ifdef USE_ROOT
  #include "TH1F.h"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(DetectorConstruction* det, RunAction* run,
                         HistoManager* hist)
:detector(det), runAct(run), histoManager(hist)
{
  drawFlag = "none";
  printModulo = 10000;
  eventMessenger = new EventActionMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{
  delete eventMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* evt)
{   
  G4int evtNb = evt->GetEventID();

  //survey printing
  if (evtNb%printModulo == 0)
    G4cout << "\n---> Begin Of Event: " << evtNb << G4endl;
    
  //initialize EnergyDeposit per event
  //
  for (G4int k=0; k<MaxAbsor; k++)
    energyDeposit[k] = energyLeaving[k] = trackLengthCh[k] = 0.0;   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* evt)
{
  for (G4int k=0; k<detector->GetNbOfAbsor(); k++) {
     runAct->fillPerEvent(k,energyDeposit[k],trackLengthCh[k],
                       energyLeaving[k]/(G4double)(detector->GetNbOfLayers()));
#ifdef USE_AIDA
      if (histoManager->GetHisto(k)) {
	G4double unit = histoManager->GetHistoUnit(k); 
	histoManager->GetHisto(k)->fill(energyDeposit[k]/unit);
      }  
#endif

#ifdef USE_ROOT
      if (histoManager->GetHisto(k)) {
	G4double unit = histoManager->GetHistoUnit(k); 
	histoManager->GetHisto(k)->Fill(energyDeposit[k]/unit);
      }  
#endif
  }

  if (G4VVisManager::GetConcreteInstance())
    {
     G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
     G4int n_trajectories = 0;
     if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();
     for (G4int i=0; i<n_trajectories; i++) 
        { G4Trajectory* trj = (G4Trajectory*)
	                             ((*(evt->GetTrajectoryContainer()))[i]);
          if (drawFlag == "all") trj->DrawTrajectory(1000);
          else if ((drawFlag == "charged")&&(trj->GetCharge() != 0.))
                                  trj->DrawTrajectory(1000); 
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


