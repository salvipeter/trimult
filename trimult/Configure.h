// Added for compilation on Linux
#include <cstdint>
#define __forceinline
#define strcpy_s(dest,destsz,src) strcpy(dest,src)
#define strcat_s(dest,destsz,src) strcat(dest,src)
using __int64 = int64_t;

#define numResvOneTile 3300000
#define numResvTile 2400000
#define numResvHash 3300000
#define numResvTilling 200
#define MAXK 6

#define _SaveTetTri	0 // save tet triangles from tetgen
#define _SaveTile 1

#define hasTri false
#define doPause false
#define plainPTB 0.00000001
#define BADEDGE_LIMIT 30
#define hfPI 1.570796
