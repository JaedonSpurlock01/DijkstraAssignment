#include <iostream>
#include <vector>
#include <functional>

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