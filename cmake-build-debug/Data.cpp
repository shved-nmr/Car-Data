//
// Created by erkki on 11/01/2020.
//
#include <iostream>
#include "Data.h"

float Data::calc_consumption(float fuel, float end_mileage, float start_mileage) {
    float av_consumption = 0;
    av_consumption = fuel/(end_mileage-start_mileage)*100;
    return av_consumption;
}

float Data::calc_distance(float end_mil, float start_mil) {
    float distance = end_mil-start_mil;
    return distance;
}

std::ofstream &operator<<(std::ofstream &write, const Data &writeData) {
    write << writeData.start_loc << " " << writeData.end_loc << " " << writeData.start_h << " " << writeData.start_min
    << " " << writeData.end_h << " " << writeData.end_min << " " << writeData.start_mileage << " " << writeData.end_mileage
    << " " << writeData.fuel << " " << writeData.av_consumption << " " << writeData.driven_distance << " ";


    return write;
}

std::ifstream &operator>>(std::ifstream &read, Data &readData) {

    read >> readData.start_loc >> readData.end_loc >> readData.start_h >> readData.start_min
    >> readData.end_h >> readData.end_min >> readData.start_mileage >> readData.end_mileage
    >> readData.fuel >> readData.av_consumption >> readData.driven_distance;

    return read;
}

bool Data::operator==(const Data &d) {
    
    return start_loc == d.start_loc && end_loc == d.end_loc && start_h == d.start_h && start_min == d.start_min &&
    end_h == d.end_h && end_min == d.end_min && start_mileage == d.start_mileage && end_mileage == d.end_mileage &&
    fuel == d.fuel && av_consumption == d.av_consumption && driven_distance == d.driven_distance;
}
