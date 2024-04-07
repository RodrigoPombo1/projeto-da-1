#include "Supersource.h"

/// @brief Initializes the supersource constructor
/// complexity: O(n) (n = number of water reservoirs)
/// @param water_reservoirs pointer to the water reservoirs
/// @param pipelines pointer to the pipelines
Supersource::Supersource(std::unordered_map<std::string, Water_reservoir> *water_reservoirs, std::unordered_map<std::string, Pipeline> *pipelines) {
    this->maximum_delivery = 0;
    this->flow = 0;
    this->water_reservoirs_pointer = water_reservoirs;
    for (auto &water_reservoir : *water_reservoirs) {
        if (water_reservoir.second.isActive()) {
            this->maximum_delivery += water_reservoir.second.getMaximumDelivery();
            for (auto &pipeline: water_reservoir.second.getOutputPipelinesCodes()) {
                if (pipelines->at(pipeline).isActive()) {
                    this->super_source_output_pipelines_codes_map_to_pointer.insert({pipeline, &pipelines->at(pipeline)});
                }
            }
        }
    }
}

/// @brief Gets the maximum delivery of the supersource
/// complexity: O(1)
/// @return the maximum delivery of the supersource
double Supersource::getMaximumDelivery() {
    return this->maximum_delivery;
}

/// @brief Gets the flow of the supersource
/// complexity: O(1)
/// @return the flow of the supersource
double Supersource::getFlow() {
    return this->flow;
}

/// @brief Gets pointers to the codes of the output pipelines of the supersource
/// complexity: O(1)
/// @return an unordered map with pointers to the codes of the output pipelines of the supersource
std::unordered_map<std::string, Pipeline*> Supersource::getSuperSourceOutputPipelinesCodesMapToPointers() {
    return this->super_source_output_pipelines_codes_map_to_pointer;
}

/// @brief Sets the flow of the supersource
/// complexity: O(1)
/// @param flow the flow of the supersource
void Supersource::setFlowToSupersource(double flow) {
    this->flow = flow;
}

/// @brief Adds a flow to the supersource output of a specific reservoir
/// complexity: O(1)
/// @param reservoir_code the code of the reservoir
/// @param flow the flow to be added
void Supersource::addFlowToSuperSourceOutputOfSpecificReservoir(std::string reservoir_code, double flow) {
    this->water_reservoirs_pointer->at(reservoir_code).addOutputFlow(flow);
}

/// @brief Removes a flow from the supersource output of a specific reservoir
/// complexity: O(1)
/// @param reservoir_code the code of the reservoir
/// @param flow the flow to be removed
void Supersource::removeFlowFromSuperSourceOutputOfSpecificReservoir(std::string reservoir_code, double flow) {
    this->water_reservoirs_pointer->at(reservoir_code).removeOutputFlow(flow);
}

/// @brief Checks if the supersource has a reservoir
/// complexity: O(1)
/// @param reservoir_code the code of the reservoir
/// @return true if the supersource has the reservoir, false otherwise
bool Supersource::hasReservoir(std::string reservoir_code) {
    return this->water_reservoirs_pointer->find(reservoir_code) != this->water_reservoirs_pointer->end();
}

/// @brief Gets the codes of the reservoirs
/// complexity: O(n) (n = number of reservoirs)
/// @return vector with the codes of the reservoirs
std::vector<std::string> Supersource::getReservoirsCodes() {
    std::vector<std::string> reservoirs_codes;
    for (auto &reservoir : *this->water_reservoirs_pointer) {
        if (reservoir.second.isActive()) {
            reservoirs_codes.push_back(reservoir.first);
        }
    }
    return reservoirs_codes;
}

/// @brief Checks if the supersource has an output edge
/// complexity: O(1)
/// @param pipeline_code the code of the pipeline to search for
/// @return true if the supersource has the output edge, false otherwise
bool Supersource::hasOutputEdge(std::string pipeline_code) {
    return this->super_source_output_pipelines_codes_map_to_pointer.find(pipeline_code) != this->super_source_output_pipelines_codes_map_to_pointer.end();
}