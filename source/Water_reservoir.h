//
// Created by rodri on 03/04/2024.
//

#ifndef PROJETO_DA_1_WATER_RESERVOIR_H
#define PROJETO_DA_1_WATER_RESERVOIR_H

#include <string>
#include <vector>
#include "Pipeline.h"

class Pipeline;

class Water_reservoir {
private:
    int id;
    std::string code;
    std::string name;
    std::string municipality;
    int maximum_delivery;
    std::vector<std::string> input_pipelines;
    std::vector<std::string> output_pipelines;
public:
    Water_reservoir(int id, std::string code, std::string name, std::string municipality, int maximum_delivery);
    int getId();
    std::string getCode();
    std::string getName();
    std::string getMunicipality();
    int getMaximumDelivery();
    void addInputPipeline(std::string pipeline_code);
    void removeInputPipeline(std::string pipeline_code);
    void addOutputPipeline(std::string pipeline_code);
    void removeOutputPipeline(std::string pipeline_code);
    bool operator==(const Water_reservoir &other) const;
};


#endif //PROJETO_DA_1_WATER_RESERVOIR_H
