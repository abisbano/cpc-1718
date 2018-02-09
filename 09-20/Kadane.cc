/*
  Kadane.cc

  author: Andrea Bisbano
  date: 10/10/17
  problem: http://practice.geeksforgeeks.org/problems/kadanes-algorithm/0

  description:
   This solution exploits two properties of the subarray with maximum sum:
   1. Sum of values of each subarray of the optimum subarray is positive.
      Consider the array [3 -4 5], here the sum of subarray [3 -4] is -1. If
      we consider the whole array as solution, the result is 4, instead if we
      remove that subarray we see there's a better solution (which is 5).
   2. The value that precede the first value of the optimal subarray is
      a negative one. This is easier to prove: if that value is positive, then
      we might add it to the solution to have an higher value.
   Using these two properties we can iterate only one time over the element of the array.

  time cost: O(n) because we need to scan one time the whole array.
  space cost: O(1) because we don't need additional storage.

 */

#include<vector>
#include<iostream>
#include<cassert>
#include<climits>

int32_t kadane(const std::vector<int32_t> &vec) {
  int32_t maxSum = INT_MIN;
  int32_t sum = 0;
  for (auto it = vec.begin(), end = vec.end(); it != end; ++it) {
  /* We use this if statment to apply both properties:
     1. if the sum till now is negative, we start over
     2. a negative element as head of the subarray implies property 1
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
  int N;
  int val;

  std::cin >> T;
  assert(T > 0 && T <= 200);

  for (size_t i = 0; i < T; ++i) {
    std::cin >> N;
    assert(N > 0 && N <= 1000);

    vec.reserve(N);

    for (size_t j = 0; j < N; ++j) {
      std::cin >> val;
      assert(val >= -100 && val <= 100);
      vec.push_back(val);
    }
    std::cout << kadane(vec) << "\n";
    vec.clear();
  }
}
