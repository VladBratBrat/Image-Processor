#include <iostream>

#include "application.h"
#include "bmp_worker.h"
#include "filter_factory.h"
#include "filter_errors.h"
#include "parser.h"

using namespace application;

int Application::Run(int argc, char** argv) {
    if (argc == 1) {
        return 1;
    }

    Parser parser;
    Parser::ParseResult parser_result = parser.Parse(argc, argv);

    switch (parser_result) {
        case Parser::ParseResult::InputFileNotFound:
            std::cerr << "Input file is not in arguments or has errors in path";
            return 1;
        case Parser::ParseResult::OutputFileNotFound:
            std::cerr << "Output file is not in args or has errors in path";
            return 1;
        case Parser::ParseResult::FilterIsMissing:
            std::cerr << "New filter is missing";
            return 1;
        default:
            break;
    }

    BMPImage image;
    BMPImage::BMPResult image_result = image.ReadFromFile(parser.GetInputFile());

    switch (image_result) {
        case BMPImage::BMPResult::ImageBMPIsNot24Bits:
            std::cerr << "Image file from input is not 24bits";
            return 1;
        case BMPImage::BMPResult::ImageIsNotBMP:
            std::cerr << "Image file is not bmp";
            return 1;
        case BMPImage::BMPResult::InputFileNotOpened:
            std::cerr << "Could not open an input file";
            return 1;
        default:
            break;
    }

    Pipeline pipeline;
    FilterFactory factory;

    FilterError error = factory.MakePipeline(parser.GetFilterDesc(), pipeline);

    switch (error.GetErrorName()) {
        case FilterError::FilterListError::PositiveIntegers:
            std::cerr << error.GetErrorInfo() << " parameters should be positive integers";
            return 1;
        case FilterError::FilterListError::FloatNumbers:
            std::cerr << error.GetErrorInfo() << " parameters should be float";
            return 1;
        case FilterError::FilterListError::NotZeroFloatNumber:
            std::cerr << error.GetErrorInfo() << " parameters should be not-zero float";
            return 1;
        case FilterError::FilterListError::NotFilter:
            std::cerr << error.GetErrorInfo() << " is not a filter";
            return 1;
        case FilterError::FilterListError::NumParametersDiff:
            std::cerr << error.GetErrorInfo() << " filter has wrong number of arguments";
            return 1;
        default:
            break;
    }

    pipeline.Apply(image);

    image_result = image.WriteToFile(parser.GetOutputFile());

    switch (image_result) {
        case BMPImage::BMPResult::OutputFileNotOpened:
            std::cerr << "Could not open an output file";
            return 1;
        default:
            break;
    }

    return 0;
}
