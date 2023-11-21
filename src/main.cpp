#include <iostream>
#include <fstream>
#include "graph.hpp"
#include "parsing.cpp"
#include <vector>

main(int argc, char **argv)
{
    // Program summary
    std::cout << "Authors: Jaedon & Yashaswi\nDate: 11/x/2023\nCourse: CS311 (Data Structures and Algorithms)\nDescription: Program to find the shortest route between cities\n";
    std::cout << "-----------------------------------------------------\n";

    // Load city data
    ifstream citiesFile("city.txt");
    ifstream routesFile("road.txt");
    if (!citiesFile || !routesFile)
    {
        return 1; // Files are required
    }

    // Add cities from city.txt
    CityGraph cities = CityGraph();
    std::vector<std::vector<std::string>> parsedCities = parse_cities_file(citiesFile);
    for (int i = 0; i < parsedCities.size(); i++)
    {
        std::string id = parsedCities[i][0];
        std::string code = parsedCities[i][1];
        std::string name = parsedCities[i][2];
        unsigned population = std::stoi(parsedCities[i][3]);
        int elevation = std::stoi(parsedCities[i][4]);

        cities.add_city(id, code, name, population, elevation);
    }

    // Add routes from road.txt
    std::vector<std::vector<std::string>> parsedRoutes = parse_routes_file(routesFile);
    for (int i = 0; i < parsedRoutes.size(); i++)
    {
        unsigned from_city = parsedRoutes[i][0];
        unsigned to_city = parsedRoutes[i][1];
        unsigned distance = parsedRoutes[i][2];

        cities.add_connection(from_city, to_city, distance);
    }

    // Process command line args
    std::string starting_city = argv[0];
    std::string target_city = argv[1];

    // Program termination
    citiesFile.close();
    routesFile.close();
    return 0;
}