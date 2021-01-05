extern "C" {
#include <pb.h>
#include <pb_common.h>
#include <pb_decode.h>
#include <pb_encode.h>
#include <sensor.pb.h>

}

bool encode_string(pb_ostream_t *stream, const pb_field_t *field, void * const *arg)
{
  Serial.print("encode_string...\n");

  char *str = "DDR!";

  if (!pb_encode_tag_for_field(stream, field))
    return false;

  return pb_encode_string(stream, (uint8_t*)str, strlen(str));
}
bool encode_channel(pb_ostream_t *stream, const pb_field_t *field, void * const *arg)
{
  Serial.print("encode_channel...\n");

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




void setup()
{
  Serial.begin(9600); //This pipes to the serial monitor
  while(!Serial);
  Serial1.begin(9600); //This is the UART, pipes to sensors attached to board
  while(!Serial1);
  Serial.println("In setup");
}

void encod()
{
  /* This is the buffer where we will store our message. */
   uint8_t buffer[512];
  size_t length;
  bool status;

  /* Encode our message */
  {
    /* Allocate space on the stack to store the message data.
    *
    * Nanopb generates simple struct definitions for all the messages.
    * - check out the contents of simple.pb.h!
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
   Serial.write(buffer,length);
   Serial.print("the status is... ");
   Serial.println(message.Status);
   Serial.println("");
   Serial.println("press anything to get encoded data");
   while(!Serial.available());
   char ch = Serial.read();
  }   
  
    
}

void loop()
{
  encod();
  
}

   
   



