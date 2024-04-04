//
// Created by rodri on 03/04/2024.
//

#ifndef PROJETO_DA_1_MENU_H
#define PROJETO_DA_1_MENU_H

#include "request.h"
#include <string>
#include <iostream>
#include <vector>

class menu {
private:
    request Request;
    bool go_back_to_main_menu;
    // functions common to all menus
    int print_menu_and_get_choice_input(std::string current_selection, std::vector<std::string> options,
                                        bool is_main_menu = false);
    int print_menu_and_get_number_input(std::string current_selection);
    std::string print_menu_and_get_string_input(std::string current_selection);
    void print_separator();
    int print_result_and_get_choice_input(std::string current_selection, std::vector<std::string> results);

    // main menu
    void main_menu();
    void basic_service_metrics();
    void reliability_and_sensitivity_to_failures();

    // basic_service_metrics
    void basic_service_metrics_maximum_of_water_that_can_reach();
        void basic_service_metrics_maximum_of_water_that_can_reach_all_cities();
        void basic_service_metrics_maximum_of_water_that_can_reach_a_specific_city();
            bool show_on_output_or_output_to_file_for_a_specific_city(std::string city_code);
    void basic_service_metrics_can_the_network_configuration_meet_the_water_needs_of_its_customers();
    void basic_service_metrics_balance_the_load();

    // reliability_and_sensitivity_to_failures
    void reliability_and_sensitivity_to_failures_select_water_reservoir_to_remove();
    void reliability_and_sensitivity_to_failures_select_pumping_station_to_remove();
    void reliability_and_sensitivity_to_failures_which_pumping_stations_can_be_removed_without_affecting_the_network();
    void reliability_and_sensitivity_to_failures_select_city();
        void reliability_and_sensitivity_to_failures_pipelines_make_impossible_to_deliver(std::string city_code);
        void reliability_and_sensitivity_to_failures_see_the_effect_of_removing_each_pipeline_of_the_city_to_the_entire_network(std::string city_code);
public:
    menu();
};


#endif //PROJETO_DA_1_MENU_H
