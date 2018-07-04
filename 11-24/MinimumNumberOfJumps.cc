/*
 MinimumNumberOfJumps.cc
 Author: Andrea Bisbano
 Date: 25/01/18
 Problem: https://practice.geeksforgeeks.org/problems/minimum-number-of-jumps/0
 Solution description:
  This algorithm uses the support of three values: maxReach, step and jumps.
  - maxReach represent the maximum reachable index in any moment. It is initialized with the value
    of the first element of the input array.
  - step represent the number of steps that can be done before a jump (it is also initalized with
    the value of the first element of the input array).
  - jumps represent the minimum number of jumps needed to reach the current index (starts from 1)
  Then the algorithm loops on the input array and at each step:
  1. if the current index is the last element it means the end is reachable and the solution
    is the value of `jumps'.
  2. it computes the new maximum index reachable, which is the maximum between the current and
    the last index reachable from the current index.
  3. decreases the step counter.
  4. if there aren't steps left, to go to the next index is needed a jump, so it increments a jump,
    but only if the current index is in the reachable range (e.g. is less than maxReach).
 Time cost: O(N)
 Space cost: O(1)
 */

#include<vector>
#include<iostream>
#include<cassert>
#include<algorithm>

int64_t minimumNumberOfJumps(const std::vector<size_t> &vec, size_t n) {

  if (n <= 1) {
    return 0;
  }
  if (vec[0] == 0) {
    return -1;
  }

  size_t maxReach = vec[0]; // maximal reachable index in the array
  size_t step = vec[0]; //
  size_t jumps = 1;

  for (size_t i = 1; i < n; ++i) {
    if (i == n-1) {
      return jumps;
    }
    maxReach = std::max(maxReach, i+vec[i]);
    --step;

    if (step == 0) {
      ++jumps;
      if (i >= maxReach) {
        return -1;
      }
      step = maxReach - i;
    }

  }
  return -1;

}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t T, N;
  size_t value;
  std::vector<size_t> vec;

  std::cin >> T;
  assert(T >= 1 && T <= 40);
  for (size_t i = 0; i < T; ++i) {
    std::cin >> N;
    assert(N >= 1 && N <= 100);
    vec.reserve(N);
    for (size_t i = 0; i < N; ++i) {
      std::cin >> value;
      assert(value >= 0 && value <= 100);
      vec.push_back(value);
    }

    std::cout << minimumNumberOfJumps(vec, N) << "\n";
    vec.clear();
  }
  return 0;
}
