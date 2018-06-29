/*
 LongestPalindromicSubsequence.cc
 Author: Andrea Bisbano
 Date: 28/01/18
 Problem: https://practice.geeksforgeeks.org/problems/longest-palindromic-subsequence/0
 Solution:
  Given a string S of length N, this algorithm creates a DP table of size N*N where the generic element
  T[i][j] is the lenght of the longest palindromic subsequence (LPS) of the substring starting from
  the ith character to the jth. To fill the table, the algorithm starts with the elements in the diagonal
  (they're all 1) and then the genenir element T[i][j] is:
  1. (2 + T[i+1][j-1]) if the two chars are equal
  2. the maximum between T[i-1][j] and T[i][j-1] if these aren't equal (e.g. is the LPS without considering
      one of the border element.
  The solution is the element in the top right corner (e.g. the whole string)
 Time cost: O(N^2)
 Space cost: O(N^2)
 */

#include<vector>
#include<iostream>
#include<cassert>
#include<algorithm>

uint64_t longestPalindromicSubsequence(std::string &str) {
  size_t n = str.size();
  std::vector<std::vector<uint64_t>> table(n, std::vector<uint64_t>(n,0));

  for (int64_t i = n-1; i >= 0; --i) {
    for (size_t j = i; j < n; ++j) {
      if (i == j) {
        table[i][j] = 1;
        continue;
      }
      if (str[i] == str[j]) {
        table[i][j] = 2 + table[i+1][j-1];
      } else {
        table[i][j] = std::max(table[i+1][j], table[i][j-1]);
      }
    }
  }
  return table[0][n-1];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t T;
  std::string str;

  std::cin >> T;
  assert(T >= 1 && T <= 100);

  for (size_t i = 0; i < T; ++i) {
    std::cin >> str;
    assert(str.size() >= 1 && str.size() <= 1000);
    std::cout << longestPalindromicSubsequence(str) << "\n";
  }
  return 0;
}
