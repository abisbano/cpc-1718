/*
 UpdateTheArray.cc
 Author: Andrea Bisbano
 Date: 12/01/18
 Problem: http://www.spoj.com/problems/UPDATEIT/
 Solution description:
  Given an update (l, r, val) to the array A, instead of updating all the elements in the range (l, r)
  we update only A[l] and A[r+1] increasing and decresing their value by val.
  After that we can compute the prefix sum of the array and in each position we will have the updated
  value of the original array.
  We can do this because the queries are after all the update operation and so we pay only one time
  the biggest cost of the process.
 Time cost: O(n) for each query and O(1) for each update.
 Space cost: O(n) to store the prefix sum array.
*/

#include <iostream>
#include <cassert>
#include <vector>

std::vector<uint64_t> computeSum(std::vector<uint64_t> &vec, size_t n) {
  std::vector<uint64_t> result(n,0);
  result[0] = vec[0];
  for (size_t i = 1; i < n; ++i) {
    result[i] = result[i-1] + vec[i];
  }
  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t testCases;

  uint32_t n, u, q;
  uint32_t l, r, val;
  uint32_t index;

  std::cin >> testCases;
  assert(testCases >= 1 && testCases <= 10);

  for(size_t i = 0; i < testCases; ++i) {
    std::cin >> n >> u;
    assert(n >= 1 && n <= 10000);
    assert(u >= 1 && u <= 100000);

    std::vector<uint64_t> vec(n+1, 0);

    for (size_t j = 0; j < u; ++j) {
      std::cin >> l >> r >> val;
      assert(l >= 0 && l < n);
      assert(r >= 0 && r < n);
      assert(val >= 0 && val <= 10000);

      vec[l] += val;
      vec[r+1] -= val;
    }

    std::cin >> q;

    auto prefixSum = computeSum(vec, n);

    for (size_t j = 0; j < q; ++j) {
      std::cin >> index;
      std::cout << prefixSum[index] << "\n";
    }
  }
  return 0;
}
