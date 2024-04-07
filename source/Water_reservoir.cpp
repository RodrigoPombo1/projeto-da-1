#include "Water_reservoir.h"
using namespace std;

/// @brief Initializes the water reservoir constructor
/// complexity: O(1)
/// @param id the ID of the water reservoir
/// @param code the code of the water reservoir
/// @param name the name of the water reservoir
/// @param municipality the municipality of the water reservoir
/// @param maximum_delivery the maximum delivery of the water reservoir
Water_reservoir::Water_reservoir(int id, std::string code, std::string name, std::string municipality, double maximum_delivery) {
    this->id = id;
    this->code = code;
    this->name = name;
    this->municipality = municipality;
    this->maximum_delivery = maximum_delivery;
    this->active = true;
    this->visited = false;
    this->output_pipelines = vector<std::string>();
}

/// @brief Gets the ID of the water reservoir
/// complexity: O(1)
/// @return the ID of the water reservoir
int Water_reservoir::getId() {
    return this->id;
}

/// @brief Gets the code of the water reservoir
/// complexity: O(1)
/// @return the code of the water reservoir
string Water_reservoir::getCode() {
    return this->code;
}

/// @brief Gets the name of the water reservoir
/// complexity: O(1)
/// @return the name of the water reservoir
string Water_reservoir::getName() {
    return this->name;
}

/// @brief Gets the municipality of the water reservoir
/// complexity: O(1)
/// @return the municipality of the water reservoir
string Water_reservoir::getMunicipality() {
    return this->municipality;
}

/// @brief Gets the maximum delivery of the water reservoir
/// complexity: O(1)
/// @return the maximum delivery of the water reservoir
double Water_reservoir::getMaximumDelivery() {
    return this->maximum_delivery;
}

/// @brief Checks if the water reservoir is active
/// complexity: O(1)
/// @return true if the water reservoir is active, false otherwise
bool Water_reservoir::isActive() {
    return this->active;
}

/// @brief Sets the water reservoir as active or inactive
/// complexity: O(1)
/// @param active true if the water reservoir is active, false otherwise
void Water_reservoir::setActive(bool active) {
    this->active = active;
}

/// @brief Checks if the water reservoir has been visited
/// complexity: O(1)
/// @return true if the water reservoir has been visited, false otherwise
bool Water_reservoir::hasBeenVisited() {
    return this->visited;
}

/// @brief Sets the water reservoir as visited or not visited
/// complexity: O(1)
/// @param visited true if the water reservoir has been visited, false otherwise
void Water_reservoir::setVisited(bool visited) {
    this->visited = visited;
}

/// @brief Sets the output flow of the water reservoir
/// complexity: O(1)
/// @param flow the output flow of the water reservoir
void Water_reservoir::setOutputFlow(double flow) {
    this->output_flow = flow;
}

/// @brief Gets the output flow of the water reservoir
/// complexity: O(1)
/// @return the output flow of the water reservoir
double Water_reservoir::getOutputFlow() {
    return this->output_flow;
}

/// @brief Adds flow to the output flow of the water reservoir
/// complexity: O(1)
/// @param flow the flow to be added
void Water_reservoir::addOutputFlow(double flow) {
    this->output_flow += flow;
}

/// @brief Removes flow from the output flow of the water reservoir
/// complexity: O(1)
/// @param flow the flow to be removed
void Water_reservoir::removeOutputFlow(double flow) {
    this->output_flow -= flow;
}

/// @brief Adds an output pipeline to the water reservoir
/// complexity: O(1)
/// @param pipeline_code the code of the pipeline
void Water_reservoir::addOutputPipeline(string pipeline_code) {
    this->output_pipelines.push_back(pipeline_code);
}

/// @brief Removes an output pipeline from the water reservoir
/// complexity: O(n) (n = number of output pipelines)
/// @param pipeline_code the code of the pipeline
void Water_reservoir::removeOutputPipeline(string pipeline_code) {
    for (int i = 0; i < this->output_pipelines.size(); i++) {
        if (this->output_pipelines[i] == pipeline_code) {
            this->output_pipelines.erase(this->output_pipelines.begin() + i);
            break;
        }
    }
}

/// @brief Gets the codes of the output pipelines
/// complexity: O(1)
/// @return vector with the codes of the output pipelines
vector<string> Water_reservoir::getOutputPipelinesCodes() {
    return this->output_pipelines;
}

/// @brief Defines an operator to check if two water reservoirs are the same
/// complexity: O(1)
/// @param other the other water reservoir to compare
/// @return true if the water reservoirs are the same, false otherwise
bool Water_reservoir::operator==(const Water_reservoir &other) const {
    return this->id == other.id;
}