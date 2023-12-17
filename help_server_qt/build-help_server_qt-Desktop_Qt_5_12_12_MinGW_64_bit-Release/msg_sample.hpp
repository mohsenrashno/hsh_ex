#include "include/darc-rpc.hpp"

class msg_params : public dc::msg_serializer {
 public:
  uint8_t a, b, c;

  virtual void serialize(uint8_t* buffer, size_t* buffer_size) override {
    buffer[0] = a;
    buffer[1] = b;
    buffer[2] = c;

    *buffer_size = 3;
  }

  virtual bool deserialize(uint8_t* buffer, const size_t buffer_size) override {
    if (buffer_size < 3) {
      return false;
    }
    a = buffer[0];
    b = buffer[1];
    c = buffer[2];
    return true;
  }
};

class msg_result : public dc::msg_serializer {
 public:
  uint16_t value1;
  uint16_t value2;
  uint16_t value3;

  virtual void serialize(uint8_t* buffer, size_t* buffer_size) override {
    buffer[0] = static_cast<uint8_t>(value1 & 0x00FF);
    buffer[1] = static_cast<uint8_t>(value1 >> 8);
    buffer[3] = static_cast<uint8_t>(value2 & 0x00FF);
    buffer[4] = static_cast<uint8_t>(value2 >> 8);
    buffer[5] = static_cast<uint8_t>(value3 & 0x00FF);
    buffer[6] = static_cast<uint8_t>(value3 >> 8);
    *buffer_size = 6;
  }

  virtual bool deserialize(uint8_t* buffer, const size_t buffer_size) override {
    if (buffer_size != 6) {
      return false;
    }
    value1 = static_cast<uint16_t>(buffer[0]) |
            (static_cast<uint16_t>(buffer[1]) << 8);
    value2 = static_cast<uint16_t>(buffer[3]) |
            (static_cast<uint16_t>(buffer[4]) << 8);
    value3 = static_cast<uint16_t>(buffer[5]) |
            (static_cast<uint16_t>(buffer[6]) << 8);
    return true;
  }
};
