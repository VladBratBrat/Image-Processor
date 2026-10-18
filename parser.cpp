#include <regex>

#include "parser.h"

Parser::ParseResult Parser::Parse(int argc, char **argv) {
    std::regex path_to_file(R"(\.bmp$)");
    std::regex filter_regexp(R"(^-[\w]+$)");
    std::regex param_regexp(R"(^[0-9\.]+$)");
    std::smatch match;

    bool input_file_found = false;
    bool output_file_found = false;

    FilterDesc filter;

    for (size_t i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (i == 1) {
            input_file_found = std::regex_search(arg, match, path_to_file);
            input_file_ = (input_file_found ? arg : "");
            if (!input_file_found) {
                return ParseResult::InputFileNotFound;
            }
            continue;
        } else if (i == 2) {
            output_file_found = std::regex_search(arg, match, path_to_file);
            output_file_ = (output_file_found ? arg : "");
            if (!output_file_found) {
                return ParseResult::OutputFileNotFound;
            }
            continue;
        }

        if (filter.name != nullptr) {
            std::regex_match(arg, match, param_regexp);
            if (!match.empty()) {
                filter.params.push_back(argv[i]);
                continue;
            } else {
                filters_.push_back(filter);
                filter = FilterDesc();
            }
        }

        if (filter.name == nullptr) {
            std::regex_match(arg, match, filter_regexp);
            filter.name = (match.empty() ? nullptr : argv[i] + 1);
            if (match.empty()) {
                return ParseResult::FilterIsMissing;
            }
        }
    }

    if (filter.name != nullptr) {
        filters_.push_back(filter);
        filter.name = nullptr;
    }

    return ParseResult::OK;
}
