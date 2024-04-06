//
// Created by rodri on 03/04/2024.
//

#include "City.h"
using namespace std;

City::City(int id, string code, string name, double demand, int population) {
    this->id = id;
    this->code = code;
    this->name = name;
    this->demand = demand;
    this->population = population;
    this->active = true;
    this->visited = false;
    this->receiving_flow = 0;
    this->input_pipelines_codes = vector<std::string>();
}

int City::getId() {
    return this->id;
}

string City::getCode() {
    return this->code;
}

string City::getName() {
    return this->name;
}

double City::getDemand() {
    return this->demand;
}

int City::getPopulation() {
    return this->population;
}

double City::getReceivingFlow() {
    return this->receiving_flow;
}

void City::setReceivingFlow(double flow) {
    this->receiving_flow = flow;
}

void City::addReceivingFlow(double flow) {
    this->receiving_flow += flow;
}

void City::removeReceivingFlow(double flow) {
    this->receiving_flow -= flow;
}

bool City::isActive() {
    return this->active;
}

void City::setActive(bool active) {
    this->active = active;
}

bool City::hasBeenVisited() {
    return this->visited;
}

void City::setVisited(bool visited) {
    this->visited = visited;
}

void City::addInputPipeline(string pipeline_code) {
    this->input_pipelines_codes.push_back(pipeline_code);
}

std::vector<std::string> City::getInputPipelinesCodes() {
    return this->input_pipelines_codes;
}

bool City::operator==(const City &other) const {
    return this->id == other.id;
}