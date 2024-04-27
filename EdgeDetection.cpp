#include "EdgeDetection.h"

const std::array<std::array<float, 3>, 3> EDGE = {{{0, -1, 0}, {-1, 4, -1}, {-0, -1, 0}}};

EdgeDet::EdgeDet() : BaseFilterWMatr(EDGE) {
}
EdgeDetTh::EdgeDetTh(float thresold) {
    threshold_ = thresold;
}
void EdgeDetTh::ApplyToPixel(Image& image, int32_t x, int32_t y) const {
    auto pixel = image.Getcolour(x, y);
    if (pixel.red > threshold_) {
        pixel.red = 1;
        pixel.blue = 1;
        pixel.green = 1;
    } else {
        pixel.red = 0;
        pixel.blue = 0;
        pixel.green = 0;
    }
    image.Setcolour(pixel, x, y);
}
