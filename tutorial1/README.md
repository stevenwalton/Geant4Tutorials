# Tutorial 1
It is important to note that we do not want to cmake our tutorials in the source directory. Thus we create the build directory and cmake from there. 

If you are in tutorial-build, then you can run the command
```
    cmake ../tutorial1
```
Then you will want to make the file, which can be done with
```
    make -j#
```
Where you want to replace "#" with the number of processors you want to make with. In these tutorials you don't really have to use the j flag because the programs are simple, but it is good to know for later when you master Geant and you need to make larger programs.

What is in this tutorial
------------------------
We go through (almost) the MOST basic example I can think of making. The files we need are

- main.cpp
- DetectorConstruction
- PhysicsList
- PrimaryGeneratorAction
- CMakeLists.txt

Note that these files are MANDATORY! You can combine all the c++ files together, but it is not suggested, stay organized.

In our DetectorConstruction file you will see how we define materials (multiple ways), and create a world box as well as a small physical box inside. We are filling the entire world with Air and the box with water.

Tips for playing around
-------------
Remember that cout and endl in geant are G4cout and G4endl. 
- Try to figure out how to print the materials table. 
- Why did I comment out the liquid Argon? Is it a problem if you don't?
- See if using `G4UniformRand()` you can make the beams come from an incident plane instead of a point.
