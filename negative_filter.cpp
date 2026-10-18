#include "negative_filter.h"

void NegativeFilter::Apply(BMPImage& image) {
    AllPixels& pixels = image.GetPixels();

    for (std::vector<BMPImage::Pixel>& x : pixels) {
        for (BMPImage::Pixel& pixel : x) {
            pixel = (BMPImage::Pixel(1.0f, 1.0f, 1.0f) - pixel);
        }
    }
}