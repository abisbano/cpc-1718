/*
 IlyaAndQueries.cc
 Author: Andrea Bisbano
 Date: 08/01/18
 Problem: http://codeforces.com/problemset/problem/313/B?locale=en
 Solution:
  Given the input string s of length n, the algorithm create a binary array B, where B[i] is 1 iif
  s[i] = s[i+1], otherwise 0. Then it computes and stores the prefix sum of that array.
  To solve a query is enough to read the prefix sums of the delimiters and compute the difference.
 Time cost: O(N+M) where N is the length of the whole string and O(N) the cost of the computation of the
            prefix sum. M is the number of queries and O(1) the cost of each one.
 Space cost: O(N) because we need to store the prefix sum array.
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
