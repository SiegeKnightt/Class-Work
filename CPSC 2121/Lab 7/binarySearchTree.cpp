/*
 * Name: Reeves Farrell
 * Date Submitted: Due Mar 31 by 11:59pm
 * Lab Section: 005
 * Assignment Name: Lab 7: Binary Search Tree
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>

#include "binarySearchTree.h"

using namespace std;

void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  if (T == nullptr) return new Node(k);
  if (k < T->key) T->left = insert(T->left, k);
  else T->right = insert(T->right, k);
  fix_size(T);
  return T;
}

// returns a vector of key values corresponding to the inorder traversal of T (i.e., the contents of T in sorted order)
vector<int> inorder_traversal(Node *T)
{
  vector<int> inorder;
  vector<int> rhs;
  if (T == nullptr) return inorder;
  inorder=inorder_traversal(T->left);
  inorder.push_back(T->key);
  rhs=inorder_traversal(T->right);
  inorder.insert(inorder.end(), rhs.begin(), rhs.end());
  return inorder;
}

// return a pointer to the node with key k in tree T, or nullptr if it doesn't exist
// Implement Node *find(Node *T, int k)
Node *find(Node *T, int k) {

  // If tree is empty
  // return nullptr
  if (T == nullptr) {

    return nullptr;
  }
  // If the key is found, return T
  else if (k == T->key) {

    return T;
  }
  // Goes into the left or right sub tree
  // to find the correct node
  else if (T->key < k) {

    return find(T->right, k);
  }
  else {

    return find(T->left, k);
  }
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
// Implement Node *select(Node *T, int r)
Node *select(Node *T, int r) {

  assert(T!=nullptr && r>=0 && r<T->size);

  int rank = T->left ? T->left->size : 0;

  if (r == rank) {

    return T;
  }
  // Checks left and right node sub trees
  // to find node with same rank as r
  else if (rank < r) {

    int r2 = r - rank;

    r2 = r2 - 1;

    return select(T->right, r2);
  }
  else {

    return select(T->left, r);
  }
}

// Join trees L and R (with L containing keys all <= the keys in R)
// Return a pointer to the joined tree. 
// choose either the root of L or the root of R to be the root of the joined tree
// (where we choose with probabilities proportional to the sizes of L and R)
  
// Implement Node *join(Node *L, Node *R) 
Node *join(Node *L, Node *R) {
  
  if (L == nullptr) {

    return R;
  }

  if (R == nullptr) {

    return L;
  }

  // Has to be here incase trees are empty
  double key = rand() / (L->size + R->size);

  if (key < L->size) {

    L->right = join(L->right, R);

    fix_size(L);

    return L;
  }
  else if (key >= L->size) {

    R->left = join(L, R->left);

    fix_size(R);

    return R;
  }

  return nullptr;
}

// remove key k from T, returning a pointer to the resulting tree.
// it is required that k be present in T
// Implement Node *remove(Node *T, int k)
Node *remove(Node *T, int k) {
  
  assert(T != nullptr);

  if (T == nullptr) {

    return nullptr;
  }

  if (k == T->key) {

    Node *temp = join(T->left, T->right);

    delete T;

    return temp;
  }
  // If k is less than key,
  // go into left sub tree
  // remove the key from the left
  else if (k < T->key) {

    T->left = remove(T->left, k);
  }
  // If k is bigger than key,
  // go into right sub tree
  // remove the key from the right
  else {

    T->right = remove(T->right, k);
  }

  // Updates the size
  T->size = T->size - 1;

  fix_size(T);

  return T;
}

// Split tree T on key k into tree L (containing keys <= k) and a tree R (containing keys > k)
// Implement void split(Node *T, int k, Node **L, Node **R)
void split(Node *T, int k, Node **L, Node **R) {
  
  if (T == nullptr) {

    *R = nullptr;

    *L = nullptr;

    return;
  }

  if (k < T->key) {

    Node **l2 = &(T->left);

    split(T->left, k, L, l2);

    *R = T;

    fix_size(T);
  }
  else {

    Node **r2 = &(T->right);

    split(T->right, k, r2, R);

    *L = T;

    fix_size(T);
  }

  fix_size(T);
}

// insert key k into the tree T, returning a pointer to the resulting tree
// If k is the Nth node inserted into T, then:
// with probability 1/N, insert k at the root of T
// otherwise, insert_random k recursively left or right of the root of T
  
// Implement Node *insert_random(Node *T, int k)
Node *insert_random(Node *T, int k) {

  if (T == nullptr) {

    return new Node(k);
  }

  int temp = rand() % (T->size + 1);

  // IF no nodes exist in thr right subtree
  // insert at the root of the tree
  if (temp == 0) {

    Node *temp2 = new Node(k);

    split(T, k, &(temp2->left), &(temp2->right));

    fix_size(temp2);

    return temp2;
  }

  // Split T at K if k is in the left
  if (k < T->key) {

    T->left = insert_random(T->left, k);
  }
  // Split T at K if k is in the right
  else {

    T->right = insert_random(T->right, k);
  }

  fix_size(T);

  return T;
}

void printVector(vector<int> v)
{
    for (int i=0; i<v.size(); i++)
    {
        cout << v[i] << endl;
    }
}

int main(void)
{
  vector<int> inorder;
  vector<int> A(10,0);
  
  // put 0..9 into A[0..9] in random order
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  cout << "Contents of A (to be inserted into BST):\n";
  printVector(A);
  
  // insert contents of A into a BST
  Node *T = nullptr;
  for (int i=0; i<10; i++) T = insert(T, A[i]);
  
  // print contents of BST (should be 0..9 in sorted order)
  cout << "Contents of BST (should be 0..9 in sorted order):\n";
  inorder=inorder_traversal(T);
  printVector(inorder);

  // test select
  for (int i=0; i<10; i++) {
    Node *result = select(T, i);
    if (!result || result->key != i) cout << "Select test failed for select(" << i << ")!\n";
  }

  // test find: Elements 0..9 should be found; 10 should not be found
  cout << "Elements 0..9 should be found; 10 should not be found:\n";
  for (int i=0; i<11; i++) 
    if (find(T,i)) cout << i << " found\n";
    else cout << i << " not found\n";

  // test split
  Node *L, *R;
  split(T, 4, &L, &R);
  cout << "Contents of left tree after split (should be 0..4):\n";
  inorder=inorder_traversal(L);
  printVector(inorder);
  cout << "Left tree size " << L->size << "\n";
  cout << "Contents of right tree after split (should be 5..9):\n";
  inorder=inorder_traversal(R);
  printVector(inorder);
  cout << "Right tree size " << R->size << "\n";
    
  // test join
  T = join(L, R);
  cout << "Contents of re-joined tree (should be 0..9)\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
  cout << "Tree size " << T->size << "\n";
  
  // test remove
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  for (int i=0; i<10; i++) {
    T = remove(T, A[i]);
    cout << "Contents of tree after removing " << A[i] << ":\n";
    inorder=inorder_traversal(T);
    printVector(inorder);
    if (T != nullptr)
      cout << "Tree size " << T->size << "\n";
  }

  // test insert_random
  cout << "Inserting 1 million elements in order; this should be very fast...\n";
  for (int i=0; i<1000000; i++) T = insert_random(T, i);
  cout << "Tree size " << T->size << "\n";
  cout << "Done\n";
  
  return 0;
}
