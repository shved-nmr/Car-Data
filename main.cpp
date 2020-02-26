#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <array>
#include "cmake-build-debug/Data.h"

using namespace std;

Data add_trip(Data trips[], int array_index);

void print_data(Data trips[], int array_index);

void print_average(Data trips[], int array_index);

void record_data(Data trips[], int array_index);

void clear_records();

Data read_data(Data trips[], int &array_index);

void remove_data(Data trips[], int array_index);

int main() {
    const int array_size = 100;
    int array_index = 0;
    Data trips[array_size] = {};
    int choice;


    while (1) {


        cout << "=============== Driving Diary ================" << endl;

        cout << "1. Add New Trip" << endl;
        cout << "2. Display Your Trips" << endl;
        cout << "3. Print Average Fuel Consumption" << endl;
        cout << "4. Save Your Data to a File" << endl;
        cout << "5. Clear All Records Saved in the File" << endl;
        cout << "6. Read Data from File" << endl;
        cout << "7. Remove an Entry" << endl;
        cout << "0. Exit" << endl;

        cout << "~~~~~~~~~~~~~~~~~~~ Wheely ~~~~~~~~~~~~~~~~~~~" << endl;

        cout << "Please, enter your action:" << endl;
        cin >> choice;


        switch (choice) {
            case 1:
                add_trip(trips, array_index);
                array_index++;
                break;

            case 2:
                print_data(trips, array_index);
                break;

            case 3:
                print_average(trips, array_index);
                break;

            case 4:
                record_data(trips, array_index);
                break;

            case 5:
                clear_records();
                break;
            case 6:
                read_data(trips, array_index);
                break;
            case 7:
                remove_data(trips, array_index);
                break;
            case 0:
                exit(0);
            default:
                cout << "Invalid input" << endl;
                break;
        }
    }

}

Data add_trip(Data trips[], int array_index) {

    const int MAX_H = 23;
    const int MAX_MIN = 59;
    const int MIN_TIME = 0;
    const float MIN_FUEL = 0;
    Data NewEntry;
    char colon;
    cout << "Please, enter the starting location of your journey" << endl;
    cin >> NewEntry.start_loc;

    for (;;) {
        cout << "Please, enter the starting time of your journey (HH:MM)" << endl;
        cin >> NewEntry.start_h >> colon >> NewEntry.start_min;
        if (cin.fail()) {
            cout << "Not an int." << endl;
            cin.clear();
            fflush(stdin);
        } else if (NewEntry.start_h < MIN_TIME || NewEntry.start_h > MAX_H || NewEntry.start_min < MIN_TIME ||
                   NewEntry.start_min > MAX_MIN) {
            cout << "Please, enter valid time. Make sure to type colon in between HH and MM." << endl;
        } else {
            break;
        }
    }

    for (;;) {
        cout << "Please, enter the mileage at the beginning of your journey" << endl;
        cin >> NewEntry.start_mileage;
        if (cin.fail()) {
            cout << "Not an int." << endl;
            cin.clear();
            fflush(stdin);
        } else {
            break;
        }
    }

    cout << "Please, enter the ending location of your journey" << endl;
    cin >> NewEntry.end_loc;

    for (;;) {
        cout << "Please, enter the ending time of your journey (HH:MM)" << endl;
        cin >> NewEntry.end_h >> colon >> NewEntry.end_min;
        if (cin.fail()) {
            cout << "Not an int." << endl;
            cin.clear();
            fflush(stdin);
        } else if (NewEntry.end_h < MIN_TIME || NewEntry.end_h > MAX_H || NewEntry.end_min < MIN_TIME ||
                   NewEntry.end_min > MAX_MIN) {
            cout << "Please, enter valid time. Make sure to type colon in between HH and MM." << endl;
        } else {
            break;
        }
    }


    for (;;) {
        cout << "Please, enter the mileage at the end of your journey: " << endl;
        cin >> NewEntry.end_mileage;

        if (cin.fail()) {
            cout << "Not an int." << endl;
            cin.clear();
            fflush(stdin);

        } else if (NewEntry.end_mileage > NewEntry.start_mileage) {
            break;

        } else {
            cout << "The end mileage must be larger than the start mileage!" << endl;
        }
    }

    for (;;) {
        cout << "Please, enter the amount of fuel bought for the trip (Optional, type in 0 if not wanted)" << endl;
        cin >> NewEntry.fuel;
        if (cin.fail()) {
            cout << "Not an int." << endl;
            cin.clear();
            fflush(stdin);
        } else {
            break;
        }
    }

    if (NewEntry.fuel > MIN_FUEL) {
        NewEntry.av_consumption = NewEntry.calc_consumption(NewEntry.fuel, NewEntry.end_mileage,
                                                            NewEntry.start_mileage);
    }

    NewEntry.driven_distance = NewEntry.calc_distance(NewEntry.end_mileage, NewEntry.start_mileage);
    if (array_index < 99) {
        trips[array_index] = NewEntry;
    } else {
        cout << "The array is full!" << endl;
    }


    return NewEntry;
}

