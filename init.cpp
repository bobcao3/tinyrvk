#include "uart.hpp"
#include "console.hpp"
#include "memory.hpp"
#include "printf.h"
#include "thread.hpp"

extern "C" uint8_t _memory_start;
extern "C" uint8_t _memory_end;

namespace tinyrvk {

void init() {  
  // https://github.com/qemu/qemu/blob/master/hw/riscv/virt.c
  devices::UART uart({.base_addr = 0x10000000, .freq = 3686400, .baud = 115200});
  utils::Console console(&uart);
  console.print("Hello World!\n");

  static memory::PhysicalMemoryManager pmm(size_t(&_memory_start), 128 << 20);
  static threads::TaskSystem ts(pmm);

  console.print("Scheduler initialized.\n");

  while (true) {
    asm ("wfi");
  }
}

}  // namespace tinyrvk

extern "C" {
void _cpp_entry() {
  tinyrvk::init();
}
}
