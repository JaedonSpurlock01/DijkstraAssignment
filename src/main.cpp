#include <iostream>
#include <fstream>
#include "graph.h"
#include "parsing.cpp"
#include "error.cpp"
#include <vector>

const std::string CITY_FILE_PATH = "../lib/cities.txt";
const std::string ROUTE_FILE_PATH = "../lib/routes.txt";
const unsigned COMMAND_LINE_ARGS_COUNT = 3;

void print_program_summary();

int main(int argc, char **argv)
{
    /*------------------------------------------------------------------*/
    // Verify and setup proper files
    /*------------------------------------------------------------------*/
    verify_commandline_args(argc, argv, COMMAND_LINE_ARGS_COUNT);

    std::ifstream citiesFile(CITY_FILE_PATH);
    std::ifstream routesFile(ROUTE_FILE_PATH);

    verify_files({&citiesFile, &routesFile});
    /*------------------------------------------------------------------*/

    print_program_summary();

    /*------------------------------------------------------------------*/
    // Initialize City Data
    /*------------------------------------------------------------------*/
    CityGraph cities = CityGraph();

    std::vector<std::vector<std::string>> parsedCities = parse_cities_file(citiesFile);
    cities.add_multiple_cities(parsedCities);

    std::vector<std::vector<unsigned>> parsedRoutes = parse_routes_file(routesFile);
    cities.add_multiple_connections(parsedRoutes);
    /*------------------------------------------------------------------*/

    /*------------------------------------------------------------------*/
    // Verify if ID's exist, then print shortest path between them
    /*------------------------------------------------------------------*/
    verify_city_ids([&cities](const std::string &cityID)
                    { return cities.search_by_city_id(cityID); },
                    {argv[1], argv[2]});

    cities.print_shortest_path_between(argv[1], argv[2]);
    /*------------------------------------------------------------------*/

    // Program termination
    citiesFile.close();
    routesFile.close();
    return 0;
}

void print_program_summary()
{
    std::cout << "Authors: Jaedon & Yashaswi\nDate: 11/x/2023\nCourse: CS311 (Data Structures and Algorithms)\nDescription: Program to find the shortest route between cities\n";
    std::cout << "-----------------------------------------------------\n";
}