# Changes in Tutorial 5
------------------------
This time we had the goal to get the Effective Dosages in the detector. If we reference 
ICRP 103 we can find the weights that each particle has, specifically neutrons are a problem.
Unfortunately the dosage detector we've been using does not account for the weights of the 
particles. That's okay though, because we can do it manually. In this case we need to define
how each step works. So we'll again build off of what we already have, there are probably
more clever ways to do this task but this works. We want to minimize computation time so we
are only going to change how steps work when they are inside the detector. Once we know
we are in the detector we need to get some items here.

We know that the Effective Dose (unit: Sv) is the sum of the weights times the equivalent dose. 
The Equivalent dose is the sum of the weight of the organ times the organ's absorbed dose. We
don't care so much about that so we are just going to assume H\_T = D. That is the absorbed dose,
grays, absorbed. We know that one gray is a joule per kilogram or 100 rad. So from here we can 
back out our effective dose. 
```
E = sum(w_p * D)
```
So in the Stepping Action we are able to grab the mass of the detector (in this case 800kg) and
we will use the energy of the particle. So for each event (each time something happens: particle
splits, decay, strike, etc) we get the total energy deposited in the detector. Remember here that
GEANT4 uses units, so we divide those out. We then convert from MeV to Joules (we're being 
explicit). We also want to make sure that we are not counting non-ionizing radiation, as that 
does not get counted in the dosage. We then figure out which particle is depositing the energy
and apply the correct weight. We give a warning at the end in case we don't know the particle and
do not apply any weight. If you want to use fission fragments or other things you will have to
add them manually. Finally we add our effective dosage to the event. You will notice that we 
add specifically what each particle's dose is (we do not call this out in the end of our run but
this is left as an exercise). 

We will next move to EventAction. Here we output the total energy deposits and effective dosages
at the end of each event. We also add this to the effective dosage in RunAction. You need to do
this if you want to get the total effective dosage at the end of the run. You will see these
numbers at the end of the run and you can add them to verify that you are getting the correct
effective dosage. We output the energy so the same can be done there too.

Finally we'll run the program and turn the beam on. You will notice that the total dosage in the
plate and the effective dosage is the same. This is to be expected because we are firing gammas
and you will notice that the only secondaries created are betas, which have a weight of 1. To
check that we did this all correctly we'll switch the gun to fire protons and up the energy to
100 MeV so we can hit the plate (remember we programmed these into the menu). You will notice no
secondaries and that effective dosage is twice that of the total deposited dosage. We have again
verified that we did things correctly (and that total dosage doesn't account for weight) because
protons have a weight of 2. 

## Minor Changes made
---------------------
We included the options to run multiple macros at once. Try this out by running

`./tutorial5 run1.mac run2.mac`

You will notice that the output becomes cumbersome. I left the output to illustrate this point and let the reader
experiment with multithreaded options in this configuration (See Example B3's main file). 

We also moved the material definition outside of the DetectorContruction file. You can also do this as a class,
but it is simple to do as a standard header file. If you have a more complex geometry and material list this
will be suggested as it makes reading the code easier. Remember, GEANT4 is just C++, so we can do anything that we
normally would do there here. 
