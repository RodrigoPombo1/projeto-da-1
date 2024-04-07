#include "menu.h"

using namespace std;

/// @brief Prints current menu and gets the input corresponding to the choice from the options
/// @param current_selection current menu selected
/// @param options vector with the diferent options in the menu
/// @param is_main_menu boolean value corresponding to being the main menu or not
/// @return choice made
int menu::print_menu_and_get_choice_input(string current_selection, vector<string> options, bool is_main_menu) {
    int input;
    bool valid_input = false;
    while (!valid_input) {
        cout << current_selection << endl;

        this->print_separator();

        for (int i = 0; i < options.size(); i++) {
            cout << i + 1 << ". " << options[i] << endl;
        }
        if (!is_main_menu) {
            cout << "0. Go back to previous menu\n";
            cout << "-1. Go back to main menu\n";
        } else {
            cout << "0. Exit\n";
        }
        this->print_separator();

        cout << "Chose one of the options above by entering the corresponding number and press enter\n";
        cin >> input;
        if (input >= -1 && input <= (int) options.size() && !is_main_menu) {
            valid_input = true;
        } else if (input >= 0 && input <= (int) options.size() && is_main_menu) {
            valid_input = true;
        } else {
            cout << "Invalid input, please try again\n";
        }
    }
    return input;
}

/// @brief Prints a separator
void menu::print_separator() {
    cout << "---------------------------------------------------------------------------\n";
}

/// @brief Prints current menu and gets number input
/// @param current_selection current menu selected
/// @return number input chosen
int menu::print_menu_and_get_number_input(string current_selection) {
    int input;
    bool valid_input = false;
    while (!valid_input) {
        cout << current_selection << endl;

        this->print_separator();

        cout << "Enter a number above 1" << " and press enter\n";

        this->print_separator();

        cout << "0. Go back to previous menu\n";
        cout << "-1. Go back to main menu\n";

        this->print_separator();

        cout << "Chose one of the options above by entering the corresponding number and press enter\n";
        cin >> input;
        if (input >= -1) {
            valid_input = true;
        } else {
            cout << "Invalid input, please try again\n";
        }
    }
    return input;
}

/// @brief Prints current menu and gets string input
/// @param current_selection current menu selected
/// @return string input chosen
string menu::print_menu_and_get_string_input(string current_selection) {
    string input;
    bool valid_input = false;
    while (!valid_input) {
        cout << current_selection << endl;

        this->print_separator();

        cout << "Enter a string and press enter\n";

        this->print_separator();

        cout << "0. Go back to previous menu\n";
        cout << "-1. Go back to main menu\n";

        this->print_separator();

        cout << "Chose one of the options above by entering a string or the corresponding number and press enter\n";
        cin >> input;
        if (input != "") {
            valid_input = true;
        } else {
            cout << "Invalid input, please try again\n";
        }
    }
    return input;
}

/// @brief Prints results from the request and gets choice input
/// @param current_selection current menu selected
/// @param results vector with the results from the request made
/// @return input chosen
int menu::print_result_and_get_choice_input(std::string current_selection, std::vector<std::string> results) {
    int input;
    bool valid_input = false;
    while (!valid_input) {
        cout << current_selection << endl;

        this->print_separator();

        for (int i = 0; i < results.size(); i++) {
            cout << i + 1 << ". " << results[i] << endl;
        }

        this->print_separator();

        cout << "0. Go back to previous menu\n";
        cout << "-1. Go back to main menu\n";

        this->print_separator();

        cout << "Chose one of the options above by entering the corresponding number and press enter\n";
        cin >> input;
        if (input >= -1 && input <= 0) {
            valid_input = true;
        } else {
            cout << "Invalid input, please try again\n";
        }
    }
    return input;
}

/// @brief Initializes the menu
menu::menu() {
    this->main_menu();
}