void print_data(Data trips[], int array_index) {
    float low_lim = 0;
    float upp_lim = 0;
    cout << "enter the lower limit of driven distance" << endl;
    cin >> low_lim;
    cout << "enter the upper limit of driven distance" << endl;
    cin >> upp_lim;

    for (int i = 0; i < array_index; i++) {
        if (trips[i].driven_distance > low_lim && trips[i].driven_distance < upp_lim) {
            cout << "Entry ID: " << i << endl;
            cout << "Starting location: " << trips[i].start_loc << endl;
            cout << "Starting time: " << trips[i].start_h << ":" << trips[i].start_min << endl;
            cout << "Starting mileage: " << trips[i].start_mileage << " km" << endl;
            cout << "End location: " << trips[i].end_loc << endl;
            cout << "End time: " << trips[i].end_h << ":" << trips[i].end_min << endl;
            cout << "End mileage: " << trips[i].end_mileage << " km" << endl;
            if (trips[i].fuel > 0) {
                cout << "Amount of fuel tanked: " << trips[i].fuel << " l" << endl;
                cout << setprecision(4);
                cout << "Average consumption: " << trips[i].av_consumption << " l/100 km" << endl;
            } else {
                cout << "No fuel data" << endl;
            }
            cout << "Distance driven: " << trips[i].driven_distance << endl;
            cout << "______________________________________________" << endl;
        }
    }
    cout << " " << endl;
}

void record_data(Data trips[], int array_index) {
    ofstream myfile;
    Data test_data[100] = {};
    ifstream test_d;
    int t = 0;
    test_d.open("Data.txt", ios::in);
    while (!test_d.eof()) {
        test_d >> test_data[t];
        ++t;
    }

    myfile.open("Data.txt", ios::app);
    if (!myfile) {
        cerr << "Unable to open file data.txt";
        exit(1);
    }

    for (int i = 0; i < array_index; i++) {
        bool found = false;
        for (int z = 0; z < t; z++) {
            if (trips[i] == test_data[z]) {
                found = true;
                break;
            }
        }
        if (!found) {
            myfile << trips[i];
        }
    }
}

Data read_data(Data trips[], int &array_index) {
    Data test;
    ifstream myfile;
    Data data_array[100] = {};
    myfile.open("Data.txt", ios::in);


    while (!myfile.eof()) {
        myfile >> test;
        bool found = false;
        for (int z = 0; z < array_index; z++) {

            if (trips[z] == test) {
                found = true;
                break;
            }
        }
        if (!found) {
            trips[array_index] = test;
            array_index++;
        }
    }

    return test;
}

void print_average(Data trips[], int array_index) {

    for (int i = 0; i < array_index; i++) {
        if (trips[i].fuel != 0) {
            float average_cons = trips[i].calc_consumption(trips[i].fuel, trips[i].end_mileage, trips[i].start_mileage);
            cout << setprecision(4);
            cout << "The average fuel consumption of your trip from " << trips[i].start_loc << " to "
                 << trips[i].end_loc
                 << " is: " << average_cons << "l/100km" << endl;
        } else {
            cout << "No fuel data found." << endl;
        }
    }
}

void clear_records() {
    ofstream myfile;
    Data NewDataClean;

    myfile.open("Data.txt", ios::out | ios::trunc);

    if (!myfile) {
        cerr << "Unable to open file data.txt, try again. The data has not been erased.";
        exit(1);
    }
    cout << "The data was successfully erased from the Data.txt file!" << endl;
    myfile.close();
}

void remove_data(Data trips[], int array_index) {
    int delete_ID = 0;

    cout << "Please, provide the ID of the element to be deleted: " << endl;
    cin >> delete_ID;
    cout << "array index: " << array_index << endl;

    for (int i = delete_ID; i < (array_index); i++) {

        trips[i] = trips[i + 1];

    }
}