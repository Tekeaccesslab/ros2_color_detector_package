from launch import LaunchDescription
from launch_ros.actions import Node
 
def generate_launch_description():
    ld = LaunchDescription()
     
    color_filter=Node(
         package="green",
         namespace='image_color_filter', # Make sure this matches the subscriber's namespace
         executable='color_filter', # Name of the executable
         name='image_subscriber' # Any name is fine
       )
    
    webcam_driver= Node(
         package="orange",
         namespace='webcam_image_publisher', # Make sure this matches the publisher's namespace
         executable='webcam_driver', # Name of the executable
         name='image_publisher' # Any name is fine
       )
   
    ld.add_action(color_filter)
    ld.add_action(webcam_driver)
    
    return ld