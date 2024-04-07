#include "ReverseEdge.h"

using namespace std;

/// @brief Initializes the reverse edge constructor
/// complexity: O(1)
/// @param pipeline the pipeline that the reverse edge is based on
ReverseEdge::ReverseEdge(Pipeline *pipeline) {
    this->non_reverse_edge_pipeline_pointer = pipeline;
    this->flow = pipeline->getFlow();
    this->capacity = pipeline->getCapacity();
    this->active = pipeline->isActive();
    this->non_reverse_edge_code = pipeline->getCode();
    this->residual_capacity = this->capacity - this->flow;
}

/// @brief Gets the code of the non-reverse edge
/// complexity: O(1)
/// @return the code of the non-reverse edge
string ReverseEdge::getNonReverseEdgeCode() {
    return this->non_reverse_edge_code;
}

/// @brief Gets the capacity of the reverse edge
/// complexity: O(1)
/// @return the capacity of the reverse edge
double ReverseEdge::getCapacity() {
    return this->capacity;
}

/// @brief Checks if the reverse edge is active
/// complexity: O(1)
/// @return true if the reverse edge is active, false otherwise
bool ReverseEdge::isActive() {
    return this->active;
}

/// @brief Sets the reverse edge as active or inactive
/// complexity: O(1)
/// @param active true if the reverse edge is active, false otherwise
void ReverseEdge::setActive(bool active) {
    this->active = active;
}

/// @brief Gets the flow of the reverse edge
/// complexity: O(1)
/// @return the flow of the reverse edge
double ReverseEdge::getFlow() {
    return this->flow;
}

/// @brief Sets the flow of the reverse edge
/// complexity: O(1)
/// @param flow the flow of the reverse edge
void ReverseEdge::setFlow(double flow) {
    this->flow = flow;
    this->residual_capacity = this->capacity - flow;
}

/// @brief Gets the residual capacity of the reverse edge
/// complexity: O(1)
/// @return the residual capacity of the reverse edge
double ReverseEdge::getResidualCapacity() {
    return this->residual_capacity;
}

/// @brief Gets the pointer to the non-reverse edge pipeline
/// complexity: O(1)
/// @return the pointer to the non-reverse edge pipeline
Pipeline* ReverseEdge::getNonReverseEdgePipelinePointer() {
    return this->non_reverse_edge_pipeline_pointer;
}