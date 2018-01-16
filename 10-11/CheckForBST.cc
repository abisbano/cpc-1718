/*
  CheckForBST.cc

  author: Andrea Bisbano
  date: 02/01/18
  problem: https://practice.geeksforgeeks.org/problems/check-for-bst/1

  solution description:
 The idea of this solution is to compute the min and max values of a tree and compare those values
  with the root to see if it's a BST or not (i.e. a tree is a BST if the maximum value of the left
  subtree is smaller than the value of the root and the minimum value of the right subtree is smaller
  than the value of the root).
 To compute that we use the funcion `maybeComputeMinMax' which, given a Node and a boolean value,
  returns the minimum and maximum values of the tree iif it's a BST, otherwise the values returned
  can be any.

 The cost of the algorithm is O(n) because we need to traverse the whole tree and we don't need additional
  space because the function is recursive. We would need additional space for a stack if the visit is
  iterative.

*/

/*
 Please note that it's Function problem i.e.
 you need to write your solution in the form of Function(s) only.
 Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/* A binary tree node has data, pointer to left child
 and a pointer to right child
 struct Node {
 int data;
 Node* left, * right;
 }; */
/* Should return true if tree represented by root is BST.
 For example, return  value should be 1 for following tree.
 20
 /      \
 10       30
 and return value should be 0 for following tree.
 10
 /      \
 20       30 */

#include <utility>
#include <algorithm>

std::pair<int, int> maybeComputeMinMax(Node* root, bool *isBST) {
  int min = root->data;
  int max = root->data;

  // If at any point the boolean becomes false, we do nothing.
  if (*isBST) {
    if (root->left) {
      auto leftMinMax = maybeComputeMinMax(root->left, isBST);
      if (leftMinMax.second > root->data) {
        *isBST = false;
      } else {
        min = std::min(min, leftMinMax.first);
      }
    }

    if (root->right) {
      auto rightMinMax = maybeComputeMinMax(root->right, isBST);
      if (rightMinMax.first < root->data) {
        *isBST = false;
      } else {
        max = std::max(max, rightMinMax.second);
      }
    }
  }

  return std::make_pair(min, max);
}

bool isBST(Node* root) {
  if (!root) return true;
  bool result = true;
  maybeComputeMinMax(root, &result);
  return result;
}