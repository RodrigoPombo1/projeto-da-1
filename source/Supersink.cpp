//
// Created by rodri on 06/04/2024.
//

#include "Supersink.h"

using namespace std;

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

double Supersink::getDemand() {
    return this->demand;
}

double Supersink::getFlow() {
    return this->flow;
}

std::unordered_map<std::string, Pipeline*> Supersink::getSuperSinkInputPipelinesCodesMapToPointers() {
    return this->super_sink_input_pipelines_codes_map_to_pointer;
}

void Supersink::setFlowToSupersink(double flow) {
    this->flow = flow;
}

void Supersink::addFlowToSuperSinkInputOfSpecificCity(std::string city_code, double flow) {
    this->cities_pointer->at(city_code).addReceivingFlow(flow);
}

void Supersink::removeFlowFromSuperSinkInputOfSpecificCity(std::string city_code, double flow) {
    this->cities_pointer->at(city_code).removeReceivingFlow(flow);
}

bool Supersink::hasCity(std::string city_code) {
    return this->cities_pointer->find(city_code) != this->cities_pointer->end();
}

std::vector<std::string> Supersink::getCitiesCodes() {
    std::vector<std::string> cities_codes;
    for (auto &city : *this->cities_pointer) {
        if (city.second.isActive()) {
            cities_codes.push_back(city.first);
        }
    }
    return cities_codes;
}

bool Supersink::hasInputEdge(std::string pipeline_code) {
    return this->super_sink_input_pipelines_codes_map_to_pointer.find(pipeline_code) != this->super_sink_input_pipelines_codes_map_to_pointer.end();
}