/*
 * Bridge.hpp
 *
 *  Created on: 15 janv. 2020
 *      Author: Joris Offouga
 */

#ifndef BRIDGE_HPP_
#define BRIDGE_HPP_

#include <c-periphery/serial.h>
#include <systemd/sd-bus.h>
#include <string>
#include "Message.hpp"

class Bridge
{
public:
	Bridge();
	~Bridge();
	int init(std::string &device);
	void run();
	int sendToDBus(message_t *msg);

private:
	std::string m_device;
	serial_t *m_serial;
	uint8_t m_buf[255];
	Message m_msg;
	sd_bus *m_bus = nullptr;
	bool is_open = false;
};


#endif /* BRIDGE_HPP_ */
