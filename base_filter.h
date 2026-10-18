#ifndef CPP_HSE_BASE_FILTER_H
#define CPP_HSE_BASE_FILTER_H

#include "bmp_worker.h"
#include "filter_desc.h"

using AllPixels = std::vector<std::vector<BMPImage::Pixel>>;

class BaseFilter {
public:
    BaseFilter() = default;
    virtual ~BaseFilter() = default;

    virtual void Apply(BMPImage& image) = 0;

    explicit BaseFilter(const FilterDesc& filter) : filter_(filter){};

    const FilterDesc& GetFilter() const {
        return filter_;
    }

private:
    FilterDesc filter_;
};

#endif  // CPP_HSE_BASE_FILTER_H