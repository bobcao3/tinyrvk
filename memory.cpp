#include "memory.hpp"

extern "C" size_t _bss_end;

namespace tinyrvk {
namespace memory {

PhysicalMemoryManager::PhysicalMemoryManager(size_t dram_base, size_t dram_size) {
  size_t head = (size_t)&_bss_end;
  free_stack = (PAddr*)head;
  head += (dram_size >> kPageSizeBits) * sizeof(size_t);

  head = align_up_pot(head, kPageSizeBits);

  size_t available_dram = (dram_base + dram_size - head) ;
  size_t num_stack_pages = 2;
  size_t available_pages = (available_dram >> kPageSizeBits) - num_stack_pages;
  free_stack_size += available_pages;

  PAddr curr_page { .addr = head };
  for (size_t i = 0; i < available_pages; i++) {
    free_stack[i] = curr_page;
    curr_page.addr += kPageSize;
  }
}

PAddr PhysicalMemoryManager::alloc_page() {
  if (free_stack_size == 0) {
    return PAddr{ .addr = 0 };
  }
  free_stack_size--;
  return free_stack[free_stack_size];
}

void PhysicalMemoryManager::free_page(PAddr addr) {
  free_stack[free_stack_size] = addr;
  free_stack_size++;
}

}  // namespace memory
}  // namespace tinyrvk