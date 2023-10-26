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


<pre>
<code id="code-snippet">
git clone https://github.com/antmicro/ros2-camera-node.git
cd access_ws

</code>
</pre>

<button class="btn" data-clipboard-target="#code-snippet">Copy</button>

<script>
var clipboard = new ClipboardJS('.btn');

clipboard.on('success', function(e) {
    e.clearSelection();
});
</script>


