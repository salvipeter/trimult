# TriMultPoly

Ming Zou et al.'s [3D polygon triangulation software](https://www.cse.wustl.edu/~taoju/zoum/projects/TriMultPoly/index.html) compiled on Linux with CMake. Also includes Hang Si's [tetrahedral mesh generator](http://wias-berlin.de/software/index.jsp?id=TetGen&lang=1).

The changes are minimal:

- `Configure.h` has a few extra defines at the beginning of the file
- Windows-specific parts of `main.cpp` were omitted
