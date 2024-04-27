#include "Grayscale.h"
const float F_R = 0.299;
const float F_B = 0.114;
const float F_G = 0.587;
Grayscale::Grayscale() {
}

void Grayscale::ApplyToPixel(Image& image, int32_t x, int32_t y) const {
    auto pixel = image.Getcolour(x, y);
    pixel.red = pixel.red * F_R + pixel.blue * F_B + pixel.green * F_G;
    pixel.blue = pixel.red;
    pixel.green = pixel.red;
    image.Setcolour(pixel, x, y);
}
