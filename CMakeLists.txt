cmake_minimum_required(VERSION 2.8.3)
project(camera_model)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -fPIC")


find_package(Boost REQUIRED COMPONENTS filesystem program_options system)
include_directories(${Boost_INCLUDE_DIRS})

find_package(OpenCV REQUIRED)


find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})


find_package(Eigen3 REQUIRED)
include_directories(
  ${EIGEN3_INCLUDE_DIRS}
)


include_directories("include")


FILE(GLOB CamodocalCameraModelSources
        src/chessboard/Chessboard.cc
        src/calib/CameraCalibration.cc
        src/camera_models/Camera.cc
        src/camera_models/CameraFactory.cc
        src/camera_models/CostFunctionFactory.cc
        src/camera_models/PinholeCamera.cc
        src/camera_models/CataCamera.cc
        src/camera_models/EquidistantCamera.cc
        src/camera_models/ScaramuzzaCamera.cc
        src/sparse_graph/Transform.cc
        src/gpl/gpl.cc
        src/gpl/EigenQuaternionParameterization.cc
    )



add_executable(Calibration
    src/intrinsic_calib.cc
    ${CamodocalCameraModelSources}
    )

add_executable( prog1
    examples/1_readcamera_from_yaml.cpp
    ${CamodocalCameraModelSources}
    )

add_executable( prog2
    examples/2_readcamera_from_scratch.cpp
    ${CamodocalCameraModelSources}
    )

#add_library(camera_model
#    src/chessboard/Chessboard.cc
#    src/calib/CameraCalibration.cc
#    src/camera_models/Camera.cc
#    src/camera_models/CameraFactory.cc
#    src/camera_models/CostFunctionFactory.cc
#    src/camera_models/PinholeCamera.cc
#    src/camera_models/CataCamera.cc
#    src/camera_models/EquidistantCamera.cc
#    src/camera_models/ScaramuzzaCamera.cc
#    src/sparse_graph/Transform.cc
#    src/gpl/gpl.cc
#    src/gpl/EigenQuaternionParameterization.cc)

target_link_libraries(Calibration ${Boost_LIBRARIES} ${OpenCV_LIBS} ${CERES_LIBRARIES})

target_link_libraries(prog1 ${Boost_LIBRARIES} ${OpenCV_LIBS} ${CERES_LIBRARIES})
target_link_libraries(prog2 ${Boost_LIBRARIES} ${OpenCV_LIBS} ${CERES_LIBRARIES})

#target_link_libraries(camera_model ${Boost_LIBRARIES} ${OpenCV_LIBS} ${CERES_LIBRARIES})
