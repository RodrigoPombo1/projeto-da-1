#include "Pumping_station.h"

using namespace std;

/// @brief Initializes the pumping station constructor
/// complexity: O(1)
/// @param id the ID of the pumping station
/// @param code the code of the pumping station
Pumping_station::Pumping_station(int id, string code) {
    this->id = id;
    this->code = code;
    this->input_pipelines = vector<string>();
    this->output_pipelines = vector<string>();
    this->active = true;
}

/// @brief Gets the ID of the pumping station
/// complexity: O(1)
/// @return the ID of the pumping station
int Pumping_station::getId() {
    return this->id;
}

/// @brief Gets the code of the pumping station
/// complexity: O(1)
/// @return the code of the pumping station
string Pumping_station::getCode() {
    return this->code;
}

/// @brief Checks if the pumping station is active
/// complexity: O(1)
/// @return true if the pumping station is active, false otherwise
bool Pumping_station::isActive() {
    return this->active;
}

/// @brief Sets the pumping station as active or inactive
/// complexity: O(1)
/// @param active true if the pumping station is active, false otherwise
void Pumping_station::setActive(bool active) {
    this->active = active;
}

/// @brief Adds a input pipeline to the pumping station
/// complexity: O(1)
/// @param pipeline_code the code of the pipeline
void Pumping_station::addInputPipeline(std::string pipeline_code) {
    this->input_pipelines.push_back(pipeline_code);
}

/// @brief Removes a input pipeline from the pumping station
/// complexity: O(n) (n = number of input pipelines)
/// @param pipeline_code the code of the pipeline
void Pumping_station::removeInputPipeline(std::string pipeline_code) {
    for (int i = 0; i < this->input_pipelines.size(); i++) {
        if (this->input_pipelines[i] == pipeline_code) {
            this->input_pipelines.erase(this->input_pipelines.begin() + i);
            break;
        }
    }
}

/// @brief Adds a output pipeline to the pumping station
/// complexity: O(1)
/// @param pipeline_code the code of the pipeline
void Pumping_station::addOutputPipeline(std::string pipeline_code) {
    this->output_pipelines.push_back(pipeline_code);
}

/// @brief Removes a output pipeline from the pumping station
/// complexity: O(n) (n = number of output pipelines)
/// @param pipeline_code the code of the pipeline
void Pumping_station::removeOutputPipeline(std::string pipeline_code) {
    for (int i = 0; i < this->output_pipelines.size(); i++) {
        if (this->output_pipelines[i] == pipeline_code) {
            this->output_pipelines.erase(this->output_pipelines.begin() + i);
            break;
        }
    }
}

/// @brief Gets the input pipelines codes
/// complexity: O(1)
/// @return vector with the input pipelines codes
vector<string> Pumping_station::getInputPipelinesCodes() {
    return this->input_pipelines;
}

/// @brief Gets the output pipelines codes
/// complexity: O(1)
/// @return vector with the output pipelines codes
vector<string> Pumping_station::getOutputPipelinesCodes() {
    return this->output_pipelines;
}

/// @brief Checks if the pumping station has been visited
/// complexity: O(1)
/// @return true if the pumping station has been visited, false otherwise
bool Pumping_station::hasBeenVisited() {
    return this->visited;
}

/// @brief Sets the pumping station as visited or not visited
/// complexity: O(1)
/// @param visited true if the pumping station has been visited, false otherwise
void Pumping_station::setVisited(bool visited) {
    this->visited = visited;
}

/// @brief Defines an operator to check if two pumping stations are the same
/// complexity: O(1)
/// @param other the other pumping station to compare
/// @return true if the pumping stations are the same, false otherwise
bool Pumping_station::operator==(const Pumping_station &other) const {
    return this->id == other.id;
}