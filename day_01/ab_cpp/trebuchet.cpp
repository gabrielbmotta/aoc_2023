#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

/*! Gets the calibration value from an improved calibration document line.
 *
 * \param line amended line containing the calibration value.
 *
 * \return The calibration value.
 *
 * \exception std::invalid_argument \p line does not contain any digits.
 */
int GetCalibrationValue(std::string &line);

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

    // Just echo calibration values for now for now
    std::string line;
    while (std::getline(input, line))
    {
        std::cout << GetCalibrationValue(line) << std::endl;
    }
}

// Get the calibration value from an improved calibration document line
int GetCalibrationValue(std::string &line)
{
    // Get the first digit
    auto first_digit = -1;
    for (auto it = line.begin(); it != line.end(); it++)
    {
        if (isdigit(*it))
        {
            first_digit = *it - '0';
            break;
        }
    }

    // We know for certain that the first (and last) digit is positive since
    // negative values can't be expressed in less than two characters (ie. 1 vs.
    // -1)
    if (first_digit < 0)
    {
        throw std::invalid_argument("line must contain at least one digit");
    }

    // Get the second digit
    for (auto rit = line.rbegin(); rit != line.rend(); rit++)
    {
        if (isdigit(*rit))
        {
            auto second_digit = *rit - '0';
            return first_digit * 10 + second_digit;
        }
    }

    // Shouldn't be possible to reach here, but for completeness
    throw std::runtime_error("reached impossible end");
}
