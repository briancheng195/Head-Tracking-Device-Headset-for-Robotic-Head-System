# Head-Tracking-Device-Headset-for-Robotic-Head-System

This project is a further continuation on my internship project, the Development of Advanced Intelligent Manipulation (AIM), where I further utilised the GY-85 9 DOF IMU sensor in measuring the roll angle. 

With the calculation of the yaw, pitch and roll angles of the IMU sensor, this provides greater accuracy for the robotic head system to mimic the head movements of the user.

Thus, I also designed a CAD model of a pan-tilt-roll system with SolidWorks, so as to improve the design of the robotic head system by providing it with a greater range of freedom in movement. 

# Robotic Head Tracking Device
- Contains the GY-85 9DOF IMU (in-built acccelerometer, gyrometer and magnetometer)
- Using the accelerometer, able to determine the pitch angle based on calculating the angle from the change in acceleration in the x and z-directions as the IMU   sensor is tilted upwards/downwards (pitch movement)
- Using the accelerometer, able to determine the roll angle based on calculating the angle from the change in acceleration in the y and z-directions as the IMU    sensor is tilted rightwards/leftwards (roll movement)
- Using the magnetometer, able to determine the yaw angle based on calculating the angle from the change in magnetic field strength in the x and y-directions as   the IMU sensor is rotated clockwise/anticlockwise (yaw movement)
- Data (pitch and yaw values) are transmitted through radio (using the nRF2401L module) to the robotic head system
- A 3-D printed headset is created to store the head tracking device and for the user to wear the headset to control the robot's head movements

# Robotic Head System
- It acts as the receiver as the microcontroller receives the pitch and yaw data from the head tracking device (using the nRF2401L module)
- The microcontroller processes the pitch and yaw data and maps them to degree values, in order to control two 180 degree posiitonal servo motors (one for each   movement) respectively
- The servo motors are set up in a pan-tilt mount system to mimic the head movements of the user

# Vision of the Robotic Head System
- A Intel RealSense Depth Camera (D415) provides the vision for the robotic head. A 3-D printed casing is created to attach the depth camera on the pan-tilt       mount system
- To remotely stream the depth camera footage, the camera is connected to a single board computer (Raspberry Pi 4) with the camera packages and a VNC client       installed
- Any electronic devices (such as a smartphone) with the VNC viewer can access the depth camera footage remotely and the electronic device can be slotted inside   the headset
