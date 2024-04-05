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
    this->input_pipelines = vector<Pipeline*>();
    this->output_pipelines = vector<Pipeline*>();
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

void City::addInputPipeline(Pipeline *pipeline) {
    this->input_pipelines.push_back(pipeline);
}

void City::removeInputPipeline(Pipeline *pipeline) {
    for (int i = 0; i < this->input_pipelines.size(); i++) {
        if (this->input_pipelines[i] == pipeline) {
            this->input_pipelines.erase(this->input_pipelines.begin() + i);
            break;
        }
    }
}

void City::addOutputPipeline(Pipeline *pipeline) {
    this->output_pipelines.push_back(pipeline);
}

void City::removeOutputPipeline(Pipeline *pipeline) {
    for (int i = 0; i < this->output_pipelines.size(); i++) {
        if (this->output_pipelines[i] == pipeline) {
            this->output_pipelines.erase(this->output_pipelines.begin() + i);
            break;
        }
    }
}

bool City::operator==(const City &other) const {
    return this->id == other.id;
}