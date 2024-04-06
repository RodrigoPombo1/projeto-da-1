//
// Created by rodri on 03/04/2024.
//

#ifndef PROJETO_DA_1_CITY_H
#define PROJETO_DA_1_CITY_H

#include <string>
#include <vector>
#include "Pipeline.h"

class Pipeline;

class City {
private:
    int id;
    std::string code;
    std::string name;
    double demand;
    double receiving_flow;
    int population;
    bool active;
    bool visited;
    std::vector<std::string> input_pipelines_codes;
public:
    City(int id, std::string code, std::string name, double demand, int population);
    int getId();
    std::string getCode();
    std::string getName();
    double getDemand();
    int getPopulation();
    double getReceivingFlow();
    void setReceivingFlow(double flow);
    void addReceivingFlow(double flow);
    void removeReceivingFlow(double flow);
    bool isActive();
    void setActive(bool active);
    bool hasBeenVisited();
    void setVisited(bool visited);
    void addInputPipeline(std::string pipeline_code);
    std::vector<std::string> getInputPipelinesCodes();
    bool operator==(const City &other) const;
};


#endif //PROJETO_DA_1_CITY_H
