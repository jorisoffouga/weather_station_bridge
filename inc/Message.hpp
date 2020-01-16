/*
 * Message.h
 *
 *  Created on: 16 janv. 2020
 *      Author: Joris Offouga
 */

#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <stdint.h>

/*
 * Format:
 *
 * Fields: |   SOF    |  len  |  type  | Data |
 * nBytes: |   0x55   |   1   |   1    |   N  |
 *
 * type: Device type
 * data: Payload
 * crc: TODO
 */

#define SOF 0x55

typedef enum {
	TEMP = 0x00,
	PRESS = 0x01,
	HUMIDITY = 0x02,
}sensor_type_t;

typedef struct message_s{
	uint8_t len;
	uint8_t type;
	uint8_t data[125];
}message_t;

class Message {
public:
	Message();
	virtual ~Message();
	message_t *Parse(uint8_t *data, uint8_t len);
	void toString(message_t *message);
};

#endif /* MESSAGE_HPP_ */
