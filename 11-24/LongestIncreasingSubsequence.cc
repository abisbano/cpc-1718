/*
 LongestIncreasingSubsequence.cc
 Author: Andrea Bisbano
 Date: 24/01/18
 Problem: https://practice.geeksforgeeks.org/problems/longest-increasing-subsequence/0
 Solution:
  This algorithm creates an array E where each element is the minimum possible last value of an IS of
  size equal to the index. At each step the algorithm processes a value V. If V is bigger than the last
  element of E, it's added at the end of the array. Otherwise, the algorithm searches in E the first
  value greater than V, and it replaces it in E with V.
  The LIS is the size of the array after the algorithm has processed the whole input.
 Time cost: O(NlogN)
 Space cost: O(N) because the new array can't exceed the input size.
 */

#include<vector>
#include<iostream>
#include<cassert>
#include<algorithm>

size_t binarySearch(const std::vector<uint64_t> &v, int l, int r, uint64_t key) {
  while (r-l > 1) {
    size_t m = l + (r-l)/2;
    if (v[m] >= key) {
      r = m;
    } else {
      l = m;
    }
  }
  return r;
}

uint64_t longestIncreasingSubsequence(const std::vector<uint64_t> &sequence) {
  if (sequence.empty()) {
    return 0;
  }
  size_t n = sequence.size();
  uint64_t size = 1;
  std::vector<uint64_t> ends(n,0);
  ends[0] = sequence[0];
  for (size_t i = 1; i < n; ++i) {
    if (sequence[i] > ends[size-1]) {
      ends[size++] = sequence[i];
    } else {
      ends[binarySearch(ends, -1, size-1, sequence[i])] = sequence[i];
    }
  }
  return size;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t T, N;
  uint64_t value;
  std::vector<uint64_t> sequence;

  std::cin >> T;
  assert(T >= 1 && T <= 100);
  for (size_t i = 0; i < T; ++i) {
    std::cin >> N;
    assert(N <= 1000);
    sequence.reserve(N);
    for (size_t i = 0; i < N; ++i) {
      std::cin >> value;
      assert(value <= 300);
      sequence.push_back(value);
    }

    std::cout << longestIncreasingSubsequence(sequence) << "\n";
    sequence.clear();
  }
  return 0;
}
