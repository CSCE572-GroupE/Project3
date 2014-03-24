#include <ros/ros.h>
#include "sensor_msgs/Int32"

void wifiMessageRecieved(sensor_msgs::Int32 wifiStrengthObject){
	ROS_INFO_STREAM(wifiStrengthObject.data);
}

int main(int argc, char **argv){
	ros::init(argc, argv, "monitor_node");
	ros::Nodehandle nh;
	
	ros::Subscriber sub = nh.subscribe("wifi_ss", 1000, &wifiMessageRecieved);

	ros::spin();
}
