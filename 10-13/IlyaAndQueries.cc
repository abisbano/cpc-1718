/*
  IlyaAndQueries.cc

  author: Andrea Bisbano
  date: 08/01/18
  problem: http://codeforces.com/problemset/problem/313/B?locale=en

  solution description:
 Given the input string s of length n, the idea is to create a binary array B, where B[i] is 1 iif
  s[i] = s[i+1], otherwise 0. After that, we precompute the prefix-sum of that array and then solving
  the queries is immediate (i.e. reading of two array position and a subtraction).

 The cost of the computation of the prefix sum is O(n), where n is the length of the string.
  After that the cost of each query is O(1). So for m queries, the total cost is O(n+m).
 The cost in space is O(n), the space needed to store the prefix-sum array.
*/

#include <iostream>
#include <cassert>
#include <string>
#include <vector>

std::vector<uint32_t> precomputePrefixSum(std::string str) {
  size_t n = str.length();

  std::vector<uint32_t> result;
  result.reserve(n);
  uint32_t sum = 0;
  result.push_back(sum);

  for (size_t i = 0; i < n-1; ++i) {
    if (str[i] == str[i+1]) {
      ++sum;
    }
    result.push_back(sum);
  }

  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::string str; // input string
  uint32_t m; // number of queries
  uint32_t l;
  uint32_t r;

  std::cin >> str;
  assert(str.length() >= 2 && str.length() <= 100000);

  auto prefixSum = precomputePrefixSum(str);

  std::cin >> m;
  assert(m >= 1 && m <= 100000);

  for (size_t i = 0; i < m; ++i) {
    std::cin >> l;
    std::cin >> r;
    std::cout << prefixSum[r-1] - prefixSum[l-1] << "\n";
  }

  return 0;
}
