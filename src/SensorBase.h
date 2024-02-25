#ifndef _SensorBase_h
#define _SensorBase_h

#include <vector>
#include <string>
#include <stdint.h>
#include <DriversWmbusMeters/meters_common_implementation.h>
#include <DriversWmbusMeters/meters.h>
class SensorBase {
 public:
  SensorBase(std::string meter_id, std::string type, std::string property_to_send, std::string keyString, Unit unit)
      : _type(type), _meter_id(meter_id), _property_to_send(property_to_send), _unit(unit) {
    _key = hexToBytes(keyString);
    _keyString = keyString;
    MeterInfo mi;
    mi.parse(type, type, meter_id, keyString);
    _meter = createMeter(&mi);
     Serial.print("Initialized meter:");
     Serial.println(type.c_str());
  };

  ~SensorBase(){
    _key.clear();
  }

  std::string get_type() {
    return this->_type;
  };
  std::string get_meter_id() {
    return this->_meter_id;
  };
  std::string get_property_to_send() {
    return this->_property_to_send;
  };
  std::vector<unsigned char> get_key() {
    return this->_key;
  };
  std::string get_key_string() {
    return this->_keyString;
  };

  float handleTelegram(std::vector<uchar> frame) {
     Serial.println("wMBus-lib: handling telegram");
    std::string id = _meter_id;
    bool id_match = false;
    Telegram* tt = new Telegram();
    AboutTelegram about;
    _meter->handleTelegram(about, frame, false, &id, &id_match, tt);
     Serial.println("wMBus-lib: getting numeric value");
    std::string vals= _meter->debugValues();
    Serial.println(vals.c_str());
    double val = _meter->getNumericValue(_property_to_send, _unit);
    delete tt;
    return val;
  }

  void virtual setNewValue(int value){};
  void virtual iterateAlways(){};

 protected:
  SensorBase();
  std::vector<unsigned char> _key;
  std::string _type;
  std::string _meter_id;
  std::string _property_to_send = "total_water_m3";
  std::string _keyString;
  std::shared_ptr<Meter> _meter;
  Unit _unit;

 private:
  AboutTelegram _about;
  std::vector<unsigned char> hexToBytes(const std::string& hex) {
    std::vector<unsigned char> bytes;

    if (hex.length() == 0) {
      bytes = {};
    }
    else {
      for (unsigned int i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        unsigned char byte = (unsigned char)strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(byte);
      }
    }
    return bytes;
  }
};
#endif