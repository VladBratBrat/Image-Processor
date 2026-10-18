#include <vector>
#include <unordered_map>

#include "filter_desc.h"
#include "filter_factory.h"
#include "pipeline.h"

std::pair<BaseFilter*, FilterError> FilterFactory::ProcessFilter(FilterDesc f_desc, Pipeline& pipeline) {
    std::string filter_name = f_desc.name;
    BaseFilter* filter = nullptr;
    FilterError error;

    std::pair<std::pair<MakeFilter, int32_t>, bool> get_filter = pipeline.GetInfoFilter(filter_name);

    if (!get_filter.second) {
        return {filter, FilterError(filter_name, FilterError::FilterListError::NotFilter)};
    }

    if (f_desc.params.size() != get_filter.first.second) {  // TODO - один раз
        return {filter, FilterError(filter_name, FilterError::FilterListError::NumParametersDiff)};
    }

    return get_filter.first.first(f_desc);
}

FilterError FilterFactory::MakePipeline(const std::vector<FilterDesc>& f_descriptions, Pipeline& pipeline) {
    // TODO - вынести image, не записывать
    pipeline.Initialize();
    for (const FilterDesc& f_desc : f_descriptions) {
        std::pair<BaseFilter*, FilterError> filter = ProcessFilter(f_desc, pipeline);
        if (filter.second.GetErrorName() != FilterError::FilterListError::OK) {

            return filter.second;
        }
        pipeline.AddFilter(filter.first);
    }
    return FilterError(FilterError::FilterListError::OK);
}