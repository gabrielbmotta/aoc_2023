#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    std::cout << "Calibration Document Decoder and Summation Analysis Tool" << std::endl
              << "(optimized for trebuchets)" << std::endl
              << std::endl;

    // Check for valid input
    if (argc == 1)
    {
        std::cout << "No document to decode...why am I here?" << std::endl;
        return EXIT_FAILURE;
    }
    else if (argc != 2)
    {
        std::cout << "Patience! One calibration document at a time, please." << std::endl;
        return EXIT_FAILURE;
    }

    // Open input file
    char *input_name = argv[1];
    std::cout << "I'll get " << input_name << " decoded for you in a hot sec..." << std::endl;
    std::ifstream input(input_name);

    // Just echo it for now
    std::string line;
    while (std::getline(input, line))
    {
        std::cout << line << std::endl;
    }
}
