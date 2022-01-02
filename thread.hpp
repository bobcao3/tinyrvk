#pragma once

#include "common.hpp"

#include "memory.hpp"

namespace tinyrvk {
namespace threads {

using ThreadID = size_t;

constexpr ThreadID kInvalidThreadID = std::numeric_limits<size_t>::max();

class TaskSystem {
 private:
  memory::PhysicalMemoryManager &pmm;

  struct ThreadControlBlock {
    ThreadID thread_id{kInvalidThreadID};
    void *stack{nullptr};

    // Context
    void *pc{nullptr};
    uint64_t gpr[31]{0};
  };

  size_t num_threads{0};
  ThreadControlBlock *tcb_array;

  ThreadID current_thread{0};

 public:
  TaskSystem(memory::PhysicalMemoryManager &pmm);

  ThreadID create_thread(void(* start_addr));

  void yield();
  void terminate();
  
  void sched();
};

}
}
