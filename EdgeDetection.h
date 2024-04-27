#pragma once
#include "base.h"

class EdgeDet : public BaseFilterWMatr {
public:
    EdgeDet();
};

class EdgeDetTh : public BaseFilterPixel {
public:
    explicit EdgeDetTh(float thresold);
    void ApplyToPixel(Image& image, int32_t x, int32_t y) const final;

private:
    float threshold_;
};