/*
 LongestPrefixSuffix.cc
 Author: Andrea Bisbano
 Date: 12/02/18
 Problem: https://practice.geeksforgeeks.org/problems/longest-prefix-suffix/0
 Solution:
  This algorithm creates and array LPS where for each i, LPS[i] is the maximum length of a prefix which
  is also a suffix in the substring from char 0 to i. To do so it uses the preprocessing algorithm
  of KMP search.
 TODO: explain KMP
 Time cost: O(n)
 Space cost: O(n)
*/

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

int computePrefixFunction(const std::string& text, size_t n) {
  std::vector<int> lps(n,0);
  uint32_t len = 0;

  size_t i = 1;
  while (i < n) {
    if (text[i] == text[len]) {
      ++len;
      lps[i] = len;
      ++i;
    } else {
      if (len != 0) {
        len = lps[len-1];
      } else {
        lps[i] = 0;
        ++i;
      }
    }
  }
  return lps[n-1];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t T;
  std::string text;

  std::cin >> T;
  assert(T >= 1 && T <= 100);

  for (size_t i = 0; i < T; ++i) {
    std::cin >> text;
    std::cout << computePrefixFunction(text, text.length()) << "\n";
  }
  return 0;
}
