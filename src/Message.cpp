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

#define INDEX_SOF 0
#define INDEX_LEN 1
#define INDEX_TYPE 2
#define INDEX_DATA 3

message_t *Message::Parse(uint8_t *data, uint8_t len)
{
	message_t *msg = reinterpret_cast<message_t*>(malloc(sizeof(message_t)));

	if(!msg)
		return nullptr;

	if(data[INDEX_SOF] != SOF){
		free(msg);
		return nullptr;
	}

	msg->len = data[INDEX_LEN];
	msg->type = static_cast<sensor_type_t>(data[INDEX_TYPE]);

	for(int i = 0; i < msg->len; ++i)
	{
		msg->data[i] = data[INDEX_DATA + i];
	}

	return msg;
}

std::string Message::toString(message_t *message)
{
	return std::to_string(message->data[0]) + "." + std::to_string(message->data[1]);
}

std::string Message::toString(sensor_type_t type)
{
	switch (type) {
		case TEMP:
			return "Temperature";
		case PRESS:
			return "Pressure";
		case HUMIDITY:
			return "Humidity";
		default:
			return "Unknown";
	}
}
