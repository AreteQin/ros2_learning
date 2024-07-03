// subscribe to gps and image data
// and use approximate time synchronization
//
// Created by qin on 2/29/24.
//

#include <iostream>
#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <vision_msgs/msg/detection2_d_array.hpp>
#include <message_filters/time_synchronizer.h>
#include <message_filters/subscriber.h>
#include <glog/logging.h>
#include <image_transport/image_transport.hpp>
#include <geometry_msgs/msg/pose_array.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <message_filters/sync_policies/approximate_time.h>

using namespace std;

void
ImageGpsCallback(const sensor_msgs::msg::Image::ConstSharedPtr& msg,
                 const sensor_msgs::msg::NavSatFix::ConstSharedPtr& msg_drone_GPS)
{
    cout << "ImageGpsCallback" << endl;
    // print GPS data
    cout << "GPS: " << msg_drone_GPS->latitude << ", " << msg_drone_GPS->longitude << endl;
    // show image
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
        RCLCPP_ERROR(rclcpp::get_logger("cv_bridge"), "cv_bridge exception: %s", e.what());
        return;
    }
}

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);

    auto node = rclcpp::Node::make_shared("fire_localization");
    // set image_transport parameter to "compressed"
    node->declare_parameter<std::string>("image_transport", "compressed");

    // message filter for images
    image_transport::ImageTransport it(node);
    message_filters::Subscriber<sensor_msgs::msg::Image> sub_image
        (node, "/dji_osdk_ros/main_wide_RGB");
    message_filters::Subscriber<sensor_msgs::msg::NavSatFix> sub_drone_GPS
        (node, "/dji_osdk_ros/gps_position");

    // Sync the subscribed data
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::msg::Image,
                                                            sensor_msgs::msg::NavSatFix> approximate_policy;
    message_filters::Synchronizer<approximate_policy> syncApproximate(approximate_policy(100),
                                                                      sub_image,
                                                                      sub_drone_GPS);
    syncApproximate.setMaxIntervalDuration(rclcpp::Duration(3, 0));
    syncApproximate.registerCallback(std::bind(std::placeholders::_1, std::placeholders::_2));

    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}
