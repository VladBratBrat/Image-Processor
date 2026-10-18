#ifndef CPP_HSE_MATRIX_FILTER_H
#define CPP_HSE_MATRIX_FILTER_H

#include "base_filter.h"

class MatrixFilter : public BaseFilter {
public:
    MatrixFilter() = default;
    ~MatrixFilter() override = default;

    void Apply(BMPImage& image) override = 0;
};

#endif  // CPP_HSE_MATRIX_FILTER_H