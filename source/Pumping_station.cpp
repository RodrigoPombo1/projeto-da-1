//
// Created by rodri on 03/04/2024.
//

#include "Pumping_station.h"

using namespace std;

Pumping_station::Pumping_station(int id, string code) {
    this->id = id;
    this->code = code;
    this->input_pipelines = vector<Pipeline*>();
    this->output_pipelines = vector<Pipeline*>();
}

int Pumping_station::getId() {
    return this->id;
}

string Pumping_station::getCode() {
    return this->code;
}

void Pumping_station::addInputPipeline(Pipeline *pipeline) {
    this->input_pipelines.push_back(pipeline);
}

void Pumping_station::removeInputPipeline(Pipeline *pipeline) {
    for (int i = 0; i < this->input_pipelines.size(); i++) {
        if (this->input_pipelines[i] == pipeline) {
            this->input_pipelines.erase(this->input_pipelines.begin() + i);
            break;
        }
    }
}

void Pumping_station::addOutputPipeline(Pipeline *pipeline) {
    this->output_pipelines.push_back(pipeline);
}

void Pumping_station::removeOutputPipeline(Pipeline *pipeline) {
    for (int i = 0; i < this->output_pipelines.size(); i++) {
        if (this->output_pipelines[i] == pipeline) {
            this->output_pipelines.erase(this->output_pipelines.begin() + i);
            break;
        }
    }
}

void Pumping_station::addBidirectionalPipeline(Pipeline *pipeline) {
    this->bidirectional_pipelines.push_back(pipeline);
}

void Pumping_station::removeBidirectionalPipeline(Pipeline *pipeline) {
    for (int i = 0; i < this->bidirectional_pipelines.size(); i++) {
        if (this->bidirectional_pipelines[i] == pipeline) {
            this->bidirectional_pipelines.erase(this->bidirectional_pipelines.begin() + i);
            break;
        }
    }
}

bool Pumping_station::operator==(const Pumping_station &other) const {
    return this->id == other.id;
}