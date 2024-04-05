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
    this->input_pipelines_codes = vector<std::string>();
    this->output_pipelines_codes = vector<std::string>();
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

void City::addInputPipeline(string pipeline_code) {
    this->input_pipelines_codes.push_back(pipeline_code);
}

void City::removeInputPipeline(string pipeline_code) {
    for (int i = 0; i < this->input_pipelines_codes.size(); i++) {
        if (this->input_pipelines_codes[i] == pipeline_code) {
            this->input_pipelines_codes.erase(this->input_pipelines_codes.begin() + i);
            break;
        }
    }
}

void City::addOutputPipeline(string pipeline_code) {
    this->output_pipelines_codes.push_back(pipeline_code);
}

void City::removeOutputPipeline(string pipeline_code) {
    for (int i = 0; i < this->output_pipelines_codes.size(); i++) {
        if (this->output_pipelines_codes[i] == pipeline_code) {
            this->output_pipelines_codes.erase(this->output_pipelines_codes.begin() + i);
            break;
        }
    }
}

bool City::operator==(const City &other) const {
    return this->id == other.id;
}