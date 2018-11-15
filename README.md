part of [camodocal](https://github.com/hengli/camodocal)

## Required
[Google Ceres](http://ceres-solver.org)
[Eigen3](http://eigen.tuxfamily.org/index.php?title=Main_Page)
[OpenCV 3](https://www.opencv.org/)
[Boost](https://www.boost.org/)

## How to compile (Standalone)
```
mkdir build
cmake ..
make
```

It is very easy to adapt this into your own projects. You will need
to copy the `include` and `src` directories to your project and
edit your cmake files accordingly. Look at my cmake file to know how to do it. 

## Calibration:

Use [intrinsic_calib.cc](src/camera_models/intrinsic_calib.cc) to calibrate your camera.

## Undistortion / Geometry:

See [Camera.h](include/camodocal/camera_models/Camera.h) for general interface:

 - liftProjective: Lift points from the image plane to the projective space.
 - spaceToPlane: Projects 3D points to the image plane (Pi function)

## Examples
Example usage of camodocal by mpkuse.

- *1_readcamera_from_yaml.cpp*: How to initialize CameraPtr with yaml file.
