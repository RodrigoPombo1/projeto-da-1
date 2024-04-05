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
    std::vector<std::string> input_pipelines_codes;
    std::vector<std::string> output_pipelines_codes;
public:
    City(int id, std::string code, std::string name, double demand, int population);
    int getId();
    std::string getCode();
    std::string getName();
    double getDemand();
    int getPopulation();
    void addInputPipeline(std::string pipeline_code);
    void removeInputPipeline(std::string pipeline_code);
    void addOutputPipeline(std::string pipeline_code);
    void removeOutputPipeline(std::string pipeline_code);
    bool operator==(const City &other) const;
};


#endif //PROJETO_DA_1_CITY_H
