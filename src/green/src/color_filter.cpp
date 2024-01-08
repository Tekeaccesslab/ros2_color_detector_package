
//  North Carolina A&T University
//  AccessLab ros2 project 
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "std_msgs/msg/header.hpp"
#include <chrono>
#include <ctime>
#include <cv_bridge/cv_bridge.h> // cv_bridge converts between ROS 2 image messages and OpenCV image representations.
#include <image_transport/image_transport.hpp> // Using image_transport allows us to publish and subscribe to compressed image streams in ROS2
#include <opencv2/opencv.hpp> 

 
using namespace std::chrono_literals;
class ImageColorFilterNode : public rclcpp::Node {
public:
    ImageColorFilterNode() : Node("image_color_filter") {

        // Change the QoS here, this case Reliability changed from Relaible default to BEST_EFFORT as per the Requirement
        rclcpp::QoS custom_qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
        custom_qos_profile.reliability(rmw_qos_reliability_policy_t::RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);

        subscription_ = create_subscription<sensor_msgs::msg::Image>(
            "webcam/image_raw", custom_qos_profile,
            [this](const sensor_msgs::msg::Image::SharedPtr msg) {
                processImage(msg);
            });

        declare_parameter<int>("color_threshold", 100);
        get_parameter("color_threshold", color_threshold_);

        // declared parameters for lower_Blue in HSV to add parameters from launch
        declare_parameter<int>("h_low", 0);
        declare_parameter<int>("s_low", 0);
        declare_parameter<int>("v_low", 0);
       // declared parameters for upper_Blue in HSV
        declare_parameter<int>("h_high", 0);      
        declare_parameter<int>("s_high", 0);       
        declare_parameter<int>("v_high", 0);
        // Get H,S and V for lower and higher Blue
        get_parameter("h_low", h_low);
        get_parameter("s_low", s_low);
        get_parameter("v_low", v_low);

        get_parameter("h_high", h_high);
        get_parameter("s_high", s_high);       
        get_parameter("v_high", v_high);

    }

private:
    void processImage(const sensor_msgs::msg::Image::SharedPtr msg) {
        cv_bridge::CvImagePtr cv_ptr;
        // cv_bridge::CvImagePtr cv_ptr2;
        try {
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_8UC3);
            // cv_ptr2 = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_8UC3);
        } catch (cv_bridge::Exception& e) {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
            return;
        }

    cv::Mat hsvImage;
    cv::cvtColor(cv_ptr->image, hsvImage, cv::COLOR_BGR2HSV);

    // Define the lower and upper bounds for blue color in HSV
    // cv::Scalar lowerBlue = cv::Scalar(100, 50, 50);
    // cv::Scalar upperBlue = cv::Scalar(140, 255, 255);

    //Get the lower and upper bounds for blue color in HSV from launch
    cv::Scalar lowerBlue = cv::Scalar(h_low, s_low, v_low);
    cv::Scalar upperBlue = cv::Scalar(h_high, s_high, v_high);
    // Threshold the image to detect blue color
    cv::Mat blueMask;
    cv::inRange(hsvImage, lowerBlue, upperBlue, blueMask);

    // Bitwise AND the original image and the mask to get the blue regions
    cv::Mat blueRegions;
    cv::bitwise_and(cv_ptr->image, cv_ptr->image, blueRegions, blueMask);

    // Transform blue regions to red
    cv::Mat redRegions = blueRegions.clone();
    redRegions.setTo(cv::Scalar(0, 0, 255), blueMask);

    // Bitwise NOT the mask to get non-blue regions
    cv::Mat nonBlueMask;
    cv::bitwise_not(blueMask, nonBlueMask);

    // Bitwise AND the original image and the inverted mask to get non-blue regions
    cv::Mat nonBlueRegions;
    cv::bitwise_and(cv_ptr->image, cv_ptr->image, nonBlueRegions, nonBlueMask);

    // Combine red and non-blue regions to get the final image
    cv::Mat result;
    cv::add(redRegions, nonBlueRegions, result);

    // Display the result
    cv::imshow("Original Image", cv_ptr->image);
    cv::imshow("Detected blue region", blueRegions);
    cv::imshow("Blue to Red changed part", result);
    cv::waitKey(30);
    
    }
    int h_low;
    int s_low;
    int v_low;

    int h_high;   
    int s_high;  
    int v_high;

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
    int color_threshold_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ImageColorFilterNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

