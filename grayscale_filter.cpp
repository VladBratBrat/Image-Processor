#include "grayscale_filter.h"

void GrayScaleFilter::Apply(BMPImage& image) {
    AllPixels& pixels = image.GetPixels();

    for (std::vector<BMPImage::Pixel>& x : pixels) {
        for (BMPImage::Pixel& pixel : x) {
            pixel.blue_ = RED_MULT * pixel.red_ + GREEN_MULT * pixel.green_ + BLUE_MULT * pixel.blue_;
            pixel.red_ = pixel.blue_;
            pixel.green_ = pixel.blue_;
        }
    }
}