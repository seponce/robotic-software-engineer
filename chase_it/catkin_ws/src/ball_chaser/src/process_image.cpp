#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ROS_INFO_STREAM("Drive robot to white ball");

    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    // Call the safe_move service and pass the requested joint angles
    if (!client.call(srv))
        ROS_ERROR("Failed to call service drive_robot");

}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
    int white_pixel = 255;

    // Loop through each pixel in the image and check if its equal to the first one
    int size_image = img.height * img.step;
    float left = (float)size_image / 3;
    float mid = (float)size_image / 2;
    float right = (float)size_image;

    float lon_x = 0.0;
    float ang_z = 0.0;

    for (int i = 0; i < size_image; i++) {

        if (img.data[i] == white_pixel) {
            ROS_INFO_STREAM("white identified!");

            // Depending on the white ball position, call the drive_bot function and pass velocities to it
            // mid / forward
     	    if (i > left && i < right){
	       ROS_INFO_STREAM("forward to ball");
               lon_x = 0.5;
               ang_z = 0.0;
	       break;
	    }
	    // left
            else if (i <= left){
               ROS_INFO_STREAM("left to ball");
	       lon_x = 0.0;
               ang_z = 0.5;	       
 	       break;
            }
            // right
            else if (i >= right){
               ROS_INFO_STREAM("right to ball");
               lon_x = 0.0;
	       ang_z = -0.5;	       
	       break;
            }
        }
    }

    if (lon_x == 0.0 && ang_z == 0.0){
      ROS_INFO_STREAM("stop robot");
      drive_robot(lon_x, ang_z);
    }else{
      drive_robot(lon_x, ang_z);
    }
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
