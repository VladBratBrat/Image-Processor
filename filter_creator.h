#ifndef CPP_HSE_FILTER_CREATOR_H
#define CPP_HSE_FILTER_CREATOR_H

#include "base_filter.h"
#include "filter_errors.h"

namespace create_filter {

bool ConvertToIntNumber(const char* filter_name, int32_t& value_return);
bool ConvertToFloatNumber(const char* filter_name, float& value_return);

std::pair<BaseFilter*, FilterError> MakeCropFilter(const FilterDesc& desc);
std::pair<BaseFilter*, FilterError> MakeGsFilter(const FilterDesc& desc);
std::pair<BaseFilter*, FilterError> MakeNegFilter(const FilterDesc& desc);
std::pair<BaseFilter*, FilterError> MakeSharpFilter(const FilterDesc& desc);
std::pair<BaseFilter*, FilterError> MakeEdgeFilter(const FilterDesc& desc);
std::pair<BaseFilter*, FilterError> MakeGaussBlurFilter(const FilterDesc& desc);
std::pair<BaseFilter*, FilterError> MakeCrystalizeFilter(const FilterDesc& desc);

}

#endif  // CPP_HSE_FILTER_CREATOR_H
