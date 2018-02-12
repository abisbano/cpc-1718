/*
 WilburArray.cc
 Author: Andrea Bisbano
 Date: 18/01/18
 Problem: http://codeforces.com/problemset/problem/596/B?locale=en
 Solution:
  The idea is to keep a counter K which starts from 0 that represent the previous element of the
  array. For each element of the array we compute the difference between the value and K and update
  K with the current value. The sum of differences is the minumum number of operation to create the
  result array.
 Time cost: O(N) to scan the input array.
 Space cost: O(1) beacuse we need only one support variable.
*/

#include <iostream>
#include <cassert>
#include <vector>

uint64_t wilburArray(const std::vector<int64_t> &vec) {
  uint64_t result = 0;
  int64_t current = 0;
  for (const int64_t &v : vec) {
    if (v > current) {
      result += (v - current);
    } else {
      result += (current - v);
    }
    current = v;
  }
  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::vector<int64_t> vec;
  size_t n;
  int64_t value;

  std::cin >> n;
  assert(n >= 1 && n <= 200000);
  vec.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> value;
    assert (value >= -1000000000 && value <= 1000000000);
    vec.push_back(value);
  }

  std::cout << wilburArray(vec) << "\n";
}
