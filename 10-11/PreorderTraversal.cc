/*
 PreorderTraversal.cc
 Author: Andrea Bisbano
 Date: 04/01/18
 Problem: https://practice.geeksforgeeks.org/problems/preorder-traversal-and-bst/0
 Solution:
  In a preorder traversal, the root of a tree is seen first, followed by its left subtree and then
  its right subtree. The algorithm compares each value with its predecessor.
  If the value is greater, then it has to be in the right subtree. The stack containing the right ancestors
  is visited until it finds the first greater value, which is set as the father of the current node
  (updating the variable `leftAncestor'). If the stack is empty, the value itself is assigned
  to the variable.
  If the value is smaller, then it has to be in the left subtree. If the value is smaller the variable
  `leftAncestor' then this means that node is in the wrong subtree and thus the tree is not a BST.
  Otherwise the values is pushed to the stack.
 Time cost: O(n) because we have at most 2n comparisons.
 Space cost: O(n) because the stack size can't exceed the original number of nodes.
*/

#include <cassert>
#include <vector>
#include <stack>
#include <iostream>


bool PreorderTraversal(const std::vector<int32_t> &traversal) {

  size_t size = traversal.size();
  int32_t leftAncestor = -1;
  int32_t father = traversal[0];
  std::stack<int32_t> rightAncestor;

  for (size_t i = 1; i < size; ++i) {

    if (traversal[i] > father) {
      // current value is in the right subtree (e.g. it updates leftAncestor)
      if (rightAncestor.empty()) {
        leftAncestor = traversal[i];
      } else {
        while (traversal[i] < rightAncestor.top()) {
          rightAncestor.pop();
        }
        leftAncestor = rightAncestor.top();
        rightAncestor.pop();
      }

    } else {
      // current value is in the left subtree
      if (traversal[i] < leftAncestor) {
        return false;
      }
      rightAncestor.push(traversal[i]);
    }
    father = traversal[i];
  }

  return true;

}

int main() {
  size_t testCases;
  size_t N;
  std::vector<int32_t> vec;
  int32_t value;

  std::cin >> testCases;
  assert (testCases >= 1 && testCases <= 55);

  for (size_t i = 0; i < testCases; ++i) {
    std::cin >> N;
    assert(N >= 1 && N <= 1000);
    vec.reserve(N);
    for (size_t j = 0; j < N; ++j) {
      std::cin >> value;
      assert(value >= 1 && value <= 1000);
      vec.push_back(value);
    }
    std::cout << PreorderTraversal(vec) << std::endl;
    vec.clear();
  }
}
