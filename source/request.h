//
// Created by rodri on 03/04/2024.
//

#ifndef PROJETO_DA_1_REQUEST_H
#define PROJETO_DA_1_REQUEST_H

#include "csv_reader.h"
#include "Supersink.h"
#include "Supersource.h"

class request {
private:
    csv_reader csvReader;
    std::unordered_map<std::string, City> cities;
    std::unordered_map<std::string, Water_reservoir> reservoirs;
    std::unordered_map<std::string, Pumping_station> stations;
    std::unordered_map<std::string, Pipeline> pipes;
public:
    request();
};

#endif //PROJETO_DA_1_REQUEST_H
