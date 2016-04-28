#ifndef DFSPARKS_EFFECT_PLASMA_H
#define DFSPARKS_EFFECT_PLASMA_H
#include <DFSParks_Color.h>
#include <DFSParks_Math.h>
#include <DFSparks_Effect.h>

namespace dfsparks {

template <typename Pixels> class Plasma : public Effect<Pixels> {
public:
  Plasma(int32_t sp) : speed(sp) {}

private:
  void on_render(Pixels &pixels) override {
    int32_t elapsed = this->get_elapsed_time();
    int width = Pixels::width;
    int height = Pixels::height;

    uint8_t offset = speed * elapsed / 255;
    int plasVector = offset * 16;

    // Calculate current center of plasma pattern (can be offscreen)
    int xOffset = cos8(plasVector / 256);
    int yOffset = sin8(plasVector / 256);

    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        uint8_t hue = sin8(sqrt(square(((float)x - 7.5) * 10 + xOffset - 127) +
                                square(((float)y - 2) * 10 + yOffset - 127)) +
                           offset);
        pixels.set_color(x, y, hsl(hue, 255, 255));
      }
    }
  }

  int32_t speed;
};

} // namespace dfsparks

#endif /* DFSPARKS_EFFECT_PLASMA_H */