/*
 * Bridge.cpp
 *
 *  Created on: 15 janv. 2020
 *      Author: Joris Offouga
 */

#include "Bridge.hpp"
#include <iostream>
#include <unistd.h>
#include <cstring>

#define INTERFACE_NAME "local.WeatherMonitor.WeatherMonitor"
#define PATH "/"
#define BUS_NAME "org.weather.monitor"
#define METHOD "setWeatherInfos"

Bridge::Bridge()
{
	m_serial = nullptr;
}

Bridge::~Bridge()
{
	if (is_open) {
		serial_close(m_serial);
		serial_free(m_serial);
	}
}

int Bridge::init(std::string &device)
{
	int ret = 0;

	m_serial = serial_new();

	if(m_serial == NULL)
	{
		std::cerr << "Cannot acquire allocation for m_serial object" << std::endl;
		return -1;
	}

	if (serial_open(m_serial, device.c_str(), 115200) < 0){
		std::cerr << "Cannot open " << device << std::endl;
		std::cerr << serial_errmsg(m_serial) << std::endl;
		return -1;
	}

	std::cout << "Open Successful " << device << std::endl ;
	is_open = true;

	serial_flush(m_serial);

	ret = sd_bus_open_user(&m_bus);

	if (ret < 0) {
		std::cerr << "Failed to connect to system bus: " << std::strerror(-ret) << std::endl;
		return -1;
	}

	return 1;
}

int Bridge::sendToDBus(message_t *msg)
{
	sd_bus_error error = SD_BUS_ERROR_NULL;
	sd_bus_message *reply = nullptr;
	int ret;

	ret = sd_bus_call_method(m_bus, BUS_NAME,
			PATH, INTERFACE_NAME,
			METHOD,
			&error,
			&reply,
			"si",
			m_msg.toString(msg).c_str(), static_cast<int>(msg->type));

	if (ret < 0) {
		std::cerr << "Failed to issue method call: " << error.message << std::endl;
		return -1;
	}

	return 1;
}

void Bridge::run()
{
	unsigned int count = 0;
	int l_count = 0;
	std::cout << "Started Bridge Thread" << std::endl;
	for(;;){
		if(serial_input_waiting(m_serial, &count) ==  0){
			l_count = serial_read(m_serial, m_buf, count, -1);
			if (l_count >= 3) {
				message_t *msg = m_msg.Parse(m_buf, count);
				if (msg != nullptr) {
					std::cout << m_msg.toString(static_cast<sensor_type_t>(msg->type))
									<< ": "<< m_msg.toString(msg) << std::endl;
					if (sendToDBus(msg) < 0) {
						std::cerr << "Failed to send dbus message" << std::endl;
					}
					free(msg);
				}
				memset(m_buf, 0, sizeof(m_buf));
				serial_flush(m_serial);
			}
		}
		usleep(1000);
	}
}
