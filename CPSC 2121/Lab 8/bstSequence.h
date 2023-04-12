/*
 * Name: Reeves Farrell
 * Date Submitted: Due April 5th by 11:59pm
 * Lab Section: 005
 * Assignment Name: Lab 8: Storing a Sequence in a Binary Search Tree
 */

#pragma once

#include <iostream>
#include <vector>

using namespace std;

struct Node {
  int key;
  int size;
  Node *left;
  Node *right;
  Node (int k) { key = k; size = 1; left = right = nullptr; }
};

void fix_size(Node *T);
Node *insert(Node *T, int v, int r);
vector<int> inorder_traversal(Node *T);
Node *select(Node *T, int r);
void split(Node *T, int r, Node **L, Node **R);
Node *insert_random(Node *T, int v, int r);
bool did_x_beat_y(int x, int y);
Node *order_n_teams(int n);
void printVector(vector<int> v);
int helper(Node*, int);