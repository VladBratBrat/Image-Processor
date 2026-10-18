#ifndef CPP_HSE_BMP_WORKER_H
#define CPP_HSE_BMP_WORKER_H

#include <array>
#include <cstdint>
#include <string>
#include <vector>

static const uint16_t BMP_SIGNATURE = 0x4D42;
static const uint16_t BITS_PER_PIXEL = 24;
static const uint16_t PIXEL_BYTES = 3;

static const float COLOR_BITS = 255.0f;

class BMPImage {
public:
#pragma pack(push, 1)
    struct BMPHeaderInfo {
        uint16_t signature;
        uint32_t file_size;
        uint16_t app_specific1;
        uint16_t app_specific2;
        uint32_t data_offset;
    };
    struct DIBHeaderInfo {
        uint32_t header_size;
        int32_t width;
        int32_t height;
        uint16_t plane;
        uint16_t bits_per_pixel;
        uint32_t compression;
        uint32_t image_size;
        int32_t x_resolution;
        int32_t y_resolution;
        uint32_t colors_used;
        uint32_t colors_important;
    };
#pragma pack(pop)
    struct BMPHeader {
        BMPHeaderInfo file;
        DIBHeaderInfo info;
    };
    struct Pixel {
        float blue_;
        float green_;
        float red_;

        Pixel() = default;

        Pixel(float blue, float green, float red) : blue_{blue}, green_{green}, red_{red} {};

        void operator=(const std::array<uint8_t, 3>& pixel_read);

        Pixel operator*(const float mult) const {
            return Pixel(blue_ * mult, green_ * mult, red_ * mult);
        }

        Pixel operator+(const Pixel& other) const {
            return Pixel(blue_ + other.blue_, green_ + other.green_, red_ + other.red_);
        }

        Pixel operator-(const Pixel& other) const {
            return Pixel(blue_ - other.blue_, green_ - other.green_, red_ - other.red_);
        }

        Pixel& operator+=(const Pixel& other) {
            blue_ += other.blue_;
            green_ += other.green_;
            red_ += other.red_;
            return *this;
        }

        Pixel& operator*=(const float mult) {
            blue_ *= mult;
            green_ *= mult;
            red_ *= mult;
            return *this;
        }

        void Limit();

        std::array<uint8_t, 3> GetInts() const;
    };

    BMPImage() = default;
    ~BMPImage() = default;
    BMPImage& operator=(const BMPImage&) = default;

    int32_t GetWidth() const {
        return bmp_header_.info.width;
    }

    int32_t GetHeight() const {
        return bmp_header_.info.height;
    }

    void SetHeight(const int32_t height) {
        bmp_header_.info.height = height;
    }

    void SetWidth(const int32_t width) {
        bmp_header_.info.width = width;
    }

    enum class BMPResult { OK, InputFileNotOpened, ImageIsNotBMP, ImageBMPIsNot24Bits, OutputFileNotOpened };

    BMPResult ReadFromFile(const std::string& path);

    BMPResult WriteToFile(const std::string& path);

    const BMPHeader& GetBMPHeader() const {
        return bmp_header_;
    }

    std::vector<std::vector<Pixel>>& GetPixels() {
        return pixels_;
    }

private:
    BMPHeader bmp_header_;
    std::vector<std::vector<Pixel>> pixels_;
};

#endif  // CPP_HSE_BMP_WORKER_H