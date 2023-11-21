#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>

using namespace std;

class CityNode
{

private:
   string _ID = "";
   string _city_code = "";
   string _city_name = "";
   unsigned int _population = -1;
   int _elevation = -1;
   int shortest_distance = INT8_MAX;

   /*
    * [IMPORTANT]
    *  Linked-list of neighbors
    */
   list<CityNode *> neighbors;

public:
   CityNode(string id, string code, string name, unsigned int ppl, int elevation)
   {
      this->_city_code = code;
      this->_city_name = name;
      this->_ID = id;
      this->_population = ppl;
      this->_elevation = elevation;
   }
};

/**
 * [IMPORTANT]
 *
 * 1) Sketch details of well thought OOP outline of the Graph data structure with every possible function
 * 2) Break down code in functions in such a way that any team member can collaborate to complete this without needing to grasp full picture.
 * 3) Label each function and make commits for each function completed.
 */
class CityGraph
{

private:
   // vector version of graph (stable)
   // vector<CityNode *> NodeList;

   // untested map version of graph (unstable)
   // A city code maps to a city node
   unordered_map<string, CityNode *> NodeList;

public:
   // Add a city to the list of cities
   void add_city(string id, string code, string name, unsigned int ppl, int elevation)
   {
      CityNode *city = new CityNode(id, code, name, ppl, elevation);
      NodeList[id] = city;
   }

   // Remove the city from the list of cities
   void delete_city(string id)
   {
      // Given a list, must delete a node using a  id.
   }

   // Add a route between cities (DOESNT USE DISTANCE YET)
   void add_connection(unsigned from_city_code, unsigned to_city_code, unsigned distance)
   {
      CityNode *from_city = this->NodeList[to_string(from_city_code)];
      CityNode *to_city = this->NodeList[to_string(to_city_code)];
      from_city->neighbors.push_back(to_city);
   }

   // Remove a route between cities (HARD, requires removal from list)
   void delete_connection()
   {
      // Given two nodes, erase the connection between them
      // Access the info using nodes.
   }
};