/// @brief Prints the main menu
void menu::main_menu() {
    while (true) {
        this->go_back_to_main_menu = false;
        string current_menu = "Main menu";
        vector<string> options = {"Basic service metrics", "Reliability and sensitivity to failures"};
        int input = this->print_menu_and_get_choice_input(current_menu, options, true);
        switch (input) {
            case 0:
                return;
            case 1:
                this->basic_service_metrics();
                break;
            case 2:
                this->reliability_and_sensitivity_to_failures();
                break;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

/// @brief Prints options for the basic service metrics menu
void menu::basic_service_metrics() {
    while (!this->go_back_to_main_menu) {
        this->go_back_to_main_menu = false;
        string current_menu = "Basic service metrics";
        vector<string> options = {"Maximum of water that can reach cities", "Can the network configuration meet the water needs of its customers",
                                  "Balance the load"};
        int input = this->print_menu_and_get_choice_input(current_menu, options);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            case 1:
                this->basic_service_metrics_maximum_of_water_that_can_reach();
                break;
            case 2:
                this->basic_service_metrics_can_the_network_configuration_meet_the_water_needs_of_its_customers();
                break;
            case 3:
                this->basic_service_metrics_balance_the_load();
                break;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

/// @brief Prints options for the maximum of water that can reach cities menu
void menu::basic_service_metrics_maximum_of_water_that_can_reach() {
    while (!this->go_back_to_main_menu) {
        this->go_back_to_main_menu = false;
        string current_menu = "Maximum of water that can reach";
        vector<string> options = {"All cities", "A specific city"};
        int input = this->print_menu_and_get_choice_input(current_menu, options);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            case 1:
                this->basic_service_metrics_maximum_of_water_that_can_reach_all_cities();
                break;
            case 2:
                this->basic_service_metrics_maximum_of_water_that_can_reach_a_specific_city();
                break;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

/// @brief Gets the maximum of water that can reach all cities
void menu::basic_service_metrics_maximum_of_water_that_can_reach_all_cities() {
    while (!this->go_back_to_main_menu) {
        this->go_back_to_main_menu = false;
        string current_menu = "Maximum of water that can reach all cities";
        vector<string> options = {"Show on output", "Output to file"};
        int input = this->print_menu_and_get_choice_input(current_menu, options);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            case 1:
                print_result_and_get_choice_input("Maximum of water that can reach all cities", Request.get_maximum_amount_of_water_all_and_each_city());
                break;
            case 2:
                // TODO (actual result and then output it in a file)
                break;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

/// @brief Gets the maximum of water that can reach a specific city
void menu::basic_service_metrics_maximum_of_water_that_can_reach_a_specific_city() {
    while (!this->go_back_to_main_menu) {
        this->go_back_to_main_menu = false;
        string current_menu = "Maximum of water that can reach a specific city - enter city code";
        string input = this->print_menu_and_get_string_input(current_menu);
        if (input == "0") {
            return;
        } else if (input == "-1") {
            this->go_back_to_main_menu = true;
            return;
        } else {
            bool is_input_valid = Request.check_city_exists(input);
            if (!is_input_valid) {
                cout << "City with code " << input << " does not exist\n";
            } else {
                show_on_output_or_output_to_file_for_a_specific_city(input);
            }
        }
    }
}

/// @brief Shows the maximum of water that can reach a specific city on output or output to file (not implemented)
/// @param city_code code of the city
/// @return true if it wants to show an output or false to output to file for a specific city
bool menu::show_on_output_or_output_to_file_for_a_specific_city(string city_code) {
    while (!this->go_back_to_main_menu) {
        this->go_back_to_main_menu = false;
        string current_menu = "Show on output or output to file for city with code " + city_code;
        vector<string> options = {"Show on output", "Output to file"};
        int input = this->print_menu_and_get_choice_input(current_menu, options);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return false;
            case 0:
                return false;
            case 1:
                print_result_and_get_choice_input("Maximum of water that can reach city with code " + city_code, {Request.get_maximum_amount_of_water_for_a_specific_city(city_code)});
                break;
            case 2:
                // TODO (actual result and then output it in a file)
                break;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

/// @brief Gets all the cities that can be supplied
void menu::basic_service_metrics_can_the_network_configuration_meet_the_water_needs_of_its_customers() {
    while (!this->go_back_to_main_menu) {
        this->go_back_to_main_menu = false;
        string current_menu = "Can the network configuration meet the water needs of its customers";
        vector<string> result = Request.can_all_cities_be_supplied();
        // TODO compute result
        int input = this->print_result_and_get_choice_input(current_menu, result);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

/// @brief Prints options for the balance the load menu
void menu::basic_service_metrics_balance_the_load() {
    while (!this->go_back_to_main_menu) {
        this->go_back_to_main_menu = false;
        string current_menu = "Balance the load";
        vector<string> result; // TODO
        // TODO compute result
        int input = this->print_result_and_get_choice_input(current_menu, result);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

/// @brief Prints options for the reliability and sensitivity to failures menu
void menu::reliability_and_sensitivity_to_failures() {
    while (!this->go_back_to_main_menu) {
        this->go_back_to_main_menu = false;
        string current_menu = "Reliability and sensitivity to failures";
        vector<string> options = {"Select water reservoir to remove", "Select pumping station to remove",
                                  "Which pumping stations can be removed without affecting the network", "Select city"};
        int input = this->print_menu_and_get_choice_input(current_menu, options);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            case 1:
                this->reliability_and_sensitivity_to_failures_select_water_reservoir_to_remove();
                break;
            case 2:
                this->reliability_and_sensitivity_to_failures_select_pumping_station_to_remove();
                break;
            case 3:
                this->reliability_and_sensitivity_to_failures_which_pumping_stations_can_be_removed_without_affecting_the_network();
                break;
            case 4:
                this->reliability_and_sensitivity_to_failures_select_city();
                break;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

/// @brief Gets all cities and each city that get the maximum amount of water that can be supplied after deactivating a specific water reservoir
void menu::reliability_and_sensitivity_to_failures_select_water_reservoir_to_remove() {
    while (!this->go_back_to_main_menu) {
        this->go_back_to_main_menu = false;
        string current_menu = "Select water reservoir to remove";
        string input = this->print_menu_and_get_string_input(current_menu);
        if (input == "0") {
            return;
        } else if (input == "-1") {
            this->go_back_to_main_menu = true;
            return;
        } else {
            bool is_input_valid = Request.check_water_reservoir_exists(input);
            if (!is_input_valid) {
                cout << "Water reservoir with code " << input << " does not exist\n";
            } else {
                vector<string> result = Request.get_maximum_amount_of_water_all_and_each_city_that_cannot_be_supplied_but_deactivate_reservoir(input);
                int input2 = print_result_and_get_choice_input("Removed water reservoir: " + input, result);
                switch (input2) {
                    case -1:
                        this->go_back_to_main_menu = true;
                        return;
                    case 0:
                        return;
                    default:
                        cout << "Invalid input, please try again\n";
                        break;
                }
            }
        }
    }
}

/// @brief Gets all cities and each city that get the maximum amount of water that can be supplied after deactivating a specific pumping station
void menu::reliability_and_sensitivity_to_failures_select_pumping_station_to_remove() {
    while (!this->go_back_to_main_menu) {
        this->go_back_to_main_menu = false;
        string current_menu = "Select pumping station to remove";
        string input = this->print_menu_and_get_string_input(current_menu);
        if (input == "0") {
            return;
        } else if (input == "-1") {
            this->go_back_to_main_menu = true;
            return;
        } else {
            bool is_input_valid = Request.check_pumping_station_exists(input);
            if (!is_input_valid) {
                cout << "Pumping station with code " << input << " does not exist\n";
            } else {
                vector<string> result = Request.get_maximum_amount_of_water_all_and_each_city_that_cannot_be_supplied_but_deactivate_station(input);
                int input2 = print_result_and_get_choice_input("Removed pumping station: " + input, result);
                switch (input2) {
                    case -1:
                        this->go_back_to_main_menu = true;
                        return;
                    case 0:
                        return;
                    default:
                        cout << "Invalid input, please try again\n";
                        break;
                }
            }
        }
    }
}

/// @brief Gets the cities in deficit when each pumping station is removed
void menu::reliability_and_sensitivity_to_failures_which_pumping_stations_can_be_removed_without_affecting_the_network() {
    while (!this->go_back_to_main_menu) {
        this->go_back_to_main_menu = false;
        string current_menu = "Which pumping stations can be removed without affecting the network";
        vector<string> result = Request.go_through_each_pumping_station_and_check_what_city_in_deficit_when_they_are_removed();
        int input = this->print_result_and_get_choice_input(current_menu, result);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

/// @brief Prints options for the select city menu of the reliability and sensitivity to failures
void menu::reliability_and_sensitivity_to_failures_select_city() {
    while (!this->go_back_to_main_menu) {
        this->go_back_to_main_menu = false;
        string current_menu = "Select city";
        string city_code = this->print_menu_and_get_string_input(current_menu);
        if (city_code == "0") {
            return;
        } else if (city_code == "-1") {
            this->go_back_to_main_menu = true;
            return;
        } else {
            bool is_input_valid = Request.check_city_exists(city_code);
            if (!is_input_valid) {
                cout << "City with code " << city_code << " does not exist\n";
            } else {
                while (true) {
                    this->go_back_to_main_menu = false;
                    string current_menu = "City with code " + city_code;
                    vector<string> options = {"Pipelines that make impossible to deliver to this specific city", "See the effect of removing each pipeline of the city to the entire network"};
                    int input = this->print_menu_and_get_choice_input(current_menu, options);
                    switch (input) {
                        case -1:
                            this->go_back_to_main_menu = true;
                            return;
                        case 0:
                            return;
                        case 1:
                            reliability_and_sensitivity_to_failures_pipelines_make_impossible_to_deliver(city_code);
                            break;
                        case 2:
                            reliability_and_sensitivity_to_failures_see_the_effect_of_removing_each_pipeline_of_the_city_to_the_entire_network(city_code);
                            break;
                        default:
                            cout << "Invalid input, please try again\n";
                            break;
                    }
                }
            }
        }
    }
}

/// @brief Gets the cities in deficit when each pipe is removed for each city
void menu::reliability_and_sensitivity_to_failures_pipelines_make_impossible_to_deliver(string city_code) {
    while (!this->go_back_to_main_menu) {
        this->go_back_to_main_menu = false;
        string current_menu = "Pipelines that make impossible to deliver to city with code " + city_code;
        vector<string> result = Request.iterate_over_each_pipe_in_specific_city_and_check_if_removing_them_the_city_flow_would_be_in_deficit(city_code);
        int input = this->print_result_and_get_choice_input(current_menu, result);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

/// @brief Gets the cities in deficit when each pipe is removed for all cities
void menu::reliability_and_sensitivity_to_failures_see_the_effect_of_removing_each_pipeline_of_the_city_to_the_entire_network(string city_code) {
    while (!this->go_back_to_main_menu) {
        this->go_back_to_main_menu = false;
        string current_menu = "See the effect of removing each pipeline of the city with code " + city_code + " to the entire network";
        vector<string> result = Request.iterate_over_each_pipe_in_specific_city_and_check_if_removing_them_the_network_flow_would_be_in_deficit(city_code);
        int input = this->print_result_and_get_choice_input(current_menu, result);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}