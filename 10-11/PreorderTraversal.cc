/*
  PreorderTraversal.cc

  author: Andrea Bisbano
  date: 04/01/18
  problem: https://practice.geeksforgeeks.org/problems/check-for-bst/1

  solution description:

 This solution exploit the fact that in a preorder traversal we find first the father, then the left
  subtree and then the right one. So for each value we have two cases: the value is either larger or
  smaller than the value of the father.
 In case is smaller, we compare the current value with the last ancestor which has a right child, if
  is greater than that the input can't represent a BST, otherwise we store the current value in a stack
  and we continue the computation.
 In case is larger, we search in the stack the real father of that value (i.e. the first value smaller
  than the current). If the stack is empty the father will be the previous value.

 The cost in time of this algorithm is O(n) because when we compare a value stored in the stack we also
  remove that, so we have at most 2n comparisons. For the same reason the additional cost in space is
  O(n), beacuse the stack can't exceed the original number of node.
*/

#include <cassert>
#include <vector>
#include <stack>
#include <iostream>


bool PreorderTraversal(const std::vector<int32_t> &traversal) {

  int32_t leftAncestor = -1;
  int32_t father = -1; // dummy value to have a for range loop
  std::stack<int32_t> rightAncestor;

  for (auto value : traversal) {
    if (father == -1) {
      father = value;
      continue;
    }

    if (value > father) {
      if (rightAncestor.empty()) {
        leftAncestor = value;
      } else {
        while (value < rightAncestor.top()) {
          rightAncestor.pop();
        }
        leftAncestor = rightAncestor.top();
        rightAncestor.pop();
      }
    }
    else  {
      if (value < leftAncestor) {
        return false;
      }
      rightAncestor.push(value);
    }
    father = value;
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
