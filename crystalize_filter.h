#ifndef CPP_HSE_CRYSTALIZE_H
#define CPP_HSE_CRYSTALIZE_H

#include "base_filter.h"

class CrystalizeFilter : public BaseFilter {
public:
    CrystalizeFilter() = default;
    ~CrystalizeFilter() override = default;

    void Apply(BMPImage& image) override;

    explicit CrystalizeFilter(float radius) : radius_(radius){};

    float GetRadius() const {
        return radius_;
    }

private:
    float radius_;
};

#endif  // CPP_HSE_CRYSTALIZE_H
