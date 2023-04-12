/*
 * Name: Reeves Farrell
 * Date Submitted: Due March 6th
 * Lab Section: 005
 * Assignment Name: Lab 5: Spell Checker Using a Hash Table
 */

#include "stringset.h"
#include <functional>
#include <string>
#include <iostream>

using namespace std;

Stringset::Stringset() : table(4), num_elems(0), size(4) {}

//Used in test cases and testStringset() in main.cpp, do not modify
vector<list<string>> Stringset::getTable() const
{
    return table;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getNumElems() const
{
    return num_elems;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getSize() const
{
    return size;
}

void Stringset::insert(string word) {

    if (find(word)) {

        return;
    }

    // Gets the key for the word
    int key = hash<string>{}(word) % table.size();

    // Adds the word to the list
    table[key].push_back(word);

    // Updates the size
    num_elems = num_elems + 1;

    if (num_elems > table.size()) {
        
        // Creayes a new table with the new size
        vector<list<string>> newTable(table.size() * 2);
        
        for (const auto& list : table) {
            
            for (const auto& words : list) {

                // Gets a new key for the word
                int newKey = hash<string>{}(words) % newTable.size();

                // Inserts the word to the new linked list
                newTable[newKey].push_back(words);
            }
        }

        // Replaces table with newTable
        table = newTable;

        size = table.size();
    }
}

bool Stringset::find(string word) const {

    // Gets the key for the word
    int key = hash<string>{}(word) % table.size();

    // Loops through the linked list
    for (auto& temp : table[key]) {

        // Returns true if word is found
        if (temp == word) {

            return true;
        }
    }

    // Returns false if not found
    return false;
}

void Stringset::remove(string word) {

    // Gets the key for the word
    int key = hash<string>{}(word) % table.size();

    // Loops through the linked list
    for (auto temp = table[key].begin(); temp != table[key].end(); temp++) {

        if (*temp == word) {

            // Deletes the word from the list
            table[key].erase(temp);

            // Decrements the number of elements by 1
            num_elems = num_elems - 1;

            return;
        }
    }
}