//
// Created by rodri on 03/04/2024.
//

#ifndef PROJETO_DA_1_CSV_READER_H
#define PROJETO_DA_1_CSV_READER_H

#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "City.h"
#include "Pipeline.h"
#include "Water_reservoir.h"
#include "Pumping_station.h"

class csv_reader {
private:
    std::string cities_csv_file_name;
    std::string pipes_csv_file_name;
    std::string reservoir_csv_file_name;
    std::string stations_csv_file_name;
    void read_cities_csv();
    void read_pipes_csv();
    void read_reservoir_csv();
    void read_stations_csv();
    std::unordered_map<std::string, City> cities;
    std::unordered_map<std::string, Water_reservoir> reservoirs;
    std::unordered_map<std::string, Pumping_station> stations;
    std::unordered_map<std::string, Pipeline> pipes;
public:
    csv_reader();
    std::unordered_map<std::string, City> getCities();
    std::unordered_map<std::string, Pipeline> getPipes();
    std::unordered_map<std::string, Water_reservoir> getReservoirs();
    std::unordered_map<std::string, Pumping_station> getStations();
};


#endif //PROJETO_DA_1_CSV_READER_H
