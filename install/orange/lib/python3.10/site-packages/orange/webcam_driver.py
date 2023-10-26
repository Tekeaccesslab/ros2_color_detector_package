# Basic ROS 2 program to publish real-time streaming  video from your built-in webcam
  
# Import the necessary libraries
import rclpy # Python Client Library for ROS 2
from rclpy.node import Node # Handles the creation of nodes
from sensor_msgs.msg import Image # Image is the message type
from cv_bridge import CvBridge # Package to convert between ROS and OpenCV Images
import cv2 # OpenCV library
from rclpy.qos import QoSProfile
from std_msgs.msg import String
from rclpy.qos import QoSReliabilityPolicy
from rclpy.qos import QoSDurabilityPolicy
import time
# import os
# import numpy as np
# import matplotlib.pyplot as plt

# def load_images(paths: list[str]) -> tuple[list[NDArrayRGB], list[str]]: ...

class ImagePublisher(Node):
  """
  Create an ImagePublisher class, which is a subclass of the Node class.
  """
  def __init__(self):
    """
    Class constructor to set up the node
    """
    # Initiate the Node class's constructor and give it a name
    super().__init__('webcam_image_publisher')

    # qos_profile = self.new_default_qos_profile()
    # qos_profile.reliability = self.QoSReliabilityPolicy.BEST_EFFORT
    # qos_profile = self.QoSPresetProfiles.get_from_profile(QoSPresetProfiles.BEST_EFFORT)

    # publisher = node.create_publisher(String, "my_topic", qos_profile)
      
    # Create the publisher. This publisher will publish an Image
    # to the video_frames topic. The queue size is 10 messages.

    qos_profile = QoSProfile(
            reliability=QoSReliabilityPolicy.BEST_EFFORT,
            durability=QoSDurabilityPolicy.VOLATILE,
            depth=10  # Adjust the queue depth as needed
        )
    self.publisher_ = self.create_publisher(Image, 'webcam/image_raw', qos_profile)
    # self.publisher_ = self.create_publisher(Image, 'webcam/image_raw', 10)
      
    # We will publish a message every 0.1 seconds
    timer_period = 0.1  # seconds
      
    # Create the timer
    self.timer = self.create_timer(timer_period, self.timer_callback)
         
    # Create a VideoCapture object
    # The argument '0' gets the default webcam.
    self.cap = cv2.VideoCapture(0)
         
    # Used to convert between ROS and OpenCV images
    self.br = CvBridge()
   
  def timer_callback(self):
    """
    Callback function.
    This function gets called every 0.1 seconds.
    """
    # Capture frame-by-frame
    # This method returns True/False as well
    # as the video frame.
    ret, frame = self.cap.read()
          
    if ret == True:
      # Publish the image.
      # The 'cv2_to_imgmsg' method converts an OpenCV image to a ROS 2 image message
      current_time = time.time()
      frame = cv2.putText(frame, f"Time: {current_time:.2f}", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

      image_msg = self.br.cv2_to_imgmsg(frame, "8UC3") # frame is in opencv format so we need to change it to ros image tp publish as msg
      # image_msg = self.br.cv2_to_imgmsg(frame, "bgr8") # "8UC3" and "bgr8" are opencv Encoding Techniques
      image_msg.header.stamp = self.get_clock().now().to_msg()
            # image_pub.publish(image_msg)
      self.publisher_.publish(self.br.cv2_to_imgmsg(frame))
 
    # Display the message on the console
    self.get_logger().info('Publishing video frame')
  
def main(args=None):
  
  # Initialize the rclpy library
  rclpy.init(args=args)
  
  # Create the node
  
  image_publisher = ImagePublisher()
  
  
  
  # Spin the node so the callback function is called.
  rclpy.spin(image_publisher)
  
  # Destroy the node explicitly
  # (optional - otherwise it will be done automatically
  # when the garbage collector destroys the node object)
  image_publisher.destroy_node()
  
  # Shutdown the ROS client library for Python
  rclpy.shutdown()
  
if __name__ == '__main__':
  main()

