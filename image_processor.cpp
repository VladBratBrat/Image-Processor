#include <iostream>
#include <exception>

#include "application.h"
#include "helper.h"

using namespace application;
using namespace helper;

int main(int argc, char** argv) {
    try {
        if (argc == 1) {
            HelpTextOutput();
            return 0;
        }
        Application app;
        return app.Run(argc, argv);
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error!" << std::endl;
    }
}