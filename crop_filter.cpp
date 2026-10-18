#include "crop_filter.h"

void CropFilter::Apply(BMPImage& image) {
    AllPixels& pixels = image.GetPixels();

    int32_t height_cut = GetHeightCut();
    int32_t width_cut = GetWidthCut();

    if (height_cut < image.GetHeight()) {
        int32_t height = image.GetHeight();

        for (int32_t x = height - 1; x >= height_cut; --x) {
            pixels.pop_back();
        }

        image.SetHeight(height_cut);
    }

    if (width_cut < image.GetWidth()) {
        int32_t height = image.GetHeight();
        int32_t width = image.GetWidth();

        for (int32_t x = 0; x < height; ++x) {
            for (int32_t y = width - 1; y >= width_cut; --y) {
                pixels[x].pop_back();
            }
        }

        image.SetWidth(width_cut);
    }
}
