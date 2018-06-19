/*
 Towers.cc
 Author: Andrea Bisbano
 Date: 18/10/17
 Problem: http://codeforces.com/problemset/problem/37/A?locale=en
 Solution:
  This solution don't use the comparison model. We exploit the fact that the maximum possibile length of
  a bar is 1000 (and we call it M). We create a support array A of M+1 elements, where for each i
  A[i] is the number of bars of length i in the input.
  While we are creating the input array we compare the current value to the maximum value so far,
  so we don't have to scan the whole support array.
 Time cost: O(N) because we just have to scan the input array one time.
 Space cost: O(M) to store the support array.
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

#define MAX_VALUE 1000

void computeTowers(const std::vector<uint32_t> &vec, uint32_t& resultHeight, uint32_t& resultTowers) {
  std::vector<uint32_t> towers = std::vector<uint32_t>(MAX_VALUE + 1, 0);
  for (auto val : vec) {
    if (towers[val] == 0) {
      // That's a new tower, so we increase counting.
      ++resultTowers;
    }
    ++towers[val];
    if (towers[val] > resultHeight) {
      resultHeight = towers[val];
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  
  uint32_t N = 0;
  uint32_t val = 0;
  std::vector<uint32_t> vec;
  uint32_t resultHeight = 0;
  uint32_t resultTowers = 0;

  std::cin >> N;
  assert(N <= 1000);
  vec.reserve(N);
  for (uint32_t i = 0; i < N; ++i) {
    std::cin >> val;
    assert(val <= MAX_VALUE);
    vec.push_back(val);
  }
  computeTowers(vec, resultHeight, resultTowers);
  std::cout << resultHeight << " " << resultTowers << "\n";
}
