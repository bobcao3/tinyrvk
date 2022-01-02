#include "common.hpp"
#include "uart.hpp"
#include "console.hpp"
#include "printf.h"

extern "C" {

struct CSRCause {
  size_t exception_code : 63;
  size_t interrupt : 1;
};

size_t handle_trap(CSRCause scause, size_t sepc, size_t *stack) {
  if (scause.interrupt == 1) {
    return sepc;
  }

  // Panic routine
  const char* exception_cause[] = {
    "Instruction address misaligned\n",
    "Instruction address fault\n",
    "Illegal instruction\n",
    "Breakpoint\n",
    "Load address misaligned\n",
    "Load access fault\n",
    "Store/AMO address misaligned\n",
    "Store/AMO access fault\n",
    "ECALL from U-Mode\n",
    "ECALL from S-Mode\n",
    "Reserved\n",
    "Reserved\n",
    "Instruction page fault\n",
    "Load page fault\n",
    "Reserved\n",
    "Store/AMO page fault\n"
  };

  tinyrvk::devices::UART uart({.base_addr = 0x10000000, .freq = 3686400, .baud = 115200});
  tinyrvk::utils::Console console(&uart);
  console.print("======= UNHANDLED TRAP =======\n");
  if (scause.interrupt == 0) {
    if (scause.exception_code < 16) {
      console.print(exception_cause[scause.exception_code]);
    }
  }
  char strbuf[256];
  snprintf(strbuf, 256, "Interrupt = %x, Cause = %d, PC = 0x%016llx\n", scause.interrupt, scause.exception_code, sepc);
  console.print(strbuf);
  snprintf(strbuf, 256, "ra = 0x%016llx\n", stack[1]);
  console.print(strbuf);
  size_t sp = 0;
  asm("csrr %0, sscratch" : "=r"(sp));
  snprintf(strbuf, 256, "sp = 0x%016llx\n", sp);
  console.print(strbuf);
  snprintf(strbuf, 256, "gp = 0x%016llx\n", stack[3]);
  console.print(strbuf);
  snprintf(strbuf, 256, "tp = 0x%016llx\n", stack[4]);
  console.print(strbuf);
  snprintf(strbuf, 256, "t0 = 0x%016llx t1 = 0x%016llx t2 = 0x%016llx\n", stack[5], stack[6], stack[7]);
  console.print(strbuf);
  snprintf(strbuf, 256, "t3 = 0x%016llx t4 = 0x%016llx t5 = 0x%016llx t6 = 0x%016llx\n", stack[28], stack[29], stack[30], stack[31]);
  console.print(strbuf);
  snprintf(strbuf, 256, "s0 = 0x%016llx s1 = 0x%016llx\n", stack[8], stack[9]);
  console.print(strbuf);
  snprintf(strbuf, 256, "s2 = 0x%016llx s3 = 0x%016llx s4 = 0x%016llx s5 = 0x%016llx s6 = 0x%016llx\n", stack[18], stack[19], stack[20], stack[21], stack[22]);
  console.print(strbuf);
  snprintf(strbuf, 256, "s7 = 0x%016llx s8 = 0x%016llx s9 = 0x%016llx s10= 0x%016llx s11= 0x%016llx\n", stack[23], stack[24], stack[25], stack[26], stack[27]);
  console.print(strbuf);
  snprintf(strbuf, 256, "a0 = 0x%016llx a1 = 0x%016llx a2 = 0x%016llx a3 = 0x%016llx\n", stack[10], stack[11], stack[12], stack[13]);
  console.print(strbuf);
  snprintf(strbuf, 256, "a4 = 0x%016llx a5 = 0x%016llx a6 = 0x%016llx a7 = 0x%016llx\n", stack[14], stack[15], stack[16], stack[17]);
  console.print(strbuf);
  console.print("======= UNHANDLED TRAP =======\n");
  while (true) {
    asm ("wfi");
  }
}

}