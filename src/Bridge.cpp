/*
 * bridge.cpp
 *
 *  Created on: 15 janv. 2020
 *      Author: Joris Offouga
 */

#include "Bridge.hpp"
#include <iostream>
#include <unistd.h>
#include <cstring>

Bridge::Bridge(std::string device)
{
	m_device = device;
}

Bridge::~Bridge()
{
	serial_close(m_serial);
	serial_free(m_serial);
}

int Bridge::Init()
{
	m_serial = serial_new();

	if(m_serial == NULL)
	{
		std::cerr << "Cannot acquire allocation for m_serial object" << std::endl;
		return -1;
	}

	if (serial_open(m_serial, m_device.c_str(), 115200) < 0){
		std::cerr << "Cannot open " << m_device;
		std::cerr << serial_errmsg(m_serial) << std::endl;
		return -1;
	}

	std::cout << "Open Successful " << m_device << std::endl ;

	serial_flush(m_serial);
	return 1;

}

void Bridge::Run()
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
					m_msg.toString(msg);
					free(msg);
				}
				memset(m_buf, 0, sizeof(m_buf));
				serial_flush(m_serial);
			}
		}
		usleep(1000);
	}
}
