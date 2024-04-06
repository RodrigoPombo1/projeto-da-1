cmake_minimum_required(VERSION 3.26)
project(projeto_da_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(projeto_da_1 main.cpp
        source/menu.cpp
        source/menu.h
        source/request.cpp
        source/request.h
        source/csv_reader.cpp
        source/csv_reader.h
        source/Water_reservoir.cpp
        source/Water_reservoir.h
        source/Pumping_station.cpp
        source/Pumping_station.h
        source/City.cpp
        source/City.h
        source/Pipeline.cpp
        source/Pipeline.h
        source/Supersource.cpp
        source/Supersource.h
        source/Supersink.cpp
        source/Supersink.h
        source/ReverseEdge.cpp
        source/ReverseEdge.h
)

include_directories(source)
