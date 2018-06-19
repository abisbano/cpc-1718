/*
 NextLargerElement.cc
 Author: Andrea Bisbano
 Date: 10/11/17
 Problem: http://practice.geeksforgeeks.org/problems/next-larger-element/0
 Solution:
  We use a stack to store, in decreasing order, the position of the elements
  for which we still have to find the next larger element (NLE). At each step
  of the loop, we remove from the head all the elements smaller than the current
  one, which is set as NLE of all those elements.
  Then we push that element to the head of the stack, and we know that all
  the other elements will be greater then that.
 Time cost: O(n) beacuse for each element we perform at most one push and one pop operation.
 Space cost: O(n) because we need to allocate the stack and in worst case scenario it can be of the same
              size of the input array (i.e. that occurs when the input element are sorted in decreasing
              order, so none has a NLE).
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <stack>

void nextLargerElement(const std::vector<uint32_t> &vec, std::vector<int32_t> &result) {
  std::stack<uint32_t> S;

  for (size_t i = 0; i < vec.size(); ++i) {
    while ((!S.empty()) && vec[S.top()] <= vec[i]) {
      result[S.top()] = vec[i];
      S.pop();
    }
    S.push(i);
  }

}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t T = 0;
  std::vector<uint32_t> vec;
  std::vector<int32_t> result;
  size_t size = 0;
  uint32_t val = 0;

  std::cin >> T;
  assert(T <= 200);

  for (size_t i = 0; i < T; ++i) {
    std::cin >> size;
    assert(size <= 1000);
    vec.reserve(size);
    result = std::vector<int32_t>(size, -1);

    for (size_t j = 0; j < size; ++j) {
      std::cin >> val;
      assert(val <= 10000);
      vec.push_back(val);
    }
    nextLargerElement(vec, result);
    for (auto k : result) {
      std::cout << k << " ";
    }
    std::cout << "\n";
    vec.clear();
    result.clear();
  }
}
