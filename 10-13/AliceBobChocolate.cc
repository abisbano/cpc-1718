/*
 AliceBobChocolate.cc
 Author: Andrea Bisbano
 Date: 09/01/18
 Problem: http://codeforces.com/problemset/problem/6/C?locale=en
 solution:
  The algorithm computes both prefix sum and suffix sum of the input array. Prefix sum represent Alice
  and suffix sum Bob. At each step of computation, the algorithm chooses to increase only the smaller
  value and it terminates when all the elements of the array have been processed one time, instead of
  computing the whole sums.
 Time cost: O(n) to scan the elements of the array.
 Space cost: O(1) because there's no need to store whole prefix/suffix sum.
*/

#include <iostream>
#include <cassert>
#include <vector>

uint32_t aliceBobChocolate(std::vector<uint32_t> bars) {
  size_t barAlice = -1, barBob = bars.size() ;
  uint64_t timeAlice = 0, timeBob = 0;
  uint32_t resultAlice = 0, resultBob;

  while (barBob - barAlice != 1) {
    if (timeAlice <= timeBob) {
      ++barAlice;
      timeAlice += bars[barAlice];
    } else {
      --barBob;
      timeBob += bars[barBob];
    }
  }
  return barAlice + 1;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t n;
  uint32_t value;
  std::vector<uint32_t> vec;

  std::cin >> n;
  assert(n >= 1 && n <= 100000);
  vec.reserve(n);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> value;
    vec.push_back(value);
  }

  auto result = aliceBobChocolate(vec);
  std::cout << result << " " << n - result << "\n";
  return 0;
}
