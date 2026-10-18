#ifndef CPP_HSE_NEGATIVE_FILTER_H
#define CPP_HSE_NEGATIVE_FILTER_H

#include "bmp_worker.h"
#include "matrix_filter.h"

class NegativeFilter : public MatrixFilter {
public:
    void Apply(BMPImage& image) override;
};

#endif  // CPP_HSE_NEGATIVE_FILTER_H