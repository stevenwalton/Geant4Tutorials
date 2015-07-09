#include "StackingAction.hh"

#include "G4Track.hh"
#include "G4NeutrinoE.hh"

StackingAction::StackingAction()
{}

StackingAction::~StackingAction()
{}

G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track* track)
{
  // Keep Primary Particle
  if (track -> GetParentID() == 0) return fUrgent;

  // KILL the secondary neutrinos (from beta decays
  if (track -> GetDefinition() == G4NeutrinoE::NeutrinoE()) return fKill;
  else return fUrgent;
}

