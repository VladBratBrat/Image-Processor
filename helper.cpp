#include <iostream>

#include "helper.h"

void helper::HelpTextOutput() {
    std::cerr << "\nThe argument line should be following:\n{name of program} {path to input file} {path to output "
                 "file} [-{name of filter 1} [parameter of filter 1] [parameter of filter 2] ...] [-{name of filter 2} "
                 "[parameter of filter 1] [parameter of filter 2] ...] ... \n\nExample: ./image_processor input.bmp "
                 "/tmp/output.bmp -crop 800 600 -gs -blur 0.5\n\nList of filters and their arguments:\n-crop width "
                 "height : Cuts the image to a specified width and height, parameters - two non-negative integers. If "
                 "the requested width or height is larger than the original image, the available portion of the image "
                 "will be displayed. Use the upper left part of the image\n-gs : "
                 "convert image to grayscale\n-neg : convert image to negative\n-sharp : sharpening\n-edge threshold : "
                 "edge detection, parameter threshold - float\n-blur sigma : gaussian blur, parameter - float "
                 "sigma\n-crystalize radius "
                 ": crystalize an image with the following radius, parameter radius - float";
}