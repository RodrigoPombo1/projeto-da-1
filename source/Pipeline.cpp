#include "Pipeline.h"

using namespace std;

/// @brief Initializes the pipeline constructor
/// complexity: O(1)
/// @param capacity the capacity of the pipeline
/// @param code the code of the pipeline
/// @param service_point_a the first service point of the pipeline
/// @param service_point_b the second service point of the pipeline
/// @param service_point_type_a the type of the first service point
/// @param service_point_type_b the type of the second service point
Pipeline::Pipeline(double capacity, string code, service_point service_point_a, service_point service_point_b, service_point_type service_point_type_a, service_point_type service_point_type_b) {
    this->flow = 0;
    this->code = code;
    this->capacity = capacity;
    this->active = true;
    this->service_point_a = service_point_a;
    this->service_point_b = service_point_b;
    this->service_point_type_a = service_point_type_a;
    this->service_point_type_b = service_point_type_b;
    this->residual_capacity = capacity - this->flow;
    this->reverse_edge_pointer = nullptr;
}

/// @brief Gets the code of the pipeline
/// complexity: O(1)
/// @return the code of the pipeline
string Pipeline::getCode() {
    return this->code;
}

/// @brief Gets the capacity of the pipeline
/// complexity: O(1)
/// @return the capacity of the pipeline
double Pipeline::getCapacity() {
    return this->capacity;
}

/// @brief Checks if the pipeline is active
/// complexity: O(1)
/// @return true if the pipeline is active, false otherwise
bool Pipeline::isActive() {
    return this->active;
}

/// @brief Sets the pipeline as active or inactive
/// complexity: O(1)
/// @param active true if the pipeline is active, false otherwise
void Pipeline::setActive(bool active) {
    this->active = active;
}

/// @brief Gets the flow of the pipeline
/// complexity: O(1)
/// @return the flow of the pipeline
double Pipeline::getFlow() {
    return this->flow;
}

/// @brief Sets the flow of the pipeline
/// complexity: O(1)
/// @param flow the flow of the pipeline
void Pipeline::setFlow(double flow) {
    try {
        if (flow > this->capacity) {
            throw invalid_argument("Flow cannot be greater than capacity");
        }
    } catch (invalid_argument &e) {
        cout << e.what() << endl;
        return;
    }
    this->flow = flow;
    this->residual_capacity = this->capacity - flow;
}

/// @brief Gets the capacity left in the pipeline
/// complexity: O(1)
/// @return the capacity left in the pipeline
double Pipeline::getResidualCapacity() {
    return this->residual_capacity;
}

/// @brief Gets the service point A of the pipeline
/// complexity: O(1)
/// @return the service point A of the pipeline
service_point Pipeline::getServicePointA() {
    return this->service_point_a;
}

/// @brief Gets the service point B of the pipeline
/// complexity: O(1)
/// @return the service point B of the pipeline
service_point Pipeline::getServicePointB() {
    return this->service_point_b;
}

/// @brief Defines an operator to check if two pipelines are the same
/// complexity: O(1)
/// @param other the other pipeline to compare
/// @return true if the pipelines are the same, false otherwise
bool Pipeline::operator==(const Pipeline &other) const {
    if (!(this->capacity == other.capacity && this->service_point_type_a == other.service_point_type_a && this->service_point_type_b == other.service_point_type_b)) {
        return false;
    }
    bool check_service_point_a = false;
    bool check_service_point_b = false;
    if (this->service_point_type_a == PUMPING_STATION) {
        check_service_point_a = this->service_point_a.pumping_station == other.service_point_a.pumping_station;
    } else if (this->service_point_type_a == WATER_RESERVOIR) {
        check_service_point_a = this->service_point_a.water_reservoir == other.service_point_a.water_reservoir;
    } else if (this->service_point_type_a == CITY) {
        check_service_point_a = this->service_point_a.city == other.service_point_a.city;
    }
    if (this->service_point_type_b == PUMPING_STATION) {
        check_service_point_b = this->service_point_b.pumping_station == other.service_point_b.pumping_station;
    } else if (this->service_point_type_b == WATER_RESERVOIR) {
        check_service_point_b = this->service_point_b.water_reservoir == other.service_point_b.water_reservoir;
    } else if (this->service_point_type_b == CITY) {
        check_service_point_b = this->service_point_b.city == other.service_point_b.city;
    }
    return check_service_point_a && check_service_point_b;
}

/// @brief Gets the type of the service point A
/// complexity: O(1)
/// @return the type of the service point A
service_point_type Pipeline::getServicePointTypeA() {
    return this->service_point_type_a;
}

/// @brief Gets the type of the service point B
/// complexity: O(1)
/// @return the type of the service point B
service_point_type Pipeline::getServicePointTypeB() {
    return this->service_point_type_b;
}

/// @brief Gets the pointer to the reverse edge
/// complexity: O(1)
/// @return the pointer to the reverse edge
ReverseEdge* Pipeline::getReverseEdgePointer() {
    return this->reverse_edge_pointer;
}

/// @brief Defines an operator to check if two service points are the same
/// complexity: O(1)
/// @param a the first service point
/// @param b the second service point
/// @return true if the service points are the same, false otherwise
bool operator==(const service_point &a, const service_point &b) {
    if (a.pumping_station != nullptr && b.pumping_station != nullptr) {
        return a.pumping_station == b.pumping_station;
    } else if (a.water_reservoir != nullptr && b.water_reservoir != nullptr) {
        return a.water_reservoir == b.water_reservoir;
    } else if (a.city != nullptr && b.city != nullptr) {
        return a.city == b.city;
    }
    return false;
}