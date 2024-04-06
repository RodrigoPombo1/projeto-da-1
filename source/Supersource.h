//
// Created by rodri on 06/04/2024.
//

#ifndef PROJETO_DA_1_SUPERSOURCE_H
#define PROJETO_DA_1_SUPERSOURCE_H

#include <string>
#include <unordered_map>
#include "Water_reservoir.h"

class Supersource {
private:
    double maximum_delivery;
    double flow;
    std::unordered_map<std::string, Water_reservoir> *water_reservoirs_pointer;
    std::unordered_map<std::string, Pipeline*> super_source_output_pipelines_codes_map_to_pointer;
public:
    Supersource(std::unordered_map<std::string, Water_reservoir> *water_reservoirs, std::unordered_map<std::string, Pipeline> *pipelines);
    double getMaximumDelivery();
    double getFlow();
    std::unordered_map<std::string, Pipeline*> getSuperSourceOutputPipelinesCodesMapToPointers();
    void setFlowToSupersource(double flow);
    void addFlowToSuperSourceOutputOfSpecificReservoir(std::string reservoir_code, double flow);
    void removeFlowFromSuperSourceOutputOfSpecificReservoir(std::string reservoir_code, double flow);
};


#endif //PROJETO_DA_1_SUPERSOURCE_H
