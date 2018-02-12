/*
 LittleGirlMaximumSum.cc
 Author: Andrea Bisbano
 Date: 10/01/18
 Problem: http://codeforces.com/problemset/problem/276/C?locale=en
 Solution:
  The idea of this solution is to compute the number of times each element is called in a query and sort the
  element in a way s.t. the largest value is called the most.
  To do so, we create an array F s.t. given a query (l, r), we increase F[l] and decrease F[r]. By doing
  that, the prefix sum of F in any position will be the number of times that this position is queried.
  After the computation of the prefix sum of F, we sort it and we sort the input one. And at last we compute
  the maximum sum by just summing the element i F[i] times.
 Time cost: O(nlogn) because the sorting cost is dominant.
 Space cost: O(n) vecause we need to store the frequency array and its prefix sum array.
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

uint64_t maximumSum(std::vector<uint64_t> &values, std::vector<int32_t> &freq) {

  uint64_t result = 0;
  size_t n = values.size();
  std::vector<uint32_t> prefixSum(n,0);
  uint64_t sum = 0;

  prefixSum[0] = freq[0];
  for (size_t i = 1; i < n; ++i) {
    prefixSum[i] = prefixSum[i-1] + freq[i];
  }

  std::sort(values.begin(), values.end());
  std::sort(prefixSum.begin(), prefixSum.end());

  for (size_t i = 0; i < n; ++i) {
    result += (values[i] * prefixSum[i]);
  }

  return result;

}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  uint64_t n, q;
  uint64_t l, r;

  std::cin >> n;
  assert(n >= 1 && n <= 200000);

  std::cin >> q;
  assert(q >= 1 && q <= 200000);

  std::vector<uint64_t> vec(n,0);
  std::vector<int32_t> freq(n+1,0);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> vec[i];
  }

  for (size_t i = 0; i < q; ++i) {
    std::cin >> l;
    std::cin >> r;
    assert(l <= n && r <= n);
    ++freq[l-1];
    --freq[r];
  }

  std::cout << maximumSum(vec, freq) << "\n";

  return 0;
}
