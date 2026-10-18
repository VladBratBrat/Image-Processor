#ifndef CPP_HSE_PIPELINE_H
#define CPP_HSE_PIPELINE_H

#include <map>
#include <vector>

#include "filter_errors.h"
#include "base_filter.h"
#include "bmp_worker.h"

using MakeFilter = std::pair<BaseFilter*, FilterError> (*)(const FilterDesc&);
using GetFilter = std::map<std::string, std::pair<MakeFilter, int32_t>>;

class Pipeline {
public:
    Pipeline() = default;
    ~Pipeline();
    Pipeline(const Pipeline&) = delete;
    Pipeline& operator=(const Pipeline&) = delete;

    void AddFilter(BaseFilter* filter);

    void Apply(BMPImage& image);

    void Initialize();

    std::pair<std::pair<MakeFilter, int32_t>, bool> GetInfoFilter(const std::string& filter) {
        GetFilter::iterator iter = get_filter_.find(filter);
        if (iter == get_filter_.end()) {
            return std::make_pair(std::make_pair(nullptr, -1), false);
        }
        return std::make_pair(iter->second, true); // TODO обработать нули
    }

    // TODO в отдельный модуль

private:
    std::vector<BaseFilter*> filters_;
    GetFilter get_filter_;
};

#endif  // CPP_HSE_PIPELINE_H