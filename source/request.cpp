//
// Created by rodri on 03/04/2024.
//

#include "request.h"

using namespace std;

request::request() {
    this->csvReader = csv_reader();
    this->cities = this->csvReader.getCities();
    this->reservoirs = this->csvReader.getReservoirs();
    this->stations = this->csvReader.getStations();
    this->pipes = this->csvReader.getPipes();
}

// o algoritmo no fundo so vai ter o supersink o supersource as pipelines e as pumping stations
// tudo o q e interagir com cidades e reservatorios vai estar dentro do supersink e do supersource