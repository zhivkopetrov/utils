/*
 * LimitValues.hpp
 *
 *  Use to initialize values with their maximum values.
 */

#ifndef UTILS_LIMITVALUES_H_
#define UTILS_LIMITVALUES_H_

// C system headers

// C++ system headers
#include <cstddef>
#include <cstdint>
#include <limits>

// Other libraries headers

// Own components headers

// Forward Declarations

#define INIT_INT8_VALUE std::numeric_limits<int8_t>::max()
#define INIT_INT16_VALUE std::numeric_limits<int16_t>::max()
#define INIT_INT32_VALUE std::numeric_limits<int32_t>::max()
#define INIT_INT64_VALUE std::numeric_limits<int64_t>::max()

#define INIT_UINT8_VALUE std::numeric_limits<uint8_t>::max()
#define INIT_UINT16_VALUE std::numeric_limits<uint16_t>::max()
#define INIT_UINT32_VALUE std::numeric_limits<uint32_t>::max()
#define INIT_UINT64_VALUE std::numeric_limits<uint64_t>::max()

#define INIT_SIZE_T_VALUE std::numeric_limits<size_t>::max()

#endif /* UTILS_LIMITVALUES_H_ */
