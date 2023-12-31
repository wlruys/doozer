#pragma once
#ifndef CYTHON_SLEEP_H
#define CYTHON_SLEEP_H

#include <chrono>
#include <cstdint>
#include <time.h>
#include <unistd.h>

#ifdef DOOZER_ENABLE_NVTX
#include <nvtx3/nvtx3.hpp>
#endif

using namespace std;
using namespace chrono;

void cpu_busy_sleep(const uint64_t micro) {

#ifdef DOOZER_ENABLE_NVTX
  nvtx3::scoped_range r{"cpp::cpu_busy_sleep"};
#endif

  auto block = chrono::microseconds(micro);
  auto time_start = chrono::high_resolution_clock::now();

  auto now = chrono::high_resolution_clock::now();
  auto elapsed = chrono::duration_cast<chrono::microseconds>(now - time_start);

  do {
    now = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::microseconds>(now - time_start);
  } while (elapsed.count() < micro);
}

void gpu_busy_sleep(const int device, const uint64_t t, intptr_t stream_ptr);

#endif
