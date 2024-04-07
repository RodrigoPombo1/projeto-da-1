#include "City.h"
using namespace std;

/// @brief Initializes the city constructor
/// complexity: O(1)
/// @param id the ID of the city
/// @param code the code of the city
/// @param name the name of the city
/// @param demand the demand of the city
/// @param population the population of the city
City::City(int id, string code, string name, double demand, int population) {
    this->id = id;
    this->code = code;
    this->name = name;
    this->demand = demand;
    this->population = population;
    this->active = true;
    this->receiving_flow = 0;
    this->input_pipelines_codes = vector<std::string>();
}

/// @brief Gets the ID of the city
/// complexity: O(1)
/// @return the ID of the city
int City::getId() {
    return this->id;
}

/// @brief Gets the code of the city
/// complexity: O(1)
/// @return the code of the city
string City::getCode() {
    return this->code;
}

/// @brief Gets the name of the city
/// complexity: O(1)
/// @return the name of the city
string City::getName() {
    return this->name;
}

/// @brief Gets the demand of the city
/// complexity: O(1)
/// @return the demand of the city
double City::getDemand() {
    return this->demand;
}

/// @brief Gets the population of the city
/// complexity: O(1)
/// @return the population of the city
int City::getPopulation() {
    return this->population;
}

/// @brief Gets the flow the city receives
/// complexity: O(1)
/// @return the flow the city receives
double City::getReceivingFlow() {
    return this->receiving_flow;
}

/// @brief Sets the flow the city receives
/// complexity: O(1)
/// @param flow the flow the city receives
void City::setReceivingFlow(double flow) {
    this->receiving_flow = flow;
}

/// @brief Adds flow to the flow the city is receiving
/// complexity: O(1)
/// @param flow the flow to be added
void City::addReceivingFlow(double flow) {
    this->receiving_flow += flow;
}

/// @brief Removes flow from the flow the city is receiving
/// complexity: O(1)
/// @param flow the flow to be removed
void City::removeReceivingFlow(double flow) {
    this->receiving_flow -= flow;
}

/// @brief Checks if the city is active
/// complexity: O(1)
/// @return true if the city is active, false otherwise
bool City::isActive() {
    return this->active;
}

/// @brief Sets the city as active or inactive
/// complexity: O(1)
/// @param active true if the city is active, false otherwise
void City::setActive(bool active) {
    this->active = active;
}

/// @brief Adds a pipeline to the city
/// complexity: O(1)
/// @param pipeline_code the code of the pipeline to be added
void City::addInputPipeline(string pipeline_code) {
    this->input_pipelines_codes.push_back(pipeline_code);
}

/// @brief Gets the code for the pipelines that are connected to the city
/// complexity: O(1)
/// @return vector with the codes for the pipelines that are connected to the city
std::vector<std::string> City::getInputPipelinesCodes() {
    return this->input_pipelines_codes;
}

/// @brief Checks if the city has been visited
/// complexity: O(1)
/// @return true if the city has been visited, false otherwise
bool City::hasBeenVisited() {
    return this->visited;
}

/// @brief Sets the city as visited or not visited
/// complexity: O(1)
/// @param visited true if the city has been visited, false otherwise
void City::setVisited(bool visited) {
    this->visited = visited;
}

/// @brief Defines an operator to check if two cities are the same
/// complexity: O(1)
/// @param other the city to be compared
/// @return true if the cities are the same, false otherwise
bool City::operator==(const City &other) const {
    return this->id == other.id;
}