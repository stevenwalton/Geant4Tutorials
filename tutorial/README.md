# Tutorial 1
It is important to note that we do not want to cmake our tutorials in the source directory. Thus we create the build directory and cmake from there. 

If you are in tutorial-build, then you can run the command
```
    cmake ../tutorial
```
Then you will want to make the file, which can be done with
```
    make -j#
```
Where you want to replace "#" with the number of processors you want to make with. In these tutorials you don't really have to use the j flag because the programs are simple, but it is good to know for later when you master Geant and you need to make larger programs.

What is in this tutorial
------------------------------------------------------
We go through (almost) the MOST basic example I can think of making. The files we need are

- main.cpp
- DetectorConstruction
- PhysicsList
- PrimaryGeneratorAction
- CMakeLists.txt

The geant files I will have a src folder for the *.cpp files and an include file for the *.hh files. You can combine the cpp and hh files if you want, but I suggest keeping organized. 

In our DetectorConstruction file you will see how we define materials (multiple ways), and create a world box as well as a small physical box inside. We are filling the entire world with Air and the box with water.
