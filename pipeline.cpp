#include "pipeline.h"
#include "filter_creator.h"

Pipeline::~Pipeline() {
    for (BaseFilter* filter : filters_) {
        if (filter != nullptr) {
            delete filter;
        }
    }
    filters_.clear();
}

void Pipeline::Apply(BMPImage& image) {
    for (BaseFilter* f : filters_) {
        f->Apply(image);
    }
}

void Pipeline::AddFilter(BaseFilter* filter) {
    filters_.push_back(filter);
}

void Pipeline::Initialize() {
    get_filter_["crop"] = {create_filter::MakeCropFilter, 2};
    get_filter_["gs"] = {create_filter::MakeGsFilter, 0};
    get_filter_["neg"] = {create_filter::MakeNegFilter, 0};
    get_filter_["sharp"] = {create_filter::MakeSharpFilter, 0};
    get_filter_["edge"] = {create_filter::MakeEdgeFilter, 1};
    get_filter_["blur"] = {create_filter::MakeGaussBlurFilter, 1};
    get_filter_["crystalize"] = {create_filter::MakeCrystalizeFilter, 1};
}
