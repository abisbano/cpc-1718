/*
  LongestIncreasingSubsequence.cc

  author: Andrea Bisbano
  date: 26/01/18
  problem: https://practice.geeksforgeeks.org/problems/longest-bitonic-subsequence/0

  solution description:

 FIXME: Clean code and write description of solution

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
  std::vector<uint64_t> ends(n,0);
  ends[0] = *begin;
  while (begin != end) {
    if (*begin < ends[0]) {
      ends[0] = *begin;
    } else if (*begin > ends[size-1]) {
      ends[size++] = *begin;
    } else {
      ends[binarySearch(ends, -1, size-1, *begin)] = *begin;
    }
    *accumulator += size;
    ++begin;
    ++accumulator;
  }
}

uint64_t longestBitonicSubsequence(std::vector<uint64_t> &sequence) {
  if (sequence.size() == 0) {
    return 0;
  }
  size_t N = sequence.size();
  uint64_t value, max = 0;

  std::vector<uint64_t> vec(N,0);
  accumulateLIS(sequence.begin(), sequence.end(), vec.begin());
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
    assert(N >= 0 && N <= 100);
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
