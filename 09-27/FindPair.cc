/*
 FindPair.cc
 Author: Andrea Bisbano
 Date: 19/11/17
 Problem: http://codeforces.com/problemset/problem/160/C?locale=en
 Solution:
  The idea is to sort the input array in increasing order. Then the pair `k' will be the couple <a_i, a_j>
  where i=k/n and j=((k-1)-l*n)/r and `r' in the number of keys equal to a_i and `l' the number of keys smaller
  than a_i.
 Time ost: O(nlogn) because we need to sort the input array.
 Space cost: O(1)
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

std::pair<int64_t, int64_t> findPair(std::vector<int64_t> &vec, size_t k) {
  int64_t first, second;

  std::sort(vec.begin(), vec.end());
  size_t n = vec.size();

  size_t i = (k-1) / n;
  first = vec[i];
  size_t l = 0;
  for (; l < n; ++l) {
    if (vec[l] == first) break;
  }
  size_t r = std::count(vec.begin(), vec.end(), first);
  second = vec[((k-1)-l*n)/r];

  return std::make_pair(first, second);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  
  size_t size;
  size_t k;
  std::vector<int64_t> vec;
  int64_t val;

  std::cin >> size;
  assert(size >= 1 && size <= 10000);
  vec.reserve(size);
  std::cin >> k;
  assert(k >= 1 && k <= size*size);
  for (int i = 0; i < size; ++i) {
    std::cin >> val;
    assert(val >= -1000000000 && val <= 1000000000);
    vec.push_back(val);
  }

  auto result = findPair(vec, k);

  std::cout << result.first << " " << result.second << std::endl;


}
