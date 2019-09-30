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



## USE:
Two main files for you to use camera model: [Camera.h](https://github.com/dvorak0/camera_model/blob/master/include/camera_model/camera_models/Camera.h) and [CameraFactory.h](https://github.com/gaowenliang/camera_model/blob/master/include/camera_model/camera_models/CameraFactory.h).
### 1.load in the camera model calibration file
Use function in [CameraFactory.h](https://github.com/gaowenliang/camera_model/blob/master/include/camera_model/camera_models/CameraFactory.h) to load in the camra calibration file:

```c++
#include <camera_model/camera_models/CameraFactory.h>

camera_model::CameraPtr cam;

void loadCameraFile(std::string camera_model_file)
{
    cam = camera_model::CameraFactory::instance()->generateCameraFromYamlFile(camera_model_file);
}

void makeFromScratch( )
{
    cam = camodocal::CameraFactory::instance()->generateCamera( camodocal::Camera::PINHOLE, "my_camera", cv::Size(480,640) );
    vector<double>parameterVec;
    cam->writeParameters( parameterVec );
    parameterVec[4] = 481.20; //fx
    parameterVec[5] = 480.; //fy
    parameterVec[6] = 319.50; //cx
    parameterVec[7] = 239.50; //cy
    cam->readParameters( parameterVec );
    cout << "Cam:\n" << cam->parametersToString() << endl;

    // Similarly other camera types can also be loaded from scratch,
    // just be careful on the ordering of the parameterVec, see relavant source code for details.
}
```

### 2.projection and back-projection point
See [Camera.h](https://github.com/dvorak0/camera_model/blob/master/include/camera_model/camera_models/Camera.h) for general interface:

Projection (3D ---> 2D) function:
[spaceToPlane](https://github.com/gaowenliang/camera_model/blob/master/calibrate_template/fisheye_calibration.sh) :Projects 3D points to the image plane (Pi function)

```c++
#include <camera_model/camera_models/CameraFactory.h>

camera_model::CameraPtr cam;

void loadCameraFile(std::string camera_model_file)
{
    cam = camera_model::CameraFactory::instance()->generateCameraFromYamlFile(camera_model_file);
}

void useProjection(Eigen::Vector3d P)
{
    Eigen::Vector2d p_dst;
    cam->spaceToPlane(P, p_dst);
}
```

Back Projection (2D ---> 3D) function:
[liftSphere](https://github.com/gaowenliang/camera_model/blob/master/calibrate_template/fisheye_calibration.sh):   Lift points from the image plane to the projective space.
```c++
#include <camera_model/camera_models/CameraFactory.h>

camera_model::CameraPtr cam;

void loadCameraFile(std::string camera_model_file)
{
    cam = camera_model::CameraFactory::instance()->generateCameraFromYamlFile(camera_model_file);
}

void useProjection(Eigen::Vector3d P)
{
    Eigen::Vector2d p_dst;
    cam->spaceToPlane(P, p_dst);
}

void useBackProjection(Eigen::Vector2d p)
{
    Eigen::Vector3d P_dst;
    cam->liftSphere(p, P_dst);
}
```

#### liftSphere
- liftProjective
- normalize vector

#### liftProjective
- K.inverse() * [ u;v;1]
- apply inverse distortion

#### spaceToPlace (Pi function)
- P := (X/Z, Y/Z)
- \pho := apply distortion to P
- K . \pho

#### lemma on spaceToPlane
=> if input to spaceToPlane is (u,v,1) instead of a real 3d point, it has the effect of applying distorion to this point, assuming the input (u,v,1) is normalized image co-ordinate


## Examples
Example usage of camodocal by mpkuse.

- *1_readcamera_from_yaml.cpp*: How to initialize CameraPtr with yaml file.
