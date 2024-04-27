#pragma once
#include "base.h"

class Grayscale : public BaseFilterPixel {
public:
    Grayscale();
    void ApplyToPixel(Image& image, int32_t x, int32_t y) const final;
};