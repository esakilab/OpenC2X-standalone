#include "SerialPort.h"
#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "sensor_msgs/PointCloud2.h"
#include "sensor_msgs/PointCloud.h"
#include "sensor_msgs/point_cloud_conversion.h"
#include "autoware_msgs/DetectedObjectArray.h"
#include <common/utility/CommunicationSender.h>
#include <common/utility/LoggingUtility.h>
#include <common/utility/Constants.h>
#include <common/buffers/autoware.pb.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/asio.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <string>
#include <common/config/config.h>
#include "projects.h"
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>

namespace asio = boost::asio;
using asio::ip::tcp;

struct message {
	int speed;
	int latitude;
	int longitude;
	int time;

};

struct socket_message{
	std::vector<int> speed;
	std::vector<int> latitude;
	std::vector<int> longitude;
	std::vector<int> time;

private:
	friend class boost::serialization::access;
	template<class Archive>
		void serialize( Archive& ar, unsigned int ver){
			ar & speed;
			ar & latitude;
			ar & longitude;
			ar & time;
		}
};

// struct socket_message{
// 	std::vector<message> data;

// private:
// 	friend class boost::serialization::access;
// 	template<class Archive>
// 		void serialize( Archive& ar, unsigned int ver){
// 			ar & data;
// 		}
// };


void init(ros::NodeHandle n);
void sendToRouter();
double calcSpeed();
void timeCalc();
void callback(const geometry_msgs::PoseStamped msg);
void callback_objects(const autoware_msgs::DetectedObjectArray msg);
void sampleCallback(autoware_msgs::DetectedObjectArray msg);
std::vector<geometry_msgs::Point32> createLine();std::vector<geometry_msgs::Point32> createConvexHull();
sensor_msgs::ChannelFloat32 createChannel(std::string name);
void createObjectsPublisher(const ros::TimerEvent&);
void createPointsPublisher(const ros::TimerEvent&);
std::string paramOrganize(std::string param);


ros::NodeHandle *n;
double speed;
double longitude;
double latitude;
float generationUnixTime;
long generationUnixTimeSec;
long generationUnixTimeNSec;
geometry_msgs::PoseStamped nowPose;
geometry_msgs::PoseStamped prevPose;

PJ *p_proj;
std::ofstream delay_output_file;

int sockfd;

socket_message s_message;

tcp::socket socket(asio::io_service);
