#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <diagnostic_msgs/DiagnosticArray.h>
#include <diagnostic_msgs/DiagnosticStatus.h>

void wifiMessageRecieved(std_msgs::Int32 wifiStrengthObject){
	ROS_INFO_STREAM("Wifi Signal Strength: " << wifiStrengthObject.data << "%");
}

void diagnosticMessageRecieved(diagnostic_msgs::DiagnosticArray diagnosticArray){
	diagnostic_msgs::DiagnosticStatus statusArray[diagnosticArray.size()];
	statusArray = diagnosticArray.status;
	for (int i = 0; i < statusArray.size(); i++){
		diagnostic_msgs::DiagnosticStatus status = statusArray[i];
		ROS_INFO_STREAM("Diagnostic Type: " << status.level << " MESSAGE: " << status.name << " -- " << status.message);
	}
}

int main(int argc, char **argv){
	ros::init(argc, argv, "monitor_node");
	ros::NodeHandle nh;
	
	ros::Subscriber wifiSubcriber = nh.subscribe("/wifi_ss", 1000, &wifiMessageRecieved);
	ros::Subscriber diagnosticSubscriber = nh.subscribe("/diagnostics_toplevel_state", 1000, &diagnosticMessageRecieved);
	
	ros::spin();
}
