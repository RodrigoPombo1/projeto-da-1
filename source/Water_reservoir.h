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
    double maximum_delivery;
    double output_flow;
    bool active;
    bool visited;
    std::vector<std::string> output_pipelines;
public:
    Water_reservoir(int id, std::string code, std::string name, std::string municipality, double maximum_delivery);
    int getId();
    std::string getCode();
    std::string getName();
    std::string getMunicipality();
    double getMaximumDelivery();
    bool isActive();
    void setActive(bool active);
    bool hasBeenVisited();
    void setVisited(bool visited);
    void setOutputFlow(double flow);
    double getOutputFlow();
    void addOutputFlow(double flow);
    void removeOutputFlow(double flow);
    void addOutputPipeline(std::string pipeline_code);
    void removeOutputPipeline(std::string pipeline_code);
    std::vector<std::string> getOutputPipelinesCodes();
    bool operator==(const Water_reservoir &other) const;
};


#endif //PROJETO_DA_1_WATER_RESERVOIR_H
