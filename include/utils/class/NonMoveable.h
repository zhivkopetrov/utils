#ifndef UTILS_NONMOVEABLE_H_
#define UTILS_NONMOVEABLE_H_

// System headers

// Other libraries headers

// Own components headers

// Forward declarations

class NonMoveable {
public:
  NonMoveable() = default;
  NonMoveable(NonMoveable&& other) = delete;
  NonMoveable& operator=(NonMoveable&& other) = delete;
};

#endif /* UTILS_NONMOVEABLE_H_ */
