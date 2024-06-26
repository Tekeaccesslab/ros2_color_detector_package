# ros2_color_detector_package
This package turns detected blue pixels into red by detecting blue color in an image captured by a webcam. 
The webcam camera's Frame is captured by the Python program and published as /webcam/image_raw. Subject: Including the current time in the picture 
The C++ package will Subscribe to this Topic and Detects only the blue color 

# Dependencies
  * Ros2 humble
  * Opencv
  * Cv_bridge
  * Image_transport

# Building the Webcam Node
  Follow the steps below to build the project:

<button class="btn" data-clipboard-target="#code-snippet"></button>

<pre>
<code>
git clone https://github.com/Tekeaccesslab/ros2_color_detector_package.git
</code>
</pre>


<button class="btn" data-clipboard-target="#code-snippet"></button>

<pre>
<code>
cd access_ws/
colcon build
</code>
</pre>

<button class="btn" data-clipboard-target="#code-snippet"></button>

<pre>
<code>
. install/setup.bash
</code>
</pre>

And run 
<pre>
<code>
ros2 launch cpp_launch launch.py
</code>
</pre>


Will display

<pre>
<code>
accesslabros2@accesslabros2:~/access_ws$ ros2 launch cpp_launch launch.py
[INFO] [launch]: All log files can be found below /home/accesslabros2/.ros/log/2023-10-26-11-42-17-741469-accesslabros2-34106
[INFO] [launch]: Default logging verbosity is set to INFO
[INFO] [color_filter-1]: process started with pid [34107]
[INFO] [webcam_driver-2]: process started with pid [34109]
[webcam_driver-2] [INFO] [1698334938.622328104] [webcam_image_publisher]: Publishing video frame
[webcam_driver-2] [INFO] [1698334938.630429642] [webcam_image_publisher]: Publishing video frame
[webcam_driver-2] [INFO] [1698334938.664125898] [webcam_image_publisher]: Publishing video frame
[webcam_driver-2] [INFO] [1698334938.737682443] [webcam_image_publisher]: Publishing video frame
[webcam_driver-2] [INFO] [1698334938.837957318] [webcam_image_publisher]: Publishing video frame
[webcam_driver-2] [INFO] [1698334938.937327735] [webcam_image_publisher]: Publishing video frame
[webcam_driver-2] [INFO] [1698334939.036417684] [webcam_image_publisher]: Publishing video frame
[webcam_driver-2] [INFO] [1698334939.137448575] [webcam_image_publisher]: Publishing video frame
[webcam_driver-2] [INFO] [1698334939.236349191] [webcam_image_publisher]: Publishing video frame
</code>
</pre>

![Blue_2_Red](https://github.com/Tekeaccesslab/ros2_color_detector_package/assets/146024181/c199fae7-aad8-45a4-a72b-7430793dd469)




