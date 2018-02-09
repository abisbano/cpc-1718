/*
  EditDistance.cc

  author: Andrea Bisbano
  date: 25/01/18
  problem: https://practice.geeksforgeeks.org/problems/edit-distance/0

  solution description:

 FIXME: Clean code and write description of solution

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
