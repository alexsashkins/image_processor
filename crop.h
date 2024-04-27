#pragma once
#include "base.h"

class Crop : public BaseFilter {
public:
    Crop(int32_t new_height, int32_t new_width);
    void Apply(Image &image) const final;

private:
    int32_t n_heigth_;
    int32_t n_width_;
};