#include <Arduino.h>
#include <vector>
#include "WmbusMeter.h"
#include "Esp.h"

uint16_t packetSize1 (uint8_t lField)
{
  uint16_t nrBytes;
  uint8_t  nrBlocks;

  // The 2 first blocks contains 25 bytes when excluding CRC and the L-field
  // The other blocks contains 16 bytes when excluding the CRC-fields
  // Less than 26 (15 + 10) 
  if ( lField < 26 ) {
    nrBlocks = 2;
  }
  else { 
    nrBlocks = (((lField - 26) / 16) + 3);
  }

  // Add all extra fields, excluding the CRC fields
  nrBytes = lField + 1;

  // Add the CRC fields, each block is contains 2 CRC bytes
  nrBytes += (2 * nrBlocks);

  return (nrBytes);
}
SET_LOOP_TASK_STACK_SIZE(16*1024);
void setup() {
  Serial.begin(115200);
  Serial.println("wMBus-lib: TESTS:");
  float memory= ESP.getFreeHeap() / 1024.0;
  Serial.print("Memory:");
  Serial.println(memory);
  
 Serial.print("Apator08");
uint8_t packet1[254] = { 0x73,0x44,0x14,0x86,0xDD,0x44,0x44,0x00,0x03,0x03,0xA0,0xB9,0xE5,0x27,0x00,0x4C,0x40,0x34,0xB3,0x1C,0xED,0x01,0x06,0xFF,0x01,0xD0,0x93,0x27,0x00,0x65,0xF0,0x22,0x00,0x96,0x61,0x23,0x00,0x54,0xD0,0x23,0x00,0xEC,0x49,0x24,0x00,0x18,0xB4,0x24,0x00,0x5F,0x01,0x25,0x00,0x93,0x6D,0x25,0x00,0xFF,0xD5,0x25,0x00,0x0E,0x3D,0x26,0x00,0x1E,0xAC,0x26,0x00,0x0B,0x20,0x27,0x00,0x03,0x00,0x00,0x00,0x00,0x37,0x1D,0x0B,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x2C,0x00,0x33,0x15,0x0C,0x01,0x0D,0x2F,0x00,0x00,0x00,0x00,0x00,0x00, };
std::vector<unsigned char> frame1(packet1, packet1 + packetSize1(packet1[0]));
WmbusMeter* meter1 = new WmbusMeter();
meter1->add_sensor(new SensorBase("004444DD", "apator08", "total", "",Unit::M3));
float val1 = meter1->parse_frame(frame1);
 Serial.print("value: ");
 Serial.println(val1); // 871.57m3
   memory= ESP.getFreeHeap() / 1024.0;
  Serial.print("Memory:");
  Serial.println(memory);


 Serial.println("Apator16-2");
uint8_t packet2[254] = { 0x6E,0x44,0x01,0x06,0x20,0x20,0x20,0x20,0x05,0x07,0x7A,0x9A,0x00,0x60,0x85,0x2F,0x2F,0x0F,0x0A,0x73,0x43,0x93,0xCC,0x00,0x00,0x43,0x5B,0x01,0x83,0x00,0x1A,0x54,0xE0,0x6F,0x63,0x02,0x91,0x34,0x25,0x10,0x03,0x0F,0x00,0x00,0x7B,0x01,0x3E,0x0B,0x00,0x00,0x3E,0x0B,0x00,0x00,0x3E,0x0B,0x00,0x00,0x3E,0x0B,0x00,0x00,0x3E,0x0B,0x00,0x00,0x3E,0x0B,0x00,0x00,0x3E,0x0B,0x00,0x00,0x65,0x00,0x00,0x00,0x3D,0x00,0x00,0x00,0x3D,0x00,0x00,0x00,0x3D,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xA0,0x91,0x0C,0xB0,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xA6,0x2B, };
std::vector<unsigned char> frame2(packet2, packet2 + packetSize1(packet2[0]));
WmbusMeter* meter2 = new WmbusMeter();
meter2->add_sensor(new SensorBase("20202020", "apator162", "total", "",Unit::M3));
float val2 = meter2->parse_frame(frame2);
 Serial.print("value: ");
 Serial.println(val2); // 3.84
  Serial.println("Apator16-2 END");
 memory= ESP.getFreeHeap() / 1024.0;
  Serial.print("Memory:");
  Serial.println(memory);


 Serial.println("Iperl");
uint8_t packet3[254] = { 0x1E,0x44,0xAE,0x4C,0x99,0x56,0x34,0x12,0x68,0x07,0x7A,0x36,0x00,0x10,0x00,0x2F,0x2F,0x04,0x13,0x18,0x1E,0x00,0x00,0x02,0x3B,0x00,0x00,0x2F,0x2F,0x2F,0x2F, };
std::vector<unsigned char> frame3(packet3, packet3 + packetSize1(packet3[0]));
WmbusMeter* meter3 = new WmbusMeter();
meter3->add_sensor(new SensorBase("12345699", "iperl", "total", "",Unit::M3));
float val3 = meter3->parse_frame(frame3);
 Serial.print("value: ");
 Serial.println(val3); //  7.70m3
  Serial.println("Iperl END");
 memory= ESP.getFreeHeap() / 1024.0;
  Serial.print("Memory:");
  Serial.println(memory);


 Serial.println("mkradio4");
 // https://wmbusmeters.org/analyze/2f4468508235710295620fcca2069f2f2705c00210000000101a1a11087e111211110e0e110f120f110511111013a53a100e0e1011131c6f
uint8_t packet4[254] = { 0x2F,0x44,0x68,0x50,0x82,0x35,0x71,0x02,0x95,0x62,0x0F,0xCC,0xA2,0x06,0x9F,0x2F,0x27,0x05,0xC0,0x02,0x10,0x00,0x00,0x00,0x10,0x1A,0x1A,0x11,0x08,0x7E,0x11,0x12,0x11,0x11,0x0E,0x0E,0x11,0x0F,0x12,0x0F,0x11,0x05,0x11,0x11,0x10,0x13,0xA5,0x3A,0x10,0x0E,0x0E,0x10,0x11,0x13,0x1C,0x6F };
std::vector<unsigned char> frame4(packet4, packet4 + packetSize1(packet4[0]));
WmbusMeter* meter4 = new WmbusMeter();
meter4->add_sensor(new SensorBase("02713582", "mkradio4", "total", "",Unit::M3));
float val4 = meter4->parse_frame(frame4);
 Serial.print("value: ");
 Serial.println(val4);

  Serial.println("mkradio4 END");
 memory= ESP.getFreeHeap() / 1024.0;
  Serial.print("Memory:");
  Serial.println(memory);

   Serial.println("izar");
 // https://wmbusmeters.org/analyze/19442423860775035048A251520015BEB6B2E1ED623A18FC74A5
uint8_t packet5[254] = {0x19,0x44,0x24,0x23,0x86,0x07,0x75,0x03,0x50,0x48,0xA2,0x51,0x52,0x00,0x15,0xBE,0xB6,0xB2,0xE1,0xED,0x62,0x3A,0x18,0xFC,0x74,0xA5, };
std::vector<unsigned char> frame5(packet5, packet5 + packetSize1(packet5[0]));
WmbusMeter* meter5 = new WmbusMeter();
meter5->add_sensor(new SensorBase("48500375", "izar", "total", "",Unit::M3));
float val5 = meter5->parse_frame(frame5);
 Serial.print("value: ");
 Serial.println(val5); //521.602

  Serial.println("izar END");
 memory= ESP.getFreeHeap() / 1024.0;
  Serial.print("Memory:");
  Serial.println(memory);

   Serial.println("amiplus");
 // https://wmbusmeters.org/analyze/4E4401061010101002027A000040052F2F0E035040691500000B2B300300066D00790C7423400C78371204860BABC8FC100000000E833C8074000000000BAB3C0000000AFDC9FC0136022F2F2F2F2F
uint8_t packet6[254] = {0x4E,0x44,0x01,0x06,0x10,0x10,0x10,0x10,0x02,0x02,0x7A,0x00,0x00,0x40,0x05,0x2F,0x2F,0x0E,0x03,0x50,0x40,0x69,0x15,0x00,0x00,0x0B,0x2B,0x30,0x03,0x00,0x06,0x6D,0x00,0x79,0x0C,0x74,0x23,0x40,0x0C,0x78,0x37,0x12,0x04,0x86,0x0B,0xAB,0xC8,0xFC,0x10,0x00,0x00,0x00,0x0E,0x83,0x3C,0x80,0x74,0x00,0x00,0x00,0x00,0x0B,0xAB,0x3C,0x00,0x00,0x00,0x0A,0xFD,0xC9,0xFC,0x01,0x36,0x02,0x2F,0x2F,0x2F,0x2F,0x2F,};
std::vector<unsigned char> frame6(packet6, packet6 + packetSize1(packet6[0]));
WmbusMeter* meter6 = new WmbusMeter();
meter6->add_sensor(new SensorBase("10101010", "amiplus", "current_power_consumption", "", Unit::KWH));
float val6 = meter6->parse_frame(frame6);
 Serial.print("value: ");
 Serial.println(val6); //0.33

  Serial.println("amiplus END");
 memory= ESP.getFreeHeap() / 1024.0;
  Serial.print("Memory:");
  Serial.println(memory);

 Serial.println("wMBus-lib: TESTS END");
}

void loop() {
  // put your main code here, to run repeatedly:
}
