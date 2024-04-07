//
// Created by rodri on 03/04/2024.
//

#include <iostream>
#include "request.h"

using namespace std;

request::request() {
    this->csvReader = csv_reader();
    this->cities = this->csvReader.getCities();
    this->water_reservoirs = this->csvReader.getReservoirs();
    this->stations = this->csvReader.getStations();
    this->pipes = this->csvReader.getPipes();

//    // for test TODO: remove
//    cout << EdmondsKarp() << "\n";
//    cout << cities.at("C_1").getReceivingFlow() << "\n";
//    cout << cities.at("C_2").getReceivingFlow() << "\n";
//    cout << cities.at("C_3").getReceivingFlow() << "\n";
//    cout << cities.at("C_4").getReceivingFlow() << "\n";
//    cout << cities.at("C_5").getReceivingFlow() << "\n";
//    cout << cities.at("C_6").getReceivingFlow() << "\n";
//    cout << cities.at("C_7").getReceivingFlow() << "\n";
//    cout << cities.at("C_8").getReceivingFlow() << "\n";
//    cout << cities.at("C_9").getReceivingFlow() << "\n";
//    cout << cities.at("C_10").getReceivingFlow() << "\n";
}

// o algoritmo no fundo so vai ter o supersink o supersource as pipelines e as pumping stations
// tudo o q e interagir com cidades e reservatorios vai estar dentro do supersink e do supersource

