#include <iostream>
#include <vector>
#include <functional>

/**
 * @brief Verify if the number of command line arguments matches the count
 *        If they don't match correctly, the program will terminate with exit status 1
 */
void verify_commandline_args(int argc, char **argv, int count)
{
    if (argc != count)
    {
        // Return and quite the program on incorrect arguments
        std::cout << "\x1b[31mIncorrect Command Line Arguments\x1b[0m" << std::endl;
        std::cout << "\x1b[33m[Error Details]: "
                  << "2 arguments are required"
                  << "\x1b[0m" << std::endl;
        exit(1);
    }
}

/**
 * @brief Verify if the files exist in the directory and is readable,
 *        If they are invalid, the program will terminate with exit status 1
 */
void verify_files(const std::vector<std::istream *> &files)
{
    for (auto file : files)
    {
        if (!file || !file->good())
        {
            std::cout << "File not found or not readable\n";
            exit(1); // Files are required
        }
    }
}

/**
 * @brief General function to validate if a ID exists, uses a function pointer and an array of IDs to check for validity
 *        If an ID doesn't exist, the program will terminate with exit status 1
 */
void verify_city_ids(const std::function<bool(const std::string &)> &searchFunction, const std::vector<std::string> &cityIDs)
{
    for (const auto &cityID : cityIDs)
    {
        if (!searchFunction(cityID))
        {
            std::cout << "Invalid city code: " << cityID << std::endl;
            exit(1);
        }
    }
}