#ifndef CPP_HSE_SHARP_FILTER_H
#define CPP_HSE_SHARP_FILTER_H

#include "matrix_filter.h"
#include "bmp_worker.h"

class SharpFilter : public MatrixFilter {
public:
    void Apply(BMPImage& image) override;
};

#endif  // CPP_HSE_SHARP_FILTER_H
