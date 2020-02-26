//
// Created by erkki on 11/01/2020.
//
#include <iostream>
#include <string>
#include <ctime>
#ifndef CARDATA_DATA_H
#define CARDATA_DATA_H
#include <fstream>
using namespace std;

class Data {
public:
    string start_loc;
    string end_loc;
    int start_h;
    int start_min;
    int end_h;
    int end_min;
    float start_mileage;
    float end_mileage;
    float fuel;
    float av_consumption;
    float driven_distance;

    float calc_consumption(float fuel, float end_mileage, float start_mileage);
    float calc_distance(float end_mil, float start_mil);

    friend std::ofstream &operator << (std::ofstream& write, const Data&writeData);
    friend std::ifstream &operator >> (std::ifstream& read, Data&readData);

    bool operator==(const Data &d);
};


#endif //CARDATA_DATA_H
