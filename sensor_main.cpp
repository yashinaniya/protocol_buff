// sensor_main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "pb_encode.h"
#include "pb_decode.h"
#include "pb.h"
#include "pb_common.h"
#include "sensor.pb.h"



bool encode_string(pb_ostream_t *stream, const pb_field_t *field, void * const *arg)
{
	printf("encode_sensorid...\n");

	char *str = "DRR!";

	if (!pb_encode_tag_for_field(stream, field))
		return false;

	return pb_encode_string(stream, (uint8_t*)str, strlen(str));
}
bool encode_channel(pb_ostream_t *stream, const pb_field_t *field, void * const *arg)
{
	printf("encode_channel...\n");

	char *srtt = "temperature sensor!";

	if (!pb_encode_tag_for_field(stream, field))
		return false;

	return pb_encode_string(stream, (uint8_t*)srtt, strlen(srtt));
}

bool encode_int32repeated(pb_ostream_t *stream, const pb_field_t *field, void * const *arg)
{
	int val = 44;
	if (!pb_encode_tag_for_field(stream, field))
		return false;

	return pb_encode_varint(stream, val);
}

bool decode_int32repeated(pb_istream_t *stream, const pb_field_t *field, void **arg)
{
	uint64_t value;
	if (!pb_decode_varint(stream, &value))
		return false;

	printf((char*)*arg, (long)value);
	return true;
}
bool decode_string(pb_istream_t *stream, const pb_field_t *field, void **arg)
{
	printf("decode_string...\n");

	uint8_t buffer[1024] = { 0 };

	/* We could read block-by-block to avoid the large buffer... */
	if (stream->bytes_left > sizeof(buffer) - 1)
		return false;

	if (!pb_read(stream, buffer, stream->bytes_left))
		return false;

	/* Print the string, in format comparable with protoc --decode.
	* Format comes from the arg defined in main().
	*/
	printf((char*)*arg, buffer);
	return true;
}




int main()
{
	/* This is the buffer where we will store our message. */
	uint8_t buffer[1024];
	size_t length;
	bool status;

	/* Encode our message */
	{
		/* Allocate space on the stack to store the message data.
		* It is a good idea to always initialize your structures
		* so that you do not have garbage data from RAM in there.
		*/
		Data message = Data_init_zero;


		/* Create a stream that will write to our buffer. */
		pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

		/* Fill in the callback */
		message.SensorID.funcs.encode = &encode_string;
		message.ChannelID.funcs.encode = &encode_channel;
		message.Status = 1;
		message.Value.funcs.encode = &encode_int32repeated;





		/* Now we are ready to encode the message! */
		status = pb_encode(&stream, Data_fields, &message);

		/* Then just check for any errors.. */
		if (!status)
		{
			printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
			return 1;
		}
		length = stream.bytes_written;

	}

	{
		/* Allocate space for the decoded message. */
		Data message = Data_init_zero;



		/* Create a stream that reads from the buffer. */
		pb_istream_t stream = pb_istream_from_buffer(buffer, length);

		/* Fill in the callback and arg */
		message.SensorID.funcs.decode = &decode_string;
		message.SensorID.arg = "stringvalue: \"%s\"\n";
		message.ChannelID.funcs.decode = &decode_string;
		message.ChannelID.arg = "channelvalue: \"%s\"\n";
		message.Value.funcs.decode = &decode_int32repeated;
		message.Value.arg = "int32Repeated: %ld\n";


		/* Now we are ready to decode the message. */
		status = pb_decode(&stream, Data_fields, &message);

		/* Check for errors... */
		if (!status)
		{
			printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
			return 1;
		}
		printf("Your status was %d!\n", message.Status);
	}

	return 0;

}

