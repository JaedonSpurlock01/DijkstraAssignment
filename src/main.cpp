#include <iostream>
#include <fstream>
#include "graph.cpp"
#include <vector>

// Implement later, should return an array of arrays where each array has the corresponding city data
vector<vector<std::string>> parse_cities_file(istream &file);

// Implement later, should return an array of arrays where each array has the corresponding route data
vector<vector<unsigned>> parse_routes_file(istream &file);

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

    // Add cities
    CityGraph cities = CityGraph();
    vector<vector<std::string>> parsedCities = parse_cities_file(citiesFile);
    for (int i = 0; i < parsedCities.size(); i++)
    {
        std::string id = parsedCities[i][0];
        std::string code = parsedCities[i][1];
        std::string name = parsedCities[i][2];
        unsigned population = std::stoi(parsedCities[i][3]);
        int elevation = std::stoi(parsedCities[i][4]);

        cities.add_city(id, code, name, population, elevation);
    }

    // Add routes

    // Process command line args
    std::string starting_city = argv[0];
    std::string target_city = argv[1];

    // Program termination
    citiesFile.close();
    routesFile.close();
    return 0;
}