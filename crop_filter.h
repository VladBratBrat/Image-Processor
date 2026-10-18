#ifndef CPP_HSE_CROP_FILTER_H
#define CPP_HSE_CROP_FILTER_H

#include "base_filter.h"

class CropFilter : public BaseFilter {
public:
    CropFilter() = default;
    ~CropFilter() override = default;

    void Apply(BMPImage& image) override;

    explicit CropFilter(int32_t width_cut, int32_t height_cut) : height_cut_(height_cut), width_cut_(width_cut) {};

    int32_t GetHeightCut() const {
        return height_cut_;
    }

    int32_t GetWidthCut() const {
        return width_cut_;
    }

    void SetHeightCut(const int32_t& height_cut) {
        height_cut_ = height_cut;
    }

    void SetWidthCut(const int32_t& width_cut) {
        width_cut_ = width_cut;
    }

private:
    int32_t height_cut_;
    int32_t width_cut_;
};

#endif  // CPP_HSE_CROP_FILTER_H