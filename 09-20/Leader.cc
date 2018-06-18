/*
 Leader.cc
 Author: Andrea Bisbano
 Date: 06/10/17
 Problem: http://practice.geeksforgeeks.org/problems/leaders-in-an-array/0#ExpectOP
 Solution:
  We scan the array in reverse order and we keep track of the current maximum element.
  Every time the maximum element is updated means we've found a new leader (since we
  know all the elements on the right are smaller than that.
 Time cost: O(n) because we need to scan one time the whole array.
 Space cost: O(n) because we need to store the values that are leader.
*/

#include <iostream>
#include <vector>
#include <cassert>

void findLeaders(const std::vector<uint32_t> &vec, std::vector<uint32_t> &leaders) {
  uint32_t max = vec.back();
  // last element is always a leader.
  leaders.push_back(max);

  for (auto it = vec.rbegin() + 1, end = vec.rend(); it != end; ++it) {
    if (*it > max) {
      max = *it;
      leaders.push_back(max);
    }
  }

  return;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t T = 0;
  std::vector<uint32_t> vec;
  std::vector<uint32_t> leaders;
  size_t size = 0;
  uint32_t val = 0;

  std::cin >> T;
  assert(T > 0 && T <= 100);

  for (int i = 0; i < T; ++i) {
    std::cin >> size;
    assert(size > 0 && size <=100);
    vec.reserve(size);
    leaders.reserve(size);
    for (int j = 0; j < size; ++j) {
      std::cin >> val;
      assert(val >= 0 && val <= 100);
      vec.push_back(val);
    }
    findLeaders(vec, leaders);

    for (auto it = leaders.rbegin(), end = leaders.rend();
         it != end; ++it) {
      std::cout << *it << " ";
    }
    std::cout << "\n";

    vec.clear();
    leaders.clear();
  }
}
