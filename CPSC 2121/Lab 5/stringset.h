/*
 * Name: Reeves Farrell
 * Date Submitted: Due March 6th
 * Lab Section: 005
 * Assignment Name: Lab 5: Spell Checker Using a Hash Table
 */

#pragma once

#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

//Stringset class, do not modify definitions for existing members
class Stringset
{
    private:
        vector<list<string>> table;
        int num_elems;
        int size;
    public:
        Stringset();
        vector<list<string>> getTable() const;
        int getNumElems() const;
        int getSize() const;
        void insert(string word);
        bool find(string word) const;
        void remove(string word);
};