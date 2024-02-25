#include "WmbusMeter.h"
#include <string>
#include "DriversWmbusMeters/meters.h"

WmbusMeter::~WmbusMeter(){
  for (const auto& kv : this->sensors_) {
    delete kv.second;
  }
}
WmbusMeter::WmbusMeter(uint8_t mosi, uint8_t miso, uint8_t clk, uint8_t cs, uint8_t gdo0, uint8_t gdo2)
{
  Serial.print("wMBus-lib: Initializing with GPIO: ");
  Serial.print(mosi);
  Serial.print(",");
  Serial.print(miso);
  Serial.print(",");
  Serial.print(clk);
  Serial.print(",");
  Serial.print(cs);
  Serial.print(",");
  Serial.print(gdo0);
  Serial.print(",");
  Serial.print(gdo2);
  Serial.println(" GPIO");
};

void WmbusMeter::add_sensor(SensorBase *sensor)
{
  this->sensors_[sensor->get_meter_id()] = sensor;
  Serial.println("------");
  Serial.print("Type:");
  Serial.println(sensor->get_type().c_str());
  Serial.print("Id:");
  Serial.println(sensor->get_meter_id().c_str());
  Serial.print("Key:");
  Serial.println(sensor->get_key_string().c_str());
  Serial.print("Property:");
  Serial.println(sensor->get_property_to_send().c_str());
}

float WmbusMeter::parse_frame(std::vector<unsigned char> &frame)
{
  Serial.println("wMBus-lib: Formatting as string.");
  std::string telegram = format_hex_pretty(frame);

  Serial.println("wMBus-lib: Removing helping characters.");

  telegram.erase(std::remove(telegram.begin(), telegram.end(), '.'), telegram.end());

  Serial.println("wMBus-lib: Getting meter id.");
  std::string meterIdString = telegram.substr(8, 8);
  char s[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  s[0] = meterIdString[6];
  s[1] = meterIdString[7];
  s[2] = meterIdString[4];
  s[3] = meterIdString[5];
  s[4] = meterIdString[2];
  s[5] = meterIdString[3];
  s[6] = meterIdString[0];
  s[7] = meterIdString[1];
  std::string meterIdRealString = s;
  Serial.println("As is:");
  Serial.println(meterIdString.c_str());
  Serial.print("Meter id:");
  Serial.println(meterIdRealString.c_str());
  // either we have sensors defined or we have just one without ID (like Izar)
  if (sensors_.count(meterIdRealString) > 0 || (sensors_.size() == 1 && sensors_.begin()->second->get_meter_id() == ""))
  {
    Serial.println("wMBus-lib: Getting sensor config.");
    auto sensor = (sensors_.size() == 1 && sensors_.begin()->second->get_meter_id() == "") ? sensors_.begin()->second : sensors_[meterIdRealString];
    bool isOk = true;
    float readValue = 0.0;

    readValue = sensor->handleTelegram(frame);
    Serial.print("Meter id as number: ");
    Serial.println(meterIdString.c_str());
    Serial.print("Meter id as string: ");
    Serial.println(meterIdRealString.c_str());
    Serial.print(readValue);
    Serial.println("m3");
      sensor->setNewValue(readValue * 1000);
      sensor->iterateAlways();
    return readValue;
  }
  else
  {
    Serial.print("wMBus-lib: Config for meter: ");
    Serial.print(meterIdRealString.c_str());
    Serial.println(" does not exist.");
  }
  return 0.0;
}
