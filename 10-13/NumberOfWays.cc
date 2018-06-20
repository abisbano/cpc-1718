/*
 NumberOfWays.cc
 Author: Andrea Bisbano
 Date: 10/01/18
 Problem: http://codeforces.com/problemset/problem/466/C?locale=en
 Solution:
  The algorithm computes the sum S of all the elements of the array A. If that number isn't
  a multiple of 3 then it replies false. Otherwise, it computes the array C where in each
  position `i' is stored the number of suffixes of the A[i..n] subarray that have sum equal
  to S/3. Then it computes the prefix sum of A and for each position `i', if the sum is equal
  to $/3, it increases the number of possible solutions by C[i+2].
 Time cost: O(n) because we need to compute the suffix sum and the prefix sum of the input array.
 Space cost: O(n) because we need to store the array C.
 */

#include <iostream>
#include <cassert>
#include <string>
#include <vector>

uint64_t numberOfWays(std::vector<int64_t> vec) {
  int64_t sum = 0;
  for (auto i : vec) {
    sum += i;
  }
  if (sum % 3 != 0) {
    return 0;
  }

  sum = sum / 3;
  size_t n = vec.size();
  uint64_t suffixes = 0;
  int64_t partialSum = 0;
  std::vector<uint64_t> B(n, 0);

  uint64_t result = 0;

  for (int64_t i = n-1; i >= 0; --i) {
    partialSum += vec[i];
    if (partialSum == sum) {
      ++suffixes;
    }
    B[i] = suffixes;
  }

  partialSum = 0;

  for (int64_t i = 0; i < n - 2; ++i) {
    partialSum += vec[i];
    if (partialSum == sum) {
      result += B[i+2];
    }
  }

  return result;

}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t n;
  int64_t value;
  std::vector<int64_t> vec;

  std::cin >> n;
  assert(n >= 1 && n <= 500000);
  vec.reserve(n);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> value;
    vec.push_back(value);
  }

  std::cout << numberOfWays(vec) << "\n";
  return 0;
}
