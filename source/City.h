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
    int population;
    std::vector<Pipeline*> input_pipelines;
    std::vector<Pipeline*> output_pipelines;
    std::vector<Pipeline*> bidirectional_pipelines;
public:
    City(int id, std::string code, std::string name, double demand, int population);
    int getId();
    std::string getCode();
    std::string getName();
    double getDemand();
    int getPopulation();
    void addInputPipeline(Pipeline *pipeline);
    void removeInputPipeline(Pipeline *pipeline);
    void addOutputPipeline(Pipeline *pipeline);
    void removeOutputPipeline(Pipeline *pipeline);
    void addBidirectionalPipeline(Pipeline *pipeline);
    void removeBidirectionalPipeline(Pipeline *pipeline);
    bool operator==(const City &other) const;
};


#endif //PROJETO_DA_1_CITY_H
