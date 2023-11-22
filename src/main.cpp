#include <iostream>
#include <fstream>
#include "graph.cpp"
#include "parsing.cpp"
#include <vector>


string verify_commandline_args(int argc, char **argv){
    //Purpose: Use these two args and check if their valid
    //Validity criterion:
    string Verified = "true"; 
    
    if(argc > 3){
       Verified = "cmd args exceed limit of 3";
    }
    
    else if(argc < 3){
       Verified = "cmd args are less than 3";
       
    }

    return Verified; 
}

int main(int argc, char **argv)
{   //Check and verify args validity
   
    string verified = verify_commandline_args(argc, argv);

    if(verified != "true"){
        //Return and quite the program on incorrect arguments
        cout << "\x1b[31mIncorrect Command Line Arguments\x1b[0m" << endl; 
        cout << "\x1b[33m[Error Details]: " << verified << "\x1b[0m"  <<endl; 
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
    std::vector<std::vector<unsigned>> parsedRoutes = parse_routes_file(routesFile);
    for (int i = 0; i < parsedRoutes.size(); i++)
    {
        unsigned from_city = parsedRoutes[i][0];
        unsigned to_city = parsedRoutes[i][1];
        unsigned distance = parsedRoutes[i][2];

        cities.add_connection(from_city, to_city, distance);
    }

    // Process command line args
    // std::string starting_city = argv[0];
    // std::string target_city = argv[1];

    // Program termination
    citiesFile.close();
    routesFile.close();
    return 0;
}