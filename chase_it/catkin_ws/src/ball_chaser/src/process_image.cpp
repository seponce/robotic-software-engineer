#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
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
    float part = (float)img.step / 3;
    int section = 0;
    int left = 0;
    int mid = 0;
    int right = 0;
  
    for (int i=0; i < img.height * img.step; i+=3){
	if (img.data[i] == white_pixel && img.data[i+1] == white_pixel && img.data[i+2] == white_pixel){
	    section = i % img.step;

            // Depending on the white ball position, call the drive_bot function and pass velocities to it
            // mid / forward
            if (section >= part && section < (2*part)){
               mid++;
            }
            // left
            else if (section < part){
               left++;
            }
            // right
            else if (section >= (2*part)){
               right++;
            }
	}
    }

    if (left > mid && left > right){
       drive_robot(0.2, 0.5);
    }else if (mid > left && mid > right){
       drive_robot(0.2, 0.0);
    }else if (right > left && right > mid){
       drive_robot(0.2, -0.5);
    }else{
      drive_robot(0.0, 0.0);
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
