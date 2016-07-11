# First thing first
---
Once you have Geant4 installed this is the first place that you should start. Before 
you start creating simulations it is important that we know how to build some of the
examples. So first we want to find the example directory. This will be in your 
geant4-install path/share/Geant4.version/examples/basic

Once we are there make a new directory called `B1-build`, or whatever you want to call 
it. Move into that directory then run
```
cmake ../B1
make -j6
./example1
```
You should now be running the first Geant4 example and see something like this
![B1 example image](http://i.imgur.com/8AW9itx.png)
This is using the QT visualization tools, and if you have something different that is
okay as long as you see something.

Now we want to run a simulation. So in the section where it says "Session" type
`/run/beamOn 10` where this simulates the run of 10 gamma beams coming in from the 
left side. This is a uniform distribution from the yz plane at the most -x point in our
world. Checkout `foo/basic/B1/src/B1PrimaryGeneratorAction.cc` to see how this was
created.
On the output you will see the total radiation accumulated in the volume, see B1RunAction.cc
for more details.

We can also change the particle type by running `/gun/particle e-`, changing it to an
electron. Running another 10 particles we can see a lot more yellow dots and that all
the green lines begin with a red section (with more yellow dots). The yellow dots 
represent an interaction of some kind. The colour of the beam indicated its charge. 
Red indicated a negative charge, green a neutral (so in this case a gamma ray) and blue
a positive charge (verify by switching to a positron, e+. And try a proton, proton).

You can also change the energy levels of the incident beam by running `/gun/energy 10 MeV`
And then rerun. 

It is good to check out the `vis.mac` and `run.mac` files in the B1 directory. `vis.mac`
will contain the initial commands for the setup. Including how the camera is oriented, 
axes, text, and more. The `run.mac` file contains a macro for running the program. If
you just want results and no visualizations you can just run `./exampleB1 run1.mac` and
it will run the commands listed in the file for you. This is extremely useful if you
need to run bigger tests. If you will be outputting a lot I suggest running something 
like `./exampleB1 run1.mac | tee output.txt` which will save all the output that goes
to the screen also in a file called `output.txt`. 

I suggest that you look through the basic examples to see how everything is created. 
These are some of the simpler geometries and scenarios that can be created.
