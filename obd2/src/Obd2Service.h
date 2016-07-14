#ifndef OBD2SERVICE_H_
#define OBD2SERVICE_H_

/**
 * @addtogroup obd2
 * @{
 */

#include "SerialPort.h"
#include <utility/CommunicationSender.h>
#include <utility/LoggingUtility.h>
#include <buffers/build/obd2.pb.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/asio.hpp>
#include <string>
#include <config/config.h>

/** Struct that holds the configuration for Obd2Service.
 * The configuration is defined in <a href="../../obd2/config/config.xml">obd2/config/config.xml</a>.
 */
struct Obd2Config {
	/** True iff OBD2 should be simulated, false for using real data.
	 *
	 */
	bool mSimulateData;

	/** The USB device OBD2 is connected to (default: /dev/ttyUSB0).
	 *
	 */
	char* mDevice;

	/** The frequency in ms at which new OBD2 data should be distributed (default: 500).
	 *	Note: a frequency of 100ms does not work.
	 */
	int mFrequency;

	void loadConfigXML(const std::string &filename) {
		boost::property_tree::ptree pt;
		read_xml(filename, pt);

		mSimulateData = pt.get("obd2.SimulateData", true);
		std::string device = pt.get("obd2.Device", "//dev//ttyUSB0");
		mDevice = strdup(device.c_str());
		mFrequency = pt.get("obd2.Frequency", 100);
	}
};

/**
 * Class that connects to OBD2 via serial port and offers its data to other modules via ZMQ.
 */
class Obd2Service {
public:
	Obd2Service(Obd2Config &config);
	~Obd2Service();
	void init();

	/** Reads the actual vehicle data from OBD2 and distributes it via ZMQ.
	 *  Periodically reads speed and rpm data from OBD2 if simulating data is turned off,
	 *	writes it into a protocol buffer and sends it to services such as CaService and DenService.
	 *	@param ec Boost error code.
	 *	@param serial SerialPort that handles the actual connection to OBD2 via serial port.
	 */
	void receiveData(const boost::system::error_code &ec, SerialPort* serial);

	/** Simulates vehicle speed.
	 *  Simulates vehicle speed using a random distribution.
	 */
	double simulateSpeed();

	/** Simulates vehicle data and distributes it via ZMQ.
	 *  Periodically simulates speed data if simulating data is turned on,
	 *	writes it into a protocol buffer and sends it to services such as CaService and DenService.
	 *	@param ec Boost error code.
	 */
	void simulateData(const boost::system::error_code &ec);

	/** Distributes OBD2 via ZMQ.
	 *  Sends OBD2 via ZMQ to services such as CaService and DenService and logs the data.
	 *  @param obd2 The OBD2 to be sent to services.
	 */
	void sendToServices(obd2Package::OBD2 obd2);

private:
	Obd2Config mConfig;
	GlobalConfig mGlobalConfig;

	CommunicationSender* mSender;
	LoggingUtility* mLogger;

	//for simulation only
	std::default_random_engine mRandNumberGen;
	std::bernoulli_distribution mBernoulli;
	std::uniform_real_distribution<double> mUniform;

	boost::asio::io_service mIoService;
	boost::asio::deadline_timer* mTimer;
};

/** @} */ //end group

#endif
