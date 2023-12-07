#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

/*! Gets the calibration value from an improved calibration document line.
 *
 * \param line amended line containing the calibration value.
 *
 * \return The calibration value.
 *
 * \exception std::invalid_argument \p line does not contain any digits.
 */
int GetCalibrationValue(const std::string &line);

/*! Converts spelled-out digits in an improved calibration document line.
 *
 * This function converts the first and last digits that are spelled out---one
 * to nine---to arabic numerals---1 to 9.
 *
 * \param line amended line containing the calibration value.
 *
 * \return The amended line with spelled-out digits converted to arabic
 * numerals.
 */
std::string ConvertSpelledOutDigits(const std::string &line);

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
    std::ifstream input(input_name);
    std::cout << "I'll get " << input_name << " decoded for you in a hot sec..." << std::endl
              << std::endl;

    // Parse input line by line
    std::string line;
    auto sum_calibration_values = 0;
    while (std::getline(input, line))
    {
        // Get calibration value
        auto calibration_value = GetCalibrationValue(line);
        std::cout << calibration_value << " from " << line << std::endl;

        // Add it to the sum
        sum_calibration_values += calibration_value;
    }
    std::cout << std::endl;

    // Drumroll, please
    std::cout << "Sum of all of the calibration values: " << sum_calibration_values << std::endl
              << "Now go get 'em, tiger!" << std::endl;
}

// Get the calibration value from an improved calibration document line
int GetCalibrationValue(const std::string &line)
{
    auto converted_line = ConvertSpelledOutDigits(line);
    // std::cout << ConvertSpelledOutDigits(line) << std::endl;

    // Get the first digit
    auto first_digit = -1;
    for (auto it = converted_line.begin(); it != converted_line.end(); it++)
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
    for (auto rit = converted_line.rbegin(); rit != converted_line.rend(); rit++)
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

// Convert spelled-out digits to arabic numerals
std::string ConvertSpelledOutDigits(const std::string &line)
{
    // Possible spelled-out digits
    const std::vector<std::string> digits = {
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine"};

    // First index is position of the match. Second index is the index of the
    // digit that matched
    std::vector<int> first_digit = {(int)line.size(), -1};
    std::vector<int> last_digit = {-1, -1};

    // Look for each index
    for (auto i = 0; i < digits.size(); i++)
    {
        // Start from the left
        auto pos = (int)line.find(digits[i]);
        if (pos == std::string::npos)
        {
            continue;
        }
        if (pos < first_digit[0])
        {
            first_digit = {(int)pos, i};
        }

        // Then from the right
        pos = (int)line.rfind(digits[i]);
        if (pos > last_digit[0])
        {
            last_digit = {(int)pos, i};
        }
    }

    // Negative index means no matches were found
    if (first_digit[1] < 0 || last_digit[1] < 0)
    {
        return line;
    }

    // Make the substitutions
    std::string r_str = line;
    r_str[first_digit[0]] = first_digit[1] + '1';
    r_str[last_digit[0]] = last_digit[1] + '1';
    return r_str;
}
