/*
  AlternativeThinking.cc

  author: Andrea Bisbano
  date: 18/01/18
  problem: http://codeforces.com/problemset/problem/603/A?locale=en

  solution description:
 TO BE WRITTEN
 */

#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>

uint64_t countAlternative(const std::string &str, uint64_t n) {
  uint64_t count = 2;
  char last = '\0';
  for (const char &c : str) {
    if (c != last) {
      ++count;
      last = c;
    }
  }
  return std::min(count, n);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  uint64_t n;
  std::string str;

  std::cin >> n;
  std::cin >> str;

  std::cout << countAlternative(str, n) << std::endl;
  return 0;

}
