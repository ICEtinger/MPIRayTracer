# distributed Ray Tracer tool with C++ and MPI

This project uses C++ with MPI to display a Ray Tracer image according to Phong's ilumination model and calculated in a distributed fashion. 
Additionally, it uses the OpenCV library to plot the images.

To choose a desired plotting situation, it suffices to change the camera, scene and lightSource functions at the main.cpp file (the ones currently written at the code serve as an example).
General documentation is provided in the header files. 
Low-level documentation of the main core of calculations is provided in the Ray.cpp file.

