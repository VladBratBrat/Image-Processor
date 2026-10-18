#ifndef CPP_HSE_PARSER_H
#define CPP_HSE_PARSER_H

#include <string>
#include <vector>

#include "filter_desc.h"

class Parser {
public:
    enum class ParseResult { OK, InputFileNotFound, OutputFileNotFound, FilterIsMissing };

    Parser() = default;
    ~Parser() = default;

    ParseResult Parse(int argc, char** argv);

    const std::vector<FilterDesc>& GetFilterDesc() const {
        return filters_;
    }

    const std::string& GetInputFile() const {
        return input_file_;
    }

    const std::string& GetOutputFile() const {
        return output_file_;
    }

private:

    std::string input_file_;
    std::string output_file_;
    std::vector<FilterDesc> filters_;
};

#endif  // CPP_HSE_PARSER_H
