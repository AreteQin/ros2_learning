cmake_minimum_required(VERSION 3.8)
project(ros2_learning)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules) # Add elements to list

find_package(OpenCV 4 REQUIRED)
#find_package(Sophus REQUIRED)
#find_package(Pangolin REQUIRED) # used to show pointcloud
#find_package(CSparse REQUIRED)

#find_package(G2O REQUIRED)
#if (G2O_FOUND)
#    message(STATUS "G2O found. Version: ${G2O_VERSION}")
#endif (G2O_FOUND)

#find_package(Eigen3 REQUIRED)
#find_package(realsense2 REQUIRED)
#find_package(GLFW REQUIRED)
#find_package(Boost COMPONENTS system filesystem serialization REQUIRED)
#find_package(OpenMP REQUIRED)
#find_package(Ceres REQUIRED)

#find_package(PCL REQUIRED)
#include_directories(${PCL_INCLUDE_DIRS})
#add_definitions(${PCL_DEFINITIONS})

# ROS support
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)
find_package(message_filters REQUIRED)
find_package(vision_msgs REQUIRED)
find_package(Glog REQUIRED)

#if (OPENMP_FOUND)
#    message(STATUS "OpenMP found will try to link!")
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
#endif ()

include_directories(
        ${OpenCV_INCLUDE_DIRS}
#        ${G2O_INCLUDE_DIRS}
#        ${Sophus_INCLUDE_DIRS}
#        ${EIGEN3_INCLUDE_DIR}
        #        "/usr/include/eigen3/"
#        ${Pangolin_INCLUDE_DIRS}
#        ${CSPARSE_INCLUDE_DIR}
#        ${REALSENSE_INCLUDE_DIR}
        #        ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}
        #        ${GLFW_INCLUDE_DIRS}
        #        ${Boost_INCLUDE_DIR}
        #        ${CERES_INCLUDE_DIRS}
)

add_executable(ros2_test src/ros2_test.cpp
)
target_link_libraries(ros2_test
        ${GLOG_LIBRARIES}
)
ament_target_dependencies(ros2_test
        rclcpp
        sensor_msgs
        message_filters
        vision_msgs
        image_transport
        cv_bridge
)

ament_package()