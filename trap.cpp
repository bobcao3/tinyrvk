#include "common.hpp"
#include "uart.hpp"
#include "console.hpp"
#include "printf.h"

extern "C" {

void handle_trap(int scause, size_t sepc, uint64_t *stack) {
  // Panic routine
  tinyrvk::devices::UART uart({.base_addr = 0x10000000, .freq = 3686400, .baud = 115200});
  tinyrvk::utils::Console console(&uart);
  console.print("======= UNHANDLED TRAP =======\n");
  char strbuf[256];
  snprintf(strbuf, 256, "Cause %d, PC=0x%llx\n", scause, sepc);
  console.print(strbuf);
  snprintf(strbuf, 256, "ra=0x%llx\n", stack[1]);
  console.print(strbuf);
  snprintf(strbuf, 256, "sp=0x%llx\n", stack[2]);
  console.print(strbuf);
  snprintf(strbuf, 256, "gp=0x%llx\n", stack[3]);
  console.print(strbuf);
  snprintf(strbuf, 256, "tp=0x%llx\n", stack[4]);
  console.print(strbuf);
  snprintf(strbuf, 256, "t0=0x%llx t1=0x%llx t2=0x%llx\n", stack[5], stack[6], stack[7]);
  console.print(strbuf);
  snprintf(strbuf, 256, "t3=0x%llx t4=0x%llx t5=0x%llx t6=0x%llx\n", stack[28], stack[29], stack[30], stack[31]);
  console.print(strbuf);
  snprintf(strbuf, 256, "s0=0x%llx s1=0x%llx\n", stack[8], stack[9]);
  console.print(strbuf);
  snprintf(strbuf, 256, "s2=0x%llx s3=0x%llx s4=0x%llx s5=0x%llx s6=0x%llx\n", stack[18], stack[19], stack[20], stack[21], stack[22]);
  console.print(strbuf);
  snprintf(strbuf, 256, "s7=0x%llx s8=0x%llx s9=0x%llx s10=0x%llx s11=0x%llx\n", stack[23], stack[24], stack[25], stack[26], stack[27]);
  console.print(strbuf);
  snprintf(strbuf, 256, "a0=0x%llx a1=0x%llx a2=0x%llx a3=0x%llx\n", stack[10], stack[11], stack[12], stack[13]);
  console.print(strbuf);
  snprintf(strbuf, 256, "a4=0x%llx a5=0x%llx a6=0x%llx a7=0x%llx\n", stack[14], stack[15], stack[16], stack[17]);
  console.print(strbuf);
  console.print("======= UNHANDLED TRAP =======\n");
  while (true) {
    asm ("wfi");
  }
}

}