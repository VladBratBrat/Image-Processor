#ifndef CPP_HSE_FILTER_ERRORS_H
#define CPP_HSE_FILTER_ERRORS_H

#include <string>

class FilterError {
public:
    enum class FilterListError { OK, PositiveIntegers, FloatNumbers, NotZeroFloatNumber, NotFilter, NumParametersDiff };

    FilterError() = default; // TODO - по-другому
    explicit FilterError(FilterListError error_name)
        : error_name_(error_name){};
    explicit FilterError(const std::string& error_info, FilterListError error_name)
        : error_info_(error_info), error_name_(error_name){};

    std::string GetErrorInfo() const {
        return error_info_;
    }

    FilterListError GetErrorName() const {
        return error_name_;
    }

private:
    std::string error_info_;
    FilterListError error_name_;
};

#endif  // CPP_HSE_FILTER_ERRORS_H
