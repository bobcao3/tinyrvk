#include "memory.hpp"

namespace tinyrvk {
namespace memory {

PhysicalMemoryManager::PhysicalMemoryManager(size_t dram_base, size_t dram_size) : bitmap(_heap_start) {
  size_t bitmap_end = _heap_start + BitMap::compute_size(dram_size >> kPageSizeBits);
  size_t bitmap_end_page = (bitmap_end >> kPageSizeBits) + ((bitmap_end & (kPageSize - 1)) ? 1 : 0);
  free_stack = (PAddr *)(bitmap_end);

  size_t available_dram = (dram_size - _heap_start) ;
  size_t num_stack_pages = 1;
  size_t available_pages = (available_dram >> kPageSizeBits) - num_stack_pages;
  free_stack_size += available_pages;

  PAddr curr_page { .addr = bitmap_end_page << kPageSizeBits };
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