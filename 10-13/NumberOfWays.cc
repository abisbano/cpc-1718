/*
  NumberOfWays.cc

  author: Andrea Bisbano
  date: 10/01/18
  problem: http://codeforces.com/problemset/problem/466/C?locale=en

  solution description:
 The idea of this solution is to compute the sum S of the elements of the array A[1..n]. If that number isn't
  divisible for 3 the answer is trivial and is false. Otherwise, we compute and array C where in position i
  we store the number of suffixes of A[i..n] that has as um S/3.
 After that we compute the prefix sum of A and when in position i we have the value S/3, we add C[i+2]
  to the number of the possible solution.
 The cost of this algorithm is O(n), where n is the number of elements of the array. The cost in space
  is also O(n) because we need to store the array C.

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

  std::cout << numberOfWays(vec) << std::endl;
  return 0;
}
