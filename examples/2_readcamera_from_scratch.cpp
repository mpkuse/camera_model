#include <iostream>
#include <string>
#include <vector>

#include "camodocal/camera_models/Camera.h"
#include "camodocal/camera_models/CameraFactory.h"


int main()
{
    camodocal::CameraPtr cam;
    cam = camodocal::CameraFactory::instance()->generateCamera( camodocal::Camera::PINHOLE, "my_camera", cv::Size(480,640) );
    std::vector<double>parameterVec;
    cam->writeParameters( parameterVec );
    parameterVec[4] = 481.20; //fx
    parameterVec[5] = 480.; //fy
    parameterVec[6] = 319.50; //cx
    parameterVec[7] = 239.50; //cy
    cam->readParameters( parameterVec );
    std::cout << "Cam:\n" << cam->parametersToString() << std::endl;

}
