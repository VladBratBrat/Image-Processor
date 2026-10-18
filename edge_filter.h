#ifndef CPP_HSE_EDGE_FILTER_H
#define CPP_HSE_EDGE_FILTER_H

#include "matrix_filter.h"
#include "bmp_worker.h"

class EdgeFilter : public MatrixFilter {
public:
    EdgeFilter() = default;
    ~EdgeFilter() override = default;

    void Apply(BMPImage& image) override;

    explicit EdgeFilter(const float& threshold) : threshold_(threshold){};

    void SetThreshold(const float& threshold) {
        threshold_ = threshold;
    }

    float GetThreshold() const {
        return threshold_;
    }

private:
    float threshold_;
};

#endif  // CPP_HSE_EDGE_FILTER_H
