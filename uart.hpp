#pragma once

#include "common.hpp"
#include "console.hpp"

namespace tinyrvk {
namespace devices {

// NS16550 UART
class UART : public utils::SerialConsoleDevice {
 private:
  struct UARTCtrlRegs {
    union {
      uint8_t rbr; /* Receive Buffer Register */
      uint8_t thr; /* Transmit Hold Register */
      uint8_t dll; /* Divisor LSB (LCR_DLAB) */
    };
    union {
      uint8_t ier; /* Interrupt Enable Register */
      uint8_t dlm; /* Divisor MSB (LCR_DLAB) */
    };
    uint8_t fcr; /* FIFO Control Register */
    uint8_t lcr; /* Line Control Register */
    uint8_t mcr; /* Modem Control Register */
    uint8_t lsr; /* Line Status Register */
    uint8_t msr; /* Modem Status Register */
    uint8_t scr; /* Scratch Register */
  };

  enum {
    LCR_DLAB = 0x80, /* Divisor Latch Bit */
    LCR_8BIT = 0x03, /* 8-bit */
    LCR_PODD = 0x08, /* Parity Odd */

    LSR_DA = 0x01, /* Data Available */
    LSR_OE = 0x02, /* Overrun Error */
    LSR_PE = 0x04, /* Parity Error */
    LSR_FE = 0x08, /* Framing Error */
    LSR_BI = 0x10, /* Break indicator */
    LSR_RE = 0x20, /* THR is empty */
    LSR_RI = 0x40, /* THR is empty and line is idle */
    LSR_EF = 0x80, /* Erroneous data in FIFO */
  };

  UARTCtrlRegs *regs;

 public:
  struct UARTParams {
    size_t base_addr;
    uint32_t freq;
    uint32_t baud;
  };

  UART(const UARTParams &params);

  void putc(uint8_t c);
};

}  // namespace devices
}  // namespace tinyrvk
