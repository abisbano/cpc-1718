/*
 MaximumPathSum.cc
 Author: Andrea Bisbano
 Date: 05/01/18
 Problem: https://practice.geeksforgeeks.org/problems/maximum-path-sum/1
 Solution:
  The idea behind this solution is that for each node we have three possibilities:
  1. is the root of the subtree covering the path
  2. is a inner node of the path
  3. is no part of the path
  Exploiting this idea, we use a function that, given a node, returns the maximum value of the path from
  a leaf to that inner node (case 2). If the given node has both left and right child, it also computes the
  value of the path composed by the node itself and the best possible paths of the two child.
  If a node is a leaf, it simply returns the value itself.
  When the visit of the tree is completed, we have the value of the best path.
 Time cost: O(n) because we need to visit all the nodes of the tree.
 Space cost: O(1)
*/

/*
 Please note that it's Function problem i.e.
 you need to write your solution in the form of Function(s) only.
 Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*Complete the function below
 Node is as follows

struct Node{
 int data;
 Node *left, *right;
 };
*/

#include <climits>
#include <algorithm>

int computePathSum(Node *root, int *maximum) {
  int leftPath = INT_MIN;
  int rightPath = INT_MIN;

  if (!root->left && !root->right) {
    // It's a leaf.
    return root->data;
  }

  // recursive calls
  if (root->left) {
    leftPath = computePathSum(root->left, maximum);
  }
  if (root->right) {
    rightPath = computePathSum(root->right, maximum);
  }

  // If it has two children try to update the maximum.
  if (root-> left && root->right) {
    int sum = root->data + leftPath + rightPath;
    *maximum = std::max(*maximum, sum);
  }
  return std::max(leftPath, rightPath) + root->data;
}

int maxPathSum(struct Node *root) {
  int result = INT_MIN;
  computePathSum(root, &result);
  return result;
}
