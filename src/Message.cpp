/*
 * Message.cpp
 *
 *  Created on: 16 janv. 2020
 *      Author: Joris Offouga
 */

#include "Message.hpp"
#include <stdlib.h>
#include <cstring>
#include <iostream>

Message::Message() {

}

Message::~Message() {

}

message_t *Message::Parse(uint8_t *data, uint8_t len)
{
	message_t *msg = reinterpret_cast<message_t*>(malloc(sizeof(message_t)));

	if(!msg)
		return nullptr;

	if(data[0] != SOF)
		return nullptr;

	msg->len = data[1];
	msg->type = static_cast<sensor_type_t>(data[2]);

	for(int i = 0; i < msg->len; ++i)
	{
		msg->data[i] = data[3 + i];
	}

	return msg;

}

void Message::toString(message_t *message)
{
	std::string type;

	switch (message->type) {
		case TEMP:
			type = "Temperature";
			break;
		case PRESS:
			type = "Pressure";
			break;
		case HUMIDITY:
			type = "Humidity";
			break;
		default:
			break;
	}

	std::cout << type << ": " << std::to_string(message->data[0]) << "." <<
			std::to_string(message->data[1])<< std::endl;
}
