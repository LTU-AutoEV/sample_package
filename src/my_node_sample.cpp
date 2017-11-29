#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

// Includes for working with images
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/highgui/highgui.hpp>

// Change this value if you are subscribing to a different camera
#define CAM_TOPIC "/camera_1/cam_pub/image_raw"
#define TWIST_PUB "/rb_drive/rb_drive/twist_cmd"

#define NODE_NAME "my_node_sample"

/**
 * SampleNode
 * =======================
 *
 */
class SampleNode
{
public:
    SampleNode();
    void imageCb(const sensor_msgs::ImageConstPtr& msg);

private:
    geometry_msgs::Twist computeTwist(const cv::Mat& src);

    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    ros::Publisher pub_;

};


/**
 * Constructor
 * ===========
 *
 * Do all initilization code here. This way, our main() function only
 *   needs to instantiate the SampleNode object once and do nothing
 *   else (see main() below).
 *
 * In this case, we only need to set up the image subscriber
 */
SampleNode::SampleNode()
    :nh_{"~"}, it_{nh_}
{
    // Subscribe to the camera publisher node
    image_sub_ = it_.subscribe(CAM_TOPIC, 1, &SampleNode::imageCb, this);

    // Publish on the l2bot twist command topic
    pub_ = nh_.advertise<geometry_msgs::Twist>(TWIST_PUB, 10);

}



/**
 * Callback function
 * =================
 *
 * Called once every time a image is published on the topic this
 *   node is subscribed to. The image is passed to the function as
 *   a ImageConstPtr
 */
void SampleNode::imageCb(const sensor_msgs::ImageConstPtr& msg)
{
    //Convert to cv image
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    // Compute how the l2bot should turn
    geometry_msgs::Twist twist = computeTwist(cv_ptr->image);

    // Publish the message
    pub_.publish(twist);
}


/**
 * Count White Pixels Example
 * ==========================
 * This function uses dynamic thresholding to binarize the imput image.
 * It then counts the number of white pixels and returns (#white)/(#total)
 *
 * https://docs.opencv.org/2.4/modules/imgproc/doc/miscellaneous_transformations.html?highlight=threshold
 */
geometry_msgs::Twist SampleNode::computeTwist(const cv::Mat& src)
{
    // Speed is any value from 0.0 to 3.0
    // 0.0 is stop, 3.0 is full speed
    double speed = 0.0;
    // Turn is any value from -2 to +2
    // 0.0 is no turn (straight)
    // -2 and +2 are sharp right and left turns
    double turn = 0.0;


    // Compute speed and turn

    // YOUR CODE HERE



    // Return a Twist message (don't change this)
    geometry_msgs::Twist msg;
    msg.linear.x  = speed;
    msg.angular.z = turn;
    return msg;
}




int main(int argc, char** argv)
{
    // Change "my_node_sample" to the name of your node 
    ros::init(argc, argv, NODE_NAME);

    // Create a SampleNode object.
    // Since initialization code is in the constructor, we do
    //   not need to do anything else with this object
    SampleNode sd{};

    // Change "my_node_sample" to the name of your node 
    ROS_INFO_STREAM(NODE_NAME << " running!");
    ros::spin();
    return 0;
}
