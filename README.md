# Geant4Tutorials
============================
Geant4 tutorials made by Steven Walton:

I will be making videos for these at well. 
We will go through tutorials and build our first Geant4 application, step by step
First we will get a basic geometry, then get a visualization where we can run a beam through it, then we will focus on the physics

--------------------------------------
I am not an expert at Geant, this is both to help me learn and to help others that have the same problems as me. I welcome emails from others that would like to correct me and help with this. I am doing this because most of the information on Geant I see out there suggests that one should just review the examples and just dive in to making an application from there.

It is my belief that one should be able to see and make and understand what is the bare
essentials before building more complex ones. Going through the examples there are a 
lot of different ways of doing things and I am trying to piece together the parts from
the [Geant4 User's Guide] (can be found at http://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/ForApplicationDeveloper/fo/BookForAppliDev.pdf). Please reference this material, as it has much more information than I will include. The point of this is just to get your feet wet.

Install Guide
--------------
[Install Guide and Options](http://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/InstallationGuide/fo/BookInstalGuide.pdf)

Remember that if you would like to add more options (such as data, graphics libraries, or multithreading) you can just run the cmake in your build directory and add them. 

Standard Options are located on page 17 of this document (section 2.3.1). Please read it

Suggested Install
----------------------
If you have separate root and home partitions you may want to check where you are installing to and make sure you have enough room.
Follow the instruction document, but I use the following cmake command.

```
cmake -DCMAKE_INSTALL_PREFIX=/path/to/geant4-install_dir -DGEANT4_BUILD_MULTITHREADED=ON -DGEATN4_INSTALL_DATA=ON -DGEANT4_USE_GDML=ON -DGEANT4_USE_XM=ON -DGEANT4_USE_RAYTRACER_X11=ON -DGEANT4_USE_QT=ON -DGEANT$_USE_OPENGL_X11=ON /path/to/geant4.10.version.number
```
I have had some bugs when building and pointing to where the installed data is, so I 
suggest just letting Geant4 download the data for you.
I also like using the QT visualization tools as it seems to work better with Ubuntu 16.
I found when building with the other visualizers that I would have problems, and the QT
version allows you to move the camera without having to manually set it. This can save 
some time if you need to view multiple angles. 

Next we continue with the make
```$ make -j6```

This makes the build with 6 processors, replace 6 with the number of processors you
want to use (suggested max being 1 less than the number of threads you have)

```# make install```

Use sudo for this if you are installing to `/opt`, but you don't need sudo if you are 
building into the home directory.

Remember if you want to add additional D flags you can always remake the build. 
