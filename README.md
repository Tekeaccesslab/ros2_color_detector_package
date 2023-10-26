# ros2_color_detector_package
This package detects blue colors from frame from webcam camera and change the detected blue pixels to red. 
The Python python package capture Frame from our webcam camera and publish it as /webcam/image_raw Topic  Adding the current time on the image 
The C++ package will Subscribe to this Topic and Detects only the blue color 

# Dependencies
  * ROS2 HUMBLE
  * OPENCV
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




