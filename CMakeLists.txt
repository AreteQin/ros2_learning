cmake_minimum_required(VERSION 3.5)
project(temp_sync)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(message_filters REQUIRED)

add_executable(syncer src/ros2_test.cpp)
ament_target_dependencies(syncer rclcpp sensor_msgs message_filters)

install(TARGETS syncer
        DESTINATION lib/${PROJECT_NAME})

ament_package()