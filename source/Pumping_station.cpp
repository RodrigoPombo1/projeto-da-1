//
// Created by rodri on 03/04/2024.
//

#include "Pumping_station.h"

using namespace std;

Pumping_station::Pumping_station(int id, string code) {
    this->id = id;
    this->code = code;
    this->input_pipelines = vector<string>();
    this->output_pipelines = vector<string>();
    this->active = true;
    this->visited = false;
}

int Pumping_station::getId() {
    return this->id;
}

string Pumping_station::getCode() {
    return this->code;
}

bool Pumping_station::isActive() {
    return this->active;
}

void Pumping_station::setActive(bool active) {
    this->active = active;
}

bool Pumping_station::hasBeenVisited() {
    return this->visited;
}

void Pumping_station::setVisited(bool visited) {
    this->visited = visited;
}

void Pumping_station::addInputPipeline(std::string pipeline_code) {
    this->input_pipelines.push_back(pipeline_code);
}

void Pumping_station::removeInputPipeline(std::string pipeline_code) {
    for (int i = 0; i < this->input_pipelines.size(); i++) {
        if (this->input_pipelines[i] == pipeline_code) {
            this->input_pipelines.erase(this->input_pipelines.begin() + i);
            break;
        }
    }
}

void Pumping_station::addOutputPipeline(std::string pipeline_code) {
    this->output_pipelines.push_back(pipeline_code);
}

void Pumping_station::removeOutputPipeline(std::string pipeline_code) {
    for (int i = 0; i < this->output_pipelines.size(); i++) {
        if (this->output_pipelines[i] == pipeline_code) {
            this->output_pipelines.erase(this->output_pipelines.begin() + i);
            break;
        }
    }
}

bool Pumping_station::operator==(const Pumping_station &other) const {
    return this->id == other.id;
}