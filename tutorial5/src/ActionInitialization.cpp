/* This code will be used to run the Primary Generator Action, Run Action, and Stacking actions. 
 * This is just for helping with organization
 */
#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "StackingAction.hh"

#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization(DetectorConstruction* detConst)
  : G4VUserActionInitialization(),
    fDetConst(detConst)
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction);
}

void ActionInitialization::Build() const
{
  SetUserAction(new PrimaryGeneratorAction);
  RunAction* rAction = new RunAction;
  SetUserAction(rAction);
  EventAction* event = new EventAction(rAction);
  SetUserAction(event);
  SetUserAction(new SteppingAction(fDetConst, event));
  SetUserAction(new StackingAction);
}

