#pragma once

#include "common.hpp"

namespace tinyrvk {
namespace memory {

#define VM_VADDR_SIZE 39

struct Sv32VAddr {
  union {
    uint32_t addr;
    struct {
      uint32_t vpn1 : 10;
      uint32_t vpn0 : 10;
      uint32_t page_offset : 12;
    };
  };
};

struct Sv39VAddr {
  union {
    uint64_t addr;
    struct {
      uint64_t vpn2 : 9;
      uint64_t vpn1 : 9;
      uint64_t vpn0 : 9;
      uint64_t page_offset : 12;
    };
  };
};

struct Sv48VAddr {
  union {
    uint64_t addr;
    struct {
      uint64_t vpn3 : 9;
      uint64_t vpn2 : 9;
      uint64_t vpn1 : 9;
      uint64_t vpn0 : 9;
      uint64_t page_offset : 12;
    };
  };
};

struct Sv57VAddr {
  union {
    uint64_t addr;
    struct {
      uint64_t vpn4 : 9;
      uint64_t vpn3 : 9;
      uint64_t vpn2 : 9;
      uint64_t vpn1 : 9;
      uint64_t vpn0 : 9;
      uint64_t page_offset : 12;
    };
  };
};

struct Sv32PAddr {
  union {
    uint64_t addr;
    struct {
      uint64_t ppn1 : 12;
      uint64_t ppn0 : 10;
      uint64_t page_offset : 12;
    };
  };
};

struct Sv39PAddr {
  union {
    uint64_t addr;
    struct {
      uint64_t ppn2 : 26;
      uint64_t ppn1 : 9;
      uint64_t ppn0 : 9;
      uint64_t page_offset : 12;
    };
  };
};

struct Sv48PAddr {
  union {
    uint64_t addr;
    struct {
      uint64_t ppn3 : 17;
      uint64_t ppn2 : 9;
      uint64_t ppn1 : 9;
      uint64_t ppn0 : 9;
      uint64_t page_offset : 12;
    };
  };
};

struct Sv57PAddr {
  union {
    uint64_t addr;
    struct {
      uint64_t ppn4 : 8;
      uint64_t ppn3 : 9;
      uint64_t ppn2 : 9;
      uint64_t ppn1 : 9;
      uint64_t ppn0 : 9;
      uint64_t page_offset : 12;
    };
  };
};

struct Sv32PTE {
  uint32_t ppn1 : 12; /* PPN[1] */
  uint32_t ppn0 : 10; /* PPN[0] */
  uint8_t rsw : 2;    /* Reserved for supervisor */
  uint8_t d : 1;      /* Dirty */
  uint8_t a : 1;      /* Accessed */
  uint8_t g : 1;      /* Global mapping */
  uint8_t u : 1;      /* U-mode access */
  uint8_t x : 1;      /* Execute */
  uint8_t w : 1;      /* Write */
  uint8_t r : 1;      /* Read */
  uint8_t v : 1;      /* Valid */

  bool is_leaf() {
    return (r == 1) || (x == 1);
  }
};

struct Sv39PTE {
  uint32_t n : 1;    /* Extension: Svnapot */
  uint32_t pbmt : 2; /* Extension: Svpbmt */
  uint32_t reserved : 7;
  uint32_t ppn2 : 26; /* PPN[2] */
  uint32_t ppn1 : 9;  /* PPN[1] */
  uint32_t ppn0 : 9;  /* PPN[0] */
  uint8_t rsw : 2;    /* Reserved for supervisor */
  uint8_t d : 1;      /* Dirty */
  uint8_t a : 1;      /* Accessed */
  uint8_t g : 1;      /* Global mapping */
  uint8_t u : 1;      /* U-mode access */
  uint8_t x : 1;      /* Execute */
  uint8_t w : 1;      /* Write */
  uint8_t r : 1;      /* Read */
  uint8_t v : 1;      /* Valid */

  bool is_leaf() {
    return (r == 1) || (x == 1);
  }
};

struct Sv48PTE {
  uint32_t n : 1;    /* Extension: Svnapot */
  uint32_t pbmt : 2; /* Extension: Svpbmt */
  uint32_t reserved : 7;
  uint32_t ppn3 : 17; /* PPN[3] */
  uint32_t ppn2 : 9;  /* PPN[2] */
  uint32_t ppn1 : 9;  /* PPN[1] */
  uint32_t ppn0 : 9;  /* PPN[0] */
  uint8_t rsw : 2;    /* Reserved for supervisor */
  uint8_t d : 1;      /* Dirty */
  uint8_t a : 1;      /* Accessed */
  uint8_t g : 1;      /* Global mapping */
  uint8_t u : 1;      /* U-mode access */
  uint8_t x : 1;      /* Execute */
  uint8_t w : 1;      /* Write */
  uint8_t r : 1;      /* Read */
  uint8_t v : 1;      /* Valid */

  bool is_leaf() {
    return (r == 1) || (x == 1);
  }
};

struct Sv57PTE {
  uint32_t n : 1;    /* Extension: Svnapot */
  uint32_t pbmt : 2; /* Extension: Svpbmt */
  uint32_t reserved : 7;
  uint32_t ppn4 : 8; /* PPN[4] */
  uint32_t ppn3 : 9; /* PPN[3] */
  uint32_t ppn2 : 9; /* PPN[2] */
  uint32_t ppn1 : 9; /* PPN[1] */
  uint32_t ppn0 : 9; /* PPN[0] */
  uint8_t rsw : 2;   /* Reserved for supervisor */
  uint8_t d : 1;     /* Dirty */
  uint8_t a : 1;     /* Accessed */
  uint8_t g : 1;     /* Global mapping */
  uint8_t u : 1;     /* U-mode access */
  uint8_t x : 1;     /* Execute */
  uint8_t w : 1;     /* Write */
  uint8_t r : 1;     /* Read */
  uint8_t v : 1;     /* Valid */

  bool is_leaf() {
    return (r == 1) || (x == 1);
  }
};

#if VM_VADDR_SIZE == 32  // Sv32

using VAddr = Sv32VAddr;
using PAddr = Sv32PAddr;
using PTE = Sv32PTE;

#elif VM_VADDR_SIZE == 39  // Sv39

using VAddr = Sv39VAddr;
using PAddr = Sv39PAddr;
using PTE = Sv39PTE;

#elif VM_VADDR_SIZE == 48  // Sv48

using VAddr = Sv48VAddr;
using PAddr = Sv48PAddr;
using PTE = Sv48PTE;

#elif VM_VADDR_SIZE == 57  // Sv57

using VAddr = Sv57VAddr;
using PAddr = Sv57PAddr;
using PTE = Sv57PTE;

#endif

constexpr size_t kPageSize = 4096;
constexpr size_t kPageSizeBits = 12;

class PhysicalMemoryManager {
 private:
  PAddr *free_stack;
  size_t free_stack_size;

 public:
  PhysicalMemoryManager(size_t dram_base, size_t dram_size);

  PAddr alloc_page();
  void free_page(PAddr addr);
};

class PageTable {
 public:
  PageTable();

  void enable();
  void disable();
};

}  // namespace memory
}  // namespace tinyrvk
