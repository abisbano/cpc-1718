/*
 TrappingRain.cc
 Author: Andrea Bisbano
 Date: 27/10/17
 Problem: http://practice.geeksforgeeks.org/problems/trapping-rain-water/0
 Solution:
  We begin creating an array of the same size of the input array.
  In each position of the new array we store the maximum value of the left
  subarray starting from the same position in the original array.
  After that we scan the original array in reverse order, keeping track of the
  maximum value so far. For each element, the water trapped is the difference
  between the current value and the minimun between the maximum of left and right
  subarrays.
 Time cost: O(n), because we need to scan the array 2 times.
 Space cost: O(n) to store the support array of the same length.
 */

#include<vector>
#include<iostream>
#include<cassert>
#include<algorithm>

uint32_t trappingRain(const std::vector<uint32_t> &vec) {
  uint32_t result = 0;
  std::vector<uint32_t> leftMax;
  leftMax.reserve(vec.size());
  uint32_t currentMax = 0; // We use a dummy value for the first element,
                           // since it hasn't a left subarray.

  for (auto it = vec.begin(), end = vec.end(); it != end; ++it) {
    leftMax.push_back(currentMax);
    if (*it > currentMax) {
      currentMax = *it;
    }
  }

  currentMax = 0; // Reset the value

  auto it2 = leftMax.rbegin();
  for (auto it1 = vec.rbegin(), end = vec.rend(); it1 != end; ++it1, ++it2) {
    if (*it1 > currentMax) {
      currentMax = *it1;
    } else {
      if (*it1 < *it2) {
        result += (std::min(currentMax, *it2) - *it1);
      }
    }
  }
  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t T;
  std::vector<uint32_t> vec;
  size_t size;
  uint32_t val;

  std::cin >> T;
  assert(T <= 100);

  for (size_t i = 0; i < T; ++i) {
    std::cin >> size;
    assert(size <= 100);
    vec.reserve(size);
    for (size_t j = 0; j < size; ++j) {
      std::cin >> val;
      assert(val < 10);
      vec.push_back(val);
    }

    std::cout << trappingRain(vec) << "\n";
    vec.clear();
  }
}
