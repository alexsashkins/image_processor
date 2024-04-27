#include "base.h"

BaseFilter::~BaseFilter() {
}
void BaseFilterPixel::Apply(Image& image) const {
    for (int32_t i = 0; i < image.Getheight(); ++i) {
        for (int32_t j = 0; j < image.Getwidth(); ++j) {
            ApplyToPixel(image, j, i);
        }
    }
}

BaseFilterWMatr::BaseFilterWMatr(std::array<std::array<float, 3>, 3> matr) {
    for (int32_t i = 0; i < 3; ++i) {
        for (int32_t j = 0; j < 3; ++j) {
            matr_[i][j] = matr[i][j];
        }
    }
}

void BaseFilterWMatr::Apply(Image& image) const {
    auto heigth_i = image.Getheight();
    auto width_i = image.Getwidth();
    std::vector<std::vector<RGB>> new_pix(heigth_i, std::vector<RGB>(width_i));
    for (int32_t i = 0; i < heigth_i; ++i) {
        for (int32_t j = 0; j < width_i; ++j) {
            std::array<std::array<RGB, 3>, 3> pix;
            for (int32_t a = 0; a < 3; ++a) {
                for (int32_t b = 0; b < 3; ++b) {
                    int32_t new_x = std::min(heigth_i - 1, std::max(i + a - 1, 0));
                    int32_t new_y = std::min(width_i - 1, std::max(j + b - 1, 0));
                    pix[a][b] = image.Getcolour(new_y, new_x);
                }
            }
            float new_red = 0;
            float new_blue = 0;
            float new_green = 0;
            for (int32_t a = 0; a < 3; ++a) {
                for (int32_t b = 0; b < 3; ++b) {
                    new_red += pix[a][b].red * matr_[a][b];
                    new_green += pix[a][b].green * matr_[a][b];
                    new_blue += pix[a][b].blue * matr_[a][b];
                }
            }
            new_red = std::min(static_cast<float>(1), std::max(static_cast<float>(0), new_red));
            new_blue = std::min(static_cast<float>(1), std::max(static_cast<float>(0), new_blue));
            new_green = std::min(static_cast<float>(1), std::max(static_cast<float>(0), new_green));
            RGB new_pixel(new_red, new_blue, new_green);
            new_pix[i][j] = new_pixel;
        }
    }
    for (int32_t i = 0; i < heigth_i; ++i) {
        for (int32_t j = 0; j < width_i; ++j) {
            image.Setcolour(new_pix[i][j], j, i);
        }
    }
}
