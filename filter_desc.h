#ifndef CPP_HSE_FILTER_DESC_H
#define CPP_HSE_FILTER_DESC_H

#include <vector>

struct FilterDesc {
    FilterDesc() : name{nullptr} {};
    const char* name; // TODO const char
    std::vector<const char*> params;
};

#endif  // CPP_HSE_FILTER_DESC_H