#include <iostream>
#include <string>

#include "camodocal/camera_models/Camera.h"
#include "camodocal/camera_models/CameraFactory.h"


int main()
{
    // std::string calib_file = "../examples/sample_kannala_brandt.yaml";
    std::string calib_file = "../examples/sample_pinhole.yaml";

    camodocal::CameraPtr m_camera;
    std::cout << ((m_camera)?"cam is initialized":"cam is not initiazed") << std::endl; //this should print 'not initialized'

    m_camera = camodocal::CameraFactory::instance()->generateCameraFromYamlFile(calib_file);
    std::cout << ((m_camera)?"cam is initialized":"cam is not initiazed") << std::endl; //this should print 'initialized'

    // Inbuild function for priniting
    std::cout << m_camera->parametersToString() << std::endl;

    // Custom priniting info
    std::cout << "imageWidth="  << m_camera->imageWidth() << std::endl;
    std::cout << "imageHeight=" << m_camera->imageHeight() << std::endl;
    std::cout << "model_type=" << m_camera->modelType() << std::endl;
    std::cout << "camera_name=" << m_camera->cameraName() << std::endl;

}
