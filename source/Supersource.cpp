//
// Created by rodri on 06/04/2024.
//

#include "Supersource.h"

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

double Supersource::getMaximumDelivery() {
    return this->maximum_delivery;
}

double Supersource::getFlow() {
    return this->flow;
}

std::unordered_map<std::string, Pipeline*> Supersource::getSuperSourceOutputPipelinesCodesMapToPointers() {
    return this->super_source_output_pipelines_codes_map_to_pointer;
}

void Supersource::setFlowToSupersource(double flow) {
    this->flow = flow;
}

void Supersource::addFlowToSuperSourceOutputOfSpecificReservoir(std::string reservoir_code, double flow) {
    this->water_reservoirs_pointer->at(reservoir_code).addOutputFlow(flow);
}

void Supersource::removeFlowFromSuperSourceOutputOfSpecificReservoir(std::string reservoir_code, double flow) {
    this->water_reservoirs_pointer->at(reservoir_code).removeOutputFlow(flow);
}

bool Supersource::hasReservoir(std::string reservoir_code) {
    return this->water_reservoirs_pointer->find(reservoir_code) != this->water_reservoirs_pointer->end();
}

std::vector<std::string> Supersource::getReservoirsCodes() {
    std::vector<std::string> reservoirs_codes;
    for (auto &reservoir : *this->water_reservoirs_pointer) {
        if (reservoir.second.isActive()) {
            reservoirs_codes.push_back(reservoir.first);
        }
    }
    return reservoirs_codes;
}

bool Supersource::hasOutputEdge(std::string pipeline_code) {
    return this->super_source_output_pipelines_codes_map_to_pointer.find(pipeline_code) != this->super_source_output_pipelines_codes_map_to_pointer.end();
}