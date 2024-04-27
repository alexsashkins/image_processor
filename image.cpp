#include "image.h"
#include <fstream>

RGB::RGB() : red(0), green(0), blue(0) {
}

RGB::RGB(float red1, float blue1, float green1) {
    red = red1;
    blue = blue1;
    green = green1;
}

RGB::~RGB() {
}

Image::Image(int width, int height) {
    m_width_ = width;
    m_height_ = height;
    pixels_ = std::vector<std::vector<RGB>>(height, std::vector<RGB>(width));
}
Image::~Image() {
}
int32_t Image::Getheight() const {
    return m_height_;
}
int32_t Image::Getwidth() const {
    return m_width_;
}
RGB Image::Getcolour(int x, int y) const {
    return pixels_[y][x];
}
void Image::Setcolour(const RGB& colour, int x, int y) {
    pixels_[y][x].red = colour.red;
    pixels_[y][x].green = colour.green;
    pixels_[y][x].blue = colour.blue;
}
void Image::Export(const char* path) const {
    std::ofstream fileout;
    fileout.open(path, std::ifstream::out | std::ifstream::binary);
    unsigned char bmp_pad[3] = {0, 0, 0};
    const int paddingamount = (((4 - ((m_width_ * 3) % 4)) % 4) % 4);
    const int file_header_size = 14;
    const int info_header_size = 40;
    const int file_size = file_header_size + info_header_size + m_width_ * m_height_ * 3 + paddingamount * m_height_;
    unsigned char file_header[file_header_size];
    file_header[0] = 'B';
    file_header[1] = 'M';
    file_header[2] = file_size;
    file_header[3] = file_size >> 8;                        // NOLINT
    file_header[4] = file_size >> 16;                       // NOLINT
    file_header[5] = file_size >> 24;                       // NOLINT
    file_header[6] = 0;                                     // NOLINT
    file_header[7] = 0;                                     // NOLINT
    file_header[8] = 0;                                     // NOLINT
    file_header[9] = 0;                                     // NOLINT
    file_header[10] = file_header_size + info_header_size;  // NOLINT
    file_header[11] = 0;                                    // NOLINT
    file_header[12] = 0;                                    // NOLINT
    file_header[13] = 0;                                    // NOLINT
    unsigned char info_header[info_header_size];
    info_header[0] = info_header_size;
    info_header[1] = 0;
    info_header[2] = 0;
    info_header[3] = 0;
    info_header[4] = m_width_;
    info_header[5] = m_width_ >> 8;     // NOLINT
    info_header[6] = m_width_ >> 16;    // NOLINT
    info_header[7] = m_width_ >> 24;    // NOLINT
    info_header[8] = m_height_;         // NOLINT
    info_header[9] = m_height_ >> 8;    // NOLINT
    info_header[10] = m_height_ >> 16;  // NOLINT
    info_header[11] = m_height_ >> 24;  // NOLINT
    info_header[12] = 1;                // NOLINT
    info_header[13] = 0;                // NOLINT
    info_header[14] = 24;               // NOLINT
    info_header[15] = 0;                // NOLINT
    info_header[16] = 0;                // NOLINT
    info_header[17] = 0;                // NOLINT
    info_header[18] = 0;                // NOLINT
    info_header[19] = 0;                // NOLINT
    info_header[20] = 0;                // NOLINT
    info_header[21] = 0;                // NOLINT
    info_header[22] = 0;                // NOLINT
    info_header[23] = 0;                // NOLINT
    info_header[24] = 0;                // NOLINT
    info_header[25] = 0;                // NOLINT
    info_header[26] = 0;                // NOLINT
    info_header[27] = 0;                // NOLINT
    info_header[28] = 0;                // NOLINT
    info_header[29] = 0;                // NOLINT
    info_header[30] = 0;                // NOLINT
    info_header[31] = 0;                // NOLINT
    info_header[32] = 0;                // NOLINT
    info_header[33] = 0;                // NOLINT
    info_header[34] = 0;                // NOLINT
    info_header[35] = 0;                // NOLINT
    info_header[36] = 0;                // NOLINT
    info_header[37] = 0;                // NOLINT
    info_header[38] = 0;                // NOLINT
    info_header[39] = 0;                // NOLINT
    fileout.write(reinterpret_cast<char*>(file_header), file_header_size);
    fileout.write(reinterpret_cast<char*>(info_header), info_header_size);
    for (int y = 0; y < m_height_; ++y) {
        for (int x = 0; x < m_width_; ++x) {
            unsigned char r = static_cast<unsigned char>(Getcolour(x, y).red * 255.0f);    // NOLINT
            unsigned char g = static_cast<unsigned char>(Getcolour(x, y).green * 255.0f);  // NOLINT
            unsigned char b = static_cast<unsigned char>(Getcolour(x, y).blue * 255.0f);   // NOLINT
            unsigned char colour[] = {b, g, r};
            fileout.write(reinterpret_cast<char*>(colour), 3);
        }
        fileout.write(reinterpret_cast<char*>(bmp_pad), paddingamount);
    }
    fileout.close();
}

void Image::Read(const char* path) {
    std::ifstream filein;
    filein.open(path, std::ifstream::in | std::ifstream::binary);
    const int file_header_size = 14;
    const int info_header_size = 40;
    unsigned char fileheader[file_header_size];
    filein.read(reinterpret_cast<char*>(fileheader), file_header_size);
    unsigned char infoheader[info_header_size];
    filein.read(reinterpret_cast<char*>(infoheader), info_header_size);
    m_width_ = infoheader[4] + (infoheader[5] << 8) + (infoheader[6] << 16) + (infoheader[7] << 24);     // NOLINT
    m_height_ = infoheader[8] + (infoheader[9] << 8) + (infoheader[10] << 16) + (infoheader[11] << 24);  // NOLINT
    pixels_.resize(m_height_, std::vector<RGB>(m_width_));
    const int padding = (((4 - ((m_width_ * 3) % 4)) % 4) % 4);
    for (int y = 0; y < m_height_; ++y) {
        for (int x = 0; x < m_width_; ++x) {
            unsigned char colour[3];
            filein.read(reinterpret_cast<char*>(colour), 3);
            pixels_[y][x].red = static_cast<float>(colour[2]) / 255.0f;    // NOLINT
            pixels_[y][x].green = static_cast<float>(colour[1]) / 255.0f;  // NOLINT
            pixels_[y][x].blue = static_cast<float>(colour[0]) / 255.0f;   // NOLINT
        }
        filein.ignore(padding);
    }
    filein.close();
}
void Image::ChangeSize(int32_t width, int32_t height) {
    int32_t yk = 0;
    for (int32_t i = m_height_ - std::min(height, m_height_); i < m_height_; ++i) {
        swap(pixels_[i], pixels_[yk]);
        ++yk;
    }
    m_width_ = std::min(width, m_width_);
    m_height_ = std::min(height, m_height_);
}
