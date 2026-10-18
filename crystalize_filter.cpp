#include <chrono>
#include <random>
#include <unordered_map>
#include <vector>

#include "crystalize_filter.h"

static const float MULT = 1.5f;

using VectorPixelsCords = std::vector<std::vector<std::vector<std::pair<int32_t, int32_t>>>>;
using MapSquares = std::unordered_map<int32_t, std::vector<std::pair<int32_t, int32_t>>>;

int32_t GetSquareDistance(int32_t x, int32_t y, int32_t pos_x, int32_t pos_y) {
    return (x - pos_x) * (x - pos_x) + (y - pos_y) * (y - pos_y);
}

void CrystalizeFilter::Apply(BMPImage& image) {
    AllPixels& pixels = image.GetPixels();

    int32_t height = image.GetHeight();
    int32_t width = image.GetWidth();

    float radius = GetRadius();

    int32_t square_len = static_cast<int32_t>(ceil(radius * MULT));
    int32_t height_rand = static_cast<int32_t>(ceil(height / square_len) + 1);
    int32_t width_rand = static_cast<int32_t>(ceil(width / square_len) + 1);

    VectorPixelsCords random_pixels;
    random_pixels.resize(height_rand);

    for (int32_t x = 0; x < height_rand; ++x) {
        random_pixels[x].resize(width_rand);
    }

    std::mt19937 gen(1);
    int32_t num_rand_pixels =
        2 * static_cast<int32_t>(static_cast<float>(height * width) / ((2 * radius) * (2 * radius)));

    for (int32_t x = 0; x < num_rand_pixels; ++x) {
        int32_t pos_x = (std::abs(static_cast<int32_t>(gen())) % height);
        int32_t pos_y = (std::abs(static_cast<int32_t>(gen())) % width);

        random_pixels[pos_x / square_len][pos_y / square_len].push_back({pos_x, pos_y});
    }

    MapSquares squares;

    int32_t min_dist = INT32_MAX;
    int32_t rand_square_x = 0;
    int32_t rand_square_y = 0;

    int32_t poss_square_x = 0;
    int32_t poss_square_y = 0;

    for (int32_t x = 0; x < height; ++x) {
        for (int32_t y = 0; y < width; ++y) {
            min_dist = INT32_MAX;
            rand_square_x = 0;
            rand_square_y = 0;

            for (int32_t pos_x = -1; pos_x <= 1; ++pos_x) {
                for (int32_t pos_y = -1; pos_y <= 1; ++pos_y) {
                    poss_square_x = std::max(0, std::min(height_rand - 1, (x / square_len) + pos_x));
                    poss_square_y = std::max(0, std::min(width_rand - 1, (y / square_len) + pos_y));

                    for (std::pair<int32_t, int32_t> z : random_pixels[poss_square_x][poss_square_y]) {
                        if (GetSquareDistance(x, y, z.first, z.second) < min_dist) {
                            min_dist = GetSquareDistance(x, y, z.first, z.second);
                            rand_square_x = poss_square_x;
                            rand_square_y = poss_square_y;
                        }
                    }
                }
            }

            squares[rand_square_x * width_rand + rand_square_y].push_back({x, y});
        }
    }

    for (int32_t x = 0; x < height_rand; ++x) {
        for (int32_t y = 0; y < width_rand; ++y) {
            if (squares[x * width_rand + y].empty()) {
                continue;
            }
            size_t len = squares[x * width_rand + y].size();
            BMPImage::Pixel average_pixel = BMPImage::Pixel(0.0f, 0.0f, 0.0f);
            for (std::pair<int32_t, int32_t> z : squares[x * width_rand + y]) {
                average_pixel = average_pixel + pixels[z.first][z.second];
            }

            average_pixel.blue_ /= static_cast<float>(len);
            average_pixel.green_ /= static_cast<float>(len);
            average_pixel.red_ /= static_cast<float>(len);

            for (std::pair<int32_t, int32_t> z : squares[x * width_rand + y]) {
                pixels[z.first][z.second] = average_pixel;
            }
        }
    }
}
