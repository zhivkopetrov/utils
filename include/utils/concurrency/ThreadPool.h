#ifndef UTILS_THREADPOOL_H_
#define UTILS_THREADPOOL_H_

// System headers
#include <functional>
#include <future>

// Other libraries headers

// Own components headers
#include "utils/class/NonCopyable.h"
#include "utils/class/NonMoveable.h"
#include "utils/concurrency/ThreadSafeQueue.h"

// Forward Declarations

using TaskCb = std::function<void()>;

class ThreadPool : public NonCopyable, public NonMoveable {
 public:
  void init(uint32_t workersCount = 0);
  void start();
  void shutdown();
  uint32_t getWorkersCount() const;

  template <typename T, class... Args>
  std::future<typename std::invoke_result_t<T, Args...>> submit(
      T&& f, Args&&... args) {
    using return_type = typename std::invoke_result_t<T, Args...>;

    auto packagedTaskPtr = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<T>(f), std::forward<Args>(args)...));
    std::future<return_type> res = packagedTaskPtr->get_future();

    TaskCb task = [packagedTaskPtr]() { (*packagedTaskPtr)(); };
    mTasks.push(std::move(task));

    return res;
  }

 private:
  std::vector<std::thread> mWorkers;
  ThreadSafeQueue<TaskCb> mTasks;
  std::function<void()> mWorkerLoop;
  uint32_t mWorkersCount{};
};

#endif /* UTILS_THREADPOOL_H_ */
