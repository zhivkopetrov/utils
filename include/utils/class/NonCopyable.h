#ifndef UTILS_NONCOPYABLE_H_
#define UTILS_NONCOPYABLE_H_

// System headers

// Other libraries headers

// Own components headers

// Forward declarations

class NonCopyable {
public:
  NonCopyable() = default;
  NonCopyable(const NonCopyable& other) = delete;
  NonCopyable& operator=(const NonCopyable& other) = delete;
};

#endif /* UTILS_NONCOPYABLE_H_ */
