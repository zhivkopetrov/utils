#ifndef UTILS_TOUCHENTITYINTERFACE_H_
#define UTILS_TOUCHENTITYINTERFACE_H_

// System headers

// Other libraries headers

// Own components headers

// Forward Declarations
class TouchEntity;

class TouchEntityInterface {
public:
  virtual ~TouchEntityInterface() noexcept = default;

  virtual void setLastClicked(TouchEntity* lastClicked) = 0;
};

#endif /* UTILS_TOUCHENTITYINTERFACE_H_ */
