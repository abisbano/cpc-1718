/*
 LongestCommonSubsequence.cc
 Author: Andrea Bisbano
 Date: 23/01/18
 Problem: https://practice.geeksforgeeks.org/problems/longest-common-subsequence/0
 Solution:
  this algorithm creates a DP table that stores the LCS of two substrings of the input string.
  Given an element of the table T[i][j] its value is (T[i-1][j-1] + 1) if the ith char of the first
  string and jth char of the second are equal, otherwise is the maximum value between the LCS
  of one of the string without last char (e.g. max between T[i-1][j] and T[i][j-1]).
  The solution is in the bottom right corner of the table.
 Time cost: O(N^2) to fill the table.
 Space cost: O(N^2) to store the table.
 */

#include<vector>
#include<iostream>
#include<cassert>
#include<algorithm>

uint64_t longestCommonSubsequence(size_t a, std::string &str1, size_t b, std::string &str2) {
  std::vector<std::vector<uint64_t>> table(a+1, std::vector<uint64_t>(b+1,0));

  for (size_t i = 1; i <= a; ++i) {
    for (size_t j = 1; j <= b; ++j) {
      if (str1[i-1] == str2[j-1]) {
        table[i][j] = table[i-1][j-1] + 1;
      } else {
        table[i][j] = std::max(table[i-1][j], table[i][j-1]);
      }
    }
  }
  return table[a][b];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t testCases;
  size_t length1, length2;
  std::string str1, str2;

  std::cin >> testCases;
  assert(testCases >= 1 && testCases <= 200);
  for (size_t i = 0; i < testCases; ++i) {
    std::cin >> length1 >> length2;
    assert(length1 >= 1 && length1 <= 100);
    assert(length2 >= 1 && length2 <= 100);
    std::cin >> str1 >> str2;
    std::cout << longestCommonSubsequence(length1, str1, length2, str2) << "\n";
  }
  return 0;
}
