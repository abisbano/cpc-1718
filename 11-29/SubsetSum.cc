/*
  SubsetSum.cc

  author: Andrea Bisbano
  date: 26/01/18
  problem: https://practice.geeksforgeeks.org/problems/subset-sum-problem/0

  solution description:

 FIXME: Clean code and write description of solution

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
    assert(N >= 0 && N <= 100);
    sequence.reserve(N);
    sum = 0;
    for (size_t i = 0; i < N; ++i) {
      std::cin >> value;
      assert(value >= 0 && value <= 1000);
      sum += value;
      sequence.push_back(value);
    }

    std::cout << (isSubsetSum(sequence, N, sum) ? "YES" : "NO") << "\n";
    sequence.clear();
  }
  return 0;
}
