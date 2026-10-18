#include <cmath>
#include <vector>

#include "bmp_worker.h"
#include "gauss_blur_filter.h"

static const int32_t RADIUS = 20;
static const float PI = static_cast<float>(acos(-1));

void GaussBlurFilter::Apply(BMPImage& image) {
    float sigma = GetSigma();

    AllPixels& pixels = image.GetPixels();

    BMPImage image_copy = image;
    AllPixels& pixels_copy = image_copy.GetPixels();

    int32_t height = image.GetHeight() - 1;
    int32_t width = image.GetWidth() - 1;

    std::vector<float> horizontal;
    float sum_horizontal = 0;

    for (int32_t x = -RADIUS; x <= RADIUS; ++x) {
        horizontal.push_back(std::exp(-static_cast<float>(x * x) / (2 * sigma * sigma)));
        sum_horizontal += horizontal.back();
    }

    for (float& x : horizontal) {
        x /= sum_horizontal;
    }

    for (int32_t x = 0; x <= height; ++x) {
        for (int32_t y = 0; y <= width; ++y) {
            pixels[x][y] = BMPImage::Pixel(0.0f, 0.0f, 0.0f);
            for (int32_t dy = -RADIUS; dy <= RADIUS; ++dy) {
                int32_t pos_y = std::max(0, std::min(width, y + dy));
                pixels[x][y] += pixels_copy[x][pos_y] * horizontal[dy + RADIUS];
            }
        }
    }

    for (int32_t x = 0; x <= height; ++x) {
        for (int32_t y = 0; y <= width; ++y) {
            pixels_copy[x][y] = BMPImage::Pixel(0.0f, 0.0f, 0.0f);
            for (int32_t dx = -RADIUS; dx <= RADIUS; ++dx) {
                int32_t pos_x = std::max(0, std::min(height, x + dx));
                pixels_copy[x][y] += pixels[pos_x][y] * horizontal[dx + RADIUS];
            }
        }
    }

    for (int32_t x = 0; x <= height; ++x) {
        for (int32_t y = 0; y <= width; ++y) {
            pixels_copy[x][y].Limit();
            pixels[x][y] = pixels_copy[x][y];
        }
    }
}