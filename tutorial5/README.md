# Changes in Tutorial 5
This time we had the goal to get the Effective Dosages in the detector. If we reference 
ICRP 103 we can find the weights that each particle has, specifically neutrons are a problem.
We know that the dose (grays) are J/kg. So in SteppingAction we first check to see if we are 
in the Detector volume. We do this so that we don't look at the dosages of any other areas, and
this will save computation time (we are only concerned with this area). Then we get the
mass of the detector. We also grab the total energy deposited in the event. 

We know this energy deposit is in eV's so we divide that out (make sure to have SystemOfUnits) 
and then convert to Joules. We are only interested in the ionizing energies to we remove any
that aren't. Then we calculate dose as the ionizing energy divided by mass (J/kg). 

From here we find the particle name and apply the proper weighting. We use the ICRP values given 
and the functions for neutrons. We will then get the effective dosage at the end of each event. 
Note that we are not adding together the total dosages of ALL the events.
