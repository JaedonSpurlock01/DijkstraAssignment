#include <iostream>
#include <fstream>
#include "graph.cpp"
#include "parsing.cpp"
#include <vector>

string verify_commandline_args(int argc, char **argv)
{
    // Purpose: Use these two args and check if their valid
    // Validity criterion:
    string Verified = "true";

    if (argc > 3)
    {
        Verified = "cmd args exceed limit of 3";
    }

    else if (argc < 3)
    {
        Verified = "cmd args are less than 3";
    }

    return Verified;
}

int main(int argc, char **argv)
{ // Check and verify args validity

    string verified = verify_commandline_args(argc, argv);

    if (verified != "true")
    {
        // Return and quite the program on incorrect arguments
        cout << "\x1b[31mIncorrect Command Line Arguments\x1b[0m" << endl;
        cout << "\x1b[33m[Error Details]: " << verified << "\x1b[0m" << endl;
        return 1;
    }

    // Program summary
    std::cout << "Authors: Jaedon & Yashaswi\nDate: 11/x/2023\nCourse: CS311 (Data Structures and Algorithms)\nDescription: Program to find the shortest route between cities\n";
    std::cout << "-----------------------------------------------------\n";

    // Load city data
    ifstream citiesFile("../lib/cities.txt");
    ifstream routesFile("../lib/routes.txt");

    if (!citiesFile || !routesFile)
    {
        std::cout << "File not found\n";
        return 1; // Files are required
    }

    // Add cities from city.txt
    CityGraph cities = CityGraph();
    std::vector<std::vector<std::string>> parsedCities = parse_cities_file(citiesFile);
    cities.add_multiple_cities(parsedCities);

    // Add routes from road.txt
    std::vector<std::vector<unsigned>> parsedRoutes = parse_routes_file(routesFile);
    cities.add_multiple_connections(parsedRoutes);

    // Checking if the arguments exist or not in the hashmap
    bool verify = true;
    if (cities.search_by_city_id(argv[1]) == false)
    {
        cout << "Invalid city code: " << argv[1] << endl;
        verify = false;
    }

    if (cities.search_by_city_id(argv[2]) == false)
    {
        cout << "Invalid city code: " << argv[2] << endl;
        verify = false;
    }

    if (verify == false)
        return 0;

    cities.print_shortest_path_between(argv[1], argv[2]);

    // Program termination
    citiesFile.close();
    routesFile.close();
    return 0;
}