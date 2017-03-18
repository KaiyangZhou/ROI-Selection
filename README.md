# Depth-Based ROI Selection
## Overview
This is the ROI selection method used in the paper[Detecting Humans in RGB-D Data with CNNs](https://kaiyangzhou.github.io/files/MVA17.pdf). It reduces the search space in an image and produces a set of square proposals. It was particularly designed for human upper body detection, but it can be modified to suit object detection as well.

## How to use
1. in command line run `git clone https://github.com/KaiyangZhou/ROI_Selection.git`
2. `cd` to the **ROI_Selection** directory and run `matlab` (if you have installed)
3. run `build()` to generate **mex** files
4. run `demo()` to see what happens

`img.mat` contains a color image and an aligned depth image (unit in meters), which are obtained from [RGBD people dataset](http://www2.informatik.uni-freiburg.de/~spinello/RGBD-dataset.html).

Core functions are enclosed in `functions/roi_selection.m`. For detailed descriptions, please refer to [our paper](https://kaiyangzhou.github.io/files/MVA17.pdf).

If you have any questions regarding these codes, please do not hesitate to contact me: `kaiyangzhou92@gmail.com`

## Reference
```
@inbook{kzhou2017humandetect,
title = {Detecting Humans in RGB-D Data with CNNs},
author = {Kaiyang Zhou and Adeline Paiement and Majid Mirmehdi},
year = {2017},
month = {2},
booktitle = {IAPR Conference on Machine Vision Applications (MVA2017)},
}
```
