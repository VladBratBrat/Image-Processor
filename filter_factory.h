#ifndef CPP_HSE_FILTER_FACTORY_H
#define CPP_HSE_FILTER_FACTORY_H

#include <vector>

#include "base_filter.h"
#include "filter_desc.h"
#include "pipeline.h"
#include "filter_errors.h"

class FilterFactory {
public:
    FilterError MakePipeline(const std::vector<FilterDesc>& f_descriptions, Pipeline& pipeline);
    std::pair<BaseFilter*, FilterError> ProcessFilter(FilterDesc f_desc, Pipeline& pipeline);
};

#endif  // CPP_HSE_FILTER_FACTORY_H