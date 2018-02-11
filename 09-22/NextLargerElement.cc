/*
 NextLargerElement.cc
 Author: Andrea Bisbano
 Date: 10/11/17
 Problem: http://practice.geeksforgeeks.org/problems/next-larger-element/0
 Solution:
  We want to use a stack to store, in increasing order, the position of the elemnts for which we still
  have to find the next larger element. At each step of the loop, we remove from the head all the elements
  smaller than the current one, which is set as NLE for all the previously removed elements. After that,
  we push the current element to the head of the stack and we know for construction that the other
  elements in the stack are largher than that
 Time cost: O(n) beacuse for element we perform at most one push and one pop operation.
 Space cost: O(n) because we need to allocate the stack and in worst case scenario it can be of the same
              size of the input array (i.e. that occurs when the input element are sorted in decreasing
              order, so none has a NLE).
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <stack>

void nextLargerElement(const std::vector<int> &vec, std::vector<int> &result) {
  std::stack<int> st;

  for (int i = 0; i < vec.size(); ++i) {
    while ((!st.empty()) && vec[st.top()] <= vec[i]) {
      result[st.top()] = vec[i];
      st.pop();
    }
    st.push(i);
  }

}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int T = 0;  std::vector<int> vec;
  std::vector<int> result;
  int size = 0;
  int val = 0;

  std::cin >> T;
  assert(T > 0 && T <= 200);

  for (int i = 0; i < T; ++i) {
    std::cin >> size;
    assert(size > 0 && size <= 1000);
    vec.reserve(size);
    result = std::vector<int>(size, -1);

    for (int j = 0; j < size; ++j) {
      std::cin >> val;
      // This assertion is commented out because it invalidates the test case on geeksforgeek,
      // even if the problem states that each element is in [1, 1000].
      //assert(val > 0 && val <= 1000);
      vec.push_back(val);
    }
    nextLargerElement(vec, result);
    for (int k : result) {
      std::cout << k << " ";
    }
    std::cout << "\n";
    vec.clear();
    result.clear();
  }
}
