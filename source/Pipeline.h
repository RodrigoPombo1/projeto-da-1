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
#include "ReverseEdge.h"
#include <string>
#include <vector>

class City;
class Water_reservoir;
class Pumping_station;
class ReverseEdge;

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
    double capacity;
    double residual_capacity;
    double flow;
    bool active;
    ReverseEdge* reverse_edge_pointer;
    std::string code;
    service_point service_point_a;
    service_point service_point_b;
    service_point_type service_point_type_a;
    service_point_type service_point_type_b;
public:
    Pipeline(double capacity, std::string code, service_point service_point_a, service_point service_point_b, service_point_type service_point_type_a, service_point_type service_point_type_b);
    std::string getCode();
    double getCapacity();
    bool isActive();
    void setActive(bool active);
    double getFlow();
    void setFlow(double flow);
    double getResidualCapacity();
    service_point getServicePointA();
    service_point getServicePointB();
    service_point_type getServicePointTypeA();
    service_point_type getServicePointTypeB();
    ReverseEdge* getReverseEdgePointer();
    bool operator==(const Pipeline &other) const;
};


#endif //PROJETO_DA_1_PIPELINE_H
