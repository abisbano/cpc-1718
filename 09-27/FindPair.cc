/*
 FindPair.cc
 Author: Andrea Bisbano
 Date: 19/11/17
 Problem: http://codeforces.com/problemset/problem/160/C?locale=en
 Solution:
  The idea is to sort the input array in increasing order. Then the pair `k' will be the couple <a_i, a_j>
  where i = k/n and j = ((k-1)-l*n)/r. `r' is the number of keys equal to a_i and `l' is the number of keys
  smaller than a_i.
 Time cost: O(nlogn) to sort the input array.
 Space cost: O(1)
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

std::pair<int64_t, int64_t> findPair(std::vector<int64_t> &vec, int64_t k) {
  int64_t first, second;

  std::sort(vec.begin(), vec.end());

  uint64_t n = vec.size();
  first = vec[(k-1) / n];
  uint64_t l = 0;
  for (; l < n; ++l) {
    if (vec[l] == first) break;
  }
  uint64_t r = l;
  // manual search is better than std::find
  for (; r < n; ++r) {
    if (vec[r] != first) break;
  }
  r = r - l;

  second = vec[((k-1)-l*n)/r];

  return std::make_pair(first, second);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  
  uint64_t size;
  uint64_t k;
  std::vector<int64_t> vec;
  int64_t val;

  std::cin >> size;
  assert(size <= 100000);
  vec.reserve(size);
  std::cin >> k;
  assert(k >= 1 && k <= size*size);
  for (uint64_t i = 0; i < size; ++i) {
    std::cin >> val;
    vec.push_back(val);
  }

  auto result = findPair(vec, k);

  std::cout << result.first << " " << result.second << "\n";
}
