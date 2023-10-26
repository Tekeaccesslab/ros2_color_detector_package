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
  * Clone the repository and go to the newly created directory:
    git clone https://github.com/Tekeaccesslab/ros2_color_detector_package.git

    cd access_ws

    colcon build
git clone https://github.com/antmicro/ros2-camera-node.git
cd ros2-camera-node/




<script src="https://cdnjs.cloudflare.com/ajax/libs/clipboard.js/2.0.8/clipboard.min.js"></script>

<pre>
<code id="code-snippet">
git clone https://github.com/antmicro/ros2-camera-node.git
</code>
</pre>

<button class="btn" data-clipboard-target="#code-snippet">Copy</button>

<script>
var clipboard = new ClipboardJS('.btn');

clipboard.on('success', function(e) {
    e.clearSelection();
});
</script>

<style>
.btn {
    background-color: #0074d9;
    color: white;
    border: none;
    border-radius: 4px;
    padding: 5px 10px;
    cursor: pointer;
}
</style>
