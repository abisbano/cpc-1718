/*
 Leader.cc
 Author: Andrea Bisbano
 Date: 06/10/17
 Problem: http://practice.geeksforgeeks.org/problems/leaders-in-an-array/0#ExpectOP
 Solution:
  The idea is to search the maximum element of the array starting scanning from the end.
  By doing this, each time we update the maximum element we know that it's a leader because
    is guaranteed that the past element are smaller than it.
 Time cost: O(n) because we need to scan one time the whole array.
 Space cost: O(n) because for each element we need to store if it's a leader or not.
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
  size_t N = 0;
  uint32_t val = 0;

  std::cin >> T;
  assert(T > 0 && T <= 100);

  for (int i = 0; i < T; ++i) {
    std::cin >> N;
    assert(N > 0 && N <=100);
    vec.reserve(N);
    leaders.reserve(N);
    for (int j = 0; j < N; ++j) {
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
