// Corresponding header
#include "utils/concurrency/ThreadPool.h"

// System headers

// Other libraries headers

// Own components headers
#include "utils/Log.h"

namespace {
uint32_t computeMaxWorkerThreads(uint32_t workersCount) {
  const uint32_t maxHardwareThreads = std::thread::hardware_concurrency();
  if (0 == maxHardwareThreads) {
    workersCount = 1;
    LOGY(
        "std::thread::hardware_concurrency() hint failed -> falling back to "
        "a single thread");
  } else if (0 == workersCount) {
    workersCount = maxHardwareThreads;
  } else if (workersCount > maxHardwareThreads) {
    LOGY(
        "workersThreadsCount requested [%u] more that maxHardwareThreads [%u]. "
        "Falling back to maxHardwareThreads",
        workersCount, maxHardwareThreads);
    workersCount = maxHardwareThreads;
  }

  return workersCount;
}
}  // namespace

void ThreadPool::init(uint32_t workersCount) {
  mWorkersCount = computeMaxWorkerThreads(workersCount);
  mWorkers.reserve(mWorkersCount);

  mWorkerLoop = [this]() {
    TaskCb taskCb;
    while (true) {
      using namespace std::literals;
      const auto [isShutdowned, hasTimedOut] = mTasks.waitAndPop(taskCb, 60s);
      if (isShutdowned) {
        break;
      }

      if (hasTimedOut) {
        continue;
      }

      taskCb();
    }
  };
}

void ThreadPool::start() {
  LOG("Starting ThreadPool with [%u] workerThreads", mWorkersCount);
  for (uint32_t i = 0; i < mWorkersCount; ++i) {
    mWorkers.emplace_back(mWorkerLoop);
  }
}

void ThreadPool::shutdown() {
  mTasks.shutdown();
  for (std::thread& worker : mWorkers) {
    worker.join();
  }
}

uint32_t ThreadPool::getWorkersCount() const { return mWorkersCount; }
