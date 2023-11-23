#include <iostream>
#include <fstream>
#include "graph.cpp"
#include "parsing.cpp"
#include "error.cpp"
#include <vector>

const std::string CITY_FILE = "../lib/cities.txt";
const std::string ROUTE_FILE = "../lib/routes.txt";

int main(int argc, char **argv)
{
    // Verify correct number of command line arguments, terminate program if not 2
    verify_commandline_args(argc, argv, 3);

    // Load city data
    ifstream citiesFile(CITY_FILE);
    ifstream routesFile(ROUTE_FILE);

    // Check if files are correct, if not terminate program
    verify_files({&citiesFile, &routesFile});

    // Program summary
    std::cout << "Authors: Jaedon & Yashaswi\nDate: 11/x/2023\nCourse: CS311 (Data Structures and Algorithms)\nDescription: Program to find the shortest route between cities\n";
    std::cout << "-----------------------------------------------------\n";

    // Create and setup city data in the form of a graph
    CityGraph cities = CityGraph();
    std::vector<std::vector<std::string>> parsedCities = parse_cities_file(citiesFile);
    cities.add_multiple_cities(parsedCities);
    std::vector<std::vector<unsigned>> parsedRoutes = parse_routes_file(routesFile);
    cities.add_multiple_connections(parsedRoutes);

    // Checking if the arguments exist or not in list of cities
    verify_city_ids([&cities](const std::string &cityID)
                    { return cities.search_by_city_id(cityID); },
                    {argv[1], argv[2]});

    cities.print_shortest_path_between(argv[1], argv[2]);

    // Program termination
    citiesFile.close();
    routesFile.close();
    return 0;
}