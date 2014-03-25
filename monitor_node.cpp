#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <diagnostic_msgs/DiagnosticArray.h>
#include <diagnostic_msgs/DiagnosticStatus.h>
#include <diagnostic_msgs/KeyValue.h>

void wifiMessageReceived(std_msgs::Int32 wifiStrengthObject){
	ROS_INFO_STREAM("Wifi Signal Strength: " << wifiStrengthObject.data << "%");
}


void batteryMessageReceived(std_msgs::Int32 batteryPercentageObject){
	ROS_INFO_STREAM("Create Battery Status: " << batteryPercentageObject.data << "%");
}

int main(int argc, char **argv){
	ros::init(argc, argv, "monitor_node");
	ros::NodeHandle nh;
	
	ros::Subscriber wifiSubcriber = nh.subscribe("/wifi_ss", 1000, &wifiMessageReceived);
 	ros::Subscriber batterySubscriber = nh.subscribe("/battery_percentage", 1000, &batteryMessageReceived);	
	ros::spin();
}
