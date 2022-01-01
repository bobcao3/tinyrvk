#include "uart.hpp"
#include "console.hpp"

namespace tinyrvk {

void init() {
  // https://github.com/qemu/qemu/blob/master/hw/riscv/virt.c
  devices::UART uart({.base_addr = 0x10000000, .freq = 3686400, .baud = 115200});
  utils::Console console(&uart);
  console.print("Hello World!\n");
}

}  // namespace tinyrvk

extern "C" {
__attribute__((section(".text.init")))
void _start() {
  tinyrvk::init();

  while (true) {
    asm ("wfi");
  }
}
}
