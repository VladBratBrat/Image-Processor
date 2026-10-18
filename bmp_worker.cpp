#include <array>
#include <fstream>

#include "bmp_worker.h"

std::array<uint8_t, 3> BMPImage::Pixel::GetInts() const {
    std::array<uint8_t, 3> get_ints = {static_cast<uint8_t>(blue_ * COLOR_BITS),
                                       static_cast<uint8_t>(green_ * COLOR_BITS),
                                       static_cast<uint8_t>(red_ * COLOR_BITS)};
    return get_ints;
}

void BMPImage::Pixel::operator=(const std::array<uint8_t, 3> &pixel_read) {
    blue_ = static_cast<float>(pixel_read[0]) / COLOR_BITS;
    green_ = static_cast<float>(pixel_read[1]) / COLOR_BITS;
    red_ = static_cast<float>(pixel_read[2]) / COLOR_BITS;
}

void BMPImage::Pixel::Limit() {
    this->blue_ = std::max(0.0f, std::min(1.0f, this->blue_));
    this->red_ = std::max(0.0f, std::min(1.0f, this->red_));
    this->green_ = std::max(0.0f, std::min(1.0f, this->green_));
}

BMPImage::BMPResult BMPImage::ReadFromFile(const std::string &path) {
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open()) {
        return BMPResult::InputFileNotOpened;
    }

    file.read(reinterpret_cast<char *>(&bmp_header_.file), sizeof(BMPHeaderInfo));
    file.read(reinterpret_cast<char *>(&bmp_header_.info), sizeof(DIBHeaderInfo));

    if (bmp_header_.file.signature != BMP_SIGNATURE) {
        return BMPResult::ImageIsNotBMP;
    }

    if (bmp_header_.info.bits_per_pixel != BITS_PER_PIXEL) {
        return BMPResult::ImageBMPIsNot24Bits;
    }

    file.seekg(bmp_header_.file.data_offset);

    int32_t width = GetWidth();
    int32_t height = GetHeight();
    uint32_t padding = (4 - (3 * width % 4)) % 4;

    std::vector<uint8_t> pixels_row(PIXEL_BYTES * width);

    for (size_t x = 0; x < abs(height); ++x) {
        pixels_.emplace_back();
    }

    if (height < 0) {
        height = abs(height);
    }

    for (size_t x = height; x >= 1; --x) {
        file.read(reinterpret_cast<char *>(&pixels_row[0]), PIXEL_BYTES * width);
        pixels_[x - 1].resize(width);
        for (size_t y = 0; y < 3 * width; y += 3) {
            pixels_[x - 1][y / 3] = std::array<uint8_t, 3>{pixels_row[y], pixels_row[y + 1], pixels_row[y + 2]};
        }
        file.seekg(padding, std::ios::cur);
    }

    return BMPResult::OK;
}

BMPImage::BMPResult BMPImage::WriteToFile(const std::string &path) {
    std::ofstream file(path, std::ios::binary);

    if (!file.is_open()) {
        return BMPResult::InputFileNotOpened;
    }

    file.write(reinterpret_cast<char *>(&bmp_header_.file), sizeof(BMPHeaderInfo));
    file.write(reinterpret_cast<char *>(&bmp_header_.info), sizeof(DIBHeaderInfo));

    int32_t width = GetWidth();
    int32_t height = GetHeight();
    uint32_t padding = (4 - (3 * width % 4)) % 4;

    std::vector<uint8_t> pixels_row(PIXEL_BYTES * width);

    char padding_byts[3]{0, 0, 0};

    if (height < 0) {
        height = abs(height);
    }

    for (size_t x = height; x >= 1; --x) {
        for (size_t y = 0; y < width; ++y) {
            std::array<uint8_t, 3> single_pixel = pixels_[x - 1][y].GetInts();
            pixels_row[3 * y] = single_pixel[0];
            pixels_row[3 * y + 1] = single_pixel[1];
            pixels_row[3 * y + 2] = single_pixel[2];
        }
        file.write(reinterpret_cast<char *>(&pixels_row[0]), PIXEL_BYTES * width);
        file.write(padding_byts, padding);
    }

    return BMPResult::OK;
}