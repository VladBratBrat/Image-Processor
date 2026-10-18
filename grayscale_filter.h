#ifndef CPP_HSE_GRAY_SCALE_H
#define CPP_HSE_GRAY_SCALE_H

#include "bmp_worker.h"
#include "matrix_filter.h"

static const float RED_MULT = 0.299f;
static const float GREEN_MULT = 0.587f;
static const float BLUE_MULT = 0.114f;

class GrayScaleFilter : public MatrixFilter {
public:
    void Apply(BMPImage& image) override;
};

#endif  // CPP_HSE_GRAY_SCALE_H