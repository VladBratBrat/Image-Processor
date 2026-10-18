#include <cctype>
#include <climits>
#include <math.h>

#include "crop_filter.h"
#include "crystalize_filter.h"
#include "edge_filter.h"
#include "filter_errors.h"
#include "gauss_blur_filter.h"
#include "grayscale_filter.h"
#include "negative_filter.h"
#include "pipeline.h"
#include "sharp_filter.h"
#include "filter_creator.h"

static const int32_t BASE = 10;

bool create_filter::ConvertToIntNumber(const char* filter_name, int32_t& value_return) {
    char* end = nullptr;
    int32_t value = static_cast<int32_t>(std::strtol(filter_name, &end, BASE));
    if (end != filter_name && *end == '\0' && value > 0 && value != INT_MAX) {
        value_return = value;
        return true;
        return true;
    }
    return false;
}

bool create_filter::ConvertToFloatNumber(const char* filter_name, float& value_return) {
    char* end = nullptr;
    float value = std::strtof(filter_name, &end);
    if (end != filter_name && *end == '\0' && value != HUGE_VALF && value != -HUGE_VALF && !std::isnan(value)) {
        value_return = value;
        return true;
    }
    return false;
}

std::pair<BaseFilter*, FilterError> create_filter::MakeCropFilter(const FilterDesc& desc) {
    int32_t width_cut = 0;
    int32_t height_cut = 0;
    bool not_all_ints = false;
    not_all_ints |= !ConvertToIntNumber(desc.params[0], width_cut);
    not_all_ints |= !ConvertToIntNumber(desc.params[1], height_cut);

    FilterError error;
    BaseFilter* base_filter = nullptr;

    if (not_all_ints) {
        return {base_filter, FilterError(std::string(desc.name), FilterError::FilterListError::PositiveIntegers)};
    }

    base_filter = new CropFilter(width_cut, height_cut);

    return std::make_pair(base_filter, FilterError(FilterError::FilterListError::OK));
}

std::pair<BaseFilter*, FilterError> create_filter::MakeGsFilter(const FilterDesc& desc) {
    BaseFilter* base_filter = new GrayScaleFilter();
    FilterError error;

    return {base_filter, FilterError(FilterError::FilterListError::OK)};
}

std::pair<BaseFilter*, FilterError> create_filter::MakeNegFilter(const FilterDesc& desc) {
    BaseFilter* base_filter = new NegativeFilter();
    FilterError error;

    return {base_filter, FilterError(FilterError::FilterListError::OK)};
}

std::pair<BaseFilter*, FilterError> create_filter::MakeSharpFilter(const FilterDesc& desc) {
    BaseFilter* base_filter = new SharpFilter();
    FilterError error;

    return {base_filter, FilterError(FilterError::FilterListError::OK)};
}

std::pair<BaseFilter*, FilterError> create_filter::MakeEdgeFilter(const FilterDesc& desc) {
    float threshold = 0.0f;
    bool not_float = true;
    not_float |= ConvertToFloatNumber(desc.params[0], threshold);

    FilterError error;
    BaseFilter* base_filter = nullptr;

    if (!not_float) {
        return {base_filter, FilterError(std::string(desc.name), FilterError::FilterListError::FloatNumbers)};
    }

    base_filter = new EdgeFilter(threshold);

    return {base_filter, FilterError(FilterError::FilterListError::OK)};
}

std::pair<BaseFilter*, FilterError> create_filter::MakeGaussBlurFilter(const FilterDesc& desc) {
    float sigma = 0.0f;
    bool not_float = true;
    not_float |= ConvertToFloatNumber(desc.params[0], sigma);

    FilterError error;
    BaseFilter* base_filter = nullptr;

    if (!not_float) {
        return {base_filter, FilterError(std::string(desc.name), FilterError::FilterListError::FloatNumbers)};
    }
    if (sigma == 0.0f) {
        return {base_filter, FilterError(std::string(desc.name), FilterError::FilterListError::NotZeroFloatNumber)};
    }

    base_filter = new GaussBlurFilter(sigma);
    return {base_filter, FilterError(FilterError::FilterListError::OK)};
}

std::pair<BaseFilter*, FilterError> create_filter::MakeCrystalizeFilter(const FilterDesc& desc) {
    float radius = 0.0f;

    FilterError error;
    BaseFilter* base_filter = nullptr;

    if (!ConvertToFloatNumber(desc.params[0], radius)) {
        return {base_filter, FilterError(std::string(desc.name), FilterError::FilterListError::FloatNumbers)};
    }

    base_filter = new CrystalizeFilter(radius);
    return {base_filter, FilterError(FilterError::FilterListError::OK)};
}
