# Changes in Tutorial 6
------------------------
This tutorial is focusing on parallelization.

As simulations get much larger, we can't do very much on just one processor. We will actually be focusing on threading
our program. Through sources that you can find on the web, you will see that GEANT4 scales linearly with the number of processors
and continues to scale with more threads than processors. Though the latter is not as efficient. GEANT4 is highly parallelizable, 
and it is a good idea to do this in all the codes that you can.
