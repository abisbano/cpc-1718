/*
 TrappingRain.cc
 Author: Andrea Bisbano
 Date: 27/10/17
 Problem: http://practice.geeksforgeeks.org/problems/trapping-rain-water/0
 Solution:
  The idea of this solution is to precompute and store in an array of the same
  size of the input data the value of the maximum element in the left subarray
  of each element.
  After that we scan the original array in reverse order, keeping track of the
  maximum value so far. For each element, the water trapped is the difference
  between the current value and the minimun between the maximum to the right
  and to the left.
 Time cost: O(n), because we need to scan the array 2 times.
 Space cost: O(n) to store the support array of the same length.
 */

#include<vector>
#include<iostream>
#include<cassert>
#include<algorithm>

int32_t trappingRain(const std::vector<int32_t> &vec) {
  int32_t result = 0;
  std::vector<int32_t> leftMax;
  leftMax.reserve(vec.size());
  int32_t currentMax = -1; // We use a dummy value for the first element,
                           // since it hasn't a left subarray.

  for (auto it = vec.begin(), end = vec.end(); it != end; ++it) {
    leftMax.push_back(currentMax);
    if (*it > currentMax) {
      currentMax = *it;
    }
  }

  currentMax = -1; // We use the same variable for the maximum of the right subarray

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
  std::vector<int32_t> vec;
  size_t N;
  int32_t val;

  std::cin >> T;
  assert(T > 0 && T <= 100);

  for (size_t i = 0; i < T; ++i) {
    std::cin >> N;
    assert(N > 2 && N <= 100);
    vec.reserve(N);
    for (size_t j = 0; j < N; ++j) {
      std::cin >> val;
      assert(val >= 0 && val < 10);
      vec.push_back(val);
    }

    std::cout << trappingRain(vec) << "\n";
    vec.clear();
  }
}