double request::EdmondsKarp() {
    resetFlowForEachCity();
    resetFlowForEachWaterReservoir();
    resetFlowForEachPipeline();

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
        ////////////////
        // BFS
        ////////////////

        // criar queue para o bfs
        queue<string> q;
        auto water_reservoirs_from_supersource = supersource.getReservoirsCodes();
        unordered_map<string, string> predecessor;
        for (auto iterator : water_reservoirs_from_supersource) {
            if (this->water_reservoirs.at(iterator).getOutputFlow() < this->water_reservoirs.at(iterator).getMaximumDelivery()) {
                q.push(iterator);
            }
        }
        // criar um estrutura para guardar os predecessores
        bool predecessor_has_node_of_supersink = false;
        while (!q.empty() && !predecessor_has_node_of_supersink) {
            string current_node_code = q.front();
            q.pop();

            //////////// checking regular output pipes

            // get the edges to iterate through
            std::vector<std::string> output_pipes;

            // nunca pode ser uma cidade as nodes na queue
            if (this->water_reservoirs.find(current_node_code) != this->water_reservoirs.end()) {
                for (auto iterator : this->water_reservoirs.at(current_node_code).getOutputPipelinesCodes()) {
                    // check if the pipe is active
                    if (!this->pipes.at(iterator).isActive()) {
                        continue;
                    }
                    output_pipes.push_back(iterator);
                }
            }
            else {
                for (auto iterator : this->stations.at(current_node_code).getOutputPipelinesCodes()) {
                    // check if the pipe is active
                    if (!this->pipes.at(iterator).isActive()) {
                        continue;
                    }
                    output_pipes.push_back(iterator);
                }
            }

            // iterate through each output pipe of the current node
            for (auto pipe_code : output_pipes) {
                // get the pipe pointer
                Pipeline *pipe = &this->pipes.at(pipe_code);

                // check if pipe is active
                if (!pipe->isActive()) {
                    continue;
                }

                // get the service point B code
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
                    case WATER_RESERVOIR : { // tecnicamente nunca pode ser este caso
                        code_of_current_pipe_service_point_B = pipe->getServicePointB().water_reservoir->getCode();
                        // check water reservoir is active
                        if (!pipe->getServicePointB().water_reservoir->isActive()) {
                            continue;
                        }
                        break;
                    }
                }
                bool is_output_pipe_service_point_B_part_of_super_source = supersource.hasReservoir(code_of_current_pipe_service_point_B);  // isto tecnicamente vai dar sempre falso pq n ha input pipes nos reservatorios e por isso tambem n ha output de outras nodes a levar para la
                bool is_current_pipe_service_point_B_part_of_predecessor = false;
                for (auto node_in_predecessor : predecessor) {
                    if (node_in_predecessor.first == code_of_current_pipe_service_point_B) {
                        is_current_pipe_service_point_B_part_of_predecessor = true;
                        break;
                    }
                }
                bool is_output_pipe_to_city_with_no_more_demand = false;
                if (current_pipe_service_point_B_type == CITY) {
                    if (cities.at(code_of_current_pipe_service_point_B).getDemand() - cities.at(code_of_current_pipe_service_point_B).getReceivingFlow() == 0) {
                        is_output_pipe_to_city_with_no_more_demand = true;
                    }
                }
                if ((!is_current_pipe_service_point_B_part_of_predecessor) && !(is_output_pipe_service_point_B_part_of_super_source) && !is_output_pipe_to_city_with_no_more_demand && (pipes.at(pipe_code).getCapacity() > pipes.at(pipe_code).getFlow())) {
                    predecessor.insert({code_of_current_pipe_service_point_B, pipe_code});
                    q.push(code_of_current_pipe_service_point_B);
                }
            }

            ////////////// condição para a paragem da loop do bfs inteiro
            for (auto element : predecessor) {
                if (supersink.hasCity(element.first)) {
                    predecessor_has_node_of_supersink = true;
                    break;
                }
            }
        }

        /////////////////////////////////////////
        // Dealing with found augmenting path
        /////////////////////////////////////////

        // check if a predecessor pipe leads to the supersink
        bool there_is_node_in_predecessor_part_of_supersink = false;
        string code_of_node_part_of_supersink_that_was_found;
        for (auto element_pair : predecessor) {
            if (supersink.hasCity(element_pair.first)) {
                code_of_node_part_of_supersink_that_was_found = element_pair.first;
                there_is_node_in_predecessor_part_of_supersink = true;
            }
        }
        if (there_is_node_in_predecessor_part_of_supersink) {
            // augmenting path found
            // determining the amount of flow we can send
            double bottleneck = std::numeric_limits<double>::infinity();

            string current_node_code = code_of_node_part_of_supersink_that_was_found;
            while (!supersource.hasReservoir(current_node_code)) {
                string code_of_edge_that_led_to_current_node = predecessor.at(current_node_code);
                Pipeline *pipe = &this->pipes.at(code_of_edge_that_led_to_current_node);
                double residual_capacity = pipe->getResidualCapacity();
                if (residual_capacity < bottleneck) {
                    bottleneck = residual_capacity;
                }
                switch (pipe->getServicePointTypeA()) {
                    case CITY : {
                        current_node_code = pipe->getServicePointA().city->getCode();
                        break;
                    }
                    case PUMPING_STATION : {
                        current_node_code = pipe->getServicePointA().pumping_station->getCode();
                        break;
                    }
                    case WATER_RESERVOIR : {
                        current_node_code = pipe->getServicePointA().water_reservoir->getCode();
                        break;
                    }
                }
            }

            // check if the source can send this much flow
            double maximum_remaining_delivery = water_reservoirs.at(current_node_code).getMaximumDelivery() - water_reservoirs.at(current_node_code).getOutputFlow();
            if (maximum_remaining_delivery < 0) {
                throw invalid_argument("Maximum delivery cannot be less than 0");
            }
            if (maximum_remaining_delivery < bottleneck) {
                bottleneck = maximum_remaining_delivery;
            }

            // check if the sink can receive this much flow
            double maximum_remaining_demand = cities.at(code_of_node_part_of_supersink_that_was_found).getDemand() - cities.at(code_of_node_part_of_supersink_that_was_found).getReceivingFlow();
            if (maximum_remaining_demand < 0) {
                throw invalid_argument("Maximum demand cannot be less than 0");
            }
            if (maximum_remaining_demand < bottleneck) {
                bottleneck = maximum_remaining_demand;
            }

            // a bottleneck nunca deveria ser 0 pq verificamos antes de escolher a augmenting path a ver se aquele e valido ou n tipo se ainda tem capacidade ou n os dois
            if (bottleneck > 0) { // ignore augmenting path as we can't send any flow
//                 put last node visited in the path the sink node that the path leads to
                current_node_code = code_of_node_part_of_supersink_that_was_found;
                while (!supersource.hasReservoir(current_node_code)) {
                    string code_of_edge_that_led_to_current_node = predecessor.at(current_node_code);
                    Pipeline *pipe = &this->pipes.at(code_of_edge_that_led_to_current_node);
                    pipe->setFlow(pipe->getFlow() + bottleneck);
                    reverse_edges.at(code_of_edge_that_led_to_current_node).setFlow(
                            reverse_edges.at(code_of_edge_that_led_to_current_node).getFlow() - bottleneck);
                    switch (pipe->getServicePointTypeA()) {
                        case CITY : {
                            current_node_code = pipe->getServicePointA().city->getCode();
                            break;
                        }
                        case PUMPING_STATION : {
                            current_node_code = pipe->getServicePointA().pumping_station->getCode();
                            break;
                        }
                        case WATER_RESERVOIR : {
                            current_node_code = pipe->getServicePointA().water_reservoir->getCode();
                            break;
                        }
                    }
                }
                flow += bottleneck;
                updateFlowForEachCity();
                updateFlowForEachWaterReservoir();
            }
        }
        else {
            break;
        }
    }
