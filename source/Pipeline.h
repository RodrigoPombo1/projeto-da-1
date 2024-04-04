//
// Created by rodri on 03/04/2024.
//

#ifndef PROJETO_DA_1_PIPELINE_H
#define PROJETO_DA_1_PIPELINE_H

#include <string>
#include <vector>
#include "Pumping_station.h"
#include "Water_reservoir.h"
#include "City.h"
#include <string>
#include <vector>

class City;
class Water_reservoir;
class Pumping_station;

union service_point {
    Pumping_station *pumping_station;
    Water_reservoir *water_reservoir;
    City *city;
};

enum service_point_type {
    PUMPING_STATION,
    WATER_RESERVOIR,
    CITY
};

class Pipeline {
private:
    int capacity;
    bool is_unidirectional;
    service_point service_point_a;
    service_point service_point_b;
    service_point_type service_point_type_a;
    service_point_type service_point_type_b;
public:
    Pipeline(int capacity, bool is_unidirectional, service_point service_point_a, service_point service_point_b, service_point_type service_point_type_a, service_point_type service_point_type_b);
    int getCapacity();
    bool getIsUnidirectional();
    service_point getServicePointA();
    service_point getServicePointB();
    bool operator==(const Pipeline &other) const;
};


#endif //PROJETO_DA_1_PIPELINE_H
