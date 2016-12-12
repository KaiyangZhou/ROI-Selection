# Depth-Based ROI Selection
## Overview
This is an ROI selection method based on depth data. It reduces the search space in an image and produces a set of square proposals. It is particularly designed for human upper body detection, but it can be modified to suit object detection as well. Detailed description coming soon.

## How to use
1. in command line run `git clone https://github.com/KaiyangZhou/ROI_Selection.git`
2. `cd` to the **ROI_Selection** directory and run `matlab` (if you have installed)
3. run `build()` to generate **mex** files
4. run `demo()` to see what happens

`img.mat` contains a color image and an aligned depth image (in meters), which are obtained from [*RGBD people dataset*] (http://www2.informatik.uni-freiburg.de/~spinello/RGBD-dataset.html).

**Codes are well annotated so they are easy to read**

If you have any questions, please do not hesitate to contact me: `kaiyangzhou92@gmail.com`

## Reference
Coming soon ...