//    updateFlowForEachCity();
//    updateFlowForEachWaterReservoir();
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

void request::updateFlowForEachCity() {
    for (auto &city : this->cities) {
        vector<string> pipes_codes = city.second.getInputPipelinesCodes();
        double receiving_flow = 0;
        for (auto &pipe_code : pipes_codes) {
            receiving_flow += this->pipes.at(pipe_code).getFlow();
        }
        city.second.setReceivingFlow(receiving_flow);
    }
}

void request::updateFlowForEachWaterReservoir() {
    for (auto &water_reservoir : this->water_reservoirs) {
        vector<string> pipes_codes = water_reservoir.second.getOutputPipelinesCodes();
        double output_flow = 0;
        for (auto &pipe_code : pipes_codes) {
            output_flow += this->pipes.at(pipe_code).getFlow();
        }
        water_reservoir.second.setOutputFlow(output_flow);
    }
}

void request::resetFlowForEachCity() {
    for (auto &city : this->cities) {
        city.second.setReceivingFlow(0);
    }
}

void request::resetFlowForEachWaterReservoir() {
    for (auto &water_reservoir : this->water_reservoirs) {
        water_reservoir.second.setOutputFlow(0);
    }
}

void request::resetFlowForEachPipeline() {
    for (auto &pipe : this->pipes) {
        pipe.second.setFlow(0);
    }
}

std::vector<std::string> request::get_maximum_amount_of_water_all_and_each_city() {
    setAllActive();
    resetFlowForEachCity();
    resetFlowForEachWaterReservoir();
    resetFlowForEachPipeline();
    double flow = EdmondsKarp();
    vector<string> result;
    result.push_back("Total flow of the network: " + to_string(flow));
    for (auto &city : this->cities) {
        result.push_back("City " + city.first + " received " + to_string(city.second.getReceivingFlow()) + " of water");
    }
    return result;
}

bool request::check_city_exists(string city_code) {
    return this->cities.find(city_code) != this->cities.end();
}

std::string request::get_maximum_amount_of_water_for_a_specific_city(string city_code) {
    setAllActive();
    resetFlowForEachCity();
    resetFlowForEachWaterReservoir();
    resetFlowForEachPipeline();
    double flow = EdmondsKarp();
    return to_string(this->cities.at(city_code).getReceivingFlow());
}

std ::vector<std::string> request::can_all_cities_be_supplied() {
    setAllActive();
    resetFlowForEachCity();
    resetFlowForEachWaterReservoir();
    resetFlowForEachPipeline();
    double flow = EdmondsKarp();
    vector<string> result;
    for (auto &city : this->cities) {
        if (city.second.getReceivingFlow() < city.second.getDemand()) {
            result.push_back("City " + city.first + " cannot be supplied: Receiving Flow is " + to_string(city.second.getReceivingFlow()) + " and Demand is " + to_string(city.second.getDemand()));
        }
    }
    if (result.empty()) {
        result.push_back("All cities can be supplied");
    }
    return result;
}

bool request::check_water_reservoir_exists(string water_reservoir_code) {
    return this->water_reservoirs.find(water_reservoir_code) != this->water_reservoirs.end();
}

std::vector<std::string> request::get_maximum_amount_of_water_all_and_each_city_that_cannot_be_supplied_but_deactivate_reservoir(
        std::string reservoir_code) {
    setAllActive();
    setWaterReservoirInactive(reservoir_code);
    resetFlowForEachCity();
    resetFlowForEachWaterReservoir();
    resetFlowForEachPipeline();
    double flow = EdmondsKarp();
    vector<string> result;
    for (auto &city : this->cities) {
        if (city.second.getReceivingFlow() < city.second.getDemand()) {
            result.push_back("City " + city.first + " cannot be supplied: Receiving Flow is " + to_string(city.second.getReceivingFlow()) + " and Demand is " + to_string(city.second.getDemand()));
        }
    }
    if (result.empty()) {
        result.push_back("All cities can be supplied");
    }
    setAllActive();
    return result;
}

bool request::check_pumping_station_exists(string pumping_station_code) {
    return this->stations.find(pumping_station_code) != this->stations.end();
}

