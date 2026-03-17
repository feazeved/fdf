This project has been created as part of the 42 curriculum by Felipe Suassuna.

FdF is a 3D terrain renderer that transforms 2D coordinate maps into interactive isometric projections. The project focuses on the graphics pipeline, linear algebra, and low-level performance optimization in a C environment. 

Matrix Transformations: Designed a rendering engine that applies rotation, scaling, and translation matrices to project raw data (up to 400x400 points) into 3D space. 

Optimized Algorithms: Implemented Bresenham’s and Xiaolin Wu’s line algorithms, optimized via direct pixel buffer manipulation for smooth frame rates. 

Real-Time Responsiveness: Managed window events and computational loads to ensure the renderer simulates high-performance dashboard instruments. 


Prerequisites: Requires MiniLibX (included or installed via system). 

Compilation: Run make.

Execution: ./fdf [path_to_map.fdf]
