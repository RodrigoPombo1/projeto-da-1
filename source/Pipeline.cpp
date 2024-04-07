//
// Created by rodri on 03/04/2024.
//

#include "Pipeline.h"

using namespace std;

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

string Pipeline::getCode() {
    return this->code;
}

double Pipeline::getCapacity() {
    return this->capacity;
}

bool Pipeline::isActive() {
    return this->active;
}

void Pipeline::setActive(bool active) {
    this->active = active;
}

double Pipeline::getFlow() {
    return this->flow;
}

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

double Pipeline::getResidualCapacity() {
    return this->residual_capacity;
}

service_point Pipeline::getServicePointA() {
    return this->service_point_a;
}

service_point Pipeline::getServicePointB() {
    return this->service_point_b;
}

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

service_point_type Pipeline::getServicePointTypeA() {
    return this->service_point_type_a;
}

service_point_type Pipeline::getServicePointTypeB() {
    return this->service_point_type_b;
}

ReverseEdge* Pipeline::getReverseEdgePointer() {
    return this->reverse_edge_pointer;
}

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