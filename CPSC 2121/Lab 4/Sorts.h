/*
 * Name: Reeves Farrell
 * Date Submitted: Due Feb 20th
 * Lab Section: 005
 * Assignment Name: Lab 4: Searching and Sorting
 */

#pragma once

#include <vector>
#include <cstdlib>

template <class T>
std::vector<T> mergeSort(std::vector<T> lst) {

    // Creates left and right half
    std::vector<T> left;
    std::vector<T> right;
    
    if (lst.size() <= 1) {
        
        return lst;
    }

    // Creates the middle value
    int middle = lst.size() / 2;

    // Fills in the left and right vectors
    for (int i = 0; i < middle; i++) {

        left.push_back(lst[i]);
    }
    for (int i = middle; i < lst.size(); i++) {

        right.push_back(lst[i]);
    }
    
    // Sorts the right half
    right = mergeSort(right);

    // Sorts the left half
    left = mergeSort(left);
    
    // Creates a merged list
    std::vector<T> merged;

    int i = 0;
    int j = 0;

    // Loops to actually merge the halves
    while (i < left.size() && j < right.size()) {

        if (left[i] < right[j]) {

            merged.push_back(left[i++]);
        } 
        else {

            merged.push_back(right[j++]);
        }
    }

    while (i < left.size()) {

        merged.push_back(left[i++]);
    }

    while (j < right.size()) {

        merged.push_back(right[j++]);
    }
    
    // Returns the sorted vector
    return merged;
}

template <class T>
std::vector<T> quickSort(std::vector<T> lst){

    // Checks if list is empty
    if (lst.size() <= 1) {

        return lst;
    }

    // Creates a random pivot index
    int pivNum = rand() % lst.size();

    // Gets the value at the pivot index
    T piv = lst[pivNum];

    // Creates the left and right for the sort
    std::vector<T> left;
    std::vector<T> right;

    // Fills in the left and right vector
    for (int i = 0; i < lst.size(); i++) {

        if (lst[i] < piv) {

            left.push_back(lst[i]);
        }
        else if (lst[i] > piv) {

            right.push_back(lst[i]);
        }
        else {

            continue;
        }
    }

    // Sorts each smaller list
    right = quickSort(right);

    // Sorts each smaller list
    left = quickSort(left);

    // Combines the lists including the pivot
    left.push_back(piv);
    left.insert(left.end(), right.begin(), right.end());

    return left;
}
