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
    std::vector<Pipeline*> input_pipelines;
    std::vector<Pipeline*> output_pipelines;
    std::vector<Pipeline*> bidirectional_pipelines;
public:
    Pumping_station(int id, std::string code);
    int getId();
    std::string getCode();
    void addInputPipeline(Pipeline *pipeline);
    void removeInputPipeline(Pipeline *pipeline);
    void addOutputPipeline(Pipeline *pipeline);
    void removeOutputPipeline(Pipeline *pipeline);
    void addBidirectionalPipeline(Pipeline *pipeline);
    void removeBidirectionalPipeline(Pipeline *pipeline);
    bool operator==(const Pumping_station &other) const;
};


#endif //PROJETO_DA_1_PUMPING_STATION_H
