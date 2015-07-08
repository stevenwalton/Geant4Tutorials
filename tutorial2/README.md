# Tutorial 2: Visualization
In this tutorial we make it possible to visualize the trajectory of the Geantino that we are firing (a noninteracting particle used for testing).

I use the OpenGL library to visualize this, if you do not have this library then please see the User's Guide, or look at one of the other examples (vis.mac) to see how they use another driver. Remember to make sure that Geant has that library turned on. Remember that you can always go back to the build library and cmake with new flags.

What's new in this tutorial
---------------------
In this tutorial we have changed our CMakeLists.txt file and added init vis.mac and vis.mac files to open the visualizer.

I do get a weird memory error when running OGL, so what I do to work around this is just give it a memory with a large number.
