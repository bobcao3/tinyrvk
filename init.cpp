#include "uart.hpp"
#include "console.hpp"
#include "memory.hpp"
#include "printf.h"

extern "C" size_t _memory_start;

namespace tinyrvk {

void init() {
  // https://github.com/qemu/qemu/blob/master/hw/riscv/virt.c
  devices::UART uart({.base_addr = 0x10000000, .freq = 3686400, .baud = 115200});
  utils::Console console(&uart);
  console.print("Hello World!\n");

  static memory::PhysicalMemoryManager pmm(size_t(&_memory_start), 128 << 20);
  auto addr0 = pmm.alloc_page();

  char strbuf[256];

  snprintf(strbuf, 256, "Alloc addr 0x%llx\n", addr0.addr);
  console.print(strbuf);

  auto addr1 = pmm.alloc_page();

  snprintf(strbuf, 256, "Alloc addr 0x%llx\n", addr1.addr);
  console.print(strbuf);

  auto addr2 = pmm.alloc_page();

  snprintf(strbuf, 256, "Alloc addr 0x%llx\n", addr2.addr);
  console.print(strbuf);

  pmm.free_page(addr1);

  auto addr3 = pmm.alloc_page();

  snprintf(strbuf, 256, "Alloc addr 0x%llx\n", addr3.addr);
  console.print(strbuf);

  pmm.free_page(addr3);
  pmm.free_page(addr1);

  auto addr4 = pmm.alloc_page();

  snprintf(strbuf, 256, "Alloc addr 0x%llx\n", addr4.addr);
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
