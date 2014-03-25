/**************************************************
* CSCE 574 Robotics                               *
* Project : Project 3                             *
* Date: 3/25/2014                                 *
***************************************************/

#include <ros/ros.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <std_msgs/Int32.h>
#include <create_node/TurtlebotSensorState.h>


using namespace std;

//initialize variables
const string IFNAME = "wlan0";
int batteryPercentage;
int bumps_wheeldrops;

//Determines the wifi signal strenth of the netbook
std_msgs::Int32 determineWifiStrength(){
    std_msgs::Int32 value;
    value.data = -1;

    //error opening input file
    ifstream input("/proc/net/wireless");
    if(!input)
    {
     	cout << "Couldn't open the file\n";
	return value;
    }

    string line;
    string word;

    //Parse input file and grab the value we need
    while(getline(input, line)) {
        istringstream bp(line);	
        string fname;
        bp >> fname;
        if(fname == IFNAME + ':')
        {
            replace(line.begin(), line.end(), '.', ' ');
	    bp >> word; bp >> word;
            ROS_INFO_STREAM("Current WiFi Signal Strength: " << word << '\n');
            value.data = atoi(word.c_str());
 	    return value;    
 	}
    }


    return value;
}

//Deciphers what the int32 bumps_wheeldrops means
string determineWheeldrops(){
	std_msgs::Int32 wheeldrop;
	wheeldrop.data = bumps_wheeldrops;
	char myString;
	switch(wheeldrop) {
		case 0:
	    		//all wheels are on the ground and the front bumper is not colliding with any objects
	    		//send out no messages
	    		break;
	    	case 1:
	    		//right bumper contact
	    		ROS_INFO_STREAM("Bumper contact right.");
	    		myString = "Bumper contact right.";
	    		return myString;
	    		break;
	    	case 2:
	    		//left bumper contact
	    		ROS_INFO_STREAM("Bumper contact left.");
	    		myString = "Bumper contact left.";
	    		return myString;
	    		break;
	    	case 3:
	    		//right and left bumper contact
	    		ROS_INFO_STREAM("Bumper contact center.");
	    		myString = "Bumper contact center.";
	    		return myString;
	    		break;
	    	case 4:
	    		//right wheel dropping
	    		ROS_INFO_STREAM("Wheel drop right.");
	    		myString = "Wheel drop right.";
	    		return myString;
	    		break;
	    	case 8:
	    		//left wheel dropping
	    		ROS_INFO_STREAM("Wheel drop left.");
	    		myString = "Wheel drop left.";
	    		return myString;
	    		break;
	    	case 12:
	    		//right and left wheels dropping
	    		ROS_INFO_STREAM("Wheel drop right and left simultaneous.");
	    		myString = "Wheel drop right and left simultaneous.";
	    		return myString;
	    		break;
	    	case 16:
	    		//caster wheel dropping
	    		ROS_INFO_STREAM("Wheel drop caster.");
	    		myString = "Wheel drop caster.";
	    		return myString;
	    		break;
	    	case 20:
	    		//right and caster wheel dropping
	    		ROS_INFO_STREAM("Wheel drop right and caster simultaneous.");
	    		myString = "Wheel drop right and caster simultaneous.";
	    		return myString;
	    		break;
	    	case 24:
	    		//left and caster wheel dropping
	    		ROS_INFO_STREAM("Wheel drop left and caster simultaneous.");
	    		myString = "Wheel drop left and caster simultaneous.";
	    		return myString;
	    		break;
	    	case 28:
	    		//all three wheels dropped
	    		ROS_INFO_STREAM("Wheel drop right, left, and caster simultaneous.");
	    		myString = "Wheel drop right, left, and caster simultaneous.";
	    		return myString;
	    		break;
	    	default:
	    		//default error action
	    		ROS_INFO_STREAM("You should not be seeing this!!! ***BAD*** ");
	    		myString = "You should not be seeing this!!! ***BAD*** ";
	    		return myString;
	    		break;
	    }
}

//Receives sensor state messages and uses that information to provide basic sensor diagnostics
void turtlebotSensorStateMessageReceived(create_node::TurtlebotSensorState sensorState){
	batteryPercentage = int(double(sensorState.charge)/sensorState.capacity * 100);	
	bumps_wheeldrops = sensorState.bumps_wheeldrops;
}


int main(int argc, char** argv)
{
	ros::init(argc,argv, "wifi_signal_strength");
	ros::NodeHandle nh;
	
	//Subscribers
	ros::Subscriber batterySubscriber = nh.subscribe("/turtlebot_node/sensor_state", 1000, &turtlebotSensorStateMessageReceived);
	
	//Publishers
	ros::Publisher wifiPublisher = nh.advertise <std_msgs::Int32>("/wifi_ss",1000);
	ros::Publisher batteryPublisher = nh.advertise <std_msgs::Int32>("/battery_percentage", 1000);
	ros::Publisher wheeldropPublisher = nh.advertise <string>("/bump_wheeldrop", 1000);	

	//Adjust rate of sent messages
	ros::Rate rate(100);


	while(ros::ok()){

	    //Publish wifi signal strength
	    wifiPublisher.publish(determineWifiStrength());

	    //Publish icreate battery percentage remaining
	    std_msgs::Int32 battery;
	    battery.data = batteryPercentage;
	    batteryPublisher.publish(battery);

	    //Publish Bump and Wheeldrop Info Messages
	    wheeldropPublisher.publish(determineWheeldrops());
	    
	    rate.sleep();
	    ros::spinOnce();
	}
}
