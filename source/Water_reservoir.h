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
    std::vector<Pipeline*> input_pipelines;
    std::vector<Pipeline*> output_pipelines;
    std::vector<Pipeline*> bidirectional_pipelines;
public:
    Water_reservoir(int id, std::string code, std::string name, std::string municipality, int maximum_delivery);
    int getId();
    std::string getCode();
    std::string getName();
    std::string getMunicipality();
    int getMaximumDelivery();
    void addInputPipeline(Pipeline *pipeline);
    void removeInputPipeline(Pipeline *pipeline);
    void addOutputPipeline(Pipeline *pipeline);
    void removeOutputPipeline(Pipeline *pipeline);
    void addBidirectionalPipeline(Pipeline *pipeline);
    void removeBidirectionalPipeline(Pipeline *pipeline);
    bool operator==(const Water_reservoir &other) const;
};


#endif //PROJETO_DA_1_WATER_RESERVOIR_H
