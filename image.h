#pragma once
#include <vector>

struct RGB {
    RGB();
    float red;
    float green;
    float blue;
    RGB(float red1, float blue1, float green1);
    ~RGB();
};

class Image {
public:
    Image(int width, int heigth);
    ~Image();

    RGB Getcolour(int x, int y) const;
    int32_t Getheight() const;
    int32_t Getwidth() const;
    void ChangeSize(int32_t width, int32_t heigth);
    void Setcolour(const RGB& colour, int x, int y);

    void Export(const char* path) const;
    void Read(const char* path);

private:
    int m_width_;
    int m_height_;
    std::vector<std::vector<RGB>> pixels_;
};