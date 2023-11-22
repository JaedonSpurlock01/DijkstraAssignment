#include <stdio.h>
#include <iostream>
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
      *  Each node in the list has a tuple with (neighbor, distance_to_neighbor)
      */
      list<pair<CityNode *, unsigned>> neighbors;

   public:
      CityNode(string id, string code, string name, unsigned int ppl, int elevation)
      {
         this->_city_code = code;
         this->_city_name = name;
         this->_ID = id;
         this->_population = ppl;
         this->_elevation = elevation;
      }

      list<pair<CityNode*, unsigned>> fetch_neighbors()
      {
         return this->neighbors;
      }

      std::string fetch_city_name()
      {
         return this->_city_name;
      }

      list<pair<CityNode*, unsigned>> get_neighbor_at(){

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

      cout << "Added " << name << " to the list of cities\n";
   }

   // Remove the city from the list of cities
   void delete_city(string id)
   {
      // Given a list, must delete a node using a  id.
   }

   // Add a route between cities
   void add_connection(unsigned from_city_code, unsigned to_city_code, unsigned distance)
   {
      CityNode *from_city = this->NodeList[to_string(from_city_code)];
      CityNode *to_city = this->NodeList[to_string(to_city_code)];

      // Create a tuple with the qualities (target, weight)
      auto new_edge = make_pair(to_city, distance);

      // Add new connection to source node (directed-graph, so we don't need to do same for target node)
      from_city->fetch_neighbors().push_back(new_edge);

      cout << "Added a route from " << from_city->fetch_city_name() << " to " << to_city->fetch_city_name() << " with a distance of " << distance << "\n";
   }

   // Remove a route between cities (HARD, requires removal from list)
   void delete_connection(string source_city_code, string target_city_code)
   {
      //IMPLEMENT: Given two nodes erase the connection between them. Iterate thru source's neighbors to find target and reset it to something else

      CityNode* source = this->NodeList[source_city_code];
      CityNode* target = this->NodeList[target_city_code];

      //for (auto it = source->neighbors.begin(); it != source->neighbors.end(); ++it) {
       // std::cout << "Neighbor: " << it->first << ", Distance: " << it->second << std::endl;
      //}
   }


   bool search_by_city_id(string id){
      //[IMPLEMENT]: Given a string id traverse through NodeList structure to find a match
      for(const auto& city: this->NodeList){
         if(city.first == id){
            return true; 
         }
      }
      return false; 
   }

   bool search_by_city(CityNode* ctr){
     //[IMPLEMENT]: Given a *ptr traverse thru nodelist structure to find a match
     for(const auto& city: this->NodeList){
       if(city.second == ctr){
         return true;
       }
     }
     return false; 
   }
};