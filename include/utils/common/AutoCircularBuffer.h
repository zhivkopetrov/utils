/*
 * AutoCircularBuffer.h
 *
 * @brief an automatic storage implementation of the CircularBuffer class.
 *        The AutoCircularBuffer is practically the same as CircularBuffer
 *        with the only difference is that it's data lives on the stack
 *        (if AutoCircularBuffer object was created on the stack),
 *        while CircularBuffers data lives on the heap.
 *
 *        WARNING: use this class only with limited size and only
 *                 for performance-crucial code.
 *                 If used with large enough size -> can directly lead
 *                                                 to stack overflow exception.
 */

#ifndef UTILS_AUTOCIRCULARBUFFER_H_
#define UTILS_AUTOCIRCULARBUFFER_H_

// System headers
#include <algorithm>  //for std::min
#include <cstdint>
#include <cstring>

// Other libraries headers

// Own components headers
#include "utils/class/NonCopyable.h"
#include "utils/class/NonMoveable.h"

// Forward declarations

template <const uint64_t size>
class AutoCircularBuffer : public NonCopyable, public NonMoveable {
 public:
  AutoCircularBuffer() : _capacity(size), _readIndex(0), _writeIndex(0) {
    memset(_buf, 0, sizeof(_buf));
  }

  /** @brief used for reading data from the CircularBuffer
   *
   *  @param uint8_t *      - outData buffer
   *  @param const uint64_t - bytes count to read
   *
   *  @return uint64_t      - bytes actually read
   *                          (less bytes than requested can be returned
   *                          if required bytes count is bigger than
   *                                                used buffer capacity)
   *
   *          NOTE: this method modified the readIndex
   *                                 (so same data can not be read twice)
   * */
  uint64_t read(uint8_t *outData, const uint64_t bytes) {
    const uint64_t bytesRead = readNoAdvance(outData, bytes);

    updateIndex(bytesRead, _readIndex);

    return bytesRead;
  }

  /** @brief used for reading data from the CircilarBuffer
   *
   *  @param uint8_t *      - outData buffer
   *  @param const uint64_t - bytes count to read
   *
   *  @return uint64_t      - bytes actually read
   *                          (less bytes than requested can be returned
   *                          if required bytes count is bigger than
   *                                                used buffer capacity)
   *
   *          NOTE: this method does not modify the readIndex
   *                            (so same data can be read multiple times)
   * */
  uint64_t readNoAdvance(uint8_t *outData, const uint64_t bytes) {
    const uint64_t FIRST_READ_BYTES = std::min(bytes, getUsed());
    const uint64_t SECOND_READ_BYTES =
        std::min(FIRST_READ_BYTES, _capacity - _readIndex);

    memcpy(outData, _buf + _readIndex, SECOND_READ_BYTES);

    memcpy(outData + SECOND_READ_BYTES, _buf,
           FIRST_READ_BYTES - SECOND_READ_BYTES);

    return FIRST_READ_BYTES;
  }

  /** @brief used for writing data to the CircularBuffer
   *
   *  @param const uint8_t * - inData buffer
   *  @param const uint64_t  - bytes count to write
   *
   *  @return uint64_t       - bytes actually written
   *                           (less bytes than requested can be returned
   *                           if required bytes count is bigger than
   *                                                free buffer capacity)
   * */
  uint64_t write(const uint8_t *data, const uint64_t bytes) {
    const uint64_t FIRST_WRITE_BYTES = std::min(bytes, getFree());
    const uint64_t SECOND_WRITE_BYTES =
        std::min(FIRST_WRITE_BYTES, _capacity - _writeIndex);

    memcpy(_buf + _writeIndex, data, SECOND_WRITE_BYTES);

    memcpy(_buf, data + SECOND_WRITE_BYTES,
           FIRST_WRITE_BYTES - SECOND_WRITE_BYTES);

    updateIndex(FIRST_WRITE_BYTES, _writeIndex);

    return bytes;
  }

  /** @brief used to determine the CircularBuffer's free bytes for writing
   *
   *  @return uint64_t - empty bytes for writing count
   * */
  uint64_t getFree() const {
    return (_capacity - 1 - _writeIndex + _readIndex) % _capacity;
  }

  /** @brief used to count the CircularBuffer's occupied bytes
   *
   *  @return uint64_t - occupied bytes from reading count
   * */
  uint64_t getUsed() const {
    return (_writeIndex >= _readIndex) ? _writeIndex - _readIndex
                                       : _capacity - _readIndex + _writeIndex;
  }

  bool isEmpty() const { return _writeIndex == _readIndex; }

  /** @brief used to completely empty the CircularBuffer from it's
   *         content, (like after successful initialization status) */
  void reset();

  /** @brief used to retrieve data from Buffer container
   *
   *        NOTE: the operator >> can be chained to extract multiple
   *              data variables from different types at the same time.
   *
   *        Example: CircularBuffer buff;
   *                 buff.init();
   *                 std::vector<uint8_t> buffer(32, 0xFF);
   *                 buff.write(buffer.data(), buffer.size());
   *
   *                 uint32_t var1 = 0;
   *                 uint64_t var2 = 0;
   *                 uint8_t  var3 = 0;
   *
   *                 buff >> var1 >> var2 >> var3;
   * */
  template <class T>
  AutoCircularBuffer &operator>>(T &value) {
    read(reinterpret_cast<uint8_t *>(&value), sizeof(value));

    return *this;
  }

  /** @brief used to fill data to the Buffer container
   *
   *        NOTE: the operator << can be chained to push multiple
   *              data variables from different types at the same time.
   *
   *        NOTE2: use operator << only for primitive data types.
   *               For more complex types -> use the ::write() methods
   *               instead.
   *
   *        Example: CircularBuffer buff;
   *                 buff.init();
   *
   *                 uint32_t var1 = 0;
   *                 uint64_t var2 = 0;
   *                 uint8_t  var3 = 0;
   *
   *                 buff << var1 << var2 << var3;
   * */
  template <class T>
  AutoCircularBuffer &operator<<(const T value) {
    write(reinterpret_cast<const uint8_t *>(&value), sizeof(value));

    return *this;
  }

 private:
  /** @brief used internally update the read/write index
   *
   *  @param const uint64_t - number of processes bytes
   *  @param uint64_t &     - reference to the current read/write index
   * */
  void updateIndex(const uint64_t processedBytes, uint64_t &index) {
    processedBytes >= (_capacity - index)
        ? index = index + processedBytes - _capacity
        : index = index + processedBytes;
  }

  /* Holds the actual buffer data */
  uint8_t _buf[size];

  /* Holds the buffer maximum capacity */
  uint64_t _capacity;

  /* Holds current read index */
  uint64_t _readIndex;

  /* Holds current write index */
  uint64_t _writeIndex;
};

#endif /* UTILS_AUTOCIRCULARBUFFER_HPP_ */
