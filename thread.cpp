#include "thread.hpp"

extern "C" void emulate_s_trap();

namespace tinyrvk {
namespace threads {

static TaskSystem *ts{nullptr};

TaskSystem::TaskSystem(memory::PhysicalMemoryManager &pmm) : pmm(pmm) {
  ts = this;

  tcb_array = (ThreadControlBlock *)pmm.alloc_page().addr;

  num_threads = 1;
  tcb_array[0].thread_id = ThreadID{0};

  // Simulate a software trap
  emulate_s_trap();
}

}  // namespace threads
}  // namespace tinyrvk