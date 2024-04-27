#pragma once
#include "base.h"

class Negative : public BaseFilterPixel {
public:
    Negative();
    void ApplyToPixel(Image& image, int32_t x, int32_t y) const final;
};