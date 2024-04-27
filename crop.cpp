#include "crop.h"

Crop::Crop(int32_t new_height, int32_t new_width) {
    n_heigth_ = new_height;
    n_width_ = new_width;
}
void Crop::Apply(Image& image) const {
    image.ChangeSize(n_width_, n_heigth_);
}
