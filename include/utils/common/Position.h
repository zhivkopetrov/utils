#ifndef UTILS_POSITION_H_
#define UTILS_POSITION_H_

// C system headers

// C++ system headers
#include <cstdint>

// Other libraries headers

// Own components headers

// Forward declarations
struct Rectangle;
struct Point;

class Position {
 public:
  Position() = delete;

  /** @brief Use to draw image/text in center of rectangle
   *
   *   @param Rectangle rec  - coordinate of rectangle
   *   @param int32_t width  - width of object that must to be centered
   *   @param int32_t height - height of object that must to be centered
   *
   *   @return Point to start drawing
   */
  static Point getCentral(const Rectangle& rec, const int32_t width,
                          const int32_t height);

  /** @brief Calculate x point to start drawing in center
   *
   *   @param int32_t sectionX      - start coordinate of the straight line
   *   @param int32_t sectionHeidht - width of the straight line
   *   @param int32_t imageHeight   - width of image to centering
   *
   *   @return int32_t              - x point
   */
  static inline int32_t getMiddleX(const int32_t sectionX,
                                   const int32_t sectionWidth,
                                   const int32_t imageWidth) {
    return sectionX + ((sectionWidth - imageWidth) / 2);
  }

  /** @brief Calculate y point to start drawing in center
   *
   *   @param int32_t sectionY      - start coordinate of the straight line
   *   @param int32_t sectionHeidht - height of the straight line
   *   @param int32_t imageHeight   - height of image to centering
   *
   *   @return int32_t              - y point
   */
  static inline int32_t getMiddleY(const int32_t sectionY,
                                   const int32_t sectionHeight,
                                   const int32_t imageHeight) {
    return sectionY + ((sectionHeight - imageHeight) / 2);
  }

  /** @brief Use to draw image/text aligned to the right side of rectangle
   *
   *   @param Rectangle rec  - coordinate of rectangle
   *   @param int32_t width  - width of object that must to be centered
   *   @param int32_t height - height of object that must to be centered
   *
   *   @return Point to start drawing
   */
  static Point getRightMiddle(const Rectangle& rec, const int32_t width,
                              const int32_t height);

  /** @brief Calculate x point to start drawing aligned to the right
   *
   *   @param int32_t sectionX      - start coordinate of the straight line
   *   @param int32_t sectionHeidht - height of the straight line
   *   @param int32_t imageHeight   - height of image to centering
   *
   *   @return int32_t              - x point
   */
  static inline int32_t getRightX(const int32_t sectionX,
                                  const int32_t sectionWidth,
                                  const int32_t imageWidth) {
    return sectionX + (sectionWidth - imageWidth);
  }
};

#endif  // UTILS_POSITION_H_
