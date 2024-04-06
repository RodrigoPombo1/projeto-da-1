//
// Created by rodri on 03/04/2024.
//

#include "request.h"

using namespace std;

request::request() {
    this->csvReader = csv_reader();
    this->cities = this->csvReader.getCities();
    this->water_reservoirs = this->csvReader.getReservoirs();
    this->stations = this->csvReader.getStations();
    this->pipes = this->csvReader.getPipes();
}

// o algoritmo no fundo so vai ter o supersink o supersource as pipelines e as pumping stations
// tudo o q e interagir com cidades e reservatorios vai estar dentro do supersink e do supersource

double request::EdmondsKarp() {
    // criar o supersource e o supersink
    Supersource supersource = Supersource(&this->water_reservoirs, &this->pipes);
    Supersink supersink = Supersink(&this->cities, &this->pipes);
    string supersource_code = "supersource";
    string supersink_code = "supersink";

    // criar os reverse edges
    std::unordered_map<std::string, ReverseEdge> reverse_edges;
    for (auto &pipe : this->pipes) {
        reverse_edges.insert({pipe.first, ReverseEdge(&pipe.second)});
    }

    double flow = 0;

    while (true) {
        // criar queue para o bfs
        queue<string> q;
        for (auto &water_reservoir : supersource.getReservoirsCodes()) {
            q.push(water_reservoir);
        }
        // criar um estrutura para guardar os predecessores
        vector<string> predecessor;
        bool predecessor_has_sink = false;
        while (!q.empty() && !predecessor_has_sink) {
            string current_code = q.front();
            q.pop();

            // get the edges to iterate through
            std::vector<std::string> output_pipes;
            auto iterator = stations.find(current_code);
            // case where the edge is a station
            if (iterator != stations.end()) {
                for (auto iterator : iterator->second.getOutputPipelinesCodes()) {
                    // check if the pipe is active
                    if (!this->pipes.at(iterator).isActive()) {
                        continue;
                    }
                    output_pipes.push_back(iterator);
                }
            }
            // other case (where the edge is not a station and only works if its a water_reservoir)
            else {
                auto iterator = water_reservoirs.find(current_code);
                if (iterator != water_reservoirs.end()) {
                    for (auto iterator : iterator->second.getOutputPipelinesCodes()) {
                        // check if the pipe is active
                        if (!this->pipes.at(iterator).isActive()) {
                            continue;
                        }
                        output_pipes.push_back(iterator);
                    }
                }
            }

            // iterate through each output pipe
            for (auto &pipe_code : output_pipes) {
                // get the pipe pointer
                Pipeline *pipe = &this->pipes.at(pipe_code);

                // check if pipe is active
                if (!pipe->isActive()) {
                    continue;
                }

                // get the service point type B code
                service_point_type current_pipe_service_point_B_type = pipe->getServicePointTypeB();
                std::string code_of_current_pipe_service_point_B;
                switch (current_pipe_service_point_B_type) {
                    case CITY : {
                        code_of_current_pipe_service_point_B = pipe->getServicePointB().city->getCode();
                        // check city is active
                        if (!pipe->getServicePointB().city->isActive()) {
                            continue;
                        }
                        break;
                    }
                    case PUMPING_STATION : {
                        code_of_current_pipe_service_point_B = pipe->getServicePointB().pumping_station->getCode();
                        // check pumping station is active
                        if (!pipe->getServicePointB().pumping_station->isActive()) {
                            continue;
                        }
                        break;
                    }
                    case WATER_RESERVOIR : {
                        code_of_current_pipe_service_point_B = pipe->getServicePointB().water_reservoir->getCode();
                        // check water reservoir is active
                        if (!pipe->getServicePointB().water_reservoir->isActive()) {
                            continue;
                        }
                        break;
                    }
                }
                bool is_output_node_part_of_super_source = supersource.hasReservoir(code_of_current_pipe_service_point_B);
                bool is_current_pipe_part_of_predecessor = false;
                for (auto element : predecessor) {
                    if (element == code_of_current_pipe_service_point_B) {
                        is_current_pipe_part_of_predecessor = true;
                        break;
                    }
                }
                if (is_current_pipe_part_of_predecessor && is_output_node_part_of_super_source && (pipes.at(pipe_code).getCapacity() > pipes.at(pipe_code).getFlow())) {
                    predecessor.push_back(pipe_code);
                    q.push(pipe_code);
                }
            }
            for (auto &pipe_code : predecessor) {
                Pipeline *pipe = &this->pipes.at(pipe_code);
                if (pipe->isActive()) {
                    if (pipe->getServicePointTypeB() == CITY) {
                        if (supersink.hasCity(pipe->getServicePointB().city->getCode())) {
                            predecessor_has_sink = true;
                        }
                    }
                }
            }
        }

        // check if the last predecessor node is in the supersink
        bool there_is_edge_connecting_to_super_sink = false;
        string pipe_connecting_to_sink_code;
        for (auto &pipe_code : predecessor) {
            Pipeline *pipe = &this->pipes.at(pipe_code);
            if (pipe->isActive()) {
                if (pipe->getServicePointTypeB() == CITY) {
                    if (supersink.hasCity(pipe->getServicePointB().city->getCode())) {
                        there_is_edge_connecting_to_super_sink = true;
                        pipe_connecting_to_sink_code = pipe_code;
                    }
                }
            }
        }
        if (!there_is_edge_connecting_to_super_sink) {
            // augmenting path found
            // determining the amount of flow we can send
            double bottleneck = std::numeric_limits<double>::infinity();

            // put the last node visited in the path the sink node that the path leads to
            string current_edge_code = pipe_connecting_to_sink_code;
            while (!supersource.hasOutputEdge(current_edge_code)) {
                // find edge that connects to the current edge
                string predecessor_edge_code;
                for (auto element : predecessor) {
                    if (pipes.at(element).getServicePointB() == pipes.at(current_edge_code).getServicePointA()) {
                        predecessor_edge_code = element;
                        break;
                    }
                }
                double residual_capacity;
                Pipeline *pipe = &this->pipes.at(predecessor_edge_code);
                residual_capacity = pipe->getResidualCapacity();
                if (residual_capacity < bottleneck) {
                    bottleneck = residual_capacity;
                }
                current_edge_code = predecessor_edge_code;
            }
            // put last node visited in the path the sink node that the path leads to
            current_edge_code = pipe_connecting_to_sink_code;
            while (!supersource.hasOutputEdge(current_edge_code)) {
                string predecessor_edge_code;
                for (auto element : predecessor) {
                    if (pipes.at(element).getServicePointB() == pipes.at(current_edge_code).getServicePointA()) {
                        predecessor_edge_code = element;
                        break;
                    }
                }
                Pipeline *pipe = &this->pipes.at(predecessor_edge_code);
                pipe->setFlow(pipe->getFlow() + bottleneck);
                reverse_edges.at(predecessor_edge_code).setFlow(reverse_edges.at(predecessor_edge_code).getFlow() - bottleneck);
                current_edge_code = predecessor_edge_code;
            }
            flow += bottleneck;
        }
        else {
            break;
        }
    }
    return flow;
}

