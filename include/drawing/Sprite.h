#ifndef UTILS_INCLUDE_DRAWING_SPRITE_H_
#define UTILS_INCLUDE_DRAWING_SPRITE_H_

// C system headers

// C++ system headers
#include <cstdint>
#include <vector>

// Other libraries headers

// Own components headers
#include "utils/include/drawing/Rectangle.h"

class Sprite {
 public:
  Sprite();
  ~Sprite();

  /** @brief used to load spriteData(precise frame Rectangle coordinates)
   *                                                    from resources.bin
   *
   *  @param const uint64_t - unique resource ID
   *  @param const std::vector<Rectangle> & - spriteData from
   *                                                        resources.bin
   * */
  void init(const uint64_t rsrcId, const std::vector<Rectangle>& spriteData);

  /** @brief used to unload spriteData
   * */
  void deinit();

  /** @brief used to set current frame Rectangle.
   *         Even if Image does not have sprites it is still valid to
   *         call setFrame(0)
   *
   *  @param const int32_t - input frame index
   * */
  void setFrame(const int32_t frameIndex);

  /** @brief used to obtain currently set frame index
   *
   *  @param int32_t - frame index
   * */
  inline int32_t getFrame() const { return _currFrame; }

  /** @brief used to obtain currently set frame index
   *         NOTE: since index is used every as an int32_T -> static_cast
   *                   it here to prevent casts all across the code base.
   *
   *  @return int32_t - total frame count
   * */
  inline int32_t getFrameCount() const {
    return static_cast<int32_t>(_spriteData.size());
  }

  /** @brief used to set next valid frame index.
   *         NOTE: if maxFrames are reached frame 0 is set.
   * */
  inline void setNextFrame();

  /** @brief used to set previous valid frame index.
   *         NOTE: if -1 index is reached frame _maxFrames - 1 is set.
   * */
  inline void setPrevFrame();

  /** @brief used to manually add an additional frame to the frame vector
   *          Constrains: the frame rectangle must be from the
   *                       same source file image as the original frames
   *  @const Rectangle& - new frame Rectangle dimensions
   * */
  inline void addFrame(const Rectangle& frameRect);

  /** @brief used to acquire the currently set frame rectangle
   *
   *  @returns Rectangle - frame Rectangle dimensions
   * */
  inline Rectangle getFrameRect() const { return _spriteData[_currFrame]; }

  /** @brief used to obtain currently set resource ID for the sprite
   *
   *  @return uint64_t - unique resource ID
   * */
  inline uint64_t getFramesRsrcId() const { return _rsrcId; }

 private:
  // A vector containing all frame Rectangles for the Image owner
  // of the Sprite
  std::vector<Rectangle> _spriteData;

  int32_t _currFrame;
  int32_t _maxFrames;

  // used for LOG functions if a problem occurs
  uint64_t _rsrcId;
};

#endif /* UTILS_INCLUDE_DRAWING_SPRITE_H_ */
