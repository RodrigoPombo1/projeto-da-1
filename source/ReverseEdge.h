//
// Created by rodri on 06/04/2024.
//

#ifndef PROJETO_DA_1_REVERSEEDGE_H
#define PROJETO_DA_1_REVERSEEDGE_H

#include <string>
#include <vector>
#include "Pumping_station.h"
#include "Water_reservoir.h"
#include "City.h"
#include "Pipeline.h"
#include <string>
#include <vector>

class City;
class Water_reservoir;
class Pumping_station;
class Pipeline;

class ReverseEdge {
private:
    double capacity;
    double residual_capacity;
    double flow;
    bool active;
    std::string non_reverse_edge_code;
    Pipeline* non_reverse_edge_pipeline_pointer;
public:
    ReverseEdge(Pipeline *pipeline_pointer);
    std::string getNonReverseEdgeCode();
    double getCapacity();
    bool isActive();
    void setActive(bool active);
    double getFlow();
    void setFlow(double flow);
    double getResidualCapacity();
    Pipeline* getNonReverseEdgePipelinePointer();
};


#endif //PROJETO_DA_1_REVERSEEDGE_H
