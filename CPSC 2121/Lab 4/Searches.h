/*
 * Name: Reeves Farrell
 * Date Submitted: Due Feb 20th
 * Lab Section: 005
 * Assignment Name: Lab 4: Searching and Sorting
 */

#pragma once

#include <vector>

template <class T>
int linearSearch(std::vector<T> data, T target){

    for (int i = 0; i < data.size(); i++) {

        if (data.at(i) == target) {

            return i;
        }
    }

    return -1;
}


template <class T>
int binarySearch(std::vector<T> data, T target){

    int upper = data.size();
    int lower = 0;
    
    while (lower < upper) {

        int middle = (lower + upper) / 2;
        
        if (target == data.at(middle)) {

            return middle;
        }

        if (target > data.at(middle)) {

            lower = middle + 1;
        }
        else {

            upper = middle - 1;
        }
    }

    return -1;
}
