/*
 EditDistance.cc
 Author: Andrea Bisbano
 Date: 25/01/18
 Problem: https://practice.geeksforgeeks.org/problems/edit-distance/0
 Solution:
  This algorithm creates a DP table T where T[i][j] represent the edit distance between the first i
  characters of the first string and the first j characters of the second string.
  The first line and the first column of the row (e.g. i = 0 or j = 0) are initialized with the difference
  between the two lengths (as only insert operation are needed). Then, for any T[i][j], there are two cases:
  - if the last chars of both strings are the same, then it is equal to T[i-1][j-1] (e.g. the edit distance
    is the same without considering last characters of both strings)
  - otherwise it is the the minimium adjacent (between T[i-1][j], T[i][j-1] and T[i-1][j-1]) increased by 1.
 Time cost:
 Space cost:
 */

#include<vector>
#include<iostream>
#include<cassert>
#include<algorithm>
#include<string>

uint64_t editDistance(const std::string &str1, const std::string &str2) {

  size_t r = str1.size();
  size_t c = str2.size();
  std::vector<std::vector<uint64_t>> table(r+1, std::vector<uint64_t>(c+1, 0));

  for (size_t i = 0; i <= r; ++i) {
    for (size_t j = 0; j <= c; ++j) {
      if (i == 0) {
        table[i][j] = j;
        continue;
      }
      if (j == 0) {
        table[i][j] = i;
        continue;
      }

      if (str1[i-1] == str2[j-1]) {
        table[i][j] = table[i-1][j-1];
      } else {
        table[i][j] = 1 + std::min({table[i-1][j], table[i][j-1],table[i-1][j-1]});
      }
    }
  }
  return table[r][c];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t T;
  size_t l1, l2;
  std::string str1, str2;

  std::cin >> T;
  assert(T >= 1 && T <= 50);
  for (size_t i = 0; i < T; ++i) {
    std::cin >> l1 >> l2;
    assert(l1 >= 1 && l1 <= 100);
    assert(l2 >= 1 && l2 <= 100);
    std::cin >> str1 >> str2;

    std::cout << editDistance(str1, str2) << "\n";
  }
  return 0;
}
