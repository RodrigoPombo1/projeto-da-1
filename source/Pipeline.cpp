//
// Created by rodri on 03/04/2024.
//

#include "Pipeline.h"

using namespace std;

Pipeline::Pipeline(int capacity, bool is_unidirectional, service_point service_point_a, service_point service_point_b, service_point_type service_point_type_a, service_point_type service_point_type_b) {
    this->capacity = capacity;
    this->is_unidirectional = is_unidirectional;
    this->service_point_a = service_point_a;
    this->service_point_b = service_point_b;
    this->service_point_type_a = service_point_type_a;
    this->service_point_type_b = service_point_type_b;
}

int Pipeline::getCapacity() {
    return this->capacity;
}

bool Pipeline::getIsUnidirectional() {
    return this->is_unidirectional;
}

service_point Pipeline::getServicePointA() {
    return this->service_point_a;
}

service_point Pipeline::getServicePointB() {
    return this->service_point_b;
}

bool Pipeline::operator==(const Pipeline &other) const {
    if (!(this->capacity == other.capacity && this->is_unidirectional == other.is_unidirectional && this->service_point_type_a == other.service_point_type_a && this->service_point_type_b == other.service_point_type_b)) {
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