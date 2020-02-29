# Introduction to ROS
Basic commands to operate ROS

```sh
### Starting the Master process in a separate terminal
roscore

### Execute diferents nodes
rosrun turtlesim turtlesim_node
rosrun turtlesim turtle_teleop_key

### List all nodes
rosnode list

### List all topics
rostopics list

### Get information about one topic
rostopic info /turtle1/cmd_vel

### Get information about message
rosmsg info geometry_msgs/Twist

### Echo message on topic
rostopic echo /turtle1/cmd_vel
```

