#include <map>
#include <vector>

#include "sharp_filter.h"

static const float CENTER_MULT = 5.0f;

void SharpFilter::Apply(BMPImage& image) {
    std::map<std::pair<int32_t, int32_t>, float> value;

    value[{0, 0}] = CENTER_MULT;
    value[{-1, 0}] = -1.0f;
    value[{1, 0}] = -1.0f;
    value[{0, 1}] = -1.0f;
    value[{0, -1}] = -1.0f;

    std::vector<std::pair<int32_t, int32_t>> moves = {{0, 0}, {-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    AllPixels& pixels = image.GetPixels();

    BMPImage image_copy = image;
    AllPixels& pixels_copy = image_copy.GetPixels();

    int32_t height = image.GetHeight() - 1;
    int32_t width = image.GetWidth() - 1;

    int32_t pos_from_x = 0;
    int32_t pos_from_y = 0;

    for (int32_t x = 0; x <= height; ++x) {
        for (int32_t y = 0; y <= width; ++y) {
            pixels[x][y] = BMPImage::Pixel(0.0f, 0.0f, 0.0f);

            for (std::pair<int32_t, int32_t>& to_move : moves) {
                pos_from_x = std::max(0, std::min(x + to_move.first, height));
                pos_from_y = std::max(0, std::min(y + to_move.second, width));

                pixels[x][y] += pixels_copy[pos_from_x][pos_from_y] * value[{to_move.first, to_move.second}];
            }

            pixels[x][y].Limit();
        }
    }
}