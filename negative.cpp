#include "negative.h"

Negative::Negative() {
}
void Negative::ApplyToPixel(Image& image, int32_t x, int32_t y) const {
    auto pixel = image.Getcolour(x, y);
    pixel.red = 1 - pixel.red;
    pixel.blue = 1 - pixel.blue;
    pixel.green = 1 - pixel.green;
    image.Setcolour(pixel, x, y);
}
