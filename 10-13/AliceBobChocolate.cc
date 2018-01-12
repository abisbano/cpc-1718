/*
  AliceBobChocolate.cc

  author: Andrea Bisbano
  date: 09/01/18
  problem: http://codeforces.com/problemset/problem/6/C?locale=en

  solution description:
 The idea of this solution is to compute prefix sum and suffix sum of the same array. We don't need to
  compute the whole sums, so at each step of the iteration we choose to increment only the one that has
  a smaller value and we keep count of the number of elements processed by the prefix sum. When we have
  processed all the elements of the array we can stop the algorithm and we have the solution.
 The cost in time for this algorithm is O(n), where n is the number of elements in the array and the
  cost in space is O(1), since we don't have to store the prefix/suffix sum but only the partial sum.
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
