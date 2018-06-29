/*
 LongestBitonicSubsequence.cc
 Author: Andrea Bisbano
 Date: 26/01/18
 Problem: https://practice.geeksforgeeks.org/problems/longest-bitonic-subsequence/0
 Solution:
  This algorithm creates a DP array where each element represent the length of the Bitonic Subsequence
  if it's considered the element in that position as in the middle of the sequence (e.g. after that
  element the sequence is decreasing).
  To create this array, it's used a variation of the algorithm for the Longest Increasing Subsequece.
  That algorithm is performed two times: the first one on the input array in regular order and the second
  time on the same array in reverse order. At every execution the solution array is generated using an
  accumulator that counts the lenght of the incresing subsequence up to that particular position.
  Then, after the two computations the result is the maximal element of the generated array decresed
  by 1, because the central element is counted two times.
 Time cost: O(NlogN) which is the same cost of the LIS.
 Space cost: O(N) because the solution array is of the same size of the input array.
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

template <typename it1, typename it2>
void accumulateLIS(it1 begin, it1 end, it2 accumulator) {
  if (begin == end) {
    return;
  }
  size_t n = end - begin;
  uint64_t size = 1;
  std::vector<uint64_t> lastEl(n,0);
  lastEl[0] = *begin;
  for ( ; begin != end; ++begin, ++accumulator) {
    if (*begin > lastEl[size-1]) {
      lastEl[size++] = *begin;
    } else {
      lastEl[binarySearch(lastEl, -1, size-1, *begin)] = *begin;
    }
    *accumulator += size;
  }
}

uint64_t longestBitonicSubsequence(std::vector<uint64_t> &sequence) {
  if (sequence.size() == 0) {
    return 0;
  }
  size_t N = sequence.size();
  uint64_t value, max = 0;

  std::vector<uint64_t> vec(N,0);
  // First computation: after that `vec' contains the length of IS for each position.
  accumulateLIS(sequence.begin(), sequence.end(), vec.begin());
  // Second computation: after that `vec' contains the lengths of BS for each position.
  accumulateLIS(sequence.rbegin(), sequence.rend(), vec.rbegin());
  return *std::max_element(vec.begin(), vec.end()) - 1;
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
    assert(N <= 100);
    sequence.reserve(N);
    for (size_t i = 0; i < N; ++i) {
      std::cin >> value;
      sequence.push_back(value);
    }
    std::cout << longestBitonicSubsequence(sequence) << "\n";
    sequence.clear();
  }
  return 0;
}
