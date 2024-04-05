//
// Created by rodri on 03/04/2024.
//

#ifndef PROJETO_DA_1_PUMPING_STATION_H
#define PROJETO_DA_1_PUMPING_STATION_H

#include <string>
#include <vector>

#include "Pipeline.h"

class Pipeline;

class Pumping_station {
private:
    int id;
    std::string code;
    std::vector<std::string> input_pipelines;
    std::vector<std::string> output_pipelines;
public:
    Pumping_station(int id, std::string code);
    int getId();
    std::string getCode();
    void addInputPipeline(std::string pipeline_code);
    void removeInputPipeline(std::string pipeline_code);
    void addOutputPipeline(std::string pipeline_code);
    void removeOutputPipeline(std::string pipeline_code);
    bool operator==(const Pumping_station &other) const;
};


#endif //PROJETO_DA_1_PUMPING_STATION_H