void request::setCityInactive(string city_code) {
    this->cities.at(city_code).setActive(false);
    for (auto &pipe_code : this->cities.at(city_code).getInputPipelinesCodes()) {
        this->pipes.at(pipe_code).setActive(false);
    }
}

void request::setWaterReservoirInactive(string water_reservoir_code) {
    this->water_reservoirs.at(water_reservoir_code).setActive(false);
    for (auto &pipe_code : this->water_reservoirs.at(water_reservoir_code).getOutputPipelinesCodes()) {
        this->pipes.at(pipe_code).setActive(false);
    }
}

void request::setPumpingStationInactive(string pumping_station_code) {
    this->stations.at(pumping_station_code).setActive(false);
    for (auto &pipe_code : this->stations.at(pumping_station_code).getInputPipelinesCodes()) {
        this->pipes.at(pipe_code).setActive(false);
    }
    for (auto &pipe_code : this->stations.at(pumping_station_code).getOutputPipelinesCodes()) {
        this->pipes.at(pipe_code).setActive(false);
    }
}

void request::setPipelineInactive(string pipeline_code) {
    Pipeline *pipeline_pointer = &this->pipes.at(pipeline_code);
    pipeline_pointer->setActive(false);
}

void request::setAllActive() {
    for (auto &city : this->cities) {
        city.second.setActive(true);
    }
    for (auto &water_reservoir : this->water_reservoirs) {
        water_reservoir.second.setActive(true);
    }
    for (auto &station : this->stations) {
        station.second.setActive(true);
    }
    for (auto &pipe : this->pipes) {
        pipe.second.setActive(true);
    }
}