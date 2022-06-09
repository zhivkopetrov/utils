/*
 * ThreadSafeQueue.h
 *  @brief: thread-safe multiple producer, multiple consumer queue
 */

#ifndef UTILS_THREADSAFEQUEUE_H_
#define UTILS_THREADSAFEQUEUE_H_

// System headers
#include <condition_variable>
#include <memory>
#include <chrono>
#include <mutex>
#include <queue>
#include <utility>

// Other libraries headers

// Own components headers
#include "utils/class/NonCopyable.h"
#include "utils/class/NonMoveable.h"

// Forward Declarations

struct WaitOutcome {
  bool isShutdowned = false;
  bool hasTimedOut = false;
};

template <typename T>
class ThreadSafeQueue : public NonCopyable, public NonMoveable {
public:
  /** @brief used to push new elements to the queue
   *
   *         NOTE: push() method moves the pushed data,
   *                                              rather than copying it.
   *
   *  @param T && - rvalue reference to the data that is being pushed
   * */
  void push(T &&newData) {
    // lock the queue
    std::unique_lock<std::mutex> lock(_mutex);

    // push the data to queue by moving it
    _data.push(std::move(newData));

    /** Manually unlock the queue since we want to notify any threads
     * that are waiting for data
     * */
    lock.unlock();

    // notify one blocked thread
    _condVar.notify_one();
  }

  /** @brief used to push new elements to the queue
   *
   *         NOTE: use pushWithCopy() method only when you have a
   *               good reason not to have your original resource moved.
   *               pushWithCopy() method copies the pushed data,
   *                                              rather than moving it.
   *
   *  @param const T & - reference to the data that is being pushed
   * */
  void pushWithCopy(const T &newData) {
    // lock the queue
    std::unique_lock<std::mutex> lock(_mutex);

    // push the data to queue by copying it
    _data.push(newData);

    /** Manually unlock the mutex since we want to notify any threads
     * that are waiting for data
     * */
    lock.unlock();

    // notify one blocked thread
    _condVar.notify_one();
  }

  /** @brief used to acquire data from the queue.
   *
   *         NOTE: if queue is empty - the thread is put to sleep with
   *               a condition variable and when new data is being pushed
   *               into the queue or the timeout hits -
   *               the thread is woken up again
   *
   *  @param T &    - reference to the value that is being popped
   *                                                       from the queue
   *  @param const std::chrono::microseconds& - timeout to wait (60s default)
   *
   *  @returns WaitOutcome - has success and timed out
   * */
  WaitOutcome waitAndPop(T &value, const std::chrono::microseconds &timeout =
      std::chrono::microseconds(60000000)) {
    // lock the queue
    std::unique_lock<std::mutex> lock(_mutex);

    /** Condition variables can be subject to spurious wake-ups,
     *  so it is important to check the actual condition
     *  being waited for when the call to wait returns
     * */
    const bool hasTimedOut = !_condVar.wait_for(lock, timeout, [this]() {
      if (!_isShutdowned && _data.empty()) {
        return false;
      }
      return true;
    });

    if (_isShutdowned || hasTimedOut) {
      return WaitOutcome{_isShutdowned, hasTimedOut};
    }

    // acquire the data from the queue
    value = std::move(_data.front());

    // pop the 'moved' queue node
    _data.pop();

    return WaitOutcome{};
  }

  /** @brief used to acquire data from the queue.
   *
   *         NOTE: if queue is empty - the thread is put to sleep with
   *               a condition variable and when new data is being pushed
   *               into the queue - the thread is woken up again
   *
   *  @param const std::chrono::microseconds& - timeout to wait (60s default)
   *
   *  @return - unique_ptr to the value that is being popped from the queue
   * */
  std::unique_ptr<T> waitAndPop(const std::chrono::microseconds &timeout =
      std::chrono::microseconds(60000000)) {
    // lock the queue
    std::unique_lock<std::mutex> lock(_mutex);

    /** Condition variables can be subject to spurious wake-ups,
     *  so it is important to check the actual condition
     *  being waited for when the call to wait returns
     * */
    const bool hasTimedOut = !_condVar.wait_for(lock, timeout, [this]() {
      if (!_isShutdowned && _data.empty()) {
        return false;
      }
      return true;
    });

    if (_isShutdowned || hasTimedOut) {
      return nullptr;
    }

    // acquire the data from the queue
    std::unique_ptr<T> res(std::make_unique<T>(std::move(_data.front())));

    // pop the 'moved' queue node
    _data.pop();

    return res;
  }

  /** @brief used to try and acquire data from the queue.
   *
   *         NOTE: if queue is not empty - the data from the queue is
   *               being moved to the T & value function argument
   *
   *  @param bool - pop was successful or not
   * */
  bool tryPop(T &value) {
    // lock the queue
    std::lock_guard<std::mutex> lock(_mutex);

    if (_isShutdowned || _data.empty()) {
      return false;
    }

    // acquire the data from the queue
    value = std::move(_data.front());

    // pop the 'moved' queue node
    _data.pop();

    // try_pop() succeeded -> return true status
    return true;
  }

  /** @brief used to try and acquire data from the queue.
   *
   *         NOTE: if queue is not empty - the data from the queue is
   *               being moved to the T & value function argument
   *
   *  @param std::unique_ptr<T> - unique_ptr to the value
   *                                  that is being popped from the queue.
   *
   *                              If unique_ptr is empty -
   *                                            the pop was not successful
   * */
  std::unique_ptr<T> tryPop() {
    // lock the queue
    std::lock_guard<std::mutex> lock(_mutex);

    if (_isShutdowned || _data.empty()) {
      return nullptr;
    }

    // acquire the data from the queue and pop
    std::unique_ptr<T> res(std::make_unique<T>(std::move(_data.front())));

    // pop the 'moved' queue node
    _data.pop();

    // try_pop() succeeded -> return qnique_ptr to the popped data
    return res;
  }

  /** @brief used check the empty status of the queue.
   *
   *  @param bool - is queue empty or not
   * */
  bool isEmpty() const {
    // lock the queue
    std::lock_guard<std::mutex> lock(_mutex);

    // return empty status
    return _data.empty();
  }

  /** @brief used acquire the size of the queue.
   *
   *  @param uint64_t - the size of the queue container
   * */
  uint64_t size() const {
    // lock the queue
    std::lock_guard<std::mutex> lock(_mutex);

    // return actual queue size
    return _data.size();
  }

  /** @brief used initiate shutdown of the queue
   *         (usually invoking of this method by the developer should be
   *          followed by joining thread producers and thread consumers)
   * */
  void shutdown() {
    // lock the queue
    std::lock_guard<std::mutex> lock(_mutex);

    _isShutdowned = true;

    // notify all block threads that execution must be terminated
    _condVar.notify_all();
  }

  /** @brief used to check if the queue has completed shutdown
   * */
  bool isShutDowned() const {
    // lock the queue
    std::lock_guard<std::mutex> lock(_mutex);
    return _isShutdowned;
  }

private:
  // the actual queue holding the data
  std::queue<T> _data;

  // the queue mutex used for locking on thread-shared resources
  mutable std::mutex _mutex;

  /** Conditional variable used for waking threads that are currently
   * waiting for data to be pushed to the queue (starvation)
   * so they can process it
   * */
  std::condition_variable _condVar;

  /** A flag used to signal waiting thread that user requested
   *  queue shutdown with ::shutdown() method (and will probably
   *  join the threads) afterwards
   *  */
  bool _isShutdowned = false;
};

#endif /* UTILS_THREADSAFEQUEUE_H_ */
