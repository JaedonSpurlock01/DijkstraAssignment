#include <iostream>
#include <vector>
#include <fstream>
#include <string>

// Parses cities file and returns a vector of vectors where
// each vector has string id, string code, string name, string population, string elevation
std::vector<std::vector<std::string>> parse_cities_file(std::istream &file)
{
    std::vector<std::vector<std::string>> cities;
    std::string id, code, name, population, elevation;

    while (!file.eof())
    {
        std::vector<std::string> city;

        std::getline(file, id, '\t');
        std::getline(file, code, '\t');
        std::getline(file, name, '\t');
        std::getline(file, population, '\t');
        std::getline(file, elevation, '\n');

        city.push_back(id);
        city.push_back(code);
        city.push_back(name);
        city.push_back(population);
        city.push_back(elevation);
        cities.push_back(city);
    }

    return cities;
}

// Parses routes/roads file and returns a vector of vectors where
// each vector has from_city (source), to_city (target), distance (weight)
std::vector<std::vector<unsigned>> parse_routes_file(std::istream &file)
{
    std::vector<std::vector<unsigned>> routes;
    unsigned from_city = 0, to_city = 0, distance = 0;

    while (file >> from_city)
    {
        std::vector<unsigned> route;

        file >> to_city;
        file >> distance;

        route.push_back(from_city);
        route.push_back(to_city);
        route.push_back(distance);
        routes.push_back(route);
    }

    return routes;
}