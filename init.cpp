#include "uart.hpp"
#include "console.hpp"
#include "memory.hpp"
#include "printf.h"

namespace tinyrvk {

void init() {
  // https://github.com/qemu/qemu/blob/master/hw/riscv/virt.c
  devices::UART uart({.base_addr = 0x10000000, .freq = 3686400, .baud = 115200});
  utils::Console console(&uart);
  console.print("Hello World!\n");

  static memory::PhysicalMemoryManager pmm(_memory_start, _memory_end - _memory_start);
  memory::PAddr addr = pmm.alloc_page();

  char strbuf[256];
  snprintf(strbuf, 256, "Alloc addr 0x%llx\n", addr.addr);
  console.print(strbuf);
}

}  // namespace tinyrvk

extern "C" {
void _cpp_entry() {
  tinyrvk::init();

  while (true) {
    asm ("wfi");
  }
}
}
