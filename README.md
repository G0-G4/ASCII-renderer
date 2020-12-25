# ASCII-renderer

# is a simple renderer for windows terminal 

![teapot](images/teapot.png)
![cone](images/cone.png)
![cone1](images/cone1.png)

## controls:

* W A S D Q E for moving object
* Z X and arrows for rotating
* C V for scaling
* R for changing render type

to open an .obj file you can drag and drop it on .exe file or run the program from a terminal with a path to the model as
a comand line parameter.

## some issues:

* .obj file should contain only vertex and face data, all faces should be triangles.
* problems with loading some models, if they are not rotated (solving - rotate a model a little bit in a 3d editor)