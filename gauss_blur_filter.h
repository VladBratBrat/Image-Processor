#ifndef CPP_HSE_GAUSS_BLUR_H
#define CPP_HSE_GAUSS_BLUR_H

#include "matrix_filter.h"
#include "bmp_worker.h"

class GaussBlurFilter : public MatrixFilter {
public:
    GaussBlurFilter() = default;
    ~GaussBlurFilter() override = default;

    void Apply(BMPImage& image) override;

    explicit GaussBlurFilter(const float& sigma) : sigma_(sigma){};

    void SetSigma(const float& sigma) {
        sigma_ = sigma;
    }

    float GetSigma() const {
        return sigma_;
    }

private:
    float sigma_;
};

#endif  // CPP_HSE_GAUSS_BLUR_H
