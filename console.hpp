#pragma once

#include "common.hpp"

namespace tinyrvk {
namespace utils {

class SerialConsoleDevice {
public:
    void putc(uint8_t c);
};

template<class DeviceT>
class Console {
private:
  DeviceT *device;

public:
  Console(DeviceT *device) : device(device) {
    static_assert(std::is_base_of<SerialConsoleDevice, DeviceT>::value, "utils::Console must use a device that implements utils::SerialConsoleDevice");
  }

  void print(const char* str) {
    if (!str) str = "nullptr";
    while (*str) {
      device->putc(*str);
      str++;
    }
  }
};

}
}
