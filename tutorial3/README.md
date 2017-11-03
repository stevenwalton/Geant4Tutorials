# Tutorial 3: Counting dose through a flux field

So running the last tutorial you will see that we just have a Geantino passing through the box. Now we want to use a different particle and get some interactions

What we changed
-----------
In this tutorial we have changed our firing particle to a gamma ray.  

We need to add a lot more here with the ActionInitialization, Run, RunAction, and Stacking Action files. With these we are initializing the run a different way (see change to the main file). The Stacking Action file is especially important if you don't want to track neutrinos. In beta decays we get neutrinos/antineutrinos. Generally we won't want to track these because they don't really interfere with people or objects. Since we are looking for radiation dosages we just want to free up computer time and delete these as soon as they appear. If you are following along to the changes I'm making from B3 you will notice that they track "good" events. Since they are concerned with the positron-electron annihilation they want to see productions that are exactly 511keV and they specify this. It is good to pay attention to how they do this, if you are looking for specific applications (like a PET scan).

I also introduced a macro, called `run.mac`. You can see the change made in the main file. We check `argc` (that is if there are arguments passed to the run command, eg `./tutorial3 run.mac`) and if so, we have it run the command. See the if/else statement that checks if `ui` is not 0.

Play around
-------------
Play around with the vis manager here's some things you should practice.

- Change the gun energy
``` 
  /gun/energy 50 MeV
```
- Change the gun particle
```
  /gun/particle e+
```
If you type in an invalid particle you will get the full list of particles. 
It is also available in [chapter 5.3](http://geant4.cern.ch/G4UsersDocuments/UsersGuides/ForApplicationDeveloper/html/TrackingAndPhysics/particle.html)
- Change the viewing angle

- Make the box empty and fire a gamma at the water target. What happens? 

- Make both the box and the water a detector and see the different dosages each take.

