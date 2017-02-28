/* NEW FILE
 * Here we are really just deleting neutrinos because we don't care about them
 */
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

  // KILL the secondary neutrinos (from beta decays)
  if (track -> GetDefinition() == G4NeutrinoE::NeutrinoE()) return fKill;
  else return fUrgent;
}

/* 
 * Remember that during beta decays there is either a neutrino or antineutrino. We are just killing the neutrinos here because of the B+ decay, find
 * out how to kill the antineutrino form the e- decay 
 */
