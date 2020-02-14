Study of vertex activity in sFGD simulation, for both voxels and hits.

## How to use
Download software from https://github.com/t2k-nd280-upgrade/t2k-nd280-upgrade </br>

Replace **SFGD_Reconstruction.cc** in `/t2k-nd280-upgrade/src/app/Reconstruction/src/` </br>
Replace **submit_nd280upgrade_targetreco** in `/t2k-nd280-upgrade/src/app/Reconstruction/submit_nd280upgrade_targetreco/` </br>

both are in src </br>

Macros VertexActivity.cc, DynamicVertexActivity.cc and vertexHitA.cc uses different software called **sfgd_framework**.

## Macros description
1. VertexActivity.cc - Main study uses Voxels
2. vertexHitA.cc - Uses 2D hits, side project
3. DynamicVertexActivity.cc - Side project, uses voxels as 1st. but VA boxes are assymetric.
