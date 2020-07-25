// Corresponding header
#include "utils/common/CircularBuffer.h"

// C system headers

// C++ system headers
#include <algorithm>  //for std::min
#include <cstring>

// Other libraries headers

// Own components headers
#include "utils/ErrorCode.h"
#include "utils/Log.h"

// default constructor
CircularBuffer::CircularBuffer()
    : _buf(nullptr), _capacity(0), _readIndex(0), _writeIndex(0) {}

// move constructor
CircularBuffer::CircularBuffer(CircularBuffer&& movedOther) {
  // take ownership of resources
  _buf = movedOther._buf;
  _capacity = movedOther._capacity;
  _readIndex = movedOther._readIndex;
  _writeIndex = movedOther._writeIndex;

  // ownership of resource should be taken from moved instance
  movedOther._buf = nullptr;
  movedOther._capacity = 0;
  movedOther._readIndex = 0;
  movedOther._writeIndex = 0;
}

// move assignment operator
CircularBuffer& CircularBuffer::operator=(CircularBuffer&& movedOther) {
  // check for self-assignment
  if (this != &movedOther) {
    // take ownership of resources
    _buf = movedOther._buf;
    _capacity = movedOther._capacity;
    _readIndex = movedOther._readIndex;
    _writeIndex = movedOther._writeIndex;

    // ownership of resource should be taken from moved instance
    movedOther._buf = nullptr;
    movedOther._capacity = 0;
    movedOther._readIndex = 0;
    movedOther._writeIndex = 0;
  }

  return *this;
}

CircularBuffer::~CircularBuffer() {
  if (_buf)  // sanity check
  {
    delete[] _buf;
    _buf = nullptr;
  }
}

int32_t CircularBuffer::init(const uint64_t capacity) {
  if (_buf) {
    LOGERR("CircularBuffer already initialized! Will not initialize twice");
    return FAILURE;
  }

  _buf = new uint8_t[capacity];
  if (nullptr == _buf) {
    LOGERR("Error, bad alloc for _buf");
    return FAILURE;
  }

  _capacity = capacity;
  memset(_buf, 0, _capacity);

  return SUCCESS;
}

uint64_t CircularBuffer::read(uint8_t* outData, const uint64_t bytes) {
  const uint64_t bytesRead = readNoAdvance(outData, bytes);

  updateIndex(bytesRead, _readIndex);

  return bytesRead;
}

uint64_t CircularBuffer::readNoAdvance(uint8_t* outData, const uint64_t bytes) {
  const uint64_t FIRST_READ_BYTES = std::min(bytes, getUsed());
  const uint64_t SECOND_READ_BYTES =
      std::min(FIRST_READ_BYTES, _capacity - _readIndex);

  memcpy(outData, _buf + _readIndex, SECOND_READ_BYTES);

  memcpy(outData + SECOND_READ_BYTES, _buf,
         FIRST_READ_BYTES - SECOND_READ_BYTES);

  return FIRST_READ_BYTES;
}

uint64_t CircularBuffer::write(const uint8_t* data, const uint64_t bytes) {
  const uint64_t FIRST_WRITE_BYTES = std::min(bytes, getFree());
  const uint64_t SECOND_WRITE_BYTES =
      std::min(FIRST_WRITE_BYTES, _capacity - _writeIndex);

  memcpy(_buf + _writeIndex, data, SECOND_WRITE_BYTES);

  memcpy(_buf, data + SECOND_WRITE_BYTES,
         FIRST_WRITE_BYTES - SECOND_WRITE_BYTES);

  updateIndex(FIRST_WRITE_BYTES, _writeIndex);

  return bytes;
}

void CircularBuffer::reset() {
  if (nullptr != _buf) {
    memset(_buf, 0, _capacity);
  }

  _readIndex = 0;
  _writeIndex = 0;
}
