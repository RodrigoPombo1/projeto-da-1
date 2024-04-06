//
// Created by rodri on 03/04/2024.
//

#include "Water_reservoir.h"
using namespace std;

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

double Water_reservoir::getMaximumDelivery() {
    return this->maximum_delivery;
}

bool Water_reservoir::isActive() {
    return this->active;
}

void Water_reservoir::setActive(bool active) {
    this->active = active;
}

bool Water_reservoir::hasBeenVisited() {
    return this->visited;
}

void Water_reservoir::setVisited(bool visited) {
    this->visited = visited;
}

void Water_reservoir::setOutputFlow(double flow) {
    this->output_flow = flow;
}

double Water_reservoir::getOutputFlow() {
    return this->output_flow;
}

void Water_reservoir::addOutputFlow(double flow) {
    this->output_flow += flow;
}

void Water_reservoir::removeOutputFlow(double flow) {
    this->output_flow -= flow;
}

void Water_reservoir::addOutputPipeline(string pipeline_code) {
    this->output_pipelines.push_back(pipeline_code);
}

void Water_reservoir::removeOutputPipeline(string pipeline_code) {
    for (int i = 0; i < this->output_pipelines.size(); i++) {
        if (this->output_pipelines[i] == pipeline_code) {
            this->output_pipelines.erase(this->output_pipelines.begin() + i);
            break;
        }
    }
}

vector<string> Water_reservoir::getOutputPipelinesCodes() {
    return this->output_pipelines;
}

bool Water_reservoir::operator==(const Water_reservoir &other) const {
    return this->id == other.id;
}