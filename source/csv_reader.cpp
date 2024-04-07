//
// Created by rodri on 03/04/2024.
//

#include "csv_reader.h"

using namespace std;

csv_reader::csv_reader() {
    // for the small dataset
    this->cities_csv_file_name = "data/Cities_Madeira.csv";
    this->pipes_csv_file_name = "data/Pipes_Madeira.csv";
    this->reservoir_csv_file_name = "data/Reservoirs_Madeira.csv";
    this->stations_csv_file_name = "data/Stations_Madeira.csv";

    // for the large dataset
//    this->cities_csv_file_name = "data/Cities.csv";
//    this->pipes_csv_file_name = "data/Pipes.csv";
//    this->reservoir_csv_file_name = "data/Reservoir.csv"; // é mesmo sem o s
//    this->stations_csv_file_name = "data/Stations.csv";

    read_cities_csv();
    read_reservoir_csv();
    read_stations_csv();
    read_pipes_csv();
}

void csv_reader::read_cities_csv() {
    ifstream file(this->cities_csv_file_name);
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string id, code, name, demand, population;
        getline(ss, name, ',');
        getline(ss, id, ',');
        getline(ss, code, ',');
        getline(ss, demand, ',');
        getline(ss, population, ',');
        City city(stoi(id), code, name, stod(demand), stoi(population));
        this->cities.insert({code, city});
    }
    file.close();
}

void csv_reader::read_stations_csv() {
    ifstream file(this->stations_csv_file_name);
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string id, code, name, capacity, cost;
        getline(ss, id, ',');
        getline(ss, code, ',');
        Pumping_station station(stoi(id), code);
        this->stations.insert({code, station});
    }
    file.close();
}

void csv_reader::read_reservoir_csv() {
    ifstream file(this->reservoir_csv_file_name);
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string  name, municipality, id, code, maximum_delivery;
        getline(ss, name, ',');
        getline(ss, municipality, ',');
        getline(ss, id, ',');
        getline(ss, code, ',');
        getline(ss, maximum_delivery, ',');
        Water_reservoir reservoir(stoi(id), code, name, municipality, stod(maximum_delivery));
        this->reservoirs.insert({code, reservoir});
    }
    file.close();
}

void csv_reader::read_pipes_csv() {
    ifstream file(this->pipes_csv_file_name);
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string service_point_a_code, service_point_b_code, capacity, direction;
        getline(ss, service_point_a_code, ',');
        getline(ss, service_point_b_code, ',');
        getline(ss, capacity, ',');
        getline(ss, direction, ',');
        bool is_unidirectional = (direction == "1");
        service_point_type service_point_type_a, service_point_type_b;
        switch (service_point_a_code[0]) {
            case 'C' : {
                service_point_type_a = CITY;
                break;
            }
            case 'P' : {
                service_point_type_a = PUMPING_STATION;
                break;
            }
            case 'R' : {
                service_point_type_a = WATER_RESERVOIR;
                break;
            }
        }
        switch (service_point_b_code[0]) {
            case 'C' : {
                service_point_type_b = CITY;
                break;
            }
            case 'P' : {
                service_point_type_b = PUMPING_STATION;
                break;
            }
            case 'R' : {
                service_point_type_b = WATER_RESERVOIR;
                break;
            }
        }
        service_point service_point_a, service_point_b;
        switch (service_point_type_a) {
            case CITY : {
                service_point_a.city = &this->cities.at(service_point_a_code);
                break;
            }
            case PUMPING_STATION : {
                service_point_a.pumping_station = &this->stations.at(service_point_a_code);
                break;
            }
            case WATER_RESERVOIR : {
                service_point_a.water_reservoir = &this->reservoirs.at(service_point_a_code);
                break;
            }
        }
        switch (service_point_type_b) {
            case CITY : {
                service_point_b.city = &this->cities.at(service_point_b_code);
                break;
            }
            case PUMPING_STATION : {
                service_point_b.pumping_station = &this->stations.at(service_point_b_code);
                break;
            }
            case WATER_RESERVOIR : {
                service_point_b.water_reservoir = &this->reservoirs.at(service_point_b_code);
                break;
            }
        }
        string pipe_code = service_point_a_code + "_to_" + service_point_b_code;
        Pipeline pipe(stoi(capacity), pipe_code, service_point_a, service_point_b, service_point_type_a, service_point_type_b);
        this->pipes.insert({pipe_code,pipe});
        // add the pipe to the service points
        // case where its unidirectional
        if (is_unidirectional) {
            switch (service_point_type_a) {
                case PUMPING_STATION : {
                    this->stations.at(service_point_a_code).addOutputPipeline(pipe_code);
                    break;
                }
                case WATER_RESERVOIR : {
                    this->reservoirs.at(service_point_a_code).addOutputPipeline(pipe_code);
                    break;
                }
            }
            switch (service_point_type_b) {
                case CITY : {
                    this->cities.at(service_point_b_code).addInputPipeline(pipe_code);
                    break;
                }
                case PUMPING_STATION : {
                    this->stations.at(service_point_b_code).addInputPipeline(pipe_code);
                    break;
                }
            }
        }
        // case where its bidirectional
        else {
            string reverse_pipe_code = service_point_b_code + "_to_" + service_point_a_code;
            Pipeline reverse_pipe = Pipeline(stoi(capacity), reverse_pipe_code, service_point_b, service_point_a, service_point_type_b, service_point_type_a);
            this->pipes.insert({reverse_pipe_code, reverse_pipe});
            switch (service_point_type_a) {
                case CITY : {
                    this->cities.at(service_point_a_code).addInputPipeline(reverse_pipe_code);
                    break;
                }
                case PUMPING_STATION : {
                    this->stations.at(service_point_a_code).addOutputPipeline(pipe_code);
                    this->stations.at(service_point_a_code).addInputPipeline(reverse_pipe_code);
                    break;
                }
                case WATER_RESERVOIR : {
                    this->reservoirs.at(service_point_a_code).addOutputPipeline(pipe_code);
                    break;
                }
            }
            switch (service_point_type_b) {
                case CITY : {
                    this->cities.at(service_point_b_code).addInputPipeline(pipe_code);
                    break;
                }
                case PUMPING_STATION : {
                    this->stations.at(service_point_b_code).addOutputPipeline(reverse_pipe_code);
                    this->stations.at(service_point_b_code).addInputPipeline(pipe_code);
                    break;
                }
                case WATER_RESERVOIR : {
                    this->reservoirs.at(service_point_b_code).addOutputPipeline(reverse_pipe_code);
                    break;
                }
            }
        }
    }
    file.close();
}

unordered_map<string, City> csv_reader::getCities() {
    return this->cities;
}

unordered_map<string, Pipeline> csv_reader::getPipes() {
    return this->pipes;
}

unordered_map<string, Water_reservoir> csv_reader::getReservoirs() {
    return this->reservoirs;
}

unordered_map<string, Pumping_station> csv_reader::getStations() {
    return this->stations;
}