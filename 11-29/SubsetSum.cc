/*
 SubsetSum.cc
 Author: Andrea Bisbano
 Date: 26/01/18
 Problem: https://practice.geeksforgeeks.org/problems/subset-sum-problem/0
 Solution:
  This algorithm computes the sum S of the input array A. If it's an odd number then it immediately returns
  false, otherwise it creates a boolean DP table T of size N * (S/2), where N is the length of A.
  The element T[i][j] represent the subproblem limited to the first i elements and to the sum j.
  The generic element T[i][j] is true if one of these conditions holds:
  1. T[i-1][j] is true (e.g. the latest element isn't part of the sum)
  2. T[i-1][j - A[i-1]] is true (e.g. the latest element is part of the sum)
  Thanks to the first condition, instead of computing the whole table it is enough to stop after
  the algorithm finds a row there the last element is true (e.g. T[i][S] is true for any i).
 Time cost: O(NS), where N is the lenght of input array and S the sum.
 Space cost: O(NS) to store the whole table.
 */

#include<vector>
#include<iostream>
#include<cassert>
#include<algorithm>

bool isSubsetSum(const std::vector<uint64_t> &vec, size_t n, uint64_t sum) {
  if (n <= 1) {
    return false;
  }
  if (sum % 2 == 1) {
    return false;
  }
  sum /= 2;
  std::vector<std::vector<bool>> table(n+1, std::vector<bool>(sum+1, false));

  for (size_t i = 0; i <= n; ++i) {
    table[i][0] = true;
  }
  for (size_t i = 1; i <= n; ++i) {
    for (size_t j = 1; j <= sum; ++j) {
      table[i][j] = table[i-1][j] || (vec[i-1] <= j && table[i-1][j-vec[i-1]]);
    }
    if (table[i][sum]) {
      return true;
    }
  }
  return false;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t T, N;
  uint64_t value;
  uint64_t sum;
  std::vector<uint64_t> sequence;

  std::cin >> T;
  assert(T >= 1 && T <= 100);
  for (size_t i = 0; i < T; ++i) {
    std::cin >> N;
    assert(N <= 100);
    sequence.reserve(N);
    sum = 0;
    for (size_t i = 0; i < N; ++i) {
      std::cin >> value;
      assert(value <= 1000);
      sum += value;
      sequence.push_back(value);
    }
    std::cout << (isSubsetSum(sequence, N, sum) ? "YES" : "NO") << "\n";

    sequence.clear();
  }
  return 0;
}
