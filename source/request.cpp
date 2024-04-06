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
    Supersource supersource(&this->water_reservoirs, &this->pipes);
    Supersink supersink(&this->cities, &this->pipes);
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
        q.push(supersource_code);
        // criar um estrutura para guardar os predecessores
        std::unordered_set<string> predecessor;
        while (!q.empty() && predecessor.find(supersink_code) == predecessor.end()) {
            string current_code = q.front();
            q.pop();

            // get the edges to iterate
            std::vector<std::string> output_pipes;
            if (current_code == supersource_code) {
                for (auto iterator : supersource.getSuperSourceOutputPipelinesCodesMapToPointers()) {
                    output_pipes.push_back(iterator.first);
                }
            }
            else {
                auto iterator = cities.find(current_code);
                if (iterator != cities.end()) {
                    output_pipes = vector<string>();
                }
                else {
                    auto iterator = stations.find(current_code);
                    if (iterator != stations.end()) {
                        for (auto iterator : iterator->second.getOutputPipelinesCodes()) {
                            output_pipes.push_back(iterator);
                        }
                    }
                    else {
                        auto iterator = water_reservoirs.find(current_code);
                        if (iterator != water_reservoirs.end()) {
                            for (auto iterator : iterator->second.getOutputPipelinesCodes()) {
                                output_pipes.push_back(iterator);
                            }
                        }
                    }
                }
            }

            for (auto &pipe_code : output_pipes) {
                // get the pipe pointer
                Pipeline *pipe = &this->pipes.at(pipe_code);

                // get the service point type B code
                service_point_type current_pipe_service_point_B_type = pipe->getServicePointTypeB();
                std::string code_of_current_pipe_service_point_B;
                switch (current_pipe_service_point_B_type) {
                    case CITY : {
                        code_of_current_pipe_service_point_B = pipe->getServicePointB().city->getCode();
                        break;
                    }
                    case PUMPING_STATION : {
                        code_of_current_pipe_service_point_B = pipe->getServicePointB().pumping_station->getCode();
                        break;
                    }
                    case WATER_RESERVOIR : {
                        code_of_current_pipe_service_point_B = pipe->getServicePointB().water_reservoir->getCode();
                        break;
                    }
                }
                if ((predecessor.find(code_of_current_pipe_service_point_B) == predecessor.end()) && (code_of_current_pipe_service_point_B != supersource_code) && (reverse_edges.at(pipe_code).getCapacity() > reverse_edges.at(pipe_code).getFlow())) {
                    predecessor.insert(code_of_current_pipe_service_point_B);
                    q.push(code_of_current_pipe_service_point_B);
                }
            }
        }

        if (!(predecessor.find(supersink_code) == predecessor.end())) {
            // augmenting path found
            // determining the amount of flow we can send
            double bottleneck = std::numeric_limits<double>::infinity();
            string current_code = supersink_code;
            while (current_code != supersource_code) {
                string predecessor_code = *predecessor.find(current_code);
                Pipeline *pipe = &this->pipes.at(predecessor_code + "_to_" + current_code);
                double residual_capacity = pipe->getResidualCapacity();
                if (residual_capacity < bottleneck) {
                    bottleneck = residual_capacity;
                }
                current_code = predecessor_code;
            }
            current_code = supersink_code;
            while (current_code != supersource_code) {
                string predecessor_code = *predecessor.find(current_code);
                Pipeline *pipe = &this->pipes.at(predecessor_code + "_to_" + current_code);
                pipe->setFlow(pipe->getFlow() + bottleneck);
                reverse_edges.at(predecessor_code + "_to_" + current_code).setFlow(reverse_edges.at(predecessor_code + "_to_" + current_code).getFlow() - bottleneck);
                current_code = predecessor_code;
            }
            flow += bottleneck;
        }
        else {
            break;
        }
    }
    return flow;
}