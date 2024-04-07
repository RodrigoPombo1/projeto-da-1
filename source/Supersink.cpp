#include "Supersink.h"

using namespace std;

/// @brief Initializes the supersink constructor
/// complexity: O(n) (n = number of cities)
/// @param cities pointer to the cities
/// @param pipelines pointer to the pipelines
Supersink::Supersink(std::unordered_map<std::string, City> *cities, std::unordered_map<std::string, Pipeline> *pipelines) {
    this->demand = 0;
    this->flow = 0;
    for (auto &city : *cities) {
        if (city.second.isActive()) {
            this->demand += city.second.getDemand();
            for (auto &pipeline: city.second.getInputPipelinesCodes()) {
                this->super_sink_input_pipelines_codes_map_to_pointer.insert({pipeline, &pipelines->at(pipeline)});
            }
        }
    }
    this->cities_pointer = cities;
}

/// @brief Gets the demand of the supersink
/// complexity: O(1)
/// @return the demand of the supersink
double Supersink::getDemand() {
    return this->demand;
}

/// @brief Gets the flow of the supersink
/// complexity: O(1)
/// @return the flow of the supersink
double Supersink::getFlow() {
    return this->flow;
}

/// @brief Gets pointers to the codes of the input pipelines of the supersink
/// complexity: O(1)
/// @return an unordered map with pointers to the codes of the input pipelines of the supersink
std::unordered_map<std::string, Pipeline*> Supersink::getSuperSinkInputPipelinesCodesMapToPointers() {
    return this->super_sink_input_pipelines_codes_map_to_pointer;
}

/// @brief Sets the flow of the supersink
/// complexity: O(1)
/// @param flow the flow of the supersink
void Supersink::setFlowToSupersink(double flow) {
    this->flow = flow;
}

/// @brief Adds a flow to the supersink input of a specific city
/// complexity: O(1)
/// @param city_code the code of the city
/// @param flow the flow to be added
void Supersink::addFlowToSuperSinkInputOfSpecificCity(std::string city_code, double flow) {
    this->cities_pointer->at(city_code).addReceivingFlow(flow);
}

/// @brief Removes a flow from the supersink input of a specific city
/// complexity: O(1)
/// @param city_code the code of the city
/// @param flow the flow to be removed
void Supersink::removeFlowFromSuperSinkInputOfSpecificCity(std::string city_code, double flow) {
    this->cities_pointer->at(city_code).removeReceivingFlow(flow);
}

/// @brief Checks if the supersink has a city
/// complexity: O(1)
/// @param city_code the code of the city
/// @return true if the supersink has the city, false otherwise
bool Supersink::hasCity(std::string city_code) {
    return this->cities_pointer->find(city_code) != this->cities_pointer->end();
}

/// @brief Gets the codes of the cities
/// complexity: O(n) (n = number of cities)
/// @return a vector with the codes of the cities
std::vector<std::string> Supersink::getCitiesCodes() {
    std::vector<std::string> cities_codes;
    for (auto &city : *this->cities_pointer) {
        if (city.second.isActive()) {
            cities_codes.push_back(city.first);
        }
    }
    return cities_codes;
}

/// @brief Checks if the supersink has an input edge
/// complexity: O(1)
/// @param pipeline_code the code of the pipeline
/// @return true if the supersink has the input edge, false otherwise
bool Supersink::hasInputEdge(std::string pipeline_code) {
    return this->super_sink_input_pipelines_codes_map_to_pointer.find(pipeline_code) != this->super_sink_input_pipelines_codes_map_to_pointer.end();
}