#include <ros/ros.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <std_msgs/Int32.h>

using namespace std;

const string IFNAME = "wlan0";


int main(int argc, char** argv)
{
	ros::init(argc,argv, "wifi_signal_strength");
	ros::NodeHandle nh;

	ros::Publisher pub = nh.advertise <std_msgs::Int32>("/wifi_ss",1000);

	ros::Rate rate(0.2);

	while(ros::ok()){


	ifstream input("/proc/net/wireless");
    	if(!input)
    	{
     	  cout << "Couldn't open the file\n";
	  return 1;
	}

    	string line;
	string word;
    while(getline(input, line)) {
        istringstream bp(line);	
        string fname;
        bp >> fname;
        if(fname == IFNAME + ':')
        {
            replace(line.begin(), line.end(), '.', ' ');
	    bp >> word; bp >> word;
	    ROS_INFO_STREAM("Current WiFi Signal Strength: " << word << '\n');
	    std_msgs::Int32 value;
	    value.data = atoi(word.c_str());
//	    ROS_INFO_STREAM("converted value: " << value.data);
	    pub.publish(value);
        }
    }

	

	rate.sleep();
	}
}





