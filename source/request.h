//
// Created by rodri on 03/04/2024.
//

#ifndef PROJETO_DA_1_REQUEST_H
#define PROJETO_DA_1_REQUEST_H

#include "csv_reader.h"
#include "Supersink.h"
#include "Supersource.h"
#include "ReverseEdge.h"
#include <queue>
#include <unordered_set>
#include <limits>

class request {
private:
    csv_reader csvReader;
    std::unordered_map<std::string, City> cities;
    std::unordered_map<std::string, Water_reservoir> water_reservoirs;
    std::unordered_map<std::string, Pumping_station> stations;
    std::unordered_map<std::string, Pipeline> pipes;

    // methods
    double EdmondsKarp();
    void setCityInactive(std::string city_code);
    void setWaterReservoirInactive(std::string water_reservoir_code);
    void setPumpingStationInactive(std::string pumping_station_code);
    void setPipelineInactive(std::string pipeline_code);
    void setAllActive();
    void updateFlowForEachCity();
    void updateFlowForEachWaterReservoir();
    void resetFlowForEachCity();
    void resetFlowForEachWaterReservoir();
    void resetFlowForEachPipeline();
public:
    request();
    std::vector<std::string> get_maximum_amount_of_water_all_and_each_city();
    std::string get_maximum_amount_of_water_for_a_specific_city(std::string city_code);
    bool check_city_exists(std::string city_code);
    bool check_water_reservoir_exists(std::string water_reservoir_code);
    bool check_pumping_station_exists(std::string pumping_station_code);
    std::vector<std::string> can_all_cities_be_supplied();
    std::vector<std::string> get_maximum_amount_of_water_all_and_each_city_that_cannot_be_supplied_but_deactivate_reservoir(std::string reservoir_code);
    std::vector<std::string> get_maximum_amount_of_water_all_and_each_city_that_cannot_be_supplied_but_deactivate_station(std::string station_code);
};

#endif //PROJETO_DA_1_REQUEST_H
