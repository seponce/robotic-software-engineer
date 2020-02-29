# Introduction to catkin
Basic commands to operate catkin on ROS

```sh
### create a catkin workspace and a sub directory
mkdir -p /home/workspace/catkin_ws/src
cd /home/workspace/catkin_ws/src

### initialize the catkin workspace
catkin_init_workspace

### return top-level directory
cd /home/workspace/catkin_ws

### build workspace
catkin_make

### cloning the simple_arm Package
cd /home/workspace/catkin_ws/src/
git clone -b first_interaction https://github.com/udacity/RoboND-simple_arm/ simple_arm

### building the simple_arm package
cd /home/workspace/catkin_ws/
catkin_make

### (Optional error in packages)
sudo apt-get install ros-kinetic-controller-manager

### ROS launch
cd /home/workspace/catkin_ws/
catkin_make
source devel/setup.bash
roslaunch simple_arm robot_spawn.launch

### ROS Package Dependencies
rosdep check <package 

### To have rosdep install packages, invoke the following command from the root of the catkin workspace
rosdep install -i <package name>

### simple_arm Package Dependencies
cd /home/workspace/catkin_ws/ 
source devel/setup.bash
rosdep check simple_arm

### Dive Deeper into Packages
cd /home/workspace/catkin_ws/src
catkin_create_pkg <your_package_name> [dependency1 dependency2 …]
catkin_create_pkg first_package
```

