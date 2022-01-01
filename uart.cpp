#include "uart.hpp"

namespace tinyrvk {
namespace devices {

UART::UART(const UARTParams &params) : regs((UARTCtrlRegs *)params.base_addr) {
  uint32_t divisor = params.freq / (16 * params.baud);
  regs->lcr = LCR_DLAB;
  regs->dll = divisor & 0xff;
  regs->dlm = (divisor >> 8) & 0xff;
  regs->lcr = LCR_PODD | LCR_8BIT;
}

void UART::putc(uint8_t c) {
  while ((regs->lsr & LSR_RI) == 0)
    ;
  regs->thr = c;
}

}  // namespace devices
}  // namespace tinyrvk
