#pragma once
#include "image.h"

#include <array>

class BaseFilter {
public:
    virtual void Apply(Image& image) const = 0;
    virtual ~BaseFilter();
};

class BaseFilterWMatr : public BaseFilter {
public:
    explicit BaseFilterWMatr(std::array<std::array<float, 3>, 3> matr);
    void Apply(Image& image) const final;

private:
    std::array<std::array<float, 3>, 3> matr_;
};

class BaseFilterPixel : public BaseFilter {
public:
    void Apply(Image& image) const final;

    virtual void ApplyToPixel(Image& image, int32_t x, int32_t y) const = 0;
};