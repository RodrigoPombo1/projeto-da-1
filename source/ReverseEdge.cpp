//
// Created by rodri on 06/04/2024.
//

#include "ReverseEdge.h"

using namespace std;

ReverseEdge::ReverseEdge(Pipeline *pipeline) {
    this->non_reverse_edge_pipeline_pointer = pipeline;
    this->flow = pipeline->getFlow();
    this->capacity = pipeline->getCapacity();
    this->active = pipeline->isActive();
    this->non_reverse_edge_code = pipeline->getCode();
    this->residual_capacity = this->capacity - this->flow;
}

string ReverseEdge::getNonReverseEdgeCode() {
    return this->non_reverse_edge_code;
}

double ReverseEdge::getCapacity() {
    return this->capacity;
}

bool ReverseEdge::isActive() {
    return this->active;
}

void ReverseEdge::setActive(bool active) {
    this->active = active;
}

double ReverseEdge::getFlow() {
    return this->flow;
}

void ReverseEdge::setFlow(double flow) {
    this->flow = flow;
    this->residual_capacity = this->capacity - flow;
}

double ReverseEdge::getResidualCapacity() {
    return this->residual_capacity;
}

Pipeline* ReverseEdge::getNonReverseEdgePipelinePointer() {
    return this->non_reverse_edge_pipeline_pointer;
}