std::vector<std::string> request::get_maximum_amount_of_water_all_and_each_city_that_cannot_be_supplied_but_deactivate_station(
        std::string station_code) {
    setAllActive();
    setPumpingStationInactive(station_code);
    resetFlowForEachCity();
    resetFlowForEachWaterReservoir();
    resetFlowForEachPipeline();
    double flow = EdmondsKarp();
    vector<string> result;
    for (auto &city : this->cities) {
        if (city.second.getReceivingFlow() < city.second.getDemand()) {
            result.push_back("City " + city.first + " cannot be supplied: Receiving Flow is " + to_string(city.second.getReceivingFlow()) + " and Demand is " + to_string(city.second.getDemand()));
        }
    }
    if (result.empty()) {
        result.push_back("All cities can be supplied");
    }
    setAllActive();
    resetFlowForEachCity();
    resetFlowForEachWaterReservoir();
    resetFlowForEachPipeline();
    return result;
}

vector<string> request::go_through_each_pumping_station_and_check_what_city_in_deficit_when_they_are_removed() {
    vector<string> result;
    for (auto &station : this->stations) {
        result.push_back("Removing pumping station " + station.first + " from the network");
        setAllActive();
        setPumpingStationInactive(station.first);
        resetFlowForEachCity();
        resetFlowForEachWaterReservoir();
        resetFlowForEachPipeline();
        double flow = EdmondsKarp();
        for (auto &city : this->cities) {
            if (city.second.getReceivingFlow() < city.second.getDemand()) {
                result.push_back("City " + city.first + " cannot be supplied: Receiving Flow is " + to_string(city.second.getReceivingFlow()) + " and Demand is " + to_string(city.second.getDemand()));
            }
        }
        if (result.empty()) {
            result.push_back("All cities can be supplied");
        }
    }
    setAllActive();
    resetFlowForEachCity();
    resetFlowForEachWaterReservoir();
    resetFlowForEachPipeline();
    return result;
}

vector<string> request::iterate_over_each_pipe_in_specific_city_and_check_if_removing_them_the_city_flow_would_be_in_deficit(string city_code) {
    vector<string> result;
    for (auto &pipe_code : this->cities.at(city_code).getInputPipelinesCodes()) {
        result.push_back("Removing pipe " + pipe_code + " from the network");
        setAllActive();
        setPipelineInactive(pipe_code);
        resetFlowForEachCity();
        resetFlowForEachWaterReservoir();
        resetFlowForEachPipeline();
        double flow = EdmondsKarp();
        if (this->cities.at(city_code).getReceivingFlow() < this->cities.at(city_code).getDemand()) {
            result.push_back("City " + city_code + " cannot be supplied: Receiving Flow is " + to_string(this->cities.at(city_code).getReceivingFlow()) + " and Demand is " + to_string(this->cities.at(city_code).getDemand()));
        }
        else {
            result.push_back("City " + city_code + " can be supplied: Receiving Flow is " + to_string(this->cities.at(city_code).getReceivingFlow()) + " and Demand is " + to_string(this->cities.at(city_code).getDemand()));
        }
    }
    setAllActive();
    resetFlowForEachCity();
    resetFlowForEachWaterReservoir();
    resetFlowForEachPipeline();
    return result;
}

vector<string> request::iterate_over_each_pipe_in_specific_city_and_check_if_removing_them_the_network_flow_would_be_in_deficit(string city_code) {
    vector<string> result;
    for (auto &pipe_code : this->cities.at(city_code).getInputPipelinesCodes()) {
        setAllActive();
        setPipelineInactive(pipe_code);
        resetFlowForEachCity();
        resetFlowForEachWaterReservoir();
        resetFlowForEachPipeline();
        double flow = EdmondsKarp();
        vector<string> deficit;
        for (auto &city : this->cities) {
            if (city.second.getReceivingFlow() < city.second.getDemand()) {
                deficit.push_back("City " + city.first + " cannot be supplied: Receiving Flow is " + to_string(this->cities.at(city.first).getReceivingFlow()) + " and Demand is " + to_string(this->cities.at(city.first).getDemand()));
            }
        }
        if (!deficit.empty()) {
            result.push_back("Removing pipe " + pipe_code + " from the network would cause a deficit in the network:");
            result.insert(result.end(), deficit.begin(), deficit.end());
        }
        else {
            result.push_back("Removing pipe " + pipe_code + " from the network would not cause a deficit in the network");
        }
    }
    setAllActive();
    resetFlowForEachCity();
    resetFlowForEachWaterReservoir();
    resetFlowForEachPipeline();
    return result;
}