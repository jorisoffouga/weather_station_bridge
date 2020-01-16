/*
 * bridge.hpp
 *
 *  Created on: 15 janv. 2020
 *      Author: Joris Offouga
 */

#ifndef BRIDGE_HPP_
#define BRIDGE_HPP_

#include <c-periphery/serial.h>
#include <string>
#include <thread>
#include "Message.hpp"

class Bridge
{
public:
	Bridge(std::string device);
	~Bridge();
	int Init();
	void Run();

private:
	std::string m_device;
	serial_t *m_serial;
	uint8_t m_buf[255];
	Message m_msg;
};


#endif /* INC_BRIDGE_HPP_ */
