/*
 Kadane.cc
 Author: Andrea Bisbano
 Date: 10/10/17
 Problem: http://practice.geeksforgeeks.org/problems/kadanes-algorithm/0
 Solution:
  This solution exploits two properties of the subarray with maximum sum:
  1. Sum of values of each subarray of the optimum subarray is positive.
      Consider the array [3 -4 5], here the sum of subarray [3 -4] is -1. If
      we consider the whole array as solution, the result is 4, instead if we
      remove that subarray we see there's a better solution (which is 5).
  2. The value that precede the first value of the optimal subarray is
      a negative one. This is easy to prove: if that value is positive, then
      we might add it to the solution to have an higher value.
  Using these two properties we can iterate only one time over the element of the array.
 Time cost: O(n) because we need to scan one time the whole array.
 Space cost: O(1).
 */

#include<vector>
#include<iostream>
#include<cassert>
#include<climits>

int32_t kadane(const std::vector<int32_t> &vec) {
  int32_t maxSum = INT_MIN;
  int32_t sum = 0;
  for (auto it = vec.begin(), end = vec.end(); it != end; ++it) {
  /* One if statement is enough to apply both properties:
     1. if the sum of the current subarray is negative, we start over
     2. if we're considering a negative number as first element, we fall to case 1
  */
    if (sum > 0)
      sum += *it;
    else
      sum = *it;

    if (sum > maxSum)
      maxSum = sum;
  }
  return maxSum;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t T;
  std::vector<int> vec;
  size_t size;
  int32_t val;

  std::cin >> T;
  assert(T <= 200);

  for (size_t i = 0; i < T; ++i) {
    std::cin >> size;
    assert(size <= 1000);

    vec.reserve(size);

    for (size_t j = 0; j < size; ++j) {
      std::cin >> val;
      assert(val >= -100 && val <= 100);
      vec.push_back(val);
    }
    std::cout << kadane(vec) << "\n";
    vec.clear();
  }
}
