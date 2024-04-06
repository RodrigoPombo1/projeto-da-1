//
// Created by rodri on 06/04/2024.
//

#ifndef PROJETO_DA_1_SUPERSINK_H
#define PROJETO_DA_1_SUPERSINK_H

#include <string>
#include <unordered_map>
#include "City.h"

class Supersink {
private:
    double demand;
    double flow;
    std::unordered_map<std::string, City> *cities_pointer;
    std::unordered_map<std::string, Pipeline*> super_sink_input_pipelines_codes_map_to_pointer;
public:
    Supersink(std::unordered_map<std::string, City> *cities, std::unordered_map<std::string, Pipeline> *pipelines);
    double getDemand();
    double getFlow();
    std::unordered_map<std::string, Pipeline*> getSuperSinkInputPipelinesCodesMapToPointers();
    void setFlowToSupersink(double flow);
    void addFlowToSuperSinkInputOfSpecificCity(std::string city_code, double flow);
    void removeFlowFromSuperSinkInputOfSpecificCity(std::string city_code, double flow);
};


#endif //PROJETO_DA_1_SUPERSINK_H
