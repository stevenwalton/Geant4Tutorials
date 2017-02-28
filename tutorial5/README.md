# Changes in Tutorial 4
The biggest change we did is that we stated to count the number of secondaries
We use the filter `G4PSNofSecondary` to count the number of secondary e-,e+,protons, and neutrons.
These filters are set within the detector construction class and are added in the run class.
Pay special attention to the comments made and how order matters when setting the filters and 
calling back the hits maps

We have also added to the GUI. Specifically we have a run button that will run a single event as well as one
to run 10 events. A menu has also been created and that allows you to change the energy levels and the gun's
particle. 
