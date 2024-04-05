//
// Created by rodri on 03/04/2024.
//

#include "Water_reservoir.h"
using namespace std;

Water_reservoir::Water_reservoir(int id, std::string code, std::string name, std::string municipality, int maximum_delivery) {
    this->id = id;
    this->code = code;
    this->name = name;
    this->municipality = municipality;
    this->maximum_delivery = maximum_delivery;
    this->input_pipelines = vector<Pipeline*>();
    this->output_pipelines = vector<Pipeline*>();
}

int Water_reservoir::getId() {
    return this->id;
}

string Water_reservoir::getCode() {
    return this->code;
}

string Water_reservoir::getName() {
    return this->name;
}

string Water_reservoir::getMunicipality() {
    return this->municipality;
}

int Water_reservoir::getMaximumDelivery() {
    return this->maximum_delivery;
}

void Water_reservoir::addInputPipeline(Pipeline *pipeline) {
    this->input_pipelines.push_back(pipeline);
}

void Water_reservoir::removeInputPipeline(Pipeline *pipeline) {
    for (int i = 0; i < this->input_pipelines.size(); i++) {
        if (this->input_pipelines[i] == pipeline) {
            this->input_pipelines.erase(this->input_pipelines.begin() + i);
            break;
        }
    }
}

void Water_reservoir::addOutputPipeline(Pipeline *pipeline) {
    this->output_pipelines.push_back(pipeline);
}

void Water_reservoir::removeOutputPipeline(Pipeline *pipeline) {
    for (int i = 0; i < this->output_pipelines.size(); i++) {
        if (this->output_pipelines[i] == pipeline) {
            this->output_pipelines.erase(this->output_pipelines.begin() + i);
            break;
        }
    }
}

bool Water_reservoir::operator==(const Water_reservoir &other) const {
    return this->id == other.id;
}